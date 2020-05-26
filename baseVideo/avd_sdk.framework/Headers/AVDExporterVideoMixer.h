//
//  AVDExporterVideoMixer.h
//  avd_sdk
//
//  Created by 盛锋 on 2018/6/26.
//  Copyright © 2018年 t3ee. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AVDCommon.h"

@interface AVDExporterVideoMixer : NSObject

/**
 *  添加视频布局
 *
 *  @param deviceId deviceId视频流id
 *  @param zorder   层级
 *  @param x        0-1.0 x 坐标 example 屏幕宽320 布局在x为160 时 x = 0.5
 *  @param y        0-1.0 x 坐标 example 屏幕宽320 布局在x为160 时 x = 0.5
 *  @param width    0-1.0  example 屏幕宽320 布局在宽为100 时 x = 100/320
 *  @param height   0-1.0  example 屏幕高640 布局在x为160 时 x = 160/640
 *
 *  @return 错误代码
 */
- (AVDResult)addSubVideo:(AVDDeviceId)deviceId zorder:(NSInteger)zorder x:(float)x y:(float)y width:(float)width height:(float)height;


/**
 *  修改视频布局
 *
 *  @param deviceId deviceId视频流id
 *  @param zorder   层级
 *  @param x        0-1.0 x 坐标 example 屏幕宽320 布局在x为160 时 x = 0.5
 *  @param y        0-1.0 x 坐标 example 屏幕宽320 布局在x为160 时 x = 0.5
 *  @param width    0-1.0  example 屏幕宽320 布局在宽为100 时 x = 100/320
 *  @param height   0-1.0  example 屏幕高640 布局在x为160 时 x = 160/640
 *
 *  @return 错误代码
 */
- (AVDResult)modSubVideo:(AVDDeviceId)deviceId zorder:(NSInteger)zorder x:(float)x y:(float)y width:(float)width height:(float)height;


/**
 *  移除指定视频布局
 *
 *  @param deviceId 视频id
 *
 *  @return 错误代码
 */
- (BOOL)removeSubVideo:(AVDDeviceId)deviceId;


/**
 *  清空所有视频布局
 */
- (void)clearSubVideos;

@end
