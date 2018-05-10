//
//  ShaderTexture2DMatrix.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/10.
//  Copyright © 2018年 Nao. All rights reserved.
//

const GLchar* shaderVertTexture2DMatrix = R"(
uniform mediump mat4 unif_matrix;
attribute mediump vec4 attr_pos;
attribute mediump vec2 attr_uv;
varying mediump vec2 vary_uv;
void main() {
    gl_Position = unif_matrix * attr_pos;
    vary_uv = attr_uv;
}
)";
