//
//  SGEAGLView.h
//  SimpleGameEngine
//
//  Created by Nao on 2018/03/21.
//  Copyright © 2018年 Nao. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <OpenGLES/ES2/gl.h>

@interface SGEAGLView : UIView
{
    EAGLContext *renderingContext;
    GLuint frameBuffer;
    GLuint colorBuffer;
    GLuint depthStencilBuffer;
    GLint renderingWidth;
    GLint renderingHeight;
    BOOL initialized;
}

@property (readonly) GLint renderingWidth;
@property (readonly) GLint renderingHeight;

+ (id) viewWithFrame:(CGRect)frame;
- (EAGLContext*) renderingContext;
- (void) postFrontBuffer;
- (void) unbindGL;
- (BOOL) ready;

- (int) getWidth;
- (int) getHeight;

@end
