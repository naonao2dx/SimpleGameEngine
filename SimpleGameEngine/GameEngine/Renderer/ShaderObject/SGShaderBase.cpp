//
//  SGShaderBase.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/18.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include <OpenGLES/ES2/gl.h>
#include "SGShaderBase.hpp"
#include "SGConsole.hpp"
#include "SGFileUtils.hpp"
#include <assert.h>

using namespace SimpleGameEngine;

ShaderBase::ShaderBase()
: _blendFunc(BlendFunc::DISABLE)
, _alpha(1.0)
{
    
}

ShaderBase::~ShaderBase()
{
    glUseProgram(0);
    Console::logDebug("GLError: %d", glGetError());
    assert(glGetError == GL_NO_ERROR);
    
    glDeleteProgram(_shader);
    assert(glGetError == GL_NO_ERROR);
}

void ShaderBase::use()
{
    // Start using shader
    glUseProgram(_shader);
    assert(glGetError() == GL_NO_ERROR);
}

void ShaderBase::setVertex(const std::vector<Vertex> vertex)
{
    _vertex = vertex;
}

void ShaderBase::setBlendFunc(BlendFunc blendFunc)
{
    _blendFunc = blendFunc;
}

void ShaderBase::vertexToArray(std::vector<Vertex> vertex, SimpleGameEngine::Vertex vertexAarray[])
{
    for (int i = 0; i < vertex.size(); i++) {
        vertexAarray[i] = vertex.at(i);
    }
}

void ShaderBase::vertexToArray2D(std::vector<Vertex> vertex, GLfloat position[], GLubyte color[], GLfloat uv[])
{
    for (int i = 0; i < vertex.size(); i++) {
        position[i * 2] = vertex.at(i).position.x;
        position[i * 2 + 1] = vertex.at(i).position.y;
        
        if (nullptr != color) {
            color[i * 4] = vertex.at(i).color.r;
            color[i * 4 + 1] = vertex.at(i).color.g;
            color[i * 4 + 2] = vertex.at(i).color.b;
            color[i * 4 + 3] = vertex.at(i).color.a;
        }
        
        if (nullptr != uv) {
            uv[i * 2] = vertex.at(i).uv.x;
            uv[i * 2 + 1] = vertex.at(i).uv.y;
        }
    }
}

void ShaderBase::vertexToArray3D(std::vector<Vertex> vertex, GLfloat position[], GLubyte color[], GLfloat uv[])
{
    for (int i = 0; i < vertex.size(); i++) {
        position[i * 3] = vertex.at(i).position.x;
        position[i * 3 + 1] = vertex.at(i).position.y;
        position[i * 3 + 2] = vertex.at(i).position.z;
        
        if (nullptr != color) {
            color[i * 4] = vertex.at(i).color.r;
            color[i * 4 + 1] = vertex.at(i).color.g;
            color[i * 4 + 2] = vertex.at(i).color.b;
            color[i * 4 + 3] = vertex.at(i).color.a;
        }
        
        if (nullptr != uv) {
            uv[i * 2] = vertex.at(i).uv.x;
            uv[i * 2 + 1] = vertex.at(i).uv.y;
        }
    }
}

void ShaderBase::vertexToPosition(std::vector<Vertex> vertex, GLfloat position[]) {
    for (int i = 0; i < vertex.size(); i++) {
        position[i * 2] = vertex.at(i).position.x;
        position[i * 2 + 1] = vertex.at(i).position.y;
    }
}

void ShaderBase::vertexToPosition3D(std::vector<Vertex> vertex, GLfloat *position) {
    for (int i = 0; i < vertex.size(); i++) {
        position[i * 3] = vertex.at(i).position.x;
        position[i * 3 + 1] = vertex.at(i).position.y;
        position[i * 3 + 2] = vertex.at(i).position.z;
    }
}

