//
//  AVDVideo.h
//  avd_sdk
//
//  Created by skin on 15-7-21.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#ifndef avd_sdk_AVDVideo_h
#define avd_sdk_AVDVideo_h

#import "AVDModule.h"
#import "AVDDevice.h"
#import "AVDCamera.h"
#import "AVDVideoRenderer.h"
#import "AVDFakeVideoCapturer.h"
#import "CoreVideo/CVPixelBuffer.h"

typedef enum : NSUInteger {
    AVDCaptureOrientation_Portrait = 1 << 0 ,//home btn bottom
    AVDCaptureOrientation_UpsideDown = 1 << 1,// home top
    AVDCaptureOrientation_LandscapeLeft = 1 << 2,// home left
    AVDCaptureOrientation_LandscapeRight = 1 << 3,// home right
} AVDCaptureOrientation;

@class AVDRoom;

/**
 * 房间中视频模块回调接口.
 *
 * 视频模块回调接口定义了房间中视频相关的通知和视频异步操作返回。
 */
@protocol AVDVideoDelegate<NSObject>

@required
/// 通知
/** 摄像头状态更改通知
 *
 * @param[in] status 摄像头状态。
 * @param[in] fromId 摄像头Id，唯一标示一个摄像头。
 * @note 当摄像头状态更改后，房间内所有用户接收到此通知。
 */
- (void) onCameraStatusNotify:(enum AVDDeviceStatus)status deviceId:(AVDDeviceId)fromId;

@optional
/** 摄像头数据更改通知
 *
 * @param[in] level 摄像头整形数据。
 * @param[in] *description 摄像头字符串数据。
 * @param[in] fromId 摄像头Id，唯一标示一个摄像头。
 * @note 当摄像头数据更改后，房间内所有用户接收到此通知, notify when publishLocalCamera(Camera), updateCameraData。
 */
- (void) onCameraDataNotify:(NSInteger)level description:(NSString*)description deviceId:(AVDDeviceId)fromId;
/** 摄像头视频发布通知
 *
 * @param[in] *camera 摄像头信息，摄像头信息中level和description为应用层数据，应用层可以使用这些字段保存次摄像头视频相关的应用逻辑数据，方便标示、订阅视频。
 *
 * @note 当摄像头视频发布时，房间内所有用户接收到此通知；因通知的重要程度，将从onCameraStatusNotify中分离出此状态。
 * @sa publishLocalCamera
 * @sa publishLocalAssist
 */
- (void) onPublishCameraNotify:(AVDCamera*)camera;
/** 摄像头视频取消发布通知
 *
 * @param[in] *camera 摄像头信息。
 *
 * @note 当摄像头视频取消发布时，房间内所有用户接收到此通知；因通知的重要程度，将从onCameraStatusNotify中分离出此状态。
 * @sa unpublishLocalCamera
 * @sa unpublishLocalAssist
 */
- (void) onUnpublishCameraNotify:(AVDCamera*)camera;

/// 异步返回
/** 本用户订阅视频异步返回
 *
 * @param[in] result 错误代码。
 * @param[in] fromId 摄像头Id，唯一标示一路视频。
 *
 * @sa subscribe
 */
- (void) onSubscribeResult:(AVDResult)result deviceId:(AVDDeviceId)fromId;
/** 本用户取消订阅视频异步返回
 *
 * @param[in] result 错误代码。
 * @param[in] fromId 摄像头Id，唯一标示一路视频。
 *
 * @sa unsubscribe
 */
- (void) onUnsubscribeResult:(AVDResult)result deviceId:(AVDDeviceId)fromId;
/** 本用户发布摄像头视频异步返回
 *
 * @param[in] result 错误代码。
 * @param[in] fromId 摄像头Id，唯一标示一路视频。
 *
 * @sa publishLocalCamera
 * @sa publishLocalAssist
 */
- (void) onPublishLocalResult:(AVDResult)result deviceId:(AVDDeviceId)fromId;
/** 本用户取消发布摄像头视频异步返回
 *
 * @param[in] result 错误代码。
 * @param[in] fromId 摄像头Id，唯一标示一路视频。
 *
 * @sa unpublishLocalCamera
 * @sa unpublishLocalAssist
 */
