#include "Include/Stdafx.h"
#include "../Resource.h"
#include "../include/GlobalOption.h"
#include "../include/GameFrameControl.h"

#define		WEB_HEIGHT					100					//网页高度

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CGameFrameControl, CDialog)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_MESSAGE(WM_HIT_EXPMESSTION,OnHitExpression)
	ON_BN_CLICKED(IDC_GAME_RULE, OnBnClickedRule)
	ON_BN_CLICKED(IDC_GAME_OPTION, OnBnClickedOption)
	ON_BN_CLICKED(IDC_QUIT_GAME, OnBnClickedQuitGame)
	ON_BN_CLICKED(IDC_SEND_CHAT, OnBnClickedSendChat)
	ON_BN_CLICKED(IDC_EXPRESSION, OnBnClickedExpression)
	ON_BN_CLICKED(IDC_COLOR_SET, OnBnClickedColorSet)
	ON_BN_CLICKED(IDC_CLEAN_SCREEN, OnBnClickedCleanScreen)
	ON_MESSAGE(WM_USER+999,SetUserInfo)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//构造函数
CGameFrameControl::CGameFrameControl(CGameFrameDlg * pGameFrameDlg) : CDialog(IDD_FRAME_CONTROL), m_pGameFrameDlg(pGameFrameDlg)
{
	//设置变量
	m_bRectify=false;
	m_bInitDialog=false;
	m_pAdBrower=NULL;
	m_pIClientKernel=NULL;
	HINSTANCE hInstance=GetModuleHandle(GAMEFRAMEWORK_EXPORTS_NAME);
	m_ImageLeftViewLM.SetLoadInfo(IDB_LEFT_VIEW_LM,hInstance);
	m_ImageLeftViewMM.SetLoadInfo(IDB_LEFT_VIEW_MM,hInstance);
	m_ImageLeftViewRM.SetLoadInfo(IDB_LEFT_VIEW_RM,hInstance);
	m_ImageLeftViewLTM.SetLoadInfo(IDB_LEFT_VIEW_LTM,hInstance);
	m_ImageLeftViewRTM.SetLoadInfo(IDB_LEFT_VIEW_RTM,hInstance);
	m_ImageLeftViewLT.SetLoadInfo(IDB_LEFT_VIEW_LT,hInstance);
	m_ImageLeftViewMT.SetLoadInfo(IDB_LEFT_VIEW_MT,hInstance);
	m_ImageLeftViewRT.SetLoadInfo(IDB_LEFT_VIEW_RT,hInstance);
	m_ImageLeftViewLB.SetLoadInfo(IDB_LEFT_VIEW_LB,hInstance);
	m_ImageLeftViewMB.SetLoadInfo(IDB_LEFT_VIEW_MB,hInstance);
	m_ImageLeftViewRB.SetLoadInfo(IDB_LEFT_VIEW_RB,hInstance);
	m_ImageLeftViewLBM.SetLoadInfo(IDB_LEFT_VIEW_LBM,hInstance);
	m_ImageLeftViewRBM.SetLoadInfo(IDB_LEFT_VIEW_RBM,hInstance);

	return;
}

//析构函数
CGameFrameControl::~CGameFrameControl()
{
}

//控件绑定
void CGameFrameControl::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PHRASE, m_btPhrase);
	DDX_Control(pDX, IDC_COLOR_SET, m_btColorSet);
	DDX_Control(pDX, IDC_SEND_CHAT, m_btSendChat);
	DDX_Control(pDX, IDC_EXPRESSION, m_btExpression);
	DDX_Control(pDX, IDC_CLEAN_SCREEN, m_btCleanScreen);
	DDX_Control(pDX, IDC_CHAT_INPUT, m_ChatInput);
	DDX_Control(pDX, IDC_CHAT_MESSAGE, m_ChatMessage);
	DDX_Control(pDX, IDC_USER_LIST, m_UserListView);
	DDX_Control(pDX, IDC_GAME_OPTION, m_btGameOption);
	DDX_Control(pDX, IDC_QUIT_GAME, m_btQuitGame);
	DDX_Control(pDX, IDC_GAME_RULE, m_btGameRule);
	DDX_Control(pDX, IDC_CHAT_OBJECT, m_ChatObject);
}

