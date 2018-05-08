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

bool FileUtils::getAssetContents(const std::string &filename, std::string &buf)
{
    std::string assetpath = "/Assets/" + filename;
    return getContents(assetpath, buf);
}

bool FileUtils::getContents(const std::string& filename, std::string& buf)
{
    if (filename.empty())
        return false;
    
    std::string filepath = _bundlePath + filename;
    
    std::ifstream ifs(filepath, std::ios::in | std::ios::binary);
    if (ifs.fail())
        return false;
    
    std::istreambuf_iterator<char> it(ifs);
    std::istreambuf_iterator<char> last;
    
    std::string contents(it, last);
    buf = contents;
    return true;
}

char* FileUtils::getContents(const std::string& filename)
{
    std::string filepath = _bundlePath + "/" + filename;
    std::ifstream ifs(filepath, std::ios::in | std::ios::binary);

    ifs.seekg(0,std::ios::end);
    size_t size = ifs.tellg();
    ifs.seekg(0, std::ifstream::beg);
    
    Console::logDebug("size: %d", size);
    
    char* buf = new char[size];
    ifs.read(buf, size);

    return buf;
}

void FileUtils::setBundlePath(const std::string &bundlePath)
{
    _bundlePath = bundlePath;
}
