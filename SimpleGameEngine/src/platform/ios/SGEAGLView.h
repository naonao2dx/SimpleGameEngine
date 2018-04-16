//
//  SGEAGLView.h
//  SimpleGameEngine
//
//  Created by Nao on 2018/03/21.
//  Copyright © 2018年 Nao. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface SGEAGLView : UIView
{
    EAGLContext *context_; // weak ref
}

@property(nonatomic,readonly) EAGLContext *context;

+ (id) viewWithFrame:(CGRect)frame;

- (int) getWidth;
- (int) getHeight;

- (void) update;

@end