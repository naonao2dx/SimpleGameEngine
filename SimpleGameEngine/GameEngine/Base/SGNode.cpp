//
//  SGNode.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/17.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGNode.hpp"
#include <memory>
class vector;

using namespace SimpleGameEngine;

Node::Node()
: _shaderType(0)
, _vertex()
{
}

bool Node::init()
{
    _shaderManager = ShaderManager::getInstance();
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
