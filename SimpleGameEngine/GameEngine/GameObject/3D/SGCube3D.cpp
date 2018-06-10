//
//  SGCube3D.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/31.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGCube3D.hpp"
#include "SGShaderPositionAndColor.hpp"
#include "SGShaderPositionAndColor3D.hpp"
#include "SGSpriteCache.hpp"
#include "SGConsole.hpp"

using namespace SimpleGameEngine;

std::shared_ptr<Cube3D> Cube3D::createWithColor(const SimpleGameEngine::Color4F& color)
{
    std::shared_ptr<Cube3D> obj(new (std::nothrow) Cube3D());
    obj->setColor(color);
    obj->setShaderProgram(ShaderManager::ShaderType::POSITION_AND_COLOR_3D);
    return obj;
}

Cube3D::Cube3D()
{
    _vertex.reserve(36);
    setVertex();
}

void Cube3D::setColor(const SimpleGameEngine::Color4F &color)
{
    _color = color;
}

void Cube3D::setSize3D(SimpleGameEngine::Vec3 size)
{
    setWidth(size.x);
    setHeight(size.y);
    setDepth(size.z);
}

void Cube3D::draw()
{
    _shaderProgram->setVertex(_vertex);
    _shaderProgram->setShape(GL_TRIANGLES);
    std::dynamic_pointer_cast<ShaderPositionAndColor>(_shaderProgram)->setColor(_color);
    std::dynamic_pointer_cast<ShaderPositionAndColor>(_shaderProgram)->setLineWidth(1.0f);
    std::dynamic_pointer_cast<ShaderPositionAndColor3D>(_shaderProgram)->setWlp(_camera->getWlp());
    _shaderProgram->draw();
}

void Cube3D::setVertex()
{
    _vertex.clear();
    const GLfloat LEFT = static_cast<GLfloat>(_position.x) - static_cast<GLfloat>(_width)/2.0f;
    const GLfloat RIGHT = static_cast<GLfloat>(_position.x) + static_cast<GLfloat>(_width)/2.0f;
    const GLfloat FRONT = static_cast<GLfloat>(_position.z) - static_cast<GLfloat>(_depth)/2.0f;
    const GLfloat BACK = static_cast<GLfloat>(_position.z) + static_cast<GLfloat>(_depth)/2.0f;
    const GLfloat TOP = static_cast<GLfloat>(_position.y) + static_cast<GLfloat>(_height)/2.0f;
    const GLfloat BOTTOM = static_cast<GLfloat>(_position.y) - static_cast<GLfloat>(_height)/2.0f;
    
    // BOTTOM
    _vertex.emplace_back( Vertex({LEFT, BOTTOM, FRONT}));
    _vertex.emplace_back( Vertex({RIGHT, BOTTOM, FRONT}));
    _vertex.emplace_back( Vertex({LEFT, BOTTOM, BACK}));
    _vertex.emplace_back( Vertex({LEFT, BOTTOM, BACK}));
    _vertex.emplace_back( Vertex({RIGHT, BOTTOM, FRONT}));
    _vertex.emplace_back( Vertex({RIGHT, BOTTOM, BACK}));
    
    // TOP
    _vertex.emplace_back( Vertex({LEFT, TOP, FRONT}));
    _vertex.emplace_back( Vertex({LEFT, TOP, BACK}));
    _vertex.emplace_back( Vertex({RIGHT, TOP, FRONT}));
    _vertex.emplace_back( Vertex({LEFT, TOP, BACK}));
    _vertex.emplace_back( Vertex({RIGHT, TOP, BACK}));
    _vertex.emplace_back( Vertex({RIGHT, TOP, FRONT}));
    
    // RIGHT
    _vertex.emplace_back( Vertex({RIGHT, TOP, FRONT}));
    _vertex.emplace_back( Vertex({RIGHT, TOP, BACK}));
    _vertex.emplace_back( Vertex({RIGHT, BOTTOM, FRONT}));
    _vertex.emplace_back( Vertex({RIGHT, TOP, BACK}));
    _vertex.emplace_back( Vertex({RIGHT, BOTTOM, BACK}));
    _vertex.emplace_back( Vertex({RIGHT, BOTTOM, FRONT}));
    
    // LEFT
    _vertex.emplace_back( Vertex({LEFT, TOP, FRONT}));
    _vertex.emplace_back( Vertex({LEFT, BOTTOM, FRONT}));
    _vertex.emplace_back( Vertex({LEFT, TOP, BACK}));
    _vertex.emplace_back( Vertex({LEFT, TOP, BACK}));
    _vertex.emplace_back( Vertex({LEFT, BOTTOM, FRONT}));
    _vertex.emplace_back( Vertex({LEFT, BOTTOM, BACK}));
    
    // BACK
    _vertex.emplace_back( Vertex({LEFT, TOP, BACK}));
    _vertex.emplace_back( Vertex({LEFT, BOTTOM, BACK}));
    _vertex.emplace_back( Vertex({RIGHT, TOP, BACK}));
    _vertex.emplace_back( Vertex({RIGHT, TOP, BACK}));
    _vertex.emplace_back( Vertex({LEFT, BOTTOM, BACK}));
    _vertex.emplace_back( Vertex({RIGHT, BOTTOM, BACK}));
    
    // FRONT
    _vertex.emplace_back( Vertex({LEFT, TOP, FRONT}));
    _vertex.emplace_back( Vertex({RIGHT, TOP, FRONT}));
    _vertex.emplace_back( Vertex({LEFT, BOTTOM, FRONT}));
    _vertex.emplace_back( Vertex({RIGHT, TOP, FRONT}));
    _vertex.emplace_back( Vertex({RIGHT, BOTTOM, FRONT}));
    _vertex.emplace_back( Vertex({LEFT, BOTTOM, FRONT}));
    
}
