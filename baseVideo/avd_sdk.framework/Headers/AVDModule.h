//
//  AVDModule.h
//  avd_sdk
//
//  Created by skin on 15-9-19.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#import "AVDRoom.h"
#import "AVDUserManager.h"

/**
 * 功能模块类型.
 */
enum AVDModuleType
{
    mt_chat,                                                    /**< 聊天模块类型  */
    mt_audio,                                                   /**< 语音模块类型  */
    mt_video,                                                   /**< 视频模块类型  */
    mt_screen,                                                  /**< 屏幕共享模块类型  */
    mt_whiteboard,                                              /**< 白板模块类型  */
    mt_annotation,                                              /**< 注释模块类型  */
    mt_streamExporter,                                          /**< 录制模块类型  */

};

@interface AVDModule : NSObject

@property(nonatomic, weak, readonly)AVDRoom* room;              /**< 房间对象指针  */
@property(nonatomic, weak, readonly)AVDUserManager* usermanager;/**< 用户管理模块指针  */
@property(nonatomic, assign, readonly)enum AVDModuleType type;  /**< 模块类型  */

/** 判断是否是自己的用户Id
 * @param[in] userId 用户Id
 * @return 返回是否是自己。
 */
- (BOOL) isSelfUser:(AVDUserId)userId;

/** 判断是否是自己的设备Id
 * @param[in] deviceId 设备Id
 * @return 返回是否是自己。
 */
- (BOOL) isSelfDevice:(AVDDeviceId)deviceId;

/** 获取设备Id的关联用户Id
 * @param[in] deviceId 设备Id
 * @return 返回用户Id。
 */
- (AVDUserId)getOwnerId:(AVDDeviceId)deviceId;

/** 获取设备Id的关联用户名称
 * @param[in] deviceId 设备Id
 * @return 返回用户名称。
 */
- (NSString*)getOwnerName:(AVDDeviceId)deviceId;

@end
