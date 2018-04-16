//
//  AppDelegate.cpp
//  SimpleGameEngine
//
//  Created by Nao on 2018/04/17.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "AppDelegate.hpp"
#include "../src/base/SGDirector.hpp"

using namespace SimpleGameEngine;

bool AppDelegate::applicationDidFinishLaunching()
{
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    
    return true;
}