//初始化函数
BOOL CGameFrameControl::OnInitDialog()
{
	__super::OnInitDialog();

	//设置控件
	m_UserListView.InitUserListView();
	m_ChatMessage.SetBackgroundColor(FALSE,RGB(165,189,213));

	//设置按钮
	HINSTANCE hInstance=GetModuleHandle(GAMEFRAMEWORK_EXPORTS_NAME);
	m_btPhrase.SetButtonImage(IDB_BT_EXPESSION,hInstance,false);
	m_btExpression.SetButtonImage(IDB_BT_EXPESSION,hInstance,false);
	m_btColorSet.SetButtonImage(IDB_BT_COLOR_SET,hInstance,false);
	m_btCleanScreen.SetButtonImage(IDB_BT_CLEAN_SCREEN,hInstance,false);
	m_btSendChat.SetButtonImage(IDB_BT_SEND_CHAT,hInstance,false);
	m_btGameOption.SetButtonImage(IDB_BT_OPTION,hInstance,false);
	//m_btQuitGame.SetButtonImage(IDB_BT_QUIT,hInstance,false);
	m_btQuitGame.ShowWindow(SW_HIDE);
	m_btGameRule.SetButtonImage(IDB_BT_GAME_RULE,hInstance,false);

	//建立提示控件
	m_ToolTipCtrl.Create(this);
	m_ToolTipCtrl.Activate(TRUE);
	m_ToolTipCtrl.AddTool(GetDlgItem(IDC_EXPRESSION),TEXT("表情"));
	m_ToolTipCtrl.AddTool(GetDlgItem(IDC_COLOR_SET),TEXT("颜色"));
	m_ToolTipCtrl.AddTool(GetDlgItem(IDC_CLEAN_SCREEN),TEXT("清屏"));
	m_ToolTipCtrl.AddTool(GetDlgItem(IDC_SEND_CHAT),TEXT("发送"));

	//创建广告
	m_pAdBrower = new CHtmlBrower;
	m_pAdBrower->Create(NULL,NULL,WS_VISIBLE|WS_CHILD,CRect(0,0,0,0),this,20,NULL);

	//聊天对象
	m_ChatObject.AddString(TEXT("所有人"));
	m_ChatObject.SetCurSel(0);

	//设置变量
	m_bInitDialog=true;
	
	g_GlobalOption.m_lFrameContorl = this->GetSafeHwnd();

	return TRUE;
}

//设置用户信息IE
LRESULT CGameFrameControl::SetUserInfo(WPARAM wParam, LPARAM lParam){
	TCHAR szRuleUrl[128];
	_snprintf(szRuleUrl,sizeof(szRuleUrl),TEXT("http://222.223.65.99/client/info.asp?id=%ld&kindid=%ld"),m_pIClientKernel->GetUserInfo(m_pIClientKernel->GetMeChairID())->dwUserID,m_UserListView.m_wKindID);
	m_pAdBrower->Navigate(TEXT(szRuleUrl));
	m_pAdBrower->EnableBrowser(true);
	return 0;
}

//消息过虑
BOOL CGameFrameControl::PreTranslateMessage(MSG * pMsg)
{
	if ((pMsg->message==WM_KEYDOWN)&&(pMsg->wParam==VK_RETURN))
	{
		OnBnClickedSendChat();
		return TRUE;
	}
	m_ToolTipCtrl.RelayEvent(pMsg);
	return __super::PreTranslateMessage(pMsg);
}

//设置内核
void CGameFrameControl::SetClientKernel(IClientKernel * pIClientKernel)
{
	m_pIClientKernel=pIClientKernel;
	return;
}

//重置控制
void CGameFrameControl::ResetGameFrameControl()
{
	//聊天对象
	int nChatCount=m_ChatObject.GetCount();
	for (int i=1;i<nChatCount;i++) m_ChatObject.DeleteString(1);

	//清理列表
	m_UserListView.DeleteAllItems();

	return;
}

//加入用户
bool CGameFrameControl::InsertUserItem(tagUserData * pUserData)
{
	
	return m_UserListView.InsertUserItem(pUserData);
}

//更新用户
bool CGameFrameControl::UpdateUserItem(tagUserData * pUserData)
{
	return m_UserListView.UpdateUserItem(pUserData);
}

