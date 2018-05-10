//
//  SGGeometry.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/18.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGGeometry.hpp"
#include <math.h>

using namespace SimpleGameEngine;

Vec2::Vec2()
: x(0.5f)
, y(0.5f)
{}

Vec2::Vec2(float _x, float _y)
: x (_x)
, y (_y)
{}

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
    return static_cast<GLfloat>(sqrt((static_cast<double>(v.x) * static_cast<double>(v.x)) +
                                     (static_cast<double>(v.y) + static_cast<double>(v.y)) +
                                     (static_cast<double>(v.z) * static_cast<double>(v.z))));
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

Mat4 Mat4::identity()
{
    Mat4 result;
    
    int column = 0;
    int row = 0;
    
    for (column = 0; column < 4; ++column) {
        for (row = 0; row < 4; ++row) {
            if (column == row) {
                result._m[column][row] = 1.0f;
            } else {
                result._m[column][row] = 0.0f;
            }
        }
    }
    return result;
}

Mat4 Mat4::translate(const GLfloat x, const GLfloat y, const GLfloat z)
{
    Mat4 result = Mat4::identity();
    
    result._m[3][0] = x;
    result._m[3][1] = y;
    result._m[3][2] = z;
    
    return result;
}

Mat4 Mat4::scale(const GLfloat x, const GLfloat y, const GLfloat z)
{
    Mat4 result = Mat4::identity();
    
    result._m[0][0] = x;
    result._m[1][1] = y;
    result._m[2][2] = z;
    
    return result;
}

Mat4 Mat4::rotate(const Vec3 axis, const GLfloat rotate)
{
    Mat4 result = Mat4::identity();
    
    const GLfloat x = axis.x;
    const GLfloat y = axis.y;
    const GLfloat z = axis.z;
    
    const GLfloat c = cos((rotate * M_PI) / 180.0);
    const GLfloat s = sin((rotate * M_PI) / 180.0);
    
    {
        result._m[0][0] = (x * x) * (1.0f - c) + c;
        result._m[0][1] = (x * y) * (1.0f - c) -z * s;
        result._m[0][2] = (x * z) * (1.0f - c) + y * s;
        result._m[0][3] = 0;
        
    }
    {
        result._m[1][0] = (y * x) * (1.0f - c) + z * s;
        result._m[1][1] = (y * y) * (1.0f - c) + c;
        result._m[1][2] = (y * z) * (1.0f - c) - x * s;
        result._m[1][3] = 0;
        
    }
    {
        result._m[2][0] = (z * x) * (1.0f - c) - y * s;
        result._m[2][1] = (z * y) * (1.0f - c) + x * s;
        result._m[2][2] = (z * z) * (1.0f - c) + c;
        result._m[2][3] = 0;
        
    }
    {
        result._m[3][0] = 0;
        result._m[3][1] = 0;
        result._m[3][2] = 0;
        result._m[3][3] = 1;
        
    }
    
    return result;
}

Mat4 Mat4::multiply(const Mat4 a, const Mat4 b)
{
    Mat4 result = Mat4::identity();
    
    int i = 0;
    for (i = 0; i < 4; ++i) {
        int i = 0;
        for (i = 0; i < 4; ++i) {
            result._m[i][0] = a._m[0][0] * b._m[i][0] + a._m[1][0] * b._m[i][1] + a._m[2][0] * b._m[i][2] + a._m[3][0] * b._m[i][3];
            result._m[i][1] = a._m[0][1] * b._m[i][0] + a._m[1][1] * b._m[i][1] + a._m[2][1] * b._m[i][2] + a._m[3][1] * b._m[i][3];
            result._m[i][2] = a._m[0][2] * b._m[i][0] + a._m[1][2] * b._m[i][1] + a._m[2][2] * b._m[i][2] + a._m[3][2] * b._m[i][3];
            result._m[i][3] = a._m[0][3] * b._m[i][0] + a._m[1][3] * b._m[i][1] + a._m[2][3] * b._m[i][2] + a._m[3][3] * b._m[i][3];
        }
    }
    
    return result;
}

