//
//  SGShaderPositionAndColor.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/24.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGShaderPositionAndColor_hpp
#define SGShaderPositionAndColor_hpp

#include "SGShaderProgram.hpp"

namespace SimpleGameEngine {
    class ShaderPositionAndColor : public ShaderProgram
    {
    public:
        ShaderPositionAndColor(const GLchar* vertShaderSource, const GLchar* fragShaderSource);
    };
}

#endif /* SGShaderPositionAndColor_hpp */
