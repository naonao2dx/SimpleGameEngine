//
//  SGShaderPositionAndColor3D3D.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/22.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include <assert.h>
#include <vector>
#include "SGShaderPositionAndColor3D.hpp"
#include "SGGeometry.hpp"
#include "SGConsole.hpp"

using namespace SimpleGameEngine;

ShaderPositionAndColor3D::ShaderPositionAndColor3D(const GLchar* vertShaderSource, const GLchar* fragShaderSource)
{
    createShader(vertShaderSource, fragShaderSource);
    init();
}

void ShaderPositionAndColor3D::draw()
{
    use();
    
    GLfloat position[_vertex.size() * 3];
    vertexToPosition3D(_vertex, position);
    
    glLineWidth(_lineWidth);
    glEnableVertexAttribArray(_attrPos);
    glVertexAttribPointer(_attrPos, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)position);
    
    // Fragment data
    glUniform4f(_unifColor, _color.r, _color.g, _color.b, _color.a);
    
    // Draw
    glDrawArrays(_shape, 0, static_cast<GLsizei>(_vertex.size()));
}
