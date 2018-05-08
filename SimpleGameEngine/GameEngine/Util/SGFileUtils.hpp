//
//  FileUtils.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/18.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef FileUtils_hpp
#define FileUtils_hpp

#include <memory>
#include <string>

namespace SimpleGameEngine {
    class FileUtils
    {
    public:
        static std::shared_ptr<FileUtils> getInstance();
        void setBundlePath(const std::string& bundlePath);
        bool getAssetContents(const std::string& filename, std::string& buf);
        bool getContents(const std::string& filename, std::string& buf);
        char* getContents(const std::string& filename);
    private:
        std::string _bundlePath;
    };
}

#endif /* SGFileUtils_hpp */
