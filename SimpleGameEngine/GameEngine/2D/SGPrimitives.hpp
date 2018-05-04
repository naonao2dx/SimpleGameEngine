//
//  SGPrimitives.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/17.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGPrimitives_hpp
#define SGPrimitives_hpp

#include "../Renderer/SGShaderManager.hpp"
#include "../Renderer/SGShaderProgram.hpp"
#include "../Base/SGDirector.hpp"

namespace SimpleGameEngine {
    class Primitives : public DrawingObject
    {
    public:
        static std::shared_ptr<Primitives> create(int shapeType);
        static std::shared_ptr<Primitives> createWithVertexColorShader(int shapeType);
        void setVertex(std::vector<Vertex> &vertex);
        void setNormalizedVertex(std::vector<Vertex> &normalizedVertex);
        void setColor(const Color4F& color);
        void setLineWidth(GLfloat lineWidth);
        inline std::vector<Vertex> getVertex() const { return _vertex; };
        inline std::vector<Vertex> getNormalizedVertex() const { return _normalizedVertex; };
        inline Color4F getColor() const { return _color; };
        inline GLfloat getLineWidth() const { return _lineWidth; };
    private:
        Primitives(int shapeType);
        void setShaderPositionAndColor();
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
        std::shared_ptr<ShaderProgram> _shaderProgram;
        inline virtual void visit() override { draw(); };
        virtual void draw() override;
    };
}

#endif /* SGPrimitives_hpp */

