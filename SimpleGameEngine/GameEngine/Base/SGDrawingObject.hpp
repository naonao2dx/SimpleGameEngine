//
//  SGDrawingObject.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/04.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGDrawingObject_hpp
#define SGDrawingObject_hpp

#include "SGCamera.hpp"
#include "SGShaderManager.hpp"
#include "SGShaderProgram.hpp"

namespace SimpleGameEngine {
    class DrawingObject
    {
    public:
        virtual void visit() = 0;
        virtual void draw() = 0;
        void setShaderProgram(ShaderManager::ShaderType shaderType);
        inline void setCamera(std::shared_ptr<Camera> camera) { _camera = camera; };
    protected:
        DrawingObject();
        std::shared_ptr<Camera> _camera;
        int _shaderType;
        std::shared_ptr<ShaderManager> _shaderManager;
        std::shared_ptr<ShaderProgram> _shaderProgram;
    };
}

#endif /* SGDrawingObject_hpp */
