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
, uv(Vec2::ZERO)
{
}

Vertex::Vertex(Vec3 _position)
: position(_position)
, color(Color4B::WHITE)
, uv(Vec2::ZERO)
{
}

Vertex::Vertex(Vec3 _position, Color4B _color)
: position(_position)
, color(_color)
, uv(Vec2::ZERO)
{
}

Vertex::Vertex(Vec3 _position, Vec2 _uv)
: position(_position)
, color(Color4B::WHITE)
, uv(_uv)
{
}

Vertex::Vertex(Vec2 _position)
: color(Color4B::WHITE)
, uv(Vec2::ZERO)
{
    position.x = _position.x;
    position.y = _position.y;
    position.z = 0.0f;
}

Vertex::Vertex(Vec2 _position, Color4B _color)
: color(_color)
, uv(Vec2::ZERO)
{
    position.x = _position.x;
    position.y = _position.y;
    position.z = 0.0f;
}

Vertex::Vertex(Vec2 _position, Vec2 _uv)
: color(Color4B::WHITE)
, uv(_uv)
{
    position.x = _position.x;
    position.y = _position.y;
    position.z = 0.0f;
}

Vertex::Vertex(Vec2 _position, Color4B _color, Vec2 _uv)
: color(_color)
, uv(_uv)
{
    position.x = _position.x;
    position.y = _position.y;
    position.z = 0.0f;
}
