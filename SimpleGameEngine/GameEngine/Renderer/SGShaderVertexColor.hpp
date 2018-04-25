//
//  SGShaderVertexColor.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/25.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGShaderVertexColor_hpp
#define SGShaderVertexColor_hpp

#include "SGShaderProgram.hpp"

namespace SimpleGameEngine {
    class ShaderVertexColor : public ShaderProgram
    {
    public:
        ShaderVertexColor(const GLchar* vertShaderSource, const GLchar* fragShaderSource);
        virtual void draw() override;
    private:
        bool init();
        GLint _attrPos;
        GLint _attrColor;
        std::vector<Color4F> vertexColor;
    };
}

#endif /* SGShaderVertexColor_hpp */
