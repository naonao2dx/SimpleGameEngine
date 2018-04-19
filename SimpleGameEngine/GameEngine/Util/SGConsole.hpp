//
//  SGConsole.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/17.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGConsole_hpp
#define SGConsole_hpp

namespace SimpleGameEngine {
    class Console
    {
    public:
        static void logDebug(const char *fmt, ...);
    };
}

#endif /* SGConsole_hpp */
