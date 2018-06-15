//
//  SGShaderManager.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/18.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGShaderManager.hpp"
#include "SGShaderBase.hpp"
#include "SGShaderPositionAndColor.hpp"
#include "SGShaderPositionAndColor3D.hpp"
#include "SGShaderVertexColor.hpp"
#include "SGShaderTexture2D.hpp"
#include "SGShaderMaskTexture.hpp"
#include "SGShaderTexture2DMatrix.hpp"
#include "SGShaderTexture3D.hpp"
#include "SGShaderModel3D.hpp"

#include "ShaderSource/Vertex/ShaderPosition.vert"
#include "ShaderSource/Vertex/ShaderPositionCamera.vert"
#include "ShaderSource/Fragment/ShaderColor.frag"

#include "ShaderSource/Vertex/ShaderVertexColor.vert"
#include "ShaderSource/Fragment/ShaderVertexColor.frag"

#include "ShaderSource/Vertex/ShaderTexture2D.vert"
#include "ShaderSource/Fragment/ShaderTexture2D.frag"

#include "ShaderSource/Vertex/ShaderMaskTexture.vert"
#include "ShaderSource/Fragment/ShaderMaskTexture.frag"

#include "ShaderSource/Vertex/ShaderTexture2DMatrix.vert"
#include "ShaderSource/Fragment/ShaderTexture2DMatrix.frag"

#include "ShaderSource/Vertex/ShaderTexture3D.vert"

#include "ShaderSource/Fragment/ShaderModel3D.frag"

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
    
    auto shaderPositionAndColor3D = std::make_shared<ShaderPositionAndColor3D>(shaderVertPositionCamera, shaderFragColor);
    _shaderMap.emplace(POSITION_AND_COLOR_3D, shaderPositionAndColor3D);
    
    auto shaderVertexColor = std::make_shared<ShaderVertexColor>(shaderVertVertexColor, shaderFragVertexColor);
    _shaderMap.emplace(VERTEX_COLOR, shaderVertexColor);
    
    auto shaderTexture2D = std::make_shared<ShaderTexture2D>(shaderVertTexture2D, shaderFragTexture2D);
    _shaderMap.emplace(TEXTURE_2D, shaderTexture2D);
    
    auto shaderBlendTexture = std::make_shared<ShaderMaskTexture>(shaderVertMaskTexture, shaderFragMaskTexture);
    _shaderMap.emplace(BLEND_TEXTURE, shaderBlendTexture);
    
    auto shaderTexture2DMatrix = std::make_shared<ShaderTexture2DMatrix>(shaderVertTexture2DMatrix, shaderFragTexture2DMatrix);
    _shaderMap.emplace(TEXTURE_2D_MATRIX, shaderTexture2DMatrix);
    
    auto shaderTexture3D = std::make_shared<ShaderTexture3D>(shaderVertTexture3D, shaderFragTexture2D);
    _shaderMap.emplace(TEXTURE_3D, shaderTexture3D);
    
    auto shaderModel3D = std::make_shared<ShaderModel3D>(shaderVertTexture3D, shaderFragModel3D);
    _shaderMap.emplace(MODEL_3D, shaderModel3D);
}

std::shared_ptr<ShaderBase> ShaderManager::getShaderProgram(ShaderType shaderType)
{
    return _shaderMap.at(shaderType);
}
