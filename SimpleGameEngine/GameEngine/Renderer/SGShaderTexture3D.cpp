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
    
    GLfloat position[_vertex.size() * 3];
    GLfloat uv[_vertex.size() * 2];
    vertexToArray3D(_vertex, position, nullptr, uv);
    
    glEnableVertexAttribArray(_attrPos);
    glEnableVertexAttribArray(_attrUV);
    
    glUniform1i(_unifTexture, 0);
    
    glVertexAttribPointer(_attrPos, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)position);
    glVertexAttribPointer(_attrUV, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)uv);
    
    glUniformMatrix4fv(_unifWlp, 1, GL_FALSE, (GLfloat*) _wlp.m);
    
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(_vertex.size()));
}
