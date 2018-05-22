//
//  SGDirectorCaller.m
//  SimpleGameEngine
//
//  Created by Nao on 2018/03/21.
//  Copyright © 2018年 Nao. All rights reserved.
//

#include <memory>
#include "SGDirector.hpp"
#import <UIKit/UIKit.h>
#import <mach/mach_time.h>
#import "SGDirectorCaller.h"
#import "SGEAGLView.h"
#import <GLKit/GLKit.h>

static id s_sharedDirectorCaller;

@implementation SGDirectorCaller

@synthesize interval;

+ (id) sharedDirectorCaller
{
    if (s_sharedDirectorCaller == nil) {
        s_sharedDirectorCaller = [[SGDirectorCaller alloc] init];
    }
    return s_sharedDirectorCaller;
}

- (instancetype)init
{
    if (self = [super init]) {
        isAppActive = [UIApplication sharedApplication].applicationState == UIApplicationStateActive;
        NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];
        [nc addObserver:self selector:@selector(appDidBecomeActive) name:UIApplicationDidBecomeActiveNotification object:nil];
        [nc addObserver:self selector:@selector(appDidBecomeInactive) name:UIApplicationWillResignActiveNotification object:nil];
        self.interval = 1 / 60.0f;
        
        
    }
    return self;
}

- (void) startMainLoop
{
    [self stopMainLoop];
    
    displayLink = [NSClassFromString(@"CADisplayLink") displayLinkWithTarget:self selector:@selector(doCaller:)];
    [displayLink setPreferredFramesPerSecond:self.interval];
    [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
}

- (void) stopMainLoop
{
    [displayLink invalidate];
    displayLink = nil;
}

- (void) setAnimationInterval:(double)intervalNew
{
    [self stopMainLoop];
    
    self.interval = 60.0 * intervalNew;
    
    displayLink = [NSClassFromString(@"CADisplayLink") displayLinkWithTarget:self selector:@selector(doCaller:)];
    [displayLink setPreferredFramesPerSecond:self.interval];
    [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
}

- (void) doCaller: (id) sender
{
    auto director = SimpleGameEngine::Director::getInstance();
    std::shared_ptr<SimpleGameEngine::GLView> glView = director->getOpenGLView();
    
    SGEAGLView* saglView = (__bridge SGEAGLView *)glView->getEAGLView();
    EAGLContext* sgContext = [saglView renderingContext];
    if (sgContext != [EAGLContext currentContext]) {
        glFlush();
    }
    [EAGLContext setCurrentContext: sgContext];
    
    CFTimeInterval dt = ((CADisplayLink*)displayLink).timestamp - lastDisplayTime;
    lastDisplayTime = ((CADisplayLink*)displayLink).timestamp;
    director->mainloop(dt);
    
    [saglView postFrontBuffer];

}

- (void)appDidBecomeActive
{
    [self initLastDisplayTime];
    
    isAppActive = YES;
}

- (void)appDidBecomeInactive
{
    isAppActive = NO;
}

-(void)initLastDisplayTime
{
    struct mach_timebase_info timeBaseInfo;
    mach_timebase_info(&timeBaseInfo);
    CGFloat clockFrequency = (CGFloat)timeBaseInfo.denom / (CGFloat)timeBaseInfo.numer;
    clockFrequency *= 1000000000.0;
    // convert absolute time to seconds and should minus one frame time interval
    lastDisplayTime = (mach_absolute_time() / clockFrequency) - ((1.0 / 60) * self.interval);
}

- (void) dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

@end
