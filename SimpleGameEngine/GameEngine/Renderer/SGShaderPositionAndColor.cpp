//
//  SGShaderPositionAndColor.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/24.
//  Copyright © 2018年 Nao. All rights reserved.
//
#include <assert.h>
#include "SGShaderPositionAndColor.hpp"
#include "../Util/SGConsole.hpp"

using namespace SimpleGameEngine;

ShaderPositionAndColor::ShaderPositionAndColor(const GLchar* vertShaderSource, const GLchar* fragShaderSource)
{
    createShader(vertShaderSource, fragShaderSource);
}
