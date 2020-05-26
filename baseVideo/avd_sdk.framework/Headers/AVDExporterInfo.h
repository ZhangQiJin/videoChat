//
//  AVDExporterInfo.h
//  avd_sdk
//
//  Created by 盛锋 on 2018/6/22.
//  Copyright © 2018年 t3ee. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AVDCommon.h"

@interface AVDExporterInfo : NSObject

@property (nonatomic, copy)NSString *recordId;/**< 录制(直播频道)ID */
@property (nonatomic, copy)AVDRoomId roomId;/**< 关联房间号 */
@property (nonatomic, copy)AVDUserId creatorId;/**< 创建者用户ID */
@property (nonatomic, copy)NSString *name;/**< 名称 */
@property (nonatomic, copy)NSString *appdata;/**< 应用自定义数据, json */
@property (nonatomic, copy)NSString *createTime;/**< 创建起始时间 */
@property (nonatomic, assign)NSInteger status;/**< 状态 */
@property (nonatomic, assign)NSInteger size;/**< 录制：录制文件大小*   直播：直播当前时长*/
/**
 * < 录制：文件名称
 *	 直播：推流地址；
 */
@property (nonatomic, copy)NSString *desturl;
/**< 
 *   录制：播放录制链接列表,可能多个文件,如录制mp4视频分辨率变化会产生多个文件
 *	 直播：推流地址，和播放地址；根据url协议确定地址用途：如rtmp是推流和播放地址；htl是播放地址；
 */
@property (nonatomic, copy)NSString *playurls;



@end
