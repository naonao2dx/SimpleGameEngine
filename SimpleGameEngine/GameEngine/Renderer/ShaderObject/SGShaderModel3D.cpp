//
//  SGShaderModel3D.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/06/15.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGShaderModel3D.hpp"
#include "SGSpriteCache.hpp"

using namespace SimpleGameEngine;

ShaderModel3D::ShaderModel3D(const GLchar* vertShaderSource, const GLchar* fragShaderSource)
{
    createShader(vertShaderSource, fragShaderSource);
    init();
}

bool ShaderModel3D::init()
{
    _attrPos = glGetAttribLocation(_shader, "attr_pos");
    assert(_attrPos >= 0);
    
    _attrUV = glGetAttribLocation(_shader, "attr_uv");
    assert(_attrUV >= 0);
    
    _unifColor = glGetUniformLocation(_shader, "unif_color");
    assert(_unifTexture >= 0);
    
    _unifTexture = glGetUniformLocation(_shader, "unif_texture");
    assert(_unifTexture >= 0);
    
    _unifWlp = glGetUniformLocation(_shader, "unif_wlp");
    assert(_unifWlp >= 0);
    
    return true;
}

void ShaderModel3D::draw()
{
    ShaderBase3D::draw();
    
    glEnableVertexAttribArray(_attrPos);
    glEnableVertexAttribArray(_attrUV);
    
    glVertexAttribPointer(_attrPos, 3, GL_FLOAT, GL_FALSE, sizeof(PmdVertex), &_model->_vertices[0].position);
    glVertexAttribPointer(_attrUV, 2, GL_FLOAT, GL_FALSE, sizeof(PmdVertex), &_model->_vertices[0].uv);
    
    glUniformMatrix4fv(_unifWlp, 1, GL_FALSE, (GLfloat*)_wlp.m);
    
    GLint beginIndecesIndex = 0;
    
    for (int i = 0; i < _model->_materialsNum; ++i) {
        PmdMaterial* material = &_model->_materials[i];
        std::string textureName { material->diffuseTextureName };
        textureName += ".png";
        std::shared_ptr<SpriteCache> spriteCache = SpriteCache::getInstance();
        std::shared_ptr<Texture2D> texture = spriteCache->getTextureData(textureName);
        if (texture) {
            glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
            glUniform1i(_unifTexture, 0);
            glUniform4f(_unifColor, 0, 0, 0, 0);
        } else {
            glUniform4f(_unifColor, material->diffuse.x, material->diffuse.y, material->diffuse.z, material->diffuse.w);
        }
        
        glDrawElements(GL_TRIANGLES, material->indicesNum, GL_UNSIGNED_SHORT, _model->_indices + beginIndecesIndex);
        assert(glGetError() == GL_NO_ERROR);
        beginIndecesIndex += material->indicesNum;
    }
    
    
}
