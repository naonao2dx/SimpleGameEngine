//
//  SGVertex.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/07.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGVertex.h"

using namespace SimpleGameEngine;

Vertex::Vertex()
: position(0.0f, 0.0f, 0.0f)
, color(Color4B::WHITE)
{
}

Vertex::Vertex(Vec3 _position)
: position(_position)
, color(Color4B::WHITE)
{
}

Vertex::Vertex(Vec3 _position, Color4B _color)
: position(_position)
, color(_color)
{
}

Vertex::Vertex(Vec2 _position)
: color(Color4B::WHITE)
{
    position.x = _position.x;
    position.y = _position.y;
    position.z = 0.0f;
}

Vertex::Vertex(Vec2 _position, Color4B _color)
: color(_color)
{
    position.x = _position.x;
    position.y = _position.y;
    position.z = 0.0f;
}

VertexWithColor::VertexWithColor()
: position(0.0f, 0.0f, 0.0f)
, color(Color4B::WHITE)
{
}

VertexWithColor::VertexWithColor(Vec3 _position)
: position(_position)
, color(Color4B::WHITE)
{
}

VertexWithColor::VertexWithColor(Vec3 _position, Color4B _color)
: position(_position)
, color(_color)
{
}

VertexWithColor::VertexWithColor(Vec2 _position)
: color(Color4B::WHITE)
{
    position.x = _position.x;
    position.y = _position.y;
    position.z = 0.0f;
}

VertexWithColor::VertexWithColor(Vec2 _position, Color4B _color)
: color(_color)
{
    position.x = _position.x;
    position.y = _position.y;
    position.z = 0.0f;
}
