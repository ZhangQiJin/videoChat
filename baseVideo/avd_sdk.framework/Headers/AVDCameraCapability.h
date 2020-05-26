//
//  AVDCameraCapability.h
//  avd_sdk
//
//  Created by skin on 15-9-19.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
	* 视频采集信息结构.
	*
	* 视频采集结构定义了视频采集相关参数，包含视频分辨率和帧率。
	*/
@interface AVDCameraCapability : NSObject

- (instancetype) initWithWidth:(NSInteger)w height:(NSInteger)h fps:(NSInteger)fps;

@property(nonatomic, assign) NSInteger width;           /**< 视频宽度  */
@property(nonatomic, assign) NSInteger height;          /**< 视频高度  */
@property(nonatomic, assign) NSInteger maxFPS;          /**< 视频帧率  */
@property(nonatomic, assign) NSInteger catX;          /**< 裁剪的x坐标  */
@property(nonatomic, assign) NSInteger catY;          /**< 裁剪的y坐标  */
@property(nonatomic, assign) NSInteger catW;          /**< 保留的w  */
@property(nonatomic, assign) NSInteger catH;          /**< 保留的h  */

@end
