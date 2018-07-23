//
//  HelloScene.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/17.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef HelloScene_hpp
#define HelloScene_hpp

#include "SGBaseScene.hpp"
#include "SGPmdData.hpp"

class HelloScene : public SimpleGameEngine::Scene
{
public:
    static std::shared_ptr<SimpleGameEngine::Scene> createScene();
    static std::shared_ptr<HelloScene> create();
    virtual bool init() override;
    virtual void update() override;
    
    GLint _rotate;
    GLfloat _alpha = 1.0;
    std::shared_ptr<SimpleGameEngine::PmdData> pmd;
};



#endif /* HelloScene_hpp */
