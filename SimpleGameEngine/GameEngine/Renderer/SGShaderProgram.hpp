//
//  SGShaderProgram.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/18.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGShaderProgram_hpp
#define SGShaderProgram_hpp

#include <memory>
#include <vector>
#include <OpenGLES/ES2/gl.h>
#include "../Util/SGGeometry.hpp"
#include "../Util/SGColor.hpp"

namespace SimpleGameEngine {
    class ShaderProgram
    {
    public:
        void use();
        virtual void draw();
        void setPosition(std::vector<std::shared_ptr<Vec2>> position);
        void setColor(Color4F color);
        void setShape(GLenum shape);
        void setLineWidth(GLfloat lineWidth);
    protected:
        ShaderProgram(){};
        void createShader(const GLchar* vertShaderSource, const GLchar* fragShaderSource);
        GLuint compileShader(GLuint shaderType, const GLchar *source);
        GLuint _shader;
        std::vector<std::shared_ptr<Vec2>> _position;
        Color4F _color;
        GLenum _shape;
        GLfloat _lineWidth;
    };
}

#endif /* SGShaderProgram_hpp */
