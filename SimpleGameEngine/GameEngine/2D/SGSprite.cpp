//
//  SGSprite.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/26.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include <assert.h>
#include "SGSprite.hpp"
#include "SGShaderTexture2D.hpp"
#include "SGSpriteCache.hpp"

using namespace SimpleGameEngine;

std::shared_ptr<Sprite> Sprite::create(std::string& filename)
{
    std::shared_ptr<SpriteCache> spriteCache = SpriteCache::getInstance();
    std::shared_ptr<Texture2D> texture2d = spriteCache->getTextureData(filename);
    
    std::shared_ptr<Sprite> sprite(new (std::nothrow) Sprite(std::move(texture2d)));
    
    return sprite;
}

std::shared_ptr<Sprite> Sprite::createWithCustomMipmap(std::vector<std::string> filenames)
{
    std::shared_ptr<SpriteCache> spriteCache = SpriteCache::getInstance();
    std::shared_ptr<Texture2D> texture2d = spriteCache->getTextureData(filenames);
    
    std::shared_ptr<Sprite> sprite(new (std::nothrow) Sprite(std::move(texture2d)));
    
    return sprite;
}

std::shared_ptr<Sprite> Sprite::createWithTextureAtlas(std::string &atlasname, std::string &filename)
{
    std::shared_ptr<SpriteCache> spriteCache = SpriteCache::getInstance();
    std::shared_ptr<Texture2D> texture2d = spriteCache->getTextureData(atlasname, filename);
    
    std::shared_ptr<Sprite> sprite(new (std::nothrow) Sprite(std::move(texture2d)));
    
    return sprite;
}

Sprite::Sprite(std::shared_ptr<Texture2D> texture2d)
: _texture2d(texture2d)
{
    setContentSize(_texture2d->getWidth(), _texture2d->getHeight());
    setShaderProgram(ShaderManager::ShaderType::TEXTURE_2D);
}

bool Sprite::init()
{
    return true;
}

void Sprite::draw()
{
    std::dynamic_pointer_cast<ShaderTexture2D>(_shaderProgram)->bindTexture(_texture2d->getTextureID());
    _shaderProgram->setVertex(_vertex);
    std::dynamic_pointer_cast<ShaderTexture2D>(_shaderProgram)->setVertexUV(_texture2d->getVertexUV());
    _shaderProgram->draw();
}

