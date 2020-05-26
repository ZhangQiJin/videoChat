//
//  AVDRoom.h
//  avd_sdk
//
//  Created by skin on 15-7-21.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#ifndef avd_sdk_AVDRoom_h
#define avd_sdk_AVDRoom_h

#import "AVDRoomInfo.h"
#import "AVDUser.h"
#import "AVDUserManager.h"
#import "AVDRoomStats.h"
#import "AVDMediaStats.h"

/** 房间选项
 *
 * @note 房间选项枚举列出了用于设置房间的选项，在以下函数中使用。
 * @sa setOption
 * @sa getOption
 */
enum AVDRoomOption{
    ro_video_drop_data,					/**< 值类型为bool, 字符类型为"true" or "false"：表示接收到视频数据后不解码直接丢弃，一般用于模拟客服端做并发测试。
                                         * 默认值为false，设置为true后将丢弃该房间所有接收到的视频数据。
                                         * 必须在join调用之前设置才有效。
                                         */
    ro_audio_drop_data,					/**< 值类型为bool, 字符类型为"true" or "false"：表示接收到音频数据后不解码直接丢弃，一般用于模拟客服端做并发测试。
                                         * 默认值为false，设置为true后将丢弃该房间所有接收到的音频数据。
                                         * 必须在join调用之前设置才有效。
                                         */
    ro_media_use_dtls,					/**< 值类型为bool, 字符类型为"true" or "false"：表示音视频是否启用DTLS加密，DTLS加密数据更加安全，但是会加重Server
                                         * 的负担，在UDP丢包严重的网络环境下，媒体链接需要的时间会更多（30%丢包，链接时间10s-40s）。
                                         * 默认值为true，使用的是DTLS加密方式。
                                         * 必须在join调用之前设置才有效。
                                         */
    ro_room_reconnect_times,			/**< 值类型为int32, 字符类型为"3" or "2"等数字字符：设置每次断线后重连次数。系统默认为重连3次，如需改变需要应用层自己设置。
                                         * 在join之前或者之后设置都有效。
                                         */
    ro_room_connect_timeout,			/**< 值类型为uint32,  字符类型为"3000" or "5000" ：设置链接超时时间，单位毫秒，必须是正数，系统默认是5000毫秒。
                                         * 在join之前或者之后设置都有效。
                                         */
    ro_audio_subscribe_mode,			/**< 值类型为String, 音频订阅模式：字符类型为"autosubscribe" or "nosubscribe"：分别表示自动订阅房间中全部打开的音频
                                         * or 不自动订阅音频；缺省为"autosubscribe"自动订阅模式。
                                         * 未实现。
                                         */
    ro_audio_option_codec,				/**< 值类型为String, 音频编码算法：字符类型为"ISAC" or "opus" or "AAC"：分别表示isac语音编码 和 opus音乐编码 和 AAC语音编码；缺省为"ISAC"。
                                         * 必须在join调用之前设置才有效。
                                         */
    ro_audio_mixerdata_callback_buffered,/**< 值类型为bool, 字符类型为"true" or "false"：表示房间中混音数据回调是否缓冲为1024sample后回调：缓冲(true)和不缓冲（false），
                                          *	缺省为缓冲。
                                          * 在join之前或者之后设置都有效。
                                          */
    ro_video_default_camera,			/**< 值类型为枚举CameraType, 字符类型为"front" or "back"：表示前后置摄像头模式时房间中默认使用的摄像头：前置(front)和后置（back），
                                         *	缺省为前置。
                                         * 必须在join调用之前设置才有效。
                                         */
    ro_room_auto_rejoin,				/**< 值类型为int32, 字符类型为"true" or "false"：在重连失败之后是否尝试自动重新加入房间，系统默认为true。
                                         * 在join之前或者之后设置都有效。
                                         */
    ro_room_rejoin_times,				/**< 值类型为uint32, 字符类型为"3" or "2"等数字字符：设置断线重连失败后自动加入的次数，在启用ro_room_auto_rejoin为true后有效。
                                         * 系统默认为3，尝试3次重新加入，如果都失败将通过onConnectionStatus接口返回cs_connectFailed状态。
                                         * 在join之前或者之后设置都有效。
                                         */
    ro_room_options_apply,				/**< 值类型为String, 房间中各种选项（根据字符枚举）立即应用。当前字符枚举有："audio_options"：Engine中设置的音频选项应用如aec，agc等。
                                         */
    
