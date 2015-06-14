/* 
filename: 
utf8.h 
summary: 
convert between LPTSTR and UTF8 string 

v1.0 
lichiyang 2008.03 

usage: 
//  sample code 
USES_CONVERSION;    //defined in atlconv.h 
LPCTSTR lpszSomeText = TEXT("河北CA"); 
LPSTR putf8 = T2UTF8(lpszSomeText); 

v2.0 
lichiyang 2010.12 
增加CW2UTF8/CUTF82W 2个类，用法同CW2A和CA2W 
CW2UTF8 utf8(L"中国的英文是China"); 
CUTF82W w("/xe4/xb8/xad/xe5/x9b/xbd/xe7/x9a/x84/xe8/x8b/xb1/xe6/x96/x87/xe6/x98/xaf/x43/x68/x69/x6e/x61"); 


// 
*/  

#ifndef _UTF8_CONVERT_H_  
#define _UTF8_CONVERT_H_  

//#include <atlconv.h>  

#define W2UTF8(lpw) (\
		((_lpw = lpw) == NULL) ? NULL : (\
		_convert = (lstrlenW(_lpw)+1)*3,\
		ATLW2AHELPER((LPSTR) alloca(_convert), _lpw, _convert, CP_UTF8)))

#define UTF82W(lpu) (\
				((_lpa = lpu) == NULL) ? NULL : (\
				_convert = (lstrlenA(_lpa)+1),\
				 ATLA2WHELPER((LPWSTR) alloca(_convert*2), _lpa, _convert, CP_UTF8)))

#define A2UTF8(lpa) W2UTF8(A2W(lpa))
#define UTF82A(lpu) W2T(UTF82W(lpu))



#if  defined (UNICODE) || defined (_UNICODE)
#define T2UTF8 W2UTF8
#define UTF82T UTF82W
#else
#define T2UTF8 A2UTF8
#define UTF82T UTF82A
#endif  


template< int t_nBufferLength = 128 >
class CUTF82WEX  
{  
public:  
	CUTF82WEX( LPCSTR psz ) throw(...) :  
	  m_psz( m_szBuffer )  
	  {  
		  Init( psz, CP_UTF8 );  
	  }  
	  CUTF82WEX( LPCSTR psz, UINT nCodePage ) throw(...) :  
	  m_psz( m_szBuffer )  
	  {  
		  Init( psz, nCodePage );  
	  }  
	  ~CUTF82WEX() throw()  
	  {  
		  if( m_psz != m_szBuffer )  
		  {  
			  free( m_psz );  
		  }  
	  }  

	  operator LPWSTR() const throw()  
	  {  
		  return( m_psz );  
	  }  

private:  
	void Init( LPCSTR psz, UINT nCodePage ) throw(...)  
	{  
		if (psz == NULL)  
		{  
			m_psz = NULL;  
			return;  
		}  
		int nLengthA = lstrlenA( psz )+1;  
		int nLengthW = nLengthA;  

		if( nLengthW > t_nBufferLength )  
		{  
			m_psz = static_cast< LPWSTR >( malloc( nLengthW*sizeof( wchar_t ) ) );  
			if (m_psz == NULL)  
			{  
				AtlThrow( E_OUTOFMEMORY );  
			}  
		}  

		if (::MultiByteToWideChar( nCodePage, 0, psz, nLengthA, m_psz, nLengthW ) == 0)  
		{  
			AtlThrowLastWin32();  
		}  
	}  

public:  
	LPWSTR m_psz;  
	wchar_t m_szBuffer[t_nBufferLength];  

private:  
	CUTF82WEX( const CUTF82WEX& ) throw();  
	CUTF82WEX& operator=( const CUTF82WEX& ) throw();  
};  
typedef CUTF82WEX<> CUTF82W;  


template< int t_nBufferLength = 128 >  
class CW2UTF8EX  
{  
public:  
	CW2UTF8EX( LPCWSTR psz ) throw(...) :  
	  m_psz( m_szBuffer )  
	  {  
		  Init( psz, CP_UTF8 );  
	  }  
	  CW2UTF8EX( LPCWSTR psz, UINT nCodePage ) throw(...) :  
	  m_psz( m_szBuffer )  
	  {  
		  Init( psz, nCodePage );  
	  }  
	  ~CW2UTF8EX() throw()  
	  {  
		  if( m_psz != m_szBuffer )  
		  {  
			  free( m_psz );  
		  }  
	  }  

	  operator LPSTR() const throw()  
	  {  
		  return( m_psz );  
	  }  

private:  
	void Init( LPCWSTR psz, UINT nCodePage ) throw(...)  
	{  
		if (psz == NULL)  
		{  
			m_psz = NULL;  
			return;  
		}  
		int nLengthW = lstrlenW( psz )+1;  
		int nLengthA = nLengthW*3;  

		if( nLengthA > t_nBufferLength )  
		{  
			m_psz = static_cast< LPSTR >( malloc( nLengthA*sizeof( char ) ) );  
			if (m_psz == NULL)  
			{  
				AtlThrow( E_OUTOFMEMORY );  
			}  
		}  

		if (::WideCharToMultiByte( nCodePage, 0, psz, nLengthW, m_psz, nLengthA, NULL, NULL ) == 0)  
		{  
			AtlThrowLastWin32();  
		}  
	}  

public:  
	LPSTR m_psz;  
	char m_szBuffer[t_nBufferLength];  

private:  
	CW2UTF8EX( const CW2UTF8EX& ) throw();  
	CW2UTF8EX& operator=( const CW2UTF8EX& ) throw();  
};  
typedef CW2UTF8EX<> CW2UTF8;  


#endif //_UTF8_CONVERT_H_  