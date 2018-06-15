//
//  SGGeometry.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/17.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGGeometry_hpp
#define SGGeometry_hpp

#include <OpenGLES/ES2/gl.h>

namespace SimpleGameEngine {
    struct Vec2
    {
        Vec2();
        Vec2(float _x, float _y);
        GLfloat x;
        GLfloat y;
        
        static const Vec2 ZERO;
        static const Vec2 CENTER;
    };
    
    struct Vec3
    {
        Vec3();
        Vec3(GLfloat _x, GLfloat _y, GLfloat _z);
        GLfloat x;
        GLfloat y;
        GLfloat z;
        
        static Vec3 create(GLfloat _x, GLfloat _y, GLfloat _z);
        static GLfloat length(const Vec3 v);
        static Vec3 normalized(const Vec3 v);
        static Vec3 createNormalized(const GLfloat x, const GLfloat y, const GLfloat z);
        static Vec3 cross(const Vec3 v0, const Vec3 v1);
        static GLfloat dot(const Vec3 v0, const Vec3 v1);
    };
    
    struct Vec4
    {
        Vec4();
        Vec4(GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _w);
        GLfloat x;
        GLfloat y;
        GLfloat z;
        GLfloat w;
    };
    
    struct Mat4
    {
        GLfloat m[4][4];
        
        Mat4(){};
        static Mat4 identity();
        static Mat4 translate(const GLfloat x, const GLfloat y, const GLfloat z);
        static Mat4 scale(const GLfloat x, const GLfloat y, const GLfloat z);
        static Mat4 rotate(const Vec3 axis, const GLfloat rotate);
        static Mat4 multiply(const Mat4 a, const Mat4 b);
        static Mat4 lookAt(const Vec3 position, const Vec3 look, const Vec3 up);
        static Mat4 perspective(const GLfloat near, const GLfloat far, const GLfloat fovYDegree, const GLfloat aspect);
    };
    
    struct Size
    {
        int width;
        int height;
        
        void setSize(int _width, int _height) { width = _width; height = _height; };
    };
}

#endif /* SGGeometry_hpp */
