//
//  SGShaderBase3D.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/06/10.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGShaderBase3D_hpp
#define SGShaderBase3D_hpp

#include "SGShaderBase.hpp"

namespace SimpleGameEngine {
    class ShaderBase3D : public ShaderBase
    {
    protected:
        //ShaderBase3D(){};
        //virtual ~ShaderBase3D();
        virtual void draw() override;
        
    };
}

#endif /* SGShaderBase3D_hpp */
