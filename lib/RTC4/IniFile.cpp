///////////////////////////////////////////////////////////////////////////////
//! 
//! 
//! \file		IniFile.cpp
//! 
//! \brief		Allow easy access to an ini file for multiple datatypes
//! 
//! \author		ABS GmbH Jena (HBau)
//! 
//! \date		5.4.2006 \n
//! 			 -> erstellt \n
//! 
///////////////////////////////////////////////////////////////////////////////

// --------------------- Includes ---------------------------------------------
//
#include "stdafx.h"
#include "IniFile.h"
#include "defs.h"
// --------------------- Defines ----------------------------------------------
//
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
//
// ----------------------------------------------------------------------------
//
CIniFile::CIniFile()
{
	// Extern imported Functions
    m_hShell32 = NULL;
    fnSHGetFolderPath = NULL;
	InitIniFilePath();
}
//
// ----------------------------------------------------------------------------
//
CIniFile::~CIniFile()
{
	ImportFunctions( FALSE );
}
//
// ----------------------------------------------------------------------------
//
BOOL CIniFile::Update( CString cszSection, CString cszName, 
					   CString& cszValue, BOOL bWrite)
{
	BOOL bRC;
	DWORD dwCntChar = 0;

	if(bWrite)
	{
		bRC = WritePrivateProfileString( cszSection, cszName, 
										 cszValue, m_cszIniFile ); 
	}
	else // read
	{
		cszValue.Empty();
		dwCntChar = GetPrivateProfileString( cszSection, cszName, "",
										     cszValue.GetBufferSetLength(MAX_PATH), 
											 MAX_PATH,
											 m_cszIniFile ); 
		cszValue.ReleaseBuffer();
        if (dwCntChar == (MAX_PATH-1))
        {
            dwCntChar = GetPrivateProfileString( cszSection, cszName, "",
										     cszValue.GetBufferSetLength(64*1024), 
											 64*1024,
											 m_cszIniFile ); 
            cszValue.ReleaseBuffer();
        }

		if ( cszValue.IsEmpty() ||			// nothing returned
			 (dwCntChar == 0) ||			// entry not found
			 (dwCntChar == (MAX_PATH-1)) || // entry bigger than buffer
             (dwCntChar == (64*1024-1)) )
		{
			bRC = FALSE;
		}
		else bRC = TRUE;
	}
	return bRC;
}
//
// ----------------------------------------------------------------------------
//
// BOOL CIniFile::	Update( CString cszSection, CString cszName, BOOL& cszValue, BOOL bWrite)
// {
// 	BOOL bRC;
// 	CString cstrValue;
// 	
// 	if (bWrite) 
// 	{
// 		if(cszValue)
// 			cstrValue="1";
// 		else 
// 			cstrValue="0";
// 	}
// 	bRC = Update( cszSection, cszName, cstrValue, bWrite);	
// 	if (!bWrite) 
// 	{
// 		int nValue = atoi(cszValue);
// 		if(nValue>0)cszValue=true;
// 		else cszValue=false;
// 	}
// 	return bRC;
// }


