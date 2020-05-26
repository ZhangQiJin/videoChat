//
//  AVDFakeVideoCapturer.h
//  avd_sdk
//
//  Created by skin on 15-7-21.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#ifndef avd_sdk_AVDFakeVideoCapturer_h
#define avd_sdk_AVDFakeVideoCapturer_h

#import "AVDCommon.h"

/**
 * 视频图像格式.
 */
enum AVDFourccType
{
    ft_I420,
    ft_YV12,
    ft_NV21,
    ft_NV12,
};

@protocol AVDFakeVideoCapturerDelegate<NSObject>

@optional
/// 通知
/** 视频流采集开始回调接口
 *
 * @return 开始成功或者失败，预留。
 * @note SDK开始视频采集触发此接口，返回值目前不关心，为以后预留。
 */
- (BOOL) onStart;
/** 视频流采集结束回调接口
 *
 * @note SDK停止视频采集触发此接口。
 */
- (void) onStop;

@end


/**
 * 视频流导入接口.
 *
 * 视频导入相关功能接口。
 */
@interface AVDFakeVideoCapturer : NSObject

@property (nonatomic,readonly) enum AVDFourccType fourFormat;             /**< 将要传入的视频数据类型 */
@property (nonatomic,readonly) BOOL isScreen;                             /**< 是否为屏幕共享 */

/** 创建一个视频采集器对象
 *
 * @param[in] delegate 回调对象。
 * @param[in] fourFormat 将要传入的视频数据类型。
 * @param[in] isScreen 是否是桌面共享。
 * @return 视频采集器对象指针。
 */
- (instancetype) initWithDelegate:(id <AVDFakeVideoCapturerDelegate>)delegate fourFormat:(enum AVDFourccType)fourFormat isScreen:(BOOL)isScreen;
/** 释放房间对象
 */
- (void) destory;

/** 判断Capturer是否正在运行
 * @return 是否在运行。
 */
- (BOOL) isRunning;

/** 给Capturer输入原始图像
 *
 * @param[in] pts 时间戳, nanos second。
 * @param[in] w 图像宽度
 * @param[in] h 图像高度
 * @param[in] sample  图像内容数据指针
 * @param[in] rotation 图像需要旋转的角度，顺时针方向，取值：0,90,180,270
 * @param[in] mirror 镜面图像，左右翻转
 * @return 返回错误代码：
 * 	AVD_OK						成功
 * 	RTC_ERR_VIDEO_CONVERT_FAILED	转换图像格式失败，有可能是内存分配失败，可考虑重启程序。
 *	Err_Invalid_Arg				参数不合法，可忽略
 *	Err_Wrong_Status			状态不对，可忽略
 */
- (AVDResult) inputCapturedFrame:(NSData*)sample w:(NSInteger)w h:(NSInteger)h rotation:(NSInteger)rotation mirror:(BOOL)mirror pts:(NSInteger)pts;

- (AVDResult) inputCapturedFrame2:(size_t)length address:(uint8_t*)address  w:(NSInteger)w h:(NSInteger)h rotation:(NSInteger)rotation mirror:(BOOL)mirror pts:(NSInteger)pts;


#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Disallow init and don't add to documentation
- (id)init __attribute__((
    unavailable("init is not a supported initializer for this class.")));
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

@end

#endif
