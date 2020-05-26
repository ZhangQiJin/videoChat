//
//  ScreenCapturer_ios.m
//  ScreenCapturer_ios.m
//
//  Created by HPCL20190110 on 2019/3/13.
//  Copyright © 2019 ChinaRapidFinance. All rights reserved.
//

#import "ScreenCapturer_ios.h"


@interface ScreenCapturer_ios() <RPPreviewViewControllerDelegate>

@end

@implementation ScreenCapturer_ios

/// 单例对象
static ScreenCapturer_ios *_instance;
static dispatch_once_t onceToken;

/// 录制对象
static RPScreenRecorder *recorder;


/// 销毁对象
+ (void)destoryManager {
    
    onceToken = 0;
    // 只有置成0,GCD才会认为它从未执行过.它默认为0.这样才能保证下次再次调用shareInstance的时候,再次创建对象.
    _instance = nil;
    recorder = nil;
    
    NSLog(@"销毁录制对象  _instance:%@  recorder:%@ ", _instance, recorder);
}


+ (instancetype)allocWithZone:(struct _NSZone *)zone {
    dispatch_once(&onceToken, ^{
        _instance = [super allocWithZone:zone];
        recorder = [RPScreenRecorder sharedRecorder];
        recorder.microphoneEnabled = YES;
    });
    return _instance;
}
+ (instancetype)sharedManager {
    return [[self alloc] init];
}
- (id)copyWithZone:(NSZone *)zone {
    return _instance;
}
- (id)mutableCopyWithZone:(NSZone *)zone {
    return _instance;
}


/// 申请权限
+ (void)demandForAuthorization:(void(^)(void))authorizedResultBlock {
    // 先去 info.plit 开启相册权限,否则真机崩溃
    PHAuthorizationStatus status = [PHPhotoLibrary authorizationStatus];
    if (status == PHAuthorizationStatusAuthorized) {
        if (authorizedResultBlock) {  //已经授权
            authorizedResultBlock();
        }
        NSLog(@"相册权限已经存在");
    } else {
        [PHPhotoLibrary requestAuthorization:^(PHAuthorizationStatus status) {
            if(status == PHAuthorizationStatusAuthorized) {
                dispatch_async(dispatch_get_main_queue(), ^{
                    if (authorizedResultBlock) {  // 用户点击 "OK"
                        authorizedResultBlock();
                    }
                });
                NSLog(@"相册权限已经授权 用户授权");
            } else {
                NSLog(@"用户拒绝相册访问权限");  // 用户点击 不允许访问
            }
        }];
    }
}


#pragma mark - 开始录制
/// 开始记录
//- (void)startRecording {
//    [ScreenCapturer_ios demandForAuthorization:^{
//        [_instance turnOnRecord];
//    }];
//}

- (void)startRecording:(void(^)(uint8_t* baseAddress,size_t frameSize,VideoCaptureCapability tempCaptureCapability))videoCallBack audioBuffer:(void(^)(CMSampleBufferRef  _Nonnull sampleBuffer))audioCallBack{
    [ScreenCapturer_ios demandForAuthorization:^{
        [_instance turnOnRecord:videoCallBack audioBuffer:audioCallBack];
    }];
}

/// 开始记录
- (void)turnOnRecord:(void(^)(uint8_t* baseAddress,size_t frameSize,VideoCaptureCapability tempCaptureCapability))videoCallBack audioBuffer:(void(^)(CMSampleBufferRef  _Nonnull sampleBuffer))audioCallBack{
    if (recorder.isRecording) { //已经在录制,就返回
        return;
    }
    dispatch_async(dispatch_get_main_queue(), ^{
        if (@available(iOS 11.0, *)) {
            [recorder startCaptureWithHandler:^(CMSampleBufferRef  _Nonnull sampleBuffer, RPSampleBufferType bufferType, NSError * _Nullable error) {
                NSLog(@"录制开始... 11.0 系统");
                switch (bufferType) {
                    case RPSampleBufferTypeVideo:
                        // Handle video sample buffer
                        const int kFlags = 0;
                        CVImageBufferRef videoFrame = CMSampleBufferGetImageBuffer(sampleBuffer);
                        if (CVPixelBufferLockBaseAddress(videoFrame, kFlags) != kCVReturnSuccess) {
                            return;
                        }
                        const int kYPlaneIndex = 0;
                        const int kUVPlaneIndex = 1;
                        uint8_t* baseAddress = (uint8_t*)CVPixelBufferGetBaseAddressOfPlane(videoFrame, kYPlaneIndex);
                        size_t yPlaneBytesPerRow = CVPixelBufferGetBytesPerRowOfPlane(videoFrame, kYPlaneIndex);
                        size_t yPlaneHeight = CVPixelBufferGetHeightOfPlane(videoFrame, kYPlaneIndex);
                        size_t uvPlaneBytesPerRow = CVPixelBufferGetBytesPerRowOfPlane(videoFrame, kUVPlaneIndex);
                        size_t uvPlaneHeight = CVPixelBufferGetHeightOfPlane(videoFrame, kUVPlaneIndex);
                        size_t frameSize = yPlaneBytesPerRow * yPlaneHeight + uvPlaneBytesPerRow * uvPlaneHeight;
                        
                        VideoCaptureCapability tempCaptureCapability;
                        tempCaptureCapability.width = CVPixelBufferGetWidth(videoFrame);
                        tempCaptureCapability.height = CVPixelBufferGetHeight(videoFrame);
                        tempCaptureCapability.maxFPS = _capability.maxFPS;
                        tempCaptureCapability.rawType = kVideoNV12;
                        
                        if (videoCallBack) {
                            videoCallBack(baseAddress,frameSize,tempCaptureCapability);
                        }
                        break;
                    case RPSampleBufferTypeAudioApp:
                        // Handle audio sample buffer for app audio
                        break;
                    case RPSampleBufferTypeAudioMic:
                        // Handle audio sample buffer for mic audio
                        if (audioCallBack) {
                            audioCallBack(sampleBuffer);
                        }
                        break;
                        
                    default:
                        break;
                }
                NSLog(@"buffer = %@",sampleBuffer);
            } completionHandler:^(NSError * _Nullable error) {
                NSLog(@"complete");
            }];
        }else if (@available(iOS 10.0, *)) {
            [recorder startRecordingWithHandler:^(NSError * _Nullable error) {
                if (!error) {
                    NSLog(@"录制开始... 10.0 系统");
                }
            }];
        } else if (@available(iOS 9.0, *)) {
            [recorder startRecordingWithMicrophoneEnabled:YES handler:^(NSError * _Nullable error) {
                if (!error) {
                    NSLog(@"录制开始... 9.0 系统");
                }
            }];
        } else {
            NSLog(@"系统版本太低,无法使用录制功能.");
        }
    });
   
}

