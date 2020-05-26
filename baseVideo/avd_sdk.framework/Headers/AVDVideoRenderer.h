//
//  AVDVideoRenderer.h
//  avd_sdk
//
//  Created by skin on 15-7-21.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#ifndef avd_sdk_AVDVideoRenderer_h
#define avd_sdk_AVDVideoRenderer_h

#import <Foundation/Foundation.h>
#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#endif

/** 视频显示方式
 */
enum AVDScalingType {
    Scale_Aspect_Fit,             // video frame is scaled to fit the size of the view by maintaining the aspect ratio (black borders may be displayed).
    Scale_Aspect_Full,            // video frame is scaled to fill the size of the view by maintaining the aspect ratio. Some portion of the video frame may be clipped.
    Scale_Fill,                   // video frame is scaled to to fill the size of the view. MVideo aspect ratio is changed if necessary.
};

@class AVDI420Frame;

@protocol AVDVideoRenderer<NSObject>

// The size of the frame.
- (void)setSize:(CGSize)size;

// The frame to be displayed.
- (void)renderFrame:(AVDI420Frame*)frame;

- (void)fillBlack;

- (void)setMirror:(BOOL)value;
- (BOOL)getMirror;

- (void)setScalingType:(enum AVDScalingType)value;
- (enum AVDScalingType)getScalingType;

- (void)setVideoId:(NSString*)videoId;
- (NSString*)getVideoId;

@end

@protocol AVDVideoRendererCallBacks<NSObject>

// The size of the frame.
- (void)setSize:(CGSize)size;

// The frame to be displayed.
- (void)renderFrame:(AVDI420Frame*)frame;

@end

@protocol AVDFirstFrameCallBack<NSObject>

- (void) onFirstFrameArrived:(id<AVDVideoRenderer>)render;

@end

#endif
