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
    
    glLineWidth(_lineWidth);
    
    // Vertex data
    GLfloat position[_position.size() * 2];
    for (int i = 0; i < _position.size(); i++) {
        position[i * 2] = _position.at(i)->x;
        position[i * 2 + 1] = _position.at(i)->y;
    }
    
    glEnableVertexAttribArray(_attrPos);
    glVertexAttribPointer(_attrPos, 2, GL_FLOAT, GL_FALSE, 0., position);
    
    // Fragment data
    glUniform4f(_unifColor, _color.r, _color.g, _color.b, _color.a);
    
    // Draw
    glDrawArrays(_shape, 0, static_cast<GLsizei>(_position.size()));
}
