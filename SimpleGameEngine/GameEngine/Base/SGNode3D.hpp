//
//  SGNode3D.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/31.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGNode3D_hpp
#define SGNode3D_hpp

#include "SGDrawingObject.hpp"
#include "SGShaderManager.hpp"

namespace SimpleGameEngine {
    class Node3D : public DrawingObject
    {
    public:
        Node3D();
        void addChild(const std::shared_ptr<DrawingObject> child);
        virtual void update(){};
        
        inline Vec3 getPosition() { return _position; };
        inline int getWidth() { return _width; };
        inline int getHeight() { return _height; };
        inline int getDepth() { return _depth; };
        void setPosition(Vec3 position);
        void setWidth(int width);
        void setHeight(int height);
        void setDepth(int depth);
    protected:
        virtual void visit() override;
        virtual void draw() override {};
        virtual void setVertex() = 0;
        Vec3 _position;
        int _width;
        int _height;
        int _depth;
        std::vector<Vertex> _vertex;
    };
}

#endif /* SGNode3D_hpp */
