//
//  AVDFakeAudioCapturer.h
//  avd_sdk
//
//  Created by skin on 15-7-21.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#ifndef avd_sdk_AVDFakeAudioCapturer_h
#define avd_sdk_AVDFakeAudioCapturer_h

#import "AVDCommon.h"


/**
	* 音频流导入接口.
	*
	* 音频导入相关功能接口。
	*/
@interface AVDFakeAudioCapturer : NSObject

/** 获取一个音频采集器对象
 * @return 音频采集器对象指针。
 * @note 音频采集器整个引擎对象只有一个，为所有房间共用；
 */
+ (AVDFakeAudioCapturer*) instance;
/** 释放音频采集器对象, 空操作，此对象的生命期管理转到内部控制
 */
+ (AVDResult) destory;

/** 判断Capturer是否正在运行
 * @return 是否在运行。
 */
- (BOOL) isRunning;

/** 当前AVD引擎使用音频导入作为缺省音频源
 * @return 返回错误代码：
 * 	AVD_OK						成功
 */
- (AVDResult) enable:(BOOL)isEnable;

/** 给Capturer输入PCM原始数据
 *
 * @param[in] pts 时间戳, nanos second。
 * @param[in] sampleRate 音频采样率
 * @param[in] channels 音频采集通道数
 * @param[in] sample  音频内容数据指针
 * @return 返回错误代码：
 * 	AVD_OK						成功
 *	Err_Invalid_Arg				参数不合法，可忽略
 *	Err_Wrong_Status			状态不对，可忽略
 */
- (AVDResult) inputCapturedFrame:(NSData*)sample sampleRate:(NSInteger)sampleRate channels:(NSInteger)channels pts:(NSInteger)pts;


#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Disallow init and don't add to documentation
- (id)init __attribute__((
    unavailable("init is not a supported initializer for this class.")));
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

@end

#endif
