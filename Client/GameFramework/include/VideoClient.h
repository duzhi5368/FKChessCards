#pragma once

#include "MyUserManage.h"
#include "..\Include\UserManage.h"
#include "..\Include\OutMin.h"
#include "..\Include\InMin.h"
#include "..\Include\VideoWindow.h"

class _declspec(dllexport) CVideoClient
{
private:
	CUdpManage UdpManage;
	COutMin OutMin;
	CInMin InMin;
public:
	CVideoClient(void);
	virtual ~CVideoClient(void);
	CVideoWindow m_VideoWindow[10];

	void Init(void);
	void Release(void);

	DWORD m_Room;
	DWORD m_Desk;
	BOOL m_Enable;

	//登陆
	BOOL Login( char* IP/*服务器IP*/, int Port/*服务器端口*/, DWORD RoomID, DWORD DeskID, DWORD Pos );
	void SendAllUser( char* Buffer, int len );
	void OutSound( char* pData, int len );
	void OutVideo( DWORD Pos, char* pData, int len );
	void SaveSoundData( char* Buffer, int len );
	void OutString( DWORD Pos, char* pchar );
	CUdpSocket* GetSocket(int i);
	void Quit();
	void SendDebugMsg(char* p);

		
	void Setup();
	void Enable( bool b );
	BOOL Enable(){ return m_Enable; };
};
