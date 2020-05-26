//
//  N2MSetting.m
//  nice2meet
//
//  Created by Netease on 15/8/14.
//  Copyright (c) 2015年 Netease. All rights reserved.
//

#import "N2MSetting.h"
#import <avd_sdk/avd_sdk.h>

@implementation N2MSetting

+ (NSString*) getServerURL {
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    NSString* serverUrl = [userDefaults stringForKey:Key_serverUrl];
    if (Nil == serverUrl) {
//        serverUrl = @"https://dev.3tee.cn:441";
        serverUrl = @"http://avd.nice2meet.cn:9609";
//        serverUrl = @"http://jh.3tee.cn";
    }
    return serverUrl;
}
+ (NSString*) getAppKey {
//    return @"SDKdemo_access";
    return @"demo_access";

}
+ (NSString*) getSecretKey {
//    return @"SDKdemo_secret";
    return @"demo_secret";

}


+ (enum AVDScalingType) getVideoShowStype {
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    NSInteger nValue = [userDefaults integerForKey:Key_videoShow];
    return (0 == nValue) ? Scale_Aspect_Full : Scale_Aspect_Fit;
}
+ (BOOL) isAutoVideoOpen {
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    return [userDefaults boolForKey:Key_autoVideoOpen];
}
+ (BOOL) isAutoAudioOpen {
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    return [userDefaults boolForKey:Key_autoAudioOpen];
}
+ (BOOL) isLivecastMode {
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    return [userDefaults boolForKey:Key_livecastMode];
}
+ (NSString*) getVideoCodecOption {
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    NSInteger nValue = [userDefaults integerForKey:Key_videoCodec];
    return (0 == nValue) ? @"vp8" : @"h264";
}
+ (NSString*) getVideoResolutionOption {
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    NSInteger nValue = [userDefaults integerForKey:Key_videoResolution];
    NSString *cap = @"{\"width\":355,\"height\":288,\"maxFPS\":30}";
    if (2 == nValue) {
        cap = @"{\"width\":1280,\"height\":720,\"maxFPS\":15}";
    }
    if (1 == nValue) {
        cap = @"{\"width\":640,\"height\":480,\"maxFPS\":20}";
    }
    return cap;
}
+ (NSString*) getDataChannelNetOption {
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    NSInteger nValue = [userDefaults integerForKey:Key_datachannelNet];
    return (0 == nValue) ? @"false" : @"true";
}


+ (NSString*) getUserId {
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    NSString* sValue = [userDefaults stringForKey:Key_userId];
    if (Nil == sValue) {
        CFUUIDRef uuid = CFUUIDCreate(NULL);
        CFStringRef uuidStr = CFUUIDCreateString(NULL, uuid);
        sValue = [NSString stringWithFormat:@"%@", uuidStr];
        [userDefaults setObject:sValue forKey:Key_userId];
    }
    return sValue;
}
+ (NSString*) getUserName {
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    NSString* sValue = [userDefaults stringForKey:Key_userName];
    if (Nil == sValue) {
        UIDevice* dev = [UIDevice currentDevice];
        sValue = [dev.name stringByAppendingString:@"["];
        sValue = [sValue stringByAppendingString:dev.systemVersion];
        sValue = [sValue stringByAppendingString:@"]"];
    }
    return sValue;
}
+ (void) setUserName:(NSString*)userName {
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    [userDefaults setObject:userName forKey:Key_userName];
}
+ (NSString*) getCurrentRoomId {
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    NSString* curId = [userDefaults stringForKey:Key_roomId];
    if (nil == curId || [curId isEqualToString:@""]) {
        curId = @"13678060953";
    }
    return curId;
}
+ (void) setCurrentRoomId:(NSString*)roomId {
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    [userDefaults setObject:roomId forKey:Key_roomId];
}

+ (void) showAlertViewWithTitle:(NSString*)title message:(NSString*)message delegate:(id /*<UIAlertViewDelegate>*/)delegate cancelButtonTitle:(NSString*)btnTitle {
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:title message:message delegate:delegate cancelButtonTitle:btnTitle otherButtonTitles:nil, nil];
    [alert show];
}

@end