    //only for windows
    ro_screen_share_fps,				/**< 值类型为uint32, 字符类型为"3" or "10"等数字字符：设置共享屏幕时的帧率，系统默认为5。
                                         */
    ro_screen_share_audio,				/**< 值类型为bool, 字符类型为"true" or "false"：设置共享屏幕时的是否共享扬声器的声音；系统默认为false。暂时没实现。
                                         */
    ro_video_mixer_published=1000,		/**< 值类型为bool, 字符类型为"true" or "false"：设置房间中发布视频时是否发布混屏后视频；系统默认为false。
                                         */
   	
    ro_video_mixerdata_callback_format = 2000, /**< 值类型为MediaCodecInfo.CodecCapabilities中的枚举值, 字符类型为枚举值的字符串，目前支持一下："19" - YUV420Planar or "21" - YUV420SemiPlanar：表示房间中合屏数据回调的格式。缺省为 "19"
                                         */
};

enum AVDOutgoingInviteType {
    OutgoingInviteTypeSIP = 1,
    OutgoingInviteTypeH323 = 2,
    OutgoingInviteTypeRTSP = 3,
};

enum AVDOutgoingStatus {
    OutStatus_RpcFailed = 912,          //rpc remote server faild
    OutStatus_DeviceInroom = 914,       //device is already in room
    OutStatus_WrongDeviceAddr = 915,    //wrong device addr
    OutStatus_CallReject = 916,         //call be rejected
    OutStatus_CallFailed = 917,         //call device faild
    OutStatus_DeviceBusy = 918,         //device is busy
    OutStatus_CallTimeout = 919,        //call device timeout
    OutStatus_RemoteNumNotExist = 920,  //remote number non existing
    OutStatus_RemoteAddrUnavlid = 921,  //remote addr unavailable
    OutStatus_RemoteTerminate = 922,    //remote terminated
    
};

@protocol AVDRoomJoinDelegate <NSObject>
- (void)onJoinResult:(AVDResult)aResult;

@end

/**
 * 房间回调接口类
 *
 * 房间回调接口定义了房间对象操作的异步返回，房间通知，房间指示。
 */
@protocol AVDRoomDelegate<NSObject>

@required
/// 指示
/** 指示用户离开房间
 *
 * @param[in] reason 离开房间理由代码，正常离开为AVD_OK。
 * @param[in] fromId 指示发起用户Id。
 * @note SDK内部已经开始释放房间资源，应用层可以不调用leave
 * reason:
 * Err_User_DuplicateJoin			用户Id在别处登录，先前同一Id被踢出；
 * Err_User_DataConnection_Failed	数据链接连接失败，用户无法正常使用房间，用户被服务器踢出；
 * 其他								kickoutUser 传入的错误码，被其他用户踢出，应用层自己定义；
 */
- (void)onLeaveIndication:(AVDResult)reason fromUser:(AVDUserId)fromId;
/// 通知
/** 房间网络状态通知
 *
 * @param[in] status 当前网络状态。
 *
 */
- (void)onConnectionStatus:(enum AVDConnectionStatus)status;

@optional
/// 异步返回
/** 加入房间操作异步返回
 *
 * @param[in] result 加入错误代码。
 * @return  0 成功
 *		Err_Stream_Connection_TimeOut		房间加会超时：可能原因有服务器没返回信令握手等
 *		Err_Rest_GetMcu_Failure				集群中获取可用mcu失败；
 *		Err_Net_ChannelSignal_Failure		房间信令连接失败，检查服务器地址和端口，及本地网络；
 *		Err_Net_ChannelData_Failure			房间数据连接失败（未实现）
 * @sa join
 */
- (void)onJoinResult:(AVDResult)result;

/// 通知
/** 透明通道，接收到广播数据通知
 *
 * @param[in] data 接收到的数据指针。
 * @param[in] fromId 发送方用户Id。
 *
 * @sa sendPublicData
 */
