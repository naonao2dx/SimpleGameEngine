//
//  SGRawImage.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/25.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGRawImage_hpp
#define SGRawImage_hpp

#include <memory>

namespace SimpleGameEngine {
    class RawImage
    {
    public:
        static std::shared_ptr<RawImage> createWithFileName(std::string& cppFileName, int rawformat);
        RawImage();
        inline int getWidth() { return _width; };
        inline int getHeight() { return _height; };
        inline void* getPixelData() { return _pixelData; };
        enum TextureRawFormat {
            TEXTURE_RAW_RGBA8,
            TEXTURE_RAW_RGB8,
            TEXTURE_RAW_RGBA5551,
            TEXTURE_RAW_RGB565
        };
        
    private:
        void convertColorRGBA();
        void* _rawPixels;
        void* _pixelData;
        int _format;
        int _width;
        int _height;
        int _pixelByte;
    };
}

#endif /* SGRawImage_hpp */

