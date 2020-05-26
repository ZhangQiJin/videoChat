//
//  AVDLivecast.h
//  avd_sdk
//
//  Created by skin on 15-7-21.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#ifndef avd_sdk_AVDLivecast_h
#define avd_sdk_AVDLivecast_h

#import "AVDCommon.h"
#import "AVDVideoView.h"
#import "AVDEasyRoom.h"
#import "AVDFakeVideoCapturer.h"
#import "AVDFakeAudioCapturer.h"

/** 客户端直播状态定义 
 *
 * @note 状态迁移图
 *
 *                     [success]                                       [success]
 *      1.init -----(init)--> 2.connecting --> 3.ready ------(publishRTMP)--> 4.livecast
 *       A     <--[failed]                         |   <--[failed]              |
 *       |                                         |                            |
 *       |                                         | [conn loss]     [conn loss]|
 *       |                                         --------> 5.reconnecting <----
 *       |                                         <---------      |       ------>
 *       |                                       [reconnected]     |       [reconnected]
 *        ----------------------------------------------------------
 *                          [reconnect failed]
 */
enum AVDLivecastStatus {
    lc_init,							/**< 初始状态 */
    lc_connecting,						/**< 正在连接服务器 */
    lc_ready,							/**< 视频可以预览，准备好可以直播  */
    lc_livecast,						/**< 正在直播  */
    lc_reconnecting,					/**< 正在与服务器重连接  */
};

/**
 * 直播回调接口类
 *
 * 直播回调接口定义了直播对象操作的异步返回，直播状态通知等。
 */
@protocol AVDLivecastDelegate<NSObject>
/// 通知
/** 直播流状态更改通知
 *
 * @param[in] status 当前直播状态。
 * @note 开始推流时，会每间隔 3s 调用该回调方法来反馈该 3s 内的流状态，包括视频帧率、音频帧率、音视频总码率
 */
- (void) onStatus:(enum AVDLivecastStatus)status;
/** 直播网络状态通知
 *
 * @param[in] status 当前网络状态。
 */
- (void) onConnectionStatus:(enum AVDConnectionStatus)status;
/** 直播错误通知
 *
 * @param[in] error 错误码
 * @param[in] message 错误消息
 */
- (void) onError:(AVDResult)error message:(NSString*)message;

@end
@protocol AVDStreamStatsDelegate<NSObject>
/// 通知
/** 间隔 3s 调用该回调方法来反馈该 3s 内的流状态，包括视频帧率、音视频总码率
 *
 * @param[in] videofps 视频帧率。
 * @param[in] avbps	  音视频总码率: kbps。
 */
- (void) onStreamlast3Stats:(NSUInteger)videofps avbps:(NSUInteger)avbps;

@end

/**
 * 直播接口类
 *
 * 直播接口定义了直播对象创建和释放、直播功能操作。
 */
@interface AVDLivecast : NSObject
@property (nonatomic,weak) id <AVDLivecastDelegate> delegate;           /**< 直播回调代理 */
@property (nonatomic,weak) id <AVDStreamStatsDelegate> streamStatsdelegate; /**< 直播推流状态回调代理 */
@property (nonatomic,retain) AVDVideoParams *videoParams;               /**< 视频参数 */
@property (nonatomic,retain) AVDAudioParams *audioParams;               /**< 音频参数 */
@property (nonatomic,assign,readonly) enum AVDLivecastStatus status;    /**< 直播状态 */
@property (nonatomic,assign,readonly) BOOL isMicrophoneMute;            /**< 麦克风是否mute状态 */

/** 设置直播Id
 * @return 返回错误代码。
 * @note 直播Id唯一标识一个直播，设置后才能使用直播接口。
 */
+ (AVDResult)setLivecastId:(AVDRoomId)castId;
/** 获取直播接口
 * @return 返回直播接口指针。
 * @note 当前需要先设置直播Id，后才能使用下面所有接口。
 * @sa setLivecastId
 */
+ (AVDLivecast*) instance;
/** 释放直播接口
 */
+ (void) destory;

/** 直播对象初始化
 *
 * @return 返回错误代码。
 */
- (AVDResult) initContext;
/** 直播对象反初始化
 * @return 返回错误代码。
 */
- (AVDResult) uninit;


/** 设置视频显示窗口
 * @param[in] render 本地预览render接口。
 * @return 返回错误代码。
 * @sa IVideoRender
 */
- (AVDResult) setDisplayView:(id<AVDVideoRenderer>)render;

/** 设置视频外部导入数据源
 *
 * @param[in] vcapturer 视频外部导入数据源。
 * @return 返回错误代码。
 * @sa FakeVideoCapturer
 */
- (AVDResult) setVideoSource:(AVDFakeVideoCapturer*)vcapturer;
/** 设置音频外部导入数据源
 *
 * @param[in] acapturer 音频外部导入数据源。
 * @return 返回错误代码。
 * @sa FakeAudioCapturer
 */
- (AVDResult) setAudioSource:(AVDFakeAudioCapturer*)acapturer;

/** 预览本地缺省摄像头视频
 * @return 返回错误代码。
 */
- (AVDResult) startPreview;
/** 取消预览缺省摄像头视频
 * @return 返回错误代码。
 */
- (AVDResult) stopPreview;
/** 视频切换摄像头
 * @return 返回错误代码。
 */
- (AVDResult) switchCamera;

/** 本地麦克风静默
 * @return 返回错误代码。
 */
- (AVDResult) muteMicrophone;
/** 本地麦克风静默取消
 * @return 返回错误代码。
 */
- (AVDResult) unmuteMicrophone;

/** 抓取直播图像
 *
 * @param[in] quality  图像质量：0-100, 0最差，100最好。
 * @return 返回错误代码。
 * @note 目前在直播状态下，播放端无法抓取视频（rtmp播放器播放的时候）
 */
- (AVDResult) captureImage:(NSInteger)quality;

/** 开始直播
 *
 * @param[in] pushUrl 直播rtmp推流地址。
 * @return 返回错误代码。
 */
- (AVDResult) publisRTMP:(NSString*)pushUrl;
/** 停止直播
 *
 * @return 返回错误代码。
 */
- (AVDResult) unpublish;


/** 判断是否正在连麦中
 * @return 是否正在连麦。
 */
- (BOOL) isInRoom;
/** 直播开始连麦
 *
 * @param[in] room 互动房间接口。
 * @return 返回错误代码。
 * @note   互动房间通过创建IEasyRoom操作，需要先创建IEasyRoom接口，然后与直播接口进行挂接
 * 直播互动挂接，系统内部会实现以下缺省操作：
 *				1. 自动挂接直播的采集音视频流到房间的采集音视频流
 *				2. 自动挂接房间的合屏视频流和混音音频流到直播推送音视频流
 * @sa IEasyRoom
 */
- (AVDResult) attachRoom:(AVDEasyRoom*)room;
/** 直播停止连麦
 * @return 返回错误代码。
 */
- (AVDResult) detachRoom;


/** 设置房间选项
 *
 * @param[in] type 房间选项类型。
 * @param[in] svalue 选项内容，根据选项说明填入。
 * @return 返回错误代码。
 */
- (AVDResult) setOption:(enum AVDRoomOption)type value:(NSString*)svalue;
/** 获取房间选项
 *
 * @param[in] type 房间选项类型。
 * @return 返回选项内容，根据选项说明解析。
 */
- (NSString*) getOption:(enum AVDRoomOption)type;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Disallow init and don't add to documentation
- (id)init __attribute__((
    unavailable("init is not a supported initializer for this class.")));
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

@end

#endif
