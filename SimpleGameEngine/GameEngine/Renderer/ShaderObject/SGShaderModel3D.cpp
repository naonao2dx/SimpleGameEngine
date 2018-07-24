//
//  SGShaderModel3D.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/06/15.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGShaderModel3D.hpp"
#include "SGSpriteCache.hpp"

using namespace SimpleGameEngine;

ShaderModel3D::ShaderModel3D(const GLchar* vertShaderSource, const GLchar* fragShaderSource)
{
    createShader(vertShaderSource, fragShaderSource);
    init();
}

bool ShaderModel3D::init()
{
    _attrPos = glGetAttribLocation(_shader, "attr_pos");
    assert(_attrPos >= 0);
    
    _attrUV = glGetAttribLocation(_shader, "attr_uv");
    assert(_attrUV >= 0);
    
    _unifColor = glGetUniformLocation(_shader, "unif_color");
    assert(_unifColor >= 0);
    
    _unifTexture = glGetUniformLocation(_shader, "unif_texture");
    assert(_unifTexture >= 0);
    
    _unifWlp = glGetUniformLocation(_shader, "unif_wlp");
    assert(_unifWlp >= 0);
    
    _unifAlpha = glGetUniformLocation(_shader, "unif_alpha");
    assert(_unifAlpha >= 0);
    
    return true;
}

void ShaderModel3D::draw()
{
    _model->setVBO();
    _model->setIBO();
    
    glBindBuffer(GL_ARRAY_BUFFER, _model->_verticesBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _model->_indicesBuffer);
    
    ShaderBase3D::draw();
    
    glCullFace(GL_BACK);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glEnableVertexAttribArray(_attrPos);
    glEnableVertexAttribArray(_attrUV);
    
    glVertexAttribPointer(_attrPos, 3, GL_FLOAT, GL_FALSE, sizeof(PmdVertex), (GLvoid*) 0);
    glVertexAttribPointer(_attrUV, 2, GL_FLOAT, GL_FALSE, sizeof(PmdVertex), (GLvoid*) sizeof(Vec3));
    
    glUniformMatrix4fv(_unifWlp, 1, GL_FALSE, (GLfloat*)_wlp.m);
    glUniform1f(_unifAlpha, _alpha);
    
    // Rendering path 1
    {
        glDepthFunc(GL_LESS);
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
        glDepthMask(GL_TRUE);

        glUniform4f(_unifColor, 1.0f, 1.0f, 1.0f, 1.0f);
        glDrawElements(GL_TRIANGLES, _model->_indicesNum, GL_UNSIGNED_SHORT, (GLvoid*) 0);
        assert(glGetError() == GL_NO_ERROR);
    }
    
    // Rendering path 2
    {
        glDepthFunc(GL_EQUAL);
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        glDepthMask(GL_FALSE);

        GLint beginIndecesIndex = 0;
        
        for (int i = 0; i < _model->_materialsNum; ++i) {
            PmdMaterial* material = &_model->_materials[i];
            std::string textureName { material->diffuseTextureName };
            textureName += ".png";
            std::shared_ptr<SpriteCache> spriteCache = SpriteCache::getInstance();
            std::shared_ptr<Texture2D> texture = spriteCache->getTextureData(textureName);
            if (texture) {
                glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
                glUniform1i(_unifTexture, 0);
                glUniform4f(_unifColor, 0, 0, 0, 0);
            } else {
                glUniform4f(_unifColor, material->diffuse.x, material->diffuse.y, material->diffuse.z, material->diffuse.w);
            }
            
            glDrawElements(GL_TRIANGLES, material->indicesNum, GL_UNSIGNED_SHORT, (GLvoid*) (beginIndecesIndex * sizeof(GLushort)));
            assert(glGetError() == GL_NO_ERROR);
            beginIndecesIndex += material->indicesNum;
        }
    }

    glDepthMask(GL_TRUE);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
