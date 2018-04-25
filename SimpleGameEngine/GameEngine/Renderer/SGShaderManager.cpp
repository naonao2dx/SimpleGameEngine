//
//  SGShaderManager.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/18.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGShaderManager.hpp"
#include "SGShaderProgram.hpp"
#include "SGShaderPositionAndColor.hpp"
#include "SGShaderVertexColor.hpp"

#include "Shader/ShaderPosition.vert"
#include "Shader/ShaderColor.frag"

#include "Shader/ShaderVertexColor.vert"
#include "Shader/ShaderVertexColor.frag"

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
    auto shaderPositionAndColor = std::make_shared<ShaderPositionAndColor>(shaderVertPosition, shaderFragColor);
    _shaderMap.emplace(POSITION_AND_COLOR, shaderPositionAndColor);
    
    auto shaderVertexColor = std::make_shared<ShaderVertexColor>(shaderVertVertexColor, shaderFragVertexColor);
    _shaderMap.emplace(VERTEX_COLOR, shaderVertexColor);

}

std::shared_ptr<ShaderProgram> ShaderManager::getShaderProgram(ShaderType shaderType)
{
    return _shaderMap.at(shaderType);
}
