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

Vertex::Vertex(Vec2 _position)
: position(_position)
, color()
{
}

Vertex::Vertex(Vec2 _position, Color4B _color)
: position(_position)
, color(_color)
{
}
