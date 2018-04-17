//
//  SGTriangle.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/17.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGTriangle.hpp"
#include "SGConsole.hpp"
#include <OpenGLES/ES2/gl.h>
#include "../renderer/shader/ShaderPosition.vert"


using namespace SimpleGameEngine;

Triangle::Triangle()
{
    // Create vertex shader object
    GLuint vertShader = compileShader(GL_VERTEX_SHADER, vertShaderSource);
    
    // Fragment shader
    const GLchar *fragShaderSource =
    "void main() {"
    "   gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);"
    "}";
    
    // Create fragment shader object
    GLuint fragShader = compileShader(GL_FRAGMENT_SHADER, fragShaderSource);
    
    // Create program object
    _shaderProgram = glCreateProgram();
    
    // Link vertex shader and program object
    glAttachShader(_shaderProgram, vertShader);
    
    // Link fragment shader and program object
    glAttachShader(_shaderProgram, fragShader);
    
    // Link
    glLinkProgram(_shaderProgram);
    
    // Release shader object
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    
    // Start using shader
    glUseProgram(_shaderProgram);
}

void Triangle::draw()
{
    // Get vertex shader pos variable
    GLint posLocation = glGetAttribLocation(_shaderProgram, "pos");
    glEnableVertexAttribArray(posLocation);
    
    // Vertex data
    const GLfloat vertex[] = {
        _position.x, _position.y + 0.5f,
        _position.x - 0.5f, _position.y - 0.5f,
        _position.x + 0.5f, _position.y - 0.5f
    };
    
    // Create vertedx data
    glVertexAttribPointer(posLocation, 2, GL_FLOAT, GL_FALSE, 0., vertex);
    
    // Draw
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
