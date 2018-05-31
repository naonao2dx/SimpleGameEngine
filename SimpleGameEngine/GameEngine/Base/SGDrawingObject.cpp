//
//  SGDrawingObject.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/31.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGDrawingObject.hpp"

using namespace SimpleGameEngine;

DrawingObject::DrawingObject()
{
    _shaderManager = ShaderManager::getInstance();
}

void DrawingObject::setShaderProgram(ShaderManager::ShaderType shaderType) {
    _shaderType = shaderType;
    _shaderProgram = _shaderManager->getShaderProgram(shaderType);
}
