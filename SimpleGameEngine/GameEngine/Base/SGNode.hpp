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
    class Director;
    class Node : public DrawingObject
    {
    public:
        Node();
        void setShaderProgram(ShaderManager::ShaderType shaderType);
        void addChild(const std::shared_ptr<DrawingObject> child);
        
        inline Vec2& getPosition() { return _position; };
        inline float getPositionX() { return _position.x; };
        inline float getPositionY() { return _position.y; };
        void setPosition(const Vec2& position);
        void setPosition(const float x, const float y);
        void setPositionX(const float x);
        void setPositionY(const float y);
        
        inline Vec2& getNormalizedPosition() { return _normalizedPosition; };
        inline float getNormalizedPositionX() { return _normalizedPosition.x; };
        inline float getNormalizedPositionY() { return _normalizedPosition.y; };
        void setNormalizedPosition(const Vec2& normalizedPosition);
        void setNormalizedPosition(const float normalizedPositionX, const float normalizedPositionY);
        void setNormalizedPositionX(const float normalizedPositionX);
        void setNormalizedPositionY(const float normalizedPositionY);
        
        inline Size& getContentSize() { return _contentSize; };
        inline int getWidth() { return _contentSize.width; };
        inline int getHeight() { return _contentSize.height; };
        void setContentSize(Size& contentSize);
        void setContentSize(int width, int height);
        void setWidth(int width);
        void setHeight(int height);
    protected:
        virtual bool init();
        virtual void visit() override;
        virtual void draw() override {};
        
        float positionXtoNormalizedPositionX(int x);
        float positionYtoNormalizedPositionY(int y);
        int normalizedPositionXtoPositionX(float normalizedPositionX);
        int normalizedPositionYtoPositionY(float normalizedPositionY);
        void setVertex();
        
        std::shared_ptr<Director> _director;
        int _shaderType;
        std::vector<Vertex> _vertex;
        std::vector<std::shared_ptr<DrawingObject>> _children;
        std::shared_ptr<ShaderManager> _shaderManager;
        std::shared_ptr<ShaderProgram> _shaderProgram;
        
        Vec2 _position;
        Vec2 _normalizedPosition;
        Size _contentSize;
    };
}

#endif /* SGNode_hpp */
