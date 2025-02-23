# QNLiveKit_iOS

## 互动直播低代码iOS

qlive-sdk是七牛云推出的一款互动直播低代码解决方案sdk。只需几行代码快速接入互动连麦pk直播。

## SDK下载与Demo 使用    

### 资源下载

[DownloadResource](https://github.com/pili-engineering/QNLiveKit_iOS/tree/main/DownloadResource/)

### 资源目录说明

* frameworks：相关framework
* livekitResource：低代码库使用的资源文件
* BeautyResource：美颜资源文件
* QNLiveKitDemo：demo 工程

### Demo 使用说明

* 进入QNLiveKitDemo
* 执行 pod install
* 打开 QNLiveKitDemo.xcworkspace
* 选择真机运行。



## SDK 接入

### 配置依赖 

SDK 依赖一下资源库，具体可以参考 QNLiveKitDemo/Podfile


      pod 'QNRTCKit-iOS','5.1.1'
      pod 'Bugly','2.5.91'
      pod 'PLPlayerKit', '3.4.7'
      pod 'Masonry', '1.1.0'
      pod 'MJExtension','3.4.1'
      pod 'YYCategories','1.0.4'
      pod 'YYModel','1.0.4'
      pod 'YYWebImage','1.0.4'
      pod 'SDWebImage',' 5.12.2'
      pod 'AFNetworking','4.0.1'
      pod 'IQKeyboardManager','6.5.9'
      pod 'MBProgressHUD','1.2.0'
      pod 'MJRefresh', '3.5.0'
      pod 'SocketRocket','0.6.0'




### 接入framework

* 引入系统库：在Targets->Build Phases->Link Library With Libraries中添加如下系统库：
  * AssetsLibrary.framework
  * CoreService.framework
  * MapKit.framework

* 将framework 中的库加入工程。
* 在Targets->Build Settings->Framework Search Paths中添加 framework 路径
* 在Targets->Build Phoses 中，增加一个Copy Phase。添加 QNIMSDK.framework，并设置 Code Sign On



### 引入资源文件

* 将 livekitResource 中的资源文件，拖入项目的 Assets 中。
* 如果需要美颜，将 BeautyResource 中的资源，加入到项目中。



### 快速接入


​        
​        //初始化SDK  errorBack错误回调，可在此处更新过期的token
​        [QLive initWithToken:token serverURL:@"liveKit域名" errorBack:nil];
​        //绑定自己服务器的头像和昵称 extension为扩展字段，可以自定义同步的内容
​        [QLive setUser:user.avatar nick:user.nickname extension:nil];


​                
​         //Tips:如果需要使用内置美颜，在初始化后调用
​         [QLive setBeauty:YES]; 
​            
​        //直播列表页：
​        QLiveListController *listVc = [QLiveListController new];
​        [self.navigationController pushViewController:listVc animated:YES];


​        
​        //观众观看页面：
​        QNAudienceController *vc = [QNAudienceController new];
​        vc.roomInfo = roomInfo;
​        vc.modalPresentationStyle = UIModalPresentationFullScreen;
​        [self presentViewController:vc animated:YES completion:nil];


​    
### 详细接入

#### 初始化类


​    
​    /// 房间业务管理
​    @interface QLive : NSObject
​    
​    // 初始化
​    + (void)initWithToken:(NSString *)token serverURL:(NSString *)serverURL errorBack:(nullable void (^)(NSError *error))errorBack;
​    //绑定用户信息
​    + (void)setUser:(NSString *)avatar nick:(NSString *)nick extension:(nullable NSDictionary *)extension;
​    //创建主播端
​    + (QNLivePushClient *)createPusherClient;
​    //创建观众端
​    + (QNLivePullClient *)createPlayerClient;
​    //获得直播场景
​    + (QRooms *)getRooms;
​    //获取自己的信息
​    + (void)getSelfUser:(void (^)(QNLiveUser *user))callBack;
​    
    @end


​    

#### 主播操作


    @interface QNLivePushClient : QNLiveRoomClient
    
    //直播操作
    
    /// 开始直播
    - (void)startLive:(NSString *)roomID callBack:(nullable void (^)(QNLiveRoomInfo *_Nullable roomInfo))callBack;
    /// 停止直播
    - (void)closeRoom;
    
    //推流操作
    
    /// 启动视频采集
    - (void)enableCamera:(nullable QNCameraParams *)cameraParams renderView:(nullable QRenderView *)renderView;
    /// 切换摄像头
    - (void)switchCamera;
    /// 是否禁止本地摄像头推流
    - (void)muteCamera:(BOOL)muted;
    /// 是否禁止本地麦克风推流
    - (void)muteMicrophone:(BOOL)muted;
    /// 设置本地音频帧回调
    - (void)setAudioFrameListener:(id<QNLocalAudioTrackDelegate>)listener;
    /// 设置本地视频帧回调
    - (void)setVideoFrameListener:(id<QNLocalVideoTrackDelegate>)listener;


​    
​    //获取混流器
​    - (QMixStreamManager *)getMixStreamManager;

#### 观众操作


    @interface QNLivePullClient : QNLiveRoomClient
    
    /// 观众加入直播
    - (void)joinRoom:(NSString *)roomID callBack:(nullable void (^)(QNLiveRoomInfo *_Nullable roomInfo))callBack;
    /// 离开直播
    - (void)leaveRoom;

#### 房间操作


​    
​    @interface QRooms : NSObject
​    
​    /// 创建房间
​    /// @param param 创建房间参数
​    /// @param callBack 回调房间信息
​    - (void)createRoom:(QNCreateRoomParam *)param callBack:(nullable void (^)(QNLiveRoomInfo *roomInfo))callBack;
​    
    /// 删除房间
    /// @param callBack 回调
    - (void)deleteRoom:(NSString *)liveId callBack:(void (^)(void))callBack;
    
    /// 房间列表
    /// @param pageNumber 页数
    /// @param pageSize 页面大小
    /// @param callBack 回调房间列表
    - (void)listRoom:(NSInteger)pageNumber pageSize:(NSInteger)pageSize callBack:(nullable void (^)(NSArray<QNLiveRoomInfo *> * list))callBack;
    
    /// 查询房间信息
    /// @param callBack 回调房间信息
    - (void)getRoomInfo:(NSString *)roomID callBack:(nullable void (^)(QNLiveRoomInfo *roomInfo))callBack;
    
    @end


​    
#### 房间状态


    /// 房间生命周期
    @protocol QNRoomLifeCycleListener <NSObject>
    
    @optional
    /// 进入房间回调
    /// @param user 用户
    - (void)onRoomEnter:(QNLiveUser *)user;
    
    /// 加入房间回调
    /// @param roomInfo 房间信息
    - (void)onRoomJoined:(QNLiveRoomInfo *)roomInfo;
    
    //直播间某个属性变化
    - (BOOL)onRoomExtensions:(NSString *)extension;
    
    /// 离开回调
    - (void)onRoomLeave:(QNLiveUser *)user;
    
    /// 销毁回调
    - (void)onRoomClose;
    
    @end
    
    @interface QNLiveRoomClient : NSObject
    
    @property (nonatomic, weak) id <QNRoomLifeCycleListener> roomLifeCycleListener;
    
    /// 获取房间所有用户
    /// @param roomId 房间id
    /// @param pageNumber 页数
    /// @param pageSize 页面大小
    /// @param callBack 回调用户列表
    - (void)getUserList:(NSString *)roomId pageNumber:(NSInteger)pageNumber pageSize:(NSInteger)pageSize callBack:(void (^)(NSArray<QNLiveUser *> *   _Nonnull))callBack;
    
    //房间心跳
    - (void)roomHeartBeart:(NSString *)roomId;
    
    //更新直播扩展信息
    - (void)updateRoom:(NSString *)roomId extension:(NSString *)extension callBack:(void (^)(void))callBack;
    
    //某个房间在线用户
    - (void)getOnlineUser:(NSString *)roomId callBack:(void (^)(NSArray <QNLiveUser *> *list))callBack;
    
    //使用用户ID搜索房间用户
    - (void)searchUserByUserId:(NSString *)uid callBack:(void (^)(QNLiveUser *user))callBack;
    
    //使用用户im uid 搜索用户
    - (void)searchUserByIMUid:(NSString *)imUid callBack:(void (^)(QNLiveUser *user))callBack;


​    

#### 连麦服务


    //连麦服务
    @interface QNLinkMicService : QNLiveService
    
    @property (nonatomic, weak)id<MicLinkerListener> micLinkerListener;
    
    //获取当前房间所有连麦用户
    - (void)getAllLinker:(void (^)(NSArray <QNMicLinker *> *list))callBack;
    
    //上麦
    - (void)onMic:(BOOL)mic camera:(BOOL)camera extends:(nullable NSDictionary *)extends;
    
    //下麦
    - (void)downMic;
    
    //踢人
    - (void)kickOutUser:(NSString *)uid msg:(nullable NSString *)msg callBack:(nullable void (^)(QNMicLinker * _Nullable))callBack ;
    
    //开关麦 type:mic/camera  flag:on/off
    - (void)updateMicStatusType:(NSString *)type flag:(BOOL)flag;
    
    //申请连麦
    - (void)ApplyLink:(QNLiveUser *)receiveUser;
    
    //接受连麦
    - (void)AcceptLink:(QInvitationModel *)invitationModel;
    
    //拒绝连麦
    - (void)RejectLink:(QInvitationModel *)invitationModel;
    @end


​    
#### 连麦回调

        /// 有人上麦
    - (void)onUserJoinLink:(QNMicLinker *)micLinker;
    
    /// 有人下麦
    - (void)onUserLeave:(QNMicLinker *)micLinker;
    
    /// 有人麦克风变化
    - (void)onUserMicrophoneStatusChange:(NSString *)uid mute:(BOOL)mute;
    
    /// 有人摄像头状态变化
    - (void)onUserCameraStatusChange:(NSString *)uid mute:(BOOL)mute;
    
    /// 有人被踢
    - (void)onUserBeKick:(LinkOptionModel *)micLinker;
    
    //收到连麦邀请
    - (void)onReceiveLinkInvitation:(QInvitationModel *)model;
    
    //连麦邀请被接受
    - (void)onReceiveLinkInvitationAccept:(QInvitationModel *)model;
    
    //连麦邀请被拒绝
    - (void)onReceiveLinkInvitationReject:(QInvitationModel *)model;


​    
#### PK服务


    @interface QNPKService : QNLiveService
    
    @property (nonatomic, weak)id<PKServiceListener> delegate;
    
    //申请pk
    - (void)applyPK:(NSString *)receiveRoomId receiveUser:(QNLiveUser *)receiveUser;
    
    //接受PK申请
    - (void)AcceptPK:(QInvitationModel *)invitationModel;
    
    //拒绝PK申请
    - (void)sendPKReject:(QInvitationModel *)invitationModel;
    
    //结束pk
    - (void)stopPK:(nullable void (^)(void))callBack;
    @end

#### pk回调

    //收到PK邀请
    - (void)onReceivePKInvitation:(QInvitationModel *)model;
    //PK邀请被接受
    - (void)onReceivePKInvitationAccept:(QNPKSession *)model;
    //PK邀请被拒绝
    - (void)onReceivePKInvitationReject:(QInvitationModel *)model;
    //PK开始
    - (void)onReceiveStartPKSession:(QNPKSession *)pkSession;
    //pk结束
    - (void)onReceiveStopPKSession:(QNPKSession *)pkSession;    

#### 聊天/信令发送


​    
​    @interface QNChatRoomService : QNLiveService
​    
​    //添加聊天监听
​    - (void)addChatServiceListener:(id<QNChatRoomServiceListener>)listener;
​    //移除聊天监听
​    - (void)removeChatServiceListener;
​    
    //发公聊消息
    - (void)sendPubChatMsg:(NSString *)msg callBack:(void (^)(QNIMMessageObject *msg))callBack;
    //发进房消息
    - (void)sendWelComeMsg:(void (^)(QNIMMessageObject *msg))callBack;
    //发离开消息
    - (void)sendLeaveMsg;
    
    @end


​    
#### 聊天/信令获取


    @protocol QNChatRoomServiceListener <NSObject>
    @optional
    //有人加入聊天室
    - (void)onUserJoin:(QNLiveUser *)user message:(QNIMMessageObject *)message;
    //有人离开聊天室
    - (void)onUserLeave:(QNLiveUser *)user message:(QNIMMessageObject *)message;
    //收到公聊消息
    - (void)onReceivedPuChatMsg:(PubChatModel *)msg message:(QNIMMessageObject *)message;
    //收到点赞消息
    - (void)onReceivedLikeMsgFrom:(QNLiveUser *)sendUser;
    //收到弹幕消息
    - (void)onReceivedDamaku:(PubChatModel *)msg;
    @end

   




​    
