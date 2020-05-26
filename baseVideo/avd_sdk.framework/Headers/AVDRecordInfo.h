//
//  AVDRecordInfo.h
//  avd_sdk
//
//  Created by skin on 15-9-19.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#import "AVDCommon.h"

/** 录制音频类型定义 */
enum AVDRecordAudioType {
    ra_none,							/**< 无音频  */
    ra_user_single,						/**< 同视频用户的单用户音频  */
    ra_user_all,						/**< 整个房间中的所有音频混音  */
};
/** 录制视频类型定义 */
enum AVDRecordVideoType {
    rv_none,							/**< 无视频  */
    rv_main,							/**< 视频主流  */
    rv_ass1,							/**< 视频辅流1  */
    rv_ass2,							/**< 视频辅流2  */
};
/** 媒体文件类型定义 */
enum AVDMediaFileType {
    mt_mp4,								/**< MP4 文件格式，支持h264视频和aac音频封装  */
    mt_webm,							/**< WebM文件格式，支持vp8视频和opus音频封装  */
};
/** 录制状态定义 */
enum AVDRecordStatus {
    rs_created,							/**< 创建录制  */
    rs_recording,						/**< 正在录制（如果相应视频和音频流上传服务器，就会保持到录制中；如没数据也无录制） */
    rs_availble,						/**< 录制完成可查看  */
    rs_removed,							/**< 录制被删除  */
    rs_exception,						/**< 录制异常（如不完整等） */
};

/**
 * 录制数据结构.
 *
 * 录制数据定义了一个录制的基本信息。
 */
@interface AVDRecordInfo : NSObject

@property(nonatomic, strong, readonly) AVDRecordId id;      /**< 录制ID */
@property(nonatomic, strong) NSString* name;                /**< 录制的名称 */
@property(nonatomic, strong) NSString* adescription;        /**< 录制描述 */
@property(nonatomic, strong) NSString* tags;                /**< 录制标记 */
@property(nonatomic, strong) NSString* userId;      /**< 用户号，可不存在，存在时与audioType，videoType一起使用；录制此用户的相关音频和视频数据 */
@property(nonatomic, strong) NSString* roomId;              /**< 频道关联房间号 */
@property(nonatomic, strong, readonly) NSString* url;		/**< 播放录制链接 */
@property(nonatomic, strong, readonly) NSString* createTime;/**< 录制创建起始时间 */
@property(nonatomic, assign, readonly) enum AVDMediaFileType fileType;	/**< 媒体文件类型 */
@property(nonatomic, assign) enum AVDRecordAudioType audioType;	/**< 音频类型 */
@property(nonatomic, assign) enum AVDRecordVideoType videoType;	/**< 视频类型 */
@property(nonatomic, assign, readonly) NSInteger size;		/**< 录制文件大小 */
@property(nonatomic, assign, readonly) NSInteger duration;	/**< 录制从创建到现在的时长 */
@property(nonatomic, assign, readonly) enum AVDRecordStatus status;	/**< 录制状态 */

/**
 * 判断对象是否有效 */
- (BOOL) isValid;

@end
