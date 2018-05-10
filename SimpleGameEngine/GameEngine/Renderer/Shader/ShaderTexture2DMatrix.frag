//
//  ShaderTexture2DMatrix.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/10.
//  Copyright © 2018年 Nao. All rights reserved.
//

const GLchar* shaderFragTexture2DMatrix = R"(
uniform sampler2D texture;
varying mediump vec2 vary_uv;
void main() {
    gl_FragColor = texture2D(texture, vary_uv);
}
)";
