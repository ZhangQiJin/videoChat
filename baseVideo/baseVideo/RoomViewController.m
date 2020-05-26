//
//  RoomViewController.m
//  baseVideo
//
//  Created by 盛锋 on 2019/5/23.
//  Copyright © 2019年 Elliot. All rights reserved.
//

#import "RoomViewController.h"
#import "Masonry/Masonry.h"
#import "VideoViewRender.h"
#import "N2MSetting.h"
//#import "ScreenCapturer_ios.h"

#warning all Delegate please Jump to Definition Demo只做了2人视频展示

@interface RoomViewController ()<AVDRoomDelegate,AVDVideoDelegate,AVDUserManagerDelegate,UITabBarDelegate,AVDAudioDelegate,AVDWhiteboardDelegate>

@property (weak, nonatomic) IBOutlet UIView *navView;///<导航栏
@property (weak, nonatomic) IBOutlet UITabBar *bottomTabBar;///<底部tabbar
@property (weak, nonatomic) IBOutlet UILabel *roomId;///<房间id
@property (weak, nonatomic) AVDVideo *mvideo;///<视频模块
@property (weak, nonatomic) AVDAudio *maudio;///<音频模块
@property (weak, nonatomic) AVDUserManager *mmanager;///<用户管理模块
@property (strong, nonatomic) VideoViewRender *bigRender;///<大视频
@property (strong, nonatomic) VideoViewRender *smallRender;///<小视频
@property (weak, nonatomic) AVDScreen *mscreen;///<视频模块
@property (weak, nonatomic) AVDWhiteboard *mwhiteboard;///<白板模块
@property (strong, nonatomic) AVDCanvasView *boradView;///<白板view
@property (strong, nonatomic) AVDWhiteboardInfo *boradInfo;///<白板view
@property (assign, nonatomic) BOOL isSwitch;///<是否切换

@end

@implementation RoomViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self configRoom];
    [self setupUI];
    [self subPublishedCamers];
}

//布局
- (void)setupUI{
    //更新房间号
    self.roomId.text = [NSString stringWithFormat:@"房间号：%@",[self.room getRoomId]];
    self.bottomTabBar.delegate = self;
    UIView *superView = self.view;
    //add bigRender
    self.bigRender = [[VideoViewRender alloc] init];
    //self.bigRender.backgroundColor = [UIColor greenColor];
    [self.view addSubview:self.bigRender];
   
    //add smallRender
    self.smallRender = [[VideoViewRender alloc] init];
    //self.smallRender.backgroundColor = [UIColor blueColor];
    [self.view addSubview:self.smallRender];
    [_smallRender addGestureRecognizer:[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(switchRender)]];
    
    self.boradView = [[AVDCanvasView alloc]init];
    self.boradView.hidden = YES;
    [self.view addSubview:self.boradView];
    
    //layout bigRender
    [_bigRender mas_makeConstraints:^(MASConstraintMaker *make) {
        make.right.left.equalTo(superView);
        make.top.equalTo(self.navView.mas_bottom);
        make.bottom.equalTo(self.bottomTabBar.mas_top);
    }];
    //layout smallRender
    [_smallRender mas_makeConstraints:^(MASConstraintMaker *make) {
        make.right.equalTo(superView.mas_right).offset(-8);
        make.bottom.equalTo(self.bottomTabBar.mas_top).offset(-8);
        make.size.mas_equalTo(CGSizeMake(100, 160));
    }];
    
    [_boradView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.right.left.equalTo(superView);
        make.top.equalTo(self.navView.mas_bottom);
        make.bottom.equalTo(self.bottomTabBar.mas_top);
    }];
}

- (void)switchRender{
    UIView *superView = self.view;
    [_smallRender mas_remakeConstraints:^(MASConstraintMaker *make) {
        if (!self->_isSwitch) {
            make.right.left.equalTo(superView);
            make.top.equalTo(self.navView.mas_bottom);
            make.bottom.equalTo(self.bottomTabBar.mas_top);
        }else{
            make.right.equalTo(superView.mas_right).offset(-8);
            make.bottom.equalTo(self.bottomTabBar.mas_top).offset(-8);
            make.size.mas_equalTo(CGSizeMake(100, 160));
        }
    }];
    [_bigRender mas_remakeConstraints:^(MASConstraintMaker *make) {
        if (!self->_isSwitch) {
            make.right.equalTo(superView.mas_right).offset(-8);
            make.bottom.equalTo(self.bottomTabBar.mas_top).offset(-8);
            make.size.mas_equalTo(CGSizeMake(100, 160));
        }else{
            make.right.left.equalTo(superView);
            make.top.equalTo(self.navView.mas_bottom);
            make.bottom.equalTo(self.bottomTabBar.mas_top);
        }
    }];
    [self.view updateConstraintsIfNeeded];
    [self.view layoutIfNeeded];
    [self.view bringSubviewToFront:_isSwitch?_smallRender:_bigRender];
    _isSwitch = !_isSwitch;
}

