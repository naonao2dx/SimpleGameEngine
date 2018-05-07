//
//  SGShaderTexture2D.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/25.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGShaderTexture2D.hpp"
#include "../Platform/iOS/SGRawImage.hpp"
#include <assert.h>

using namespace SimpleGameEngine;

ShaderTexture2D::ShaderTexture2D(const GLchar* vertShaderSource, const GLchar* fragShaderSource)
: _magFilter(GL_NEAREST)
, _minFilter(GL_NEAREST)
{
    createShader(vertShaderSource, fragShaderSource);
    init();
}

ShaderTexture2D::~ShaderTexture2D()
{
}

bool ShaderTexture2D::init()
{
    _attrPos = glGetAttribLocation(_shader, "attr_pos");
    assert(_attrPos >= 0);
    
    _attrUV = glGetAttribLocation(_shader, "attr_uv");
    assert(_attrUV >= 0);
    
    _unifTexture = glGetUniformLocation(_shader, "texture");
    assert(_unifTexture >= 0);
    
    return true;
}

void ShaderTexture2D::setVertexUV(const std::vector<Vertex> vertexUV)
{
    _vertexUV = vertexUV;
}

void ShaderTexture2D::setFilter(GLuint magFilter, GLuint minFilter)
{
    _magFilter = magFilter;
    _minFilter = minFilter;
}

void ShaderTexture2D::bindTexture(GLuint textureID)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void ShaderTexture2D::draw()
{
    use();
    
    GLfloat position[_vertex.size() * 2];
    vertexToPosition(_vertex, position);
    
    GLfloat uv[_vertexUV.size() * 2];
    vertexToPosition(_vertexUV, uv);
    
    glEnableVertexAttribArray(_attrPos);
    glEnableVertexAttribArray(_attrUV);
    
    glUniform1i(_unifTexture, 0);
    
    glVertexAttribPointer(_attrPos, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)position);
    glVertexAttribPointer(_attrUV, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)uv);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, static_cast<GLsizei>(_vertex.size()));
}
