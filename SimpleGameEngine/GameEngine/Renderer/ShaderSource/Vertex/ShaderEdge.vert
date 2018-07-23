//
//  ShaderEdge.vert
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/07/23.
//  Copyright © 2018年 Nao. All rights reserved.
//

const GLchar* shaderVertEdge = R"(

attribute highp vec3 attr_pos;
attribute mediump vec3 attr_normal;
uniform mediump float unif_edgesize;
uniform highp mat4 unif_wlp;

void main() {
    gl_Position = unif_wlp * vec4( attr_pos + ( attr_normal * unif_edgesize ), 1.0 );
}
)";
