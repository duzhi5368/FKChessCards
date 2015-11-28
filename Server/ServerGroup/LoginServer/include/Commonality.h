#ifndef COMMONALITY_HEAD_FILE
#define COMMONALITY_HEAD_FILE

#pragma once

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////
//定义头文件

//命令码文件
#include "..\..\..\..\Common\CommonHead\Message\CMD_Plaza.h"
#include "..\..\..\..\Common\CommonHead\Message\CMD_Center.h"

//全局头文件
#include "..\..\..\..\Common\CommonHead\Common\GlobalField.h"
#include "..\..\..\..\Common\CommonHead\Common\GlobalService.h"

//////////////////////////////////////////////////////////////////////////
//数据库对象定义

//数据库请求标识
#define	DBR_GP_LOGON_BY_ACCOUNTS	1									//帐号登陆
#define	DBR_GP_LOGON_BY_USERID		2									//I D 登陆
#define DBR_GP_REGISTER_ACCOUNTS	3									//注册帐号

//数据库输出标识
#define DBR_GP_LOGON_SUCCESS		100									//登陆成功
#define DBR_GP_LOGON_ERROR			101									//登陆失败

//帐号登陆
struct DBR_GP_LogonByAccounts
{
	DWORD							dwClientIP;							//连接地址
	TCHAR							szAccounts[NAME_LEN];				//登录帐号
	TCHAR							szPassWord[PASS_LEN];				//登录密码
	TCHAR							szRealityPass[PASS_LEN];			//真实密码
};

//ID 登录
struct DBR_GP_LogonByUserID
{
	DWORD							dwClientIP;							//连接地址
	DWORD							dwUserID;							//用户 I D
	TCHAR							szPassWord[PASS_LEN];				//登录密码
};

//帐号注册
struct DBR_GP_RegisterAccounts
{
	DWORD							dwClientIP;							//连接地址
	TCHAR							szFace[128];						//注册头像
	TCHAR							szAccounts[NAME_LEN];				//登录帐号
	TCHAR							szPassWord[PASS_LEN];				//登录密码
};

//登陆成功
struct DBR_GP_LogonSuccess
{
	BYTE							cbGender;							//用户性别
	BYTE							cbMember;							//会员等级
	TCHAR							szFace[128];						//头像
	DWORD							dwUserID;							//用户 I D
	DWORD							dwTZPoint;							//用户点券
	DWORD							dwUserRight;						//用户等级
	DWORD							dwMasterRight;						//管理权限
	TCHAR							szAccounts[NAME_LEN];				//登录帐号
	TCHAR							szName[NAME_LEN];					//用户昵称
	TCHAR							szPassWord[PASS_LEN];				//登录密码
};

//登陆失败
struct DBR_GP_LogonError
{
	LONG							lErrorCode;							//错误代码
	TCHAR							szErrorDescribe[128];				//错误消息
};

//////////////////////////////////////////////////////////////////////////

#endif