//
//  SGLayer.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/06/11.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGLayer_hpp
#define SGLayer_hpp

#include "SGNode.hpp"

namespace SimpleGameEngine {
    class Layer : public Node
    {
    public:
        static std::shared_ptr<Layer> createLayer();
    private:
        Layer(){};
    };
}

#endif /* SGLayer_hpp */
