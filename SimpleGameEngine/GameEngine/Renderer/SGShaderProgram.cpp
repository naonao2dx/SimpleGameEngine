//
//  SGShaderProgram.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/18.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include <OpenGLES/ES2/gl.h>
#include "SGShaderProgram.hpp"
#include "../Util/SGConsole.hpp"
#include "../Util/SGFileUtils.hpp"
#include <assert.h>

using namespace SimpleGameEngine;

std::shared_ptr<ShaderProgram> ShaderProgram::createWithByteArray(const GLchar* vertShaderSource, const GLchar*  fragShaderSource)
{
    std::shared_ptr<ShaderProgram> shaderProgram(new ShaderProgram());
    
    // Create vertex shader object
    GLuint vertShader = compileShader(GL_VERTEX_SHADER, vertShaderSource);
    
    // Create fragment shader object
    GLuint fragShader = compileShader(GL_FRAGMENT_SHADER, fragShaderSource);
    
    // Create program object
    shaderProgram->_shader = glCreateProgram();
    
    // Link vertex shader and program object
    glAttachShader(shaderProgram->_shader, vertShader);
    assert(glGetError() == GL_NO_ERROR);
    
    // Link fragment shader and program object
    glAttachShader(shaderProgram->_shader, fragShader);
    assert(glGetError() == GL_NO_ERROR);
    
    // Link
    glLinkProgram(shaderProgram->_shader);
    
    // Check link error
    {
        GLint linkSuccess = 0;
        glGetProgramiv(shaderProgram->_shader, GL_LINK_STATUS, &linkSuccess);
        
        if (linkSuccess == GL_FALSE) {
            // Check status
            GLint infoLen = 0;
            // Get error message
            glGetProgramiv(shaderProgram->_shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen > 1) {
                GLchar *message = (GLchar*) calloc(infoLen, sizeof(GLchar));
                glGetProgramInfoLog(shaderProgram->_shader, infoLen, NULL, message);
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
    
    return shaderProgram;
}


GLuint ShaderProgram::getShader()
{
    return _shader;
}

void ShaderProgram::use()
{
    // Start using shader
    glUseProgram(_shader);
    assert(glGetError() == GL_NO_ERROR);
}

GLuint ShaderProgram::compileShader(GLuint shaderType, const GLchar *source)
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
