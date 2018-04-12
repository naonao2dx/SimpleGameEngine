//
//  SGDirector.cpp
//  SimpleGameEngine
//
//  Created by Nao on 2018/03/21.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include <memory>
#include <chrono>
#include <iostream>
#include "SGDirector.hpp"

#define MAX(x,y) (((x) < (y)) ? (y) : (x))

using namespace SimpleGameEngine;
static std::shared_ptr<Director> pInstance;

std::shared_ptr<Director> Director::getInstance()
{
    if (!pInstance) {
        pInstance.reset(new Director());
    }
    return pInstance;
}

bool Director::init()
{
    _renderer.reset(new (std::nothrow) Renderer);
    return true;
}

void Director::setOpenGLView(std::shared_ptr<GLView> openGLView)
{
    if(!_openGLView) {
        _openGLView = openGLView;
    }

}

void Director::mainloop() {
    drawScene();
}

void Director::mainloop(float dt) {
    _deltatime = dt;
    _deltaTimePassedByCaller = true;
    mainloop();
}

void Director::drawScene() {
    calculateDeltaTime();
    
    if (_openGLView) {
        
    }
    
    _renderer->clear();
}

void Director::calculateDeltaTime() {
    if (_nextDeltaTimeZero) {
        _deltatime = 0;
        _nextDeltaTimeZero = false;
    } else {
        if (!_deltaTimePassedByCaller) {
            auto now = std::chrono::steady_clock::now();
            _deltatime = std::chrono::duration_cast<std::chrono::microseconds>(now - _lastUpdate).count() / 1000000.0f;
            _lastUpdate = now;
        }
        _deltatime = MAX(0, _deltatime);
    }
}
