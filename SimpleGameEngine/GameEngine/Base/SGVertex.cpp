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
: _position()
, _color()
{
}

Vertex::Vertex(Vec2 position)
: _position(position)
, _color()
{
}

Vertex::Vertex(Vec2 position, Color4B color)
: _position(position)
, _color(color)
{
}
