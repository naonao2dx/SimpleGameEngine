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
#include "SGGeometry.hpp"
#include "SGColor.hpp"
#include "SGShaderManager.hpp"
#include "SGVertex.h"


namespace SimpleGameEngine {
    class Director;
    class Node : public DrawingObject
    {
    public:
        Node();
        void addChild(const std::shared_ptr<DrawingObject> child);
        void addChild(const std::shared_ptr<DrawingObject> child, int localOrderZ);
        virtual void update(){};
        
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
        
        inline Size& getOriginSize() { return _originSize; };
        inline int getOriginWidth() { return _originSize.width; };
        inline int getOriginHeight() { return _originSize.height; };
        void setOriginSize(Size& originSize);
        void setOriginSize(int width, int height);
        void setOriginWidth(int width);
        void setOriginHeigh(int height);
        
        inline Size& getContentSize() { return _contentSize; };
        inline int getWidth() { return _contentSize.width; };
        inline int getHeight() { return _contentSize.height; };
        void setContentSize(Size& contentSize);
        void setContentSize(int width, int height);
        void setWidth(int width);
        void setHeight(int height);
        
        inline Vec2& getScale() { return _scale; };
        inline int getScaleX() { return _scale.x; };
        inline int getScaleY() { return _scale.y; };
        void setScale(Vec2& scale);
        void setScale(GLfloat x, GLfloat y);
        void setScaleX(GLfloat x);
        void setScaleY(GLfloat y);
        
        inline Vec2& getOriginScale() { return _originScale; };
        inline int getOriginScaleX() { return _originScale.x; };
        inline int getOriginScaleY() { return _originScale.y; };
        
        inline GLfloat getRotate() { return _rotate; };
        void setRotate(GLfloat rotate);
        
        void setMatrix();
        
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
        std::vector<Vertex> _vertex;
        std::vector<std::shared_ptr<DrawingObject>> _children;
        
        Size _designResolutionSize;
        
        Vec2 _position;
        Vec2 _normalizedPosition;
        
        Vec2 _scale;
        Vec2 _originScale;
        
        Size _originSize;
        Size _contentSize;
        
        GLfloat _rotate;
        GLfloat _aspect;
        
        Mat4 _matrix;

    };
}

#endif /* SGNode_hpp */
