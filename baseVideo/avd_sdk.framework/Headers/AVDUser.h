//
//  AVDUser.h
//  avd_sdk
//
//  Created by skin on 15-7-21.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#ifndef avd_sdk_AVDUser_h
#define avd_sdk_AVDUser_h

#import "AVDCommon.h"
#import "AVDUserStatus.h"


/**
 * 用户数据结构.
 *
 * 用户数据定义了用户的基本信息。
 */
@interface AVDUser : NSObject

@property(nonatomic, strong, readonly) AVDUserId userId;        /**< 用户Id，应用层可设置 */
@property(nonatomic, strong) AVDUserStatus* status;             /**< 用户状态集合  */
@property(nonatomic, strong) NSString* userName;                /**< 用户名称，应用层设置  */
@property(nonatomic, strong) NSString* userData;                /**< 用户数据，应用层设置  */
@property(nonatomic, strong) NSString* userAgent;               /**< 用户数据，应用层设置  */
@property(nonatomic, assign) int nodeId;                        /**< 用户数据，应用层设置  */


- (instancetype) initWithUserId:(NSString*)userId userName:(NSString*)userName userData:(NSString*)userData;

/**
 * 判断用户对象是否有效 */
- (BOOL) isValid;
/**
 * 按视频打开、音频打开、屏幕共享排序 */
- (NSComparisonResult)compareStatusVAS:(AVDUser*)another;

@end

#endif
