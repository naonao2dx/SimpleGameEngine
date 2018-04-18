//
//  SGRenderer.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/12.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGRenderer_hpp
#define SGRenderer_hpp

#include <stdio.h>
#include "SGGeometry.hpp"

namespace SimpleGameEngine {
    class Renderer
    {
    public:
        Renderer();
        ~Renderer(){};
        
        void clear();
        void initGLView();
    private:
        RGBA _clearColor;
        
    };
}

#endif /* SGRenderer_hpp */
