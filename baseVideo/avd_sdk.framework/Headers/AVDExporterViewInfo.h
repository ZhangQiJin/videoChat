//
//  AVDExporterViewInfo.h
//  avd_sdk
//
//  Created by 盛锋 on 2018/6/22.
//  Copyright © 2018年 t3ee. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AVDExporterViewInfo : NSObject

@property (nonatomic, assign)NSInteger mixWidth;///<混流输出视频分辨率宽
@property (nonatomic, assign)NSInteger mixHeight;///<混流输出视频分辨率高
@property (nonatomic, assign)NSInteger outBitrate;///<混流输出码率
@property (nonatomic, assign)NSInteger outFps;///<混流输出帧率

@end
