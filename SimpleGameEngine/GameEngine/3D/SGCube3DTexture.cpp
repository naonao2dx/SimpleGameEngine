//
//  SGCube3DTexture.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/06/07.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGCube3DTexture.hpp"
#include "SGSpriteCache.hpp"
#include "SGShaderManager.hpp"
#include "SGShaderTexture3D.hpp"
#include "SGConsole.hpp"

using namespace SimpleGameEngine;

std::shared_ptr<Cube3DTexture> Cube3DTexture::create(std::string &filename)
{
    std::shared_ptr<SpriteCache> spriteCache = SpriteCache::getInstance();
    std::shared_ptr<Texture2D> texture2d = spriteCache->getTextureData(filename);
    
    std::shared_ptr<Cube3DTexture> obj(new (std::nothrow) Cube3DTexture(std::move(texture2d)));
    obj->setShaderProgram(ShaderManager::ShaderType::TEXTURE_3D);
    return obj;
}


Cube3DTexture::Cube3DTexture(std::shared_ptr<Texture2D> texture2d)
{
    _texture2d = texture2d;
    _vertex.reserve(36);
    setVertex();
}
void Cube3DTexture::draw()
{
    std::dynamic_pointer_cast<ShaderTexture3D>(_shaderProgram)->bindTexture(_texture2d->getTextureID());
    _shaderProgram->setVertex(_vertex);
    std::dynamic_pointer_cast<ShaderTexture3D>(_shaderProgram)->setWlp(_camera->getWlp());
    _shaderProgram->draw();
    
}

void Cube3DTexture::setVertex()
{
    _vertex.clear();
    const GLfloat LEFT = static_cast<GLfloat>(_position.x) - static_cast<GLfloat>(_width)/2.0f;
    Console::logDebug("LEFT: %f", LEFT);
    const GLfloat RIGHT = static_cast<GLfloat>(_position.x) + static_cast<GLfloat>(_width)/2.0f;
    const GLfloat FRONT = static_cast<GLfloat>(_position.z) - static_cast<GLfloat>(_depth)/2.0f;
    const GLfloat BACK = static_cast<GLfloat>(_position.z) + static_cast<GLfloat>(_depth)/2.0f;
    const GLfloat TOP = static_cast<GLfloat>(_position.y) + static_cast<GLfloat>(_height)/2.0f;
    const GLfloat BOTTOM = static_cast<GLfloat>(_position.y) - static_cast<GLfloat>(_height)/2.0f;
    
    const GLfloat UV_LEFT = 0.0f;
    const GLfloat UV_RIGHT = 1.0f;
    const GLfloat UV_TOP = 0.0f;
    const GLfloat UV_BOTTOM = 1.0f;
    
    _vertex.emplace_back( Vertex ( {LEFT, TOP, BACK}, {UV_LEFT, UV_BOTTOM} ) );
    _vertex.emplace_back( Vertex ( {RIGHT,TOP, BACK}, {UV_RIGHT, UV_BOTTOM} ) );
    _vertex.emplace_back( Vertex ( {LEFT, TOP, FRONT}, {UV_LEFT, UV_TOP} ) );
    _vertex.emplace_back( Vertex ( {RIGHT, TOP, FRONT}, {UV_RIGHT, UV_TOP} ) );
    _vertex.emplace_back( Vertex ( {LEFT, BOTTOM, FRONT}, {UV_LEFT, UV_BOTTOM} ) );
    _vertex.emplace_back( Vertex ( {RIGHT, BOTTOM, FRONT}, {UV_RIGHT, UV_BOTTOM} ) );
    _vertex.emplace_back( Vertex ( {LEFT, BOTTOM, BACK}, {UV_LEFT, UV_TOP} ) );
    _vertex.emplace_back( Vertex ( {RIGHT, BOTTOM, BACK}, {UV_RIGHT, UV_TOP} ) );
    _vertex.emplace_back( Vertex ( {LEFT, TOP, BACK}, {UV_RIGHT, UV_TOP} ) );
    _vertex.emplace_back( Vertex ( {LEFT, BOTTOM, BACK}, {UV_RIGHT, UV_BOTTOM} ) );
    _vertex.emplace_back( Vertex ( {RIGHT,TOP, BACK}, {UV_LEFT, UV_TOP} ) );
    _vertex.emplace_back( Vertex ( {RIGHT, BOTTOM, BACK}, {UV_LEFT, UV_BOTTOM} ) );
}
