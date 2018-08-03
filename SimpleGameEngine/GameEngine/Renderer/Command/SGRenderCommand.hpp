//
//  SGRenderCommand.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/08/01.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGRenderCommand_hpp
#define SGRenderCommand_hpp

#include "SGVertex.h"
#include "SGShaderBase.hpp"
#include <memory.h>

using namespace SimpleGameEngine;

struct RenderCommand
{
    Vertex* _vertices;
    GLushort* _indeices;
    GLuint _verticesNum;
    GLuint _indeicesNum;
    std::shared_ptr<ShaderBase> _shader;
};

#endif /* SGRenderCommand_hpp */
