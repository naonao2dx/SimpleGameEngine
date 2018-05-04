//
//  SGNode.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/17.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGNode_hpp
#define SGNode_hpp

#include <stdio.h>
#include <vector>
#include <OpenGLES/ES2/gl.h>
#include "SGDrawingObject.hpp"
#include "../Util/SGGeometry.hpp"
#include "../Util/SGColor.hpp"
#include "../Renderer/SGShaderManager.hpp"
#include "../Base/SGVertex.h"


namespace SimpleGameEngine {
    class Node : public DrawingObject
    {
    public:
        Node();
        void setShaderProgram(ShaderManager::ShaderType shaderType);
        void addChild(const std::shared_ptr<DrawingObject> child);
        virtual void setVertex(const std::vector<Vertex> vertex);
    protected:
        virtual bool init();
        virtual void visit() override;
        virtual void draw() override {};
        
        int _shaderType;
        std::vector<Vertex> _vertex;
        std::vector<std::shared_ptr<DrawingObject>> _children;
        std::shared_ptr<ShaderManager> _shaderManager;
        std::shared_ptr<ShaderProgram> _shaderProgram;
        
    };
}

#endif /* SGNode_hpp */
