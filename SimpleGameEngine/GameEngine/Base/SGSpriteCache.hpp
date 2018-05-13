//
//  SGSpriteCache.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/07.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGSpriteCache_hpp
#define SGSpriteCache_hpp

#include <string>
#include <unordered_map>
#include "SGTexture2D.hpp"

namespace SimpleGameEngine {
    class SpriteCache
    {
    public:
        static std::shared_ptr<SpriteCache> getInstance();
        std::shared_ptr<Texture2D> getTextureData(std::string& filename);
        std::shared_ptr<Texture2D> getTextureData(std::vector<std::string> filenames);
        std::shared_ptr<Texture2D> getTextureData(std::string& atlasName, std::string& filename);
        void clearCache();
    private:
        SpriteCache();
        bool init();
        
        std::unordered_map<std::string, std::shared_ptr<Texture2D>> _spriteCache;
    };
}

#endif /* SGSpriteCache_hpp */
