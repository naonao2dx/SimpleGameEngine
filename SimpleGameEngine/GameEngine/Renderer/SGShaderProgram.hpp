//
//  SGShaderProgram.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/18.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGShaderProgram_hpp
#define SGShaderProgram_hpp

#include <memory>

namespace SimpleGameEngine {
    class SGShaderProgram
    {
    public:
        static std::shared_ptr<SGShaderProgram> createWithFileNames(const std::string& vertShaderFilename, const std::string& fragShaderFilename);
    private:
        SGShaderProgram(){};
    };
}

#endif /* SGShaderProgram_hpp */
