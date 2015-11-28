// stdafx.cpp : 只包括标准包含文件的源文件
// GameClient.pch 将是预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

#ifdef _DEBUG
#pragma comment( lib, "../../../Client/GameFramework/Bin/GameFramework_D.lib" )
#pragma comment( lib, "../../../Common/FKUIModule/Bin/FKUIModule_D.lib" )
#else
#pragma comment( lib, "../../../Client/GameFramework/Bin/GameFramework.lib" )
#pragma comment( lib, "../../../Common/FKUIModule/Bin/FKUIModule.lib" )
#endif


