//
//  SGColor.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/18.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGColor.hpp"

using namespace SimpleGameEngine;

Color4F::Color4F()
: r(0.0f)
, g(0.0f)
, b(0.0f)
, a(0.0f)
{}

Color4F::Color4F(float _r, float _g, float _b, float _a)
: r(_r)
, g(_g)
, b(_b)
, a(_a)
{}

const Color4F Color4F::WHITE(1, 1, 1, 1);
const Color4F Color4F::BLACK(0, 0, 0, 1);
const Color4F Color4F::RED(1, 0, 0, 1);
const Color4F Color4F::GREEN(0, 1, 0, 1);
const Color4F Color4F::BLUE(0, 0, 1, 1);

Color4B::Color4B()
: r(0)
, g(0)
, b(0)
, a(0)
{}

Color4B::Color4B(GLubyte _r, GLubyte _g, GLubyte _b, GLubyte _a)
: r(_r)
, g(_g)
, b(_b)
, a(_a)
{}

const Color4B Color4B::WHITE(255, 255, 255, 255);
const Color4B Color4B::BLACK(0, 0, 0, 255);
const Color4B Color4B::RED(255, 0, 0, 255);
const Color4B Color4B::GREEN(0, 255, 0, 255);
const Color4B Color4B::BLUE(0, 0, 255, 255);

