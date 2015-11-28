#pragma once


#include "..\Include\GraphBuilder.h"
#include "..\Include\MyBaseFilter.h"
#include "..\Include\RInputPin.h"
#include "..\Include\CaptureDevice.h"

class _declspec(dllexport)  CInMin
{
private:
	CGraphBuilder* m_pVideoInGraphBuilder;
	CCaptureDevice m_VideoCaptureDevice;
	CMyBaseFilter* m_pVideoInMyBaseFilter;

	CGraphBuilder* m_pAudioInGraphBuilder;
	CCaptureDevice m_AudioCaptureDevice;
	CMyBaseFilter* m_pAudioInMyBaseFilter;
public:
	CInMin(void);
	~CInMin(void);

	void Init(int AudioDeviceIndex=0, int VedioDeviceIndex=0);
	void Release(void);

	void Run();
	void Stop();
	void Setup();
};
