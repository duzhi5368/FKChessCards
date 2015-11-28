#ifndef COMPANION_HEAD_FILE
#define COMPANION_HEAD_FILE

//////////////////////////////////////////////////////////////////////////

//平台头文件
#include "../../../Common/CommonHead/Template/Template.h"

//全局头文件
#include "../../../Common/CommonHead/Common/GlobalDef.h"

//组件头文件
#include "../../../Common/CommonHead/ModuleInterface/IUnknownEx.h"
#include "../../../Common/FKUIModule/Include/SkinControls.h"
#include "../../../Common/FKLobby/include/ComService.h"

//宏定义
#define LIT_FACE_WIDTH						16							//头像宽度
#define LIT_FACE_HEIGHT						16							//头像高度
#define NOR_FACE_WIDTH						32							//头像宽度
#define NOR_FACE_HEIGHT						32							//头像高度

//////////////////////////////////////////////////////////////////////////
//公共宏定义

//导出定义
#ifndef GAMECLIENTLOBBY_CLASS
	#ifdef  GAMECLIENTLOBBY_EXPORTS
		#define GAMECLIENTLOBBY_CLASS _declspec(dllexport)
	#else
		#define GAMECLIENTLOBBY_CLASS _declspec(dllimport)
	#endif
#endif

//模块定义
#ifdef _DEBUG
	#define GAMECLIENTLOBBY_EXPORTS_NAME	TEXT("GameClientLobby_D.dll")					//组件 DLL 名字
#else
	#define GAMECLIENTLOBBY_EXPORTS_NAME	TEXT("GameClientLobby.dll")					//组件 DLL 名字
#endif

//////////////////////////////////////////////////////////////////////////
//枚举定义

//关系定义
enum enCompanion
{
	enCompanion_UnKnow,				//未知关系
	enCompanion_Friend,				//好友关系
	enCompanion_Detest,				//厌恶关系
};

//////////////////////////////////////////////////////////////////////////
//结构定义

//长度定义
#define CP_NOTE_LEN					128									//备注长度

//用户记录结构
struct tagCompanionItem
{
	DWORD							dwUserID;							//用户 I D
	TCHAR							szFace[128];						//用户头像
	enCompanion						Companion;							//用户关系
	TCHAR							szNote[CP_NOTE_LEN];				//用户备注
	TCHAR							szAccounts[NAME_LEN];				//用户账号
	TCHAR							szName[NAME_LEN];					//用户昵称
};

//////////////////////////////////////////////////////////////////////////

#define VER_ICompanionManager INTERFACE_VERSION(2,1)
static const GUID IID_ICompanionManager={0x7bef6deb,0x5915,0x4021,0xa1,0x4f,0xa9,0xa3,0xec,0xad,0x74,0xf3};

//关系管理接口
interface ICompanionManager : public IUnknownEx
{
	//管理接口
public:
	//加载信息
	virtual bool __cdecl LoadCompanion()=NULL;
	//保存关系
	virtual bool __cdecl SaveCompanion()=NULL;
	//显示窗口
	virtual bool __cdecl ShowCompanionManager()=NULL;
	//关系数目
	virtual INT_PTR __cdecl GetCompanionItemCount()=NULL;

	//功能接口
public:
	//加入关系
	virtual const tagCompanionItem * __cdecl InsertCompanionItem(tagCompanionItem & CompanionItem)=NULL;
	//更新关系
	virtual const tagCompanionItem * __cdecl UpdateCompanionItem(tagCompanionItem & CompanionItem)=NULL;
	//更新关系
	virtual const tagCompanionItem * __cdecl UpdateCompanionItem(DWORD dwUserID, LPCTSTR pszNote)=NULL;
	//更新关系
	virtual const tagCompanionItem * __cdecl UpdateCompanionItem(DWORD dwUserID, LPCTSTR pszAccounts, LPCTSTR pszFace)=NULL;
	//删除关系
	virtual bool __cdecl DeleteCompanionItem(DWORD dwUserID)=NULL;

	//查找接口
public:
	//枚举关系
	virtual const tagCompanionItem * __cdecl EmunCompanionItem(WORD wIndex)=NULL;
	//寻找关系
	virtual const tagCompanionItem * __cdecl SearchCompanionItem(DWORD dwUserID)=NULL;
};

//////////////////////////////////////////////////////////////////////////

//关系管理辅助类
class CCompanionManagerHelper : public CTempldateHelper<ICompanionManager>
{
	//函数定义
public:
	//构造函数
	CCompanionManagerHelper(void) : CTempldateHelper<ICompanionManager>(IID_ICompanionManager,
		VER_ICompanionManager,GAMECLIENTLOBBY_EXPORTS_NAME,TEXT("CreateCompanionManager")) { }
};

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//结构体定义

