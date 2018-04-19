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
#include "../Renderer/Shader/ShaderPosition.vert"
#include "../Renderer/Shader/ShaderColor.frag"
#include <assert.h>

using namespace SimpleGameEngine;

Triangle::Triangle()
{
    _shaderProgram = _shaderManager->getShaderProgram(ShaderManager::ShaderType::POSITION_AND_COLOR);
}

void Triangle::draw()
{
    _shaderProgram->use();
    
    // Get vertex shader pos variable
    GLint attrPos = glGetAttribLocation(_shaderProgram->getShader(), "attr_pos");
    assert(attrPos >= 0);
    GLint unifColor = glGetUniformLocation(_shaderProgram->getShader(), "unif_color");
    assert(unifColor >= 0);
    
    glEnableVertexAttribArray(attrPos);
    
    // Vertex data
    const GLfloat position[] = {
        _position.x, _position.y + 0.5f,
        _position.x - 0.5f, _position.y - 0.5f,
        _position.x + 0.5f, _position.y - 0.5f
    };
    
    glVertexAttribPointer(attrPos, 2, GL_FLOAT, GL_FALSE, 0., position);
    
    // Fragment data
    glUniform4f(unifColor, _color.r, _color.g, _color.b, _color.a);
    
    // Draw
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
