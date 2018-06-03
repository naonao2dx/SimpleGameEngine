//
//  SGShaderTexture3D.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/06/02.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGShaderTexture3D.hpp"

using namespace SimpleGameEngine;

ShaderTexture3D::ShaderTexture3D(const GLchar* vertShaderSource, const GLchar* fragShaderSource)
{
    createShader(vertShaderSource, fragShaderSource);
    init();
}

bool ShaderTexture3D::init()
{
    ShaderTexture2D::init();
    _unifWlp = glGetUniformLocation(_shader, "unif_wlp");
    assert(_unifWlp >= 0);
    return true;
}
