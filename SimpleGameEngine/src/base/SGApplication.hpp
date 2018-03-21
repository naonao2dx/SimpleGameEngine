//
//  SGApplication.hpp
//  SimpleGameEngine
//
//  Created by Nao on 2018/03/21.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGApplication_hpp
#define SGApplication_hpp

#include <stdio.h>
#include "../common/Singleton.h"

namespace SimpleGameEngine {
    class Application : public Singleton<Application>
    {
    public:
        int run();
    private:
        friend class Singleton<Application>;
        Application() = default;
    };
}

#endif /* SGApplication_hpp */
