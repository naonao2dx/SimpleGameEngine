//
//  SGShaderModel3DEdge.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/07/23.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGShaderModel3DEdge.hpp"
#include "SGConsole.hpp"

using namespace SimpleGameEngine;

ShaderModel3DEdge::ShaderModel3DEdge(const GLchar* vertShaderSource, const GLchar* fragShaderSource)
{
    createShader(vertShaderSource, fragShaderSource);
    init();
}

bool ShaderModel3DEdge::init()
{
    _attrPos = glGetAttribLocation(_shader, "attr_pos");
    assert(_attrPos >= 0);
    
    _attrNormal = glGetAttribLocation(_shader, "attr_normal");
    assert(_attrNormal >= 0);
    
    _unifColor = glGetUniformLocation(_shader, "unif_color");
    assert(_unifColor >= 0);
    
    _unifWlp = glGetUniformLocation(_shader, "unif_wlp");
    assert(_unifWlp >= 0);
    
    _unifEdgesize = glGetUniformLocation(_shader, "unif_edgesize");
    assert(_unifEdgesize >= 0);
    
    return true;
}

void ShaderModel3DEdge::draw()
{
    ShaderBase3D::draw();
    glCullFace(GL_FRONT);
    glDepthFunc(GL_LESS);
    glEnableVertexAttribArray(_attrPos);
    glEnableVertexAttribArray(_attrNormal);
    
    glUniformMatrix4fv(_unifWlp, 1, GL_FALSE, (GLfloat*)_wlp.m);
    
    glVertexAttribPointer(_attrPos, 3, GL_FLOAT, GL_FALSE, sizeof(PmdVertex), &_model->_vertices[0].position);
    glVertexAttribPointer(_attrNormal, 3, GL_FLOAT, GL_FALSE, sizeof(PmdVertex), &_model->_vertices[0].normal);
    
    glUniform4f(_unifColor, 1.0f, 1.0f, 1.0f, 1.0f);
    glUniform1f(_unifEdgesize, 0.025f);
    assert(glGetError() == GL_NO_ERROR);
    
    glDrawElements(GL_TRIANGLES, _model->_indicesNum, GL_UNSIGNED_SHORT, _model->_indices);
    assert(glGetError() == GL_NO_ERROR);
    
}
