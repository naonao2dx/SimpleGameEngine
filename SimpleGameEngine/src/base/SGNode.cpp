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
:_position(Vec2({ 0.0f, 0.0f })), _color(RGBA{ 0.0f, 0.0f, 0.0f, 0.0f })
{
}

void Node::addChild(std::shared_ptr<Node> child)
{
    _children.push_back(child);
}

void Node::visit()
{
    for (auto it = _children.cbegin(); _children.cend() != it; ++it) {
        (*it)->visit();
    }
    draw();
}

void Node::draw()
{
    
}

GLuint Node::compileShader(GLuint shaderType, const GLchar *source)
{
    // Create shader object
    GLuint shader = glCreateShader(shaderType);
    // Link shader object and source code
    glShaderSource(shader, 1, &source, NULL);
    // Compile GLSL
    glCompileShader(shader);
    
    return shader;
}

void Node::setPosition(const Vec2& position)
{
    _position = position;
}

void Node::setColor(const SimpleGameEngine::RGBA &color)
{
    _color = color;
}
