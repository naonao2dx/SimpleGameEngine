//
//  SGRawImage.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/25.
//  Copyright © 2018年 Nao. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#include "SGRawImage.hpp"
#include "../../Util/SGConsole.hpp"
#include <assert.h>
#include <string>

#define CSTR2NSSTRING(c_str)       [[NSString alloc] initWithUTF8String:c_str]

using namespace SimpleGameEngine;

std::shared_ptr<RawImage> RawImage::createWithFileName(std::string& cppFileName, int rawFormat)
{
    std::shared_ptr<RawImage> rawImage = std::make_shared<RawImage>();
    
    int pixelSize = 0;
    rawImage->_format = rawFormat;
    
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
    rawImage->_width = (int)CGImageGetWidth(cgimage);
    rawImage->_height = (int)CGImageGetHeight(cgimage);
    rawImage->_pixelByte = (int)CGImageGetBitsPerPixel(cgimage) / 8;
    UInt8 *rgba = (unsigned char*)malloc(rawImage->_width * rawImage->_height * 4);
    rawImage->_pixelData = (void*)rgba;
    
    assert(rawImage->_pixelByte == 3 || rawImage->_pixelByte == 4);
    
    CGDataProviderRef provider = CGImageGetDataProvider(cgimage);
    CFDataRef data = CGDataProviderCopyData(provider);
    
    rawImage->_rawPixels = (void*)CFDataGetBytePtr(data);
    
    switch(rawImage->_pixelByte) {
        case 3:
            break;
        case 4:
            rawImage->convertColorRGBA();
            break;
    }
    
    CFRelease(data);
    image = nil;
    
    return rawImage;
}

void RawImage::convertColorRGBA()
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

RawImage::RawImage()
{
    
}
