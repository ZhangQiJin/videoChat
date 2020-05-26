//
//  AVDEasyRoom.h
//  avd_sdk
//
//  Created by skin on 15-7-21.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#ifndef avd_sdk_AVDEasyRoom_h
#define avd_sdk_AVDEasyRoom_h

#import "AVDCommon.h"
#import "AVDAudioParams.h"
#import "AVDVideoParams.h"
#import "AVDDevice.h"
#import "AVDUser.h"
#import "AVDRoom.h"
#import "AVDRoomInfo.h"
#import "AVDRoomStats.h"
#import "AVDVideoMixer.h"
#import "AVDVideoRenderer.h"
#import "AVDFakeVideoCapturer.h"
#import "AVDFakeAudioCapturer.h"

/**
 * 异步操作类型.
 */
enum AVDOperateType {
    ot_publishMicrophone = 1,		/**< 房间中分享本地音频  */
    ot_unpublishMicrophone = 2,		/**< 房间中关闭分享本地音频   */
    ot_publishCamera = 3,			/**< 房间中分享本地视频  */
    ot_unpublishCamera = 4,			/**< 房间中关闭分享本地视频  */
    ot_attachRender = 5,			/**< 房间中订阅显示视频  */
    ot_detachRender = 6,			/**< 房间中取消订阅显示视频  */
};

/**
 * 房间中音频混音数据回调接口.
 */
@protocol AVDAudioRenderer<NSObject>
/** 音频格式回调接口
 * @param[in] sampleRate 采样率。
 * @param[in] channels 通道数。
 */
- (void) onAudioParam:(NSUInteger)sampleRate channels:(NSUInteger)channels;
/** 音频数据回调接口
 * @param[in] data 数据存储。
 * @param[in] timestamp_ns 时间戳, nanos second。
 * @sa Room.Option.ro_audio_mixerdata_callback_buffered 单次混音数据回调“10ms数据”还是“1024samples数据”
 */
- (void) onAudioData:(NSData*)data pts:(NSInteger)timestamp_ns;

@end

/**
 * 简易房间回调接口类
 *
 * 简易房间回调接口定义了房间对象操作的异步返回，房间通知，房间指示。
 */
@protocol AVDEasyRoomDelegate<NSObject>
@optional
/** 指示用户离开房间
 *
 * @param[in] reason 离开房间理由代码，正常离开为AVD_OK。
 * @param[in] fromId 指示发起用户Id。
 * @note SDK内部已经开始释放房间资源，应用层可以不调用leave
 * reason:
 * Err_User_DuplicateJoin			用户Id在别处登录，先前同一Id被踢出；
 * Err_User_DataConnection_Failed	数据链接连接失败，用户无法正常使用房间，用户被服务器踢出；
 * 其他								kickoutUser 传入的错误码，被其他用户踢出，应用层自己定义；
 */
- (void)onLeaveIndication:(AVDResult)reason fromUser:(AVDUserId)fromId;
/// 通知
/** 房间网络状态通知
 *
 * @param[in] status 当前网络状态。
 *
 */
- (void)onConnectionStatus:(enum AVDConnectionStatus)status;

/// 通知
/** 透明通道，接收到广播数据通知
 *
 * @param[in] *data 接收到的数据指针。
 * @param[in] fromId 发送方用户Id。
 *
 * @sa sendPublicData
 */
- (void)onPublicData:(NSData*)data fromUser:(AVDUserId)fromId;

/** 透明通道，接收到私有数据通知
 *
 * @param[in] *data 接收到的数据指针。
 * @param[in] fromId 发送方用户Id。
 *
 * @sa sendPrivateData
 */
- (void)onPrivateData:(NSData*)data fromUser:(AVDUserId)fromId;

///
/** 用户加入房间通知
 *
 * @param[in] *user 用户信息数据。
 *
 * @note 某用户调用房间中的join加入房间后，房间内所有用户会接收到此通知
 * @sa join
 */
- (void)onUserJoinNotify:(AVDUser *)user;

/** 用户离开房间通知
 *
 * @param[in] *user 用户信息数据。
 *
 * @note 某用户调用房间中的leave离开房间后，房间内所有用户会接收到此通知
 * @sa leave
 */
- (void)onUserLeaveNotify:(AVDUser *)user;

///
/** 麦克风状态更改通知
 *
 * @param[in] status 麦克风状态。
 * @param[in] fromId 设备关联用户Id。
 * @note 当麦克风状态更改后，房间内所有用户接收到此通知。
 * @sa openMicrophone
 * @sa closeMicrophone
 */
- (void) onMicrophoneStatusNotify:(enum AVDDeviceStatus)status fromUser:(AVDUserId)fromId;
/** 摄像头状态更改通知
 *
 * @param[in] status 摄像头状态。
 * @param[in] fromId 摄像头Id，唯一标示一个摄像头。
 * @note 当摄像头状态更改后，房间内所有用户接收到此通知。
 */
