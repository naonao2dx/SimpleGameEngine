//
//  FileUtils.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/18.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include <fstream>
#include "SGFileUtils.hpp"
#include "SGConsole.hpp"

using namespace SimpleGameEngine;

std::shared_ptr<FileUtils> pInstance;

std::shared_ptr<FileUtils> FileUtils::getInstance()
{
    if (!pInstance) {
        pInstance.reset(new FileUtils());
    }
    return pInstance;
}

bool FileUtils::getContents(const std::string& filename, std::string& buf)
{
    if (filename.empty())
        return false;
    
    std::string filepath = _bundlePath + "/" + filename;
    
    std::ifstream ifs(filepath, std::ios::in | std::ios::binary);
    if (ifs.fail())
        return false;
    
    std::istreambuf_iterator<char> it(ifs);
    std::istreambuf_iterator<char> last;
    
    std::string contents(it, last);
    buf = contents;
    return true;
}

void FileUtils::setBundlePath(const std::string &bundlePath)
{
    _bundlePath = bundlePath;
}