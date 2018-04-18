//
//  SGColor.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/18.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGColor_hpp
#define SGColor_hpp

#include <stdio.h>
#include <OpenGLES/ES2/gl.h>

namespace SimpleGameEngine {
    struct Color4F
    {
        Color4F();
        Color4F(float _r, float _g, float _b, float _a);
        GLfloat r;
        GLfloat g;
        GLfloat b;
        GLfloat a;
        
        static const Color4F WHITE;
        static const Color4F BLACK;
    };
}

#endif /* SGColor_hpp */
