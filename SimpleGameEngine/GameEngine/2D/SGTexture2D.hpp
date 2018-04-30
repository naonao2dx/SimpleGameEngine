//
//  SGTexture2D.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/26.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGTexture2D_hpp
#define SGTexture2D_hpp

#include "../Base/SGNode.hpp"

namespace SimpleGameEngine {
    class Texture2D : public Node
    {
    public:
        Texture2D();
        Texture2D(std::string& filename, bool useMipMap, GLuint magFilter = GL_NEAREST, GLuint minFilter = GL_NEAREST);
        Texture2D(std::vector<std::string> filenames, GLuint magFilter = GL_NEAREST, GLuint minFilter = GL_NEAREST_MIPMAP_NEAREST);
        void setShaderTexture();
        void setShaderTextureWithMipmap();
        void setTextureFilename(std::string& filename);
        void setVertexUV(const std::vector<Vertex> vertexUV);
    protected:
        bool initWithTexture();
        bool initWithMipMap();
        virtual bool init() override;
        virtual void draw() override;
    private:
        std::string _filename;
        std::vector<std::string> _filenames;
        std::vector<Vertex> _vertexUV;
        GLuint _magFilter;
        GLuint _minFilter;
        bool _useMipMap;
    };
}

#endif /* SGTexture2D_hpp */
