//
//  AVDVideoMixer.h
//  avd_sdk
//
//  Created by skin on 15-7-21.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#ifndef avd_sdk_AVDVideoMixer_h
#define avd_sdk_AVDVideoMixer_h

#import "AVDCommon.h"
#import "AVDVideoRenderer.h"

/** 视频混频布局类型 */
enum AVDMixerVideoLayoutType {
    vl_auto_overlay,					/**< 自动布局-窗口中重叠视频 */
    vl_auto_segment,					/**< 自动布局-分割窗口排列视频 */
    vl_manual,							/**< 手动布局  */
};

/**
 * 视频混屏模块接口.
 *
 * 视频混屏模块定义房间中视频混屏、布局、订阅功能接口。
 */
@interface AVDVideoMixer : NSObject

@property (nonatomic,assign) enum AVDMixerVideoLayoutType layoutType;   /**< 各子视频在混屏视频中的布局类型 */

@property (nonatomic,assign) CGSize mixerSize;                          /**< 合屏视频图像宽,高 */

@property (nonatomic,assign) enum AVDScalingType scaling;               /**< 视频合屏时采用的拉伸方式 */

//自动布局(layout auto)：设置自动布局参数和主视频后，sdk自动来布局子视频组合成混屏视频
/** 切换混屏视频的主视频（若主视频掉线，本地主播视频切为主视频）
 *
 * @param[in] userId 摄像头Id，唯一标示一路共享的摄像头视频。
 * @return 返回错误代码。
 * @note 混屏视频的主视频在vl_auto_overlay模式下可以做切换，缺省为主播视频
 */
- (AVDResult) setMainVideo:(AVDUserId)userId; // auto layout vl_auto_overlay used.
/** 混屏视频自动布局的布局参数设置
 *
 * @param[in] isTopdown  各子视频在混屏视频上的排列顺序，true: 从上往下（左到右）排列； false: 从下往上（左到右）排列
 * @param[in] w			 各子视频相对混屏视频的宽度比例，取值0.0~1.0，内部取值为：width (混屏视频）x W
 * @param[in] h			 各子视频相对混屏视频的高度比例，取值0.0~1.0，内部取值为：height(混屏视频）x H
 * @param[in] x_begin    初始子视频在混屏视频的左上角左边位置，即x坐标，取值0.0~1.0，内部取值为：width (混屏视频）x x_begin
 * @param[in] y_begin    初始子视频在混屏视频的左上角上边位置，即y坐标，取值0.0~1.0，内部取值为：height(混屏视频）x y_begin
 * @return 返回错误代码。
 * @note 缺省设置为：vl_auto_overlay布局类型，从下往上排列; w=h=0.3f; x_begin=0.7f; y_begin=0.7f;
 */
- (AVDResult) autoLayoutParams:(BOOL)isTopdown w:(CGFloat)w h:(CGFloat)h x_begin:(CGFloat)x_begin y_begin:(CGFloat)y_begin; // auto layout used.
//手动布局(layout manual)：完全手动布局整个混屏视频，可以将一个个子视频排布在混屏视频的任意位置
/** 添加视频到混屏视频特定位置
 *
 * @param[in] userId 摄像头Id，唯一标示一路共享的摄像头视频。
 * @param[in] zorder 多个视频覆盖时，前后位置，zorder越小，视频越在前面，后面会被覆盖；取值0-n
 * @param[in] x 此视频在混屏视频的左上角左边位置，即x坐标，取值0.0~1.0，内部取值为：width (混屏视频）x X
 * @param[in] y 此视频在混屏视频的左上角上边位置，即y坐标，取值0.0~1.0，内部取值为：height(混屏视频）x Y
 * @param[in] w 此视频在混屏视频的宽度比例，取值0.0~1.0，内部取值为：width (混屏视频）x W
 * @param[in] h 此视频在混屏视频的高度比例，取值0.0~1.0，内部取值为：height(混屏视频）x H
 * @return 返回错误代码。
 * @sa addMixerOverlayVideo
 */
- (AVDResult) addSubVideo:(AVDUserId)userId; // auto layout used.
- (AVDResult) addSubVideo:(AVDUserId)userId zorder:(NSUInteger)zorder x:(CGFloat)x y:(CGFloat)y w:(CGFloat)w h:(CGFloat)h; // manual layout used.
/** 更新附加视频在混屏视频上显示的位置
 *
 * @param[in] userId 摄像头Id，唯一标示一路共享的摄像头视频。
 * @param[in] zorder 多个视频覆盖时，前后位置，zorder越小，视频越在前面，后面会被覆盖；取值0-n
 * @param[in] x 此视频在混屏视频的左上角左边位置，即x坐标，取值0.0~1.0，内部取值为：width (混屏视频）x X
 * @param[in] y 此视频在混屏视频的左上角上边位置，即y坐标，取值0.0~1.0，内部取值为：height(混屏视频）x Y
 * @param[in] w 此视频在混屏视频的宽度比例，取值0.0~1.0，内部取值为：width (混屏视频）x W
 * @param[in] h 此视频在混屏视频的高度比例，取值0.0~1.0，内部取值为：height(混屏视频）x H
 * @return 返回错误代码。
 */
- (AVDResult) updateSubVideo:(AVDUserId)userId zorder:(NSUInteger)zorder x:(CGFloat)x y:(CGFloat)y w:(CGFloat)w h:(CGFloat)h; // manual layout used.
/** 移除混屏视频上的某一视频
 *
 * @param[in] userId 摄像头Id，唯一标示一路共享的摄像头视频。
 * @return 返回错误代码。
 */
- (void) removeSubVideo:(AVDUserId)userId; // auto/manual layout used.

/** 清理掉所有的混屏视频，包括主视频；如果需要再次开启合屏，需要重新设置混屏视频和Overlay视频。
 *
 * @return 返回错误代码。
 */
- (void) clearSubVideos; // auto/manual layout used.

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Disallow init and don't add to documentation
- (id)init __attribute__((
    unavailable("init is not a supported initializer for this class.")));
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

@end

#endif
