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
#include <assert.h>

using namespace SimpleGameEngine;

Triangle::Triangle()
{
    _shaderManager = ShaderManager::getInstance();
    init();
}

bool Triangle::init()
{
    setShaderPositionAndColor();
    
    Vec2 pos1 = Vec2(0.0f, 0.5f);
    Vec2 pos2 = Vec2(-0.5f, -0.5f);
    Vec2 pos3 = Vec2(0.5f, -0.5f);
    std::vector<Vec2> position = {pos1, pos2, pos3};
    setPosition(position);
    
    setColor(Color4F::WHITE);
    return true;
}

void Triangle::setPosition(std::vector<Vec2> position)
{
    _position = std::move(position);
}

void Triangle::setShaderPositionAndColor()
{
    _shaderProgram = _shaderManager->getShaderProgram(ShaderManager::ShaderType::POSITION_AND_COLOR);
}

void Triangle::draw()
{
    _shaderProgram->use();
    
    // Vertex data
    GLfloat position[_position.size() * 2];
    for (int i = 0; i < _position.size(); i++) {
        position[i * 2] = _position.at(i).x;
        position[i * 2 + 1] = _position.at(i).y;
    }
    
    // Get vertex shader pos variable
    GLint attrPos = glGetAttribLocation(_shaderProgram->getShader(), "attr_pos");
    assert(attrPos >= 0);
    GLint unifColor = glGetUniformLocation(_shaderProgram->getShader(), "unif_color");
    assert(unifColor >= 0);
    
    glEnableVertexAttribArray(attrPos);
    
    glVertexAttribPointer(attrPos, 2, GL_FLOAT, GL_FALSE, 0., position);
    
    // Fragment data
    glUniform4f(unifColor, _color.r, _color.g, _color.b, _color.a);
    
    // Draw
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
