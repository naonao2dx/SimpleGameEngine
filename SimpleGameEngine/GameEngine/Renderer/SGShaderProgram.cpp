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
#include    <assert.h>

using namespace SimpleGameEngine;

std::shared_ptr<ShaderProgram> ShaderProgram::createWithFileNames(const std::string& vertShaderFilename, const std::string& fragShaderFilename)
{
    std::shared_ptr<ShaderProgram> shaderProgram(new ShaderProgram());
    auto fileUtils = FileUtils::getInstance();
    
    std::string vertShaderSource;
    fileUtils->getContents(vertShaderFilename, vertShaderSource);
    //Console::logDebug(vertShaderSource.data());
    
    std::string fragShaderSource;
    fileUtils->getContents(fragShaderFilename, fragShaderSource);
    //Console::logDebug(fragShaderSource.data());
    
    // Create vertex shader object
    GLuint vertShader = compileShader(GL_VERTEX_SHADER, vertShaderSource.c_str());
    
    // Create fragment shader object
    GLuint fragShader = compileShader(GL_FRAGMENT_SHADER, fragShaderSource.c_str());
    
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
            // エラーが発生したため、状態をチェックする
            GLint infoLen = 0;
            // エラーメッセージを取得
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
    std::string headersDef = (shaderType == GL_VERTEX_SHADER ? "precision highp float;\n precision highp int;\n" : "precision mediump float;\n precision mediump int;\n");
    std::string convertedDefines = "";
    
    const GLchar *sources[] = {
        headersDef.c_str(),
        convertedDefines.c_str(),
        source};
    
    
    
    // Create shader object
    GLuint shader = glCreateShader(shaderType);
    assert(shader != 0);
    assert(glGetError() == GL_NO_ERROR);
    
    // Link shader object and source code
    glShaderSource(shader, sizeof(sources)/sizeof(*sources), sources, nullptr);
    // Compile GLSL
    glCompileShader(shader);
    
    // Check compile error
    {
        GLint compileSuccess = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compileSuccess);
        if (compileSuccess == GL_FALSE) {
            // エラーが発生した
            GLint infoLen = 0;
            // エラーメッセージを取得
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen > 1) {
                GLchar *message = (GLchar*) calloc(infoLen, sizeof(GLchar));
                glGetShaderInfoLog(shader, infoLen, NULL, message);
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
