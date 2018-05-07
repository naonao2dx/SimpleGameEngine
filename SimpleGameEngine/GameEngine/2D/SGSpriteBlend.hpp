//
//  SGSpriteBlend.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/01.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGSpriteBlend_hpp
#define SGSpriteBlend_hpp

#include "SGNode.hpp"

namespace SimpleGameEngine {
    class Texture2D;
    class SpriteBlend : public Node
    {
    public:
        static std::shared_ptr<SpriteBlend> create(std::string& textureFilename, std::string& blendTextureFilename);
    protected:
        SpriteBlend(std::shared_ptr<Texture2D> texture2d, std::shared_ptr<Texture2D> blendTexture2d);
    private:
        virtual bool init() override;
        virtual void draw() override;
        std::shared_ptr<Texture2D> _texture2d;
        std::shared_ptr<Texture2D> _blendTexture2d;
    };
}

#endif /* SGSpriteBlend_hpp */
