//
//  ShaderColor.frag
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/17.
//  Copyright © 2018年 Nao. All rights reserved.
//

const GLchar *shaderFragColor = R"(

uniform lowp vec4 unif_color;
void main() {

    gl_FragColor = unif_color;
}
)";
