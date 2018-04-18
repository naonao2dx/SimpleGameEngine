//
//  SGShaderCache.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/18.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGShaderCache_hpp
#define SGShaderCache_hpp

#include <stdio.h>
#include <memory>
#include <unordered_map>
#include <string>
#include "SGShaderProgram.hpp"

namespace SimpleGameEngine {
    class SGShaderCache {
    public:
        static std::shared_ptr<SGShaderCache> getInstance();
        void loadDefaultShader();
    private:
        SGShaderCache();
        bool init();
        std::unordered_map<std::string, std::shared_ptr<SGShaderProgram>> _shaderMap;
    };
}

#endif /* SGShaderCache_hpp */
