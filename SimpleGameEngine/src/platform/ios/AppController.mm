//
//  AppController.m
//  SimpleGameEngine
//
//  Created by Nao on 2018/03/21.
//  Copyright © 2018年 Nao. All rights reserved.
//
#import "AppController.h"
#import "RootViewController.h"
#import "../../base/SGDirector.hpp"
#import "../../base/SGGLView.h"

@implementation AppController

@synthesize window;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // Add main window and set its viewController
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    _viewController = [[RootViewController alloc] init];
    [window setRootViewController:_viewController];
    [window makeKeyWindow];
    [_viewController prefersStatusBarHidden];
    
    //void* openGLView = (__bridge void *)_viewController.view;
    std::shared_ptr<SimpleGameEngine::GLView> glView = SimpleGameEngine::GLView::createWithEAGLView((__bridge void *)_viewController.view);
    SimpleGameEngine::Director::getInstance()->setOpenGLView(glView);
    return YES;
}

@end