//下载请求
struct tagDownLoadRequest
{
	bool							bDisplay;							//是否显示
	TCHAR							szDescribe[128];					//描述信息
	TCHAR							szFileName[MAX_PATH];				//本地文件
	TCHAR							szLocalPath[MAX_PATH];				//本地路径
	TCHAR							szDownLoadUrl[MAX_PATH];			//下载路径
};

//////////////////////////////////////////////////////////////////////////

#define VER_IDownLoadService INTERFACE_VERSION(3,1)
static const GUID IID_IDownLoadService={0xe0b37184,0x6fbe,0x44ac,0xa4,0x83,0xab,0xa6,0x89,0x9b,0x33,0xd4};

//下载服务接口
interface IDownLoadService : public IUnknownEx
{
	//获取数目
	virtual INT_PTR __cdecl GetDownLoadMissionCount()=NULL;
	//设置接口
	virtual bool __cdecl SetDownLoadServiceSink(IUnknownEx * pIUnknownEx)=NULL;
	//下载请求
	virtual DWORD __cdecl AddDownLoadRequest(DWORD dwDownLoadType, tagDownLoadRequest * pDownLoadRequest)=NULL;
};

//////////////////////////////////////////////////////////////////////////

#define VER_IDownLoadServiceSink INTERFACE_VERSION(1,1)
static const GUID IID_IDownLoadServiceSink={0xb339b588,0xd328,0x4482,0x96,0xde,0xc4,0x12,0xdd,0x78,0x81,0xec};

//下载服务回调接口
interface IDownLoadServiceSink : public IUnknownEx
{
};

//////////////////////////////////////////////////////////////////////////

//下载服务辅助类
class CDownLoadServiceHelper : public CTempldateHelper<IDownLoadService>
{
	//函数定义
public:
	//构造函数
	CDownLoadServiceHelper(void) : CTempldateHelper<IDownLoadService>(IID_IDownLoadService,
		VER_IDownLoadService,GAMECLIENTLOBBY_EXPORTS_NAME,TEXT("CreateDownLoadService"))
	{
	}
};



#define VER_IUserFaceRes INTERFACE_VERSION(1,1)
static const GUID IID_IUserFaceRes={0xd9c22bd3,0x986b,0x4513,0x83,0x5d,0x52,0xb4,0x13,0x20,0x76,0x34};

//头像组件接口
interface IUserFaceRes : public IUnknownEx
{
	//获取数目
	virtual WORD __cdecl GetFaceCount()=NULL;
	//获取大小
	virtual const CSize & __cdecl GetSmallFaceSize()=NULL;
	//获取大小
	virtual const CSize & __cdecl GetNormalFaceSize()=NULL;
	//绘画头像
	virtual void __cdecl DrawFace(CDC * pDC, int nXPos, int nYPos, int xSize, int ySize, LPCTSTR pszFace, int cbGender)=NULL;
	//绘画头像
	virtual void __cdecl DrawSmallFace(CDC * pDC, int nXPos, int nYPos, LPCTSTR pszFace, int cbGender)=NULL;
	//绘画头像
	virtual void __cdecl DrawNormalFace(CDC * pDC, int nXPos, int nYPos, LPCTSTR pszFace, int cbGender)=NULL;
	//绘画头像
//	virtual void __cdecl DrawNormal3DFace(CDC * pDC, int nXPos, int nYPos, WORD wFaceID)=NULL;
	
};

//////////////////////////////////////////////////////////////////////////

#define VER_IFaceControl INTERFACE_VERSION(1,1)
static const GUID IID_IFaceControl={0xd2c483c,0xbdfa,0x46a6,0x8e,0x60,0xf8,0xc8,0x77,0xed,0x59,0xc3};

//头像控件接口
interface IFaceControl : public IUnknownEx
{
	//信息接口
public:
	//头像宽度
	virtual int __cdecl GetFaceWidth()=NULL;
	//头像高度
	virtual int __cdecl GetFaceHeight()=NULL;
	//头像数目
	virtual WORD __cdecl GetFaceItemCount()=NULL;

	//绘画接口
public:
	//绘画头像
	virtual void __cdecl DrawFaceItem(CDC * pDC, int nXPos, int nYPos, WORD wFaceID)=NULL;
};

//////////////////////////////////////////////////////////////////////////

