//
//  SGShaderBase3D.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/06/10.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGShaderBase3D.hpp"

using namespace SimpleGameEngine;

void ShaderBase3D::draw()
{
    ShaderBase::draw();
    glEnable(GL_DEPTH_TEST);
}
