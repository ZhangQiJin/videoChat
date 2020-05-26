//
//  ScreenCapturer_ios.h
//  ScreenCapturer_ios
//
//  Created by HPCL20190110 on 2019/3/13.
//  Copyright © 2019 ChinaRapidFinance. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Photos/Photos.h>
#import <ReplayKit/ReplayKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface ScreenCapturer_ios : NSObject

/// 单例对象
+ (instancetype)sharedManager;

/// 销毁对象
+ (void)destoryManager;

/// 用于查看相册和麦克风权限是否已经获取;
+ (void)demandForAuthorization:(void(^)(void))authorizedResultBlock;

/// 当前是否是录制状态
+ (BOOL)isRecording;

/// 开始记录
- (void)startRecording:(void(^)(uint8_t* baseAddress,size_t frameSize,VideoCaptureCapability tempCaptureCapability))videoCallBack audioBuffer:(void(^)(CMSampleBufferRef  _Nonnull sampleBuffer))audioCallBack;

/// 停止记录
- (void)stopRecording;

@end

NS_ASSUME_NONNULL_END
