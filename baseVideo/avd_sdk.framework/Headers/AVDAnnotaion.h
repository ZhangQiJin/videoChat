//
//  AVDAnnotaion.h
//  avd_sdk
//
//  Created by 盛锋 on 2018/5/4.
//  Copyright © 2018年 t3ee. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "avd_sdk_imp.h"
#import "AVDWhiteboard.h"

@protocol AVDAnnotaionDelegate <NSObject>

/**
 *  新增注释回调
 *
 *  @param boardId       白板id
 *  @param annotaionJson 注释json字符串
 */
- (void)onAnnotationAddNotifiy:(AVDBoardId)boardId annotaionJson:(NSString *)annotaionJson;

/**
 *  更新注释回调
 *
 *  @param boardId       白板id
 *  @param annotaionId   注释id
 *  @param annotaionJson 注释json字符串
 */
- (void)onAnnotationUpdateNotifiy:(AVDBoardId)boardId annotaionId:(AVDAnnotaionId)annotaionId annotaionJson:(NSString *)annotaionJson;

/**
 *  删除注释回调
 *
 *  @param boardId     白板id
 *  @param annotaionId 注释id
 */
- (void)onAnnotationDelNotifiy:(AVDBoardId)boardId annotaionId:(AVDAnnotaionId)annotaionId;

/**
 *  清除注释回调
 *
 *  @param boardId 白板id
 *  @param userId 清除者id
 */
- (void)onAnnotationClearNotifiy:(AVDBoardId)boardId userId:(AVDUserId)userId;


@end

@interface AVDAnnotaion : AVDModule

@property (nonatomic,weak) id <AVDAnnotaionDelegate>delegate;              /**< 注释模块回调接口代理 */

@property (nonatomic,assign,readonly) AVDBoardId boardId;


//获取注释
+ (AVDAnnotaion* )getAnnotaion:(AVDRoom*)room;

/**
 *  获取当前白板id对应的注释列表
 *
 *  @param boardId 白板id
 *
 *  @return 注释列表
 */
- (NSMutableArray *)internal_getAnnotaionList:(AVDBoardId)boardId;

/**
 *  新增注释
 *
 *  @param boardId             白板id
 *  @param annotaionJsonString 新增注释的json字符串
 *
 *  @return 返回错误代码
 */
- (AVDResult)addAnnotation:(AVDBoardId)boardId annotaionString:(NSString *)annotaionJsonString;

/**
 *  移除注释
 *
 *  @param boardId             白板id
 *  @param annotaionId 需要移除的注释id
 *
 *  @return 返回错误代码
 */
- (AVDResult)removeAnnotationObj:(AVDBoardId)boardId annotaionId:(AVDAnnotaionId)annotaionId;

/**
 *  更新注释
 *
 *  @param boardId             白板id
 *  @param annotaionId         注释id
 *  @param annotaionJsonString 更新注释的json字符串
 *
 *  @return 返回错误代码
 */
- (AVDResult)updateAnnotation:(AVDBoardId)boardId annotaionId:(AVDAnnotaionId)annotaionId annotaionJsonString:(NSString *)annotaionJsonString;

/**
 *  撤销
 *
 *  @param boardId 白板id
 *
 *  @return 返回错误代码
 */
- (AVDResult)undo:(AVDBoardId)boardId;

/**
 *  重做
 *
 *  @param boardId 白板id
 *
 *  @return 返回错误代码
 */
- (AVDResult)redo:(AVDBoardId)boardId;

/**
 *  清除
 *
 *  @param boardId 白板id
 *
 *  @return 返回错误代码
 */
- (AVDResult)clear:(AVDBoardId)boardId;


@end
