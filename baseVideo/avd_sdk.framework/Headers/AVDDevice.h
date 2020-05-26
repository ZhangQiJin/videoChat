//
//  AVDDevice.h
//  avd_sdk
//
//  Created by skin on 15-9-19.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#import "AVDCommon.h"

/**
 * 设备状态.
 */
enum AVDDeviceStatus
{
    ds_none,                                                /**< 无设备状态（如设备被拔出等） */
    ds_ready,                                               /**< 设备初始化状态  */
    ds_published,                                           /**< 设备打开发布状态  */
    ds_muted,                                               /**< 设备静默状态  */
};

/**
 * 设备信息结构.
 *
 * 设备信息结构定义了设备基本信息，此处设备包括麦克风、扬声器、摄像头和屏幕窗口。
 */
@interface AVDDevice : NSObject

@property(nonatomic, strong, readonly) AVDDeviceId id;      /**< 设备Id，唯一标识一个设备  */
@property(nonatomic, strong, readonly) NSString* name;      /**< 设备名称，应用层可用于设备显示  */
@property(nonatomic, assign) enum AVDDeviceStatus status;   /**< 设备状态  */

- (instancetype) initWithId:(AVDDeviceId)did name:(NSString*)name;
/**
 * 判断设备对象是否有效 */
- (BOOL) isValid;
- (void) updateName:(NSString*)name;

@end
