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

std::shared_ptr<Primitives> Primitives::create(int shapeType)
{
    std::shared_ptr<Primitives> result(new (std::nothrow) Primitives(shapeType));
    if (result && result->init()) {
        result->setShaderPositionAndColor();
        return result;
    }
    return nullptr;
}

std::shared_ptr<Primitives> Primitives::createWithVertexColorShader(int shapeType)
{
    std::shared_ptr<Primitives> result(new (std::nothrow) Primitives(shapeType));
    if (result && result->init()) {
        result->setShaderVertexColor();
        return result;
    }
    return nullptr;
}

Primitives::Primitives(int shapeType)
: _vertex()
, _normalizedVertex()
, _shapeType(shapeType)
, _lineWidth(1.0f)
, _color(Color4F::WHITE)
{
    _director = Director::getInstance();
    _shaderManager = ShaderManager::getInstance();
}

bool Primitives::init()
{
    Vertex vert1 = Vertex { Vec2 { 0.0f, 0.5f}, Color4B::RED } ;
    Vertex vert2 = Vertex { Vec2 { -0.5f, -0.5f}, Color4B::GREEN } ;
    Vertex vert3 = Vertex { Vec2 { 0.5f, -0.5f}, Color4B::BLUE } ;
    std::vector<Vertex> vertex = { vert1, vert2, vert3 };
    setNormalizedVertex(vertex);
    
    return true;
}

void Primitives::setVertex(std::vector<Vertex> &vertex)
{
    _vertex = vertex;
    
    Size designResolutionSize = _director->getDesignResolutionSize();
    _normalizedVertex.clear();
    
    for (auto itr = vertex.cbegin(); itr != vertex.cend(); ++itr) {
        Vertex normalizedVertex;
        normalizedVertex._position.x = (itr->_position.x / designResolutionSize.width * 2) - 1.0f;
        normalizedVertex._position.y = ((itr->_position.y / designResolutionSize.height * 2) - 1.0f) * -1.0f;
        normalizedVertex._color = itr->_color;
        _normalizedVertex.emplace_back(normalizedVertex);
    }
}

void Primitives::setNormalizedVertex(std::vector<Vertex> &normalizedVertex)
{
    _normalizedVertex = normalizedVertex;
    
    Size designResolutionSize = _director->getDesignResolutionSize();
    _vertex.clear();
    
    for (auto itr = normalizedVertex.cbegin(); itr != normalizedVertex.cend(); ++itr) {
        Vertex vertex;
        vertex._position.x = (itr->_position.x + 1.0f) / 2 * designResolutionSize.width;
        vertex._position.y = (itr->_position.y / -1.0f + 1.0f) / 2 * designResolutionSize.height;
        vertex._color = itr->_color;
        _vertex.emplace_back(vertex);
    }
    
}

void Primitives::setShaderProgram(ShaderManager::ShaderType shaderType)
{
    _shaderType = shaderType;
    _shaderProgram = _shaderManager->getShaderProgram(shaderType);
}

void Primitives::setShaderPositionAndColor()
{
    setShaderProgram(ShaderManager::ShaderType::POSITION_AND_COLOR);
}

void Primitives::setShaderVertexColor()
{
    setShaderProgram(ShaderManager::ShaderType::VERTEX_COLOR);
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
    _shaderProgram->setVertex(_normalizedVertex);
    _shaderProgram->setShape(_shapeType);
    if (_shaderType == ShaderManager::ShaderType::POSITION_AND_COLOR) {
        std::dynamic_pointer_cast<ShaderPositionAndColor>(_shaderProgram)->setColor(_color);
        std::dynamic_pointer_cast<ShaderPositionAndColor>(_shaderProgram)->setLineWidth(_lineWidth);
    }
    _shaderProgram->draw();
}

