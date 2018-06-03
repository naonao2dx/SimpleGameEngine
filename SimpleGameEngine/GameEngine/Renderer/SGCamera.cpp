//
//  SGCamera.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/24.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGCamera.hpp"
#include "SGDirector.hpp"
#include "SGConsole.hpp"

using namespace SimpleGameEngine;

std::shared_ptr<Camera> Camera::create()
{
    // Default value
    Vec3 position { 0, 0, -10 };
    Vec3 look { 0, 0, 0 };
    Vec3 up { 0, 1, 0 };
    GLfloat projectionNear = 1.0f;
    GLfloat projectionFar = 100.0f;
    GLfloat projectionFovY = 45.0f;
    
    std::shared_ptr<Camera> camera {Camera::create(position, look, up, projectionNear, projectionFar, projectionFovY)};
    
    return camera;
}

std::shared_ptr<Camera> Camera::create(Vec3 position, Vec3 look, Vec3 up, GLfloat projectionNear, GLfloat projectionFar, GLfloat projectionFovY)
{
    std::shared_ptr<Camera> camera(new (std::nothrow) Camera(position, look, up, projectionNear, projectionFar, projectionFovY));
    return camera;
}

Camera::Camera(Vec3 position, Vec3 look, Vec3 up, GLfloat projectionNear, GLfloat projectionFar, GLfloat projectionFovY)
: _position(position)
, _look(look)
, _up(up)
, _projectionNear(projectionNear)
, _projectionFar(projectionFar)
, _projectionFovY(projectionFovY)
{
    auto director = Director::getInstance();
    Size designResolutionSize = director->getDesignResolutionSize();
    _projectionAspect = (GLfloat) designResolutionSize.width / (GLfloat) designResolutionSize.height;
    _lookAt = Mat4::lookAt(position, look, up);
    _projection = Mat4::perspective(_projectionNear, _projectionFar, _projectionFovY, _projectionAspect);
    _world = Mat4::identity();
    setWlp();
    Console::logDebug("here");
}

void Camera::setPosition(SimpleGameEngine::Vec3 position) {
    _position = position;
    _lookAt = Mat4::lookAt(_position, _look, _up);
    setWlp();
}

void Camera::setLook(SimpleGameEngine::Vec3 look)
{
    _look = look;
    _lookAt = Mat4::lookAt(_position, _look, _up);
    setWlp();
}

void Camera::setUp(SimpleGameEngine::Vec3 up)
{
    _up = up;
    _lookAt = Mat4::lookAt(_position, _look, _up);
    setWlp();
}

void Camera::setProjectionNear(GLfloat projectionNear)
{
    _projectionNear = projectionNear;
    _projection = Mat4::perspective(_projectionNear, _projectionFar, _projectionFovY, _projectionAspect);
    setWlp();
}

void Camera::setProjectionFar(GLfloat projectionFar)
{
    _projectionFar = projectionFar;
    _projection = Mat4::perspective(_projectionNear, _projectionFar, _projectionFovY, _projectionAspect);
    setWlp();
}

void Camera::setProjectionFovY(GLfloat projectionFovY)
{
    _projectionFovY = projectionFovY;
    _projection = Mat4::perspective(_projectionNear, _projectionFar, _projectionFovY, _projectionAspect);
    setWlp();
}

void Camera::setWorld(SimpleGameEngine::Mat4 world)
{
    _world = world;
    setWlp();
}

void Camera::setWlp()
{
    _wlp = Mat4::identity();
    _wlp = Mat4::multiply(_projection, _lookAt);
    _wlp = Mat4::multiply(_wlp, _world);
}
