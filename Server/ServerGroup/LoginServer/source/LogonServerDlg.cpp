#include "Include/stdafx.h"
#include "AtlBase.h"
#include "../Include/LogonServerDlg.h"

//////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CLogonServerDlg, CDialog)
	ON_BN_CLICKED(ID_START, OnBnClickedStartService)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedStopService)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedInitService)
END_MESSAGE_MAP()

//构造函数
CLogonServerDlg::CLogonServerDlg() : CDialog(IDD_DIALOG1)
{
	m_bAskQuit=true;
}

//析构函数
CLogonServerDlg::~CLogonServerDlg()
{
}

//控件子类化
void CLogonServerDlg::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT21, m_RichEditCtrl);
}

//初始化函数
BOOL CLogonServerDlg::OnInitDialog()
{
	__super::OnInitDialog();

	//设置图标
	HICON hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON1));
	SetIcon(hIcon,TRUE);
	SetIcon(hIcon,FALSE);

	//设置组件
	if (m_EventService.CreateInstance()==true)
	{
		IUnknownEx * pIUnknownEx=(IUnknownEx *)m_EventService->QueryInterface(IID_IUnknownEx,VER_IUnknownEx);
		m_EventService->SetRichEditHwnd(m_RichEditCtrl.GetSafeHwnd());
		m_LogonService.SetEventService(pIUnknownEx);
	}
	m_RichEditCtrl.SetBackgroundColor(FALSE,RGB(220,220,220));

	//加载配置
	LPCTSTR pszCmdLine=AfxGetApp()->m_lpCmdLine;
	if (pszCmdLine[0]!=0)
	{
		OnBnClickedStartService();
	}

	__super::OnInitDialog();

	//限制输入
	((CEdit *)GetDlgItem(IDC_EDIT8))->LimitText(5);
	((CEdit *)GetDlgItem(IDC_EDIT9))->LimitText(3);
	((CEdit *)GetDlgItem(IDC_EDIT5))->LimitText(31);
	((CEdit *)GetDlgItem(IDC_EDIT2))->LimitText(5);
	((CEdit *)GetDlgItem(IDC_EDIT3))->LimitText(31);
	((CEdit *)GetDlgItem(IDC_EDIT4))->LimitText(31);
	((CEdit *)GetDlgItem(IDC_EDIT10))->LimitText(31);

	//加载参数
	CInitParamter InitParamter;
	InitParamter.LoadInitParamter();

	//设置控件
	SetDlgItemInt(IDC_EDIT8,InitParamter.m_wListenPort,FALSE);
	SetDlgItemInt(IDC_EDIT9,InitParamter.m_wMaxConnect,FALSE);

	//登录数据库
	SetDlgItemInt(IDC_EDIT2,InitParamter.m_wUserDataBasePort,FALSE);
	SetDlgItemText(IDC_EDIT3,InitParamter.m_szUserDataBaseUser);
	SetDlgItemText(IDC_EDIT4,InitParamter.m_szUserDataBasePass);
	SetDlgItemText(IDC_EDIT10,InitParamter.m_szUserDataBaseName);

	//登录数据库地址
	DWORD dwDataBaseIP=inet_addr(InitParamter.m_szUserDataBaseAddr);
	if (dwDataBaseIP==INADDR_NONE)
	{
		LPHOSTENT lpHost=gethostbyname(InitParamter.m_szUserDataBaseAddr);
		if (lpHost!=NULL) dwDataBaseIP=((LPIN_ADDR)lpHost->h_addr)->s_addr;
	}
	CIPAddressCtrl * pDataBaseIP=(CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS1);
	pDataBaseIP->SetAddress(ntohl(dwDataBaseIP));

	//主站地址
	if (InitParamter.m_szMainPage[0]==0) SetDlgItemText(IDC_EDIT5,szStationPage);
	else SetDlgItemText(IDC_EDIT5,InitParamter.m_szMainPage);

	//中心服务器
	dwDataBaseIP=inet_addr(InitParamter.m_szCenterServerAddr);
	if (dwDataBaseIP==INADDR_NONE)
	{
		LPHOSTENT lpHost=gethostbyname(InitParamter.m_szCenterServerAddr);
		if (lpHost!=NULL) dwDataBaseIP=((LPIN_ADDR)lpHost->h_addr)->s_addr;
	}
	pDataBaseIP=(CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS2);
	pDataBaseIP->SetAddress(ntohl(dwDataBaseIP));

	return TRUE;

	return TRUE;
}

