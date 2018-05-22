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
: position()
, color()
{
}

Vertex::Vertex(Vec3 _position)
: position(_position)
{
}

Vertex::Vertex(Vec3 _position, Color4B _color)
: position(_position)
, color(_color)
{
}

Vertex::Vertex(Vec2 _position)
: color()
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
