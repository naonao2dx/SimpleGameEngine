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
        Vec3 position;
        Vec3 normal;
        Vec2 uv;
        Color4B color;
        
        Vertex();
        Vertex(Vec3 _position);
        Vertex(Vec3 _position, Color4B _color);
        Vertex(Vec3 _position, Vec2 _uv);
        Vertex(Vec3 _position, Color4B _color, Vec2 _uv);
        Vertex(Vec2 _position);
        Vertex(Vec2 _position, Color4B _color);
        Vertex(Vec2 _position, Vec2 _uv);
        Vertex(Vec2 _position, Color4B _color, Vec2 _uv);
    };
}
#endif /* SGVertex_h */
