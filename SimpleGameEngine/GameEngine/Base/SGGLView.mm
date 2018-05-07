//
//  SGGLView.cpp
//  SimpleGameEngine
//
//  Created by Nao on 2018/03/21.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include <memory>
#include "SGGLView.h"

#include "SGEAGLView.h"
#include "SGConsole.hpp"

using namespace SimpleGameEngine;

std::shared_ptr<GLView> GLView::createWithEAGLView(void* eaglView)
{
    auto ret = std::make_shared<GLView>();
    if (ret && ret->initWithEAGLView(eaglView)) {
        return ret;
    }
    return nullptr;
}

bool GLView::initWithEAGLView(void *eaglView)
{
    _eaglView = eaglView;
    SGEAGLView* glView = (__bridge SGEAGLView*)_eaglView;
    
    _screenSize.width = _designResolutionSize.width = [glView getWidth];
    _screenSize.height = _designResolutionSize.height = [glView getHeight];
    
    GLint textureUnits = 0;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &textureUnits);
    Console::logDebug("GPU Texture Units %d", textureUnits);
    
    const GLchar* const EXTENSIONS = (const GLchar* const) glGetString(GL_EXTENSIONS);
    Console::logDebug("Extensions :: %s", EXTENSIONS);
    
    return true;
}
