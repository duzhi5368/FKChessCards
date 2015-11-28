#pragma once
#include "../Resource.h"
#include "afxwin.h"
#include "GameFrame.h"
#include "afxcmn.h"

// CGameFrameVideo 对话框

class CVideoClient;
class CGameFrameVideo : public CDialog
{
	DECLARE_DYNAMIC(CGameFrameVideo)

public:
	CGameFrameVideo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGameFrameVideo();

	BOOL m_bMe; //显示自己

// 对话框数据
	enum { IDD = IDD_FRAME_VIDEO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel(){ return; };
	virtual void OnOK(){ return; };
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

protected:
	CSkinImage							m_ImageLeftViewLM;			//资源图片
	CSkinImage							m_ImageLeftViewMM;			//资源图片
	CSkinImage							m_ImageLeftViewRM;			//资源图片
	CSkinImage							m_ImageLeftViewLTM;			//资源图片
	CSkinImage							m_ImageLeftViewRTM;			//资源图片
	CSkinImage							m_ImageLeftViewLT;			//资源图片
	CSkinImage							m_ImageLeftViewMT;			//资源图片
	CSkinImage							m_ImageLeftViewRT;			//资源图片
	CSkinImage							m_ImageLeftViewLB;			//资源图片
	CSkinImage							m_ImageLeftViewMB;			//资源图片
	CSkinImage							m_ImageLeftViewRB;			//资源图片
	CSkinImage							m_ImageLeftViewLBM;			//资源图片
	CSkinImage							m_ImageLeftViewRBM;			//资源图片

public:
	virtual BOOL OnInitDialog();
	CVideoClient* m_pVideoClient;
	void SetMe();

	CSkinButton		m_btVisibleVideo; //显示、隐藏视频
	CProgressCtrl m_ProgressSoundPop;
	CSkinButton m_btVideoSetup;
	afx_msg void OnBnClickedButtonVideoSetup();
	afx_msg void OnBnClickedButtonVisible();
	
	//左视图区
	void DrawLeftViewFrame(CDC * pDC);
	afx_msg void OnPaint();
	CStatic m_video;
	afx_msg void OnStnClickedStaticVideo();
};
