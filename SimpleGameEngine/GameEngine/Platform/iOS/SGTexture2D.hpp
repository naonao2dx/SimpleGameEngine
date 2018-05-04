//
//  SGTexture2D.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/25.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGTexture2D_hpp
#define SGTexture2D_hpp

#include <memory>

namespace SimpleGameEngine {
    class Texture2D
    {
    public:
        static std::shared_ptr<Texture2D> createWithFileName(std::string& cppFileName, int rawformat);
        Texture2D();
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

#endif /* SGTexture2D_hpp */

