//
//  SGShaderManager.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/18.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGShaderManager_hpp
#define SGShaderManager_hpp

#include <memory>
#include <map>
#include <string>
#include "SGShaderProgram.hpp"

namespace SimpleGameEngine {
    class ShaderManager {
    public:
        static std::shared_ptr<ShaderManager> getInstance();
        enum ShaderType {
            POSITION_AND_COLOR,
            POSITION_AND_COLOR_3D,
            VERTEX_COLOR,
            TEXTURE_2D,
            BLEND_TEXTURE,
            TEXTURE_2D_MATRIX,
            TEXTURE_3D
        };
        std::shared_ptr<ShaderProgram> getShaderProgram(ShaderType shaderType);
        
    private:
        ShaderManager();
        bool init();
        void loadDefaultShader();
        std::map<ShaderType, std::shared_ptr<ShaderProgram>> _shaderMap;
    };
}

#endif /* SGShaderManager_hpp */
