//
//  AVDAudio.h
//  avd_sdk
//
//  Created by skin on 15-7-21.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#ifndef avd_sdk_AVDAudio_h
#define avd_sdk_AVDAudio_h

#import "AVDModule.h"
#import "AVDDevice.h"
#import "AVDAudioInfo.h"

@class AVDRoom;

/**
 * 房间中音频模块回调接口.
 *
 * 音频模块回调接口定义了房间中音频相关如麦克风、扬声器的通知和异步操作返回。
 */
@protocol AVDAudioDelegate<NSObject>

@required
/// 通知
/** 麦克风状态更改通知
 *
 * @param[in] status 麦克风状态。
 * @param[in] fromId 设备关联用户Id。
 * @note 当麦克风状态更改后，房间内所有用户接收到此通知。
 * @sa openMicrophone
 * @sa closeMicrophone
 */
- (void) onMicrophoneStatusNotify:(enum AVDDeviceStatus)status fromUser:(AVDUserId) fromId;

@optional
/** 语音激励通知
 *
 * @param[in] info 语音激励信息。
 * @note 语音激励通知，只有启用语音激励后才会有语音激励通知。启用语音激励接口为：monitorAudioLevel。
 * @sa monitorAudioLevel
 */
- (void) onAudioLevelMonitorNotify:(AVDAudioInfo*)info;

/// 异步返回
/** 本用户打开麦克风异步返回
 *
 * @param[in] result 错误代码。
 * @sa openMicrophone
 */
- (void) onOpenMicrophoneResult:(AVDResult)result;
/** 本用户关闭麦克风异步返回
 *
 * @param[in] result 错误代码。
 * @sa closeMicrophone
 */
- (void) onCloseMicrophoneResult:(AVDResult)result;

@end

enum AVDSpeakerMode {
    SM_Handfree,                        /**< 语音外放模式 */
    SM_Receiver,                        /**< 语音听筒模式 */
};

/**
 * 房间中音频混音数据回调接口.
 */
@protocol AVDAudioMixerDataDelegate<NSObject>
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
	* 房间中音频模块接口.
	*
	* 房间音频模块定义房间音频相关如麦克风、扬声器相关操作功能接口。
	*/
@interface AVDAudio : AVDModule

@property (nonatomic,weak) id <AVDAudioDelegate> delegate;        /**< 语音回调代理 */
@property (nonatomic,weak) id <AVDAudioMixerDataDelegate> mixerDataDelegate;/**< 语音数据回调代理 */


/** 获取音频功能模块对象
 *
 * @param[in] room 房间对象指针
 * @return 返回音频模块对象。
 */
+ (AVDAudio* ) getAudio:(AVDRoom*)room;

/** 打开本地麦克风发布到房间中
 *
 * @return 返回错误代码。
 * @note 为异步操作，操作结果在 onOpenMicrophoneResult 中返回。
 * @sa onOpenMicrophoneResult
 */
- (AVDResult) openMicrophone;
/** 关闭本地麦克风发布到房间中
 *
 * @return 返回错误代码。
 * @note 为异步操作，操作结果在 onCloseMicrophoneResult 中返回。
 * @sa onCloseMicrophoneResult
 */
- (AVDResult) closeMicrophone;
/** 获取本地麦克风状态
 * @return 返回麦克风状态。
 */
- (enum AVDDeviceStatus) getMicrophoneStatus;
- (BOOL) isOpenMicrophone;
// no input audio, anyone cann't listen my speak; like pause mic
/** 本地麦克风静默
 *
 * @return 返回错误代码。
 * @note 麦克风静默表示本地没有声音发布到房间中，房间中用户不会听到本地的任何声音。
 */
- (AVDResult) muteMicrophone;
/** 本地麦克风取消静默
 * @return 返回错误代码。
 */
- (AVDResult) unmuteMicrophone;
/** 判断本地麦克风是否静默
 */
- (BOOL) ismuteMicrophone;
// no output audio, cann't listen anyone sound
/** 本地扬声器静默
 *
 * @return 返回错误代码。
 * @note 扬声器静默表示房间中的声音不会在本地扬声器播放，本用户不会听到任何房间中的声音。
 */
- (AVDResult) muteSpeaker;
/** 本地扬声器取消静默
 * @return 返回错误代码。
 */
- (AVDResult) unmuteSpeaker;
/** 判断本地扬声器是否静默
 */
- (BOOL) ismuteSpeaker;

/** 开启语音激励功能
 * @return 返回错误代码。
 */
- (AVDResult) monitorAudioLevel;
/** 关闭语音激励
 * @return 返回错误代码。
 */
- (AVDResult) unmonitorAudioLevel;
/** 判断是否开启语音激励
 */
- (BOOL) ismonitorAudioLevel;

/// remote microphone control
/** 获取远端麦克风状态
 * @param[in] userId 关联用户Id。
 * @return 返回麦克风状态。
 */
- (enum AVDDeviceStatus) getRemoteMicrophoneStatus:(AVDUserId)userId;
/** 命令远端用户打开麦克风
 * @param[in] userId 关联用户Id。
 * @return 返回错误代码。
 */
- (AVDResult) remotecmdOpenMicrophone:(AVDUserId)userId;
/** 命令远端用户关闭麦克风
 * @param[in] userId 关联用户Id。
 * @return 返回错误代码。
 */
- (AVDResult) remotecmdCloseMicrophone:(AVDUserId)userId;

/** 设置耳麦模式
 * @param[in] mode 耳麦模式。
 * @return 返回错误代码。
 * @sa AVDSpeakerMode
 */
+ (AVDResult) setSpeakerMode:(enum AVDSpeakerMode)mode;
/** 获取耳麦模式
 */
+ (enum AVDSpeakerMode) getSpeakerMode;

/** 开始播放声音文件
 * @param[in] file 本地音频文件。
 * @return 返回错误代码。
 * @note 用于测试扬声器是否工作正常。
 */
- (AVDResult) playVoice:(NSString *)file;
/** 停止播放声音文件
 *
 * @return 返回错误代码。
 */
- (AVDResult) stopVoice;

/** 设置获取混音数据回调接口
 * @param[in] listener 混音数据回调指针。
 * @param[in] sampleRate 导出混音数据的采样率：16000,44100,48000。
 * @param[in] channels 导出混音数据的通道数：1，2。
 * @return 返回错误代码。
 * @sa IMixerDataListener
 * @sa ro_audio_mixerdata_callback_buffered 单次混音数据回调“10ms数据”还是“1024samples数据”
 * @note 如果音视频同时混合出流，建议先设置视频，再设置音频的回调接口，有助于音视频时间戳对齐。
 */
- (AVDResult) setMixerDataListener:(id <AVDAudioMixerDataDelegate>)listener sampleRate:(NSInteger)sampleRate;
- (AVDResult) setMixerDataListener2:(id <AVDAudioMixerDataDelegate>)listener sampleRate:(NSInteger)sampleRate channels:(NSInteger)channels;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Disallow init and don't add to documentation
- (id)init __attribute__((
    unavailable("init is not a supported initializer for this class.")));
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

@end

#endif
