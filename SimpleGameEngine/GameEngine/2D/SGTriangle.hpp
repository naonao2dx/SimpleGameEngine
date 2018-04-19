//
//  SGTriangle.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/17.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGTriangle_hpp
#define SGTriangle_hpp

#include "../Base/SGNode.hpp"
#include "../Renderer/SGShaderManager.hpp"
#include "../Renderer/SGShaderProgram.hpp"

namespace SimpleGameEngine {
    class Triangle : public Node
    {
    public:
        Triangle();
    protected:
        virtual void draw() override;
    };
}

#endif /* SGTriangle_hpp */
