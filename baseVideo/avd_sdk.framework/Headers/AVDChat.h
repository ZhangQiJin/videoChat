//
//  AVDChat.h
//  avd_sdk
//
//  Created by skin on 15-7-21.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#ifndef avd_sdk_AVDChat_h
#define avd_sdk_AVDChat_h

#import "AVDModule.h"
#import "AVDMessage.h"

@class AVDRoom;

/**
 * 房间中聊天模块回调接口.
 *
 * 聊天模块回调接口定义了房间中聊天相关的通知。
 */
@protocol AVDChatDelegate<NSObject>

@optional
/// 通知
/** 接收到公聊消息通知
 *
 * @param[in] *message 消息内容。
 * @note 当用户发送公聊消息后，房间内所有用户除发送者外都将接收到此通知。
 * @sa Message
 * @sa sendPublicMessage
 */
- (void) onPublicMessage:(AVDMessage*)message;
/** 接收到私聊消息通知
 *
 * @param[in] *message 消息内容。
 * @note 当用户发送私聊消息后，只有消息目的用户接收到此消息通知。
 * @sa Message
 * @sa sendPrivateMessage
 */
- (void) onPrivateMessage:(AVDMessage*)message;

@end


/**
	* 房间中聊天模块接口.
	*
	* 房间聊天模块定义房间中公聊和私聊等聊天功能接口。
	*/
@interface AVDChat : AVDModule


@property (nonatomic,weak) id <AVDChatDelegate>delegate;    /**< 聊天回调代理 */

/** 获取聊天功能模块对象
 *
 * @param[in] *room 房间对象指针
 * @return 返回聊天模块对象。
 */
+ (AVDChat* ) getChat:(AVDRoom*)room;

/** 发送公聊消息
 *
 * @param[in] *message 消息内容。
 *
 * @return 返回错误代码。
 */
- (AVDResult) sendPublicMessage:(NSString *)message;
/** 发送私聊消息
 *
 * @param[in] *message 消息内容。
 * @param[in] toId 私聊消息目的用户Id。
 *
 * @return 返回错误代码。
 */
- (AVDResult) sendPrivateMessage:(NSString *)message toUser:(AVDUserId)toId;

/** 获取公聊历史消息记录
 *
 * @param[in] latest 是否是最新记录（即反序）。
 * @param[in] begindex 消息起始索引。
 * @param[in] count 请求消息数量。
 *
 * @return 返回消息列表。
 * @note 返回数组中存放着AVDMessage对象
 */
- (NSMutableArray*) getPublicHistoryMessage:(BOOL)latest begin:(NSInteger)begindex count:(NSInteger)count;
/** 获取私聊历史消息记录
 *
 * @param[in] latest 是否是最新记录（即反序）。
 * @param[in] begindex 消息起始索引。
 * @param[in] count 请求消息数量。
 * @param[in] userId 聊天对方的用户Id。
 *
 * @return 返回消息列表。
 * @note 返回数组中存放着AVDMessage对象
 */
- (NSMutableArray*) getPrivateHistoryMessage:(BOOL)latest begin:(NSInteger)begindex count:(NSInteger)count userId:(AVDUserId)userId;


#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Disallow init and don't add to documentation
- (id)init __attribute__((
    unavailable("init is not a supported initializer for this class.")));
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

@end

#endif
