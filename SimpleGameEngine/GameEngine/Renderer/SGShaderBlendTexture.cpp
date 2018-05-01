//
//  SGShaderBlendTexture.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/01.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include <assert.h>
#include "SGShaderBlendTexture.hpp"

using namespace SimpleGameEngine;

ShaderBlendTexture::ShaderBlendTexture(const GLchar* vertShaderSource, const GLchar* fragShaderSource)
{
    createShader(vertShaderSource, fragShaderSource);
    init();
}

bool ShaderBlendTexture::init()
{
    _attrPos = glGetAttribLocation(_shader, "attr_pos");
    assert(_attrPos >= 0);
    
    _attrUV = glGetAttribLocation(_shader, "attr_uv");
    assert(_attrUV >= 0);
    
    _unifTexColor = glGetUniformLocation(_shader, "tex_color");
    assert(_unifTexColor >= 0);
    
    _unifTexMask = glGetUniformLocation(_shader, "tex_mask");
    assert(_unifTexMask >= 0);
    
    return true;
}

void ShaderBlendTexture::bindTexture(GLuint textureID, GLuint blendTextureID)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, blendTextureID);
}

void ShaderBlendTexture::draw()
{
    use();
    
    GLfloat position[_vertex.size() * 2];
    vertexToPosition(_vertex, position);
    
    GLfloat uv[_vertexUV.size() * 2];
    vertexToPosition(_vertexUV, uv);
    
    glEnableVertexAttribArray(_attrPos);
    glEnableVertexAttribArray(_attrUV);
    
    glVertexAttribPointer(_attrPos, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)position);
    glVertexAttribPointer(_attrUV, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)uv);
    
    glUniform1i(_unifTexColor, 0);
    glUniform1i(_unifTexMask, 1);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, static_cast<GLsizei>(_vertex.size()));
}

