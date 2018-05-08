//
//  HelloScene.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/17.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "HelloScene.hpp"
#include "../../GameEngine/Base/SGDirector.hpp"
#include "../../GameEngine/Base/SGBaseScene.hpp"
#include "../../GameEngine/Util/SGConsole.hpp"
#include "../../GameEngine/2D/SGPrimitives.hpp"
#include "../../GameEngine/Renderer/SGShaderManager.hpp"
#include "../../GameEngine/2D/SGSprite.hpp"
#include "../../GameEngine/2D/SGSpriteBlend.hpp"

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
    auto director = Director::getInstance();
    auto visibleSize = director->getDesignResolutionSize();
    Console::logDebug("Width: %d", visibleSize.width);
    Console::logDebug("Height: %d", visibleSize.height);
    
//    // Sample Primitives 1
//    std::shared_ptr<Primitives> tri = Primitives::create(GL_TRIANGLE_STRIP);
//
//    Vertex vert1 = Vertex { Vec2 {20, 50} };
//    Vertex vert2 = Vertex { Vec2 {20, 100} };
//    Vertex vert3 = Vertex { Vec2 {60, 50} };
//    Vertex vert4 = Vertex { Vec2 {60, 100} };
//    std::vector<Vertex> vertex1 = { vert1, vert2, vert3, vert4 };
//    tri->setVertex(vertex1);
//
//    Color4F color = { 1.0f, 1.0f, 0.0f, 1.0f };
//    tri->setColor(color);
//
//    addChild(tri);
//
//    // Sample Primitives 2
//    std::shared_ptr<Primitives> tri2 = Primitives::create(GL_LINE_LOOP);
//
//    Vertex vert5 = Vertex { Vec2 {-0.6f, -0.3f} };
//    Vertex vert6 = Vertex { Vec2 {-0.8f, -0.7f} };
//    Vertex vert7 = Vertex { Vec2 {-0.4f, -0.7f} };
//    std::vector<Vertex> vertex2 = { vert5, vert6, vert7 };
//    tri2->setNormalizedVertex(vertex2);
//    tri2->setLineWidth(5.0f);
//
//    Color4F color2 = { 0.0f, 1.0f, 1.0f, 1.0f };
//    tri2->setColor(color2);
//
//    addChild(tri2);
//
//    // Sample Primitives 3
//    std::shared_ptr<Primitives> tri3 = Primitives::createWithVertexColorShader(GL_TRIANGLES);
//
//    Vertex vert8 = Vertex { Vec2 {0.0f, 0.25f}, Color4B::RED };
//    Vertex vert9 = Vertex { Vec2 {-0.5, -0.25f}, Color4B::GREEN };
//    Vertex vert10 = Vertex { Vec2 {0.5f, -0.25f}, Color4B::BLUE };
//    std::vector<Vertex> vertex3 = { vert8, vert9, vert10 };
//    tri3->setNormalizedVertex(vertex3);
//    addChild(tri3);
    
    std::string atlasname("atlas.json");
    std::string filename0("dragonball.png");
    std::shared_ptr<Sprite> atlas = Sprite::createWithTextureAtlas(atlasname, filename0);
    addChild(atlas);

    // Sample Texture
    std::string filename("headphone.png");
    std::shared_ptr<Sprite> tex = Sprite::create(filename);
    tex->setPosition(45, 45);
    tex->setContentSize(90, 90);
    addChild(tex);

    // Sample Texture2
    std::string filename2("headphone2.png");
    std::shared_ptr<Sprite> tex2 = Sprite::create(filename2);
    tex2->setPosition(135, 135);
    tex2->setContentSize(90, 90);
    addChild(tex2);

    // Sample Blend Texture
    std::string filename3("azarashi.png");
    std::string filename4("blend.png");
    std::shared_ptr<SpriteBlend> tex3 = SpriteBlend::create(filename3, filename4);
    tex3->setPosition(225, 225);
    tex3->setContentSize(90, 90);
    addChild(tex3);
    
    return true;
}
