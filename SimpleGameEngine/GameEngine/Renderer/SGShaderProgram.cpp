//
//  SGShaderProgram.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/18.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGShaderProgram.hpp"
#include "../Util/SGConsole.hpp"
#include "../Util/SGFileUtils.hpp"

using namespace SimpleGameEngine;

std::shared_ptr<SGShaderProgram> SGShaderProgram::createWithFileNames(const std::string& vertShaderFilename, const std::string& fragShaderFilename)
{
    std::shared_ptr<SGShaderProgram> shaderProgram(new SGShaderProgram());
    auto fileUtils = FileUtils::getInstance();
    std::string vertSource;
    fileUtils->getContents(vertShaderFilename, vertSource);
    
    Console::logDebug("SGShaderProgram::createWithFileName");
    Console::logDebug(vertSource.c_str());
    
    return shaderProgram;
}
