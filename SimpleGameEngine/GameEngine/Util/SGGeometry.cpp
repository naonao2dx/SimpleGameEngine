//
//  SGGeometry.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/18.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGGeometry.hpp"
#include <math.h>
#include <cstring>

#define degree2radian(degree) ((degree * M_PI) / 180.0)

using namespace SimpleGameEngine;

Vec2::Vec2()
: x(0.5f)
, y(0.5f)
{}

Vec2::Vec2(float _x, float _y)
: x (_x)
, y (_y)
{}

const Vec2 Vec2::ZERO(0.0f, 0.0f);
const Vec2 Vec2::CENTER(0.5f, 0.5f);

Vec3::Vec3()
: x(0.5f)
, y(0.5f)
, z(0.5f)
{}

Vec3::Vec3(float _x, float _y, float _z)
: x(_x)
, y(_y)
, z(_z)
{}

Vec3 Vec3::create(GLfloat _x, GLfloat _y, GLfloat _z)
{
    Vec3 v {_x, _y, _z};
    return v;
}

GLfloat Vec3::length(const SimpleGameEngine::Vec3 v)
{
    return static_cast<GLfloat>(sqrt((static_cast<double>(v.x) * static_cast<double>(v.x))
                                     + (static_cast<double>(v.y) * static_cast<double>(v.y))
                                     + (static_cast<double>(v.z) * static_cast<double>(v.z))));
}

Vec3 Vec3::normalized(const SimpleGameEngine::Vec3 v)
{
    const GLfloat len = length(v);
    return Vec3(v.x / len, v.y / len, v.z / len);
}

Vec3 Vec3::createNormalized(const GLfloat x, const GLfloat y, const GLfloat z)
{
    return normalized(create(x, y, z));
}

Vec3 Vec3::cross(const SimpleGameEngine::Vec3 v0, const SimpleGameEngine::Vec3 v1)
{
    return Vec3::create(
                        (v0.y * v1.z) - (v0.z * v1.y),
                        (v0.z * v1.x) - (v0.x * v1.z),
                        (v0.x * v1.y) - (v0.y * v1.x)
                        );
}

GLfloat Vec3::dot(const SimpleGameEngine::Vec3 v0, const SimpleGameEngine::Vec3 v1)
{
    return (v0.x * v1.x) + (v0.y * v1.y) + (v0.z * v1.z);
}

Vec4::Vec4()
: x(0.5f)
, y(0.5f)
, z(0.5f)
, w(0.5f)
{}

Vec4::Vec4(float _x, float _y, float _z, float _w)
: x(_x)
, y(_y)
, z(_z)
, w(_w)
{}

Mat4 Mat4::identity()
{
    Mat4 result;
    
    int column = 0;
    int row = 0;
    
    for (column = 0; column < 4; ++column) {
        for (row = 0; row < 4; ++row) {
            if (column == row) {
                result.m[column][row] = 1.0f;
            } else {
                result.m[column][row] = 0.0f;
            }
        }
    }
    return result;
}

Mat4 Mat4::translate(const GLfloat x, const GLfloat y, const GLfloat z)
{
    Mat4 result = Mat4::identity();
    
    result.m[3][0] = x;
    result.m[3][1] = y;
    result.m[3][2] = z;
    
    return result;
}

Mat4 Mat4::scale(const GLfloat x, const GLfloat y, const GLfloat z)
{
    Mat4 result = Mat4::identity();
    
    result.m[0][0] = x;
    result.m[1][1] = y;
    result.m[2][2] = z;
    
    return result;
}

