// stdafx.cpp : 只包括标准包含文件的源文件
// CenterServer.pch 将是预编译头
// stdafx.obj 将包含预编译类型信息

#include "../Include/stdafx.h"

//
//my lib
//
#ifdef _DEBUG
#pragma comment(lib, "../../../Common/FKLobby/Bin/FKLobby_D.lib")
#else
#pragma comment(lib, "../../../Common/FKLobby/Bin/FKLobby.lib")
#endif


