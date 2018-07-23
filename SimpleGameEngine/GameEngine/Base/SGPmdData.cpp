//
//  SGPmdData.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/06/15.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGPmdData.hpp"
#include "SGConsole.hpp"
#include "SGUtil.hpp"
#include "SGShaderModel3D.hpp"
#include "SGShaderModel3DEdge.hpp"
#include "SGSpriteCache.hpp"

#define PMDFILE_HEADER_MODELNAME_LENGTH 20
#define PMDFILE_HEADER_COMMENT_LENGTH 256
#define PMDFILE_MATERIAL_TEXTURENAME_LENGTH 20
#define PMDFILE_BONE_NAME_LENGTH 20

using namespace SimpleGameEngine;

#include "SGFileUtils.hpp"

PmdHeader::PmdHeader()
: version(0.0f)
, name("")
, comment("")
{
    
}

std::shared_ptr<PmdData> PmdData::create(std::string& filename)
{
    std::shared_ptr<PmdData> obj {new (std::nothrow) PmdData};
    std::shared_ptr<FileUtils> fileUtils = FileUtils::getInstance();
    RawData* raw = fileUtils->getRawData(filename);
    obj->loadHeader(raw, &obj->_header);
    obj->loadVertices(raw);
    obj->loadIndices(raw);
    obj->loadMaterial(raw);
    obj->loadBone(raw);
    obj->createTextureList();
    obj->calcAABB();
    obj->setShaderProgram(ShaderManager::ShaderType::MODEL_3D);

    return obj;
}

PmdData::PmdData()
: _minPoint(Vec3 {-10, -10, -10})
, _maxPoint(Vec3 { 10, 10, 10})
{
    shaderEdge = _shaderManager->getShaderProgram(ShaderManager::ShaderType::MODEL_3D_EDGE);
}

void PmdData::draw()
{
    const Vec3 cameraPosition = Vec3::create(0, _maxPoint.y * 0.7f, _minPoint.z * 7.0f);
    const Vec3 cameraLook = Vec3::create(0, _maxPoint.y * 0.3f, 0);
    const Vec3 cameraUp = Vec3::create(0, 1, 0);
    const GLfloat projectionNear = 1.0f;
    const GLfloat projectionFar = (_maxPoint.z - _minPoint.z) * 30.0f;
    const GLfloat projectionFovY = 45.0f;

    _camera->setPosition(cameraPosition);
    _camera->setLook(cameraLook);
    _camera->setUp(cameraUp);
    _camera->setProjectionNear(projectionNear);
    _camera->setProjectionFar(projectionFar);
    _camera->setProjectionFovY(projectionFovY);

    std::dynamic_pointer_cast<ShaderModel3D>(_shaderProgram)->setWlp(_camera->getWlp());
    std::dynamic_pointer_cast<ShaderModel3D>(_shaderProgram)->setModel(this);
    
    _shaderProgram->setAlpha(_alpha);
    _shaderProgram->draw();
    
    std::dynamic_pointer_cast<ShaderModel3DEdge>(shaderEdge)->setWlp(_camera->getWlp());
    std::dynamic_pointer_cast<ShaderModel3DEdge>(shaderEdge)->setModel(this);
    std::dynamic_pointer_cast<ShaderModel3DEdge>(shaderEdge)->draw();
}

void PmdData::loadHeader(RawData* data, PmdHeader* header)
{
    GLbyte magic[3] = "";
    readBytes(data, magic, sizeof(magic));
    if (memcmp("Pmd", magic, sizeof(magic))) {
        Console::logDebug("Magic Error %c%c%c", magic[0], magic[1], magic[2]);
        return;
    }
    
    readBytes(data, &header->version, sizeof(GLfloat));
    if (header->version != 1.0f) {
        Console::logDebug("File Version Error(%f)", header->version);
        return;
    }
    
    readBytes(data, header->name, PMDFILE_HEADER_MODELNAME_LENGTH);
    readBytes(data, header->comment, PMDFILE_HEADER_COMMENT_LENGTH);
    
    Util::sjisToUtf8(header->name, sizeof(header->name));
    Util::sjisToUtf8(header->comment, sizeof(header->comment));
    
    Console::logDebug("PMD Name: %s", header->name);
    Console::logDebug("PMD Comment: %s", header->comment);
    
}

