//
//  SGNode.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/17.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGNode.hpp"
#include "SGDirector.hpp"
#include <memory>
class vector;

using namespace SimpleGameEngine;

Node::Node()
{
    _director = Director::getInstance();
    _shaderManager = ShaderManager::getInstance();
    
    Size designResolutionSize = _director->getDesignResolutionSize();
    setNormalizedPosition(0.5f, 0.5f);
    setContentSize(designResolutionSize);
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

void Node::setVertex(const std::vector<Vertex> vertex)
{
    _vertex = vertex;
}

float Node::positionXtoNormalizedPositionX(int x)
{
    Size designResolutionSize = _director->getDesignResolutionSize();
    return x / designResolutionSize.width * 2 - 1.0f;
}

float Node::positionYtoNormalizedPositionY(int y)
{
    Size designResolutionSize = _director->getDesignResolutionSize();
    return -(y / designResolutionSize.height * 2 - 1.0f);
}

int Node::normalizedPositionXtoPositionX(float normalizedPositionX)
{
    Size designResolutionSize = _director->getDesignResolutionSize();
    return (normalizedPositionX + 1.0f) / 2 * designResolutionSize.width;
}

int Node::normalizedPositionYtoPositionY(float normalizedPositionY)
{
    Size designResolutionSize = _director->getDesignResolutionSize();
    return (normalizedPositionY / -1.0f + 1.0f) / 2 * designResolutionSize.height;
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
}

void Node::setPositionY(const float y)
{
    _position.y = y;
    _normalizedPosition.y = positionYtoNormalizedPositionY(y);
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
}

void Node::setNormalizedPositionY(const float normalizedPositionY)
{
    _normalizedPosition.y = normalizedPositionY;
    _position.y = normalizedPositionYtoPositionY(normalizedPositionY);
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
}

void Node::setHeight(int height)
{
    _contentSize.height = height;
}
