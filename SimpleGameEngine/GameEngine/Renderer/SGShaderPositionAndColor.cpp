//
//  SGShaderPositionAndColor.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/24.
//  Copyright © 2018年 Nao. All rights reserved.
//
#include <assert.h>
#include <vector>
#include "SGShaderPositionAndColor.hpp"
#include "../Util/SGGeometry.hpp"
#include "../Util/SGConsole.hpp"

using namespace SimpleGameEngine;

ShaderPositionAndColor::ShaderPositionAndColor(const GLchar* vertShaderSource, const GLchar* fragShaderSource)
{
    createShader(vertShaderSource, fragShaderSource);
    init();
}

bool ShaderPositionAndColor::init()
{
    // Get vertex shader pos variable
    _attrPos = glGetAttribLocation(_shader, "attr_pos");
    assert(_attrPos >= 0);
    _unifColor = glGetUniformLocation(_shader, "unif_color");
    assert(_unifColor >= 0);
    return true;
}

void ShaderPositionAndColor::draw()
{
    use();
    
    GLfloat position[_vertex.size() * 2];
    vertexToPosition(position);
    
    glLineWidth(_lineWidth);
    glEnableVertexAttribArray(_attrPos);
    glVertexAttribPointer(_attrPos, 2, GL_FLOAT, GL_FALSE, 0., position);
    
    // Fragment data
    glUniform4f(_unifColor, _color.r, _color.g, _color.b, _color.a);
    
    // Draw
    glDrawArrays(_shape, 0, static_cast<GLsizei>(_vertex.size()));
}