Mat4 Mat4::rotate(const Vec3 axis, const GLfloat rotate)
{
    Mat4 result = Mat4::identity();
    
    const GLfloat x = axis.x;
    const GLfloat y = axis.y;
    const GLfloat z = axis.z;
    
    const GLfloat c = cos(degree2radian(rotate));
    const GLfloat s = sin(degree2radian(rotate));
    {
        result.m[0][0] = (x * x) * (1.0f - c) + c;
        result.m[0][1] = (x * y) * (1.0f - c) - z * s;
        result.m[0][2] = (x * z) * (1.0f - c) + y * s;
        result.m[0][3] = 0;
    }
    {
        result.m[1][0] = (y * x) * (1.0f - c) + z * s;
        result.m[1][1] = (y * y) * (1.0f - c) + c;
        result.m[1][2] = (y * z) * (1.0f - c) - x * s;
        result.m[1][3] = 0;
    }
    {
        result.m[2][0] = (z * x) * (1.0f - c) - y * s;
        result.m[2][1] = (z * y) * (1.0f - c) + x * s;
        result.m[2][2] = (z * z) * (1.0f - c) + c;
        result.m[2][3] = 0;
    }
    {
        result.m[3][0] = 0;
        result.m[3][1] = 0;
        result.m[3][2] = 0;
        result.m[3][3] = 1;
    }
    
    return result;
}

Mat4 Mat4::multiply(const Mat4 a, const Mat4 b)
{
    Mat4 result = Mat4::identity();
    
    int i = 0;
    for (i = 0; i < 4; ++i) {
        result.m[i][0] = a.m[0][0] * b.m[i][0] + a.m[1][0] * b.m[i][1] + a.m[2][0] * b.m[i][2] + a.m[3][0] * b.m[i][3];
        result.m[i][1] = a.m[0][1] * b.m[i][0] + a.m[1][1] * b.m[i][1] + a.m[2][1] * b.m[i][2] + a.m[3][1] * b.m[i][3];
        result.m[i][2] = a.m[0][2] * b.m[i][0] + a.m[1][2] * b.m[i][1] + a.m[2][2] * b.m[i][2] + a.m[3][2] * b.m[i][3];
        result.m[i][3] = a.m[0][3] * b.m[i][0] + a.m[1][3] * b.m[i][1] + a.m[2][3] * b.m[i][2] + a.m[3][3] * b.m[i][3];
    }
    
    return result;
}

Mat4 Mat4::lookAt(const SimpleGameEngine::Vec3 eye, const SimpleGameEngine::Vec3 look, const SimpleGameEngine::Vec3 up)
{
    Mat4 result;
    
    Vec3 f = Vec3::normalized(Vec3::create(look.x - eye.x, look.y - eye.y, look.z - eye.z));
    Vec3 u = Vec3::normalized(up);
    Vec3 s = Vec3::normalized(Vec3::cross(f, u));
    u = Vec3::cross(s, f);
    
    result.m[0][0] = s.x;
    result.m[1][0] = s.y;
    result.m[2][0] = s.z;
    result.m[0][1] = u.x;
    result.m[1][1] = u.y;
    result.m[2][1] = u.z;
    result.m[0][2] = -f.x;
    result.m[1][2] = -f.y;
    result.m[2][2] = -f.z;
    result.m[3][0] = -Vec3::dot(s, eye);
    result.m[3][1] = -Vec3::dot(u, eye);
    result.m[3][2] = Vec3::dot(f, eye);
    result.m[0][3] = 0;
    result.m[1][3] = 0;
    result.m[2][3] = 0;
    result.m[3][3] = 1;
    
    return result;
}

Mat4 Mat4::perspective(const GLfloat near, const GLfloat far, const GLfloat fovYDegree, const GLfloat aspect)
{
    Mat4 result;
    
    std::memset(result.m, 0x00, sizeof(Mat4));
    
    const GLfloat f = (GLfloat) (1.0 / (tan(degree2radian(fovYDegree)) / 2.0)); // 1/tan(x) == cot(x)
    
    result.m[0][0] = f / aspect;
    result.m[1][1] = f;
    result.m[2][2] = (far + near) / (near - far);
    result.m[2][3] = -1;
    result.m[3][2] = (2.0f * far * near) / (near - far);
    
    return result;
}

