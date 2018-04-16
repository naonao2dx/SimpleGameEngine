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
#include <chrono>
#include "SGGLView.h"
#include "../renderer/SGRenderer.hpp"

namespace SimpleGameEngine {
    class Director
    {
    public:
        static std::shared_ptr<Director> getInstance();
        void setOpenGLView(std::shared_ptr<GLView> openGLView);
        std::shared_ptr<GLView> getOpenGLView() { return _openGLView; };
        void mainloop();
        void mainloop(float dt);
        void drawScene();
        
        std::unique_ptr<Renderer> _renderer;
    private:
        Director() = default;
        bool init();
        
    protected:
        void calculateDeltaTime();
        float _deltatime;
        bool _deltaTimePassedByCaller;
        bool _nextDeltaTimeZero;
        std::chrono::steady_clock::time_point _lastUpdate;
        
        std::shared_ptr<GLView> _openGLView;
    };
}

#endif /* SGDirector_hpp */
