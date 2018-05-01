//
//  ShaderBlendTexture.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/01.
//  Copyright © 2018年 Nao. All rights reserved.
//

const GLchar* shaderFragBlendTexture = R"(
uniform sampler2D tex_color;
uniform sampler2D tex_mask;
varying mediump vec2 vary_uv;
void main() {
    if (texture2D(tex_mask, vary_uv).r == 0.0) {
        discard;
    }
    gl_FragColor = texture2D(tex_color, vary_uv);
}
)";
