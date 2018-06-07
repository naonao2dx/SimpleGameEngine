//
//  SGCube3DTexture.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/06/07.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGCube3DTexture_hpp
#define SGCube3DTexture_hpp

#include "SGNode3D.hpp"
#include "SGTexture2D.hpp"

namespace SimpleGameEngine {
    class Cube3DTexture : public Node3D
    {
    public:
        static std::shared_ptr<Cube3DTexture> create(std::string& filename);
    private:
        Cube3DTexture(std::shared_ptr<Texture2D> texture2d);
        virtual void draw() override;
        virtual void setVertex() override;
        std::shared_ptr<Texture2D> _texture2d;
    };
}

#endif /* SGCube3DTexture_hpp */
