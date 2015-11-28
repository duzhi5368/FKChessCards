#ifndef SKIN_CONTROLS_HEAD_FILE
#define SKIN_CONTROLS_HEAD_FILE

//////////////////////////////////////////////////////////////////////////

#include "AfxHtml.h"
//ϵͳͷ�ļ�
#include <GdiPlus.h>
#include <AtlImage.h>
using namespace Gdiplus;

//ƽ̨ͷ�ļ�
#include "..\..\CommonHead\Template\Template.h"
#include "..\..\CommonHead\ModuleInterface\IUnknownEx.h"

//////////////////////////////////////////////////////////////////////////
//�����궨��

//��������
#ifndef FKUIMODULE_CLASS
	#ifdef  FKUIMODULE_EXPORTS
		#define FKUIMODULE_CLASS _declspec(dllexport)
	#else
		#define FKUIMODULE_CLASS _declspec(dllimport)
	#endif
#endif

//ģ�鶨��
#ifdef _DEBUG
	#define FKUIMODULE_DLL_NAME	TEXT("FKUIModule_D.dll")			//��� DLL ����
#else
	#define FKUIMODULE_DLL_NAME	TEXT("FKUIModule.dll")			//��� DLL ����
#endif

//////////////////////////////////////////////////////////////////////////
//ö�ٶ���

//��������ö��
enum enAttributeType
{
	Type_EMPTY,
	Type_VOID,
	Type_INT,
	Type_BYTE,
	Type_WORD,
	Type_LONG,
	Type_DWORD,
	Type_DOUBLE,
	Type_STRING,
};

//////////////////////////////////////////////////////////////////////////

#define VER_IMouseEvent INTERFACE_VERSION(1,1)
static const GUID IID_IMouseEvent={0x4bbf8f62,0xa706,0x45c2,0x97,0x65,0xb8,0x47,0xaa,0x7,0xe7,0x8e};

//����¼��ص��ӿ�
interface IMouseEvent : public IUnknownEx
{
	//����뿪
	virtual HRESULT __cdecl OnEventMouseLeft(UINT uControlID, WPARAM wParam, LPARAM lParam)=NULL;
	//����ƶ�
	virtual HRESULT __cdecl OnEventMouseMove(UINT uControlID, WPARAM wParam, LPARAM lParam)=NULL;
	//��갴ť
	virtual HRESULT __cdecl OnEventLButtonUp(UINT uControlID, WPARAM wParam, LPARAM lParam)=NULL;
	//��갴ť
	virtual HRESULT __cdecl OnEventLButtonDown(UINT uControlID, WPARAM wParam, LPARAM lParam)=NULL;
	//��갴ť
	virtual HRESULT __cdecl OnEventRButtonUp(UINT uControlID, WPARAM wParam, LPARAM lParam)=NULL;
	//��갴ť
	virtual HRESULT __cdecl OnEventRButtonDown(UINT uControlID, WPARAM wParam, LPARAM lParam)=NULL;
};

//////////////////////////////////////////////////////////////////////////

#define VER_IAttribute INTERFACE_VERSION(1,1)
static const GUID IID_IAttribute={0xf75b8e91,0x5e0d,0x4e3a,{0xb7,0xae,0xa7,0x72,0x3d,0x4,0x41,0x8a}};

//������ӿ�
interface IAttribute : public IUnknownEx
{
	//��ȡ��ϣֵ
	virtual DWORD __cdecl GetHashValue()=NULL;
	//�Ƿ�ֻ��
	virtual bool __cdecl IsReadOnly()=NULL;
	//��ȡ����
	virtual LPCTSTR __cdecl GetAttributeName()=NULL;
	//��ȡ����
	virtual enAttributeType __cdecl GetAttributeType()=NULL;
	//��ȡ PTR
	virtual bool __cdecl GetValue(VOID * * ppvValue)=NULL;
	//��ȡ INT
	virtual bool __cdecl GetValue(INT & iValue)=NULL;
	//��ȡ BYTE
	virtual bool __cdecl GetValue(BYTE & cbValue)=NULL;
	//��ȡ WORD
	virtual bool __cdecl GetValue(WORD & wValue)=NULL;
	//��ȡ LONG
	virtual bool __cdecl GetValue(LONG & lValue)=NULL;
	//��ȡ DWORD
	virtual bool __cdecl GetValue(DWORD & dwValue)=NULL;
	//��ȡ DOUBLE
	virtual bool __cdecl GetValue(DOUBLE & dValue)=NULL;
	//��ȡ�ַ���
	virtual bool __cdecl GetValue(CString & strValue)=NULL;
	//��ȡ����
	virtual bool __cdecl GetVarValue(CString & strValue)=NULL;
	//���� INT
	virtual bool __cdecl SetValue(void * pValue)=NULL;
	//���� INT
	virtual bool __cdecl SetValue(INT iValue)=NULL;
	//���� BYTE
	virtual bool __cdecl SetValue(BYTE cbValue)=NULL;
	//���� WORD
	virtual bool __cdecl SetValue(WORD wValue)=NULL;
	//���� LONG
	virtual bool __cdecl SetValue(LONG lValue)=NULL;
	//���� DWORD
	virtual bool __cdecl SetValue(DWORD dwValue)=NULL;
	//���� DOUBLE
	virtual bool __cdecl SetValue(DOUBLE dValue)=NULL;
	//���� STRING
	virtual bool __cdecl SetValue(LPCTSTR pszValue)=NULL;
};

