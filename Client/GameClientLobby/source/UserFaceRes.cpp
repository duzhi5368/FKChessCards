#include "Include/StdAfx.h"
#include "Resource.h"
#include "../Include/UserFaceRes.h"
#include  <algorithm>
#include <vfw.h>
#pragma comment(lib,"vfw32.lib")
//////////////////////////////////////////////////////////////////////////

//宏定义
#define COLOR_TRANS						RGB(255,0,255)				//透明颜色

//////////////////////////////////////////////////////////////////////////

inline UINT DownLoad(LPVOID pParam)
{
	while (1)
	{
		if(TempFileList.size()>0)
		{
			m_HeadCS.Lock();
			std::vector<std::string>::reverse_iterator rit = TempFileList.rbegin();
			LPCTSTR pszFace = (LPCTSTR)((std::string)*rit).c_str();;
			TempFileList.erase((++rit).base());
			m_HeadCS.Unlock();
			CString DATFile=TEXT("FaceImage.DAT");

			CFileFind	finder;
			BOOL	FF;

			FF=finder.FindFile(DATFile);
			if(!FF){
				CFile pwFile;
				pwFile.Open(DATFile,CFile::modeCreate);
				pwFile.Close();
			}
			CFile pwFile;
			pwFile.Open(DATFile,CFile::modeReadWrite| CFile::typeBinary);
			char FileNum[10];
			pwFile.Read(FileNum,9);
			sprintf(FileNum,"%d",atol(FileNum)+1);
			pwFile.SeekToBegin();
			pwFile.Write(FileNum,9);

			CInternetSession    is;
			CStdioFile        *psf;

			CString picUrl="http://www.17tzy.com/tzyBBS/avatars/common/0.bmp";

			psf = is.OpenURL( picUrl, 1, INTERNET_FLAG_TRANSFER_BINARY | INTERNET_FLAG_RELOAD);

			BITMAPFILEHEADER bmfh;

			// 步骤1　读取文件头
			int nCount = psf->Read((LPVOID) &bmfh, sizeof(BITMAPFILEHEADER));

			// 判断是否是BMP格式的位图
			if(bmfh.bfType != BMP_HEADER_MARKER) 
			{
				continue;
			}

			// 计算信息头加上调色板的大小并分内存
			int nSize = bmfh.bfOffBits - sizeof(BITMAPFILEHEADER);
			LPBITMAPINFOHEADER m_pBMIH = (LPBITMAPINFOHEADER) new BYTE[nSize];

			// 步骤2　读取信息头和调色板
			nCount = psf->Read(m_pBMIH, nSize); 

			// 步骤3　读取图象数据
			LPBYTE	m_pBits = (LPBYTE) new BYTE[m_pBMIH->biSizeImage];
			nCount = psf->Read(m_pBits, m_pBMIH->biSizeImage); 

			//写入到DAT
			pwFile.SeekToEnd();
			pwFile.Write(pszFace,128);
			// 进行写操作
			pwFile.Write((LPVOID) &bmfh, sizeof(BITMAPFILEHEADER));
			pwFile.Write((LPVOID) m_pBMIH,  nSize);
			pwFile.Write((LPVOID) m_pBits, m_pBMIH->biSizeImage);

			m_HeadCS.Lock();
			ImgFileList.push_back(pszFace);
			m_HeadCS.Unlock();
		}
		
		Sleep(1);
	}
	return 0;

}

