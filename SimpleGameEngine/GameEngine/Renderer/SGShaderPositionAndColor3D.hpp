//
//  SGShaderPositionAndColor3D.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/22.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGShaderPositionAndColor3D_hpp
#define SGShaderPositionAndColor3D_hpp

#include "SGShaderProgram.hpp"
#include "SGGeometry.hpp"
#include "SGColor.hpp"

namespace SimpleGameEngine {
    class ShaderPositionAndColor3D : public ShaderProgram
    {
    public:
        ShaderPositionAndColor3D(const GLchar* vertShaderSource, const GLchar* fragShaderSource);
        
        virtual void draw() override;
        void setColor(const Color4F color);
        void setLineWidth(GLfloat lineWidth);
    private:
        bool init();
        GLint _attrPos;
        GLint _unifColor;
        Color4F _color;
        GLfloat _lineWidth;
    };
}

#endif /* SGShaderPositionAndColor3D_hpp */
