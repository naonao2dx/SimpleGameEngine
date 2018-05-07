//
//  SGSprite.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/26.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGSprite_hpp
#define SGSprite_hpp

#include "../Base/SGNode.hpp"

namespace SimpleGameEngine {
    class RawImage;
    class Sprite : public Node
    {
    public:
        static std::shared_ptr<Sprite> create(std::string& filename, bool useMipmap = false, GLuint magFilter = GL_NEAREST, GLuint minFilter = GL_NEAREST);
        static std::shared_ptr<Sprite> createWithCustomMipmap(std::vector<std::string> filenames, GLuint magFilter = GL_NEAREST, GLuint minFilter = GL_NEAREST_MIPMAP_NEAREST);
        void setShaderTexture();
        void setShaderTextureWithCustomMipmap();
        void setTextureFilename(std::string& filename);
        void setVertexUV(const std::vector<Vertex> vertexUV);
    protected:
        Sprite(){};
        Sprite(std::shared_ptr<RawImage> texture2d, bool useMipmap = false, GLuint magFilter = GL_NEAREST, GLuint minFilter = GL_NEAREST);
        Sprite(std::vector<std::shared_ptr<RawImage>> texture2ds, GLuint magFilter = GL_NEAREST, GLuint minFilter = GL_NEAREST_MIPMAP_NEAREST);
        bool initWithTexture();
        bool initWithTextureCustomMipmap();
        virtual bool init() override;
        virtual void draw() override;
    private:
        std::shared_ptr<RawImage> _rawImage;
        std::vector<std::shared_ptr<RawImage>> _rawImages;
        std::vector<Vertex> _vertexUV;
        GLuint _textureID;
        GLuint _magFilter;
        GLuint _minFilter;
        bool _useMipmap;
    };
}

#endif /* SGSprite_hpp */