//获取对于音视频模块 本demo只做简单音视频
- (void)configRoom{
    self.mvideo = [AVDVideo getVideo:self.room];//获取视频模块
    self.mvideo.delegate = self;//设置视频模块代理
    self.maudio = [AVDAudio getAudio:self.room];//获取音频模块
    self.maudio.delegate = self;//设置音频模块代理
    self.mmanager = [AVDUserManager getUserManager:self.room];//s获取用户管理模块
    self.mmanager.delegate = self;//设置用户管理回调
    self.room.delegate = self;//s设置房间代理
//    self.mscreen = [AVDScreen getScreen:self.room];
//    self.mscreen.delegate = self;
    self.mwhiteboard = [AVDWhiteboard getWhiteboard:self.room];
    self.mwhiteboard.delegate = self;
    if (self.mwhiteboard.sharedBoards.count) {
        self.boradInfo = self.mwhiteboard.sharedBoards.lastObject;
    }
    //默认发布音视频
    [self.mvideo publishLocalCamera];
    [self.maudio openMicrophone];
//    CGRect rect = [UIScreen mainScreen].bounds;
//    AVDResult ret = [self.mscreen publishScreen:0 catY:300 catW:rect.size.width catH:300];
//    NSLog(@"发布屏幕共享 ret = %d",ret);
}

//订阅已经发布的一个摄像头
- (void)subPublishedCamers{
    if (self.mvideo.publishedCameras.count>0) {
        __weak typeof(self) weakSelf = self;
        //获取已经发布的视频流列表
        [self.mvideo.publishedCameras enumerateObjectsUsingBlock:^(AVDCamera *camer, NSUInteger idx, BOOL * _Nonnull stop) {
            __strong typeof(weakSelf) strongSelf = weakSelf;
            if (![strongSelf.mvideo isSelfDevice:camer.id]) {//2人demo 排除自己在订阅一个其他的视频
                [strongSelf.mvideo subscribe:camer.id];//订阅
                [strongSelf.mvideo attachRenderWithDeviceId:camer.id render:strongSelf.bigRender];//渲染
                return ;
            }
        }];
    }
}

#pragma mark ROOM Delegate
//指示用户离开房间 reason == 807：服务器端报807错误，说明UDP不通或UDP连接超时   reason == 804：同一个userid加会， 把前一个人踢下线 reason == 808：调用rest api接口把人踢下线reason == 809：无授权 15分钟以后强制踢人 其它：你被踢出会议室
- (void)onLeaveIndication:(AVDResult)reason fromUser:(AVDUserId)fromId{
    NSLog(@"RoomViewController, onLeaveIndication, reason:%lu", (unsigned long)reason);
}

//网络状态回调
- (void)onConnectionStatus:(enum AVDConnectionStatus)status{
    if (connectFailed == status) {//链接失败 离开房间
        [self closeRoom:nil];
    }else if (connecting == status){//to do 正在重连 hud提示或者其他操作。。按自己产品设计来
        
    }else if (connected == status){//c重连成功
        
    }
}

#pragma mark --video delegate 发布视频时回调这些方法
//参会者摄像头状态回调
- (void) onCameraStatusNotify:(enum AVDDeviceStatus)status deviceId:(AVDDeviceId)fromId {
    NSLog(@"VideosView, onCameraStatusNotify, status:%u, from:%@", status, fromId);
    if ([self.mvideo isSelfDevice:fromId] || ds_published != status) {
        return ;
    }

}

//房间中所有参会者发布视频都会走这个回调
- (void) onPublishCameraNotify:(AVDCamera*)item {
    NSLog(@"VideosView, onPublishCameraNotify, camera:%@", item.id);
    if ([self.mvideo isSelfDevice:item.id]) {
        [self.mvideo attachRenderWithDeviceId:item.id render:self.smallRender];
    }else {
      AVDResult ret = [self.mvideo subscribe:item.id];
        NSLog(@"subResult = %d",ret);
    }

}

