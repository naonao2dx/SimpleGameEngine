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
#include "../../GameEngine/2D/SGTexture2D.hpp"
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
    
    Vertex vert1 = Vertex { Vec2 {-0.9f, 0.9f} };
    Vertex vert2 = Vertex { Vec2 {-0.9f, 0.6f} };
    Vertex vert3 = Vertex { Vec2 {-0.6f, 0.9f} };
    Vertex vert4 = Vertex { Vec2 {-0.6f, 0.6f} };
    std::vector<Vertex> vertex1 = { vert1, vert2, vert3, vert4 };
    tri->setVertex(vertex1);
    
    tri->setShape(GL_TRIANGLE_STRIP);
    
    Color4F color = { 1.0f, 1.0f, 0.0f, 1.0f };
    tri->setColor(color);
    
    //addChild(tri);
   
    // Sample Primitives 2
    std::shared_ptr<Primitives> tri2 = std::make_shared<Primitives>();
    
    Vertex vert5 = Vertex { Vec2 {-0.6f, -0.3f} };
    Vertex vert6 = Vertex { Vec2 {-0.8f, -0.7f} };
    Vertex vert7 = Vertex { Vec2 {-0.4f, -0.7f} };
    std::vector<Vertex> vertex2 = { vert5, vert6, vert7 };
    tri2->setVertex(vertex2);
    
    tri2->setShape(GL_LINE_LOOP);
    tri2->setLineWidth(5.0f);
    
    Color4F color2 = { 0.0f, 1.0f, 1.0f, 1.0f };
    tri2->setColor(color2);
    
    //addChild(tri2);
    
    // Sample Primitives 3
    std::shared_ptr<Primitives> tri3 = std::make_shared<Primitives>();
    
    Vertex vert8 = Vertex { Vec2 {0.0f, 0.25f}, Color4B::RED };
    Vertex vert9 = Vertex { Vec2 {-0.5, -0.25f}, Color4B::GREEN };
    Vertex vert10 = Vertex { Vec2 {0.5f, -0.25f}, Color4B::BLUE };
    std::vector<Vertex> vertex3 = { vert8, vert9, vert10 };
    tri3->setVertex(vertex3);
    tri3->setShaderVertexColor();
    tri3->setShape(GL_TRIANGLES);
    //addChild(tri3);
    
    // Sample Texture
    std::string filename("headphone.png");
    std::shared_ptr<Texture2D> tex = std::make_shared<Texture2D>(filename);
    
    Vertex vert11 = Vertex { Vec2 { -0.75f, 0.75f } } ;
    Vertex vert12 = Vertex { Vec2 { -0.75f, -0.75f } } ;
    Vertex vert13 = Vertex { Vec2 { 0.75f, 0.75f } } ;
    Vertex vert14 = Vertex { Vec2 { 0.75f, -0.75f } };
    std::vector<Vertex> vertex4 = { vert11, vert12, vert13, vert14 };
    tex->setVertex(vertex4);
    addChild(tex);
    
    return true;
}
