//
//  SGSpriteBlend.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/01.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include <assert.h>
#include "SGSpriteBlend.hpp"
#include "SGShaderBlendTexture.hpp"
#include "SGRawImage.hpp"

using namespace SimpleGameEngine;

std::shared_ptr<SpriteBlend> SpriteBlend::create(std::string& textureFilename, std::string& blendTextureFilename)
{
    std::shared_ptr<RawImage> rawImage(RawImage::createWithFileName(textureFilename, RawImage::TEXTURE_RAW_RGBA8));
    assert(rawImage != nullptr);
    
    std::shared_ptr<RawImage> blendRawImage(RawImage::createWithFileName(blendTextureFilename, RawImage::TEXTURE_RAW_RGBA8));
    assert(blendRawImage != nullptr);
    
    std::shared_ptr<SpriteBlend> result(new (std::nothrow) SpriteBlend(std::move(rawImage), std::move(blendRawImage)));
    
    return result;
}

SpriteBlend::SpriteBlend(std::shared_ptr<RawImage> rawImage, std::shared_ptr<RawImage> blendRawImage)
: _rawImage(rawImage)
, _blendRawImage(blendRawImage)
{
    init();
}

bool SpriteBlend::init()
{
    setContentSize(_rawImage->getWidth(), _rawImage->getHeight());
    
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
    _textureID = std::dynamic_pointer_cast<ShaderBlendTexture>(_shaderProgram)->setTexture(_blendRawImage, false);
    _blendTextureID = std::dynamic_pointer_cast<ShaderBlendTexture>(_shaderProgram)->setTexture(_blendRawImage, false);
    std::dynamic_pointer_cast<ShaderBlendTexture>(_shaderProgram)->bindTexture(_textureID, _blendTextureID);
}

void SpriteBlend::draw()
{
    std::dynamic_pointer_cast<ShaderBlendTexture>(_shaderProgram)->bindTexture(_textureID, _blendTextureID);
    _shaderProgram->setVertex(_vertex);
    std::dynamic_pointer_cast<ShaderTexture2D>(_shaderProgram)->setVertexUV(_vertexUV);
    _shaderProgram->draw();
}