//删除用户
bool CGameFrameControl::DeleteUserItem(tagUserData * pUserData)
{
	return m_UserListView.DeleteUserItem(pUserData);
}

//绘画消息
void CGameFrameControl::OnPaint()
{
	CPaintDC dc(this);

	//绘画背景
	DrawLeftViewFrame(&dc);

	return;
}

//设置按钮
void CGameFrameControl::OnBnClickedOption()
{
	m_pGameFrameDlg->OnGameOptionSet();
	AfxMessageBox( "exit" ) ;
	return;
}

//游戏规则
void CGameFrameControl::OnBnClickedRule()
{
	TCHAR szRuleUrl[128];
	_snprintf(szRuleUrl,sizeof(szRuleUrl),TEXT("http://222.223.65.99/client/OpenGameRule.asp?KindID=%ld"),m_UserListView.m_wKindID);
	ShellExecute(NULL,TEXT("open"),szRuleUrl,NULL,NULL,SW_SHOWDEFAULT);

	return;
}

//退出按钮
void CGameFrameControl::OnBnClickedQuitGame()
{
	AfxGetMainWnd()->PostMessage(WM_CLOSE,0,0);
	
	return;
}

//绘画背景
BOOL CGameFrameControl::OnEraseBkgnd(CDC * pDC)
{
	return TRUE;
}

//位置消息
void CGameFrameControl::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	//调整控件
	RectifyControl(cx,cy);

	return;
}

//表情消息
LRESULT CGameFrameControl::OnHitExpression(WPARAM wParam, LPARAM lParam)
{
	CExpressionItem * pExpressionItem=m_Expression.GetExpressItem((WORD)wParam);
	if (pExpressionItem!=NULL)
	{
		CString strBuffer;
		m_ChatInput.GetWindowText(strBuffer);
		strBuffer+=pExpressionItem->m_szTrancelate;
		m_ChatInput.SetWindowText(strBuffer);
		m_ChatInput.SetFocus();
		m_ChatInput.SetSel(strBuffer.GetLength(),strBuffer.GetLength());
	}

	return 0;
}

//发送按钮
void CGameFrameControl::OnBnClickedSendChat()
{
	//聊天信息
	TCHAR szChatMessage[MAX_CHAT_LEN]=TEXT("");
	m_ChatInput.GetWindowText(szChatMessage,CountArray(szChatMessage));
	if (szChatMessage[0]!=0)
	{
		DWORD dwTargetUserID=0L;
		int nItem=m_ChatObject.GetCurSel();
		if ((nItem!=LB_ERR)&&(nItem!=0)) 
		{
			dwTargetUserID=(DWORD)m_ChatObject.GetItemData(nItem);
		}
		m_ChatInput.SetWindowText(TEXT(""));
		m_pIClientKernel->SendChatMessage(dwTargetUserID,szChatMessage,g_GlobalOption.m_crChatTX);
	}

	//设置界面
	m_ChatInput.SetFocus();

	return;
}

//表情按钮
void CGameFrameControl::OnBnClickedExpression()
{
	//建立表情窗口
	if (m_Expression.GetSafeHwnd()==NULL) m_Expression.CreateExpression(this);

	//移动窗口
	CRect rcButton;
	CSize ExpressSize;
	m_Expression.GetFixSize(ExpressSize);
	m_btExpression.GetWindowRect(&rcButton);
	m_Expression.MoveWindow(rcButton.right-ExpressSize.cx,rcButton.top-ExpressSize.cy,ExpressSize.cx,ExpressSize.cy);
	m_Expression.ShowWindow(SW_SHOW);
	m_Expression.SetFocus();

	return;
}

//颜色按钮
void CGameFrameControl::OnBnClickedColorSet()
{

	//设置颜色
	CColorDialog ColorDialog(g_GlobalOption.m_crChatTX,CC_FULLOPEN);
	if (ColorDialog.DoModal()==IDOK) g_GlobalOption.m_crChatTX=ColorDialog.GetColor();

	//设置界面
	m_ChatInput.SetFocus();

	return;
}

//清屏按钮
void CGameFrameControl::OnBnClickedCleanScreen()
{
	m_ChatMessage.CleanScreen();
	return;
}

