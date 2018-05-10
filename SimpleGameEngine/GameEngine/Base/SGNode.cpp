//
//  SGNode.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/17.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGNode.hpp"
#include "SGDirector.hpp"
#include "SGConsole.hpp"
#include <memory>
class vector;

using namespace SimpleGameEngine;

Node::Node()
{
    _director = Director::getInstance();
    _shaderManager = ShaderManager::getInstance();
    _designResolutionSize = _director->getDesignResolutionSize();
    _aspect = static_cast<GLfloat>(_designResolutionSize.width) / static_cast<GLfloat>(_designResolutionSize.height);
    
    setNormalizedPosition(0.0f, 0.0f);
}

bool Node::init()
{
    return true;
}

void Node::addChild(const std::shared_ptr<DrawingObject> child)
{
    _children.push_back(child);
}

void Node::setShaderProgram(ShaderManager::ShaderType shaderType) {
    _shaderType = shaderType;
    _shaderProgram = _shaderManager->getShaderProgram(shaderType);
}

void Node::visit()
{
    for (auto it = _children.cbegin(); _children.cend() != it; ++it) {
        (*it)->visit();
    }
    draw();
}

float Node::positionXtoNormalizedPositionX(int x)
{
    _designResolutionSize = _director->getDesignResolutionSize();
    return (static_cast<float>(x) / _designResolutionSize.width) * 2 - 1.0f;
}

float Node::positionYtoNormalizedPositionY(int y)
{
    _designResolutionSize = _director->getDesignResolutionSize();
    return -(static_cast<float>(y) / _designResolutionSize.height * 2 - 1.0f);
}

int Node::normalizedPositionXtoPositionX(float normalizedPositionX)
{
    _designResolutionSize = _director->getDesignResolutionSize();
    return (normalizedPositionX + 1.0f) / 2 * _designResolutionSize.width;
}

int Node::normalizedPositionYtoPositionY(float normalizedPositionY)
{
    _designResolutionSize = _director->getDesignResolutionSize();
    return (normalizedPositionY / -1.0f + 1.0f) / 2 * _designResolutionSize.height;
}

void Node::setPosition(const Vec2& position)
{
    setPosition(position.x, position.y);
}

void Node::setPosition(const float x, const float y)
{
    setPositionX(x);
    setPositionY(y);
}

void Node::setPositionX(const float x)
{
    _position.x = x;
    _normalizedPosition.x = positionXtoNormalizedPositionX(x);
    setVertex();
    setMatrix();
}

void Node::setPositionY(const float y)
{
    _position.y = y;
    _normalizedPosition.y = positionYtoNormalizedPositionY(y);
    setVertex();
    setMatrix();
}

void Node::setNormalizedPosition(const SimpleGameEngine::Vec2 &normalizedPosition)
{
    setNormalizedPosition(normalizedPosition.x, normalizedPosition.y);
}

void Node::setNormalizedPosition(const float normalizedPositionX, const float normalizedPositionY)
{
    setNormalizedPositionX(normalizedPositionX);
    setNormalizedPositionY(normalizedPositionY);
}

void Node::setNormalizedPositionX(const float normalizedPositionX)
{
    _normalizedPosition.x = normalizedPositionX;
    _position.x = normalizedPositionXtoPositionX(normalizedPositionX);
    setVertex();
    setMatrix();
}

void Node::setNormalizedPositionY(const float normalizedPositionY)
{
    _normalizedPosition.y = normalizedPositionY;
    _position.y = normalizedPositionYtoPositionY(normalizedPositionY);
    setVertex();
    setMatrix();
}

void Node::setOriginSize(SimpleGameEngine::Size &originSize)
{
    setOriginSize(originSize.width, originSize.height);
}

void Node::setOriginSize(int width, int height)
{
    setOriginWidth(width);
    setOriginHeigh(height);
}

void Node::setOriginWidth(int width)
{
    _originSize.width = width;
    _originScale.x = static_cast<float>(width) / _designResolutionSize.width * 2;
}

