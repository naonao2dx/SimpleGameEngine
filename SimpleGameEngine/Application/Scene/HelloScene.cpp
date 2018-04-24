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
#include "../../GameEngine/2D/SGPrimitives.hpp"
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
    // Sample Primitives 1
    std::shared_ptr<Primitives> tri = std::make_shared<Primitives>();
    Vec2 pos1 = Vec2(-0.9f, 0.9f);
    Vec2 pos2 = Vec2(-0.9f, 0.6f);
    Vec2 pos3 = Vec2(-0.6f, 0.9f);
    Vec2 pos4 = Vec2(-0.6f, 0.6f);
    std::vector<Vec2> position = {pos1, pos2, pos3, pos4};
    tri->setPosition(position);
    tri->setShape(GL_TRIANGLE_STRIP);
    
    Color4F color = { 1.0f, 1.0f, 0.0f, 1.0f };
    tri->setColor(color);
    
    addChild(tri);
   
    // Sample Primitives 2
    std::shared_ptr<Primitives> tri2 = std::make_shared<Primitives>();
    Vec2 pos5 = Vec2(-0.6f, -0.3f);
    Vec2 pos6 = Vec2(-0.8f, -0.7f);
    Vec2 pos7 = Vec2(-0.4f, -0.7f);
    std::vector<Vec2> position2 = {pos5, pos6, pos7};
    tri2->setPosition(position2);
    tri2->setShape(GL_LINE_LOOP);
    tri2->setLineWidth(5.0f);
    
    
    Color4F color2 = { 0.0f, 1.0f, 1.0f, 1.0f };
    tri2->setColor(color2);
    
    addChild(tri2);
    return true;
}
