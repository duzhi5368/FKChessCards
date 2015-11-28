// stdafx.cpp : 只包括标准包含文件的源文件
// GameFrame.pch 将成为预编译头
// stdafx.obj 将包含预编译类型信息

#include "../Include/Stdafx.h"


#pragma comment( lib, "Winmm.lib" )
#ifdef _DEBUG
#pragma comment( lib, "..\\..\\Common\\FKUIModule\\bin\\FKUIModule_D.lib" )
#pragma comment( lib, "..\\GameClientLobby\\bin\\GameClientLobby_D.lib" )
#pragma comment( lib, "..\\..\\Common\\FKLobby\\bin\\FKLobby_D.lib" )
#else
#pragma comment( lib, "..\\..\\Common\\FKUIModule\\bin\\FKUIModule.lib" )
#pragma comment( lib, "..\\GameClientLobby\\bin\\GameClientLobby.lib" )
#pragma comment( lib, "..\\..\\Common\\FKLobby\\bin\\FKLobby.lib" )
#endif

