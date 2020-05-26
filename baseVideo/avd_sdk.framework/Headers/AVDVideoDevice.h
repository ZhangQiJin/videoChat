//
//  AVDVideoDevice.h
//  avd_sdk
//
//  Created by skin on 15-9-19.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#import "AVDCommon.h"
#import "AVDDevice.h"
#import "AVDVideoDeviceOptions.h"
#import "AVDPublishVideoOptions.h"

/**
 * 设备信息结构.
 *
 * 设备信息结构定义了设备基本信息，此处设备包括麦克风、扬声器、摄像头和屏幕窗口。
 */
@interface AVDVideoDevice : AVDDevice

@property(nonatomic, assign) NSInteger level;               /**< 应用层对设备设置的数据，可用于表示视频权重等, 应用层开发可用  */
@property(nonatomic, strong) NSString* adescription;        /**< 应用层对设备的描述，应用层开发可用  */
@property(nonatomic, strong) AVDVideoDeviceOptions* deviceQualities;	 /**< 视频质量类型集：摄像头通知时指摄像头支持视频质量  */
@property(nonatomic, strong) AVDPublishVideoOptions* publishedQualities; /**< 视频质量类型集：publish时是指发布视频的质量，可设置多个值； */

@end
