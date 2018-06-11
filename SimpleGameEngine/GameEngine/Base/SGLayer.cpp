//
//  SGLayer.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/06/11.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGLayer.hpp"

using namespace SimpleGameEngine;

std::shared_ptr<Layer> Layer::createLayer()
{
    std::shared_ptr<Layer> layer(new (std::nothrow) Layer);
    return layer;
}
