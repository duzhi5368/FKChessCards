#include "Include/Stdafx.h"
#include "../include/gamevideo.h"

CGameVideo::CGameVideo(void)
{
	m_WindowNum = 0; //窗口数
	m_pParent = NULL; //父窗口
	m_pGameFrameVideo = NULL; //窗口指针
	m_pVideoClient = NULL;
}

CGameVideo::~CGameVideo(void)
{
	Release();
}

void CGameVideo::Init( int WindowNum, CWnd* pParent )
{
	Release();

	m_WindowNum = WindowNum;
	m_pGameFrameVideo = new CGameFrameVideo*[WindowNum];
	m_pVideoClient = new CVideoClient;
	m_pVideoClient->Init();
	for( int i=0;i<WindowNum;i++ )
	{
        m_pGameFrameVideo[i] = new CGameFrameVideo;
		m_pGameFrameVideo[i]->Create( CGameFrameVideo::IDD, pParent );
		m_pGameFrameVideo[i]->m_pVideoClient = m_pVideoClient;
		HWND hWnd = NULL;
		m_pGameFrameVideo[i]->GetDlgItem(IDC_STATIC_VIDEO, &hWnd);
		if(hWnd)
			m_pVideoClient->m_VideoWindow[i].SetHwnd( hWnd );
	}
}

void CGameVideo::Release()
{
	if( m_pVideoClient )
	{
		delete m_pVideoClient;
        m_pVideoClient = NULL;
	}
	if( m_pGameFrameVideo )
	{
		for( int i=0;i<m_WindowNum;i++ )
		{
			delete m_pGameFrameVideo[i];
		}
		delete[] m_pGameFrameVideo;
		m_pGameFrameVideo = NULL;
	}
}

void CGameVideo::SetWindowPos( int Pos, int x, int y, int cx, int cy )
{
	if( m_pGameFrameVideo )
	{
		if( Pos>=0 && Pos<m_WindowNum )
			m_pGameFrameVideo[Pos]->SetWindowPos( m_pParent, x, y, cx, cy, NULL );
	}
}

void CGameVideo::ShowWindow( int nCmdShow, int Pos )
{
	if( m_pGameFrameVideo )
	{
		if( Pos==-1 )
		{
			for( int i=0;i<m_WindowNum;i++ )
			{
				m_pGameFrameVideo[i]->ShowWindow( nCmdShow );
			}
		}
		else if( Pos>=0 && Pos<m_WindowNum )
		{
			m_pGameFrameVideo[Pos]->ShowWindow( nCmdShow );
		}
	}
}

BOOL CGameVideo::Login( char* IP/*服务器IP*/, int Port/*服务器端口*/, DWORD RoomID, DWORD DeskID, DWORD Pos )
{
	if( m_pVideoClient )
	{
		return m_pVideoClient->Login( IP, Port, RoomID, DeskID, Pos );
	}
	return FALSE;
}