//构造函数
CUserFaceRes::CUserFaceRes(void)
{
	//加载资源
	HINSTANCE hInstancle=GetModuleHandle(GAMECLIENTLOBBY_EXPORTS_NAME);
	
	//设置变量
	m_NormalSize.SetSize(NOR_FACE_WIDTH,NOR_FACE_HEIGHT);
	m_SmallSize.SetSize(LIT_FACE_WIDTH,LIT_FACE_HEIGHT);
	ImgFileList.clear();
	TempFileList.clear();

	CString DATFile=TEXT("FaceImage.DAT");

	CFileFind	finder;
	BOOL	FF;
	BOOL    bHaveBmp=FALSE;

	FF=finder.FindFile(DATFile);
	if(!FF){
		return;
	}

	CFile pFile;
	pFile.Open(DATFile,CFile::modeRead);

	char FileNum[10];
	pFile.Read(FileNum,9);
	long NUM = atol(FileNum);

	for(long j=0;j<NUM;j++){	

		BITMAPFILEHEADER bmfh;

		// 步骤1　读取文件头
		char filename[128];
		pFile.Read(filename,127);

		int nCount = pFile.Read((LPVOID) &bmfh, sizeof(BITMAPFILEHEADER));

		// 判断是否是BMP格式的位图
		if(bmfh.bfType != BMP_HEADER_MARKER) 
		{
			continue;
		}

		// 计算信息头加上调色板的大小并分内存
		int nSize = bmfh.bfOffBits - sizeof(BITMAPFILEHEADER);
		LPBITMAPINFOHEADER m_pBMIH = (LPBITMAPINFOHEADER) new BYTE[nSize];

		// 步骤2　读取信息头和调色板
		nCount = pFile.Read(m_pBMIH, nSize); 

		// 步骤3　读取图象数据
		LPBYTE	m_pBits = (LPBYTE) new BYTE[m_pBMIH->biSizeImage];
		nCount = pFile.Read(m_pBits, m_pBMIH->biSizeImage); 

		ImgFileList.push_back(filename);
		delete m_pBits;
		delete m_pBMIH;
	}
	pFile.Close();
	m_hDrawDib  = DrawDibOpen();
	return;
}

//析构函数
CUserFaceRes::~CUserFaceRes(void)
{
}

//接口查询
void * __cdecl CUserFaceRes::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IUserFaceRes,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IUserFaceRes,Guid,dwQueryVer);
	return NULL;
}
//绘画头像
void __cdecl CUserFaceRes::DrawFace(CDC * pDC, int nXPos, int nYPos, int xSize, int ySize, LPCTSTR pszFace, int cbGender)
{
	m_HeadCS.Lock();
	int n=count(ImgFileList.begin(), ImgFileList.end(), pszFace);
	if (n<1)
	{
		int tn=count(TempFileList.begin(), TempFileList.end(), pszFace);
		if (tn<1 && strcmp(pszFace,"NoBmp")!=0)
		{

			TempFileList.push_back(pszFace);
		}
		m_HeadCS.Unlock();
		char ImgFile[128];
		if (cbGender==0)
		{
			sprintf(ImgFile,"PublicRes/male.bmp");
		}
		else
		{
			sprintf(ImgFile,"PublicRes/female.bmp");
		}
		CFile pFile;
		pFile.Open(ImgFile,CFile::modeRead);

		BITMAPFILEHEADER bmfh;

		// 步骤1　读取文件头

		int nCount = pFile.Read((LPVOID) &bmfh, sizeof(BITMAPFILEHEADER));

		// 判断是否是BMP格式的位图
		if(bmfh.bfType != BMP_HEADER_MARKER) 
		{
			return;
		}

		// 计算信息头加上调色板的大小并分内存
		int nSize = bmfh.bfOffBits - sizeof(BITMAPFILEHEADER);
		LPBITMAPINFOHEADER m_pBMIH = (LPBITMAPINFOHEADER) new BYTE[nSize];

		// 步骤2　读取信息头和调色板
		nCount = pFile.Read(m_pBMIH, nSize); 

		// 步骤3　读取图象数据
		LPBYTE	m_pBits = (LPBYTE) new BYTE[m_pBMIH->biSizeImage];
		nCount = pFile.Read(m_pBits, m_pBMIH->biSizeImage); 

		int PaletteSize = 0;

		if(m_pBMIH->biClrUsed == 0) 	// 调色板的大小为2的biBitCount次方		
		{
			switch(m_pBMIH->biBitCount)
			{
			case 1:
				PaletteSize = 2;
				break;
			case 4:
				PaletteSize = 16;
				break;
			case 8:
				PaletteSize = 256;
				break;
			case 16:
			case 24:
			case 32:
				PaletteSize = 0;
				break;
			default:
				PaletteSize = 0;
			}
		}	
		else // 调色板的大小为实际用到的颜色数
		{
			PaletteSize = m_pBMIH->biClrUsed;
		}

		LPLOGPALETTE pLogPal = (LPLOGPALETTE) new char[2 * sizeof(WORD) 
			+ PaletteSize * sizeof(PALETTEENTRY)];

		// 设置逻辑调色板的信息
		pLogPal->palVersion = 	0x300;
		pLogPal->palNumEntries = PaletteSize;

		// 拷贝DIB中的颜色表到逻辑调色板
		LPRGBQUAD pDibQuad = (LPRGBQUAD) (LPVOID) (m_pBMIH + sizeof(BITMAPINFOHEADER));
		for(int i = 0; i < PaletteSize; ++i) 
		{
			pLogPal->palPalEntry[i].peRed = pDibQuad->rgbRed;
			pLogPal->palPalEntry[i].peGreen = pDibQuad->rgbGreen;
			pLogPal->palPalEntry[i].peBlue = pDibQuad->rgbBlue;
			pLogPal->palPalEntry[i].peFlags = 0;
			pDibQuad++;
		}

		HPALETTE            m_hPalette;			//调色板句柄	

		// 如果使用调色板，则将调色板选入设备上下文
		m_hPalette = ::CreatePalette(pLogPal);

		::SelectPalette(pDC->GetSafeHdc(), m_hPalette, TRUE);

		// 设置显示模式
		pDC->SetStretchBltMode(COLORONCOLOR);

		// 在设备的ptOrigin位置上画出大小为szImage的图象
		::StretchDIBits(pDC->GetSafeHdc(), 
			nXPos, nYPos,			//起始点
			xSize,ySize,			//长和宽
			0, 0, 
			m_pBMIH->biWidth, m_pBMIH->biHeight,
			m_pBits, (LPBITMAPINFO) m_pBMIH, 
			DIB_RGB_COLORS, SRCCOPY);
		delete m_pBits;
		delete m_pBMIH;
		pFile.Close();
		return;
	}

	m_HeadCS.Unlock();
	CString DATFile=TEXT("FaceImage.DAT");

	CFileFind	finder;
	BOOL	FF;
	BOOL    bHaveBmp=FALSE;

	FF=finder.FindFile(DATFile);
	if(!FF){
		return;
	}

	CFile pFile;
	pFile.Open(DATFile,CFile::modeRead);

	char FileNum[10];
	pFile.Read(FileNum,9);
	long NUM = atol(FileNum);
	for(long j=0;j<NUM;j++){	

		BITMAPFILEHEADER bmfh;

		// 步骤1　读取文件头
		char filename[128];
		pFile.Read(filename,127);

		int nCount = pFile.Read((LPVOID) &bmfh, sizeof(BITMAPFILEHEADER));

		// 判断是否是BMP格式的位图
		if(bmfh.bfType != BMP_HEADER_MARKER) 
		{
			continue;
		}

		// 计算信息头加上调色板的大小并分内存
		int nSize = bmfh.bfOffBits - sizeof(BITMAPFILEHEADER);
		LPBITMAPINFOHEADER m_pBMIH = (LPBITMAPINFOHEADER) new BYTE[nSize];

		// 步骤2　读取信息头和调色板
		nCount = pFile.Read(m_pBMIH, nSize); 

		// 步骤3　读取图象数据
		LPBYTE	m_pBits = (LPBYTE) new BYTE[m_pBMIH->biSizeImage];
		nCount = pFile.Read(m_pBits, m_pBMIH->biSizeImage); 

		if (strcmp(filename,pszFace)==0)
		{

			int PaletteSize = 0;

			if(m_pBMIH->biClrUsed == 0) 	// 调色板的大小为2的biBitCount次方		
			{
				switch(m_pBMIH->biBitCount)
				{
				case 1:
					PaletteSize = 2;
					break;
				case 4:
					PaletteSize = 16;
					break;
				case 8:
					PaletteSize = 256;
					break;
				case 16:
				case 24:
				case 32:
					PaletteSize = 0;
					break;
				default:
					PaletteSize = 0;
				}
			}	
			else // 调色板的大小为实际用到的颜色数
			{
				PaletteSize = m_pBMIH->biClrUsed;
			}

			LPLOGPALETTE pLogPal = (LPLOGPALETTE) new char[2 * sizeof(WORD) 
				+ PaletteSize * sizeof(PALETTEENTRY)];

			// 设置逻辑调色板的信息
			pLogPal->palVersion = 	0x300;
			pLogPal->palNumEntries = PaletteSize;

			// 拷贝DIB中的颜色表到逻辑调色板
			LPRGBQUAD pDibQuad = (LPRGBQUAD) (LPVOID) (m_pBMIH + sizeof(BITMAPINFOHEADER));
			for(int i = 0; i < PaletteSize; ++i) 
			{
				pLogPal->palPalEntry[i].peRed = pDibQuad->rgbRed;
				pLogPal->palPalEntry[i].peGreen = pDibQuad->rgbGreen;
				pLogPal->palPalEntry[i].peBlue = pDibQuad->rgbBlue;
				pLogPal->palPalEntry[i].peFlags = 0;
				pDibQuad++;
			}

			HPALETTE            m_hPalette;			//调色板句柄	

			// 如果使用调色板，则将调色板选入设备上下文
			m_hPalette = ::CreatePalette(pLogPal);

			::SelectPalette(pDC->GetSafeHdc(), m_hPalette, TRUE);

			// 设置显示模式
			pDC->SetStretchBltMode(COLORONCOLOR);

			// 在设备的ptOrigin位置上画出大小为szImage的图象
			::StretchDIBits(pDC->GetSafeHdc(), 
				nXPos, nYPos,			//起始点
				xSize,ySize,			//长和宽
				0, 0, 
				m_pBMIH->biWidth, m_pBMIH->biHeight,
				m_pBits, (LPBITMAPINFO) m_pBMIH, 
				DIB_RGB_COLORS, SRCCOPY);
			delete m_pBits;
			delete m_pBMIH;
			bHaveBmp = TRUE;
			break;
		}
		delete m_pBits;
		delete m_pBMIH;

	}
	pFile.Close();
	return;
}
//绘画头像
void __cdecl CUserFaceRes::DrawSmallFace(CDC * pDC, int nXPos, int nYPos, LPCTSTR pszFace, int cbGender)
{
	m_HeadCS.Lock();
	int n=count(ImgFileList.begin(), ImgFileList.end(), pszFace);
	if (n<1)
	{
		int tn=count(TempFileList.begin(), TempFileList.end(), pszFace);
		if (tn<1 && strcmp(pszFace,"NoBmp")!=0)
		{
			
			TempFileList.push_back(pszFace);
		}
		m_HeadCS.Unlock();
		char ImgFile[128];
		if (cbGender==0)
		{
			sprintf(ImgFile,"PublicRes/male.bmp");
		}
		else
		{
			sprintf(ImgFile,"PublicRes/female.bmp");
		}
		CFile pFile;
		pFile.Open(ImgFile,CFile::modeRead);

		BITMAPFILEHEADER bmfh;

		// 步骤1　读取文件头

		int nCount = pFile.Read((LPVOID) &bmfh, sizeof(BITMAPFILEHEADER));

		// 判断是否是BMP格式的位图
		if(bmfh.bfType != BMP_HEADER_MARKER) 
		{
			return;
		}

		// 计算信息头加上调色板的大小并分内存
		int nSize = bmfh.bfOffBits - sizeof(BITMAPFILEHEADER);
		LPBITMAPINFOHEADER m_pBMIH = (LPBITMAPINFOHEADER) new BYTE[nSize];

		// 步骤2　读取信息头和调色板
		nCount = pFile.Read(m_pBMIH, nSize); 

		// 步骤3　读取图象数据
		LPBYTE	m_pBits = (LPBYTE) new BYTE[m_pBMIH->biSizeImage];
		nCount = pFile.Read(m_pBits, m_pBMIH->biSizeImage); 

		int PaletteSize = 0;

		if(m_pBMIH->biClrUsed == 0) 	// 调色板的大小为2的biBitCount次方		
		{
			switch(m_pBMIH->biBitCount)
			{
			case 1:
				PaletteSize = 2;
				break;
			case 4:
				PaletteSize = 16;
				break;
			case 8:
				PaletteSize = 256;
				break;
			case 16:
			case 24:
			case 32:
				PaletteSize = 0;
				break;
			default:
				PaletteSize = 0;
			}
		}	
		else // 调色板的大小为实际用到的颜色数
		{
			PaletteSize = m_pBMIH->biClrUsed;
		}

		LPLOGPALETTE pLogPal = (LPLOGPALETTE) new char[2 * sizeof(WORD) 
			+ PaletteSize * sizeof(PALETTEENTRY)];

		// 设置逻辑调色板的信息
		pLogPal->palVersion = 	0x300;
		pLogPal->palNumEntries = PaletteSize;

		// 拷贝DIB中的颜色表到逻辑调色板
		LPRGBQUAD pDibQuad = (LPRGBQUAD) (LPVOID) (m_pBMIH + sizeof(BITMAPINFOHEADER));
		for(int i = 0; i < PaletteSize; ++i) 
		{
			pLogPal->palPalEntry[i].peRed = pDibQuad->rgbRed;
			pLogPal->palPalEntry[i].peGreen = pDibQuad->rgbGreen;
			pLogPal->palPalEntry[i].peBlue = pDibQuad->rgbBlue;
			pLogPal->palPalEntry[i].peFlags = 0;
			pDibQuad++;
		}

		HPALETTE            m_hPalette;			//调色板句柄	

		// 如果使用调色板，则将调色板选入设备上下文
		m_hPalette = ::CreatePalette(pLogPal);

		::SelectPalette(pDC->GetSafeHdc(), m_hPalette, TRUE);

		// 设置显示模式
		pDC->SetStretchBltMode(COLORONCOLOR);

		// 在设备的ptOrigin位置上画出大小为szImage的图象
		::StretchDIBits(pDC->GetSafeHdc(), 
			nXPos, nYPos,			//起始点
			m_SmallSize.cx,m_SmallSize.cy,			//长和宽
			0, 0, 
			m_pBMIH->biWidth, m_pBMIH->biHeight,
			m_pBits, (LPBITMAPINFO) m_pBMIH, 
			DIB_RGB_COLORS, SRCCOPY);
		delete m_pBits;
		delete m_pBMIH;
		pFile.Close();
		return;
	}

	m_HeadCS.Unlock();
	CString DATFile=TEXT("FaceImage.DAT");

	CFileFind	finder;
	BOOL	FF;
	BOOL    bHaveBmp=FALSE;
	FF=finder.FindFile(DATFile);
	if(!FF){
		return;
	}

	CFile pFile;
	pFile.Open(DATFile,CFile::modeRead);

	char FileNum[10];
	pFile.Read(FileNum,9);
	long NUM = atol(FileNum);
	for(long j=0;j<NUM;j++){	

		BITMAPFILEHEADER bmfh;

		// 步骤1　读取文件头
		char filename[128];
		pFile.Read(filename,127);

		int nCount = pFile.Read((LPVOID) &bmfh, sizeof(BITMAPFILEHEADER));

		// 判断是否是BMP格式的位图
		if(bmfh.bfType != BMP_HEADER_MARKER) 
		{
			continue;
		}

		// 计算信息头加上调色板的大小并分内存
		int nSize = bmfh.bfOffBits - sizeof(BITMAPFILEHEADER);
		LPBITMAPINFOHEADER m_pBMIH = (LPBITMAPINFOHEADER) new BYTE[nSize];

		// 步骤2　读取信息头和调色板
		nCount = pFile.Read(m_pBMIH, nSize); 

		// 步骤3　读取图象数据
		LPBYTE	m_pBits = (LPBYTE) new BYTE[m_pBMIH->biSizeImage];
		nCount = pFile.Read(m_pBits, m_pBMIH->biSizeImage); 

		if (strcmp(filename,pszFace)==0)
		{

			int PaletteSize = 0;

			if(m_pBMIH->biClrUsed == 0) 	// 调色板的大小为2的biBitCount次方		
			{
				switch(m_pBMIH->biBitCount)
				{
				case 1:
					PaletteSize = 2;
					break;
				case 4:
					PaletteSize = 16;
					break;
				case 8:
					PaletteSize = 256;
					break;
				case 16:
				case 24:
				case 32:
					PaletteSize = 0;
					break;
				default:
					PaletteSize = 0;
				}
			}	
			else // 调色板的大小为实际用到的颜色数
			{
				PaletteSize = m_pBMIH->biClrUsed;
			}

			LPLOGPALETTE pLogPal = (LPLOGPALETTE) new char[2 * sizeof(WORD) 
				+ PaletteSize * sizeof(PALETTEENTRY)];

			// 设置逻辑调色板的信息
			pLogPal->palVersion = 	0x300;
			pLogPal->palNumEntries = PaletteSize;

			// 拷贝DIB中的颜色表到逻辑调色板
			LPRGBQUAD pDibQuad = (LPRGBQUAD) (LPVOID) (m_pBMIH + sizeof(BITMAPINFOHEADER));
			for(int i = 0; i < PaletteSize; ++i) 
			{
				pLogPal->palPalEntry[i].peRed = pDibQuad->rgbRed;
				pLogPal->palPalEntry[i].peGreen = pDibQuad->rgbGreen;
				pLogPal->palPalEntry[i].peBlue = pDibQuad->rgbBlue;
				pLogPal->palPalEntry[i].peFlags = 0;
				pDibQuad++;
			}

			HPALETTE            m_hPalette;			//调色板句柄	

			// 如果使用调色板，则将调色板选入设备上下文
			m_hPalette = ::CreatePalette(pLogPal);

			::SelectPalette(pDC->GetSafeHdc(), m_hPalette, TRUE);

			// 设置显示模式
			pDC->SetStretchBltMode(COLORONCOLOR);

			// 在设备的ptOrigin位置上画出大小为szImage的图象
			::StretchDIBits(pDC->GetSafeHdc(), 
				nXPos, nYPos,			//起始点
				m_SmallSize.cx,m_SmallSize.cy,			//长和宽
				0, 0, 
				m_pBMIH->biWidth, m_pBMIH->biHeight,
				m_pBits, (LPBITMAPINFO) m_pBMIH, 
				DIB_RGB_COLORS, SRCCOPY);
			delete m_pBits;
			delete m_pBMIH;
			bHaveBmp = TRUE;
			break;
		}
		delete m_pBits;
		delete m_pBMIH;

	}
	pFile.Close();
	return;
}

//绘画头像
void __cdecl CUserFaceRes::DrawNormalFace(CDC * pDC, int nXPos, int nYPos, LPCTSTR pszFace, int cbGender)
{
	m_HeadCS.Lock();
	int n=count(ImgFileList.begin(), ImgFileList.end(), pszFace);
	if (n<1)
	{
		int tn=count(TempFileList.begin(), TempFileList.end(), pszFace);
		if (tn<1 && strcmp(pszFace,"NoBmp")!=0)
		{
			TempFileList.push_back(pszFace);
		}
		m_HeadCS.Unlock();
		char ImgFile[128];
		if (cbGender==0)
		{
			sprintf(ImgFile,"PublicRes/male.bmp");
		}
		else
		{
			sprintf(ImgFile,"PublicRes/female.bmp");
		}
		CFile pFile;
		pFile.Open(ImgFile,CFile::modeReadWrite| CFile::typeBinary);

		BITMAPFILEHEADER bmfh;

		// 步骤1　读取文件头

		int nCount = pFile.Read((LPVOID) &bmfh, sizeof(BITMAPFILEHEADER));

		// 判断是否是BMP格式的位图
		if(bmfh.bfType != BMP_HEADER_MARKER) 
		{
			return;
		}

		// 计算信息头加上调色板的大小并分内存
		int nSize = bmfh.bfOffBits - sizeof(BITMAPFILEHEADER);
		LPBITMAPINFOHEADER m_pBMIH = (LPBITMAPINFOHEADER) new BYTE[nSize];

		// 步骤2　读取信息头和调色板
		nCount = pFile.Read(m_pBMIH, nSize); 

		// 步骤3　读取图象数据
		LPBYTE	m_pBits = (LPBYTE) new BYTE[m_pBMIH->biSizeImage];
		nCount = pFile.Read(m_pBits, m_pBMIH->biSizeImage); 
		pFile.Close();
		
		::StretchDIBits(pDC->GetSafeHdc(),
			nXPos,nYPos,
			m_NormalSize.cx,m_NormalSize.cy,
			0,0,
			m_pBMIH->biWidth,m_pBMIH->biHeight,
			m_pBits,(LPBITMAPINFO) m_pBMIH,
			DIB_RGB_COLORS,SRCCOPY);

		delete m_pBits;
		delete m_pBMIH;
		
		return;
	}

	m_HeadCS.Unlock();
	CString DATFile=TEXT("FaceImage.DAT");

	CFileFind	finder;
	BOOL	FF;
	BOOL    bHaveBmp=FALSE;

	FF=finder.FindFile(DATFile);
	if(!FF){
		return;
	}

	CFile pFile;
	pFile.Open(DATFile,CFile::modeRead);

	char FileNum[10];
	pFile.Read(FileNum,9);
	long NUM = atol(FileNum);
	for(long j=0;j<NUM;j++){	

		BITMAPFILEHEADER bmfh;

		// 步骤1　读取文件头
		char filename[128];
		pFile.Read(filename,127);

		int nCount = pFile.Read((LPVOID) &bmfh, sizeof(BITMAPFILEHEADER));

		// 判断是否是BMP格式的位图
		if(bmfh.bfType != BMP_HEADER_MARKER) 
		{
			continue;
		}

		// 计算信息头加上调色板的大小并分内存
		int nSize = bmfh.bfOffBits - sizeof(BITMAPFILEHEADER);
		LPBITMAPINFOHEADER m_pBMIH = (LPBITMAPINFOHEADER) new BYTE[nSize];

		// 步骤2　读取信息头和调色板
		nCount = pFile.Read(m_pBMIH, nSize); 

		// 步骤3　读取图象数据
		LPBYTE	m_pBits = (LPBYTE) new BYTE[m_pBMIH->biSizeImage];
		nCount = pFile.Read(m_pBits, m_pBMIH->biSizeImage); 

		if (strcmp(filename,pszFace)==0)
		{

			int PaletteSize = 0;

			if(m_pBMIH->biClrUsed == 0) 	// 调色板的大小为2的biBitCount次方		
			{
				switch(m_pBMIH->biBitCount)
				{
				case 1:
					PaletteSize = 2;
					break;
				case 4:
					PaletteSize = 16;
					break;
				case 8:
					PaletteSize = 256;
					break;
				case 16:
				case 24:
				case 32:
					PaletteSize = 0;
					break;
				default:
					PaletteSize = 0;
				}
			}	
			else // 调色板的大小为实际用到的颜色数
			{
				PaletteSize = m_pBMIH->biClrUsed;
			}

			LPLOGPALETTE pLogPal = (LPLOGPALETTE) new char[2 * sizeof(WORD) 
				+ PaletteSize * sizeof(PALETTEENTRY)];

			// 设置逻辑调色板的信息
			pLogPal->palVersion = 	0x300;
			pLogPal->palNumEntries = PaletteSize;

			// 拷贝DIB中的颜色表到逻辑调色板
			LPRGBQUAD pDibQuad = (LPRGBQUAD) (LPVOID) (m_pBMIH + sizeof(BITMAPINFOHEADER));
			for(int i = 0; i < PaletteSize; ++i) 
			{
				pLogPal->palPalEntry[i].peRed = pDibQuad->rgbRed;
				pLogPal->palPalEntry[i].peGreen = pDibQuad->rgbGreen;
				pLogPal->palPalEntry[i].peBlue = pDibQuad->rgbBlue;
				pLogPal->palPalEntry[i].peFlags = 0;
				pDibQuad++;
			}

			HPALETTE            m_hPalette;			//调色板句柄	

			// 如果使用调色板，则将调色板选入设备上下文
			m_hPalette = ::CreatePalette(pLogPal);

			::SelectPalette(pDC->GetSafeHdc(), m_hPalette, TRUE);

			// 设置显示模式
			pDC->SetStretchBltMode(COLORONCOLOR);

			// 在设备的ptOrigin位置上画出大小为szImage的图象
			::StretchDIBits(pDC->GetSafeHdc(), 
				nXPos, nYPos,			//起始点
				m_NormalSize.cx,m_NormalSize.cy,			//长和宽
				0, 0, 
				m_pBMIH->biWidth, m_pBMIH->biHeight,
				m_pBits, (LPBITMAPINFO) m_pBMIH, 
				DIB_RGB_COLORS, SRCCOPY);
			delete m_pBits;
			delete m_pBMIH;
			bHaveBmp = TRUE;
			break;
		}
		delete m_pBits;
		delete m_pBMIH;

	}
	pFile.Close();
	return;
}


//透明绘画
bool CUserFaceRes::AlphaDrawImage(CDC * pDestDC, int xDest, int yDest, int cxDest, int cyDest, CDC * pScrDC, int xSrc, int ySrc)
{
	//效验参数
	ASSERT(pScrDC!=NULL);
	ASSERT(pDestDC!=NULL);

	//建立 DC
	pScrDC->SetBkColor(COLOR_TRANS);
	pScrDC->SetBkMode(TRANSPARENT);

	//建立掩码图
	CDC DCMask;
	CBitmap BMPMask;
	BMPMask.CreateBitmap(cxDest,cyDest,1,1,NULL);
	DCMask.CreateCompatibleDC(pDestDC);
	DCMask.SelectObject(&BMPMask);
	DCMask.BitBlt(0,0,cxDest,cyDest,pScrDC,xSrc,ySrc,SRCCOPY);

	//绘画目标图
	CDC DCDest;
	CBitmap BMPDest;
	DCDest.CreateCompatibleDC(pDestDC);
	BMPDest.CreateCompatibleBitmap(pDestDC,cxDest,cyDest);
	DCDest.SelectObject(&BMPDest);
	DCDest.BitBlt(0,0,cxDest,cyDest,pDestDC,xDest,yDest,SRCCOPY);
	DCDest.BitBlt(0,0,cxDest,cyDest,pScrDC,xSrc,ySrc,SRCINVERT);
	DCDest.BitBlt(0,0,cxDest,cyDest,&DCMask,0,0,SRCAND);
	DCDest.BitBlt(0,0,cxDest,cyDest,pScrDC,xSrc,ySrc,SRCINVERT);
	pDestDC->BitBlt(xDest,yDest,cxDest,cyDest,&DCDest,0,0,SRCCOPY);

	//清理资源
	DCMask.DeleteDC();
	DCDest.DeleteDC();
	BMPMask.DeleteObject();
	BMPDest.DeleteObject();

	return true;
}
//////////////////////////////////////////////////////////////////////////

//建立对象函数
extern "C" __declspec(dllexport) void * __cdecl CreateUserFaceRes(const GUID & Guid, DWORD dwInterfaceVer)
{
	//建立对象
	CUserFaceRes * pUserFaceRes=NULL;
	try
	{
		pUserFaceRes=new CUserFaceRes();
		if (pUserFaceRes==NULL) throw TEXT("创建失败");
		void * pObject=pUserFaceRes->QueryInterface(Guid,dwInterfaceVer);
		AfxBeginThread(DownLoad,NULL);
		if (pObject==NULL) throw TEXT("接口查询失败");
		return pObject;
	}
	catch (...) {}

	//清理对象
	SafeDelete(pUserFaceRes);
	return NULL;
}

//////////////////////////////////////////////////////////////////////////
