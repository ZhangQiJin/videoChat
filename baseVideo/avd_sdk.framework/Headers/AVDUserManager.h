//
//  AVDUserManager.h
//  avd_sdk
//
//  Created by skin on 15-7-21.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#ifndef avd_sdk_AVDUserManager_h
#define avd_sdk_AVDUserManager_h

#import "AVDUser.h"

/**
 * 用户管理回调接口类
 *
 * 用户管理回调接口定义了房间用户和用户列表操作的异步返回，房间用户通知。
 */
@protocol AVDUserManagerDelegate<NSObject>

/// 通知
/** 用户加入房间通知
 *
 * @param[in] *user 用户信息数据。
 *
 * @note 某用户调用房间中的join加入房间后，房间内所有用户会接收到此通知
 * @sa join
 */
- (void)onUserJoinNotify:(AVDUser *)user;

/** 用户离开房间通知
 *
 * @param[in] *user 用户信息数据。
 *
 * @note 某用户调用房间中的leave离开房间后，房间内所有用户会接收到此通知
 * @sa leave
 */
- (void)onUserLeaveNotify:(AVDUser *)user;

/** 用户离开房间通知（新增一个reason回调用于区分正常离会和异常离会）
 *
 * @param[in] *user 用户信息数据。
 * @param[in] reason 离会错误码。
 * @note 某用户调用房间中的leave离开房间后，房间内所有用户会接收到此通知
 * @sa leave
 */
- (void)onUserLeaveNotify:(AVDUser *)user reason:(AVDResult)reason;

/** 用户信息更改通知
 *
 * @param[in] *user 用户信息数据。
 *
 * @note 某用户调用updateUser更改自己信息后，房间内所有用户会接收到此通知
 * @sa updateUser
 */
- (void)onUserUpdateNotify:(AVDUser *)user;

/** 用户状态更改通知
 *
 * @param[in] status 当前用户状态。
 * @param[in] fromId 关联的用户Id。
 *
 * @note 某用户调用updateSelfUserStatus更改自己状态后，房间内所有用户会接收到此通知；
 *       此通知从onUserUpdateNotify中分离出来，因用户状态更改较为频繁
 * @sa updateSelfUserStatus
 * @sa onUserUpdateNotify
 */
- (void)onUserStatusNotify:(AVDUserStatus*)status fromUser:(AVDUserId)fromId;

/** 用户应用层数据更改通知
 *
 * @param[in] *userData 当前用户应用层数据。
 * @param[in] fromId 关联的用户Id。
 *
 * @note 某用户调用updateSelfUserData更改自己应用层数据后，房间内所有用户会接收到此通知
 *       此通知从onUserUpdateNotify中分离出来，因应用层数据用户较为关注
 * @sa updateSelfUserData
 * @sa onUserUpdateNotify
 */
- (void)onUserDataNotify:(NSString *)userData fromUser:(AVDUserId)fromId;

@end


@class AVDRoom;

/**
	* 用户管理接口类
	*
	* 用户管理接口定义了房间内所有用户和用户列表相关的功能操作。
	*/
@interface AVDUserManager : NSObject


@property (nonatomic,weak) id <AVDUserManagerDelegate>delegate;         /**< 用户管理回调代理 */

@property (nonatomic,retain,readonly) NSMutableArray* participants;     /**< 参会者列表用户信息，数组中存放AVDUser对象 */

@property (nonatomic,retain,readonly) AVDUser* selfUser;                /**< 自己的用户信息 */


/** 获取用户管理功能模块对象
 *
 * @param[in] *room 房间对象指针
 * @return 返回用户管理模块对象。
 */
+ (AVDUserManager* ) getUserManager:(AVDRoom*)room;

/** 更新本用户信息
 *
 * @param[in] *user 用户信息。
 *
 * @return 返回错误代码。
 */
- (AVDResult) updateUser:(AVDUser *)user;

- (AVDResult) updateUserName:(NSString*)userName forUser:(AVDUserId)userId;
/** 判断用户是否存在
 *
 * @param[in] userId 用户Id。
 *
 * @return 是否存在用户。
 */
- (BOOL) hasUser:(AVDUserId)userId;

/** 获取关联Id的用户信息
 *
 * @param[in] userId 用户Id。
 *
 * @return 返回关联Id的用户信息。
 */
- (AVDUser *) getUser:(AVDUserId)userId;


/** 获取本用户Id
 * @return 返回本用户Id。
 */
- (AVDUserId) getSelfUserId;

/** 获取本用户名
 * @return 返回本用户名。
 */
- (NSString *) getSelfUserName;

/** 获取本用户应用层数据
 * @return 返回本用户应用层数据。
 */
- (NSString *) getSelfUserData;

/** 更改本用户的应用层数据
 *
 * @param[in] userData 本用户应用层数据。
 *
 * @return 返回错误代码。
 */
- (AVDResult) updateSelfUserData:(NSString *)userData;

/** 更改本用户的用户状态
 *
 * @param[in] *status 用户状态。
 *
 * @return 返回错误代码。
 */
- (AVDResult) updateSelfUserStatus:(AVDUserStatus*)status;

/** 获取房间中的用户数量
 * @return 返回本用户数量。
 */
- (NSUInteger) getParticipantsCount;


#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Disallow init and don't add to documentation
- (id)init __attribute__((
    unavailable("init is not a supported initializer for this class.")));
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

@end

#endif