void PmdData::loadVertices(SimpleGameEngine::RawData *data)
{
    const GLuint numVertices = readLE32(data);
    Console::logDebug("Vertices: %d", numVertices);
    
    _vertices = (PmdVertex*)malloc(sizeof(PmdVertex) * numVertices);
    _verticesNum = numVertices;
    
    for (int i = 0; i < numVertices; ++i) {
        PmdVertex *v = &_vertices[i];
        
        readBytes(data, &v->position, sizeof(Vec3));
        readBytes(data, &v->normal, sizeof(Vec3));
        readBytes(data, &v->uv, sizeof(Vec2));
        readBytes(data, &v->extra.boneNum, sizeof(GLushort) * 2);
        readBytes(data, &v->extra.boneWeight, sizeof(GLbyte));
        readBytes(data, &v->extra.edgeFlag, sizeof(GLbyte));
    }
}

void PmdData::loadMaterial(SimpleGameEngine::RawData *data)
{
    const GLuint numMaterials = readLE32(data);
    _materials = (PmdMaterial*)malloc(sizeof(PmdMaterial) * numMaterials);
    _materialsNum = numMaterials;
    
    Console::logDebug("Materials: %d", numMaterials);
    
    int sumVert = 0;
    for (int i = 0; i < numMaterials; ++i) {
        PmdMaterial *m = &_materials[i];
        
        readBytes(data, &m->diffuse, sizeof(Vec4));
        readBytes(data, &m->extra.shininess, sizeof(GLfloat));
        readBytes(data, &m->extra.specularColor, sizeof(Vec3));
        readBytes(data, &m->extra.ambientColor, sizeof(Vec3));
        readBytes(data, &m->extra.toonIndex, sizeof(GLubyte));
        readBytes(data, &m->extra.edgeFlag, sizeof(GLubyte));
        readBytes(data, &m->indicesNum, sizeof(GLuint));
        
        // テクスチャ名を読み込む
        {
            readBytes(data, m->diffuseTextureName, PMDFILE_MATERIAL_TEXTURENAME_LENGTH);
            
            // エフェクトテクスチャが含まれていれば文字列を分離する
            // diffuse.png*effect.spaのように"*"で区切られている
            GLchar *p = strchr(m->diffuseTextureName, '*');
            if (p) {
                // diffuseは"*"を無効化することで切る
                *p = '\0';
                // エフェクトは文字列コピーする
                strcpy(m->extra.effectTextureName, p + 1);
            } else {
                // エフェクトが無いなら最初の文字でターミネートする
                m->extra.effectTextureName[0] = '\0';
            }
            
            // SJISで文字列が格納されているため、UTF-8に変換をかける
            Util::sjisToUtf8(m->diffuseTextureName, sizeof(m->diffuseTextureName));
            Util::sjisToUtf8(m->extra.effectTextureName, sizeof(m->extra.effectTextureName));
            
        }
        
        Console::logDebug("material[%d] tex(%s) effect(%s) vert(%d) face(%d) toon(%d)", i, m->diffuseTextureName, m->extra.effectTextureName, m->indicesNum, m->indicesNum / 3, (int )m->extra.toonIndex);
        
        sumVert += m->indicesNum;
    }
    
    Console::logDebug("sum vert(%d) -> num(%d)", sumVert, _indicesNum);
    assert(sumVert == _indicesNum);
}