//////////////////////////////////////////////////////////////////////////

#define VER_IAttributeManager INTERFACE_VERSION(1,1)
static const GUID IID_IAttributeManager={0x5935b008,0xeaa,0x432b,{0xa4,0x89,0x3c,0x5a,0xd7,0xda,0x17,0xb1}};

//���Թ����ӿ�
interface IAttributeManager : public IUnknownEx
{
	//ע������
	virtual bool __cdecl UnRegisterAttribute(LPCTSTR pszName)=NULL;
	//ע������
	virtual bool __cdecl RegisterAttribute(LPCTSTR pszName, VOID * pPtr, bool bReadOnly)=NULL;
	//ע������
	virtual bool __cdecl RegisterAttribute(LPCTSTR pszName, INT * pInt, bool bReadOnly)=NULL;
	//ע������
	virtual bool __cdecl RegisterAttribute(LPCTSTR pszName, BYTE * pByte, bool bReadOnly)=NULL;
	//ע������
	virtual bool __cdecl RegisterAttribute(LPCTSTR pszName, WORD * pWord, bool bReadOnly)=NULL;
	//ע������
	virtual bool __cdecl RegisterAttribute(LPCTSTR pszName, LONG * pLong, bool bReadOnly)=NULL;
	//ע������
	virtual bool __cdecl RegisterAttribute(LPCTSTR pszName, DWORD * pDword, bool bReadOnly)=NULL;
	//ע������
	virtual bool __cdecl RegisterAttribute(LPCTSTR pszName, DOUBLE * pDouble, bool bReadOnly)=NULL;
	//ע������
	virtual bool __cdecl RegisterAttribute(LPCTSTR pszName, CString * pString, bool bReadOnly)=NULL;
};

//////////////////////////////////////////////////////////////////////////

#define VER_IAttributeService INTERFACE_VERSION(1,1)
static const GUID IID_IAttributeService={0x51860649,0xcff4,0x44e7,0xaa,0x63,0x6,0xb5,0x2d,0x95,0x5e,0x9f};

//���Է���ӿ�
interface IAttributeService : public IUnknownEx
{
	//��ѯ����
	virtual IAttribute * __cdecl QueryAttribute(WORD wIndex)=NULL;
	//��ѯ����
	virtual IAttribute * __cdecl QueryAttribute(LPCTSTR pszName)=NULL;
	//��ȡ����
	virtual bool __cdecl GetAttributeValue(LPCTSTR pszName, VOID * * ppvValue)=NULL;
	//��ȡ����
	virtual bool __cdecl GetAttributeValue(LPCTSTR pszName, INT & iValue)=NULL;
	//��ȡ����
	virtual bool __cdecl GetAttributeValue(LPCTSTR pszName, BYTE & cbValue)=NULL;
	//��ȡ����
	virtual bool __cdecl GetAttributeValue(LPCTSTR pszName, WORD & wValue)=NULL;
	//��ȡ����
	virtual bool __cdecl GetAttributeValue(LPCTSTR pszName, LONG & lValue)=NULL;
	//��ȡ����
	virtual bool __cdecl GetAttributeValue(LPCTSTR pszName, DWORD & dwValue)=NULL;
	//��ȡ����
	virtual bool __cdecl GetAttributeValue(LPCTSTR pszName, DOUBLE & dValue)=NULL;
	//��ȡ����
	virtual bool __cdecl GetAttributeValue(LPCTSTR pszName, CString & strValue)=NULL;
	//��ȡ����
	virtual bool __cdecl GetAttributeVarValue(LPCTSTR pszName, CString & strValue)=NULL;
	//��������
	virtual bool __cdecl SetAttributeValue(LPCTSTR pszName, void * pValue)=NULL;
	//��������
	virtual bool __cdecl SetAttributeValue(LPCTSTR pszName, INT iValue)=NULL;
	//��������
	virtual bool __cdecl SetAttributeValue(LPCTSTR pszName, BYTE cbValue)=NULL;
	//��������
	virtual bool __cdecl SetAttributeValue(LPCTSTR pszName, WORD wValue)=NULL;
	//��������
	virtual bool __cdecl SetAttributeValue(LPCTSTR pszName, LONG lValue)=NULL;
	//��������
	virtual bool __cdecl SetAttributeValue(LPCTSTR pszName, DWORD dwValue)=NULL;
	//��������
	virtual bool __cdecl SetAttributeValue(LPCTSTR pszName, DOUBLE dValue)=NULL;
	//��������
	virtual bool __cdecl SetAttributeValue(LPCTSTR pszName, LPCTSTR pszValue)=NULL;
};

