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
    
    Size designResolutionSize = _director->getDesignResolutionSize();
    setNormalizedPosition(0.0f, 0.0f);
    Console::logDebug("position: %f, %f", _position.x, _position.y);
    Console::logDebug("normalizedPosition: %f, %f", _normalizedPosition.x, _normalizedPosition.y);
    
    setContentSize(designResolutionSize.width / 2, designResolutionSize.height / 2);
    Console::logDebug("contentSize: %d, %d", _contentSize.width, _contentSize.height);
    
    Console::logDebug("left: %f", _vertex.at(0)._position.x);
    Console::logDebug("top: %f", _vertex.at(0)._position.y);
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
    Size designResolutionSize = _director->getDesignResolutionSize();
    return (static_cast<float>(x) / designResolutionSize.width) * 2 - 1.0f;
}

float Node::positionYtoNormalizedPositionY(int y)
{
    Size designResolutionSize = _director->getDesignResolutionSize();
    return -(static_cast<float>(y) / designResolutionSize.height * 2 - 1.0f);
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
    setVertex();
}

void Node::setPositionY(const float y)
{
    _position.y = y;
    _normalizedPosition.y = positionYtoNormalizedPositionY(y);
    setVertex();
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
}

void Node::setNormalizedPositionY(const float normalizedPositionY)
{
    _normalizedPosition.y = normalizedPositionY;
    _position.y = normalizedPositionYtoPositionY(normalizedPositionY);
    setVertex();
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
    setVertex();
}

void Node::setHeight(int height)
{
    _contentSize.height = height;
    setVertex();
}

void Node::setVertex()
{
    float left = positionXtoNormalizedPositionX(_position.x - (_contentSize.width / 2));
    float right = positionXtoNormalizedPositionX(_position.x + (_contentSize.width / 2));
    float top = positionYtoNormalizedPositionY(_position.y - (_contentSize.height / 2));
    float bottom = positionYtoNormalizedPositionY(_position.y + (_contentSize.height / 2));
    
    _vertex.clear();
    _vertex.emplace_back(Vertex { Vec2 { left, top } });
    _vertex.emplace_back(Vertex { Vec2 { left, bottom } });
    _vertex.emplace_back(Vertex { Vec2 { right, top } });
    _vertex.emplace_back(Vertex { Vec2 { right, bottom } });
    
//    Console::logDebug("left: %f", left);
//    Console::logDebug("bottom: %f", bottom);
//    Console::logDebug("right: %f", right);
//    Console::logDebug("top: %f", top);
}
