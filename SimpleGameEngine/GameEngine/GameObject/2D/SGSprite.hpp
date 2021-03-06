//
//  SGSprite.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/26.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGSprite_hpp
#define SGSprite_hpp

#include "SGNode.hpp"
#include "SGBlendFunc.hpp"

namespace SimpleGameEngine {
    class Texture2D;
    class Sprite : public Node
    {
    public:
        static std::shared_ptr<Sprite> create(std::string& filename);
        static std::shared_ptr<Sprite> createWithCustomMipmap(std::vector<std::string> filenames);
        static std::shared_ptr<Sprite> createWithTextureAtlas(std::string& atlasname, std::string& filename);
        
        void setBlendFunc(BlendFunc blendFunc);
    protected:
        Sprite(std::shared_ptr<Texture2D> texture2d);
        virtual bool init() override;
        virtual void draw() override;
    private:
        std::shared_ptr<Texture2D> _texture2d;
        BlendFunc _blendFunc;
    };
}

#endif /* SGSprite_hpp */
