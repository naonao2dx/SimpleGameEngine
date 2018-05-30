//
//  ShaderPositionCamera.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/24.
//  Copyright © 2018年 Nao. All rights reserved.
//

const GLchar* shaderVertPositionCamera = R"(

attribute mediump vec4 attr_pos;
uniform mediump mat4 unif_wlp;

void main()
{
    gl_Position = unif_wlp * attr_pos;
}
)";
