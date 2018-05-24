//
//  ShaderPositionCamera.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/24.
//  Copyright © 2018年 Nao. All rights reserved.
//

const GLchar* shaderVertPositionCamera = R"(

attribute mediump vec4 attr_pos;
uniform mediump mat4 unif_lookat;
uniform mediump mat4 unif_projection;

void main()
{
    gl_Position = unif_projection * unif_lookat * attr_pos;
}
)";
