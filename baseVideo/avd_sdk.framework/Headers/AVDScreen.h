//
//  AVDVideo.h
//  avd_sdk
//
//  Created by skin on 15-7-21.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#ifndef avd_sdk_AVDScreen_h
#define avd_sdk_AVDScreen_h

#import "AVDModule.h"
#import "AVDVideoDevice.h"
#import "AVDVideoRenderer.h"

typedef NS_ENUM(NSUInteger, ScreenResolutionType){
    screen_resolution_360p,///<640*360
    screen_resolution_720p,///<1280*720
    screen_resolution_1080p,///<1920*1080
    screen_resolution_full,///<默认分辨率
};

@class AVDRoom;

/**
 * 房间中屏幕窗口共享模块回调接口.
 *
 * 屏幕窗口共享模块回调接口定义了房间中屏幕窗口共享相关的通知和异步操作返回。
 */
@protocol AVDScreenDelegate<NSObject>

@required
/// 通知
/** 屏幕窗口状态更改通知
 *
 * @param[in] status 屏幕窗口状态。
 * @param[in] fromId 屏幕窗口Id，唯一标示一个屏幕或者一个应用窗口。
 * @note 当屏幕窗口状态更改后，房间内所有用户接收到此通知。
 */
- (void) onScreenStatusNotify:(enum AVDDeviceStatus)status deviceId:(AVDDeviceId)fromId;

@optional
/** 屏幕窗口数据更改通知
 *
 * @param[in] level 屏幕窗口整形数据。
 * @param[in] *description 屏幕窗口字符串数据。
 * @param[in] fromId 屏幕窗口Id，唯一标示一个屏幕窗口。
 * @note 当屏幕窗口数据更改后，房间内所有用户接收到此通知, notify when publishLocalScreen(Camera), updateScreenData。
 */
- (void) onScreenDataNotify:(NSInteger)level description:(NSString*)description deviceId:(AVDDeviceId)fromId;
/** 屏幕窗口视频发布通知
 *
 * @param[in] *screen 屏幕窗口信息，屏幕信息中level和description为应用层数据，应用层可以使用这些字段保存次屏幕窗口相关的应用逻辑数据，方便标示、订阅视频。
 *
 * @note 当屏幕窗口视频发布时，房间内所有用户接收到此通知；因通知的重要程度，将从onScreenStatusNotify中分离出此状态。
 * @sa publishScreen
 */
- (void) onPublishScreenNotify:(AVDVideoDevice *)screen;
/** 屏幕窗口视频取消发布通知
 *
 * @param[in] *screen 屏幕窗口信息。
 *
 * @note 当屏幕窗口视频取消发布时，房间内所有用户接收到此通知；因通知的重要程度，将从onScreenStatusNotify中分离出此状态。
 * @sa unpublishScreen
 */
- (void) onUnpublishScreenNotify:(AVDVideoDevice *)screen;

/// 异步返回
/** 本用户订阅屏幕窗口异步返回
 *
 * @param[in] result 错误代码。
 * @param[in] fromId 屏幕窗口Id，唯一标示一个屏幕或者一个应用窗口。
 *
 * @sa subscrible
 */
- (void) onSubscribeResult:(AVDResult)result deviceId:(AVDDeviceId)fromId;
/** 本用户取消订阅屏幕窗口异步返回
 *
 * @param[in] result 错误代码。
 * @param[in] fromId 屏幕窗口Id，唯一标示一个屏幕或者一个应用窗口。
 *
 * @sa unsubscribe
 */
- (void) onUnsubscribeResult:(AVDResult)result deviceId:(AVDDeviceId)fromId;

@end


/**
	* 房间中屏幕窗口共享模块接口.
	*
	* 房间屏幕窗口共享模块定义房间中屏幕窗口共享相关功能接口。
	*/
@interface AVDScreen : AVDModule

@property (nonatomic,weak) id <AVDScreenDelegate>delegate;              /**< 屏幕窗口共享模块回调接口代理 */

@property (nonatomic,retain,readonly) NSMutableArray* publishedScreens; /**< 已共享屏幕窗口信息列表，数组中存放AVDVideoDevice对象 */