- (void) onUnpublishLocalResult:(AVDResult)result deviceId:(AVDDeviceId)fromId;

@end


/**
	* 房间中视频模块接口.
	*
	* 房间视频模块定义房间中视频发布、订阅功能接口。
	*/
@interface AVDVideo : AVDModule

@property (nonatomic,weak) id <AVDVideoDelegate>delegate;              /**< 视频模块回调接口代理 */

/** 已共享摄像头信息列表
 * @note 摄像头列表包含本地发布的摄像头和房间中其他用户的所有正在发布的摄像头，摄像头视频要在界面上显示，远端摄像头需要首先做subcribe；
 *		而本地摄像头显示时不需要subscribe，应用层开发时需要注意。publishedCameras中保存的是AVDCamera对象。
 */
@property (nonatomic,retain,readonly) NSMutableArray* publishedCameras;
/** 已订阅摄像头信息列表
 * @note subscribedCameras中保存的是AVDCamera对象。
 */
@property (nonatomic,retain,readonly) NSMutableArray* subscribedCameras;

/** 获取视频功能模块对象
 *
 * @param[in] *room 房间对象指针
 * @return 返回视频模块对象。
 */
+ (AVDVideo* ) getVideo:(AVDRoom*)room;

//
/** 预览本地缺省摄像头视频
 *
 * @param[in] render 显示对象接口指针
 * @note 本地视频在发布到会议前，可以调用此接口进行视频预览；视频发布到会议中后，需要使用attachRender接口来进行视频显示，此时此接口无效。
 * @return 返回错误代码。
 * @sa IVideoRender
 */
- (AVDResult) previewLocalCamera:(id<AVDVideoRenderer>)render;
/** 取消预览缺省摄像头视频
 * @return 返回错误代码。
 */
- (AVDResult) unpreviewLocalCamera;
/** 发布缺省摄像头视频
 *
 * @return 返回错误代码。
 * @note 发布操作为异步操作，操作结果在 onPublishLocalResult 中返回。
 * @sa onPublishLocalResult
 */
- (AVDResult) publishLocalCamera;
/** 发布摄像头视频
 *
 * @param[in] camera 摄像头信息。
 * @return 返回错误代码。
 * @note 发布操作为异步操作，操作结果在 onPublishLocalResult 中返回。
 * @sa onPublishLocalResult
 */
- (AVDResult) publishLocalCameraWithCamera:(AVDCamera*)camera;
/** 取消发布缺省摄像头视频
 *
 * @return 返回错误代码。
 * @note 取消发布操作为异步操作，操作结果在 onUnpublishLocalResult 中返回。
 * @sa onUnpublishLocalResult
 */
- (AVDResult) unpublishLocalCamera;
/** 取消发布摄像头视频
 *
 * @param[in] deviceId 摄像头Id，唯一标示一路摄像头视频。
 * @return 返回错误代码。
 * @note 取消发布操作为异步操作，操作结果在 onUnpublishLocalResult 中返回。
 * @sa onUnpublishLocalResult
 */
- (AVDResult) unpublishLocalCamera:(AVDDeviceId)deviceId;

/** 判断是否已经打开本地摄像头
 */
- (BOOL) ispublishLocalCamera;

/** 预览本机前置或者后置摄像头视频
 *
 * @param[in] type 摄像头类型。
 * @param[in] render 显示对象接口指针
 * @note 在前后置摄像头操作模式下有效；摄像头模式设置在AVDEngine的SetOption接口中实现；取消预览接口为unpreviewLocalCamera，无需参数。
 * @return 返回错误代码；若不支持此操作返回 Err_Not_Available。
 * @sa IVideoRender
 * @sa CameraType
 */
