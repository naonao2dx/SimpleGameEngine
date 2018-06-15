//
//  SGShaderModel3D.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/06/15.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGShaderModel3D.hpp"

using namespace SimpleGameEngine;

ShaderModel3D::ShaderModel3D(const GLchar* vertShaderSource, const GLchar* fragShaderSource)
{
    createShader(vertShaderSource, fragShaderSource);
    init();
}

bool ShaderModel3D::init()
{
    _attrPos = glGetAttribLocation(_shader, "attr_pos");
    assert(_attrPos >= 0);
    
    _attrUV = glGetAttribLocation(_shader, "attr_uv");
    assert(_attrUV >= 0);
    
    _unifColor = glGetUniformLocation(_shader, "unif_color");
    assert(_unifTexture >= 0);
    
    _unifTexture = glGetUniformLocation(_shader, "unif_texture");
    assert(_unifTexture >= 0);
    
    _unifWlp = glGetUniformLocation(_shader, "unif_wlp");
    assert(_unifWlp >= 0);
    
    return true;
}

void ShaderModel3D::draw()
{
    ShaderBase3D::draw();
}
