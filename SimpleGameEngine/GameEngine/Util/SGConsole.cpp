//
//  SGConsole.cpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/17.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include "SGConsole.hpp"
#include <syslog.h>
#include <stdarg.h>

using namespace SimpleGameEngine;

void Console::logDebug(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vsyslog(LOG_DEBUG, fmt, args);
    va_end(args);
}
