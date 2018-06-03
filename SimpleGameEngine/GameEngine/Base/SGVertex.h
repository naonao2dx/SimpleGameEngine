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
        Color4B color;
        
        Vertex();
        Vertex(Vec3 _position);
        Vertex(Vec3 _position, Color4B _color);
        Vertex(Vec2 _position);
        Vertex(Vec2 _position, Color4B _color);
    };
    
    struct VertexWithColor : public Vertex
    {
        Vec3 position;
        Color4B color;
        
        VertexWithColor();
        VertexWithColor(Vec3 _position);
        VertexWithColor(Vec3 _position, Color4B _color);
        VertexWithColor(Vec2 _position);
        VertexWithColor(Vec2 _position, Color4B _color);
    };
}
#endif /* SGVertex_h */
