//
//  HelloScene.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/17.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "HelloScene.hpp"
#include "SGDirector.hpp"
#include "SGBaseScene.hpp"
#include "SGConsole.hpp"
#include "SGPrimitives.hpp"
#include "SGShaderManager.hpp"
#include "SGSprite.hpp"
#include "SGSpriteMask.hpp"
#include "SGCube3D.hpp"
#include "SGCube3DTexture.hpp"
#include "SGLayer.hpp"
#include "SGPmdData.hpp"

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
    
    std::shared_ptr<Layer> layer2D = Layer::createLayer();
    addChild(layer2D);
    
    std::shared_ptr<Layer> layer3D = Layer::createLayer();
    addChild(layer3D);
    
//    // Depth buffer sample 1
//    std::shared_ptr<Primitives> depth1 = Primitives::createWithPositionAndColor3DShader(GL_TRIANGLES);
//
//    Vertex depth1vert1 = Vertex { Vec3 {0.0f, 0.5f, -0.5f} };
//    Vertex depth1vert2 = Vertex { Vec3 {-0.5f, 0.0f, -0.5f} };
//    Vertex depth1vert3 = Vertex { Vec3 {0.5, 0.0f, -0.5f} };
//    std::vector<Vertex> depth1vertex = { depth1vert1, depth1vert2, depth1vert3 };
//    depth1->setNormalizedVertex(depth1vertex);
//
//    Color4F depthColor1 = { 1.0f, 1.0f, 0.0f, 1.0f };
//    depth1->setColor(depthColor1);
//    addChild(depth1);
//
//
//    // Depth buffer sample 2
//    std::shared_ptr<Primitives> depth2 = Primitives::createWithPositionAndColor3DShader(GL_TRIANGLE_STRIP);
//
//    Vertex depth2vert1 = Vertex { Vec3 {-0.4f, 0.1f, 0.5f} };
//    Vertex depth2vert2 = Vertex { Vec3 {-0.4f, -0.5, 0.5f} };
//    Vertex depth2vert3 = Vertex { Vec3 {0.4f, 0.1f, 0.5f} };
//    Vertex depth2vert4 = Vertex { Vec3 {0.4f, -0.5f, 0.5f} };
//    std::vector<Vertex> depth2vertex = { depth2vert1, depth2vert2, depth2vert3, depth2vert4 };
//    depth2->setNormalizedVertex(depth2vertex);
//
//    Color4F depth2color2 = { 0.0f, 1.0f, 1.0f, 1.0f };
//    depth2->setColor(depth2color2);
//    addChild(depth2);
//
//
//    // Sample Primitives 1
//    std::shared_ptr<Primitives> tri1 = Primitives::create(GL_TRIANGLE_STRIP);
//
//    Vertex tri1vert1 = Vertex { Vec2 {20, 50} };
//    Vertex tri1vert2 = Vertex { Vec2 {20, 100} };
//    Vertex tri1vert3 = Vertex { Vec2 {60, 50} };
//    Vertex tri1vert4 = Vertex { Vec2 {60, 100} };
//    std::vector<Vertex> tri1vertex = { tri1vert1, tri1vert2, tri1vert3, tri1vert4 };
//    tri1->setVertex(tri1vertex);
//
//    Color4F tri1color = { 1.0f, 1.0f, 0.0f, 1.0f };
//    tri1->setColor(tri1color);
//
//    addChild(tri1);
//
//    // Sample Primitives 2
//    std::shared_ptr<Primitives> tri2 = Primitives::create(GL_LINE_LOOP);
//
//    Vertex tri2vert1 = Vertex { Vec2 {-0.6f, -0.3f} };
//    Vertex tri2vert2 = Vertex { Vec2 {-0.8f, -0.7f} };
//    Vertex tri2vert3 = Vertex { Vec2 {-0.4f, -0.7f} };
//    std::vector<Vertex> tri2vertex = { tri2vert1, tri2vert2, tri2vert3 };
//    tri2->setNormalizedVertex(tri2vertex);
//    tri2->setLineWidth(5.0f);
//
//    Color4F tri2color2 = { 0.0f, 1.0f, 1.0f, 1.0f };
//    tri2->setColor(tri2color2);
//
//    addChild(tri2);
//
//    // Sample Primitives 3
//    std::shared_ptr<Primitives> tri3 = Primitives::createWithVertexColorShader(GL_TRIANGLES);
//
//    Vertex tri3vert1 = Vertex { Vec2 {0.0f, 0.25f}, Color4B { 255, 0, 0, 128 } };
//    Vertex tri3vert2 = Vertex { Vec2 {-0.5, -0.25f}, Color4B { 0, 255, 0, 128 } };
//    Vertex tri3vert3 = Vertex { Vec2 {0.5f, -0.25f}, Color4B { 0, 0, 255, 128 } };
//    std::vector<Vertex> tri3vertex = { tri3vert1, tri3vert2, tri3vert3 };
//    tri3->setNormalizedVertex(tri3vertex);
//    tri3->setBlendFunc(BlendFunc::DISABLE);
//    addChild(tri3);
//    
    // Sample Texture
    std::string tex1filename("headphone.png");
    std::shared_ptr<Sprite> tex1 = Sprite::create(tex1filename);
    tex1->setNormalizedPosition(0.3f, 0.0f);
    tex1->setContentSize(200, 200);
    //tex1->setBlendFunc(BlendFunc::ALPHA_PREMULTIPLIED);
    layer2D->addChild(tex1);

    // Sample Texture2
    std::string tex2filename("headphone2.png");
    std::shared_ptr<Sprite> tex2 = Sprite::create(tex2filename);
    tex2->setNormalizedPosition(0.3f, 0.0f);
    tex2->setContentSize(90, 90);
    layer2D->addChild(tex2, 0);
//
//    // Sample Blend Texture
//    std::string tex3filename1("azarashi.png");
//    std::string tex3filename2("blend.png");
//    std::shared_ptr<SpriteMask> tex3 = SpriteMask::create(tex3filename1, tex3filename2);
//    tex3->setPosition(225, 225);
//    tex3->setContentSize(90, 90);
//    addChild(tex3);
//
//
//
//    std::string atlasname("atlas.json");
//    std::string filename0("billiard.png");
//    std::shared_ptr<Sprite> atlas = Sprite::createWithTextureAtlas(atlasname, filename0);
//    atlas->setScale(0.4f, 0.4f);
//    atlas->setNormalizedPosition(0.3f, 0.0f);
//    atlas->setRotate(45.0f);
//    atlas->setBlendFunc(BlendFunc::ALPHA_PREMULTIPLIED);
//    addChild(atlas);

    
//    std::shared_ptr<Cube3D> cube = Cube3D::createWithColor(Color4F::BLUE);
//    addChild(cube);
//    std::string cubeTextureFilename("headphone2.png");
//    std::shared_ptr<Cube3DTexture> cubeTexture = Cube3DTexture::create(cubeTextureFilename);
//    layer3D->addChild(cubeTexture);
    
    _rotate = 0;
    
    _camera->setPosition(Vec3 {0.0f, 0.0f, -15.0f});
    
    std::string pmdfile("pmd-sample.pmd");
    pmd = PmdData::create(pmdfile);
    layer3D->addChild(pmd);
    
    return true;
}

void HelloScene::update()
{
    Mat4 world = Mat4::rotate(Vec3::createNormalized(0, 1, 0), _rotate);
    _camera->setWorld(world);
    _rotate += 1;
    
    if (_alpha > 0) {
        _alpha -= 0.005;
    } else {
        _alpha = 1.0;
    }
    pmd->setAlpha(_alpha);
}