- (AVDResult) previewLocalCamera:(enum AVDCameraType)type render:(id<AVDVideoRenderer>)render;
/** 预览模拟摄像头视频
 *
 * @param[in,out] fakeDevice 模拟摄像头信息，接口会生成deviceId，生成规则："userId_"+（用户输入的deviceId), 此处deviceId不能包含'_'和'{'、'}'此三个字符。
 * @param[in] *capturer 模拟摄像头视频输入接口。
 * @param[in] *render 显示对象接口指针
 * @return 返回错误代码。
 * 模拟摄像头用于在房间中导入特定已经存在的视频数据流，比如视频文件、录播系统视频流等。
 * @sa FakeVideoCapturer
 * @note render 允许被设置为NULL。
 *       fakeDevice.id 会按照3tee设备id规则重新构造成。
 * 注意：此函数必须用 unpreviewLocalCamera(String deviceId)来取消发布，不能用无参数函数；
 */
- (AVDResult) previewLocalCamera:(AVDCamera*)fakeDevice capturer:(AVDFakeVideoCapturer*)capturer render:(id<AVDVideoRenderer>)render;
/** 取消预览摄像头视频
 * @param[in] deviceId 摄像头Id。
 * @return 返回错误代码。
 */
- (AVDResult) unpreviewLocalCamera:(AVDDeviceId)deviceId;
/** 发布特定类型摄像头视频
 *
 * @param[in] type 摄像头类型。
 * @return 返回错误代码；若不支持此操作返回 Err_Not_Available。
 * @note 发布操作为异步操作，操作结果在 onPublishLocalResult 中返回。在前后置摄像头操作模式下有效；取消预览接口为unpublishLocalCamera，无需参数。
 * @sa onPublishLocalResult
 */
- (AVDResult) publishLocalCamera:(enum AVDCameraType)type;
/** 发布模拟摄像头视频
 *
 * @param[in,out] fakeDevice 模拟摄像头信息，接口会生成deviceId，生成规则："userId_"+（用户输入的deviceId), 此处deviceId不能包含'_'和'{'、'}'此三个字符。
 * @param[in]     capturer 模拟摄像头视频输入接口。
 * @return 返回错误代码。
 * @note 发布操作为异步操作，操作结果在 onPublishLocalResult 中返回。
 * 模拟摄像头用于在房间中导入特定已经存在的视频数据流，比如视频文件、录播系统视频流等。
 * 注意：此函数必须用 unpreviewLocalCamera(String deviceId)来取消发布，不能用无参数函数；
 * @sa onPublishLocalResult
 * @sa FakeVideoCapturer
 */
- (AVDResult) publishLocalCamera:(AVDCamera*)fakeDevice capturer:(AVDFakeVideoCapturer*)capturer;
/** 切换特定类型摄像头视频源
 * @note 在前后置摄像头操作模式下有效。
 * @return 返回错误代码；若不支持此操作返回 Err_Not_Available。
 */
- (AVDResult) switchToLocalCamera;
/** 切换到特定类型摄像头视频源，同上
 * @param[in] toType 摄像头类型。
 */
- (AVDResult) switchToLocalCameraWithType:(enum AVDCameraType)toType;
/** 获取当前使用的摄像头类型
 *
 * @note 在前后置摄像头操作模式下有效。
 * @return 返回摄像头类型。
 */
- (enum AVDCameraType) getCurrentCameraType;
/** 摄像头数据更改
 *
 * @param[in] deviceId 摄像头Id，唯一标示一个摄像头。
 * @param[in] level 摄像头整形数据。
 * @param[in] description 摄像头字符串数据。
 * @sa onCameraDataNotify
 */
- (AVDResult) updateCameraData:(AVDDeviceId)deviceId level:(NSInteger)level description:(NSString*)description;
/** 获取指定类型的本机摄像头信息
 *
 * @param[in] type 摄像头类型。
 * @return 返回摄像头设备信息。
 * @sa CameraType
 */
- (AVDCamera*) getCamera:(enum AVDCameraType)type;
/** 获取指定设备Id的摄像头信息
 *
 * @param[in] deviceId 设备Id。
 * @return 返回摄像头信息。
 * @note 可以返回本地用户和远端用户的摄像头信息。
 */
- (AVDCamera*) getCameraWithId:(AVDDeviceId)deviceId;

