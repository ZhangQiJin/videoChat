//
//  JoinViewController.m
//  baseVideo
//
//  Created by 盛锋 on 2019/5/23.
//  Copyright © 2019年 Elliot. All rights reserved.
//

#import "JoinViewController.h"
#import <avd_sdk/avd_sdk.h>
#import "N2MSetting.h"
#import "RoomViewController.h"

@interface JoinViewController ()<AVDEngineDelegate,AVDRoomJoinDelegate>
@property (weak, nonatomic) IBOutlet UITextField *roomId;///<房间id
@property (weak, nonatomic) IBOutlet UITextField *userName;///<用户名

@end

@implementation JoinViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    //初始化引擎
    [[AVDEngine instance] initWithServerUrl: [N2MSetting getServerURL] accessKey: [N2MSetting getAppKey] secretKey:[N2MSetting getSecretKey] delegate:self];
    [[AVDEngine instance] setLogParams:@"info debug" file:[self getLogFileName]];
    NSLog(@"引擎版本信息%@",[AVDEngine getVersion]);
    // Do any additional setup after loading the view from its nib.
}


- (NSString*)getLogFileName {
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setDateFormat:@"yyyy-MM-dd-HHmmss"];
    NSString *destDateString = [dateFormatter stringFromDate: [NSDate date] ];
    NSString *fileName = [NSString stringWithFormat:@"/%@.log", destDateString];
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *docDir = [paths objectAtIndex:0];
    docDir = [docDir stringByAppendingString:@"/logs"];
    fileName = [docDir stringByAppendingPathComponent:fileName];
    NSLog(@"getLogFileName fileName:%@", fileName);
    return fileName;
}

//初始化引擎回调并设置相关视频默认分辨率 视频编码格式（h264 vp8） 网络连接方式（tcp udp）
- (void)onInitResult:(AVDResult)result {
    if (AVD_Success == result) {//初始化成功并设置相关参数 具体定义参考AVDEngine.h
        [[UIApplication sharedApplication] setIdleTimerDisabled:YES];
        [[AVDEngine instance] setOption:video_codec_priority value:[N2MSetting getVideoCodecOption]];
        [[AVDEngine instance] setOption:camera_capability_default value:[N2MSetting getVideoResolutionOption]];
        [[AVDEngine instance] setOption:data_channel_tcp_priority value:[N2MSetting getDataChannelNetOption]];
        [[AVDEngine instance] setOption:eo_audio_agc_RecordGainMultipleValue value:@"3.0"];

        NSLog(@"AppDelegate, AVDEngine onInitResult init success");
    }else {
        [N2MSetting showAlertViewWithTitle:@"提醒" message:@"引擎初始化失败，请检查网络或者key" delegate:self cancelButtonTitle:@"知道了"];
        NSLog(@"AppDelegate, AVDEngine onInitResult init failed. result:%lu",(unsigned long)result);
    }
}

//加入房间按钮
- (IBAction)joinMeetingAction:(UIButton *)sender {
    //加入房间
    [self joinRoom];
}

//创建房间按钮
- (IBAction)creatRoom:(UIButton *)sender {
    if (!self.roomId.text.length) {
        [N2MSetting showAlertViewWithTitle:@"警告" message:@"创建房间时房间号不能为空" delegate:self cancelButtonTitle:@"知道了"];
    }
    AVDRoomInfo *roomInfo = [[AVDRoomInfo alloc]initWithRoomId:self.roomId.text roomName:self.roomId.text appRoomId:self.roomId.text ownerId:self.roomId.text  maxAttendee:5 maxAudio:5 maxVideo:5 roomMode:1 voiceActivated:YES];
    [[AVDEngine instance] scheduleRoom:roomInfo];
}

- (void)onScheduleRoomResult:(AVDResult)result roomId:(AVDRoomId)roomId{
    if (AVD_Success == result) {
        [N2MSetting showAlertViewWithTitle:@"创建成功" message:[NSString stringWithFormat:@"您创建的房间号为：%@",roomId] delegate:self cancelButtonTitle:@"知道了"];
        self.roomId.text = roomId;
    }else {
        [N2MSetting showAlertViewWithTitle:@"失败" message:@"创建房间失败" delegate:self cancelButtonTitle:@"知道了"];
    }
}



//反初始化引擎回调
- (void)onUninitResult:(AVDResult)reason {
    NSLog(@"AppDelegate, AVDEngine onUninitResult reason:%lu",(unsigned long)reason);
}

//加入房间操作
- (void)joinRoom{
    NSString* roomId = self.roomId.text;
    if ([roomId length]>0&& [self.userName.text length] >0) {
        AVDRoom* room = [AVDRoom obtain:roomId];
        AVDUser* user = [[AVDUser alloc] initWithUserId:[N2MSetting getUserId] userName:self.userName.text userData:nil];
        [room joinWithUser:user password:nil delegate:self];
    }else if ([self.roomId.text length]<=0){
        [N2MSetting showAlertViewWithTitle:@"提醒" message:@"房间号不能为空" delegate:self cancelButtonTitle:@"知道了"];
    }else{
        [N2MSetting showAlertViewWithTitle:@"提醒" message:@"用户名不能为空" delegate:self cancelButtonTitle:@"知道了"];
    }
}

//加入房间回调
- (void)onJoinResult:(AVDResult)result{
    NSLog(@"ViewController onJoinResult, result:%lu", (unsigned long)result);
    if (AVD_Success == result) {
        [N2MSetting setCurrentRoomId:self.roomId.text];
        [N2MSetting setUserName:self.userName.text];
        RoomViewController * roomVC = [[RoomViewController alloc] init];
        roomVC.room = [AVDRoom obtain:self.roomId.text];
        [self presentViewController:roomVC animated:YES completion:nil];
    }else{
        [N2MSetting showAlertViewWithTitle:@"警告" message:@"进入房间失败,请检查账号是否正确" delegate:self cancelButtonTitle:@"知道了"];
    }
}

//结束编辑 收起键盘
- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event{
    [self.view endEditing:YES];
}

@end
