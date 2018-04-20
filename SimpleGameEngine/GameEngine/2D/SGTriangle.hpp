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

namespace SimpleGameEngine {
    class Triangle : public Node
    {
    public:
        Triangle();
        void setPosition(std::vector<Vec2> position) override;
        void setShaderPositionAndColor();
    protected:
        virtual bool init() override;
        virtual void draw() override;
    private:
        std::vector<Vec2> _position;
    };
}

#endif /* SGTriangle_hpp */
