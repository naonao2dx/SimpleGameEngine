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
#include "../Util/SGGeometry.hpp"
#include "../Util/SGColor.hpp"

namespace SimpleGameEngine {
    class ShaderPositionAndColor : public ShaderProgram
    {
    public:
        ShaderPositionAndColor(const GLchar* vertShaderSource, const GLchar* fragShaderSource);
        
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

#endif /* SGShaderPositionAndColor_hpp */