- (void) onCameraStatusNotify:(enum AVDDeviceStatus)status fromUser:(AVDUserId)fromId;

/// 异步返回
/** 异步返回
 * @param[in] type 操作类型。
 * @param[in] result 操作错误代码。
 * @note 当异步操作时,异步返回结果。
 */
- (void) onOperateResult:(enum AVDOperateType)type result:(AVDResult)result;

@end


/**
 * 简易房间接口类
 *
 * 简易房间接口定义了独立的简易房间对象创建和释放、房间功能操作。
 */
@interface AVDEasyRoom : NSObject
@property (nonatomic,weak) id <AVDEasyRoomDelegate>delegate;        /**< 房间逻辑回调代理 */
@property (nonatomic,retain) AVDVideoParams *videoParams;           /**< 视频参数 */
@property (nonatomic,retain) AVDAudioParams *audioParams;           /**< 音频参数 */
@property (nonatomic,retain,readonly) AVDRoomId roomId;             /**< 当前的房间Id */
@property (nonatomic,retain,readonly) AVDRoomInfo *roomInfo;        /**< 当前的房间信息 */
@property (nonatomic,retain,readonly) AVDUserId selfUserId;         /**< 自己的用户ID */
@property (nonatomic,retain,readonly) AVDUser *selfUser;            /**< 自己的用户信息 */
@property (nonatomic,retain,readonly) NSMutableArray* participants; /**< 参会者列表用户信息， 数组中存放AVDUser对象 */


/** 获取或创建房间接口
 *
 * @param[in] roomId 房间Id。
 * @note 只支持单用户应用，不支持多用户应用。
 * @return 返回房间接口指针。
 */
+ (AVDEasyRoom*) obtain:(AVDRoomId)roomID;
/** 释放房间接口
 *
 *@note 释放房间后，App层不能再使用当前房间指针，所有引用房间指针处均需设置为NULL。
 */
- (void) destory;

/// 房间加入退出逻辑
/** 当前用户加入房间
 *
 * @param[in] *user 用户信息：用户Id(不能包含'{'、'}'字符)，用户名，用户数据等；当应用层必须传入有效的user.UserId，来唯一标识一个用户。
 * @param[in] joinresult 加房间回调接口。
 *
 * @return 返回错误代码。
 * @sa User
 */
- (AVDResult) joinWithUser:(AVDUser*)user delegate:(id<AVDRoomJoinDelegate>)joinresult;
- (BOOL) isWorking;
/** 当前用户离开房间
 *
 * @param[in] reason 用户离开房间的原因代码，正常离开为AVD_OK。
 *
 * @note 当前用户离开房间后，当前房间对象和房间的各功能模块都处于离会状态，功能操作无效。
 * @return 返回错误代码。
 */
- (AVDResult) leave:(AVDResult)reason;				// leave myself
/** 房间中踢出用户
 *
 * @param[in] reason 踢出用户的理由代码。
 * @param[in] userId 被踢出用户Id。
 *
 * @note 被踢用户将会在onLeaveIndication中接收到回调，被踢用户直接调用 leave 离开房间即可。
 * @return 返回错误代码。
 * @sa onLeaveIndication
 */
- (AVDResult) kickoutUser:(AVDResult)reason userId:(AVDUserId)userId;
/** 透明通道，发送广播数据
 *
 * @param[in] *data 发送的数据指针。
 *
 * @note 此透明通道用于承载应用层数据，广播给所有房间内用户。
 * @return 返回错误代码。
 */
- (AVDResult) sendPublicData:(NSData*)data;

/** 透明通道，发送私有数据
 *
 * @param[in] *data 发送的数据指针。
 * @param[in] toId 目的用户Id。
 *
 * @note 此透明通道用于承载应用层数据，发送给房间内某一特定用户。
 * @return 返回错误代码。
 */
- (AVDResult) sendPrivateData:(NSData*)data toUserId:(AVDUserId)toId;

/// 音视频操作
/** 开启直播（主播）或对讲（观众）前: 设置视频的输入数据源
 *
 * @param[in] *vcapturer 视频的输入数据源。
 * @return 返回错误代码。
 * @sa FakeVideoCapturer
 */
- (AVDResult) setVideoSource:(AVDFakeVideoCapturer*)vcapturer;
/** 开启直播（主播）或对讲（观众）前: 设置音频的输入数据源
 *
 * @param[in] *acapturer 音频的输入数据源。
 * @return 返回错误代码。
 * @sa FakeAudioCapturer
 */
- (AVDResult) setAudioSource:(AVDFakeAudioCapturer*)acapturer;

/** 打开本地麦克风发布到房间中
 *
 * @return 返回错误代码。
 * @note 为异步操作，操作结果在 onOpenMicrophoneResult 中返回。
 * 只支持单个音频输入设备，如果设置了 FakeAudioCapturer优先使用外部导入音频；
 * 如果没有设置外部导入音频源，根据设置使用缺省音频设备。
 * @sa onOpenMicrophoneResult
 */
