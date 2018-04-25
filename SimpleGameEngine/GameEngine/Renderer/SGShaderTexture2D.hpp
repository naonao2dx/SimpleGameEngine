//
//  SGShaderTexture2D.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/25.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGShaderTexture2D_hpp
#define SGShaderTexture2D_hpp

#include "SGShaderProgram.hpp"
#include <string>

namespace SimpleGameEngine {
    class ShaderTexture2D : public ShaderProgram
    {
    public:
        ShaderTexture2D(const GLchar* vertShaderSource, const GLchar* fragShaderSource);
        virtual void setTextureFilename(std::string& filename) override;
        virtual void draw() override;
    private:
        bool init();
        void createTexture();
        GLint _attrPos;
        GLint _attrUV;
        GLint _unifTexture;
        GLuint _textureID;
    };
}

#endif /* SGShaderTexture2D_hpp */
