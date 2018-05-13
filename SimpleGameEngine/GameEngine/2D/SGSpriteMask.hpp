//
//  SGSpriteMask.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/01.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGSpriteMask_hpp
#define SGSpriteMask_hpp

#include "SGNode.hpp"

namespace SimpleGameEngine {
    class Texture2D;
    class SpriteMask : public Node
    {
    public:
        static std::shared_ptr<SpriteMask> create(std::string& textureFilename, std::string& maskTextureFilename);
    protected:
        SpriteMask(std::shared_ptr<Texture2D> texture2d, std::shared_ptr<Texture2D> maskTexture2d);
    private:
        virtual bool init() override;
        virtual void draw() override;
        std::shared_ptr<Texture2D> _texture2d;
        std::shared_ptr<Texture2D> _maskTexture2d;
    };
}

#endif /* SGSpriteMask_hpp */
