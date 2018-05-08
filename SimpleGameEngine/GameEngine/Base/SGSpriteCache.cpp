//
//  SGSpriteCache.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/07.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGSpriteCache.hpp"

using namespace SimpleGameEngine;

static std::shared_ptr<SpriteCache> pInstance;

std::shared_ptr<SpriteCache> SpriteCache::getInstance()
{
    if (!pInstance) {
        pInstance.reset(new (std::nothrow) SpriteCache());
        pInstance->init();
    }
    return pInstance;
}

SpriteCache::SpriteCache()
{
    
}

bool SpriteCache::init()
{
    return true;
}

std::shared_ptr<Texture2D> SpriteCache::getTextureData(std::string &filename)
{
    if (_spriteCache.count(filename) != 0) {
        return _spriteCache.at(filename);
    }
    
    std::shared_ptr<Texture2D> texture2d = Texture2D::create(filename);
    _spriteCache.emplace(filename, texture2d);
    
    return texture2d;
}

std::shared_ptr<Texture2D> SpriteCache::getTextureData(std::vector<std::string> filenames)
{
    if (_spriteCache.count(filenames.at(0)) != 0) {
        return _spriteCache.at(filenames.at(0));
    }
    
    std::shared_ptr<Texture2D> texture2d = Texture2D::createWithCustomMipmap(filenames);
    _spriteCache.emplace(filenames.at(0), texture2d);
    
    return texture2d;
}

std::shared_ptr<Texture2D> SpriteCache::getTextureData(std::string &atlasName, std::string &filename)
{
    if (_spriteCache.count(atlasName) != 0) {
        return _spriteCache.at(atlasName + "/" + filename);
    }
    
    std::vector<std::shared_ptr<Texture2D>> texture2ds = Texture2D::createWithTextureAtlas(atlasName);
    
    std::string combineName;
    
    for (auto itr = texture2ds.begin(); itr != texture2ds.end(); ++itr) {
        combineName = atlasName + "/" + (*itr)->getTextureName();
        _spriteCache.emplace(combineName, (*itr));
    }
    
    return _spriteCache.at(atlasName + "/" + filename);
}

void SpriteCache::clearCache()
{
    int i = 0;
    GLuint deleteTextures[_spriteCache.size()];
    for (auto itr = _spriteCache.cbegin(); itr != _spriteCache.cend(); ++itr) {
        deleteTextures[i] = itr->second->getTextureID();
        i++;
    }
    glDeleteTextures(static_cast<GLsizei>(_spriteCache.size()), deleteTextures);
    _spriteCache.clear();
}
