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

bool ShaderPositionAndColor3D::init()
{
    ShaderPositionAndColor::init();
    _unifLookAt = glGetUniformLocation(_shader, "unif_lookat");
    assert(_unifLookAt >= 0);

    _unifProjection = glGetUniformLocation(_shader, "unif_projection");
    assert(_unifProjection >= 0);
    return true;
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
    glUniformMatrix4fv(_unifLookAt, 1, GL_FALSE, (GLfloat*) _lookAt.m);
    glUniformMatrix4fv(_unifProjection, 1, GL_FALSE, (GLfloat*) _projection.m);
    
    // Draw
    glDrawArrays(_shape, 0, static_cast<GLsizei>(_vertex.size()));
}
