//
//  SGColor.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/18.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGColor_hpp
#define SGColor_hpp

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
        static const Color4F RED;
        static const Color4F GREEN;
        static const Color4F BLUE;
    };
    
    struct Color4B
    {
        Color4B();
        Color4B(GLubyte _r, GLubyte _g, GLubyte _b, GLubyte _a);
        GLubyte r;
        GLubyte g;
        GLubyte b;
        GLubyte a;
        
        static const Color4B WHITE;
        static const Color4B BLACK;
        static const Color4B RED;
        static const Color4B GREEN;
        static const Color4B BLUE;
    };
}

#endif /* SGColor_hpp */
