//
//  SGEAGLView.m
//  SimpleGameEngine
//
//  Created by Nao on 2018/03/21.
//  Copyright © 2018年 Nao. All rights reserved.
//

#import "SGEAGLView.h"
#import <OpenGLES/ES2/gl.h>

@implementation SGEAGLView

@synthesize context=context_;

+ (Class) layerClass
{
    return [CAEAGLLayer class];
}

+ (id) viewWithFrame:(CGRect)frame
{
    return [[self alloc] initWithFrame:frame];
}

- (instancetype)initWithFrame:(CGRect)frame {
    if ((self = [super initWithFrame:frame])) {
        [self setupOpenGL];
    }
    return self;
}

- (int) getWidth
{
    CGSize bound = [self bounds].size;
    return (int)bound.width * self.contentScaleFactor;
}

- (int) getHeight
{
    CGSize bound = [self bounds].size;
    return (int)bound.height * self.contentScaleFactor;
}

- (void) layoutSubviews {
    // Set ViewPort
    glViewport(0, 0, self.frame.size.width, self.frame.size.height);
}

- (void) setupOpenGL {
    NSLog(@"SGEAGLView::setupOpenGL");
    // Layer setup
    CAEAGLLayer *layer = (CAEAGLLayer*) self.layer;
    layer.opaque = YES;
    
    // Context object setup
    context_ = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    [EAGLContext setCurrentContext:context_];
    
    // Render buffer setup
    GLuint renderBuffer;
    glGenRenderbuffers(1, &renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    [context_ renderbufferStorage:GL_RENDERBUFFER fromDrawable:layer];
    
    // Frame buffer setup
    GLuint frameBuffer;
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderBuffer);
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

@end
