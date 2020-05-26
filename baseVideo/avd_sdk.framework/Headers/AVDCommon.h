//
//  AVDCommon.h
//  avd_sdk
//
//  Created by skin on 15-7-21.
//  Copyright (c) 2015年 t3ee. All rights reserved.
//

#ifndef avd_sdk_AVDCommon_h
#define avd_sdk_AVDCommon_h

#import <Foundation/Foundation.h>

typedef NSInteger       AVDResult;
typedef NSString *      AVDUserId;
typedef NSString *      AVDRoomId;
typedef NSString *      AVDDeviceId;
typedef NSString *      AVDRecordId;
typedef NSString *      AVDLiveId;
typedef NSString *      AVDBoardId;
typedef NSString *      AVDAnnotaionId;


extern AVDUserId const OC_AVD_userId_allUser;          /**< AVD定义的虚假用户Id，用于标识房间中所有用户  */
extern AVDUserId const OC_AVD_userId_allUserWithoutMe; /**< AVD定义的虚假用户Id，用于标识房间中除了自己外的所有用户  */

extern AVDResult const AVD_Success;
extern AVDResult const AVD_Failture;
extern AVDResult const AVD_Error_NoNativeobject;
/* Returned when an instance is not initialized */
extern AVDResult const AVD_Error_Not_Initialized;
/* Returned when an instance is already initialized */
extern AVDResult const AVD_Error_Already_Initialized;
/* Returned by a not implemented function */
extern AVDResult const AVD_Error_Not_Implemented;
/* Returned when null pointer occures */
extern AVDResult const AVD_Error_Null_Pointer;
/* Returned when an unexpected error occurs */
extern AVDResult const AVD_Error_UnExpected;
/* Returned when a memory allocation fails */
extern AVDResult const AVD_Error_Out_Of_Memory;
/* Returned when an illegal value is passed */
extern AVDResult const AVD_Error_Invalid_Arg;
/* Returned when an operation can't complete due to an unavailable resource */
extern AVDResult const AVD_Error_Not_Available;
/* object cann't find */
extern AVDResult const AVD_Error_Not_Found;
/* operation timeout */
extern AVDResult const AVD_Error_TimeOut;
/* object in wrong status */
extern AVDResult const AVD_Error_Wrong_Status;
/* network failure */
extern AVDResult const AVD_Error_Network_Failure;
/* token is none */
extern AVDResult const AVD_Error_No_Token;
/* video input: image convert failed. */
extern AVDResult const AVD_Error_ImageConvert_Failed;
/* need more buff */
extern AVDResult const AVD_Error_Morebuff_Needed;
/* device already occupied */
extern AVDResult const AVD_Error_DeviceOccupied;
/* operation has done */
extern AVDResult const AVD_Error_Operation_Completed;
/* function unauthorized */
extern AVDResult const AVD_Error_Function_Unauthorized;
/* mcu_url is empty in Cluster version mcu*/
extern AVDResult const AVD_Error_Cluster_Invalid;
/* mcu connection failure*/
extern AVDResult const AVD_Error_McuConnection_Failure;
/* publish or priview or setOption(eo_camera_capability_default) not support resolution */
extern AVDResult const AVD_Error_Video_NotSupportResolution;
/* room closed*/
extern AVDResult const AVD_Error_Room_Close;
/* stream connection timeout */
extern AVDResult const AVD_Error_Stream_Connection_TimeOut;
/* get_mcu failed in cluster server */
extern AVDResult const AVD_Error_Rest_GetMcu_Failure;
/* room signal channel connect failed */
extern AVDResult const AVD_Error_Net_ChannelSignal_Failure;
/* room data channel connect failed */
extern AVDResult const AVD_Error_Net_ChannelData_Failure;
/* no data, wait for data ok.  */
extern AVDResult const AVD_Error_Waiting_Data;

// for importer
extern AVDResult const AVD_Error_Importer_Video_Failure;
extern AVDResult const AVD_Error_Importer_Audio_Failure;
extern AVDResult const AVD_Error_Importer_BeKicked;


