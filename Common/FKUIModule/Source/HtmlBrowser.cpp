#include "Include/stdafx.h"
#include "../Include/HtmlBrowser.h"

BEGIN_MESSAGE_MAP(CHtmlBrowerB, CHtmlView)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//构造函数
CHtmlBrowerB::CHtmlBrowerB()
{
	m_bEnableBrowser=false;
}

//析构函数
CHtmlBrowerB::~CHtmlBrowerB()
{
}

//销毁方法
void CHtmlBrowerB::OnDestroy()
{
	CFrameWnd* pFrame = GetParentFrame(); 
	if (pFrame != NULL && pFrame->GetActiveView() == this) pFrame->SetActiveView(NULL); 
}

//转向网页
void CHtmlBrowerB::Navigate(LPCTSTR pszURL)
{
	ASSERT(pszURL!=NULL);
	m_strNavigateUrl=pszURL;
	if (m_bEnableBrowser) __super::Navigate(m_strNavigateUrl,NULL,NULL,NULL,NULL);
	return;
}

//启用网页
bool CHtmlBrowerB::EnableBrowser(bool bEnableBrowser)
{
	if (m_bEnableBrowser!=bEnableBrowser)
	{
		m_bEnableBrowser=bEnableBrowser;
		if (m_bEnableBrowser==true)
		{
			if ((GetSafeHwnd()!=NULL)&&(m_strNavigateUrl.IsEmpty()==FALSE))
			{
				__super::Navigate(m_strNavigateUrl,NULL,NULL,NULL,NULL);
			}
		}
		else m_strNavigateUrl.Empty();
	}
	return m_bEnableBrowser;
}

//////////////////////////////////////////////////////////////////////////