//////////////////////////////////////////////////////////////////////////

#define VER_ISkinRecord INTERFACE_VERSION(1,1)
static const GUID IID_ISkinRecord={0x3b41889b,0xc8c2,0x4b07,0xa1,0x7e,0xad,0x98,0x41,0x57,0x1d,0x60};

//�������ýӿ�
interface ISkinRecord : public IUnknownEx
{
	//��ȡĿ¼
	virtual LPCTSTR __cdecl GetResourceDirectory()=NULL;
	//��ȡ����
	virtual int __cdecl ReadInt(LPCTSTR pszClassName, LPCTSTR pszItem, int iDefValue)=NULL;
	//��ȡ����
	virtual COLORREF __cdecl ReadColor(LPCTSTR pszClassName, LPCTSTR pszItem, COLORREF crDefValue)=NULL;
	//��ȡ����
	virtual RECT __cdecl ReadRect(LPCTSTR pszClassName, LPCTSTR pszItem, const RECT & rcDefValue)=NULL;
	//��ȡ����
	virtual POINT __cdecl ReadPoint(LPCTSTR pszClassName, LPCTSTR pszItem, const POINT & ptDefValue)=NULL;
	//��ȡ����
	virtual CString __cdecl ReadString(LPCTSTR pszClassName, LPCTSTR pszItem, LPCTSTR pszDefValue)=NULL;
	//д�����
	virtual bool __cdecl WriteInt(LPCTSTR pszClassName, LPCTSTR pszItem, int iValue)=NULL;
	//д�����
	virtual bool __cdecl WriteColor(LPCTSTR pszClassName, LPCTSTR pszItem, COLORREF crValue)=NULL;
	//д�����
	virtual bool __cdecl WriteRect(LPCTSTR pszClassName, LPCTSTR pszItem, const RECT & rcValue)=NULL;
	//д�����
	virtual bool __cdecl WritePoint(LPCTSTR pszClassName, LPCTSTR pszItem, const POINT & ptValue)=NULL;
	//д�����
	virtual bool __cdecl WriteString(LPCTSTR pszClassName, LPCTSTR pszItem, LPCTSTR pszValue)=NULL;
};

//////////////////////////////////////////////////////////////////////////

#define VER_ISkinAttribute INTERFACE_VERSION(1,1)
static const GUID IID_ISkinAttribute={0xbd02b27d,0x7274,0x46a5,0x82,0x7b,0xc4,0x49,0x83,0xfe,0x8b,0x66};

//�������Խӿ�
interface ISkinAttribute : public IUnknownEx
{
	//��ȡ����
	virtual LPCTSTR __cdecl GetClassName()=NULL;
	//��ȡ����
	virtual HFONT __cdecl GetDefaultFont()=NULL;
	//��������
	virtual bool __cdecl SaveSkinOption()=NULL;
	//��������
	virtual bool __cdecl LoadSkinOption()=NULL;
};

//////////////////////////////////////////////////////////////////////////

//������ͷ�ļ�
#ifndef FKUIMODULE_EXPORTS
	#include "SkinEdit.h"
	#include "SkinImage.h"
	#include "SkinRichEdit.h"
	#include "SkinDialog.h"
	#include "SkinFrameWnd.h"
	#include "SkinButton.h"
	#include "TransButton.h"
	#include "SkinListCtrl.h"
	#include "SkinSplitter.h"
	#include "SkinHyperLink.h"
	#include "SkinAttribute.h"
#endif

//////////////////////////////////////////////////////////////////////////

//͸���滭
extern "C" FKUIMODULE_CLASS void AlphaDrawImage(CDC * pDesDC, int nXDes, int nYDes, int nDesWidth, int nDesHeight, 
	CDC * pScrDC, int nXScr, int nYScr, int nScrWidth, int nScrHeight, COLORREF crTransColor);

//////////////////////////////////////////////////////////////////////////

//��������
#ifndef FKUIMODULE_EXPORTS

	//�������
	inline bool SaveSkinResource() 
	{ 
		return CSkinAttribute::SaveSkinAttribute(); 
	}
	
	//���ؽ���
	inline bool LoadSkinResource(IUnknownEx * pIUnknownEx) 
	{ 
		return CSkinAttribute::LoadUserInfo(pIUnknownEx); 
	}

#endif

//////////////////////////////////////////////////////////////////////////

#endif