- (void)onPublicData:(NSData*)data fromUser:(AVDUserId)fromId;

/** 透明通道，接收到私有数据通知
 *
 * @param[in] data 接收到的数据指针。
 * @param[in] fromId 发送方用户Id。
 *
 * @sa sendPrivateData
 */
- (void)onPrivateData:(NSData*)data fromUser:(AVDUserId)fromId;

/** 房间应用层数据更改通知
 *
 * @param[in] key 应用层数据关键字。
 * @param[in] value 应用层数据关键字相关数据内容。
 *
 * @sa updateAppData
 */
- (void)onAppDataNotify:(NSString*)key value:(NSString*)value;

/** 房间状态通知
 *
 * @param[in] status 房间状态。
 *
 */
- (void)onRoomStatusNotify:(enum AVDRoomStatus)status;


/**
 邀请sip房间

 @param type 类型
 @param roomId 真实房间号
 @param addr sip地址
 @param status 状态
 @param msg msg
 */
- (void)onOutgoingInviteStatusNotify:(enum AVDOutgoingInviteType)type roomId:(NSString *)roomId addr:(NSString *)addr status:(enum AVDOutgoingStatus)status msg:(NSString *)msg;


@end



/**
* 房间接口类
*
* 房间接口定义了房间对象创建和释放、房间功能操作。
*/
@interface AVDRoom : NSObject

@property (nonatomic,weak) id <AVDRoomDelegate>delegate;        /**< 房间逻辑回调代理 */

@property (nonatomic,strong) AVDUserManager* userManager;       /**< 房间用户管理模块接口 */

/** 获取房间对象
 *
 * @note 房间对象的生命周期由AVD SDK来管理，应用层通过obtain获取一个房间对象，房间最终不使用的时候调用destory来释放。
 * @return 返回房间对象指针。
 */
+ (AVDRoom* ) obtain:(AVDRoomId)roomID;
/** 释放房间对象
 */
- (void) destory;

/** 当前用户加入房间
 *
 * @param[in] *user 用户信息：用户Id，用户名，用户数据等；当应用层必须传入有效的user.UserId，来唯一标识一个用户。
 * @param[in] *password 密码：如果是主持人请用主持人密码；如果是其他参会者，请用房间密码。
 * @param[in] joinresult 加房间回调接口。
 *
 * @return 返回错误代码。
 * @sa User
 */
- (AVDResult) joinWithUser:(AVDUser*)user delegate:(id<AVDRoomJoinDelegate>)joinresult;
- (AVDResult) joinWithUser:(AVDUser*)user password:(NSString*)password delegate:(id<AVDRoomJoinDelegate>)joinresult;
- (AVDResult) joinWithUser:(AVDUser*)user password:(NSString*)password delegate:(id<AVDRoomJoinDelegate>)joinresult oemToken:(NSString*)token;

/** 当前用户离开房间
 *
 * @param[in] reason 用户离开房间的原因代码，正常离开为AVD_OK。
 *
 * @note 当前用户离开房间后，当前房间对象和房间的各功能模块都处于离会状态，功能操作无效。
 * @return 返回错误代码。
 */
- (AVDResult) leave:(AVDResult)reason;				// leave myself

- (AVDResult) close;
/** 重新加入当前房间
 *
 * @note 当用户主动离开房间或者中间网络断线后离开房间后，可以重新调用此函数加入房间。
 * @return 返回错误代码。
 */
- (AVDResult) reJoin;

- (BOOL) isWorking;

/** 房间中踢出用户
 *
 * @param[in] reason 踢出用户的理由代码。
 * @param[in] userId 被踢出用户Id。
 *
 * @note 被踢用户将会在onLeaveIndication中接收到回调，被踢用户直接调用 leave 离开房间即可。
 * @return 返回错误代码。
 * @sa onLeaveIndication
 */
- (AVDResult) kickoutUser:(AVDResult)reason userId:(AVDUserId)userId;

/** 更新房间状态
 *
 * @param[in] status 房间状态。
 *
 * @return 返回错误代码。
 * @sa RoomStatus
 */
