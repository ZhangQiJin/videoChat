//
//  AVDVideoParams.h
//  avd_sdk
//
//  Created by skin on 15-9-19.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AVDCameraCapability.h"

/**
 * 视频参数信息结构.
 *
 * 视频参数结构定义了视频采集相关参数，包含视频分辨率和帧率。
 */
@interface AVDVideoParams : AVDCameraCapability
@property(nonatomic, assign) BOOL usedFront;            /**< 开启时是否使用前置摄像头  */

- (instancetype) initWithWidth:(NSInteger)w height:(NSInteger)h fps:(NSInteger)fps;

@end
