//
//  SGGLView.h
//  SimpleGameEngine
//
//  Created by Nao on 2018/03/21.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGGLView_h
#define SGGLView_h

#include <memory>
#include <OpenGLES/ES2/gl.h>
#include "../util/SGGeometry.hpp"

namespace SimpleGameEngine {
    class GLView
    {
    public:
        static std::shared_ptr<GLView> createWithEAGLView(void* eaglView);
        
        GLuint bufferColor;
        GLuint bufferFrame;
        
        void* getEAGLView() const { return _eaglView; }
        
    protected:
        void* _eaglView;
        bool initWithEAGLView(void* eaglView);
        
        Size _screenSize;
        Size _designResolutionSize;
        
    };
}

#endif /* SGGLView_h */

