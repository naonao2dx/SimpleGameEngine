//
//  SGApplication.hpp
//  SimpleGameEngine
//
//  Created by Nao on 2018/03/21.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGApplication_hpp
#define SGApplication_hpp

#include <memory>

namespace SimpleGameEngine {
    class Application
    {
    public:
        static std::shared_ptr<Application> getInstance();
        int run();
    private:
        Application() = default;
    };
}

#endif /* SGApplication_hpp */
