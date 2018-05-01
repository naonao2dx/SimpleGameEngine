//
//  SGBlendTexture.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/01.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGBlendTexture.hpp"
#include "SGShaderBlendTexture.hpp"

using namespace SimpleGameEngine;

BlendTexture::BlendTexture(std::string& textureFilename, std::string& blendTextureFilename)
: _textureFilename(textureFilename)
, _blendTextureFilename(blendTextureFilename)
{
    init();
}

bool BlendTexture::init()
{
    Node::init();
    
    Vertex vert1 = Vertex { Vec2 { -0.75f, 0.75f } } ;
    Vertex vert2 = Vertex { Vec2 { -0.75f, -0.75f } } ;
    Vertex vert3 = Vertex { Vec2 { 0.75f, 0.75f } } ;
    Vertex vert4 = Vertex { Vec2 { 0.75f, -0.75f } };
    std::vector<Vertex> vertex = { vert1, vert2, vert3, vert4 };
    setVertex(vertex);
    
    Vertex uv1 = Vertex { Vec2 { 0.0f, 0.0f } };
    Vertex uv2 = Vertex { Vec2 { 0.0f, 1.0f } };
    Vertex uv3 = Vertex { Vec2 { 1.0f, 0.0f } };
    Vertex uv4 = Vertex { Vec2 { 1.0f, 1.0f } };
    std::vector<Vertex> uv = { uv1, uv2, uv3, uv4 };
    setVertexUV(uv);
    
    setShaderBlendTexture();
    
    return true;
}

void BlendTexture::setVertexUV(const std::vector<Vertex> vertexUV)
{
    _vertexUV = vertexUV;
}

void BlendTexture::setShaderBlendTexture()
{
    setShaderProgram(ShaderManager::ShaderType::BLEND_TEXTURE);
    std::dynamic_pointer_cast<ShaderTexture2D>(_shaderProgram)->setFilter(GL_NEAREST, GL_NEAREST);
    _textureID = std::dynamic_pointer_cast<ShaderBlendTexture>(_shaderProgram)->setTextureFilename(_textureFilename, false);
    _blendTextureID = std::dynamic_pointer_cast<ShaderBlendTexture>(_shaderProgram)->setTextureFilename(_blendTextureFilename, false);
    std::dynamic_pointer_cast<ShaderBlendTexture>(_shaderProgram)->bindTexture(_textureID, _blendTextureID);
}

void BlendTexture::draw()
{
    std::dynamic_pointer_cast<ShaderBlendTexture>(_shaderProgram)->bindTexture(_textureID, _blendTextureID);
    _shaderProgram->setVertex(_vertex);
    std::dynamic_pointer_cast<ShaderTexture2D>(_shaderProgram)->setVertexUV(_vertexUV);
    _shaderProgram->draw();
}
