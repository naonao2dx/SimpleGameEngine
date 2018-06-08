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
#include "SGGeometry.hpp"
#include "SGColor.hpp"
#include "SGVertex.h"
#include "SGBlendFunc.hpp"

namespace SimpleGameEngine {
    class ShaderProgram
    {
    public:
        void use();
        virtual void draw();
        void setVertex(const std::vector<Vertex> vertex);
        void setShape(GLenum shape);
        void setBlendFunc(BlendFunc blendFunc);
    protected:
        ShaderProgram();
        virtual ~ShaderProgram();
        void createShader(const GLchar* vertShaderSource, const GLchar* fragShaderSource);
        GLuint compileShader(GLuint shaderType, const GLchar *source);
        void vertexToArray(std::vector<Vertex> vertex, Vertex vertexAarray[]);
        void vertexToArray2D(std::vector<Vertex> vertex, GLfloat position[], GLubyte color[] = nullptr, GLfloat uv[] = nullptr);
        void vertexToArray3D(std::vector<Vertex> vertex, GLfloat position[], GLubyte color[] = nullptr, GLfloat uv[] = nullptr);
        void vertexToPosition(std::vector<Vertex> vertex, GLfloat position[]);
        void vertexToPosition3D(std::vector<Vertex> vertex, GLfloat position[]);
        void vertexToPositionAndColor(std::vector<Vertex> vertex, GLfloat position[], GLubyte color[]);
        void vertexToPositionAndColor3D(std::vector<Vertex> vertex, GLfloat position[], GLubyte color[]);
        GLuint _shader;
        std::vector<Vertex> _vertex;
        GLenum _shape;
        BlendFunc _blendFunc;
    };
}

#endif /* SGShaderProgram_hpp */
