//
//  SGUtil.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/06/19.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGUtil.hpp"
#include <cstring>
#import <Foundation/Foundation.h>
#include "SGConsole.hpp"

#define CSTR2NSSTRING(c_str)       [[NSString alloc] initWithUTF8String:c_str]

using namespace SimpleGameEngine;

void Util::sjisToUtf8(GLchar *str, const int array_length)
{
    const int str_len = (int)strlen(str);
    if (!str_len) {
        return;
    }
    
    NSString *converted = [[NSString alloc] initWithBytes:str length:str_len encoding:NSShiftJISStringEncoding];
    const char* utf8 = [converted UTF8String];
    int converted_length = (int)strlen(utf8);
    if(converted_length >= array_length) {
        converted_length = array_length - 1;
    }
    memcpy(str, utf8, converted_length);
    str[converted_length] = '\0';
}
