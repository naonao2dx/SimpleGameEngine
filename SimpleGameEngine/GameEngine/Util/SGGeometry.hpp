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
        
        static const Vec2 CENTER;
    };
    
    struct Size
    {
        int width;
        int height;
        
        void setSize(int _width, int _height) { width = _width; height = _height; };
    };
}

#endif /* SGGeometry_hpp */