//左视图区
void CGameFrameControl::DrawLeftViewFrame(CDC * pDC)
{
	//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	//变量定义
	HDC hDC=pDC->m_hDC;
	int nXPos=0,nYPos=0;
	int nComminutePos=rcClient.Height()*3/7;

	//加载资源
	CImageHandle ImageLeftViewLMHandle(&m_ImageLeftViewLM);
	CImageHandle ImageLeftViewMMHandle(&m_ImageLeftViewMM);
	CImageHandle ImageLeftViewRMHandle(&m_ImageLeftViewRM);
	CImageHandle ImageLeftViewLTMHandle(&m_ImageLeftViewLTM);
	CImageHandle ImageLeftViewRTMHandle(&m_ImageLeftViewRTM);
	CImageHandle ImageLeftViewLTHandle(&m_ImageLeftViewLT);
	CImageHandle ImageLeftViewMTHandle(&m_ImageLeftViewMT);
	CImageHandle ImageLeftViewRTHandle(&m_ImageLeftViewRT);
	CImageHandle ImageLeftViewLBHandle(&m_ImageLeftViewLB);
	CImageHandle ImageLeftViewMBHandle(&m_ImageLeftViewMB);
	CImageHandle ImageLeftViewRBHandle(&m_ImageLeftViewRB);
	CImageHandle ImageLeftViewLBMHandle(&m_ImageLeftViewLBM);
	CImageHandle ImageLeftViewRBMHandle(&m_ImageLeftViewRBM);

	//绘画上框
	m_ImageLeftViewLT.BitBlt(hDC,0,0);
	for (nXPos=m_ImageLeftViewLT.GetWidth();nXPos<rcClient.Width();nXPos+=m_ImageLeftViewMT.GetWidth())
	{
		m_ImageLeftViewMT.BitBlt(hDC,nXPos,0);
	}
	m_ImageLeftViewRT.BitBlt(hDC,rcClient.Width()-m_ImageLeftViewRT.GetWidth(),0);

	//绘画左右
	nXPos=rcClient.Width()-m_ImageLeftViewRTM.GetWidth();
	for (nYPos=m_ImageLeftViewLT.GetHeight();nYPos<nComminutePos-m_ImageLeftViewLM.GetHeight();nYPos+=m_ImageLeftViewLTM.GetHeight())
	{
		m_ImageLeftViewLTM.BitBlt(hDC,0,nYPos);
		m_ImageLeftViewRTM.BitBlt(hDC,nXPos,nYPos);
	}

	//绘画中间
	m_ImageLeftViewLM.BitBlt(hDC,0,nComminutePos-m_ImageLeftViewLM.GetHeight());
	for (nXPos=m_ImageLeftViewLM.GetWidth();nXPos<rcClient.Width();nXPos+=m_ImageLeftViewMM.GetWidth())
	{
		m_ImageLeftViewMM.BitBlt(hDC,nXPos,nComminutePos-m_ImageLeftViewMM.GetHeight());
	}
	m_ImageLeftViewRM.BitBlt(hDC,rcClient.Width()-m_ImageLeftViewRM.GetWidth(),nComminutePos-m_ImageLeftViewRM.GetHeight());

	//绘画左右
	nXPos=rcClient.Width()-m_ImageLeftViewRBM.GetWidth();
	for (nYPos=nComminutePos;nYPos<rcClient.Height()-m_ImageLeftViewLB.GetHeight();nYPos+=m_ImageLeftViewLBM.GetHeight())
	{
		m_ImageLeftViewLBM.BitBlt(hDC,0,nYPos);
		m_ImageLeftViewRBM.BitBlt(hDC,nXPos,nYPos);
	}

	//绘画下框
	nYPos=rcClient.Height()-m_ImageLeftViewMB.GetHeight();
	m_ImageLeftViewLB.BitBlt(hDC,0,rcClient.Height()-m_ImageLeftViewLB.GetHeight());
	for (nXPos=m_ImageLeftViewLB.GetWidth();nXPos<rcClient.Width()-m_ImageLeftViewRB.GetWidth();nXPos+=m_ImageLeftViewMB.GetWidth())
	{
		m_ImageLeftViewMB.BitBlt(hDC,nXPos,nYPos);
	}
	m_ImageLeftViewRB.BitBlt(hDC,rcClient.Width()-m_ImageLeftViewRB.GetWidth(),rcClient.Height()-m_ImageLeftViewRB.GetHeight());

	return;
}

