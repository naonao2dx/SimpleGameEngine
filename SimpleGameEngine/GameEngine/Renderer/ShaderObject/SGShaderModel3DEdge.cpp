//
//  SGShaderModel3DEdge.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/07/23.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGShaderModel3DEdge.hpp"

using namespace SimpleGameEngine;

ShaderModel3DEdge::ShaderModel3DEdge(const GLchar* vertShaderSource, const GLchar* fragShaderSource)
{
    createShader(vertShaderSource, fragShaderSource);
    init();
}

bool ShaderModel3DEdge::init()
{
    return true;
}

void ShaderModel3DEdge::draw()
{
    ShaderBase3D::draw();
}
