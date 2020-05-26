//
//  AVDAudioParams.h
//  avd_sdk
//
//  Created by skin on 15-9-19.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * 音频参数信息结构.
 *
 * 音频参数结构定义了音频采集相关参数。
 */
@interface AVDAudioParams : NSObject
@property(nonatomic, assign) NSUInteger channel;
@property(nonatomic, assign) NSUInteger sampleRate;
@property(nonatomic, assign) NSUInteger bitrate;

- (instancetype) initWithChannel:(NSInteger)c sampleRate:(NSInteger)s bitrate:(NSInteger)b;

@end
