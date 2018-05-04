//
//  SGSpriteBlend.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/01.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGSpriteBlend.hpp"
#include "SGShaderBlendTexture.hpp"
#include "SGTexture2D.hpp"

using namespace SimpleGameEngine;

std::shared_ptr<SpriteBlend> SpriteBlend::create(std::string& textureFilename, std::string& blendTextureFilename)
{
    std::shared_ptr<Texture2D> texture2d(Texture2D::createWithFileName(textureFilename, Texture2D::TEXTURE_RAW_RGBA8));
    assert(texture2d != nullptr);
    
    std::shared_ptr<Texture2D> blendTexture2d(Texture2D::createWithFileName(blendTextureFilename, Texture2D::TEXTURE_RAW_RGBA8));
    assert(blendTexture2d != nullptr);
    
    std::shared_ptr<SpriteBlend> result(new (std::nothrow) SpriteBlend(std::move(texture2d), std::move(blendTexture2d)));
    
    return result;
}

SpriteBlend::SpriteBlend(std::shared_ptr<Texture2D> texture2d, std::shared_ptr<Texture2D> blendTexture2d)
: _texture2d(texture2d)
, _blendTexture2d(blendTexture2d)
{
    init();
}

bool SpriteBlend::init()
{
    setContentSize(_texture2d->getWidth(), _texture2d->getHeight());
    
    Vertex uv1 = Vertex { Vec2 { 0.0f, 0.0f } };
    Vertex uv2 = Vertex { Vec2 { 0.0f, 1.0f } };
    Vertex uv3 = Vertex { Vec2 { 1.0f, 0.0f } };
    Vertex uv4 = Vertex { Vec2 { 1.0f, 1.0f } };
    std::vector<Vertex> uv = { uv1, uv2, uv3, uv4 };
    setVertexUV(uv);
    
    setShaderSpriteBlend();
    
    return true;
}

void SpriteBlend::setVertexUV(const std::vector<Vertex> vertexUV)
{
    _vertexUV = vertexUV;
}

void SpriteBlend::setShaderSpriteBlend()
{
    setShaderProgram(ShaderManager::ShaderType::BLEND_TEXTURE);
    std::dynamic_pointer_cast<ShaderTexture2D>(_shaderProgram)->setFilter(GL_NEAREST, GL_NEAREST);
    _textureID = std::dynamic_pointer_cast<ShaderBlendTexture>(_shaderProgram)->setTexture(_texture2d, false);
    _blendTextureID = std::dynamic_pointer_cast<ShaderBlendTexture>(_shaderProgram)->setTexture(_blendTexture2d, false);
    std::dynamic_pointer_cast<ShaderBlendTexture>(_shaderProgram)->bindTexture(_textureID, _blendTextureID);
}

void SpriteBlend::draw()
{
    std::dynamic_pointer_cast<ShaderBlendTexture>(_shaderProgram)->bindTexture(_textureID, _blendTextureID);
    _shaderProgram->setVertex(_vertex);
    std::dynamic_pointer_cast<ShaderTexture2D>(_shaderProgram)->setVertexUV(_vertexUV);
    _shaderProgram->draw();
}
