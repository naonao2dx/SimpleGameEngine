//
//  SGShaderManager.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/18.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGShaderManager.hpp"
#include "SGShaderProgram.hpp"

#include "Shader/ShaderPosition.vert"
#include "Shader/ShaderColor.frag"

using namespace SimpleGameEngine;

static std::shared_ptr<ShaderManager> pInstance = nullptr;

ShaderManager::ShaderManager()
: _shaderMap()
{
}

std::shared_ptr<ShaderManager> ShaderManager::getInstance()
{
    if (!pInstance) {
        pInstance.reset(new ShaderManager());
        pInstance->init();
    }
    return pInstance;
}

bool ShaderManager::init()
{
    loadDefaultShader();
    return true;
}

void ShaderManager::loadDefaultShader()
{
    auto shader = ShaderProgram::createWithByteArray(shaderVertPosition, shaderFragColor);
    _shaderMap.emplace(POSITION_AND_COLOR, shader);

}

std::shared_ptr<ShaderProgram> ShaderManager::getShaderProgram(ShaderType shaderType)
{
    return _shaderMap.at(shaderType);
}