/// subscribe and publish list
/** 订阅摄像头视频
 *
 * @param[in] deviceId 摄像头Id，唯一标示一路摄像头视频。
 * @return 返回错误代码。
 * @note 订阅操作为异步操作，操作结果在 onSubscribeResult 中返回。
 * @sa onSubscribeResult
 */
- (AVDResult) subscribe:(AVDDeviceId)deviceId;
/** 订阅摄像头视频指定视频主辅流
 *
 * @param[in] deviceId 摄像头Id，唯一标示一路摄像头视频。
 * @param[in] stream 指定视频流（主流，辅流1，辅流2）。
 * @return 返回错误代码。
 * @note 订阅说明如同名接口所描述。
 * @sa StreamType
 */
- (AVDResult) subscribe:(AVDDeviceId)deviceId stream:(enum AVDStreamType)stream;
/** 订阅摄像头视频指定视频质量视频
 *
 * @param[in] deviceId 摄像头Id，唯一标示一路摄像头视频。
 * @param[in] quality 订阅视频的清晰度要求。
 * @return 返回错误代码。
 * @note 订阅说明如同名接口所描述。
 *  3.0版本后支持视频清晰度切换：发布视频时设置视频最大分辨率，通过此接口和changeSubscribedVideoQuality接口可以在整个
 *  房间层级来更改订阅的视频的清晰度，但要求房间中所有人清晰度要求一致才生效（通过远端分辨率更改实现）。
 *  如最大分辨率为 quality_high - 1280x720; 则：quality_normal - 640x360(high/2); quality_low - 320x240(normal/2)
 * @sa VideoQuality
 * @sa changeSubscribedVideoQuality
 */
- (AVDResult) subscribe:(AVDDeviceId)deviceId quality:(enum AVDQualityType)quality;
/** 更改订阅视频的视频质量
 *
 * @param[in] deviceId 摄像头Id，唯一标示一路摄像头视频。
 * @param[in] quality 视频质量。
 * @return 返回错误代码。
 * @sa VideoQuality
 */
- (AVDResult) changeSubscribedVideoQuality:(AVDDeviceId)deviceId quality:(enum AVDQualityType)quality;
/** 取消订阅摄像头视频
 *
 * @param[in] deviceId 摄像头Id，唯一标示一路摄像头视频。
 * @return 返回错误代码。
 * @note 取消订阅操作为异步操作，操作结果在 onUnsubscribeResult 中返回。
 * @sa onUnsubscribeResult
 */
- (AVDResult) unsubscribe:(AVDDeviceId)deviceId;

/** 判断摄像头是否已经发布到房间中
 */
- (BOOL) isCameraPublished:(AVDDeviceId)fromId;
/** 判断摄像头是否已经被本用户订阅
 */
- (BOOL) isCameraSubscribed:(AVDDeviceId)fromId;
/// remote camera control
/** 命令远端用户发布某一摄像头视频
 * @param[in] *device 摄像头信息。
 * @return 返回错误代码。
 */
- (AVDResult) remotecmdPublishCamera:(AVDCamera*)device;
/** 命令远端用户取消发布摄像头视频
 * @param[in] deviceId 摄像头Id。
 * @return 返回错误代码。
 */
- (AVDResult) remotecmdUnpublishCamera:(AVDDeviceId)deviceId;

/// render video
/** 关联视频数据和显示对象，在render中显示视频
 *
 * @param[in] deviceId 摄像头Id，唯一标示一路共享的摄像头视频。
 * @param[in] render 显示对象接口指针。
 *
 * @note 视频数据可以在多个显示对象上显示，而一个显示对象某一时刻只能显示一路视频。
 *		在本地视频发布到房间中，或者远端视频订阅成功后，调用此接口完成视频与显示对象的对接，从而在显示对象中显示视频。
 * @return 返回错误代码。
 * @sa IVideoRender
 */