//调整控件
void CGameFrameControl::RectifyControl(int nWidth, int nHeight)
{
	//状态判断
	if (m_bInitDialog==false) return;
	if ((nWidth==0)||(nHeight==0)) return;

	//变量定义
	const int nComminutePos=nHeight*3/7;
	const UINT uFlags=SWP_NOACTIVATE|SWP_NOZORDER|SWP_NOCOPYBITS;

	//移动控件
	HDWP hDwp=BeginDeferWindowPos(32);

	//列表区域
	//DeferWindowPos(hDwp,m_UserListView,NULL,5,180,nWidth-15,nComminutePos-187,uFlags);
	DeferWindowPos(hDwp,m_UserListView,NULL,1,164,nWidth-17,nComminutePos-177,uFlags);

	//聊天区域
	CRect rcButton;
	m_btPhrase.GetWindowRect(&rcButton);
	CButton * pButtonArray[]={&m_btExpression,&m_btColorSet,&m_btCleanScreen};
	//for (int i=0;i<CountArray(pButtonArray);i++)
	//{
	//	DeferWindowPos(hDwp,pButtonArray[i]->m_hWnd,NULL,15+(rcButton.Width()+5)*i,nHeight-103,rcButton.Width(),rcButton.Height(),uFlags);
	//}
	for (int i=0;i<CountArray(pButtonArray);i++)
	{
		DeferWindowPos(hDwp,pButtonArray[i]->m_hWnd,NULL,129+(rcButton.Width()+1)*i,nHeight-51,rcButton.Width(),rcButton.Height(),uFlags);
	}
	m_btSendChat.GetWindowRect(&rcButton);
	DeferWindowPos(hDwp,m_btSendChat,NULL,nWidth-rcButton.Width()-17,nHeight-31,rcButton.Width(),rcButton.Height(),uFlags);
	//DeferWindowPos(hDwp,m_ChatObject,NULL,15,nHeight-81,70,200,uFlags);
	//DeferWindowPos(hDwp,m_ChatInput,NULL,87,nHeight-81,nWidth-rcButton.Width()-107,19,uFlags);
	//DeferWindowPos(hDwp,m_ChatMessage,NULL,5,nComminutePos,nWidth-15,nHeight-nComminutePos-rcButton.Height()-92,uFlags);
	//DeferWindowPos(hDwp,m_pAdBrower->GetSafeHwnd(),NULL,3,30,nWidth-10,144,uFlags);
	DeferWindowPos(hDwp,m_ChatObject,NULL,1,nHeight-51,70,200,uFlags);
	DeferWindowPos(hDwp,m_ChatInput,NULL,1,nHeight-32,nWidth-rcButton.Width()-20,19,uFlags);
	DeferWindowPos(hDwp,m_ChatMessage,NULL,1,nComminutePos,nWidth-19,nHeight-nComminutePos-rcButton.Height()-34,uFlags);
	DeferWindowPos(hDwp,m_pAdBrower->GetSafeHwnd(),NULL,1,14,201,150,uFlags);

	//功能按钮
	int nYPosButton=nHeight-51;
	int nBeginPos=nWidth-144,nButtonSpace=0;
	m_btGameOption.GetWindowRect(&rcButton);
	DeferWindowPos(hDwp,m_btGameOption,NULL,nBeginPos,nYPosButton,rcButton.Width(),rcButton.Height(),uFlags);
	DeferWindowPos(hDwp,m_btGameRule,NULL,nBeginPos+nButtonSpace+rcButton.Width(),nYPosButton,rcButton.Width(),rcButton.Height(),uFlags);
	DeferWindowPos(hDwp,m_btQuitGame,NULL,nBeginPos+nButtonSpace*2+rcButton.Width()*2,nYPosButton,rcButton.Width(),rcButton.Height(),uFlags);


	EndDeferWindowPos(hDwp);

	//重画界面
	Invalidate(FALSE);
	UpdateWindow();

	return;
}

//////////////////////////////////////////////////////////////////////////
