//
//  AVDCamera.h
//  avd_sdk
//
//  Created by skin on 15-9-19.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#import "AVDDevice.h"
#import "AVDVideoDevice.h"

/**
 * 摄像头类型.
 */
enum AVDCameraType
{
    unknow,                                                         /**< 未知类型  */
    front,                                                          /**< 前置摄像头  */
    back,                                                           /**< 后置摄像头  */
};

/**
	* 视频摄像头信息结构.
	*
	* 视频摄像头结构定义了摄像头相关参数，主要是摄像头描述信息和视频分辨率信息。
	*/
@interface AVDCamera : AVDVideoDevice

- (instancetype) initWithDeviceId:(AVDDeviceId)did name:(NSString*)name;

@property(nonatomic, assign, readonly) enum AVDCameraType type;     /**< 摄像头类型  */


@end