BOOL CIniFile::Update( CString cszSection, CString cszName, 
					   long& nValue, BOOL bWrite)
{
	BOOL bRC;
	CString cszValue;
	
	if (bWrite) cszValue.Format("%d", nValue);
	bRC = Update( cszSection, cszName, cszValue, bWrite);
	if (!bWrite) 
	{
		nValue = atoi(cszValue);
	}
	return bRC;
}
//
// ----------------------------------------------------------------------------
//
BOOL CIniFile::Update( CString cszSection, CString cszName, 
					   int& nValue, BOOL bWrite)
{
	BOOL bRC;
	CString cszValue;
	
	if (bWrite) cszValue.Format("%d", nValue);
	bRC = Update( cszSection, cszName, cszValue, bWrite);
	if (!bWrite) 
	{
		nValue = atoi(cszValue);
	}
	return bRC;
}
//
// ----------------------------------------------------------------------------
//
BOOL CIniFile::Update( CString cszSection, CString cszName, 
					   SHORT& nValue, BOOL bWrite)
{
	BOOL bRC;
	CString cszValue;
	
	if (bWrite) cszValue.Format("%d", nValue);
	bRC = Update( cszSection, cszName, cszValue, bWrite);
	if (!bWrite) 
	{
		nValue = (SHORT)atoi(cszValue);
	}
	return bRC;
}
//
// ----------------------------------------------------------------------------
//
BOOL CIniFile::Update( CString cszSection, CString cszName, 
					   DWORD& dwValue, BOOL bWrite)
{
	BOOL bRC;
	CString cszValue;
	
	if (bWrite) cszValue.Format("%d", dwValue);
	bRC = Update( cszSection, cszName, cszValue, bWrite);
	if (!bWrite) 
	{
		dwValue = atol(cszValue);
	}
	return bRC;
}
//
// ----------------------------------------------------------------------------
//
BOOL CIniFile::Update( CString cszSection, CString cszName, 
					   UINT& dwValue, BOOL bWrite)
{
	BOOL bRC;
	CString cszValue;
	
	if (bWrite) cszValue.Format("%d", dwValue);
	bRC = Update( cszSection, cszName, cszValue, bWrite);
	if (!bWrite) 
	{
		dwValue = atol(cszValue);
	}
	return bRC;
}
//
// ----------------------------------------------------------------------------
//
BOOL CIniFile::Update( CString cszSection, CString cszName, 
					   WORD& wValue, BOOL bWrite)
{
	BOOL bRC;
	CString cszValue;
	
	if (bWrite) cszValue.Format("%d", wValue);
	bRC = Update( cszSection, cszName, cszValue, bWrite);
	if (!bWrite) 
	{
		wValue = (WORD)atol(cszValue);
	}
	return bRC;
}
//
// ----------------------------------------------------------------------------
//
BOOL CIniFile::Update( CString cszSection, CString cszName, 
					   BYTE& nValue, BOOL bWrite)
{
	BOOL bRC;
	CString cszValue;
	
	if (bWrite) cszValue.Format("%d", nValue);
	bRC = Update( cszSection, cszName, cszValue, bWrite);
	if (!bWrite) 
	{
		nValue = (BYTE)atol(cszValue);
	}
	return bRC;
}
//
// ----------------------------------------------------------------------------
//
BOOL CIniFile::Update( CString cszSection, CString cszName, 
					   double& fValue, BOOL bWrite)
{
	BOOL bRC;
	CString cszValue;
	
	if (bWrite) cszValue.Format("%f", fValue);
	bRC = Update( cszSection, cszName, cszValue, bWrite);
	if (!bWrite) 
	{
		fValue = atof(cszValue);
	}
	return bRC;
}
//
// ----------------------------------------------------------------------------
//
BOOL CIniFile::Update( CString cszSection, CString cszName, 
					   float& fValue, BOOL bWrite)
{
	BOOL bRC;
	CString cszValue;
	
	if (bWrite) cszValue.Format("%f", fValue);
	bRC = Update( cszSection, cszName, cszValue, bWrite);
	if (!bWrite) 
	{
		fValue = (float) atof(cszValue);
	}
	return bRC;
}
//
// ----------------------------------------------------------------------------
//
BOOL CIniFile::UpdateArray( CString cszSection, CString cszName, 
						 PVOID pArray, DWORD dwSize, BOOL bWrite)
{
	BOOL bRC;
	

	if ( ( (!bWrite) && IsBadReadPtr(pArray, dwSize)) ||
		 ( (bWrite) && IsBadWritePtr(pArray, dwSize)) )
		 return FALSE;


	if(bWrite)
	{
		bRC = WritePrivateProfileStruct( cszSection, cszName, 
										 pArray, dwSize, m_cszIniFile ); 
	}
	else // read
	{		
		ZeroMemory( pArray, dwSize);
		bRC = GetPrivateProfileStruct( cszSection, cszName, 
											 pArray, dwSize,
											 m_cszIniFile ); 		
	}
	return bRC;
}
//
// ----------------------------------------------------------------------------
//
BOOL CIniFile::UpdateArray( CString cszSection, CString cszName, 
						    float *pfArray, DWORD dwElements, BOOL bWrite)
{
	BOOL bRC;

	bRC = UpdateArray( cszSection, 
					   cszName, 
					   (PVOID) pfArray, 
					   dwElements*sizeof(float), 
					   bWrite); 
	return bRC;

}
//
// ----------------------------------------------------------------------------
//
BOOL CIniFile::UpdateArray( CString cszSection, CString cszName, 
						    WORD *pwArray, DWORD dwElements, BOOL bWrite)
{
	BOOL bRC;

	bRC = UpdateArray( cszSection, 
					   cszName, 
					   (PVOID) pwArray, 
					   dwElements*sizeof(WORD), 
					   bWrite); 
	return bRC;

}
//
// ----------------------------------------------------------------------------
//
BOOL CIniFile::UpdateSection( CString cszSection, CString &cszValue, BOOL bWrite)
{
	BOOL	bRC;
	DWORD	dwSize;

	if(bWrite)
	{
		bRC = WritePrivateProfileSection( cszSection, cszValue, m_cszIniFile ); 
	}
	else // read
	{		
		cszValue.Empty();
		char* pBuf;
		pBuf = cszValue.GetBufferSetLength(30*1024);
		dwSize = GetPrivateProfileSection( cszSection, 
								 pBuf, 
								 30*1024,
								 m_cszIniFile ); 
		
		// wandele das NULL-Zeichen in einen Zeilenumbruch um
		for (DWORD n=0; n<dwSize; n++)
		{
			if (pBuf[n] == '\0') 
				pBuf[n] = '\n';		
		}
		
		cszValue.ReleaseBuffer();
		
		bRC = (dwSize!=0);
	}
	return bRC;
}
//
// ----------------------------------------------------------------------------
//
BOOL CIniFile::GetSectionNames( CStringList &cszSectionNameList)
{
	DWORD dwSize = 1024*1024;
	char *szSectionNames;
	char *szPos, *szFind;

	cszSectionNameList.RemoveAll();

	szSectionNames = (char*) new char[ dwSize ];

	if ( szSectionNames != NULL)
	{
		ZeroMemory(szSectionNames, dwSize);
		GetPrivateProfileSectionNames(szSectionNames, dwSize, m_cszIniFile);

		szPos = szSectionNames;
		while (true)
		{
			if ((szPos[0] == '\0') && (szPos[1] == '\0')) break;
			if (szPos[0] == '\0') szPos++;
			szFind = strchr(szPos, '\0');
			if (szFind != NULL)
			{
				CString cszTmp;
				cszTmp = CString(szPos, szFind-szPos );
				cszSectionNameList.AddTail( cszTmp );
				szPos = szFind;
			}
		}

	}
	SAFE_DELETE_ARRAY(szSectionNames);
	return (cszSectionNameList.GetCount() > 0);
}
//
// ----------------------------------------------------------------------------
//
void CIniFile::SetIniFile( CString cszIniFileName )
{
	m_cszIniFile = cszIniFileName;
}
//
// ----------------------------------------------------------------------------
//
BOOL CIniFile::IsFileExisting(void)
{
	BOOL bResult;
	HANDLE hFile = CreateFile(	m_cszIniFile, 
								GENERIC_READ, 
								FILE_SHARE_READ, 
								NULL, 
								OPEN_EXISTING, 
								FILE_ATTRIBUTE_NORMAL, 
								NULL );

	DWORD dwRC = GetLastError();

	bResult = (hFile != INVALID_HANDLE_VALUE);

	SAFE_CLOSEHANDLE(hFile);

	return bResult;
}
//
// ----------------------------------------------------------------------------
//
BOOL CIniFile::IsFileWriteAccess(void)
{
	BOOL			bResult;
	HANDLE			hFile;

    if (!IsFileExisting())
    {
        hFile = CreateFile(	m_cszIniFile, 
						    GENERIC_READ | GENERIC_WRITE, 
						    FILE_SHARE_READ, 
						    NULL, 
						    OPEN_ALWAYS, 
						    FILE_ATTRIBUTE_NORMAL, 
						    NULL );

    }
    else
    {
	    hFile = CreateFile(	m_cszIniFile, 
						    GENERIC_READ | GENERIC_WRITE, 
						    FILE_SHARE_READ, 
						    NULL, 
						    OPEN_EXISTING, 
						    FILE_ATTRIBUTE_NORMAL, 
						    NULL );
    }

	DWORD dwRC = GetLastError();

	// if file succesfully opened
	bResult = (hFile != INVALID_HANDLE_VALUE);

	SAFE_CLOSEHANDLE(hFile);
	
	// on error return error with failure	
	return bResult;
}
//
// ----------------------------------------------------------------------------
//
BOOL CIniFile::IsPathExisting(void)
{
	char szCurrentPath[10*MAX_PATH + 1];
	BOOL bResult;
	BOOL bSetOldPath;
	CString cszPath;
	int  nIndex;

	ZeroMemory( szCurrentPath, CNT_ELEMENTS(szCurrentPath) );

	nIndex = m_cszIniFile.ReverseFind('\\');
	if (nIndex == -1) return TRUE;

	cszPath = m_cszIniFile.Left( nIndex );

	bSetOldPath = (GetCurrentDirectory(10*MAX_PATH, szCurrentPath) != 0);

	bResult = SetCurrentDirectory(cszPath);

	if (bSetOldPath) SetCurrentDirectory(szCurrentPath);

	return bResult;
}
//
// ----------------------------------------------------------------------------
//
void CIniFile::InitIniFilePath( void )
{
	CString cszAppPath, cszAppName, cszCommonAppPath;
	int nPos;

   ::GetModuleFileName(NULL, cszAppPath.GetBufferSetLength(MAX_PATH) , MAX_PATH);
   cszAppPath.ReleaseBuffer();

   nPos = cszAppPath.ReverseFind('\\');

   // invalid path
   if (nPos == -1) return;

   // the "\" char don't belong to the filename
   nPos++;

   cszAppName = cszAppPath.Right( cszAppPath.GetLength() - nPos);
   cszAppPath = cszAppPath.Left(nPos);

   nPos = cszAppName.ReverseFind('.');   
   cszAppName = cszAppName.Left(nPos);
   
   m_cszIniFile = cszAppPath + cszAppName + ".ini";

   if (!IsFileWriteAccess())
   {
       ImportFunctions(TRUE);

       if (fnSHGetFolderPath)
       {    
            #define SHGFP_TYPE_CURRENT              0x0000        // current value for user, verify it exists
            #define CSIDL_COMMON_APPDATA            0x0023        // All Users\Application Data
            // get the common application path an set it as default ini path
           if (S_OK == fnSHGetFolderPath( NULL, CSIDL_COMMON_APPDATA, NULL, SHGFP_TYPE_CURRENT, cszCommonAppPath.GetBufferSetLength(MAX_PATH)))
           {
               cszCommonAppPath.ReleaseBuffer();      
                               
               // set new path which should be access able
               m_cszIniFile = cszCommonAppPath + "\\" + cszAppName + "\\" + cszAppName + ".ini";

               if (!IsPathExisting())
                   CreateDirectory(cszCommonAppPath + "\\" + cszAppName, NULL);
           }
           else cszCommonAppPath.ReleaseBuffer();      
       }
   }
}
//
// ----------------------------------------------------------------------------
//
void CIniFile::ImportFunctions(BOOL bImport)
{
	if (bImport)
	{	

        if (m_hShell32 == NULL)
        {   
            m_hShell32 = LoadLibrary( "Shell32.dll");
        }

        if (m_hShell32 != NULL)
        {   
            fnSHGetFolderPath = (LPSHGetFolderPath) GetProcAddress( m_hShell32, "SHGetFolderPathA" );
        }
	}
	else
	{
        fnSHGetFolderPath = NULL;

        if (m_hShell32 != NULL)	
			FreeLibrary(m_hShell32);
	}
}
//
// ----------------------------------------------------------------------------
//
