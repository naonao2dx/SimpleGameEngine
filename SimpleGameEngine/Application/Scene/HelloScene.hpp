//
//  HelloScene.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/17.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef HelloScene_hpp
#define HelloScene_hpp

#include "../../GameEngine/Base/SGBaseScene.hpp"

class HelloScene : public SimpleGameEngine::Scene
{
public:
    static std::shared_ptr<SimpleGameEngine::Scene> createScene();
    static std::shared_ptr<HelloScene> create();
    virtual bool init() override;
    virtual void update() override;
    
};



#endif /* HelloScene_hpp */
