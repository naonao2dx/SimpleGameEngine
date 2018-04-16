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
#import "../../base/SGApplication.hpp"

@implementation AppController

@synthesize window;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    auto app = SimpleGameEngine::Application::getInstance();
    
    // Add main window and set its viewController
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    _viewController = [[RootViewController alloc] init];
    [window setRootViewController:_viewController];
    [window makeKeyAndVisible];
    [_viewController prefersStatusBarHidden];
    
    //void* openGLView = (__bridge void *)_viewController.view;
    std::shared_ptr<SimpleGameEngine::GLView> glView = SimpleGameEngine::GLView::createWithEAGLView((__bridge void *)_viewController.view);
    auto director = SimpleGameEngine::Director::getInstance();
    director->setOpenGLView(glView);
    
    app->run();
    
    return YES;
}

@end
