//
//  AVDWhiteboard.h
//  avd_sdk
//
//  Created by 盛锋 on 2018/5/3.
//  Copyright © 2018年 t3ee. All rights reserved.
//



#import "AVDCommon.h"
#import "AVDWhiteboardInfo.h"
#import "AVDRoom.h"
#import "AVDModule.h"

@class AVDAnnotaion;

@protocol AVDWhiteboardDelegate <NSObject>

@optional

/**
 *  接收到白板创建消息通知
 *
 *  @param whiteboardInfo 白板信息
 */
- (void)onCreateBoardNotify:(AVDWhiteboardInfo *)whiteboardInfo;

/**
 *  接收到白板移除建消息通知
 *
 *  @param whiteboardId 移除的白板id
 */
- (void)onRemoveBoardNotify:(AVDBoardId)whiteboardId;

/**
 *  接收到白板更新消息通知
 *
 *  @param whiteboardInfo 白板信息
 */
- (void)onUpdateBoardNotify:(AVDWhiteboardInfo *)whiteboardInfo;


/**
 *  共享白板消息通知
 *
 *  @param whiteboardInfo 白板信息
 */
- (void)onShareBoardNotify:(AVDWhiteboardInfo *)whiteboardInfo;

/**
 *  关闭白板工作
 *
 *  @param whiteboardId 移除的白板id
 */
- (void)onCloseBoardNotify:(AVDBoardId)whiteboardId;


@end


@interface AVDWhiteboard : AVDModule

@property (nonatomic,weak) id <AVDWhiteboardDelegate>delegate;              /**< 白板模块回调接口代理 */

@property (nonatomic,retain,readonly) NSMutableArray* publishedBoards;
@property (nonatomic,retain,readonly) NSMutableArray* sharedBoards;

/**
 *  获取白板功能模块对象
 *
 *  @param room room 房间对象指针
 *
 *  @return 返回白板模块对象。
 */
+ (AVDWhiteboard *)getWhiteboard:(AVDRoom *)room;

/**
 *  创建白板
 *
 *  @param whiteboardInfo 白板信息
 *
 *  @return 返回错误代码
 */
- (AVDResult)createBoard:(AVDWhiteboardInfo *)whiteboardInfo;

/**
 *  共享白板
 *
 *  @param whiteboardId 白板id
 *
 *  @return 返回错误代码
 */
- (AVDResult)shareBoard:(AVDBoardId)whiteboardId;

/**
 *  关闭白板
 *
 *  @param whiteboardId 白板id
 *
 *  @return 返回错误代码
 */
- (AVDResult)closeBoard:(AVDBoardId)whiteboardId;

/**
 *  移除白板
 *
 *  @param whiteboardId 白板id
 *
 *  @return 返回错误代码
 */
- (AVDResult)removeBoard:(AVDBoardId)whiteboardId;


- (AVDResult)setAnnotationToolbarView:(UIView*)view;

/**
 *  视图与白板id绑定
 *
 *  @param view         视图
 *  @param whiteboardId 白板id
 *
 *  @return 返回错误代码
 */
- (AVDResult)attachView:(UIView*)view boardInfo:(AVDWhiteboardInfo *)boardInfo;

- (AVDResult)dettachView:(UIView*)view boardId:(AVDBoardId)boardId;

/**
 *  更新白板
 *
 *  @param whiteboardId   白板id
 *  @param whiteboardInfo 白板信息
 *
 *  @return 返回错误代码
 */
- (AVDResult)updateBoard:(AVDBoardId)whiteboardId whiteboard:(AVDWhiteboardInfo *)whiteboardInfo;

/**
 *  设置白板背景图片
 *
 *  @param whiteboardId 白板id
 *  @param imageName    图片名称
 *
 *  @return 返回错误代码
 */
- (AVDResult)setBackgroundImage:(AVDBoardId)whiteboardId imageName:(NSString *)imageName;

/**
 *  设置白板背景颜色
 *
 *  @param whiteboardId 白板id
 *  @param alpha        背景色透明度 0.0-1.0
 *  @param red          red 0-255
 *  @param green        green 0-255
 *  @param blue         blue 0-255
 *
 *  @return 返回错误代码
 */
- (AVDResult)setBackgroundColor:(AVDBoardId)whiteboardId alpha:(CGFloat)alpha red:(NSInteger)red green:(NSInteger)green blue:(NSInteger)blue;

/**
 *  设置白板的宽度
 *
 *  @param whiteboardId 白板id
 *  @param width        白板宽度
 *
 *  @return 返回错误代码
 */
- (AVDResult)setWidth:(AVDBoardId)whiteboardId width:(NSInteger)width;

/**
 *  设置白板的高度
 *
 *  @param whiteboardId 白板id
 *  @param height       白板高度
 *
 *  @return 返回错误代码
 */
- (AVDResult)setHeight:(AVDBoardId)whiteboardId height:(NSInteger)height;

@end
