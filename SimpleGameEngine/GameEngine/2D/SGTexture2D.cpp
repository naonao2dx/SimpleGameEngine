//
//  SGTexture2D.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/26.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGTexture2D.hpp"
#include "../Renderer/SGShaderTexture2D.hpp"

using namespace SimpleGameEngine;

Texture2D::Texture2D()
{
    init();
}

Texture2D::Texture2D(std::string& filename, bool useMipmap, GLuint magFilter, GLuint minFilter)
: _filename(filename)
, _useMipMap(useMipmap)
, _magFilter(magFilter)
, _minFilter(minFilter)
{
    initWithTexture();
}

Texture2D::Texture2D(std::vector<std::string> filenames, GLuint magFilter, GLuint minFilter)
: _filenames(filenames)
, _magFilter(magFilter)
, _minFilter(minFilter)
{
    initWithMipMap();
}

bool Texture2D::initWithTexture()
{
    init();
    setShaderTexture();
    
    return true;
};

bool Texture2D::initWithMipMap()
{
    init();
    setShaderTextureWithMipmap();
    
    return true;
}

bool Texture2D::init()
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
    
    return true;
}

void Texture2D::setVertexUV(const std::vector<Vertex> vertexUV)
{
    _vertexUV = vertexUV;
}

void Texture2D::setShaderTexture()
{
    setShaderProgram(ShaderManager::ShaderType::TEXTURE_2D);
    std::dynamic_pointer_cast<ShaderTexture2D>(_shaderProgram)->setFilter(_magFilter, _minFilter);
    std::dynamic_pointer_cast<ShaderTexture2D>(_shaderProgram)->setTextureFilename(_filename, _useMipMap);
}

void Texture2D::setShaderTextureWithMipmap()
{
    setShaderProgram(ShaderManager::ShaderType::TEXTURE_2D);
    std::dynamic_pointer_cast<ShaderTexture2D>(_shaderProgram)->setFilter(_magFilter, _minFilter);
    std::dynamic_pointer_cast<ShaderTexture2D>(_shaderProgram)->setTextureFilenameWithCustomMimap(_filenames);
}

void Texture2D::draw()
{
    _shaderProgram->setVertex(_vertex);
    std::dynamic_pointer_cast<ShaderTexture2D>(_shaderProgram)->setVertexUV(_vertexUV);
    _shaderProgram->draw();
}

