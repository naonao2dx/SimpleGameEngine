//
//  SGEAGLView.m
//  SimpleGameEngine
//
//  Created by Nao on 2018/03/21.
//  Copyright © 2018年 Nao. All rights reserved.
//

#import "SGEAGLView.h"
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#define MAX_TOUCH_COUNT 5

@implementation SGEAGLView

@synthesize renderingWidth;
@synthesize renderingHeight;

+ (Class) layerClass
{
    return [CAEAGLLayer class];
}

- (EAGLContext*) renderingContext
{
    return renderingContext;
}

+ (id) viewWithFrame:(CGRect)frame
{
    return [[self alloc] initWithFrame:frame];
}

- (instancetype)initWithFrame:(CGRect)frame {
    if ((self = [super initWithFrame:frame])) {
        CAEAGLLayer *layer = (CAEAGLLayer*) self.layer;
        layer.opaque = YES;
        layer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                     [NSNumber numberWithBool:FALSE], kEAGLDrawablePropertyRetainedBacking,
                                     kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
        [self initializeEAGL];
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
    [super layoutSubviews];
    @synchronized(self) {
        if(![self ready]) {
            
        }
    }
    [self resizeRenderBuffer];
    [self unbindGL];
    
    initialized = YES;
}

- (void) initializeEAGL {
    self.contentScaleFactor = [UIScreen mainScreen].scale;
    
    // Context object setup
    renderingContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    {
        BOOL current = [EAGLContext setCurrentContext:renderingContext];
        assert(current == YES);
    }
    
    // Color buffer setup
    glGenRenderbuffers(1, &colorBuffer);
    
    // Depth and Stencil buffer setup
    glGenRenderbuffers(1, &depthStencilBuffer);
    assert(depthStencilBuffer);
    
    // Frame buffer setup
    glGenFramebuffers(1, &frameBuffer);
    
}

- (void) resizeRenderBuffer
{
    {
        const BOOL current = [EAGLContext setCurrentContext:renderingContext];
        assert(current == YES);
    }
    
    const float scaleFactor = [self contentScaleFactor];
    renderingWidth = (int)(self.bounds.size.width * scaleFactor);
    renderingHeight = (int)(self.bounds.size.height * scaleFactor);
    
    {
        glBindRenderbuffer(GL_RENDERBUFFER, colorBuffer);
        const BOOL complete = [renderingContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:
                               (CAEAGLLayer*)self.layer];
        assert(complete == YES);
    }
    
    glGetRenderbufferParameteriv(GL_RENDERBUFFER,  GL_RENDERBUFFER_WIDTH, &renderingWidth);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER,  GL_RENDERBUFFER_HEIGHT, &renderingHeight);
    
    {
        glBindRenderbuffer(GL_RENDERBUFFER, depthStencilBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8_OES, renderingWidth, renderingHeight);
        
        GLint   depthStencilWidth = 0;
        GLint   depthStencilHeight = 0;
        
        glGetRenderbufferParameteriv(GL_RENDERBUFFER,  GL_RENDERBUFFER_WIDTH, &depthStencilWidth);
        glGetRenderbufferParameteriv(GL_RENDERBUFFER,  GL_RENDERBUFFER_HEIGHT, &depthStencilHeight);
        
        assert(depthStencilWidth == renderingWidth);
        assert(depthStencilHeight == renderingHeight);
    }
    
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    assert(glGetError() == GL_NO_ERROR);
    
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthStencilBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthStencilBuffer);
    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
    
    {
        glFinish();
        //const BOOL current = [EAGLContext setCurrentContext:nil];
        //assert(current == YES);
    }
    
    // Set ViewPort
    glViewport(0, 0, renderingWidth, renderingHeight);
}

- (void)postFrontBuffer {
    glBindRenderbuffer(GL_RENDERBUFFER, colorBuffer);
    [renderingContext presentRenderbuffer:GL_RENDERBUFFER];
}

- (void) unbindGL
{
    BOOL current = [EAGLContext setCurrentContext:nil];
    assert(current == TRUE);
}

- (BOOL) ready
{
    return initialized;
}
    
- (void) touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    UITouch* ids[MAX_TOUCH_COUNT] = {0};
    float x[MAX_TOUCH_COUNT] = {0.0f};
    float y[MAX_TOUCH_COUNT] = {0.0f};
    
    int i = 0;
    for (UITouch *touch in touches) {
        if (i >= MAX_TOUCH_COUNT) {
            NSLog(@"touch count is limited");
            break;
        }
        
        ids[i] = touch;
        x[i] = [touch locationInView: [touch view]].x * self.contentScaleFactor;
        y[i] = [touch locationInView: [touch view]].y * self.contentScaleFactor;
        NSLog(@"touch %d began:%f, %f", i, x[i], y[i]);
        ++i;
    }
}
    
- (void) touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    UITouch* ids[MAX_TOUCH_COUNT] = {0};
    float x[MAX_TOUCH_COUNT] = {0.0f};
    float y[MAX_TOUCH_COUNT] = {0.0f};
    
    int i = 0;
    for (UITouch *touch in touches) {
        if (i >= MAX_TOUCH_COUNT) {
            NSLog(@"touch count is limited");
            break;
        }
        
        ids[i] = touch;
        x[i] = [touch locationInView: [touch view]].x * self.contentScaleFactor;
        y[i] = [touch locationInView: [touch view]].y * self.contentScaleFactor;
        NSLog(@"touch %d moved:%f, %f", i, x[i], y[i]);
        ++i;
    }
}
    
- (void) touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    UITouch* ids[MAX_TOUCH_COUNT] = {0};
    float x[MAX_TOUCH_COUNT] = {0.0f};
    float y[MAX_TOUCH_COUNT] = {0.0f};
    
    int i = 0;
    for (UITouch *touch in touches) {
        if (i >= MAX_TOUCH_COUNT) {
            NSLog(@"touch count is limited");
            break;
        }
        
        ids[i] = touch;
        x[i] = [touch locationInView: [touch view]].x * self.contentScaleFactor;
        y[i] = [touch locationInView: [touch view]].y * self.contentScaleFactor;
        NSLog(@"touch %d ended:%f, %f", i, x[i], y[i]);
        ++i;
    }
}
    
- (void) touchesCancelled:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    UITouch* ids[MAX_TOUCH_COUNT] = {0};
    float x[MAX_TOUCH_COUNT] = {0.0f};
    float y[MAX_TOUCH_COUNT] = {0.0f};
    
    int i = 0;
    for (UITouch *touch in touches) {
        if (i >= MAX_TOUCH_COUNT) {
            NSLog(@"touch count is limited");
            break;
        }
        
        ids[i] = touch;
        x[i] = [touch locationInView: [touch view]].x * self.contentScaleFactor;
        y[i] = [touch locationInView: [touch view]].y * self.contentScaleFactor;
        NSLog(@"touch %d cancelled:%f, %f", i, x[i], y[i]);
        ++i;
    }
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

@end
