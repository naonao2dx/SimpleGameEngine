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
    init();
}

ShaderTexture2D::~ShaderTexture2D()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(static_cast<GLsizei>(_textureID.size()), &(*_textureID.begin()));
    assert(glGetError == GL_NO_ERROR);
}

bool ShaderTexture2D::init()
{
    _attrPos = glGetAttribLocation(_shader, "attr_pos");
    _attrUV = glGetAttribLocation(_shader, "attr_uv");
    _unifTexture = glGetUniformLocation(_shader, "texture");
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

GLuint ShaderTexture2D::createTexture()
{
    GLuint textureID;
    
    glGenTextures(1, &textureID);
    assert(textureID != 0);
    assert(glGetError() == GL_NO_ERROR);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    assert(glGetError() == GL_NO_ERROR);
    
    glBindTexture(GL_TEXTURE_2D, textureID);
    assert(glGetError() == GL_NO_ERROR);
    
    _textureID.push_back(textureID);
    
    return textureID;
}

GLuint ShaderTexture2D::setTextureFilename(std::string& filename, bool useGenerateMipmap) {
    GLuint textureID = createTexture();
    
    std::shared_ptr<RawImage> image = RawImage::createWithFileName(filename, RawImage::TEXTURE_RAW_RGBA8);
    assert(image != nullptr);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image->getPixelData());
    assert(glGetError() == GL_NO_ERROR);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _magFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _minFilter);
    assert(glGetError() == GL_NO_ERROR);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    assert(glGetError() == GL_NO_ERROR);
    
    if (useGenerateMipmap)
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    
    return textureID;
}

GLuint ShaderTexture2D::setTextureFilenameWithCustomMimap(std::vector<std::string> filename)
{
    GLuint textureID = createTexture();
    
    int mipmapLevel = 0;
    
    for (auto itr = filename.begin(); itr != filename.end(); ++itr)
    {
        std::shared_ptr<RawImage> image = nullptr;
        image = RawImage::createWithFileName(*itr, RawImage::TEXTURE_RAW_RGBA8);
        
        glTexImage2D(GL_TEXTURE_2D, mipmapLevel, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image->getPixelData());
        assert(glGetError() == GL_NO_ERROR);
        
         ++mipmapLevel;
    }
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _magFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _minFilter);
    assert(glGetError() == GL_NO_ERROR);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    assert(glGetError() == GL_NO_ERROR);
    
    return textureID;
}

void ShaderTexture2D::bindTexture(GLuint textureID)
{
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
