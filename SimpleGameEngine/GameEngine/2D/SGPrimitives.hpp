//
//  SGPrimitives.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/04/17.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGPrimitives_hpp
#define SGPrimitives_hpp

#include "../Base/SGNode.hpp"

namespace SimpleGameEngine {
    class Primitives : public Node
    {
    public:
        Primitives();
        void setShape(GLenum shape);
        void setLineWidth(GLfloat lineWidth);
        void setShaderPositionAndColor();
    protected:
        virtual bool init() override;
        virtual void draw() override;
    private:
        GLenum _shape;
        GLfloat _lineWidth;
    };
}

#endif /* SGPrimitives_hpp */
