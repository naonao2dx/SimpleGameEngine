//
//  ShaderTexture.frag
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/25.
//  Copyright © 2018年 Nao. All rights reserved.
//

const GLchar* shaderFragTexture2D = R"(

uniform sampler2D texture;
varying mediump vec2 vary_uv;

void main() {
    gl_FragColor = texture2D(texture, vary_uv);
}
)";
