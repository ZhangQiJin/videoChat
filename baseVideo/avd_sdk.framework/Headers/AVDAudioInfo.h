//
//  AVDAudioInfo.h
//  avd_sdk
//
//  Created by skin on 15-9-19.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#import "AVDCommon.h"

/**
 * 语音激励信息结构.
 *
 * 语音激励信息信息定义了当前房间中本地语音输入和输出能量，以及远端用户的语音能量信息。
 * 语音能量幅度：0-9，其中0为无能量，9为最大能量
 */
@interface AVDAudioInfo : NSObject

@property(nonatomic, assign) NSInteger inputLevel;          /**< 本地语音输入能量  */
@property(nonatomic, assign) NSInteger outputLevel;         /**< 本地语音输出能量  */
@property(nonatomic, strong, readonly) NSDictionary* activeStreams;    /**< 远端用户的语音能量对应表，只包含能量大于0的用户 */

/**
 * 判断设备对象是否有效 */
- (BOOL) isValid;

@end
