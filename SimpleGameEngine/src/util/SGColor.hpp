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
        GLfloat r;
        GLfloat g;
        GLfloat b;
        GLfloat a;
    };
}

#endif /* SGColor_hpp */
