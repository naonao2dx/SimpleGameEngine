//
//  SGSpriteMask.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/01.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include <assert.h>
#include "SGSpriteMask.hpp"
#include "SGShaderMaskTexture.hpp"
#include "SGRawImage.hpp"
#include "SGSpriteCache.hpp"

using namespace SimpleGameEngine;

std::shared_ptr<SpriteMask> SpriteMask::create(std::string& textureFilename, std::string& maskTextureFilename)
{
    std::shared_ptr<SpriteCache> spriteCache = SpriteCache::getInstance();
    std::shared_ptr<Texture2D> texture2d = spriteCache->getTextureData(textureFilename);
    std::shared_ptr<Texture2D> maskTexture2d = spriteCache->getTextureData(maskTextureFilename);
 
    std::shared_ptr<SpriteMask> sprite(new (std::nothrow) SpriteMask(std::move(texture2d), std::move(maskTexture2d)));
    
    return sprite;
}

SpriteMask::SpriteMask(std::shared_ptr<Texture2D> texture2d, std::shared_ptr<Texture2D> maskTexture2d)
: _texture2d(texture2d)
, _maskTexture2d(maskTexture2d)
{
    setContentSize(_texture2d->getWidth(), _texture2d->getHeight());
    setShaderProgram(ShaderManager::ShaderType::BLEND_TEXTURE);
}

bool SpriteMask::init()
{
    return true;
}

void SpriteMask::draw()
{
    std::dynamic_pointer_cast<ShaderMaskTexture>(_shaderProgram)->bindTexture(_texture2d->getTextureID(), _maskTexture2d->getTextureID());
    _shaderProgram->setVertex(_vertex);
    std::dynamic_pointer_cast<ShaderMaskTexture>(_shaderProgram)->setVertexUV(_texture2d->getVertexUV());
    _shaderProgram->draw();
}
