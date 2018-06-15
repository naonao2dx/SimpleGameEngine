//
//  SGShaderModel3D.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/06/15.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGShaderModel3D_hpp
#define SGShaderModel3D_hpp

#include "SGShaderBase3D.hpp"
#include "SGPmdData.hpp"

namespace SimpleGameEngine {
    class ShaderModel3D : public ShaderBase3D
    {
    public:
        ShaderModel3D(const GLchar* vertShaderSource, const GLchar* fragShaderSource);
        inline void setWlp(Mat4 wlp) { _wlp = wlp; };
        virtual void draw() override;
        inline void setModel(PmdData* model) { _model = model; };
    protected:
        bool init();
        GLint _attrPos;
        GLint _attrUV;
        GLint _unifColor;
        GLint _unifTexture;
        GLint _unifWlp;
        Mat4 _wlp;
        PmdData* _model;
    };
}

#endif /* SGShaderModel3D_hpp */
