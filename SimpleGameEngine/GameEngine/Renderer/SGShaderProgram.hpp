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
#include <OpenGLES/ES2/gl.h>

namespace SimpleGameEngine {
    class ShaderProgram
    {
    public:
        GLuint getShader();
        void use();
    protected:
        ShaderProgram(){};
        void createShader(const GLchar* vertShaderSource, const GLchar* fragShaderSource);
        GLuint compileShader(GLuint shaderType, const GLchar *source);
        GLuint _shader;
    };
}

#endif /* SGShaderProgram_hpp */
