//
//  AVDUserStatus.h
//  avd_sdk
//
//  Created by skin on 15-9-18.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#ifndef avd_sdk_AVDUserStatus_h
#define avd_sdk_AVDUserStatus_h

#import "AVDCommon.h"

enum AVDStatusFlag
{
    microphone_has = 1 << 31,			/**< 拥有麦克风设置位  */
    microphone_on = 1 << 30,			/**< 麦克风打开设置位  */
    camera_has = 1 << 29,				/**< 拥有摄像头设置位  */
    camera_on = 1 << 28,				/**< 摄像头打开设置位  */
    screen_on = 1 << 25,				/**< 屏幕窗口共享设置位  */
    
    status_all = 0xFFFFFFFF,			/**< 所有用户状态位  */
};

/**
	* 用户状态结构.
	*
	* 用户状态定义了用户的各种状态集合信息。
	*/
@interface AVDUserStatus : NSObject

@property(nonatomic, readonly)NSInteger status;


/** 判断是否有麦克风设备 */
- (BOOL) hasMicrophone;
/** 判断是否有摄像头设备 */
- (BOOL) hasCamera;
/** 判断是否麦克风已打开 */
- (BOOL) isMicrophoneOn;
/** 判断是否摄像头已打开 */
- (BOOL) isCameraOn;
/** 判断是否屏幕窗口共享已开启 */
- (BOOL) isScreenOn;
/** 设置用户状态
 *
 * @param[in] flag 添加的用户状态。
 *
 * @note 添加用户状态是在原有用户状态上添加用户状态；
 * @sa Status
 */
- (void) setFlag:(enum AVDStatusFlag)flag;
/** 清理用户状态
 *
 * @param[in] flag 用户信息数据。
 *
 * @note 清理部分用户状态；
 * @sa Status
 */
- (void) clearFlag:(enum AVDStatusFlag)flag;


@end

#endif
