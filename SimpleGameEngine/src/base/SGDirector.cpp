//
//  SGDirector.cpp
//  SimpleGameEngine
//
//  Created by Nao on 2018/03/21.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include <memory>
#include "SGDirector.hpp"

using namespace SimpleGameEngine;

bool Director::init()
{
    return true;
}

void Director::setOpenGLView(std::shared_ptr<GLView> openGLView)
{
    if(!_openGLView) {
        _openGLView = openGLView;
    }

}
