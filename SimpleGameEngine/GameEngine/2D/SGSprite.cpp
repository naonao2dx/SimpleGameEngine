//
//  SGSprite.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/26.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include <assert.h>
#include "SGSprite.hpp"
#include "../Platform/iOS/SGRawImage.hpp"
#include "../Renderer/SGShaderTexture2D.hpp"

using namespace SimpleGameEngine;

std::shared_ptr<Sprite> Sprite::create(std::string& filename, bool useMipmap, GLuint magFilter, GLuint minFilter)
{
    std::shared_ptr<RawImage> rawImage(RawImage::createWithFileName(filename, RawImage::TEXTURE_RAW_RGBA8));
    assert(rawImage != nullptr);

    std::shared_ptr<Sprite> result(new (std::nothrow) Sprite(std::move(rawImage), useMipmap, magFilter, minFilter));
    
    return result;
}

std::shared_ptr<Sprite> Sprite::createWithCustomMipmap(std::vector<std::string> filenames, GLuint magFilter, GLuint minFilter)
{
    std::vector<std::shared_ptr<RawImage>> rawImages;
    for (auto itr = filenames.begin(); itr != filenames.end(); ++itr)
    {
        std::shared_ptr<RawImage> rawImage(RawImage::createWithFileName(*itr, RawImage::TEXTURE_RAW_RGBA8));
        assert(rawImage != nullptr);
        
        rawImages.emplace_back(rawImage);
    }
    
    std::shared_ptr<Sprite> result(new (std::nothrow) Sprite(std::move(rawImages), magFilter, minFilter));
    
    return result;
}

Sprite::Sprite(std::shared_ptr<RawImage> rawImage, bool useMipmap, GLuint magFilter, GLuint minFilter)
: _rawImage(rawImage)
, _useMipmap(useMipmap)
, _magFilter(magFilter)
, _minFilter(minFilter)
{
    initWithTexture();
}

Sprite::Sprite(std::vector<std::shared_ptr<RawImage>> rawImages, GLuint magFilter, GLuint minFilter)
: _rawImages(rawImages)
, _magFilter(magFilter)
, _minFilter(minFilter)
{
    initWithTextureCustomMipmap();
}

bool Sprite::initWithTexture()
{
    init();
    setContentSize(_rawImage->getWidth(), _rawImage->getHeight());
    setShaderTexture();
    
    return true;
};

bool Sprite::initWithTextureCustomMipmap()
{
    init();
    setContentSize(_rawImages.at(0)->getWidth(), _rawImages.at(0)->getHeight());
    setShaderTextureWithCustomMipmap();
    
    return true;
}

bool Sprite::init()
{
    Vertex uv1 = Vertex { Vec2 { 0.0f, 0.0f } };
    Vertex uv2 = Vertex { Vec2 { 0.0f, 1.0f } };
    Vertex uv3 = Vertex { Vec2 { 1.0f, 0.0f } };
    Vertex uv4 = Vertex { Vec2 { 1.0f, 1.0f } };
    std::vector<Vertex> uv = { uv1, uv2, uv3, uv4 };
    setVertexUV(uv);
    
    return true;
}

void Sprite::setVertexUV(const std::vector<Vertex> vertexUV)
{
    _vertexUV = vertexUV;
}

void Sprite::setShaderTexture()
{
    setShaderProgram(ShaderManager::ShaderType::TEXTURE_2D);
    std::dynamic_pointer_cast<ShaderTexture2D>(_shaderProgram)->setFilter(_magFilter, _minFilter);
    _textureID = std::dynamic_pointer_cast<ShaderTexture2D>(_shaderProgram)->setTexture(_rawImage, _useMipmap);
}

void Sprite::setShaderTextureWithCustomMipmap()
{
    setShaderProgram(ShaderManager::ShaderType::TEXTURE_2D);
    std::dynamic_pointer_cast<ShaderTexture2D>(_shaderProgram)->setFilter(_magFilter, _minFilter);
    _textureID = std::dynamic_pointer_cast<ShaderTexture2D>(_shaderProgram)->setTextureWithCustomMimap(_rawImages);
}

void Sprite::draw()
{
    std::dynamic_pointer_cast<ShaderTexture2D>(_shaderProgram)->bindTexture(_textureID);
    _shaderProgram->setVertex(_vertex);
    std::dynamic_pointer_cast<ShaderTexture2D>(_shaderProgram)->setVertexUV(_vertexUV);
    _shaderProgram->draw();
}

