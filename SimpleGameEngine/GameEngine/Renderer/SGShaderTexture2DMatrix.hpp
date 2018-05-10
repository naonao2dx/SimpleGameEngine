//
//  SGShaderTexture2DMatrix.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/10.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGShaderTexture2DMatrix_hpp
#define SGShaderTexture2DMatrix_hpp

#include "SGShaderTexture2D.hpp"

namespace SimpleGameEngine {
    class ShaderTexture2DMatrix : public ShaderTexture2D
    {
    public:
        ShaderTexture2DMatrix(){};
        ShaderTexture2DMatrix(const GLchar* vertShaderSource, const GLchar* fragShaderSource);
        ~ShaderTexture2DMatrix(){};
        void virtual draw() override;
        void setMatrix(Mat4& matrix);
    protected:
        virtual bool init() override;
        GLuint _unifMatrix;
        Mat4 _matrix;
    };
}

#endif /* SGShaderTexture2DMatrix_hpp */