//房间中所有参会者取消发布视频都会走这个回调
- (void) onUnpublishCameraNotify:(AVDCamera*)item {
    NSLog(@"VideosView, onUnpublishCameraNotify, camera:%@", item.id);
    if ([self.mvideo isSelfDevice:item.id]) {
        return ;
    }
    [self.mvideo unsubscribe:item.id];
    [self.mvideo detachRenderWithRender:self.bigRender];
    [self.mvideo detachRenderWithDeviceId:item.id];
 
}

#pragma mark --screen video delegate common
//摄像头订阅回调
- (void) onSubscribeResult:(AVDResult)result deviceId:(AVDDeviceId)fromId {
    NSLog(@"VideosView, onSubscribeResult, result:%lu fromId:%@", (unsigned long)result, fromId);
    if (AVD_Success != result) {
        return ;
    }
    [self.mvideo attachRenderWithDeviceId:fromId render:self.bigRender];

}
//取消订阅回调
- (void) onUnsubscribeResult:(AVDResult)result deviceId:(AVDDeviceId)fromId {
    NSLog(@"VideosView, onUnsubscribeResult, result:%lu fromId:%@", (unsigned long)result, fromId);
}

//自己发布本地视频回调
- (void) onPublishLocalResult:(AVDResult)result deviceId:(AVDDeviceId)fromId {
    NSLog(@"VideosView, onPublishLocalResult, result:%lu fromId:%@", (unsigned long)result, fromId);
}

//自己取消发布本地视频回调
- (void) onUnpublishLocalResult:(AVDResult)result deviceId:(AVDDeviceId)fromId {
    NSLog(@"VideosView, onUnpublishLocalResult, result:%lu fromId:%@", (unsigned long)result, fromId);
}

#pragma mark - 用户加会 离会回调
- (void)onUserJoinNotify:(AVDUser *)user{
    NSLog(@"onUserJoinNotify user = %@", user);
}

- (void)onUserLeaveNotify:(AVDUser *)user{
     NSLog(@"onUserLeaveNotify user = %@", user);
}


#pragma mark UI Action
//
- (IBAction)closeRoom:(UIButton *)sender {
    [self.room leave:AVD_Success];
    self.room.delegate = nil;
    [self dismissViewControllerAnimated:YES completion:^{
        [self.room destory];
    }];
    
}

-(void)tabBar:(UITabBar *)tabBar didSelectItem:(UITabBarItem *)item{
    if ([item.title isEqualToString:@"摄像头"]) {
        BOOL isOpen = NO;
        AVDResult ret = AVD_Success;
        if ([self.mvideo ispublishLocalCamera]) {
            [self.mvideo unpublishLocalCamera];
            isOpen = NO;
        } else {
            [self.mvideo publishLocalCamera:front];
            isOpen = YES;
        }
        item.selectedImage = [[UIImage imageNamed:[NSString stringWithFormat:@"icon_video_%@",isOpen?@"show":@"hide"]] imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal];
    }else if ([item.title isEqualToString:@"麦克风"]){
        BOOL isOpen = NO;
        AVDResult ret = AVD_Success;
        if ([self.maudio isOpenMicrophone]) {
            [self.maudio closeMicrophone];
            isOpen = NO;
        } else {
            [self.maudio openMicrophone];
            isOpen = YES;
        }
         item.selectedImage = [[UIImage imageNamed:[NSString stringWithFormat:@"icon_audio_%@",isOpen?@"open":@"close"]] imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal];
    }else if ([item.title isEqualToString:@"切换摄像头"]){//demo没有记录当前状态
        [self.mvideo switchToLocalCamera];
    }else if ([item.title isEqualToString:@"白板"]){//
        [self sharedBoardInfo:self.boradView];
    }else if ([item.title isEqualToString:@"停止白板"]){//
        if ([self isSelfShareBoard]) {//是自己共享的才调用close
            [self.mwhiteboard closeBoard:self.boradInfo.boardId];
        }
        [self.mwhiteboard dettachView:self.boradView  boardId:self.boradInfo.boardId];
        //下面接口支持自定义工具条
//        [self.boradView setBrushType:BrushPolyline];
//        [self.boradView setBrushColor:[UIColor greenColor]];
//        [self.boradView setBrushWidth:9];
//        [self.boradView setValue:@(YES) forKey:@"canDraw"];
    }
        
}
- (IBAction)startRecord:(UIButton *)sender {

}
- (IBAction)stopRecord:(UIButton *)sender {

}

#pragma mark - 白板

