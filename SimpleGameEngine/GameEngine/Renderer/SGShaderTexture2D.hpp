//
//  SGShaderTexture2D.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/25.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGShaderTexture2D_hpp
#define SGShaderTexture2D_hpp

#include "SGShaderProgram.hpp"
#include <string>

namespace SimpleGameEngine {
    class Texture2D;
    class ShaderTexture2D : public ShaderProgram
    {
    public:
        ShaderTexture2D(){};
        ShaderTexture2D(const GLchar* vertShaderSource, const GLchar* fragShaderSource);
        ~ShaderTexture2D();
        GLuint setTexture(std::shared_ptr<Texture2D> texture2d, bool useGenerateMipmap);
        GLuint setTextureWithCustomMimap(std::vector<std::shared_ptr<Texture2D>> texture2ds);
        void bindTexture(GLuint textureID);
        void setVertexUV(const std::vector<Vertex> vertexUV);
        void setFilter(GLuint magFilter, GLuint minFilter);
        virtual void draw() override;
        
    protected:
        virtual bool init();
        GLuint createTexture();
        GLint _attrPos;
        GLint _attrUV;
        GLint _unifTexture;
        std::vector<GLuint> _textureID;
        std::vector<Vertex> _vertexUV;
        GLuint _magFilter;
        GLuint _minFilter;
    };
}

#endif /* SGShaderTexture2D_hpp */
