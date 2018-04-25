//
//  ShaderVertexColor.frag
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/25.
//  Copyright © 2018年 Nao. All rights reserved.
//

const GLchar* shaderFragVertexColor = R"(

varying lowp vec4 vary_color;
void main() {
    gl_FragColor = vary_color;
}
)";
