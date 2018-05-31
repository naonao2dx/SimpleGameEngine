//
//  SGNode3D.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/31.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGNode3D.hpp"

using namespace SimpleGameEngine;

Node3D::Node3D()
: _position({0.0f, 0.0f, 0.0f})
, _width(1)
, _height(1)
, _depth(1)
{
    
}

void Node3D::setPosition(SimpleGameEngine::Vec3 position)
{
    _position = position;
    setVertex();
}

void Node3D::setWidth(int width)
{
    _width = width;
    setVertex();
}

void Node3D::setHeight(int height)
{
    _height = height;
    setVertex();
}

void Node3D::setDepth(int depth)
{
    _depth = depth;
    setVertex();
}

void Node3D::visit()
{
    update();
    draw();
}
