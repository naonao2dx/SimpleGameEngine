//
//  SGBaseScene.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/17.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGBaseScene.hpp"
#include "SGConsole.hpp"

using namespace SimpleGameEngine;

std::shared_ptr<Scene> Scene::create()
{
    Console::logDebug("Scene::create");
    std::shared_ptr<Scene> scene(new (std::nothrow) Scene());
    if (scene && scene->init()) {
        return scene;
    }
    return nullptr;
}

Scene::Scene()
{
    _camera = Camera::create();
}

void Scene::render()
{
    visit();
}
