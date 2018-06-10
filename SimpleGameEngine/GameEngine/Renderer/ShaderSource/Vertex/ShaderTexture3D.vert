//
//  ShaderTexture.vert
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/25.
//  Copyright © 2018年 Nao. All rights reserved.
//

const GLchar* shaderVertTexture3D = R"(

attribute mediump vec4 attr_pos;
attribute mediump vec2 attr_uv;
varying mediump vec2 vary_uv;
uniform mediump mat4 unif_wlp;

void main() {
    gl_Position = unif_wlp * attr_pos;
    vary_uv = attr_uv;
}
)";
