//
//  HelloScene.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/17.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "HelloScene.hpp"
#include "../../src/base/SGBaseScene.hpp"
#include "../../src/base/SGConsole.hpp"
#include "../../src/2D/SGTriangle.hpp"

using namespace SimpleGameEngine;

std::shared_ptr<Scene> HelloScene::createScene()
{
    Console::logDebug("HelloScene::createScene");
    return HelloScene::create();
}

std::shared_ptr<HelloScene> HelloScene::create()
{
    Console::logDebug("HelloScene::create");
    std::shared_ptr<HelloScene> scene = std::make_shared<HelloScene>();
    if (scene && scene->init()) {
        return scene;
    }
    return nullptr;
}

bool HelloScene::init()
{
    Console::logDebug("HelloScene::init");
    
    // Sample Triangle 1
    std::shared_ptr<Node> tri = std::make_shared<Triangle>();
    Vec2 position = {0.2f, -0.2f};
    tri->setPosition(position);
    addChild(tri);
   
    // Sample Triangle 2
    std::shared_ptr<Node> tri2 = std::make_shared<Triangle>();
    Vec2 position2 = {-0.2f, 0.2f};
    tri2->setPosition(position2);
    addChild(tri2);
    return true;
}
