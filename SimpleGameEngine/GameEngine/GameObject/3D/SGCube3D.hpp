//
//  SGCube3D.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/31.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGCube3D_hpp
#define SGCube3D_hpp

#include "SGNode3D.hpp"
#include "SGTexture2D.hpp"

namespace SimpleGameEngine {
    class Cube3D : public Node3D
    {
    public:
        static std::shared_ptr<Cube3D> createWithColor(const Color4F& color);
        static std::shared_ptr<Cube3D> createWithTexture(std::string& filename);
        void setColor(const Color4F& color);
        void setSize3D(Vec3 size);
    private:
        Cube3D();
        Cube3D(std::shared_ptr<Texture2D> texture2d);
        virtual void draw() override;
        virtual void setVertex() override;
        Color4F _color;
    };
}

#endif /* SGCube3D_hpp */
