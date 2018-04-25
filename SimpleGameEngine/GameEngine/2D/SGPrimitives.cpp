//
//  SGPrimitives.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/17.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGPrimitives.hpp"
#include "SGConsole.hpp"
#include "SGShaderPositionAndColor.hpp"
#include <OpenGLES/ES2/gl.h>
#include <assert.h>

using namespace SimpleGameEngine;

Primitives::Primitives()
:_shape(GL_TRIANGLES)
,_lineWidth(1.0f)
{
    init();
}

bool Primitives::init()
{
    Node::init();
    setShaderPositionAndColor();
    
    std::shared_ptr<Vec2> pos1 = std::make_shared<Vec2>(0.0f, 0.5f);
    std::shared_ptr<Vec2> pos2 = std::make_shared<Vec2>(-0.5f, -0.5f);
    std::shared_ptr<Vec2> pos3 = std::make_shared<Vec2>(0.5f, -0.5f);
    std::vector<std::shared_ptr<Vec2>> position = {pos1, pos2, pos3};
    setPosition(position);
    
    return true;
}

void Primitives::setShaderPositionAndColor()
{
    setShaderProgram(ShaderManager::ShaderType::POSITION_AND_COLOR);
}

void Primitives::setShape(GLenum shape)
{
    _shape = shape;
}

void Primitives::setLineWidth(GLfloat lineWidth)
{
    _lineWidth = lineWidth;
}

void Primitives::draw()
{
    _shaderProgram->setPosition(_position);
    _shaderProgram->setColor(_color);
    _shaderProgram->setShape(_shape);
    _shaderProgram->setLineWidth(_lineWidth);
    _shaderProgram->draw();
}
