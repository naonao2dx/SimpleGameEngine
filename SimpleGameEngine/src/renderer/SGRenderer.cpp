//
//  SGRenderer.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/12.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGRenderer.hpp"
#include "SGConsole.hpp"
#include <OpenGLES/ES2/gl.h>

using namespace SimpleGameEngine;

Renderer::Renderer()
: _clearColor(Color4F::BLACK)
{}

void Renderer::clear()
{
    glDepthMask(true);
    glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthMask(false);
}

void Renderer::initGLView()
{
    Console::logDebug("Renderer::initGLView");
}
