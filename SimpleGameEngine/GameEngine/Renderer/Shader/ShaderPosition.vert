//
//  ShaderPosition.vert
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/17.
//  Copyright © 2018年 Nao. All rights reserved.
//

const GLchar* shaderVertPosition = R"(

attribute mediump vec4 attr_pos;

void main()
{
    gl_Position = attr_pos;
}
)";
