//
//  AVDNetworkStats.h
//  avd_sdk
//
//  Created by skin on 15-9-19.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#import "AVDCommon.h"

/**
 * 网络统计信息结构.
 *
 * 网络统计信息结构定义了网络传输中的统计信息。
 */
@interface AVDNetworkStats : NSObject

@property(nonatomic, assign, readonly) NSInteger bps_received;				/**< 当前接收带宽: 3s计算  */
@property(nonatomic, assign, readonly) NSInteger bps_sent;					/**< 当前发送带宽: 3s计算  */
@property(nonatomic, assign, readonly) NSInteger lostpercent;				/**< 当前丢包率: 3s计算  */
@property(nonatomic, assign, readonly) NSInteger lostpercent_received;		/**< 当前接收丢包率: 3s计算  */
@property(nonatomic, assign, readonly) NSInteger lostpercent_sent;			/**< 当前发送丢包率: 3s计算  */
@property(nonatomic, assign, readonly) long long bytes_received;			/**< 总共已接收字节数  */
@property(nonatomic, assign, readonly) long long bytes_sent;				/**< 总共已发送字节数  */
@property(nonatomic, assign, readonly) long long packets_lost;				/**< 总共已丢包数  */
@property(nonatomic, assign, readonly) long long packets_received;			/**< 总共已接收数据包  */
@property(nonatomic, assign, readonly) long long packets_sent;				/**< 总共已发送数据包  */


@end