//确定消息
void CLogonServerDlg::OnOK()
{
	return;
}

//取消函数
void CLogonServerDlg::OnCancel()
{
	//获取状态
	bool bRuning=m_LogonService.IsService();

	//询问退出
	if ((m_bAskQuit==true)&&(bRuning==true))
	{
		CString strMessage=TEXT("登录服务器正在运行中，确实要退出吗？");
		int iRetCode=AfxMessageBox(strMessage,MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON2);
		if (iRetCode!=IDYES) return;
	}

	//停止服务
	m_bAskQuit=true;
	if (bRuning==true) m_LogonService.StopService();

	__super::OnCancel();
}

//消息解释
BOOL CLogonServerDlg::PreTranslateMessage(MSG * pMsg)
{
	if ((pMsg->message==WM_KEYDOWN)&&(pMsg->wParam==VK_ESCAPE)) return TRUE;
	return __super::PreTranslateMessage(pMsg);
}

//启动服务
void CLogonServerDlg::OnBnClickedStartService()
{
	if (m_LogonService.StartService() )
	{
		GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
		GetDlgItem(ID_START)->EnableWindow(FALSE);
		if (m_EventService.GetInterface()) m_EventService->ShowEventNotify(TEXT("登录服务启动成功"),Level_Normal);
	}

	return;
}

//停止服务
void CLogonServerDlg::OnBnClickedStopService()
{
	if (m_LogonService.StopService()==true)
	{
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
		GetDlgItem(ID_START)->EnableWindow(TRUE);
		if (m_EventService.GetInterface()) m_EventService->ShowEventNotify(TEXT("登录服务停止成功"),Level_Normal); 
	}

	return;
}

//系统配置
void CLogonServerDlg::OnBnClickedInitService()
{
	//获取输入
	CInitParamter InitParamter;
	InitParamter.m_wListenPort=GetDlgItemInt(IDC_EDIT8);
	InitParamter.m_wMaxConnect=GetDlgItemInt(IDC_EDIT9);

	//登录数据库 
	InitParamter.m_wUserDataBasePort=GetDlgItemInt(IDC_EDIT2);
	GetDlgItemText(IDC_EDIT3,InitParamter.m_szUserDataBaseUser,sizeof(InitParamter.m_szUserDataBaseUser));
	GetDlgItemText(IDC_EDIT4,InitParamter.m_szUserDataBasePass,sizeof(InitParamter.m_szUserDataBasePass));
	GetDlgItemText(IDC_EDIT10,InitParamter.m_szUserDataBaseName,sizeof(InitParamter.m_szUserDataBaseName));

	//登录数据库地址
	DWORD dwDataBaseIP=INADDR_NONE;
	BYTE * pAddrByte=(BYTE *)&dwDataBaseIP;
	((CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS1))->GetAddress(dwDataBaseIP);
	_snprintf(InitParamter.m_szUserDataBaseAddr,sizeof(InitParamter.m_szUserDataBaseAddr),TEXT("%d.%d.%d.%d"),
		pAddrByte[3],pAddrByte[2],pAddrByte[1],pAddrByte[0]);

	//主站地址
	GetDlgItemText(IDC_EDIT5,InitParamter.m_szMainPage,sizeof(InitParamter.m_szMainPage));
	if (lstrcmp(InitParamter.m_szMainPage,szStationPage)==0) InitParamter.m_szMainPage[0]=0;

	//中心服务器
	dwDataBaseIP=INADDR_NONE;
	pAddrByte=(BYTE *)&dwDataBaseIP;
	((CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS2))->GetAddress(dwDataBaseIP);
	_snprintf(InitParamter.m_szCenterServerAddr,sizeof(InitParamter.m_szCenterServerAddr),TEXT("%d.%d.%d.%d"),
		pAddrByte[3],pAddrByte[2],pAddrByte[1],pAddrByte[0]);

	//保存设置
	InitParamter.SaveInitParamter(false);

	return;
}

//////////////////////////////////////////////////////////////////////////

