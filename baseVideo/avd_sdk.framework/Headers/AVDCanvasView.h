//
//  AVDCanvasView.h
//  avd_sdk
//
//  Created by 盛锋 on 2018/5/8.
//  Copyright © 2018年 t3ee. All rights reserved.
//  画布

#import <UIKit/UIKit.h>
#import "AVDWhiteboard.h"

//画笔形状
typedef NS_ENUM(NSInteger, BrushPattern)
{
    BrushMouse = 1 << 0,//鼠标
    BrushLine  = 1 << 1,//直线
    BrushRectangle = 1 << 2,//矩形
    BrushEllipse = 1 << 3,//椭圆
    BrushPolyline = 1 << 4,//曲线
    BrushPolygon = 1 << 5,//多边形
    BrushHlightPoint = 1 << 6,//激光笔
    BrushHlightTexttag = 1 << 7,//文字
    BrushEraserLine = 1 << 8,//橡皮擦
    BrushEraserRectangle = 1 << 9,//橡皮擦
    BrushRhomb = 1 << 10,//菱形
    BrushArrow = 1 << 11,//箭头
    BrushSuccess = 1 << 12,//✔️
    BrushFailure = 1 << 13,//❌
};

@interface AVDCanvasView : UIView

@property (nonatomic,assign,readonly)BOOL canDraw;

/**
 显示白板

 @param sView 白板view
 @param board 白板对象
 @param boardInfo 白板信息
 @param anno 注释信息
 */
- (void)attachView:(UIView *)sView whiteboar:(AVDWhiteboard *)board boardInfo:(AVDWhiteboardInfo *)boardInfo annotaion:(AVDAnnotaion *)anno;


/**
 移除sdk自带的toolView

 @param sView 传nil
 */
- (void)removeBoardTool:(UIView *)sView;


/**
 设置画笔类型
 @param brushType 画笔类型
 */
- (void)setBrushType:(BrushPattern)brushType;

/**
 设置画笔颜色

 @param brushColor brushColor
 */
- (void)setBrushColor:(UIColor *)brushColor;


/**
 设置画笔宽度

 @param brushWidth brushWidth
 */
- (void)setBrushWidth:(NSInteger)brushWidth;


/**
 设置是否是橡皮擦

 @param isEraser isEraser
 */
- (void)setIsEraser:(BOOL)isEraser;


/**
 设置是否是激光笔

 @param isNite isNite
 */
- (void)setIsNite:(BOOL)isNite;


/**
 撤销
 */
- (void)unDo;


/**
 清空
 */
- (void)clearBrush;


/**
 设置工具条展开状态
 */
- (void)setIsToolOpen:(BOOL)isToolOpen;



@end
