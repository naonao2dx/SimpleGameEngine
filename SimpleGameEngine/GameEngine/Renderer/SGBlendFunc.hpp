//
//  SGBlendFunc.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/15.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGBlendFunc_hpp
#define SGBlendFunc_hpp

#include <OpenGLES/ES2/gl.h>

namespace SimpleGameEngine {
    struct BlendFunc
    {
        GLenum src;
        GLenum dst;
        
        BlendFunc(GLenum _src, GLenum _dst);
        
        static const BlendFunc DISABLE;
        static const BlendFunc ALPHA_PREMULTIPLIED;
        
        bool operator==(const BlendFunc &a) const
        {
            return src == a.src && dst == a.dst;
        }
        
        bool operator!=(const BlendFunc &a) const
        {
            return src != a.src || dst != a.dst;
        }
    };
}

#endif /* SGBlendFunc_hpp */
