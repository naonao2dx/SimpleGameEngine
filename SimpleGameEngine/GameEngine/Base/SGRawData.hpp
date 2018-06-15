//
//  SGRawData.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/06/15.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGRawData_hpp
#define SGRawData_hpp

#include "SGRawData.hpp"
#include <cstdint>

namespace SimpleGameEngine {
    struct RawData
    {
        void* head;
        int length;
        uint8_t* readHead;
    };
}

#endif /* SGRawData_hpp */
