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
#include "SGConsole.hpp"

#define MAX(x,y) (((x) < (y)) ? (y) : (x))

using namespace SimpleGameEngine;

class SGEAGLView;

static std::shared_ptr<Director> pInstance;

std::shared_ptr<Director> Director::getInstance()
{
    if (!pInstance) {
        pInstance.reset(new Director());
        pInstance->init();
    }
    return pInstance;
}

bool Director::init()
{
    _renderer.reset(new Renderer());
    return true;
}

void Director::setOpenGLView(std::shared_ptr<GLView> openGLView)
{
    if(!_openGLView) {
        _openGLView = openGLView;
    }
    
    _renderer->initGLView();

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
    //Console::logDebug("Director::drawScene");
    if (_nextScene) {
        _currentScene = _nextScene;
        _nextScene = nullptr;
    }
    
    if (_currentScene) {
        _currentScene->render();
    }
}

void Director::startScene(std::shared_ptr<Scene> scene)
{
    _nextScene = scene;
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
