//
//  SGBaseScene.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/17.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGBaseScene_hpp
#define SGBaseScene_hpp

#include "SGNode.hpp"

namespace SimpleGameEngine {
    class Scene : public Node
    {
    public:
        static std::shared_ptr<Scene> create();
        virtual bool init() override { return true; };
        virtual void render();
    protected:
        Scene();
    };
}

#endif /* SGBaseScene_hpp */
