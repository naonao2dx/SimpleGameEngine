//
//  SGBlendTexture.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/01.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGBlendTexture_hpp
#define SGBlendTexture_hpp

#include "../Base/SGNode.hpp"

namespace SimpleGameEngine {
    class BlendTexture : public Node
    {
    public:
        BlendTexture(){};
        BlendTexture(std::string& textureFilename, std::string& blendTextureFilename);
        ~BlendTexture(){};
        void setVertexUV(const std::vector<Vertex> vertexUV);
    private:
        bool init();
        std::vector<Vertex> _vertexUV;
        void setShaderBlendTexture();
        std::string _textureFilename;
        std::string _blendTextureFilename;
        GLuint _textureID;
        GLuint _blendTextureID;
        void draw();
    };
}

#endif /* SGBlendTexture_hpp */