- (AVDResult) attachRenderWithDeviceId:(AVDDeviceId)deviceId render:(id<AVDVideoRenderer>)render;
/** 解除摄像头视频数据的所有显示对象关联
 *
 * @param[in] deviceId 摄像头Id，唯一标示一路共享的摄像头视频。
 * @return 返回错误代码。
 * @sa IVideoRender
 */
- (AVDResult) detachRenderWithDeviceId:(AVDDeviceId)deviceId;
/** 解除某一显示对象与摄像头视频数据的关联
 *
 * @param[in] render 显示对象接口指针。
 * @sa IVideoRender
 */
- (AVDResult) detachRenderWithRender:(id<AVDVideoRenderer>)render;

/** 获取某一用户的缺省摄像头对象
 *
 * @param[in] userId 用户号。
 */
- (AVDCamera *) getCameraByUserId:(AVDUserId)userId;

///
/** 设置获取视频数据回调接口,此数据仅回调一份数据：数据为主视频+各个Overlay的视频，视频大小为主视频大小；如使用ILivecast接口，不需要设置此接口。
 *
 * @param[in] render 显示对象接口指针。
 * @return 返回错误代码。
 * @sa IVideoRender
 * @note 显示且回调数据时调用setVideoMixerListener，设置render为AVDVideoView，同时对AVDVideoView的callbacks代理设置回调接口；
 *       只需要回调数据时调用setVideoMixerListener2；
 *       两个函数只能调用一个
 */
- (AVDResult) setMixerDateRender:(id<AVDVideoRenderer>)render;
/** 同上：
 * @param[in] cb 回调数据接口指针。
 */
- (AVDResult) setMixerDateListener:(id<AVDVideoRendererCallBacks>)cb;
/** 设置回调视频数据的视频主视频
 *
 * @param[in] deviceId 摄像头Id，唯一标示一路共享的摄像头视频。
 * @return 返回错误代码。
 * @note 设置混屏的主视频等效于，setMixerVideoSize为主视频大小，同时addMixerOverlayVideo将主视频加入到混屏中，且充满全屏。
 */
- (AVDResult) setMixerMainVideo:(AVDDeviceId)deviceId;
/** 设置混频后视频数据的尺寸
 *
 * @param[in] width 视频图像宽。
 * @param[in] height 视频图像高。
 * @param[in] background 背景图。
 * @return 返回错误代码。
 * @sa addMixerOverlayVideo
 */
- (AVDResult) setMixerVideoSize:(NSUInteger)width height:(NSUInteger)height background:(NSString*)background;
/** 添加视频到主视频特定位置
 *
 * @param[in] deviceId 摄像头Id，唯一标示一路共享的摄像头视频。
 * @param[in] zorder 多个视频覆盖时，前后位置，zorder越小，视频越在前面，后面会被覆盖；取值0-n
 * @param[in] x 此视频在主视频的左上角左边位置，即x坐标，取值0.0~1.0，内部取值为：width (主视频）x X
 * @param[in] y 此视频在主视频的左上角上边位置，即y坐标，取值0.0~1.0，内部取值为：height(主视频）x Y
 * @param[in] w 此视频在主视频的宽度比例，取值0.0~1.0，内部取值为：width (主视频）x W
 * @param[in] h 此视频在主视频的高度比例，取值0.0~1.0，内部取值为：height(主视频）x H
 * @return 返回错误代码。
 * @sa addMixerOverlayVideo
 */
- (AVDResult) addMixerOverlayVideo:(AVDDeviceId)deviceId zorder:(NSUInteger)zorder x:(CGFloat)x y:(CGFloat)y w:(CGFloat)w h:(CGFloat)h;
/** 添加视频到主视频特定位置
 *
 * @param[in] deviceId 摄像头Id，唯一标示一路共享的摄像头视频。
 * @param[in] zorder 多个视频覆盖时，前后位置，zorder越小，视频越在下层，会被覆盖；取值0-10
 * @param[in] x 此视频在左上角左边位置，即x坐标，
 * @param[in] y 此视频在左上角上边位置，即y坐标，
 * @param[in] w 此视频宽度
 * @param[in] h 此视频高度
 * @return 返回错误代码。
 * @sa addMixerOverlayVideo
 */
