//
//  SGTexture2D.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/25.
//  Copyright © 2018年 Nao. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#include "SGTexture2D.hpp"
#include "../../Util/SGConsole.hpp"
#include <assert.h>
#include <string>

#define CSTR2NSSTRING(c_str)       [[NSString alloc] initWithUTF8String:c_str]

using namespace SimpleGameEngine;

std::shared_ptr<Texture2D> Texture2D::createWithFileName(std::string& cppFileName, int rawFormat)
{
    std::shared_ptr<Texture2D> texture2d = std::make_shared<Texture2D>();
    
    int pixelSize = 0;
    texture2d->_format = rawFormat;
    
    switch (rawFormat) {
        case TEXTURE_RAW_RGBA8:
            pixelSize = 4;
            break;
        case TEXTURE_RAW_RGB8:
            pixelSize = 3;
            break;
        case TEXTURE_RAW_RGB565:
        case TEXTURE_RAW_RGBA5551:
            pixelSize = 2;
            break;
    }
    
    assert(pixelSize > 0);
    
    NSString *fileName =[[NSString alloc] initWithFormat:@"Assets/%@", CSTR2NSSTRING(cppFileName.c_str())];
    UIImage *image = [UIImage imageNamed:fileName];
    if(!image) {
        Console::logDebug("image %s is null", cppFileName.c_str());
        return nullptr;
    }
    
    CGImageRef cgimage = image.CGImage;
    texture2d->_width = (int)CGImageGetWidth(cgimage);
    texture2d->_height = (int)CGImageGetHeight(cgimage);
    texture2d->_pixelByte = (int)CGImageGetBitsPerPixel(cgimage) / 8;
    UInt8 *rgba = (unsigned char*)malloc(texture2d->_width * texture2d->_height * 4);
    texture2d->_pixelData = (void*)rgba;
    
    assert(texture2d->_pixelByte == 3 || texture2d->_pixelByte == 4);
    
    CGDataProviderRef provider = CGImageGetDataProvider(cgimage);
    CFDataRef data = CGDataProviderCopyData(provider);
    
    texture2d->_rawPixels = (void*)CFDataGetBytePtr(data);
    
    switch(texture2d->_pixelByte) {
        case 3:
            break;
        case 4:
            texture2d->convertColorRGBA();
            break;
    }
    
    CFRelease(data);
    image = nil;
    
    return texture2d;
}

void Texture2D::convertColorRGBA()
{
    int pixels = _width * _height;
    unsigned char* src_rgba8888 = (unsigned char*) _rawPixels;
    
    switch (_format) {
        case TEXTURE_RAW_RGBA8:
            memcpy(_pixelData, src_rgba8888, pixels * 4);
            break;
            
        default:
            break;
    }
}

Texture2D::Texture2D()
{
    
}
