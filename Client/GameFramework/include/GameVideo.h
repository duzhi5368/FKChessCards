#pragma once

#include "GameFrameVideo.h"
#include "videoclient.h"

class GAMEFRAMEWORK_CLASS CGameVideo
{
private:
	int m_WindowNum; //窗口数
	CWnd* m_pParent; //父窗口
	CGameFrameVideo **m_pGameFrameVideo; //窗口指针
	//CVideoClient* m_pVideoClient; //视频客户端
	
public:
	CVideoClient	*m_pVideoClient;
	CGameVideo(void);
	virtual ~CGameVideo(void);

	//初始化
	void Init( int WindowNum, CWnd* pParent );
	void r() {return ;} ;
	//释放
	void Release();
	//设置窗口
	void SetWindowPos( int Pos, int x, int y, int cx = 0, int cy = 0 );
	void ShowWindow( int nCmdShow, int Pos=-1 );
	void SetMe( int Pos ){ m_pGameFrameVideo[Pos]->SetMe(); };
	//登陆
	BOOL Login( char* IP/*服务器IP*/, int Port/*服务器端口*/, DWORD RoomID, DWORD DeskID, DWORD Pos );
};