//获取自己当前是否已经共享白板
- (AVDWhiteboardInfo *)sharedBoardInfo:(UIView *)view{
    //NSLog(@"当前共享的白板列表 %@",self.mboard.publishedBoards);
    __block BOOL isShare = NO;
    __block AVDWhiteboardInfo *boardInfo = nil;
    AVDResult creatResult;
    [self.mwhiteboard.publishedBoards enumerateObjectsUsingBlock:^(AVDWhiteboardInfo *obj, NSUInteger idx, BOOL * _Nonnull stop) {
        if ([obj.userId isEqualToString:self.mmanager.selfUser.userId]) {
            isShare = YES;
            boardInfo = obj;
        }
    }];
    if (!isShare) {
        boardInfo = [[AVDWhiteboardInfo alloc] init];
        boardInfo.boardId = [[NSUUID UUID] UUIDString];
        boardInfo.userId = self.mmanager.selfUser.userId;
        boardInfo.width = view.frame.size.width;
        boardInfo.height = view.frame.size.height;
        boardInfo.color = [self colorWithHexString:@"#ffffff" alpha:1];
        creatResult =  [self.mwhiteboard createBoard:boardInfo];
    }
    AVDResult result = [self.mwhiteboard shareBoard:boardInfo.boardId];
    [self.mwhiteboard attachView:view boardInfo:boardInfo];
    view.hidden = NO;
    return boardInfo;
}

- (UIColor *)colorWithHexString:(NSString *)color alpha:(CGFloat)alpha{
    //删除字符串中的空格
    NSString *cString = [[color stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]] uppercaseString];
    // String should be 6 or 8 characters
    if ([cString length] < 6) {
        return [UIColor clearColor];
    }
    // strip 0X if it appears
    //如果是0x开头的，那么截取字符串，字符串从索引为2的位置开始，一直到末尾
    if ([cString hasPrefix:@"0X"]) {
        cString = [cString substringFromIndex:2];
    }
    //如果是#开头的，那么截取字符串，字符串从索引为1的位置开始，一直到末尾
    if ([cString hasPrefix:@"#"]) {
        cString = [cString substringFromIndex:1];
    }
    if ([cString length] != 6) {
        return [UIColor clearColor];
    }
    // Separate into r, g, b substrings
    NSRange range;
    range.location = 0;
    range.length = 2;
    //r
    NSString *rString = [cString substringWithRange:range];
    //g
    range.location = 2;
    NSString *gString = [cString substringWithRange:range];
    //b
    range.location = 4;
    NSString *bString = [cString substringWithRange:range];
    // Scan values
    unsigned int r, g, b;
    [[NSScanner scannerWithString:rString] scanHexInt:&r];
    [[NSScanner scannerWithString:gString] scanHexInt:&g];
    [[NSScanner scannerWithString:bString] scanHexInt:&b];
    return [UIColor colorWithRed:((float)r / 255.0f) green:((float)g / 255.0f) blue:((float)b / 255.0f) alpha:alpha];
}

- (BOOL)isSelfShareBoard{
    __block BOOL isSelf = NO;
    [self.mwhiteboard.sharedBoards enumerateObjectsUsingBlock:^(AVDWhiteboardInfo *obj, NSUInteger idx, BOOL * _Nonnull stop) {
        if ([obj.userId isEqualToString:self.mmanager.selfUser.userId]) {
            isSelf = YES;
        }
    }];
    return isSelf;
}

- (void)onCreateBoardNotify:(AVDWhiteboardInfo *)whiteboardInfo{
    self.boradInfo = whiteboardInfo;
    NSLog(@"board 1%@",self.boradInfo);
}

- (void)onRemoveBoardNotify:(AVDBoardId)whiteboardId{
    NSLog(@"board 2");
    self.boradView.hidden = YES;
    if ([self.boradInfo.boardId isEqualToString:whiteboardId]) {
        [self.mwhiteboard dettachView:self.boradView boardId:whiteboardId];
    }
}

- (void)onShareBoardNotify:(AVDWhiteboardInfo *)whiteboardInfo{
    NSLog(@"board 4 ");
    self.boradView.hidden = NO;
    [self.mwhiteboard attachView:self.boradView boardInfo:self.boradInfo];
}

- (void)onCloseBoardNotify:(AVDBoardId)whiteboardId{
    NSLog(@"board 5");
    self.boradView.hidden = YES;
    if ([self.boradInfo.boardId isEqualToString:whiteboardId]) {
        [self.mwhiteboard dettachView:self.boradView boardId:whiteboardId];
    }
}

@end
