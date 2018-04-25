//
//  ShaderVertexColor.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/25.
//  Copyright © 2018年 Nao. All rights reserved.
//

const GLchar* shaderVertVertexColor = R"(

attribute mediump vec4 attr_pos;
attribute lowp vec4 attr_color;
varying lowp vec4 vary_color;

void main() {
    gl_Position = attr_pos;
    vary_color = attr_color;
}
)";
