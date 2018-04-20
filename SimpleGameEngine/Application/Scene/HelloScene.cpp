//
//  HelloScene.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/17.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "HelloScene.hpp"
#include "../../GameEngine/Base/SGBaseScene.hpp"
#include "../../GameEngine/Util/SGConsole.hpp"
#include "../../GameEngine/2D/SGTriangle.hpp"
#include "../../GameEngine/Renderer/SGShaderManager.hpp"

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
    // Sample Triangle 1
    std::shared_ptr<Node> tri = std::make_shared<Triangle>();
    Vec2 pos1 = Vec2(-0.2f, 0.7f);
    Vec2 pos2 = Vec2(-0.7f, -0.3f);
    Vec2 pos3 = Vec2(0.3f, -0.3f);
    std::vector<Vec2> position = {pos1, pos2, pos3};
    tri->setPosition(position);
    
    Color4F color = { 1.0f, 1.0f, 0.0f, 1.0f };
    tri->setColor(color);
    
    addChild(tri);
   
    // Sample Triangle 2
    std::shared_ptr<Node> tri2 = std::make_shared<Triangle>();
    Vec2 pos4 = Vec2(0.2f, 0.3f);
    Vec2 pos5 = Vec2(-0.3f, -0.7f);
    Vec2 pos6 = Vec2(0.7f, -0.7f);
    std::vector<Vec2> position2 = {pos4, pos5, pos6};
    tri2->setPosition(position2);
    
    Color4F color2 = { 0.0f, 1.0f, 1.0f, 1.0f };
    tri2->setColor(color2);
    
    addChild(tri2);
    return true;
}
