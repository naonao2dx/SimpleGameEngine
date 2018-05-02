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
    
    Vertex vert1 = Vertex { Vec2 { 0.0f, 0.5f}, Color4B::RED } ;
    Vertex vert2 = Vertex { Vec2 { -0.5f, -0.5f}, Color4B::GREEN } ;
    Vertex vert3 = Vertex { Vec2 { 0.5f, -0.5f}, Color4B::BLUE } ;
    std::vector<Vertex> vertex = { vert1, vert2, vert3 };
    setVertex(vertex);
    
    return true;
}

void Primitives::setShaderPositionAndColor()
{
    setShaderProgram(ShaderManager::ShaderType::POSITION_AND_COLOR);
}

void Primitives::setShaderVertexColor()
{
    setShaderProgram(ShaderManager::ShaderType::VERTEX_COLOR);
}

void Primitives::setShape(GLenum shape)
{
    _shape = shape;
}

void Primitives::setColor(const Color4F& color)
{
    _color = color;
}

void Primitives::setLineWidth(GLfloat lineWidth)
{
    _lineWidth = lineWidth;
}

void Primitives::draw()
{
    _shaderProgram->setVertex(_vertex);
    _shaderProgram->setShape(_shape);
    if (_shaderType == ShaderManager::ShaderType::POSITION_AND_COLOR) {
        std::dynamic_pointer_cast<ShaderPositionAndColor>(_shaderProgram)->setColor(_color);
        std::dynamic_pointer_cast<ShaderPositionAndColor>(_shaderProgram)->setLineWidth(_lineWidth);
    }
    _shaderProgram->draw();
}
