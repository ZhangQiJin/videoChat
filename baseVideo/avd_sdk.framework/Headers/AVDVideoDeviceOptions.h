//
//  AVDVideoDeviceOptions.h
//  avd_sdk
//
//  Created by skin on 15-9-19.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#import "AVDCommon.h"
#import "AVDCameraCapability.h"

/**
 * 视频质量类型.
 */
enum AVDQualityType {
    quality_low = (1 << 0),				/**< 流畅  */
    quality_normal = (1 << 1),			/**< 标清  */
    quality_high = (1 << 2),			/**< 高清  */
};

enum AVDRatioType {
    ratio_4_3,							/**< 4:3视频  */
    ratio_16_9,							/**< 16:9视频  */
    ratio_cif,							/**< CIF比例视频  */
};

/**
 * 视频质量类.
 *
 * 视频质量类定义了视频质量，视频宽高比率，视频分辨率等。
 */
@interface AVDVideoDeviceOptions : NSObject

- (BOOL) hasQuality:(enum AVDQualityType)value;
//
- (AVDResult) setCapabilities:(NSArray*)caps;   // 数组中存放AVDCameraCapability对象
- (NSMutableArray*) getCapabilities;            // 数组中存放AVDCameraCapability对象

@end
