//
//  SGShaderVertexColor.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/25.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGShaderVertexColor.hpp"

using namespace SimpleGameEngine;

ShaderVertexColor::ShaderVertexColor(const GLchar* vertShaderSource, const GLchar* fragShaderSource)
{
    createShader(vertShaderSource, fragShaderSource);
    init();
}

bool ShaderVertexColor::init()
{
    _attrPos = glGetAttribLocation(_shader, "attr_pos");
    _attrColor = glGetAttribLocation(_shader, "attr_color");
    return true;
}

void ShaderVertexColor::draw()
{
    use();
    GLfloat position[_vertex.size() * 2];
    GLubyte color[_vertex.size() * 4];
    vertexToPositionAndColor(_vertex, position, color);
    
    glEnableVertexAttribArray(_attrPos);
    glEnableVertexAttribArray(_attrColor);
    
    glVertexAttribPointer(_attrPos, 2, GL_FLOAT, GL_FALSE, 0, position);
    glVertexAttribPointer(_attrColor, 3, GL_UNSIGNED_BYTE, GL_TRUE, 0, color);
    
    glDrawArrays(_shape, 0, static_cast<GLsizei>(_vertex.size()));
}
