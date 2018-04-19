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
        static std::shared_ptr<ShaderProgram> createWithByteArray(const GLchar* vertShaderSource, const GLchar* fragShaderSource);
        GLuint getShader();
        void use();
    private:
        static GLuint compileShader(GLuint shaderType, const GLchar *source);
        ShaderProgram(){};
        GLuint _shader;
    };
}

#endif /* SGShaderProgram_hpp */
