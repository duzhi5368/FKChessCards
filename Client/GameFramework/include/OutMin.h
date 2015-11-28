#pragma once

#include "..\Include\GraphBuilder.h"
#include "..\Include\MyBaseFilter.h"
#include "..\Include\OutputPin.h"

class _declspec(dllexport) COutMin
{
private:
	CGraphBuilder* m_pOutGraphBuilder;
	CMyBaseFilter* m_pOutMyBaseFilter;
public:
	COutMin(void);
	virtual ~COutMin(void);

	void Init(void);
	void OutSound( char* pData, int len );
	void Release(void);
};