@property (nonatomic,retain,readonly) NSMutableArray* subscribedScreens;/**< 已订阅屏幕窗口信息列表，数组中存放AVDVideoDevice对象 */

/** 获取屏幕共享功能模块对象
 *
 * @param[in] *room 房间对象指针
 * @return 返回屏幕共享模块对象。
 */
+ (AVDScreen* ) getScreen:(AVDRoom*)room;


/** 订阅共屏屏幕窗口视频
 *
 * @param[in] deviceId 屏幕窗口Id，唯一标示一路共享的屏幕窗口视频。
 * @return 返回错误代码。
 * @note 订阅操作为异步操作，操作结果在 onSubscribeResult 中返回。
 * @sa onSubscribeResult
 */
- (AVDResult) subscribe:(AVDDeviceId)deviceId;
/** 取消订阅共屏屏幕窗口视频
 *
 * @param[in] deviceId 屏幕窗口Id，唯一标示一路共享的屏幕窗口视频。
 * @return 返回错误代码。
 * @note 取消订阅操作为异步操作，操作结果在 onUnsubscribeResult 中返回。
 * @sa onUnsubscribeResult
 */
- (AVDResult) unsubscribe:(AVDDeviceId)deviceId;
/** 判断屏幕窗口是否已经被本用户订阅
 */
- (BOOL) isScreenSubscribed:(AVDDeviceId)deviceId;

/// render screen
/** 关联共享的屏幕窗口视频数据和显示对象，在render中显示视频
 *
 * @param[in] deviceId 屏幕窗口Id，唯一标示一路共享的屏幕窗口视频。
 * @param[in] render 显示对象接口指针。
 *
 * @note 视频数据可以在多个显示对象上显示，而一个显示对象某一时刻只能显示一路视频。
 *		在屏幕窗口视频发布到房间中，或者远端屏幕窗口视频订阅成功后，调用此接口完成视频与显示对象的对接，从而在显示对象中显示视频。
 * @return 返回错误代码。
 * @sa IVideoRender
 */
- (AVDResult) attachRenderWithDeviceId:(AVDDeviceId)deviceId render:(id<AVDVideoRenderer>)render;
/** 解除屏幕窗口视频的所有显示对象关联
 *
 * @param[in] deviceId 屏幕窗口Id，唯一标示一路共享的屏幕窗口视频。
 * @return 返回错误代码。
 * @sa IVideoRender
 */
- (AVDResult) detachRenderWithDeviceId:(AVDDeviceId)deviceId;
/** 解除某一显示对象与屏幕窗口视频的关联
 *
 * @param[in] render 显示对象接口指针。
 * @sa IVideoRender
 */
- (AVDResult) detachRenderWithRender:(id<AVDVideoRenderer>) render;


/**
 发布屏幕共享

 @param withAudio 是否包含麦克风
 @return 错误代码
 */
- (AVDResult) publishScreen:(BOOL)withAudio DEPRECATED_MSG_ATTRIBUTE("Please use publishScreen:(ScreenResolutionType)type fps:(int)fps");


/**
 发布指定分辨率屏幕共享
 @param type 分辨率e类型
 @param fps fps
 @return 错误代码
 */
- (AVDResult) publishScreen:(ScreenResolutionType)type fps:(int)fps;

/**
 发布屏幕共享可以指定坐标

 @param catX x
 @param catY y
 @param catW w
 @param catH h
 @return 错误代码
 */
- (AVDResult) publishScreen:(NSInteger)catX catY:(NSInteger)catY catW:(NSInteger)catW catH:(NSInteger)catH ;


/**
 取消发布

 @return 错误代码
 */
- (AVDResult) unpublishScreen;


/**
 更新桌面共享信息

 @param deviceId 设备id
 @param level 0
 @param description 描述信息{"video_name":"客服"}
 @return 错误代码
 */
- (AVDResult)updateScreenData:(AVDDeviceId)deviceId level:(NSInteger)level description:(NSString*)description;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Disallow init and don't add to documentation
- (id)init __attribute__((
    unavailable("init is not a supported initializer for this class.")));
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

@end

#endif
