//
//  AVDWhiteboardInfo.h
//  avd_sdk
//
//  Created by 盛锋 on 2018/5/3.
//  Copyright © 2018年 t3ee. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AVDCommon.h"
#import <UIKit/UIKit.h>


@interface AVDWhiteboardInfo : NSObject

@property(nonatomic, strong) AVDBoardId boardId;          /**< 白板Id */
@property(nonatomic, strong) AVDUserId userId;            /**< 白板创建者id */
@property(nonatomic, strong) NSString* title;             /**< 白板标题 */
@property(nonatomic, strong) NSString* desc;              /**< 白板描述 */
@property(nonatomic, assign) NSUInteger width;            /**< 白板宽度 */
@property(nonatomic, assign) NSUInteger height;           /**< 白板高度 */
@property(nonatomic, assign) NSInteger windowId;          /**< 父窗口id */
@property(nonatomic, strong) UIColor *color;              /**< 白板背景色 */

@end
