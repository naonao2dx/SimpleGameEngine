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
#include "SGSpriteCache.hpp"

using namespace SimpleGameEngine;

std::shared_ptr<SpriteBlend> SpriteBlend::create(std::string& textureFilename, std::string& blendTextureFilename)
{
    std::shared_ptr<SpriteCache> spriteCache = SpriteCache::getInstance();
    std::shared_ptr<Texture2D> texture2d = spriteCache->getTextureData(textureFilename);
    std::shared_ptr<Texture2D> blendTexture2d = spriteCache->getTextureData(blendTextureFilename);
 
    std::shared_ptr<SpriteBlend> sprite(new (std::nothrow) SpriteBlend(std::move(texture2d), std::move(blendTexture2d)));
    
    return sprite;
}

SpriteBlend::SpriteBlend(std::shared_ptr<Texture2D> texture2d, std::shared_ptr<Texture2D> blendTexture2d)
: _texture2d(texture2d)
, _blendTexture2d(blendTexture2d)
{
    setContentSize(_texture2d->getWidth(), _texture2d->getHeight());
    setShaderProgram(ShaderManager::ShaderType::BLEND_TEXTURE);
}

bool SpriteBlend::init()
{
    return true;
}

void SpriteBlend::draw()
{
    std::dynamic_pointer_cast<ShaderBlendTexture>(_shaderProgram)->bindTexture(_texture2d->getTextureID(), _blendTexture2d->getTextureID());
    _shaderProgram->setVertex(_vertex);
    std::dynamic_pointer_cast<ShaderBlendTexture>(_shaderProgram)->setVertexUV(_texture2d->getVertexUV());
    _shaderProgram->draw();
}
