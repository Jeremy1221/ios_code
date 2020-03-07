//
//  HXCustomNavigationController.m
//  微博照片选择
//
//  Created by 洪欣 on 2017/10/31.
//  Copyright © 2017年 洪欣. All rights reserved.
//

#import "HXCustomNavigationController.h"
#import "UIView+letad_Frame.h"

@interface HXCustomNavigationController ()

@end

@implementation HXCustomNavigationController

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (BOOL)shouldAutorotate{
    return !self.isCamera;
}

//支持的方向
- (UIInterfaceOrientationMask)supportedInterfaceOrientations {
    return self.isCamera ? UIInterfaceOrientationMaskPortrait : UIInterfaceOrientationMaskAll;
}
@end