void ShaderBase::vertexToPositionAndColor(std::vector<Vertex> vertex, GLfloat *position, GLubyte *color)
{
    for (int i = 0; i < vertex.size(); i++) {
        position[i * 2] = vertex.at(i).position.x;
        position[i * 2 + 1] = vertex.at(i).position.y;
        color[i * 4] = vertex.at(i).color.r;
        color[i * 4 + 1] = vertex.at(i).color.g;
        color[i * 4 + 2] = vertex.at(i).color.b;
        color[i * 4 + 3] = vertex.at(i).color.a;
    }
}

void ShaderBase::vertexToPositionAndColor3D(std::vector<Vertex> vertex, GLfloat *position, GLubyte *color)
{
    for (int i = 0; i < vertex.size(); i++) {
        position[i * 3] = vertex.at(i).position.x;
        position[i * 3 + 1] = vertex.at(i).position.y;
        position[i * 3 + 2] = vertex.at(i).position.z;
        color[i * 4] = vertex.at(i).color.r;
        color[i * 4 + 1] = vertex.at(i).color.g;
        color[i * 4 + 2] = vertex.at(i).color.b;
        color[i * 4 + 3] = vertex.at(i).color.a;
    }
}

void ShaderBase::setShape(GLenum shape)
{
    _shape = shape;
}

void ShaderBase::createShader(const GLchar* vertShaderSource, const GLchar* fragShaderSource)
{
    // Create vertex shader object
    GLuint vertShader = compileShader(GL_VERTEX_SHADER, vertShaderSource);
    
    // Create fragment shader object
    GLuint fragShader = compileShader(GL_FRAGMENT_SHADER, fragShaderSource);
    
    // Create program object
    _shader = glCreateProgram();
    
    // Link vertex shader and program object
    glAttachShader(_shader, vertShader);
    assert(glGetError() == GL_NO_ERROR);
    
    // Link fragment shader and program object
    glAttachShader(_shader, fragShader);
    assert(glGetError() == GL_NO_ERROR);
    
    // Link
    glLinkProgram(_shader);
    
    // Check link error
    {
        GLint linkSuccess = 0;
        glGetProgramiv(_shader, GL_LINK_STATUS, &linkSuccess);
        
        if (linkSuccess == GL_FALSE) {
            // Check status
            GLint infoLen = 0;
            // Get error message
            glGetProgramiv(_shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen > 1) {
                GLchar *message = (GLchar*) calloc(infoLen, sizeof(GLchar));
                glGetProgramInfoLog(_shader, infoLen, nullptr, message);
                Console::logDebug(message);
                free((void*) message);
            }
        }
        
        // Check no error
        assert(linkSuccess == GL_TRUE);
    }
    
    // Release shader object
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
}

GLuint ShaderBase::compileShader(GLuint shaderType, const GLchar *source)
{
    // Create shader object
    GLuint shader = glCreateShader(shaderType);
    assert(shader != 0);
    assert(glGetError() == GL_NO_ERROR);
    
    // Link shader object and source code
    glShaderSource(shader, 1, &source, nullptr);
    // Compile GLSL
    glCompileShader(shader);
    
    // Check compile error
    {
        GLint compileSuccess = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compileSuccess);
        if (compileSuccess == GL_FALSE) {
            // Error occured
            GLint infoLen = 0;
            // Get error message
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen > 1) {
                GLchar *message = (GLchar*) calloc(infoLen, sizeof(GLchar));
                glGetShaderInfoLog(shader, infoLen, nullptr, message);
                Console::logDebug(message);
                free((void*) message);
            } else {
                Console::logDebug("comple error not info...");
            }
        }
        assert(compileSuccess == GL_TRUE);
    }
    
    return shader;
}

void ShaderBase::draw()
{
    use();
    
    // Alpha blending
    if (_blendFunc != BlendFunc::DISABLE) {
        glEnable(GL_BLEND);
        glBlendFunc(_blendFunc.src, _blendFunc.dst);
    } else {
        glDisable(GL_BLEND);
        glBlendFunc(_blendFunc.src, _blendFunc.dst);
    }
}
