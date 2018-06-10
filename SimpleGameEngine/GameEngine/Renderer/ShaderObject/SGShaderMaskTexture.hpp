//
//  SGShaderMaskTexture.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/01.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGShaderMaskTexture_hpp
#define SGShaderMaskTexture_hpp

#include <OpenGLES/ES2/gl.h>
#include <map>
#include "SGShaderTexture2D.hpp"

namespace SimpleGameEngine {
    class ShaderMaskTexture : public ShaderTexture2D
    {
    public:
        ShaderMaskTexture(){};
        ShaderMaskTexture(const GLchar* vertShaderSource, const GLchar* fragShaderSource);
        ~ShaderMaskTexture(){};
        void bindTexture(GLuint textureID, GLuint maskTextureID);
        virtual void draw() override;
    protected:
        virtual bool init() override;
        GLint _unifTexColor;
        GLint _unifTexMask;
    };
}

#endif /* SGShaderMaskTexture_hpp */
