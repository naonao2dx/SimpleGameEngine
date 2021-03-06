//
//  ShaderBlendTexture.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/01.
//  Copyright © 2018年 Nao. All rights reserved.
//

const GLchar* shaderVertMaskTexture = R"(
attribute mediump vec4 attr_pos;
attribute mediump vec2 attr_uv;
varying mediump vec2 vary_uv;
void main() {
    gl_Position = attr_pos;
    vary_uv = attr_uv;
}
)";
