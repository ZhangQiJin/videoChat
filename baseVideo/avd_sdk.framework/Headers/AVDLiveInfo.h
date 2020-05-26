//
//  AVDLiveInfo.h
//  avd_sdk
//
//  Created by skin on 15-9-19.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#import "AVDCommon.h"
#import "AVDRecordInfo.h"

/** 直播状态定义 */
enum AVDLiveStatus {
    ls_created,							/**< 创建直播 */
    ls_living,							/**< 正在直播 */
    ls_stopped,							/**< 直播暂停  */
    ls_removed,							/**< 直播被删除  */
    ls_exception,						/**< 直播异常 */
};

/**
 * 直播数据结构.
 *
 * 直播数据定义了一个直播的基本信息。
 */
@interface AVDLiveInfo : NSObject

@property(nonatomic, strong, readonly) AVDLiveId id;        /**< 直播ID */
@property(nonatomic, strong) NSString* name;                /**< 直播的名称 */
@property(nonatomic, strong) NSString* adescription;        /**< 直播描述 */
@property(nonatomic, strong) NSString* tags;                /**< 直播标记 */
@property(nonatomic, strong) NSString* userId;      /**< 用户号，可不存在，存在时与audioType，videoType一起使用；直播此用户的相关音频和视频数据 */
@property(nonatomic, strong) NSString* roomId;              /**< 频道关联房间号 */
@property(nonatomic, strong, readonly) NSString* publishurl;/**< 推流地址，创建时可带上，若存在，服务器优先推送此地址 */
@property(nonatomic, strong, readonly) NSString* rtmpurl;	/**< 播放rtmp链接 */
@property(nonatomic, strong, readonly) NSString* hlsurl;	/**< 播放hls链接 */
@property(nonatomic, strong, readonly) NSString* createTime;/**< 直播创建起始时间 */
@property(nonatomic, assign) enum AVDRecordAudioType audioType;	/**< 音频类型 */
@property(nonatomic, assign) enum AVDRecordVideoType videoType;	/**< 视频类型 */
@property(nonatomic, assign, readonly) NSInteger size;		/**< 直播文件大小 */
@property(nonatomic, assign, readonly) NSInteger duration;	/**< 直播从创建到现在的时长 */
@property(nonatomic, assign, readonly) enum AVDLiveStatus status;	/**< 直播状态 */

/**
 * 判断对象是否有效 */
- (BOOL) isValid;

@end
