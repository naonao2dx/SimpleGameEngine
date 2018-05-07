//
//  SGVertex.h
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/25.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGVertex_h
#define SGVertex_h

#include "SGGeometry.hpp"
#include "SGColor.hpp"

namespace SimpleGameEngine {
    struct Vertex
    {
        Vec2 _position;
        Color4B _color;
        
        Vertex();
        Vertex(Vec2 position);
        Vertex(Vec2 position, Color4B color);
    };
}
#endif /* SGVertex_h */
