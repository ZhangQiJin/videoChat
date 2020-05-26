//
//  AVDMessage.h
//  avd_sdk
//
//  Created by skin on 15-9-19.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#import "AVDCommon.h"

/**
	* 聊天消息结构.
	*
	* 聊天消息定义了一次传输聊天的信息。
	*/
@interface AVDMessage : NSObject

@property(nonatomic, strong, readonly) NSDate*   timestamp;         /**< 消息时间戳，对应用层是本地时间，传输中用GMT时间 */
@property(nonatomic, strong, readonly) AVDUserId fromId;			/**< 消息发送者Id */
@property(nonatomic, strong, readonly) NSString* fromName;			/**< 消息发送者名 */
@property(nonatomic, strong, readonly) NSString* message;			/**< 消息内容 */

- (instancetype) initWithFromId:(NSString*) fromId
                       fromName:(NSString*) fromName
                        message:(NSString*) message;

@end
