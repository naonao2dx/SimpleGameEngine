//
//  SGShaderBlendTexture.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/01.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGShaderBlendTexture_hpp
#define SGShaderBlendTexture_hpp

#include <OpenGLES/ES2/gl.h>
#include <map>
#include "SGShaderTexture2D.hpp"

namespace SimpleGameEngine {
    class ShaderBlendTexture : public ShaderTexture2D
    {
    public:
        ShaderBlendTexture(){};
        ShaderBlendTexture(const GLchar* vertShaderSource, const GLchar* fragShaderSource);
        ~ShaderBlendTexture(){};
        void bindTexture(GLuint textureID, GLuint blendTextureID);
        virtual void draw() override;
    protected:
        virtual bool init() override;
        GLint _unifTexColor;
        GLint _unifTexMask;
    };
}



#endif /* SGShaderBlendTexture_hpp */
