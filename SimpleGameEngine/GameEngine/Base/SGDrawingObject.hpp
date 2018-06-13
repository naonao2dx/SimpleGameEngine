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
#include "SGShaderBase.hpp"

namespace SimpleGameEngine {
    class Node;
    class DrawingObject
    {
    public:
        virtual void visit() = 0;
        virtual void draw() = 0;
        void setShaderProgram(ShaderManager::ShaderType shaderType);
        inline void setCamera(std::shared_ptr<Camera> camera) { _camera = camera; };
        inline Node* getParent() { return _parent; };
        inline void setParent(Node* parent) { _parent = parent; };
    protected:
        DrawingObject();
        std::shared_ptr<Camera> _camera;
        int _shaderType;
        std::shared_ptr<ShaderManager> _shaderManager;
        std::shared_ptr<ShaderBase> _shaderProgram;
        Node* _parent;
    };
}

#endif /* SGDrawingObject_hpp */
