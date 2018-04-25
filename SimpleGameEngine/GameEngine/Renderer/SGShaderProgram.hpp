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
#include "../Base/SGVertex.h"

namespace SimpleGameEngine {
    class ShaderProgram
    {
    public:
        void use();
        virtual void draw();
        void setVertex(const std::vector<Vertex> vertex);
        void setColor(const Color4F color);
        void setShape(GLenum shape);
        void setLineWidth(GLfloat lineWidth);
        virtual void setTextureFilename(std::string& filename){};
    protected:
        ShaderProgram(){};
        void createShader(const GLchar* vertShaderSource, const GLchar* fragShaderSource);
        GLuint compileShader(GLuint shaderType, const GLchar *source);
        void vertexToPosition(GLfloat position[]);
        void vertexToPositionAndColor(GLfloat position[], GLubyte color[]);
        GLuint _shader;
        std::vector<Vertex> _vertex;
        Color4F _color;
        GLenum _shape;
        GLfloat _lineWidth;
    };
}

#endif /* SGShaderProgram_hpp */
