//
//  AVDRecord.h
//  avd_sdk
//
//  Created by skin on 15-7-21.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#ifndef avd_sdk_AVDRecord_h
#define avd_sdk_AVDRecord_h

#import "AVDCommon.h"


@class AVDRecordInfo;

/**
 * 录制回调接口类
 *
 * 录制回调接口定义了录制管理操作的异步返回。
 */
@protocol AVDRecordDelegate<NSObject>

@optional
/// 通知
/** 创建特定用户录制的异步返回
 *
 * @param[in] result 错误代码。
 * @param[in] info 录制信息。
 *
 * @sa createUserRecord
 */
- (void) onCreateUserRecord:(AVDResult)result info:(AVDRecordInfo*)info;
/** 停止特定录制的异步返回
 *
 * @param[in] result 错误代码。
 * @param[in] recordId 录制号。
 *
 * @sa stopRecord
 */
- (void) onStopRecord:(AVDResult)result id:(AVDRecordId)recordId;

///
/** 获取特定录制详细信息的异步返回
 *
 * @param[in] result 错误代码。
 * @param[in] info 录制信息。
 *
 * @sa getRecordInfo
 */
- (void) onRecordInfo:(AVDResult)result info:(AVDRecordInfo*)info;
/** 获取服务器上录制列表的异步返回
 *
 * @param[in] result 错误代码。
 * @param[in] total  总共直播数。
 * @param[in] begin  当前起始序号。 
 * @param[in] items 录制信息集合。
 *
 * @sa getWorkingRecords
 */
- (void) onRecordInfos:(AVDResult)result total:(NSInteger)total begin:(NSInteger)begin infos:(NSArray*)items;
/** 删除特定录制的异步返回
 *
 * @param[in] result 错误代码。
 * @param[in] recordId 录制号。
 *
 * @sa deleteRecord
 */
- (void) onDeleteRecord:(AVDResult)result id:(AVDRecordId)recordId;

@end


/**
 * 录制管理接口.
 *
 * 录制管理定义引擎中录制的创建、删除、信息获取和录制控制等功能。
 */
@interface AVDRecord : NSObject


@property (nonatomic,weak) id <AVDRecordDelegate>delegate;    /**< 录制回调代理 */

/** 获取AVD录制对象
 *
 * @note AVD录制是一个单例对象，一个进程空间只存在一个录制。
 * @return 返回AVD录制指针。
 */
+ (AVDRecord*) instance;
/** 释放AVD录制对象
 */
+ (AVDResult) destory;

/** 创建特定用户录制
 *
 * @param[in] info 中roomId，name, userid, fileType必须设置；创建成功时id会设置成新创建的录制Id，在异步返回中返回。
 * @return 返回错误代码。
 * @note 参数结构中的音频类型缺省为：ra_user_single
 视频类型缺省为：rv_main
 *		为异步操作，操作结果在 onCreateUserRecord 中返回。
 * @sa onCreateUserRecord
 */
- (AVDResult) createUserRecord:(AVDRecordInfo*)info;
/** 停止特定录制
 *
 * @param[in] recordId 录制号。
 * @return 返回错误代码。
 * @note 为异步操作，操作结果在 onStopRecord 中返回。
 * @sa onStopRecord
 */
- (AVDResult) stopRecord:(AVDRecordId)recordId;

/** 获取特定录制详细信息
 *
 * @param[in] recordId 录制号。
 * @return 返回错误代码。
 * @note 为异步操作，操作结果在 onRecordInfo 中返回。
 * @sa onRecordInfo
 */
- (AVDResult) getRecordInfo:(AVDRecordId)recordId;
/** 获取服务器上的录制列表
 *
 * @param[in] begindex 分页的起始索引。
 * @param[in] ncount 分页的请求数量。
 * @param[in] filter 查询条件，以json表示，如：{ "roomId":"hafds2324" }。
 * @return 返回错误代码。
 * @note 为异步操作，操作结果在 onRecordInfos 中返回。
 * @sa onRecordInfos
 */
- (AVDResult) findRecordInfos:(NSInteger)begindex count:(NSInteger)ncount filter:(NSString*)filter;
/** 删除特定录制
 *
 * @param[in] recordId 录制号。
 * @return 返回错误代码。
 * @note 为异步操作，操作结果在 onDeleteRecord 中返回。
 * @sa onDeleteRecord
 */
- (AVDResult) deleteRecord:(AVDRecordId)recordId;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Disallow init and don't add to documentation
- (id)init __attribute__((
    unavailable("init is not a supported initializer for this class.")));
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

@end

#endif
