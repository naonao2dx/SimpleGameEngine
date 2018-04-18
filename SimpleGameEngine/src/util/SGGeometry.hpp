//
//  SGGeometry.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/17.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGGeometry_hpp
#define SGGeometry_hpp

#include <stdio.h>
#include <OpenGLES/ES2/gl.h>

namespace SimpleGameEngine {
    struct Vec2
    {
        GLfloat x;
        GLfloat y;
    };
    
    struct Size
    {
        int width;
        int height;
    };
}

#endif /* SGGeometry_hpp */
