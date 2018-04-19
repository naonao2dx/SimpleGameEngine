//
//  SGShaderCache.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/18.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGShaderCache.hpp"
#include "SGShaderProgram.hpp"

using namespace SimpleGameEngine;

static std::shared_ptr<ShaderCache> pInstance = nullptr;

ShaderCache::ShaderCache()
: _shaderMap()
{
}

std::shared_ptr<ShaderCache> ShaderCache::getInstance()
{
    if (!pInstance) {
        pInstance.reset(new ShaderCache());
        pInstance->init();
    }
    return pInstance;
}

bool ShaderCache::init()
{
    auto shader = ShaderProgram::createWithFileNames(std::string("ShaderPosition.vert"), std::string("test"));
    return true;
}