//头像组件辅助类
class CUserFaceResHelper : public CTempldateHelper<IUserFaceRes>
{
	//函数定义
public:
	//构造函数
	CUserFaceResHelper(void) : CTempldateHelper<IUserFaceRes>(IID_IUserFaceRes,
		VER_IUserFaceRes,GAMECLIENTLOBBY_EXPORTS_NAME,TEXT("CreateUserFaceRes"))
	{
	}
};

//////////////////////////////////////////////////////////////////////////

//头像控件辅助类
class CFaceControlHelper : public CTempldateHelper<IFaceControl>
{
	//函数定义
public:
	//构造函数
	CFaceControlHelper(void) : CTempldateHelper<IFaceControl>(IID_IFaceControl,
		VER_IFaceControl,GAMECLIENTLOBBY_EXPORTS_NAME,TEXT("CreateFaceControl"))
	{
	}
};


//////////////////////////////////////////////////////////////////////////
//结构体定义

//消息配置
struct tagMessageOption
{
	COLORREF							crName;							//名字颜色
	COLORREF							crSystemHead;					//系统颜色
	COLORREF							crSystemString;					//系统颜色
	TCHAR								szDefaultFont[32];				//默认字体
};

//消息大小
#define MS_NORMAL						0								//常规大小
#define MS_MIDDLING						1								//中等大小
#define MS_LARGE						2								//大号字体

//////////////////////////////////////////////////////////////////////////

#define VER_IMessageProxy INTERFACE_VERSION(1,1)
static const GUID IID_IMessageProxy={0xe8bd2387,0x9c2a,0x4346,0xb3,0x2c,0x17,0xb7,0xb3,0x51,0x9a,0x2f};

//信息代理接口
interface IMessageProxy : public IUnknownEx
{
	//配置接口
public:
	//设置句柄
	virtual bool __cdecl SetRichEditHwnd(CSkinRichEdit * pSkinRichEdit)=NULL;
	//设置颜色
	virtual bool __cdecl SetMessageOption(tagMessageOption & MessageOption)=NULL;

	//控制接口
public:
	//清除屏幕
	virtual bool __cdecl CleanScreen()=NULL;
	//设置滚动
	virtual bool __cdecl SetAutoScroll(bool bScroll)=NULL;
	//加载消息
	virtual bool __cdecl LoadMessage(LPCTSTR pszFileName)=NULL;
	//保存信息
	virtual bool __cdecl SaveMessage(LPCTSTR pszFileName)=NULL;

	//信息接口
public:
	//插入图片
	virtual bool __cdecl InsertImage(CBitmap * pBitmap)=NULL;
	//插入时间
	virtual bool __cdecl InsertSystemTime(COLORREF crColor)=NULL;
	//用户名字
	virtual bool __cdecl InsertUserName(LPCTSTR pszUserName)=NULL;
	//系统消息
	virtual bool __cdecl InsertSystemString(LPCTSTR pszString, UINT uSize)=NULL;
	//特色消息
	virtual bool __cdecl InsertShtickString(LPCTSTR pszString, COLORREF crColor, UINT uSize, bool bNewLine)=NULL;
	//普通消息
	virtual bool __cdecl InsertGeneralString(LPCTSTR pszString, COLORREF crColor, UINT uSize, bool bNewLine)=NULL;
	//用户聊天
	virtual bool __cdecl InsertUserChat(LPCTSTR pszSendName, LPCTSTR pszString, COLORREF crColor, UINT uSize)=NULL;
	//用户聊天
	virtual bool __cdecl InsertUserChat(LPCTSTR pszSendName, LPCTSTR pszRecvName, LPCTSTR pszString, COLORREF crColor, UINT uSize)=NULL;
};

//////////////////////////////////////////////////////////////////////////

//消息代理辅助类
class CMessageProxyHelper : public CTempldateHelper<IMessageProxy>
{
	//函数定义
public:
	//构造函数
	CMessageProxyHelper(void) : CTempldateHelper<IMessageProxy>(IID_IMessageProxy,
		VER_IMessageProxy,GAMECLIENTLOBBY_EXPORTS_NAME,TEXT("CreateMessageProxy")) { }
};

//////////////////////////////////////////////////////////////////////////
//导出类头文件

#include "Expression.h"



//内核主命令码
#define IPC_MIAN_IPC_KERNEL					0							//内核命令

//内核子命令码
#define IPC_SUB_IPC_CLIENT_CONNECT			1							//连接通知
#define IPC_SUB_IPC_SERVER_ACCEPT			2							//应答通知
#define IPC_SUB_IPC_CLIENT_CLOSE			3							//关闭通知

//////////////////////////////////////////////////////////////////////////

