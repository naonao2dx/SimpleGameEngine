//
//  SGDrawingObject.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/04.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGDrawingObject_hpp
#define SGDrawingObject_hpp

namespace SimpleGameEngine {
    class DrawingObject
    {
    public:
        virtual void visit() = 0;
        virtual void draw() = 0;
    };
}

#endif /* SGDrawingObject_hpp */