- (AVDResult) publishMicrophone;
/** 关闭本地麦克风发布到房间中
 *
 * @return 返回错误代码。
 * @note 为异步操作，操作结果在 onCloseMicrophoneResult 中返回。
 * @sa onCloseMicrophoneResult
 */
- (AVDResult) unpublishMicrophone;

/** 预览本地缺省摄像头视频
 *
 * @param[in] *render 显示对象接口指针
 * @note 本地视频在发布到会议前，可以调用此接口进行视频预览；视频发布到会议中后，需要使用attachRender接口来进行视频显示，此时此接口无效。
 * 只支持单个视频输入设备，如果设置了 FakeVideoCapturer 优先使用外部导入视频；
 * 如果没有设置外部导入视频源，根据设置使用缺省视频设备。
 * @return 返回错误代码。
 * @sa IVideoRender
 */
- (AVDResult) previewCamera:(id<AVDVideoRenderer>)render;
/** 取消预览缺省摄像头视频
 * @return 返回错误代码。
 */
- (AVDResult) unpreviewCamera;
/** 发布缺省摄像头视频
 *
 * @return 返回错误代码。
 * @note 发布操作为异步操作，操作结果在 onPublishResult 中返回。
 * @sa onPublishResult
 */
- (AVDResult) publishCamera;
/** 取消发布缺省摄像头视频
 *
 * @return 返回错误代码。
 * @note 取消发布操作为异步操作，操作结果在 onUnpublishResult 中返回。
 * @sa onUnpublishResult
 */
- (AVDResult) unpublishCamera;
/** 关联视频数据和显示对象，在render中显示视频
 *
 * @param[in] userId 摄像头Id，唯一标示一路共享的摄像头视频。
 * @param[in] *render 显示对象接口指针。
 *
 * @note 视频数据可以在多个显示对象上显示，而一个显示对象某一时刻只能显示一路视频。
 *		在本地视频发布到房间中，或者远端视频订阅成功后，调用此接口完成视频与显示对象的对接，从而在显示对象中显示视频。
 * @return 返回错误代码。
 * @sa IVideoRender
 */
- (AVDResult) attachRender:(AVDUserId)userId render:(id<AVDVideoRenderer>)render;
/** 解除摄像头视频数据的所有显示对象关联
 *
 * @param[in] userId 摄像头Id，唯一标示一路共享的摄像头视频。
 * @return 返回错误代码。
 */
- (AVDResult) detachRender:(AVDUserId)userId;
/** 视频切换摄像头
 * @return 返回错误代码。
 */
- (AVDResult) switchCamera;
/** 判断本地麦克风是否静默
 * @return 返回静默状态。
 */
- (BOOL) ismuteMicrophone;
/** 本地麦克风静默
 * @return 返回错误代码。
 */
- (AVDResult) muteMicrophone;
/** 本地麦克风静默取消
 * @return 返回错误代码。
 */
- (AVDResult) unmuteMicrophone;

/// 音视频导出操作
/** 设置获取混音数据回调接口
 * @param[in] listener 混音数据回调指针。
 * @param[in] sampleRate 导出混音数据的采样率：16000,44100,48000。
 * @return 返回错误代码。
 * @sa IAudioRender
 * @sa ro_audio_mixerdata_callback_buffered 单次混音数据回调“10ms数据”还是“1024samples数据”
 * @note 如果音视频同时混合出流，建议先设置视频，再设置音频的回调接口，有助于音视频时间戳对齐。
 */
- (AVDResult) setAudioMixerDataListener:(id <AVDAudioRenderer>)listener sampleRate:(NSInteger)sampleRate;
/** 设置获取视频数据回调接口,此数据仅回调一份数据：数据为主视频+各个Overlay的视频，视频大小为主视频大小；如使用ILivecast接口，不需要设置此接口。
 * @param[in] listener 混音数据回调指针。
 * @return 返回错误代码。
 * @sa IVideoRender
 * @note 如果音视频同时混合出流，建议先设置视频，再设置音频的回调接口，有助于音视频时间戳对齐。
 */
- (AVDResult) setVideoMixerDataListener:(id<AVDVideoRenderer>)listener;
/** 获取视频混频布局接口
 * @return 混频布局接口
 */
- (AVDVideoMixer*) getVideoMixer;

/** 当前房间启用或关闭流量统计功能
 * @param[in] isEnable 启用或关闭。
 * @return 返回错误代码：
 * 	AVD_OK						成功
 */
- (AVDResult) enableStats:(BOOL)isEnable;
/** 获取房间的流量统计信息
 * @return 返回房间流量统计信息。
 * @sa RoomStats
 */
- (AVDRoomStats*) getRoomStats;

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
