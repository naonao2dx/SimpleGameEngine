//
//  SGCamera.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/05/24.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGCamera_hpp
#define SGCamera_hpp

#include <OpenGLES/ES2/gl.h>
#include "SGGeometry.hpp"
#include <memory>

namespace SimpleGameEngine {
    class Camera {
    public:
        static std::shared_ptr<Camera> create();
        static std::shared_ptr<Camera> create(Vec3 position, Vec3 look, Vec3 up, GLfloat projectionNear, GLfloat projectionFar, GLfloat projectionFovY);
        void setPosition(Vec3 position);
        void setLook(Vec3 look);
        void setUp(Vec3 up);
        void setProjectionNear(GLfloat projectionNear);
        void setProjectionFar(GLfloat projectionFar);
        void setProjectionFovY(GLfloat projectionForV);
        inline Mat4 getLookAt() { return _lookAt; };
        inline Mat4 getProjection() { return _projection; };
    private:
        Camera(Vec3 position, Vec3 look, Vec3 up, GLfloat projectionNear, GLfloat projectionFar, GLfloat projectionFovY);
        
        Vec3 _position;
        Vec3 _look;
        Vec3 _up;
        Mat4 _lookAt;
        GLfloat _projectionNear;
        GLfloat _projectionFar;
        GLfloat _projectionFovY;
        GLfloat _projectionAspect;
        Mat4 _projection;
        
        
    };
}

#endif /* SGCamera_hpp */
