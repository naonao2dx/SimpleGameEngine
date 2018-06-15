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

void ShaderTexture3D::draw()
{
    ShaderBase::draw();
    glEnable(GL_DEPTH_TEST);
    
//    GLfloat position[_vertex.size() * 3];
//    GLfloat uv[_vertex.size() * 2];
//    vertexToArray3D(_vertex, position, nullptr, uv);
    Vertex vertices[_vertex.size()];
    vertexToArray(_vertex, vertices);
    
    const GLushort indices[] = {
        0, 1, 2, 3,
        3, 2,
        2, 3, 4, 5,
        5, 8,
        8, 2, 9, 4,
        4, 3,
        3, 10, 5, 11,
        11, 4,
        4, 5, 6, 7,
        7, 6,
        6, 7, 0, 1
    };
    
    
    glEnableVertexAttribArray(_attrPos);
    glEnableVertexAttribArray(_attrUV);
    
    glUniform1i(_unifTexture, 0);
    
    glVertexAttribPointer(_attrPos, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)vertices);
    glVertexAttribPointer(_attrUV, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)((GLubyte*) vertices + sizeof(Vec3) + sizeof(Color4B)));
    
    glUniformMatrix4fv(_unifWlp, 1, GL_FALSE, (GLfloat*) _wlp.m);
    
    glDrawElements(GL_TRIANGLE_STRIP, 4 * 6 + 2 * 5, GL_UNSIGNED_SHORT, indices);
}