+ (BOOL)isRecording{
    return recorder.isRecording;
}

#pragma mark - 停止录制
/// 停止录制
- (void)stopRecording {
    [_instance turnOffRecord];
}

/// 停止录制
- (void)turnOffRecord {
    NSLog(@"结束录制");
    dispatch_async(dispatch_get_main_queue(), ^{
        if(@available(iOS 11.0, *)){
            [[RPScreenRecorder sharedRecorder] stopCaptureWithHandler:^(NSError * _Nullable error) {
                if (error) {  //出错
                    NSLog(@"出错: %@", error);
                } else {
                    NSLog(@"iOS 11: %@", @"结束录制");
                }
            }];
        }else{
            [[RPScreenRecorder sharedRecorder] stopRecordingWithHandler:^(RPPreviewViewController * _Nullable previewViewController, NSError * _Nullable error) {
                NSLog(@"结束回调");
                
                if (error) {  //出错
                    NSLog(@"出错: %@", error);
                } else {  //成功回调
                    
                    if (@available(iOS 10.0, *)) {
                        
                        /*
                         iOS 10 这里我选择直接保存到相册,不使用 previewViewController 弹出来
                         */
                        [self handleiOS10:previewViewController];
                        
                    } else if (@available(iOS 9.0, *)) {
                        
                        /*
                         在iOS9 里面取不到 movieURL 这个变量,程序会崩溃. 所以直接弹出这个 previewViewController 让用户来操作保存
                         */
                        [self handleiOS9:previewViewController];
                    }
                }
            }];
        }
    });
}

/// 处理 iOS 10
- (void)handleiOS10:(RPPreviewViewController *)previewViewController {
    
    NSURL *videoURL = [previewViewController valueForKey:@"movieURL"];
    
    if (videoURL) {
        BOOL compatible = UIVideoAtPathIsCompatibleWithSavedPhotosAlbum([videoURL path]);
        
        if (compatible) {
            UISaveVideoAtPathToSavedPhotosAlbum([videoURL path], self, @selector(savedPhotoImage:didFinishSavingWithError:contextInfo:), nil);
        }
        
    } else {
        NSLog(@"没有找到 movieURL");
    }
}


/// 处理 iOS 9
- (void)handleiOS9:(RPPreviewViewController *)previewViewController {
    previewViewController.previewControllerDelegate = self;
    [[UIApplication sharedApplication].keyWindow.rootViewController presentViewController:previewViewController animated:YES completion:nil];
}

#pragma mark - RPPreviewViewController 代理,用于 iOS 9
- (void)previewControllerDidFinish:(RPPreviewViewController *)previewController {
    [previewController dismissViewControllerAnimated:YES completion:nil];
    NSLog(@"预览控制器消失");
}

- (void)previewController:(RPPreviewViewController *)previewController didFinishWithActivityTypes:(NSSet <NSString *> *)activityTypes {
    NSLog(@"用户已经操作! %@", activityTypes);
}


#pragma mark - iOS 10 保存视频的回调
/// 保存视频之后的回调,这个方法不能乱写
- (void)savedPhotoImage:(UIImage*)image didFinishSavingWithError: (NSError *)error contextInfo: (void *)contextInfo {
    if (error) {
        NSLog(@"保存视频失败!!!");
    } else {
        NSLog(@"已经成功保存了视频!");
    }
}



@end
