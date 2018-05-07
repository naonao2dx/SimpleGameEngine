//
//  Texture2D.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/07.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "Texture2D.hpp"
#include <assert.h>
#include <string>
#include "SGRawImage.hpp"

using namespace SimpleGameEngine;

std::shared_ptr<Texture2D> Texture2D::create(std::string& filename)
{
    std::shared_ptr<Texture2D> texture2d(new (std::nothrow) Texture2D());
    
    std::shared_ptr<RawImage> rawImage = RawImage::createWithFileName(filename, RawImage::TEXTURE_RAW_RGBA8);
    assert(rawImage != nullptr);
    
    texture2d->setupTexture(rawImage);
    texture2d->_width = rawImage->getWidth();
    texture2d->_height = rawImage->getHeight();
    
    return texture2d;
}

std::shared_ptr<Texture2D> Texture2D::createWithCustomMipmap(std::vector<std::string> filenames)
{
    std::shared_ptr<Texture2D> texture2d(new (std::nothrow) Texture2D());
    std::vector<std::shared_ptr<RawImage>> rawImages;
    
    for (auto itr = filenames.begin(); itr != filenames.end(); ++itr) {
        rawImages.emplace_back(RawImage::createWithFileName(*itr, RawImage::TEXTURE_RAW_RGBA8));
    }
    
    texture2d->setupTextureWithCustomMipmap(rawImages);
    texture2d->_width = rawImages.at(0)->getWidth();
    texture2d->_height = rawImages.at(0)->getHeight();
    
    return texture2d;
}

Texture2D::Texture2D()
: _textureID(0)
, _rawImage(nullptr)
, _useGenerateMipmap(true)
, _magFilter(GL_NEAREST)
, _minFilter(GL_NEAREST_MIPMAP_NEAREST)
{
    Vertex uv1 = Vertex { Vec2 { 0.0f, 0.0f } };
    Vertex uv2 = Vertex { Vec2 { 0.0f, 1.0f } };
    Vertex uv3 = Vertex { Vec2 { 1.0f, 0.0f } };
    Vertex uv4 = Vertex { Vec2 { 1.0f, 1.0f } };
    _vertexUV = {uv1, uv2, uv3, uv4};
}

void Texture2D::setupTexture(std::shared_ptr<RawImage> rawImage)
{
    createTexture();
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, rawImage->getWidth(), rawImage->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, rawImage->getPixelData());
    assert(glGetError() == GL_NO_ERROR);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _magFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _minFilter);
    assert(glGetError() == GL_NO_ERROR);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    assert(glGetError() == GL_NO_ERROR);
    
    if (_useGenerateMipmap)
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }
}

void Texture2D::setupTextureWithCustomMipmap(std::vector<std::shared_ptr<RawImage>> rawImages)
{
    createTexture();
    
    int mipmapLevel = 0;
    
    for (auto itr = rawImages.begin(); itr != rawImages.end(); ++itr) {
        glTexImage2D(GL_TEXTURE_2D, mipmapLevel, GL_RGBA, (*itr)->getWidth(), (*itr)->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, (*itr)->getPixelData());
        assert(glGetError() == GL_NO_ERROR);
        
        ++mipmapLevel;
    }
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _magFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _minFilter);
    assert(glGetError() == GL_NO_ERROR);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    assert(glGetError() == GL_NO_ERROR);
}

void Texture2D::createTexture()
{
    glGenTextures(1, &_textureID);
    assert(_textureID != 0);
    assert(glGetError() == GL_NO_ERROR);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    assert(glGetError() == GL_NO_ERROR);
    
    glBindTexture(GL_TEXTURE_2D, _textureID);
    assert(glGetError() == GL_NO_ERROR);
}
