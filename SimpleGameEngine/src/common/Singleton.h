//
//  Singleton.h
//  SimpleGameEngine
//
//  Created by Nao on 2018/03/21.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef Singleton_h
#define Singleton_h

#include <memory>

template <typename T> class Singleton {
protected:
    Singleton() {};
    
public:
    virtual ~Singleton() {};
    
    Singleton(Singleton const&) = delete;
    Singleton& operator=(Singleton const&) = delete;
    
public:
    static std::shared_ptr<T> getInstance() {
        auto retPtr = pInstance.lock();
        if (!retPtr) {
            retPtr = std::shared_ptr<T>(new T{});
            pInstance = std::weak_ptr<T>(retPtr);
            return retPtr;
        }
        return pInstance.lock();
    }
    
private:
    static std::weak_ptr<T> pInstance;
};

template <typename T> std::weak_ptr<T> Singleton<T>::pInstance;

#endif /* Singleton_h */
