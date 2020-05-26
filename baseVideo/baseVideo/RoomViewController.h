///work/code/webrtc_ios_68/src/out_ios_libs/arm64_libs/obj/avd/avd_comm_google.ninja
//  RoomViewController.h
//  baseVideo
//
//  Created by 盛锋 on 2019/5/23.
//  Copyright © 2019年 Elliot. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <avd_sdk/avd_sdk.h>

NS_ASSUME_NONNULL_BEGIN

@interface RoomViewController : UIViewController

@property (strong, nonatomic) AVDRoom *room;

@end

NS_ASSUME_NONNULL_END