void Node::setOriginHeigh(int height)
{
    _originSize.height = height;
    _originScale.y = static_cast<float>(height) / _designResolutionSize.width * 2;
}

void Node::setContentSize(SimpleGameEngine::Size &contentSize)
{
    setContentSize(contentSize.width, contentSize.height);
}

void Node::setContentSize(int width, int height)
{
    setWidth(width);
    setHeight(height);
}

void Node::setWidth(int width)
{
    _contentSize.width = width;
    _scale.x = static_cast<float>(width) / static_cast<float>(_originSize.width);
    setVertex();
    setMatrix();
}

void Node::setHeight(int height)
{
    _contentSize.height = height;
    _scale.y = static_cast<float>(height) / static_cast<float>(_originSize.height);
    setVertex();
    setMatrix();
}

void Node::setScale(SimpleGameEngine::Vec2 &scale)
{
    setScale(scale.x, scale.y);
}

void Node::setScale(GLfloat x, GLfloat y)
{
    setScaleX(x);
    setScaleY(y);
}

void Node::setScaleX(GLfloat x)
{
    _scale.x = x;
    _contentSize.width = _originSize.width * x;
    setVertex();
    setMatrix();
}

void Node::setScaleY(GLfloat y)
{
    _scale.y = y;
    _contentSize.height = _originSize.height * y;
    setVertex();
    setMatrix();
}

void Node::setRotate(GLfloat rotate)
{
    _rotate = rotate;
    setMatrix();
}

void Node::setMatrix()
{
    const Mat4 aspect = Mat4::scale(1, _aspect, 1);
    
    Vec2 realScale {_originScale.x * _scale.x, _originScale.y * _scale.y};
    const Mat4 scale = Mat4::scale(realScale.x, realScale.y, 0);
//
//    const GLfloat vertexLeft = 0.5f + (1.0f - realScale.x) * 0.5f;
//    const GLfloat vertexTop = 0.5f + (1.0f - realScale.y) * 0.5f;
//    const Mat4 translate = Mat4::translate(-vertexLeft + _normalizedPosition.x, vertexTop + _normalizedPosition.y, 0);
    
    const Mat4 translate = Mat4::translate(_normalizedPosition.x, _normalizedPosition.y, 0);
    const Mat4 rotate = Mat4::rotate(Vec3::create(0.0f, 0.0f, 1.0f), _rotate);
    _matrix = Mat4::multiply(translate, aspect);
    _matrix = Mat4::multiply(_matrix, rotate);
    _matrix = Mat4::multiply(_matrix, scale);
}

void Node::setVertex()
{
//    float left = positionXtoNormalizedPositionX(_position.x - (_contentSize.width / 2));
//    float right = positionXtoNormalizedPositionX(_position.x + (_contentSize.width / 2));
//    float top = positionYtoNormalizedPositionY(_position.y - (_contentSize.height / 2));
//    float bottom = positionYtoNormalizedPositionY(_position.y + (_contentSize.height / 2));
//
    _vertex.clear();
//    _vertex.emplace_back(Vertex { Vec2 { left, top } });
//    _vertex.emplace_back(Vertex { Vec2 { left, bottom } });
//    _vertex.emplace_back(Vertex { Vec2 { right, top } });
//    _vertex.emplace_back(Vertex { Vec2 { right, bottom } });
    
    Vertex pos1 = Vertex {Vec2{-0.5f, 0.5f}};
    Vertex pos2 = Vertex {Vec2{-0.5f, -0.5f}};
    Vertex pos3 = Vertex {Vec2{0.5f, 0.5f}};
    Vertex pos4 = Vertex {Vec2{0.5f, -0.5f}};
    std::vector<Vertex> position{pos1, pos2, pos3, pos4};
    _vertex = position;
    
//    Console::logDebug("left: %f", left);
//    Console::logDebug("bottom: %f", bottom);
//    Console::logDebug("right: %f", right);
//    Console::logDebug("top: %f", top);
}
