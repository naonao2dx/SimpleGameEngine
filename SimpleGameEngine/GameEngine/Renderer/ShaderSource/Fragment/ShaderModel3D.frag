//
//  ShaderModel3D.frag
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/25.
//  Copyright © 2018年 Nao. All rights reserved.
//

const GLchar* shaderFragModel3D = R"(
uniform lowp vec4 unif_color;
uniform sampler2D unif_texture;
uniform lowp float unif_alpha;
varying mediump vec2 vary_uv;

void main() {
    if (unif_color.a == 0.0) {
        gl_FragColor = texture2D(unif_texture, vary_uv);
    } else {
        gl_FragColor = unif_color;
    }
    gl_FragColor.a *= unif_alpha;
}
)";
