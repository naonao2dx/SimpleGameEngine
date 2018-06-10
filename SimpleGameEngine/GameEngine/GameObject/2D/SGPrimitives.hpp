//
//  SGPrimitives.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/17.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGPrimitives_hpp
#define SGPrimitives_hpp

#include "SGShaderManager.hpp"
#include "SGShaderBase.hpp"
#include "SGDirector.hpp"
#include "SGDrawingObject.hpp"
#include "SGBlendFunc.hpp"
#include "SGCamera.hpp"

namespace SimpleGameEngine {
    class Primitives : public DrawingObject
    {
    public:
        static std::shared_ptr<Primitives> create(int shapeType);
        static std::shared_ptr<Primitives> createWithPositionAndColor3DShader(int shapeType);
        static std::shared_ptr<Primitives> createWithVertexColorShader(int shapeType);
        void update();
        void setVertex(std::vector<Vertex> &vertex);
        void setNormalizedVertex(std::vector<Vertex> &normalizedVertex);
        void setColor(const Color4F& color);
        void setLineWidth(GLfloat lineWidth);
        void setBlendFunc(BlendFunc blendFunc);
        inline std::vector<Vertex> getVertex() const { return _vertex; };
        inline std::vector<Vertex> getNormalizedVertex() const { return _normalizedVertex; };
        inline Color4F getColor() const { return _color; };
        inline GLfloat getLineWidth() const { return _lineWidth; };
    private:
        Primitives(int shapeType);
        void setShaderPositionAndColor();
        void setShaderPositionAndColor3D();
        void setShaderVertexColor();
        bool init();
        void setShaderProgram(ShaderManager::ShaderType shaderType);
        std::shared_ptr<Director> _director;
        int _shapeType;
        int _shaderType;
        std::vector<Vertex> _vertex;
        std::vector<Vertex> _normalizedVertex;
        GLfloat _lineWidth;
        Color4F _color;
        std::shared_ptr<ShaderManager> _shaderManager;
        std::shared_ptr<ShaderBase> _shaderProgram;
        inline virtual void visit() override { update(); draw(); };
        virtual void draw() override;
        BlendFunc _blendFunc;
    };
}

#endif /* SGPrimitives_hpp */

