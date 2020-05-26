//
//  AVDRoomStats.h
//  avd_sdk
//
//  Created by skin on 15-9-19.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#import "AVDCommon.h"
#import "AVDNetworkStats.h"

/**
 * 房间统计信息结构.
 *
 * 房间统计信息结构定义了房间级的网络，媒体等统计信息。
 */
@interface AVDRoomStats : AVDNetworkStats

@property(nonatomic, assign, readonly) NSInteger  available_receive_bandwidth;  /**< 估计接收带宽  */
@property(nonatomic, assign, readonly) NSInteger  available_send_bandwidth;     /**< 估计发送带宽  */
@property(nonatomic, strong, readonly) NSString*  local_address;	/**< 本地地址  */
@property(nonatomic, strong, readonly) NSString*  remote_address;	/**< 远端地址  */
@property(nonatomic, strong, readonly) NSString*  transport_type;	/**< 传输类型：udp : tcp  */


@end
