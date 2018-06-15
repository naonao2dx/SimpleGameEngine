//
//  SGUtil.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/06/19.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGUtil_hpp
#define SGUtil_hpp

#include <OpenGLES/ES2/gl.h>
#include "SGRawData.hpp"

namespace SimpleGameEngine {
    class Util
    {
    public:
        static void sjisToUtf8(GLchar *str, const int array_length);
    };
}

#endif /* SGUtil_hpp */
