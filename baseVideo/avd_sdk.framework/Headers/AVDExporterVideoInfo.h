//
//  AVDExporterVideoInfo.h
//  avd_sdk
//
//  Created by 盛锋 on 2018/6/22.
//  Copyright © 2018年 t3ee. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AVDCommon.h"

@interface AVDExporterVideoInfo : NSObject

@property (nonatomic,copy)AVDDeviceId deviceId;///<摄像头Id，唯一标示一路共享的摄像头视频。
//此视频在左上角左边位置（上边位置），即x坐标，取值0.0~1.0，内部取值为：width * X（height * Y）
@property (nonatomic,assign)float x;
@property (nonatomic,assign)float y;
//此视频宽度（高度）比例，取值0.0~1.0，内部取值为：width * W（height * H）
@property (nonatomic,assign)float width;
@property (nonatomic,assign)float height;
//多个视频覆盖时，前后位置，zorder越小，视频越在下层，会被覆盖；取值0-10
@property (nonatomic,assign)NSInteger zorder;
//（暂不使用）透明度
@property (nonatomic,assign)float alpha;

@end
