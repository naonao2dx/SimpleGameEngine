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

static std::shared_ptr<SGShaderCache> pInstance = nullptr;

SGShaderCache::SGShaderCache()
: _shaderMap()
{
}

std::shared_ptr<SGShaderCache> SGShaderCache::getInstance()
{
    if (!pInstance) {
        pInstance.reset(new SGShaderCache());
        pInstance->init();
    }
    return pInstance;
}

bool SGShaderCache::init()
{
    auto shader = SGShaderProgram::createWithFileNames(std::string("ShaderPosition.vert"), std::string("test"));
    return true;
}
