//
//  AVDVideoView.h
//  avd_sdk
//
//  Created by skin on 15-9-19.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "AVDVideoRenderer.h"

@interface AVDVideoView  : UIView <AVDVideoRenderer>
@property (nonatomic,weak) id <AVDVideoRendererCallBacks>callback;    /**< 视频数据回调 */
@property (nonatomic,weak) id <AVDFirstFrameCallBack>firstFrameCallback;    /**< 首帧视频数据回调通知 */
@property (nonatomic, readonly) UIView* videoView;

- (instancetype)initWithCoder:(NSCoder *)aDecoder;
- (instancetype)initWithFrame:(CGRect)frame;
- (instancetype)initForCallbacks:(id<AVDVideoRendererCallBacks>)cb;

/** 抓取直播图像保存在相册中
 *
 * @param[in] quality  图像质量：0-100, 0最差，100最好。
 * @return 返回错误代码。
 */
- (NSInteger)captureImage:(NSInteger)quality;
//
//- (void)translationWithX:(CGFloat)tx Y:(CGFloat)ty;
//- (void)scaleWithX:(CGFloat)tx Y:(CGFloat)ty;
//- (void)resetAffineTransform;

@end
