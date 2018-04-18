//
//  SGGeometry.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/18.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGGeometry.hpp"

using namespace SimpleGameEngine;

Vec2::Vec2()
: x(0.5f)
, y(0.5f)
{}

Vec2::Vec2(float _x, float _y)
: x (_x)
, y (_y)
{}

const Vec2 Vec2::CENTER(0.5f, 0.5f);
