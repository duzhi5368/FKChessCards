// GameFrameVideo.cpp : 实现文件
//

#include "Include/Stdafx.h"
#include "../include/GameFrameVideo.h"
#include "../include/videoclient.h"
#include "../include/gameframevideo.h"


// CGameFrameVideo 对话框

IMPLEMENT_DYNAMIC(CGameFrameVideo, CDialog)
CGameFrameVideo::CGameFrameVideo(CWnd* pParent /*=NULL*/)
	: CDialog(CGameFrameVideo::IDD, pParent)
{
	m_pVideoClient = NULL;

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
}

CGameFrameVideo::~CGameFrameVideo()
{
}

void CGameFrameVideo::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_ViSIBLE, m_btVisibleVideo);
	DDX_Control(pDX, IDC_PROGRESS_SOUND_POP, m_ProgressSoundPop);
	DDX_Control(pDX, IDC_BUTTON_VIDEO_SETUP, m_btVideoSetup);
	DDX_Control(pDX, IDC_STATIC_VIDEO, m_video);
}


BEGIN_MESSAGE_MAP(CGameFrameVideo, CDialog)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON_VIDEO_SETUP, OnBnClickedButtonVideoSetup)
	ON_BN_CLICKED(IDC_BUTTON_ViSIBLE, OnBnClickedButtonVisible)
	ON_WM_PAINT()
	ON_STN_CLICKED(IDC_STATIC_VIDEO, OnStnClickedStaticVideo)
END_MESSAGE_MAP()


// CGameFrameVideo 消息处理程序


BOOL CGameFrameVideo::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	return __super::PreTranslateMessage(pMsg);
}

BOOL CGameFrameVideo::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return TRUE;
}

BOOL CGameFrameVideo::OnInitDialog()
{
	__super::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//设置按钮
	HINSTANCE hInstance=GetModuleHandle(GAMEFRAMEWORK_EXPORTS_NAME);
	//m_btVisibleVideo.SetButtonImage(IDB_BT_CLEAN_SCREEN,hInstance,false);
	//m_btVideoSetup.SetButtonImage(IDB_BT_CLEAN_SCREEN,hInstance,false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CGameFrameVideo::OnBnClickedButtonVideoSetup()
{
	// TODO: 在此添加控件通知处理程序代码
	if( m_pVideoClient )
		m_pVideoClient->Setup();
}

void CGameFrameVideo::OnBnClickedButtonVisible()
{
	// TODO: 在此添加控件通知处理程序代码
	if( m_pVideoClient )
	{
		m_pVideoClient->Enable( !m_pVideoClient->Enable() );
	}
}

void CGameFrameVideo::SetMe()
{
	m_bMe = true;
	CWnd* cWnd = GetDlgItem(IDC_BUTTON_VIDEO_SETUP);
	if( cWnd )
	{
		cWnd->ShowWindow( SW_SHOW );
	}
}

//左视图区
void CGameFrameVideo::DrawLeftViewFrame(CDC * pDC)
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

void CGameFrameVideo::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	//绘画背景
	//DrawLeftViewFrame(&dc);
}

void CGameFrameVideo::OnStnClickedStaticVideo()
{
	// TODO: 在此添加控件通知处理程序代码
}
