//
//  SGShaderTexture3D.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/06/02.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGShaderTexture3D_hpp
#define SGShaderTexture3D_hpp

#include "SGShaderTexture2D.hpp"

namespace SimpleGameEngine {
    class ShaderTexture3D : public ShaderTexture2D
    {
    public:
        ShaderTexture3D(){};
        ShaderTexture3D(const GLchar* vertShaderSource, const GLchar* fragShaderSource);
        ~ShaderTexture3D(){};
        inline void setWlp(Mat4 wlp) { _wlp = wlp; };
    protected:
        virtual bool init() override;
        virtual void draw() override;
        Mat4 _wlp;
        GLint _unifWlp;
    };
}

#endif /* SGShaderTexture3D_hpp */
