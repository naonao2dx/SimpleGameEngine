//
//  SGShaderTexture2DMatrix.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/10.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGShaderTexture2DMatrix.hpp"
#include <assert.h>
#include "SGConsole.hpp"

using namespace SimpleGameEngine;

ShaderTexture2DMatrix::ShaderTexture2DMatrix(const GLchar* vertShaderSource, const GLchar* fragShaderSource)
{
    createShader(vertShaderSource, fragShaderSource);
    init();
}

bool ShaderTexture2DMatrix::init()
{
    _attrPos = glGetAttribLocation(_shader, "attr_pos");
    assert(_attrPos >= 0);
    
    _attrUV = glGetAttribLocation(_shader, "attr_uv");
    assert(_attrUV >= 0);
    
    _unifTexture = glGetUniformLocation(_shader, "texture");
    assert(_unifTexture >= 0);
    
    _unifMatrix = glGetUniformLocation(_shader, "unif_matrix");
    assert(_unifMatrix >= 0);
    
    return true;
}

void ShaderTexture2DMatrix::setMatrix(SimpleGameEngine::Mat4 &matrix)
{
    _matrix = matrix;
}

void ShaderTexture2DMatrix::draw()
{
    ShaderBase::draw();
    glDisable(GL_DEPTH_TEST);
    
    GLfloat position[_vertex.size() * 2];
    vertexToPosition(_vertex, position);
    
    GLfloat uv[_vertexUV.size() * 2];
    vertexToPosition(_vertexUV, uv);
    
    glEnableVertexAttribArray(_attrPos);
    glEnableVertexAttribArray(_attrUV);
    
    glUniform1i(_unifTexture, 0);
    
    glVertexAttribPointer(_attrPos, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)position);
    glVertexAttribPointer(_attrUV, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)uv);
    

    glUniformMatrix4fv(_unifMatrix, 1, GL_FALSE, (GLfloat*)_matrix.m);
    
    glDisable(GL_DEPTH_TEST);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, static_cast<GLsizei>(_vertex.size()));
}
