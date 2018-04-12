//
//  SGRenderer.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/12.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGRenderer.hpp"
#include <OpenGLES/ES2/gl.h>

using namespace SimpleGameEngine;

void Renderer::clear()
{
    glDepthMask(true);
    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthMask(false);
}