- (AVDResult) addMixerOverlayVideoPixel:(AVDDeviceId)deviceId zorder:(NSUInteger)zorder x:(NSUInteger)x y:(NSUInteger)y w:(NSUInteger)w h:(NSUInteger)h;
/** 更新附加视频在主视频上显示的位置
 *
 * @param[in] deviceId 摄像头Id，唯一标示一路共享的摄像头视频。
 * @param[in] zorder 多个视频覆盖时，前后位置，zorder越小，视频越在前面，后面会被覆盖；取值0-n
 * @param[in] x 此视频在主视频的左上角左边位置，即x坐标，取值0.0~1.0，内部取值为：width (主视频）x X
 * @param[in] y 此视频在主视频的左上角上边位置，即y坐标，取值0.0~1.0，内部取值为：height(主视频）x Y
 * @param[in] w 此视频在主视频的宽度比例，取值0.0~1.0，内部取值为：width (主视频）x W
 * @param[in] h 此视频在主视频的高度比例，取值0.0~1.0，内部取值为：height(主视频）x H
 * @return 返回错误代码。
 */
- (AVDResult) updateMixerOverlayVideo:(AVDDeviceId)deviceId zorder:(NSUInteger)zorder x:(CGFloat)x y:(CGFloat)y w:(CGFloat)w h:(CGFloat)h;
/** 更新附加视频在主视频上显示的位置
 *
 * @param[in] deviceId 摄像头Id，唯一标示一路共享的摄像头视频。
 * @param[in] zorder 多个视频覆盖时，前后位置，zorder越小，视频越在下层，会被覆盖；取值0-10
 * @param[in] x 此视频在左上角左边位置，即x坐标，
 * @param[in] y 此视频在左上角上边位置，即y坐标，
 * @param[in] w 此视频宽度
 * @param[in] h 此视频高度
 * @return 返回错误代码。
 */
- (AVDResult) updateMixerOverlayVideoPixel:(AVDDeviceId)deviceId zorder:(NSUInteger)zorder x:(NSUInteger)x y:(NSUInteger)y w:(NSUInteger)w h:(NSUInteger)h;
/** 移除主视频上的某一视频
 *
 * @param[in] deviceId 摄像头Id，唯一标示一路共享的摄像头视频。
 * @return 返回错误代码。
 */
- (AVDResult) removeMixerOverlayVideo:(AVDDeviceId)deviceId;
/** 清理掉所有的混屏视频，包括主视频；如果需要再次开启合屏，需要重新设置主视频和Overlay视频。
 *
 * @return 返回错误代码。
 */
- (AVDResult) clearMixerVideos;


- (AVDDeviceId) getLocalDefaultCameraId;

/** 设置视频动态码率调整的范围，最小和最大比特率，
 *
 * @param[in] deviceId 视频设备对应ID。
 * @param[in] minBitrateBps 最小比特率,单位bps。
 * @param[in] maxBitrateBps  最大比特率,单位bps。
 * @return 返回错误代码。
 * @note 例如30k/s = 30*8*1000 bps(bits/s)。当min和max相等时，码率固定，将不会动态调整。
 */
- (AVDResult) setVideoBitrate:(AVDDeviceId)deviceId min:(NSInteger)minBitrateBps max:(NSInteger)maxBitrateBps;

// setting video param

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Disallow init and don't add to documentation
- (id)init __attribute__((
    unavailable("init is not a supported initializer for this class.")));
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


+ (AVDResult) nv12ConvertPixelBuffer:(CVPixelBufferRef)pixelBuffer toData:(NSMutableData*)data;


/**
 设置摄像头支持视频采集方向

 @param Orientation Orientation
 */
+ (BOOL)setCapturerSupportOrientation:(AVDCaptureOrientation)orientation;

/**
 设置是否支持旋转

 @param autorotate
 */
+ (void)setAutorotate:(BOOL)autorotate;


/**
 设置摄像头默认采集方向

 @param Orientation 
 */
+ (void)setCapturerDefaultOrientation:(AVDCaptureOrientation)Orientation;

@end

#endif
