//
//  N2MSetting.h
//  nice2meet
//
//  Created by Netease on 15/8/14.
//  Copyright (c) 2015年 Netease. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <avd_sdk/avd_sdk.h>

@interface N2MSetting : NSObject

#define NSNotificationGestureRecognizerSelect   @"NSNotificationGestureRecognizerSelect"
#define NSNotificationUserCellRemoteCommand     @"NSNotificationUserCellRemoteCommand"

///
#define Key_serverUrl       @"Key_serverUrl"
#define Key_uiStyle         @"Key_uiStyle"
#define Key_videoCodec      @"Key_videoCodec"
#define Key_videoShow       @"Key_videoShow"
#define Key_videoResolution @"Key_videoResolution"
#define Key_datachannelNet  @"Key_datachannelNet"
#define Key_autoAudioOpen   @"Key_autoAudioOpen"
#define Key_autoVideoOpen   @"Key_autoVideoOpen"
#define Key_livecastMode    @"Key_livecastMode"

#define Key_userId          @"Key_userId"
#define Key_userName        @"Key_userName"
#define Key_roomId          @"Key_roomId"

+ (NSString*) getServerURL;
+ (NSString*) getAppKey;
+ (NSString*) getSecretKey;

+ (NSString*) getUIStype;
+ (enum AVDScalingType) getVideoShowStype;
+ (BOOL) isAutoVideoOpen;
+ (BOOL) isAutoAudioOpen;
+ (BOOL) isLivecastMode;

+ (NSString*) getVideoCodecOption;
+ (NSString*) getVideoResolutionOption;
+ (NSString*) getDataChannelNetOption;

+ (NSString*) getUserId;
+ (NSString*) getUserName;
+ (void) setUserName:(NSString*)userName;
+ (NSString*) getCurrentRoomId;
+ (void) setCurrentRoomId:(NSString*)roomId;

+ (void) showAlertViewWithTitle:(NSString*)title message:(NSString*)message delegate:(id /*<UIAlertViewDelegate>*/)delegate cancelButtonTitle:(NSString*)btnTitle;


@end