//server error code
/* client is unauthorized */
extern AVDResult const AVD_Error_Unauthorized;
/* client is rejoin error */
extern AVDResult const AVD_Error_Rejoin;
/* room not found */
extern AVDResult const AVD_Error_Room_None;
/* license expired */
extern AVDResult const AVD_Error_License_Expired;
/* mcu not register */
extern AVDResult const AVD_Error_Mcu_NoRegister;
/* http request param invalid */
extern AVDResult const AVD_Error_Rest_InvalidParam;
/* http request not supported */
extern AVDResult const AVD_Error_Rest_Notsupported;
/* http request timeout */
extern AVDResult const AVD_Error_Rest_TimeOut;
/* none available server */
extern AVDResult const AVD_Error_Server_NoAvailable;
/* server out of max user  */
extern AVDResult const AVD_Error_Server_OutofMaxUser;
/* server is box version */
extern AVDResult const AVD_Error_Server_BoxVersion;
/* room is in used */
extern AVDResult const AVD_Error_Room_InUsed;
/* schedule service not available */
extern AVDResult const AVD_Error_Schedule_Failed;
/* none mcu for roomId */
extern AVDResult const AVD_Error_NoMcu_ByRoomId;
/* mcu not found room */
extern AVDResult const AVD_Error_NoRoom_InMcu;
/* mcu is offline */
extern AVDResult const AVD_Error_Mcu_Offline;
/* master rpc timeout */
extern AVDResult const AVD_Error_Master_RpcTimeout;
/* cluster have no master */
extern AVDResult const AVD_Error_Cluster_NoMaster;
/* cluster error */
extern AVDResult const AVD_Error_Cluster_Error;
/* server is not leader */
extern AVDResult const AVD_Error_Server_NotLeader;
/* mcu server is not exist */
extern AVDResult const AVD_Error_Server_McuNone;
/* service unavailable */
extern AVDResult const AVD_Error_Service_Unavailable;
/* server time out */
extern AVDResult const AVD_Error_Server_TimeOut;
/* version not support */
extern AVDResult const AVD_Error_Version_Invalid;
/* server out of user */
extern AVDResult const AVD_Error_Server_OutofUser;
/* room out of max user */
extern AVDResult const AVD_Error_Room_OutofUser;
/* license out of max user */
extern AVDResult const AVD_Error_License_OutofUser;
/* app room id invalid */
extern AVDResult const AVD_Error_RoomId_Invalid;
/* authentication failed */
extern AVDResult const AVD_Error_Auth_Failed;
/* get mcu not found room */
extern AVDResult const AVD_Error_GetMcu_NoRoom;
/* mcu proxy connect up server failed */
extern AVDResult const AVD_Error_Proxy_UpConn_Failed;
/* database error: data invalid */
extern AVDResult const AVD_Error_Database_Error;
/* function no permission */
extern AVDResult const AVD_Error_Server_NoPermition;
/* room out of max video */
extern AVDResult const AVD_Error_Room_OutofVideo;
/* room out of max audio */
extern AVDResult const AVD_Error_Room_OutofAudio;
/* duplicate publish */
extern AVDResult const AVD_Error_Duplicate_Publish;
/* room token invalid */
extern AVDResult const AVD_Error_Room_ErrToken;
/* duplicate userid join, kick off prejoin user. */
extern AVDResult const AVD_Error_User_DuplicateJoin;
/* server internal error. */
extern AVDResult const AVD_Error_Server_InternalError;
/* server database connection timeout. */
extern AVDResult const AVD_Error_Server_DBConnTimeout;
/* data connection connect failed, kick off user. */
extern AVDResult const AVD_Error_User_DataConnection_Failed;
/* kick off user by someone. */
extern AVDResult const AVD_Error_Room_KickoffBySomeone;
/* out of license kick off user. */
extern AVDResult const AVD_Error_Room_OutofLicense;
/* closed room kick off user. */
extern AVDResult const AVD_Error_Room_closed;

#endif
