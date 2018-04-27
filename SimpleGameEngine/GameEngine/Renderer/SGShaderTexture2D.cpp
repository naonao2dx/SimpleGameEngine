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
{
    createShader(vertShaderSource, fragShaderSource);
    createTexture();
    init();
}

ShaderTexture2D::~ShaderTexture2D()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &_textureID);
    assert(glGetError == GL_NO_ERROR);
}

bool ShaderTexture2D::init()
{
    _attrPos = glGetAttribLocation(_shader, "attr_pos");
    _attrUV = glGetAttribLocation(_shader, "attr_uv");
    _unifTexture = glGetUniformLocation(_shader, "texture");
    return true;
}

void ShaderTexture2D::createTexture()
{
    glGenTextures(1, &_textureID);
    assert(_textureID != 0);
    assert(glGetError() == GL_NO_ERROR);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    assert(glGetError() == GL_NO_ERROR);
    
    glBindTexture(GL_TEXTURE_2D, _textureID);
    assert(glGetError() == GL_NO_ERROR);
}

void ShaderTexture2D::setTextureFilename(std::string& filename) {
    std::shared_ptr<RawImage> image = RawImage::createWithFileName(filename, RawImage::TEXTURE_RAW_RGBA8);
    assert(image != nullptr);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image->getPixelData());
    assert(glGetError() == GL_NO_ERROR);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    assert(glGetError() == GL_NO_ERROR);
}

void ShaderTexture2D::draw()
{
    use();
    
    GLfloat position[_vertex.size() * 2];
    vertexToPosition(position);
    
    const GLfloat uv[] = {
        0, 0,
        0, 1,
        1, 0,
        1, 1,
    };
    
    glEnableVertexAttribArray(_attrPos);
    glEnableVertexAttribArray(_attrUV);
    
    glUniform1i(_unifTexture, 0);
    
    glVertexAttribPointer(_attrPos, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)position);
    glVertexAttribPointer(_attrUV, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)uv);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, static_cast<GLsizei>(_vertex.size()));
}