- (AVDResult) updateRoomStatus:(enum AVDRoomStatus)status;
/** 获取房间状态
 *
 * @return 返回房间状态。
 * @sa RoomStatus
 */
- (enum AVDRoomStatus) getRoomStatus;

/** 获取房间Id
 *
 * @return 返回房间Id。
 */
- (AVDRoomId) getRoomId;

/** 获取房间应用层Id
 *
 * @note 房间应用层Id在应用层安排当前房间的时候由应用层来指定，方便应用层查找、标示房间。
 * @return 返回房间应用层Id。
 */
- (NSString*) getAppRoomId;

/** 获取房间名
 *
 * @return 返回房间名。
 */
- (NSString*) getRoomName;

/** 获取房间主题
 *
 * @return 返回房间主题。
 */
- (NSString*) getRoomTopic;

/** 获取房间信息
 *
 * @return 返回房间信息。
 * @sa RoomInfo
 */
- (AVDRoomInfo*) getRoomInfo;

/** 透明通道，发送广播数据
 *
 * @param[in] *data 发送的数据指针。
 *
 * @note 此透明通道用于承载应用层数据，广播给所有房间内用户。
 * @return 返回错误代码。
 */
- (AVDResult) sendPublicData:(NSData*)data;

/** 透明通道，发送私有数据
 *
 * @param[in] *data 发送的数据指针。
 * @param[in] toId 目的用户Id。
 *
 * @note 此透明通道用于承载应用层数据，发送给房间内某一特定用户。
 * @return 返回错误代码。
 */
- (AVDResult) sendPrivateData:(NSData*)data toUserId:(AVDUserId)toId;

/** 返回应用层的房间数据
 *
 * @param[in] *key 房间数据关键字。
 *
 * @note 应用层的房间数据方便应用层在房间中保留关于房间的一些业务逻辑数据，可以获取和修改应用层的房间数据。
 * @return 返回应用层的相应关键字的房间数据。
 */
- (NSString*) getAppData:(NSString*)key;
/** 修改应用层的房间数据
 *
 * @param[in] *key 房间数据关键字。
 * @param[in] *value 房间数据对应关键字的信息内容
 *
 * @return 返回错误代码。
 */
- (AVDResult) updateAppData:(NSString*)key value:(NSString*)value;
/** 创建模拟设备Id，在导入音视频时可用
 *
 * @param[in] fakeId 自定义Id。
 * @return 模拟设备Id。
 * @note 模拟摄像头信息，接口会生成deviceId，生成规则："userId_"+（用户输入的fakeId), 此处deviceId不能包含'_'和'{'、'}'此三个字符。
 * @sa previewLocalCamera
 * @sa publishLocalCamera
 */
- (AVDDeviceId) createFakeDeviceID:(AVDDeviceId)fakeId;

/** 当前房间启用或关闭流量统计功能
 * @param[in] isEnable 启用或关闭。
 * @return 返回错误代码：
 * 	AVD_OK						成功
 */
- (AVDResult) enableStats:(BOOL)isEnable;
/** 获取房间的流量统计信息
 * @return 返回房间流量统计信息。
 * @sa RoomStats
 */
- (AVDRoomStats*) getRoomStats;
/** 获取某路媒体（音频或者视频）的流量统计信息
 * @param[in] deviceId 设备Id。
 * @return 返回媒体统计信息。
 * @sa MediaStats
 */
- (AVDMediaStats*) getMediaStats:(AVDDeviceId)deviceId;

//
/** 设置房间选项
 *
 * @param[in] type 房间选项类型。
 * @param[in] svalue 房间选项值。
 *
 * @return 返回错误代码。
 */
- (AVDResult) setOption:(enum AVDRoomOption)type value:(NSString*)svalue;
/** 获取房间选项
 *
 * @param[in] type 房间选项类型。
 *
 * @return 返回房间选项值。
 */
- (NSString*) getOption:(enum AVDRoomOption)type;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Disallow init and don't add to documentation
- (id)init __attribute__((
    unavailable("init is not a supported initializer for this class.")));
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

@end

#endif
