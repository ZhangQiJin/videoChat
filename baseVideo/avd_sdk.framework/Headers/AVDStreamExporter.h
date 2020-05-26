//
//  AVDStreamExporter.h
//  avd_sdk
//
//  Created by 盛锋 on 2018/6/22.
//  Copyright © 2018年 t3ee. All rights reserved.
//

#import "AVDModule.h"
#import "AVDExporterInfo.h"
#import "AVDExporterViewInfo.h"
#import "AVDExporterVideoInfo.h"
#import "AVDExporterVideoMixer.h"

@interface AVDStreamExporter : AVDModule

/**
 *  获取录制功能模块
 *
 *  @param room room对象
 *
 *  @return 录制模块对象
 */
+ (AVDStreamExporter* )getExporter:(AVDRoom*)room;

/**
 *  创建一个本地录制
 *
 *  @param eId      录制id
 *  @param filePath 文件路径
 *  @param viewInfo 混流信息
 *
 *  @return 错误代码
 */
- (AVDResult)createLocalRecorder:(NSString *)eId filePath:(NSString *)filePath viewInfo:(AVDExporterViewInfo *)viewInfo;

/**
 *  创建本地实时录制
 *
 *  @param eId      录制id
 *  @param filePath 文件路径
 *  @param viewInfo 混流信息
 *
 *  @return 错误代码
 */
- (AVDResult)createLocalRealtimeRecorder:(NSString *)eId filePath:(NSString *)filePath viewInfo:(AVDExporterViewInfo *)viewInfo;

/**
 *  创建本地直播
 *
 *  @param eId      直播id
 *  @param pushUrl  推流地址
 *  @param viewInfo 混流信息
 *
 *  @return 错误代码
 */
- (AVDResult)createLocalLivecast:(NSString *)eId pushUrl:(NSString *)pushUrl viewInfo:(AVDExporterViewInfo *)viewInfo;

/**
 *  创建云端录制
 *
 *  @param eId      录制id
 *  @param filePath 文件路径
 *  @param viewInfo 混流信息
 *  @param block    回调
 *
 *  @return 错误代码
 */
- (AVDResult)createServerRecorder:(NSString *)eId filePath:(NSString *)filePath viewInfo:(AVDExporterViewInfo *)viewInfo block:(void(^)(AVDResult result,AVDExporterInfo *exporterInfo))block;

/**
 *  创建云端实时录制
 *
 *  @param eId      录制id
 *  @param filePath 文件路径
 *  @param viewInfo 混流信息
 *  @param block    回调
 *
 *  @return 错误代码
 */
- (AVDResult)createServerRealtimeRecorder:(NSString *)eId filePath:(NSString *)filePath viewInfo:(AVDExporterViewInfo *)viewInfo block:(void(^)(AVDResult result,AVDExporterInfo *exporterInfo))block;

/**
 *  创建云端直播
 *
 *  @param eId      直播id
 *  @param pushUrl  推流地址
 *  @param liveName 直播名字
 *  @param viewInfo 混流信息
 *  @param block    回调
 *
 *  @return 错误代码
 */
- (AVDResult)createServerLivecast:(NSString *)eId pushUrl:(NSString *)pushUrl liveName:(NSString *)liveName viewInfo:(AVDExporterViewInfo *)viewInfo block:(void(^)(AVDResult result,AVDExporterInfo *exporterInfo))block;

/**
 *  更新导出信息
 *
 *  @param eId     录制/直播id
 *  @param appData json数据
 *
 *  @return 错误代码
 */
- (AVDResult)updateExporterInfo:(NSString *)eId appData:(NSString *)appData;

/**
 *  选择一个音频
 *
 *  @param eId    录制/直播id
 *  @param userId userid
 *
 *  @return 错误代码
 */
- (AVDResult)selectAudio4Exporter:(NSString *)eId audioUserId:(AVDUserId)userId;

/**
 *  选择一个视频
 *
 *  @param eId     录制/直播id
 *  @param videoId 视频id
 *
 *  @return 错误代码
 */
- (AVDResult)selectSingleVideo4Exporter:(NSString *)eId videoId:(AVDDeviceId)videoId;

/**
 *  选择多个视频
 *
 *  @param eId    录制/直播id
 *  @param videos 视频数组
 *
 *  @return 错误代码
 */
- (AVDResult)selectMixedVideos4Exporter:(NSString *)eId mixedVideos:(NSArray *)videos;

/**
 *  获取混频布局模块
 *
 *  @param eId 录制/直播id
 *
 *  @return 混频布局模块
 */
- (AVDExporterVideoMixer *)getVideoMixer:(NSString *)eId;

/**
 *  暂停录制/直播
 *
 *  @param eId      录制/直播id
 *  @param isResume 是否重新开始
 *
 *  @return 错误代码
 */
- (AVDResult)pauseResume:(NSString *)eId isResume:(BOOL)isResume;

/**
 *  停止导出
 *
 *  @param eId 录制/直播id
 *
 *  @return 错误代码
 */
- (AVDResult)stopExporter:(NSString *)eId;

/**
 *  停止所有导出
 *
 *  @return 错误代码
 */
- (AVDResult)stopExporterAll;

/**
 *  获取指定导出信息
 *
 *  @param eId 录制/直播id
 *
 *  @return 错误代码
 */
- (AVDResult)getExporterInfo:(NSString *)eId;

/**
 *
 *
 *  @param callId   callid
 *  @param begindex 开始位置
 *  @param count    个数
 *  @param filter   filyter
 *
 *  @return 错误代码
 */
- (AVDResult)findExporterInfos:(NSInteger)callId beginIndex:(NSInteger)begindex count:(NSInteger)count filter:(NSString *)filter;

@end
