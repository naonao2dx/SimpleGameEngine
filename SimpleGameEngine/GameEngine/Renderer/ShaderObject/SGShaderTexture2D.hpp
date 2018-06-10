//
//  SGShaderTexture2D.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/25.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGShaderTexture2D_hpp
#define SGShaderTexture2D_hpp

#include "SGShaderBase2D.hpp"
#include <string>

namespace SimpleGameEngine {
    class RawImage;
    class ShaderTexture2D : public ShaderBase2D
    {
    public:
        ShaderTexture2D(){};
        ShaderTexture2D(const GLchar* vertShaderSource, const GLchar* fragShaderSource);
        virtual ~ShaderTexture2D();
        void bindTexture(GLuint textureID);
        void setVertexUV(const std::vector<Vertex> vertexUV);
        void setFilter(GLuint magFilter, GLuint minFilter);
        virtual void draw() override;
        
    protected:
        virtual bool init();
        GLint _attrPos;
        GLint _attrUV;
        GLint _unifTexture;
        std::vector<Vertex> _vertexUV;
        GLuint _magFilter;
        GLuint _minFilter;
    };
}

#endif /* SGShaderTexture2D_hpp */
