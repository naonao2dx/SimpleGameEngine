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
#include "SGShaderPositionAndColor3D.hpp"
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

std::shared_ptr<Primitives> Primitives::createWithPositionAndColor3DShader(int shapeType)
{
    std::shared_ptr<Primitives> result(new (std::nothrow) Primitives(shapeType));
    if (result && result->init()) {
        result->setShaderPositionAndColor3D();
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
, _blendFunc(BlendFunc::DISABLE)
{
    _director = Director::getInstance();
    _shaderManager = ShaderManager::getInstance();
}

bool Primitives::init()
{
    Vertex vert1 = Vertex { Vec3 { 0.0f, 0.5f, 0.0f}, Color4B::RED } ;
    Vertex vert2 = Vertex { Vec3 { -0.5f, -0.5f, 0.0f}, Color4B::GREEN } ;
    Vertex vert3 = Vertex { Vec3 { 0.5f, -0.5f, 0.0f}, Color4B::BLUE } ;
    std::vector<Vertex> vertex = { vert1, vert2, vert3 };
    setNormalizedVertex(vertex);
    
    return true;
}

void Primitives::update()
{
    
}

void Primitives::setVertex(std::vector<Vertex> &vertex)
{
    _vertex = vertex;
    
    Size designResolutionSize = _director->getDesignResolutionSize();
    _normalizedVertex.clear();
    
    for (auto itr = vertex.cbegin(); itr != vertex.cend(); ++itr) {
        Vertex normalizedVertex;
        normalizedVertex.position.x = (itr->position.x / designResolutionSize.width * 2) - 1.0f;
        normalizedVertex.position.y = ((itr->position.y / designResolutionSize.height * 2) - 1.0f) * -1.0f;
        normalizedVertex.position.z = itr->position.z;
        normalizedVertex.color = itr->color;
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
        vertex.position.x = (itr->position.x + 1.0f) / 2 * designResolutionSize.width;
        vertex.position.y = (itr->position.y / -1.0f + 1.0f) / 2 * designResolutionSize.height;
        vertex.position.z = itr->position.z;
        vertex.color = itr->color;
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

void Primitives::setShaderPositionAndColor3D()
{
    setShaderProgram(ShaderManager::ShaderType::POSITION_AND_COLOR_3D);
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

void Primitives::setBlendFunc(SimpleGameEngine::BlendFunc blendFunc)
{
    _blendFunc = blendFunc;
}

void Primitives::draw()
{
    _shaderProgram->setVertex(_normalizedVertex);
    _shaderProgram->setShape(_shapeType);
    _shaderProgram->setBlendFunc(_blendFunc);
    if (_shaderType == ShaderManager::ShaderType::POSITION_AND_COLOR || _shaderType == ShaderManager::ShaderType::POSITION_AND_COLOR_3D) {
        std::dynamic_pointer_cast<ShaderPositionAndColor>(_shaderProgram)->setColor(_color);
        std::dynamic_pointer_cast<ShaderPositionAndColor>(_shaderProgram)->setLineWidth(_lineWidth);
    }
    if (_shaderType == ShaderManager::ShaderType::POSITION_AND_COLOR_3D) {
        std::dynamic_pointer_cast<ShaderPositionAndColor3D>(_shaderProgram)->setWlp(_camera->getWlp());
    }
    _shaderProgram->draw();
}
