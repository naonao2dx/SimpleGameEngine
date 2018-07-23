//
//  SGShaderModel3DEdge.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/07/23.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGShaderModel3DEdge_hpp
#define SGShaderModel3DEdge_hpp

#include "SGShaderBase3D.hpp"
#include "SGPmdData.hpp"

namespace SimpleGameEngine {
    class ShaderModel3DEdge : public ShaderBase3D
    {
    public:
        ShaderModel3DEdge(const GLchar* vertShaderSource, const GLchar* fragShaderSource);
        inline void setWlp(Mat4 wlp) { _wlp = wlp; };
        virtual void draw() override;
    protected:
        bool init();
        GLint _attrPos;
        GLint _attrNormal;
        GLint _unifEdgesize;
        GLint _unifWlp;
        Mat4 _wlp;
    };
}
#endif /* SGShaderModel3DEdge_hpp */
