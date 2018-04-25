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
:_color(Color4F::WHITE)
,_vertex()
{
}

bool Node::init()
{
    _shaderManager = ShaderManager::getInstance();
    return true;
}

void Node::addChild(std::shared_ptr<Node> child)
{
    _children.push_back(child);
}

void Node::setShaderProgram(ShaderManager::ShaderType shaderType) {
    _shaderProgram = _shaderManager->getShaderProgram(shaderType);
}

void Node::visit()
{
    for (auto it = _children.cbegin(); _children.cend() != it; ++it) {
        (*it)->visit();
    }
    draw();
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

void Node::setColor(const Color4F &color)
{
    _color = color;
}

void Node::setVertex(const std::vector<Vertex> vertex)
{
    _vertex = vertex;
}
