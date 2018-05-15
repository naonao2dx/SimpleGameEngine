//
//  SGBlendFunc.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/15.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGBlendFunc.hpp"

using namespace SimpleGameEngine;

BlendFunc::BlendFunc(GLenum _src, GLenum _dst)
: src(_src)
, dst(_dst)
{
}

const BlendFunc BlendFunc::DISABLE(GL_ONE, GL_ZERO);
const BlendFunc BlendFunc::ALPHA_PREMULTIPLIED(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
