//
//  SGApplication.cpp
//  SimpleGameEngine
//
//  Created by Nao on 2018/03/21.
//  Copyright © 2018年 Nao. All rights reserved.
//

#import "SGApplication.hpp"
#import "../platform/ios/SGDirectorCaller.h"
#import "../../application/AppDelegate.hpp"

using namespace SimpleGameEngine;

static std::shared_ptr<Application> pInstance;

std::shared_ptr<Application> Application::getInstance()
{
    if (!pInstance) {
        pInstance.reset(new Application());
    }
    return pInstance;
}

int Application::run() {
    AppDelegate* appDelegate = new AppDelegate();
    if (appDelegate->applicationDidFinishLaunching()) {
        [[SGDirectorCaller sharedDirectorCaller] startMainLoop];
    }
    return 0;
}
