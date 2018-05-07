//
//  Texture2D.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/07.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef Texture2D_hpp
#define Texture2D_hpp

#include <OpenGLES/ES2/gl.h>
#include <memory>
#include <vector>
#include "SGVertex.h"

namespace SimpleGameEngine {
    class RawImage;
    class Texture2D
    {
    public:
        static std::shared_ptr<Texture2D> create(std::string& filename);
        static std::shared_ptr<Texture2D> createWithCustomMipmap(std::vector<std::string> filenames);
        inline GLuint getTextureID() const { return _textureID; };
        inline int getWidth() const { return _width; };
        inline int getHeight() const { return _height; };
        inline std::vector<Vertex> getVertexUV() const { return _vertexUV; };
    private:
        Texture2D();
        void setupTexture(std::shared_ptr<RawImage> rawImage);
        void setupTextureWithCustomMipmap(std::vector<std::shared_ptr<RawImage>> rawImages);
        void createTexture();
        
        std::shared_ptr<RawImage> _rawImage;
        std::vector<std::shared_ptr<RawImage>> _rawImages;
        GLuint _textureID;
        GLuint _magFilter;
        GLuint _minFilter;
        bool _useGenerateMipmap;
        std::vector<Vertex> _vertexUV;
        int _width;
        int _height;
    };
}

#endif /* Texture2D_hpp */
