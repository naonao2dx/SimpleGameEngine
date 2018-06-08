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
    ShaderProgram::draw();
    glEnable(GL_DEPTH_TEST);
    
//    GLfloat position[_vertex.size() * 3];
//    GLfloat uv[_vertex.size() * 2];
//    vertexToArray3D(_vertex, position, nullptr, uv);
    Vertex vertex[_vertex.size()];
    vertexToArray(_vertex, vertex);
    
    const GLushort vertexIndex[] = {
        2, 0, 3,
        3, 0, 1,
        
        4, 2, 5,
        5, 2, 3,
        
        6, 4, 7,
        7, 4, 5,
        
        0, 6, 1,
        1, 6, 7,
        
        9, 8, 4,
        4, 8, 2,
        
        5, 3, 11,
        11, 3, 10
    };
    
    
    glEnableVertexAttribArray(_attrPos);
    glEnableVertexAttribArray(_attrUV);
    
    glUniform1i(_unifTexture, 0);
    
    glVertexAttribPointer(_attrPos, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)vertex);
    glVertexAttribPointer(_attrUV, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)((GLubyte*) vertex + sizeof(Vec3) + sizeof(Color4B)));
    
    glUniformMatrix4fv(_unifWlp, 1, GL_FALSE, (GLfloat*) _wlp.m);
    
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, vertexIndex);
}
