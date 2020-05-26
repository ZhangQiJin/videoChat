//
//  AVDPublishVideoOptions.h
//  avd_sdk
//
//  Created by skin on 15-9-19.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#import "AVDCommon.h"
#import "AVDCameraCapability.h"
#import "AVDVideoDeviceOptions.h"

/**
 * 视频主辅流类型.
 */
enum AVDStreamType {
    avdstream_main,						/**< 主流  */
    avdstream_assist1,						/**< 辅流1  */
    avdstream_assist2,						/**< 辅流2  */
};

/**
 * 视频编解码器类型.
 */
enum AVDCodecType {
    avdcodec_vp8,							/**< VP8编解码器类型  */
    avdcodec_h264,							/**< H264编解码器类型  */
    avdcodec_vp9,							/**< VP9编解码器类型  */
//    codec_default = codec_vp8,
};

/**
 * 视频质量类.
 *
 * 视频质量类定义了视频质量，视频宽高比率，视频分辨率等。
 */
@interface AVDPublishVideoOptions : NSObject

- (instancetype) initWithCapability:(AVDCameraCapability*)cap codec:(enum AVDCodecType)codec;
//
- (BOOL) hasQuality:(enum AVDQualityType)value;
//
- (enum AVDRatioType) getRatio;
- (void) setRatio:(enum AVDRatioType)value;

//
- (AVDResult) setStreamOptionsWithQuality:(enum AVDStreamType)type
                                  quality:(enum AVDQualityType)quality codec:(enum AVDCodecType)codec;
- (AVDResult) setStreamOptionsWithCapability:(enum AVDStreamType)type
                                  capability:(AVDCameraCapability*)cap codec:(enum AVDCodecType)codec;
- (AVDCameraCapability*) getStreamCapability: (enum AVDStreamType)type;
- (enum AVDQualityType) getStreamQuality:(enum AVDStreamType)type;
- (enum AVDCodecType) getStreamCodec: (enum AVDStreamType)type;

@end
