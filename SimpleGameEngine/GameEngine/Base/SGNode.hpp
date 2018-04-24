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
#include "../Util/SGGeometry.hpp"
#include "../Util/SGColor.hpp"
#include "../Renderer/SGShaderManager.hpp"


namespace SimpleGameEngine {
    class Node
    {
    public:
        Node();
        void setShaderProgram(ShaderManager::ShaderType shaderType);
        void addChild(const std::shared_ptr<Node> child);
        void setColor(const Color4F& color);
        virtual void setPosition(const std::vector<std::shared_ptr<Vec2>> position);
    protected:
        virtual bool init();
        void visit();
        virtual void draw(){};
        GLuint compileShader(GLuint shaderType, const GLchar *source);
        
        Color4F _color;
        std::vector<std::shared_ptr<Vec2>> _position;
        std::vector<std::shared_ptr<Node>> _children;
        std::shared_ptr<ShaderManager> _shaderManager;
        std::shared_ptr<ShaderProgram> _shaderProgram;
        
    };
}

#endif /* SGNode_hpp */
