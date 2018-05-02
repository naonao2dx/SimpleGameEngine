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
#include "../Renderer/SGRenderer.hpp"
#include "SGBaseScene.hpp"

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
        void startScene(std::shared_ptr<Scene> scene);
        void setDesignResolutionSize(Size designResolutionSize);
        inline Size getDesignResolutionSize() const { return _designResolutionSize; };
        
        std::shared_ptr<Renderer> _renderer = nullptr;
    private:
        Director(){};
        bool init();
        
        std::shared_ptr<Scene> _nextScene = nullptr;
        std::shared_ptr<Scene> _currentScene = nullptr;
        Size _designResolutionSize;
        
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
