//
//  SGDirectorCaller.h
//  SimpleGameEngine
//
//  Created by Nao on 2018/03/21.
//  Copyright © 2018年 Nao. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SGDirectorCaller : NSObject {
    id displayLink;
    int interval;
    BOOL isAppActive;
    CFTimeInterval lastDisplayTime;
}
@property (readwrite) int interval;
+ (id) sharedDirectorCaller;

- (void) startMainLoop;
- (void) stopMainLoop;
- (void) doCaller: (id) sender;
- (void) setAnimationInterval: (double) interval;
@end
