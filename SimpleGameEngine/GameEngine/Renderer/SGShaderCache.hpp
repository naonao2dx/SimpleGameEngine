//
//  SGShaderCache.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/18.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGShaderCache_hpp
#define SGShaderCache_hpp

#include <memory>
#include <unordered_map>
#include <string>
#include "SGShaderProgram.hpp"

namespace SimpleGameEngine {
    class ShaderCache {
    public:
        static std::shared_ptr<ShaderCache> getInstance();
        void loadDefaultShader();
    private:
        ShaderCache();
        bool init();
        std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> _shaderMap;
    };
}

#endif /* SGShaderCache_hpp */
