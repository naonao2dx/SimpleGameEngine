//
//  SGSpriteBlend.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/01.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGSpriteBlend_hpp
#define SGSpriteBlend_hpp

#include "../Base/SGNode.hpp"

namespace SimpleGameEngine {
    class RawImage;
    class SpriteBlend : public Node
    {
    public:
        static std::shared_ptr<SpriteBlend> create(std::string& textureFilename, std::string& blendTextureFilename);
        void setVertexUV(const std::vector<Vertex> vertexUV);
        virtual ~SpriteBlend(){};
    protected:
        SpriteBlend(){};
        SpriteBlend(std::shared_ptr<RawImage> rawImage, std::shared_ptr<RawImage> blendRawImage);
    private:
        bool init();
        std::vector<Vertex> _vertexUV;
        void setShaderSpriteBlend();
        std::shared_ptr<RawImage> _rawImage;
        std::shared_ptr<RawImage> _blendRawImage;
        GLuint _textureID;
        GLuint _blendTextureID;
        void draw();
    };
}

#endif /* SGSpriteBlend_hpp */
