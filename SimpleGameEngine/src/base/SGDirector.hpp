//
//  SGDirector.hpp
//  SimpleGameEngine
//
//  Created by Nao on 2018/03/21.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGDirector_hpp
#define SGDirector_hpp

#include <memory>
#include "../common/Singleton.h"
#include "SGGLView.h"

namespace SimpleGameEngine {
    class Director : public Singleton<Director>
    {
    public:
        void setOpenGLView(std::shared_ptr<GLView> openGLView);
        std::shared_ptr<GLView> getOpenGLView() { return _openGLView; };
        
    private:
        friend class Singleton<Director>;
        Director() = default;
        bool init();
        
        std::shared_ptr<GLView> _openGLView;
    };
}

#endif /* SGDirector_hpp */