#define VER_IChannelMessageSink INTERFACE_VERSION(1,1)
static const GUID IID_IChannelMessageSink={0x7a672dca,0x141e,0x45a6,0x95,0xc4,0x43,0x79,0x23,0x7f,0x29,0x73};

//信道消息钩子接口
interface IChannelMessageSink : public IUnknownEx
{
	//信道数据处理
	virtual bool __cdecl OnChannelMessage(const IPC_Head * pHead, const void * pIPCBuffer, WORD wDataSize, HWND hWndSend)=NULL;
};

//////////////////////////////////////////////////////////////////////////

#define VER_IChannelEventSink INTERFACE_VERSION(1,1)
static const GUID IID_IChannelEventSink={0xb87334af,0x3f52,0x4e51,0x9d,0xc6,0x51,0x93,0x24,0x66,0x9e,0x2e};

//信道事件钩子接口
interface IChannelEventSink : public IUnknownEx
{
	//连接消息
	virtual bool __cdecl OnChannelConnect(HWND hWndSend)=NULL;
	//应答消息
	virtual bool __cdecl OnChannelAccept(HWND hWndSend)=NULL;
	//断开消息
	virtual bool __cdecl OnChannelClose(HWND hWndSend, bool bInitiative)=NULL;
};

//////////////////////////////////////////////////////////////////////////

#define VER_IChannelService INTERFACE_VERSION(1,1)
static const GUID IID_IChannelService={0x4d0151e9,0xbd65,0x4a4c,0xa6,0xf8,0x25,0x74,0x68,0x17,0x6e,0x74};

//信道模块接口
interface IChannelService : public IUnknownEx
{
	//设置事件
	virtual bool __cdecl SetChannelEventSink(IUnknownEx * pIUnknownEx)=NULL;
	//设置消息
	virtual bool __cdecl SetChannelMessageSink(IUnknownEx * pIUnknownEx)=NULL;
	//获取事件
	virtual void * __cdecl GetChannelEventSink(const IID & Guid, DWORD dwQueryVer)=NULL;
	//获取消息
	virtual void * __cdecl GetChannelMessageSink(const IID & Guid, DWORD dwQueryVer)=NULL;
	//是否连接
	virtual bool __cdecl IsConnect(bool bEfficacy)=NULL;
	//创建函数
	virtual bool __cdecl CreateChannel(HWND hWndServer)=NULL;
	//关闭函数
	virtual bool __cdecl CloseChannel(bool bNotifyServer, bool bNotifySink)=NULL;
	//发送数据
	virtual bool __cdecl SendData(WORD wMainCmdID, WORD wSubCmdID)=NULL;
	//发送数据
	virtual bool __cdecl SendData(WORD wMainCmdID, WORD wSubCmdID, void * pBuffer, WORD wDataSize)=NULL;
};

//////////////////////////////////////////////////////////////////////////

//信道对象辅助类
class CChannelServiceHelper : public CTempldateHelper<IChannelService>
{
	//函数定义
public:
	//构造函数
	CChannelServiceHelper(void) : CTempldateHelper<IChannelService>(IID_IChannelService,
		VER_IChannelService,GAMECLIENTLOBBY_EXPORTS_NAME,TEXT("CreateChannelService"))
	{
	}
};

//////////////////////////////////////////////////////////////////////////

//导出组件文件
#include "IPCControls.h"

//////////////////////////////////////////////////////////////////////////



#define VER_IGameRankManager INTERFACE_VERSION(1,1)
static const GUID IID_IGameRankManager={0x850e5617,0x4eab,0x4f2e,0xae,0x11,0xef,0xa3,0x22,0x65,0xe0,0xc2};

//游戏等级接口
interface IGameRankManager : public IUnknownEx
{
	//获取等级
	virtual LPCTSTR __cdecl GetGameRank(WORD wKindID, LONG lScore, WORD wGameGenre)=NULL;
};

//////////////////////////////////////////////////////////////////////////

//关系管理辅助类
class CGameRankManagerHelper : public CTempldateHelper<IGameRankManager>
{
	//函数定义
public:
	//构造函数
	CGameRankManagerHelper(void) : CTempldateHelper<IGameRankManager>(IID_IGameRankManager,
		VER_IGameRankManager,GAMECLIENTLOBBY_EXPORTS_NAME,TEXT("CreateGameRankManager")) { }
};

static CString FindExtension(const CString& name)
{
	int len = name.GetLength();
	int i;
	for (i = len-1; i >= 0; i--)
	{
		if (name[i] == '.')
		{
			return name.Mid(i+1);
		}
	}
	return CString("");
}

#endif