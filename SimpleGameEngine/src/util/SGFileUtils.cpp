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
    Console::logDebug("_bundlepath:");
    Console::logDebug(_bundlePath.c_str());
    std::string filepath = _bundlePath + "/" + filename;
    Console::logDebug("filepath:");
    Console::logDebug(filepath.c_str());
    
    std::ifstream ifs(filepath, std::ios::in | std::ios::binary);
    if (!ifs)
        return false;
    ifs.seekg(0, std::ifstream::end);
    auto filesize = static_cast<size_t>(ifs.tellg());
    ifs.seekg(0, std::ifstream::beg);
    
    buf.resize(filesize);
    std::getline(ifs, buf);
    

    return true;
}

void FileUtils::setBundlePath(const std::string &bundlePath)
{
    _bundlePath = bundlePath;
    Console::logDebug("setBundlePath");
    Console::logDebug(_bundlePath.c_str());
}
