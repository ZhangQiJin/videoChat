//
//  AVDMediaStats.h
//  avd_sdk
//
//  Created by skin on 15-9-19.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#import "AVDCommon.h"
#import "AVDNetworkStats.h"

/**
 * 媒体统计信息结构.
 *
 * 媒体统计信息结构定义了媒体级的网络，媒体等统计信息。
 */
@interface AVDMediaStats : AVDNetworkStats

@property(nonatomic, strong, readonly) NSString*  media_type;           /**< 媒体类型：audio : video  */
@property(nonatomic, strong, readonly) NSString*  codec_name;           /**< 媒体编码名称  */
@property(nonatomic, assign, readonly) NSInteger  audio_input_level;    /**< 音频输入音量  */
@property(nonatomic, assign, readonly) NSInteger  audio_output_level;	/**< 音频输出音量  */
@property(nonatomic, assign, readonly) NSInteger  frame_width;          /**< 视频宽度  */
@property(nonatomic, assign, readonly) NSInteger  frame_height;         /**< 视频高度  */
@property(nonatomic, assign, readonly) NSInteger  frame_rate;			/**< 视频帧率  */

@end
