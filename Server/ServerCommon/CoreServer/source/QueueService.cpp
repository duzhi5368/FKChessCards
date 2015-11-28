#include "Include/stdafx.h"
#include "../Include/QueueService.h"

//////////////////////////////////////////////////////////////////////////

//���캯��
CQueueServiceThread::CQueueServiceThread(void)
{
	m_hCompletionPort=NULL;
	memset(m_cbBuffer,0,sizeof(m_cbBuffer));
}

//��������
CQueueServiceThread::~CQueueServiceThread(void)
{
}

//���ú���
bool CQueueServiceThread::InitThread(HANDLE hCompletionPort)
{
	//Ч�����
	ASSERT(IsRuning()==false);
	ASSERT(m_hCompletionPort==NULL);

	//���ñ���
	m_hCompletionPort=hCompletionPort;
	memset(m_cbBuffer,0,sizeof(m_cbBuffer));

	return true;
}

//ȡ������
bool CQueueServiceThread::UnInitThread()
{
	//Ч�����
	ASSERT(IsRuning()==false);

	//���ñ���
	m_hCompletionPort=NULL;
	memset(m_cbBuffer,0,sizeof(m_cbBuffer));

	return true;
}

//���к���
bool CQueueServiceThread::RepetitionRun()
{
	//Ч�����
	ASSERT(m_hCompletionPort!=NULL);

	//��������
	DWORD dwThancferred=0;
	OVERLAPPED * pOverLapped=NULL;
	CQueueService * pQueueService=NULL;

	//�ȴ���ɶ˿�
	if (GetQueuedCompletionStatus(m_hCompletionPort,&dwThancferred,(PULONG_PTR)&pQueueService,&pOverLapped,INFINITE))
	{
		//�ж��˳�
		if (pQueueService==NULL) return false;

		//��ȡ����
		tagDataHead DataHead;
		bool bSuccess=pQueueService->GetData(DataHead,m_cbBuffer,sizeof(m_cbBuffer));
		ASSERT(bSuccess==true);

		//��������
		if (bSuccess==true) pQueueService->OnQueueServiceThread(DataHead,m_cbBuffer,DataHead.wDataSize);

		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////

//���캯��
CQueueService::CQueueService(void)
{
	m_bService=false;
	m_hCompletionPort=NULL;
	m_pIQueueServiceSink=NULL;
}

//��������
CQueueService::~CQueueService(void)
{
	//ֹͣ����
	StopService();

	return;
}

//�ӿڲ�ѯ
void * __cdecl CQueueService::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IQueueService,Guid,dwQueryVer);
	QUERYINTERFACE(IQueueServiceEngine,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IQueueServiceEngine,Guid,dwQueryVer);
	return NULL;
}

//���ýӿ�
bool __cdecl CQueueService::SetQueueServiceSink(IUnknownEx * pIUnknownEx)
{
	ASSERT(pIUnknownEx!=NULL);
	m_pIQueueServiceSink=GET_OBJECTPTR_INTERFACE(pIUnknownEx,IQueueServiceSink);
	ASSERT(m_pIQueueServiceSink!=NULL);
	return (m_pIQueueServiceSink!=NULL);
}

//������Ϣ
bool __cdecl CQueueService::GetBurthenInfo(tagBurthenInfo & BurthenInfo)
{
	CThreadLockHandle LockHandle(&m_ThreadLock);
	return m_DataStorage.GetBurthenInfo(BurthenInfo);
}

//��������
bool __cdecl CQueueService::AddToQueue(WORD wIdentifier, void * const pBuffer, WORD wDataSize)
{
	CThreadLockHandle LockHandle(&m_ThreadLock);
	m_DataStorage.AddData(wIdentifier,pBuffer,wDataSize);
	PostQueuedCompletionStatus(m_hCompletionPort,wDataSize,(ULONG_PTR)this,NULL);
	return true;
}

//��ʼ����
bool __cdecl CQueueService::StartService()
{
	//Ч�����
	ASSERT(m_bService==false);
	ASSERT(m_hCompletionPort==NULL);
	ASSERT(m_pIQueueServiceSink!=NULL);

	//������ɶ˿�
	m_hCompletionPort=CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,NULL,1);
	if (m_hCompletionPort==NULL) throw TEXT("���ж�����ɶ˿ڴ���ʧ��");

	//�����߳�
	if (m_QueueServiceThread.InitThread(m_hCompletionPort)==false) throw TEXT("���ж����̳߳�ʼ��ʧ��");
	if (m_QueueServiceThread.StartThead()==false) throw TEXT("���ж����߳�����ʧ��");

	//���ò���
	m_bService=true;

	return true;
}

//ֹͣ����
bool __cdecl CQueueService::StopService()
{
	//���ñ���
	m_bService=false;

	//ֹͣ�߳�
	if (m_hCompletionPort!=NULL) PostQueuedCompletionStatus(m_hCompletionPort,0,NULL,NULL);
	m_QueueServiceThread.StopThread();
	m_QueueServiceThread.UnInitThread();

	//�ر���ɶ˿�
	if (m_hCompletionPort!=NULL)
	{
		CloseHandle(m_hCompletionPort);
		m_hCompletionPort=NULL;
	}

	//��������
	m_DataStorage.RemoveData(false);

	return true;
}

//��ȡ����
bool CQueueService::GetData(tagDataHead & DataHead, void * pBuffer, WORD wBufferSize)
{
	CThreadLockHandle LockHandle(&m_ThreadLock);
	return m_DataStorage.GetData(DataHead,pBuffer,wBufferSize);
}

//������Ϣ
void CQueueService::OnQueueServiceThread(const tagDataHead & DataHead, void * pBuffer, WORD wDataSize)
{
	ASSERT(m_pIQueueServiceSink!=NULL);
	try	
	{ 
		m_pIQueueServiceSink->OnQueueServiceSink(DataHead.wIdentifier,pBuffer,DataHead.wDataSize,DataHead.dwInsertTime); 
	}
	catch (...) {}
	return;
}

//////////////////////////////////////////////////////////////////////////

//����������
extern "C" __declspec(dllexport) void * __cdecl CreateQueueService(const GUID & Guid, DWORD dwInterfaceVer)
{
	//��������
	CQueueService * pQueueService=NULL;
	try
	{
		pQueueService=new CQueueService();
		if (pQueueService==NULL) throw TEXT("����ʧ��");
		void * pObject=pQueueService->QueryInterface(Guid,dwInterfaceVer);
		if (pObject==NULL) throw TEXT("�ӿڲ�ѯʧ��");
		return pObject;
	}
	catch (...) {}

	//��������
	SafeDelete(pQueueService);
	return NULL;
}

//////////////////////////////////////////////////////////////////////////