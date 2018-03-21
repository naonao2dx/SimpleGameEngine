//
//  SGApplication.cpp
//  SimpleGameEngine
//
//  Created by Nao on 2018/03/21.
//  Copyright © 2018年 Nao. All rights reserved.
//

#import "SGApplication.hpp"
#import "../platform/ios/SGDirectorCaller.h"

using namespace SimpleGameEngine;

int Application::run() {
    [[SGDirectorCaller sharedDirectorCaller] startMainLoop];
    return 0;
}