void PmdData::loadIndices(SimpleGameEngine::RawData *data)
{
    const GLuint numIndices = readLE32(data);
    Console::logDebug("Indices: %d", numIndices);
    
    _indices = (GLushort*)malloc(sizeof(GLushort) * numIndices);
    _indicesNum = numIndices;
    
    readBytes(data, _indices, sizeof(GLushort) * numIndices);
    
    {
        for (int i = 0; i < numIndices; ++i) {
            // インデックスの指す値は頂点数を下回らなければならない
            assert(_indices[i] < _verticesNum);
        }
    }
}

void PmdData::loadBone(SimpleGameEngine::RawData *data)
{
    const GLuint numBones = readLE16(data);
    _bones = (PmdBone*)malloc(sizeof(PmdBone) * numBones);
    _bonesNum = numBones;
    Console::logDebug("bones: %d", numBones);
    
    for (int i = 0; i < numBones; ++i) {
        PmdBone *bone = &_bones[i];
        
        readBytes(data, bone->name, PMDFILE_BONE_NAME_LENGTH);
        Util::sjisToUtf8(bone->name, sizeof(bone->name));
        
        readBytes(data, &bone->parentBoneIndex, sizeof(GLshort));
        readBytes(data, &bone->extra.tailPosBoneIndex, sizeof(GLshort));
        readBytes(data, &bone->extra.type, sizeof(GLbyte));
        readBytes(data, &bone->extra.ikParentBoneIndex, sizeof(GLshort));
        readBytes(data, &bone->position, sizeof(Vec3));
    }
}

void PmdData::createTextureList()
{
    for (int i = 0; i < _materialsNum; ++i) {
        PmdMaterial* material = &_materials[i];
        
        if (strlen(material->diffuseTextureName)) {
            std::string texname(material->diffuseTextureName);
            texname += ".png";
            Console::logDebug("Texture name: %s", texname.c_str());
            std::shared_ptr<SpriteCache> spriteCache = SpriteCache::getInstance();
            std::shared_ptr<Texture2D> t = spriteCache->getTextureData(texname);
            _textureList[texname] = t;
        }
    }
}

void PmdData::calcAABB()
{
    _minPoint = Vec3::create(10000, 10000, 10000);
    _maxPoint = Vec3::create(-10000, -10000, -10000);
    
    for (int i = 0; i < _verticesNum; ++i) {
        _minPoint.x = (GLfloat) fmin(_minPoint.x, _vertices[i].position.x);
        _minPoint.y = (GLfloat) fmin(_minPoint.y, _vertices[i].position.y);
        _minPoint.z = (GLfloat) fmin(_minPoint.z, _vertices[i].position.z);
        
        _maxPoint.x = (GLfloat) fmax(_maxPoint.x, _vertices[i].position.x);
        _maxPoint.y = (GLfloat) fmax(_maxPoint.y, _vertices[i].position.y);
        _maxPoint.z = (GLfloat) fmax(_maxPoint.z, _vertices[i].position.z);
    }
}

int32_t PmdData::readLE32(SimpleGameEngine::RawData *data)
{
    int32_t w0 = (int16_t) (data->readHead)[0] & 0xFF;
    int32_t w1 = (int16_t) (data->readHead)[1] & 0xFF;
    int32_t w2 = (int16_t) (data->readHead)[2] & 0xFF;
    int32_t w3 = (int16_t) (data->readHead)[3] & 0xFF;
    
    data->readHead += 4;
    return (w3 << 24) | (w2 << 16) | (w1 << 8) | w0;
}

int16_t PmdData::readLE16(SimpleGameEngine::RawData *data)
{
    int16_t w0 = (int16_t) (data->readHead)[0] & 0xFF;
    int16_t w1 = (int16_t) (data->readHead)[1] & 0xFF;
    
    data->readHead += 2;
    return (w1 << 8) | w0;
}

void PmdData::readBytes(SimpleGameEngine::RawData *data, void *result, int bytes)
{
    memcpy(result, data->readHead, bytes);
    data->readHead += bytes;
}
