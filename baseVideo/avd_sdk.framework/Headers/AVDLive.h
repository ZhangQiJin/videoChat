//
//  AVDLive.h
//  avd_sdk
//
//  Created by skin on 15-7-21.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#ifndef avd_sdk_AVDLive_h
#define avd_sdk_AVDLive_h

#import "AVDCommon.h"


@class AVDLiveInfo;

/**
 * 直播回调接口类
 *
 * 直播回调接口定义了直播管理操作的异步返回。
 */
@protocol AVDLiveDelegate<NSObject>
/// 通知
/** 创建特定用户直播的异步返回
 *
 * @param[in] result 错误代码。
 * @param[in] info 直播信息。
 *
 * @sa createUserLive
 */
- (void) onCreateUserLive:(AVDResult)result info:(AVDLiveInfo*)info;
/** 停止特定直播的异步返回
 *
 * @param[in] result 错误代码。
 * @param[in] liveId 直播号。
 *
 * @sa stopLive
 */
- (void) onStopLive:(AVDResult)result id:(AVDLiveId)liveId;

///
/** 获取特定直播详细信息的异步返回
 *
 * @param[in] result 错误代码。
 * @param[in] info   直播信息。
 *
 * @sa getLiveInfo
 */
- (void) onLiveInfo:(AVDResult)result info:(AVDLiveInfo*)info;
/** 获取服务器上直播列表的异步返回
 *
 * @param[in] result 错误代码。
 * @param[in] total  总共直播数。
 * @param[in] begin  当前起始序号。 
 * @param[in] items 直播信息集合。
 *
 * @sa getWorkingLives
 */
- (void) onLiveInfos:(AVDResult)result total:(NSInteger)total begin:(NSInteger)begin infos:(NSArray*)items;
/** 删除特定直播的异步返回
 *
 * @param[in] result 错误代码。
 * @param[in] liveId 直播号。
 *
 * @sa deleteLive
 */
- (void) onDeleteLive:(AVDResult)result id:(AVDLiveId)liveId;

@end


/**
 * 直播管理接口.
 *
 * 直播管理定义引擎中直播的创建、删除、信息获取和直播控制等功能。
 */
@interface AVDLive : NSObject


@property (nonatomic,weak) id <AVDLiveDelegate>delegate;    /**< 直播回调代理 */

/** 获取AVD直播对象
 *
 * @note AVD直播是一个单例对象，一个进程空间只存在一个直播。
 * @return 返回AVD直播指针。
 */
+ (AVDLive*) instance;
/** 释放AVD直播对象
 */
+ (AVDResult) destory;

/** 创建特定用户直播
 *
 * @param[in] info 中roomId，name, userid, fileType必须设置；创建成功时id会设置成新创建的直播Id，在异步返回中返回。
 * @return 返回错误代码。
 * @note 参数结构中的音频类型缺省为：ra_user_single
 视频类型缺省为：rv_main
 *		为异步操作，操作结果在 onCreateUserLive 中返回。
 * @sa onCreateUserLive
 */
- (AVDResult) createUserLive:(AVDLiveInfo*)info;
/** 停止特定直播
 *
 * @param[in] liveId 直播号。
 * @return 返回错误代码。
 * @note 为异步操作，操作结果在 onStopLive 中返回。
 * @sa onStopLive
 */
- (AVDResult) stopLive:(AVDLiveId)liveId;

/** 获取特定直播详细信息
 *
 * @param[in] liveId 直播号。
 * @return 返回错误代码。
 * @note 为异步操作，操作结果在 onLiveInfo 中返回。
 * @sa onLiveInfo
 */
- (AVDResult) getLiveInfo:(AVDLiveId)liveId;
/** 获取服务器上的直播列表
 *
 * @param[in] begindex 分页的起始索引。
 * @param[in] ncount 分页的请求数量。
 * @param[in] filter 查询条件，以json表示，如：{ "roomId":"hafds2324" }。
 * @return 返回错误代码。
 * @note 为异步操作，操作结果在 onLiveInfos 中返回。
 * @sa onLiveInfos
 */
- (AVDResult) findLiveInfos:(NSInteger)begindex count:(NSInteger)ncount filter:(NSString*)filter;
/** 删除特定直播
 *
 * @param[in] liveId 直播号。
 * @return 返回错误代码。
 * @note 为异步操作，操作结果在 onDeleteLive 中返回。
 * @sa onDeleteLive
 */
- (AVDResult) deleteLive:(AVDLiveId)liveId;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Disallow init and don't add to documentation
- (id)init __attribute__((
    unavailable("init is not a supported initializer for this class.")));
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

@end

#endif
