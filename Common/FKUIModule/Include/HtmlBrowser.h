#ifndef HTML_BROWSER_HEAD_FILE
#define HTML_BROWSER_HEAD_FILE

#pragma once

#include "SkinControls.h"
//////////////////////////////////////////////////////////////////////////

//浏览器视图
class FKUIMODULE_CLASS CHtmlBrowerB : public CHtmlView
{
	//变量定义
protected:
	bool							m_bEnableBrowser;					//是否启用
	CString							m_strNavigateUrl;					//页面地址

	//函数定义
public:
	//构造函数
	CHtmlBrowerB();
	//析构函数
	virtual ~CHtmlBrowerB();
	afx_msg void OnDestroy(); //销毁方法

	//功能函数
public:
	//转向网页
	void Navigate(LPCTSTR pszUrl);
	//启用网页
	bool EnableBrowser(bool bEnableBrowser);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif