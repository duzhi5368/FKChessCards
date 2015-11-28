#pragma once

#define DEFAULT_INT_VALUE		0						//缺省整数值
#define DEFAULT_STRING_VALUE	"Default string"		//缺省字符串值

class CIniFile
{
public:
	CIniFile(void){}
	~CIniFile(void){}

	__inline bool Open( LPCTSTR szIniFile, bool bFullPath = false );			//打开一个ini
	__inline bool Create( LPCTSTR szIniFile, bool bFullPath = false );		//创建一个ini

	__inline DWORD GetStringValue( LPCTSTR szSection, LPCTSTR szKey, LPTSTR pszValue, DWORD dwSize, LPCTSTR pszDefault = DEFAULT_STRING_VALUE );
	__inline DWORD PutStringValue( LPCTSTR szSection, LPCTSTR szKey, LPCTSTR pszValue );

	__inline UINT GetIntValue( LPCTSTR szSection, LPCTSTR szKey, INT nDefault = DEFAULT_INT_VALUE );
	__inline void PutIntValue( LPCTSTR szSection, LPCTSTR szKey, UINT nValue );

	__inline float GetFloatValue( LPCTSTR szSection, LPCTSTR szKey, float fDefault = 0.f );
	__inline void PutFloatValue( LPCTSTR szSection, LPCTSTR szKey, float fValue );

protected:
	TCHAR m_szIniFile[MAX_PATH];	//路径

private:
	CIniFile( const CIniFile &object );
	CIniFile &operator= ( const CIniFile &object );
};

__inline bool CIniFile::Open( LPCTSTR szIniFile, bool bFullPath )
{
	ZeroMemory( m_szIniFile, sizeof( m_szIniFile ) );
	if( !bFullPath )
	{
		GetCurrentDirectory( sizeof( m_szIniFile ), m_szIniFile );
		strcat( m_szIniFile, "\\" );
	}

	strcat( m_szIniFile, szIniFile );

	WIN32_FIND_DATA finddate;
	HANDLE hFile = NULL;
	hFile = FindFirstFile( m_szIniFile, &finddate );
	if( hFile== INVALID_HANDLE_VALUE )
	{
		return false;
	}

	return true;
}

__inline bool CIniFile::Create( LPCTSTR szIniFile, bool bFullPath )
{
	ZeroMemory( m_szIniFile, sizeof( m_szIniFile ) );
	if( !bFullPath )
	{
		GetCurrentDirectory (sizeof( m_szIniFile ), m_szIniFile );
		strcat( m_szIniFile, "\\" );
	}

	strcat( m_szIniFile, szIniFile );

	HANDLE hFile = CreateFile( m_szIniFile, 
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL );

	if( hFile == INVALID_HANDLE_VALUE )
	{
		return false;
	}

	CloseHandle( hFile );
	return true;
}

__inline DWORD CIniFile::GetStringValue( LPCTSTR szSection, LPCTSTR szKey, LPTSTR pszValue, DWORD dwSize, LPCTSTR pszDefault )
{
	return GetPrivateProfileString( szSection, szKey, pszDefault, pszValue, dwSize, m_szIniFile );
}

__inline DWORD CIniFile::PutStringValue( LPCTSTR szSection, LPCTSTR szKey, LPCTSTR pszValue )
{
	return WritePrivateProfileString( szSection, szKey, pszValue, m_szIniFile );
}

__inline UINT CIniFile::GetIntValue( LPCTSTR szSection, LPCTSTR szKey, INT nDefault )
{
	return GetPrivateProfileInt( szSection, szKey, nDefault, m_szIniFile );
}

__inline void CIniFile::PutIntValue( LPCTSTR szSection, LPCTSTR szKey, UINT nValue )
{
	TCHAR szString[20] = { 0 };

	sprintf( szString, "%d", nValue );

	WritePrivateProfileString( szSection, szKey, szString, m_szIniFile );
}

__inline float CIniFile::GetFloatValue( LPCTSTR szSection, LPCTSTR szKey, float fDefault /* = 0.f */ )
{
	TCHAR szString[20] = { 0 };
	float fValue = fDefault;
	DWORD dwRet = GetPrivateProfileString( szSection, szKey, "0", szString, sizeof( szString ), m_szIniFile );	
	sscanf( szString, "%f", &fValue );
	return fValue;
}

__inline void CIniFile::PutFloatValue( LPCTSTR szSection, LPCTSTR szKey, float fValue )
{
	TCHAR szString[20] = { 0 };
	sprintf( szString, "%f", fValue );
	WritePrivateProfileString( szSection, szKey, szString, m_szIniFile );
}
