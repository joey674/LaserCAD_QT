///////////////////////////////////////////////////////////////////////////////
//! 
//! 
//! \file		IniFile.h
//! 
//! \brief		Allow easy access to an ini file for multiple datatypes
//! 
//! \author		ABS GmbH Jena (HBau)
//! 
//! \date		5.4.2006 \n
//! 			 -> erstellt \n
//! 
///////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_INIFILE_H__012A8565_549D_4B6D_A371_BE005E5C771C__INCLUDED_)
#define AFX_INIFILE_H__012A8565_549D_4B6D_A371_BE005E5C771C__INCLUDED_

// --------------------- Defines ----------------------------------------------
//
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef HRESULT  (CALLBACK* LPSHGetFolderPath)(HWND,int,HANDLE,DWORD,LPTSTR);


// ----------------------------------------------------------------------------
//
//! \brief Allow easy access to an ini file for multiple datatypes
//!
class AFX_EXT_CLASS CIniFile 
{
public:

	//! constructor
	CIniFile();
	//! destructor
	virtual ~CIniFile();

	//! \brief Read/Write an STRING value to/from the ini file
	//! \param cszSection	ini file section
	//! \param cszName		element name at section
	//! \param cszValue		value to read/write
	//! \param bWrite		if TRUE value will be written to the ini file
	//!						if FALSE value will be read from the ini file
	//!	\retval				TRUE if succuessfull
	//!	\retval				FALSE if failed

	//BOOL	Update( CString cszSection, CString cszName, BOOL& cszValue, BOOL bWrite);

	BOOL	Update( CString cszSection, CString cszName, CString& cszValue, BOOL bWrite);

	//! \brief Read/Write an LONG value to/from the ini file
	//! \param cszSection	ini file section
	//! \param cszName		element name at section
	//! \param nValue		value to read/write
	//! \param bWrite		if TRUE value will be written to the ini file
	//!						if FALSE value will be read from the ini file
	//!	\retval				TRUE if succuessfull
	//!	\retval				FALSE if failed
	BOOL	Update( CString cszSection, CString cszName, long& nValue, BOOL bWrite);

	//! \brief Read/Write an INTEGER value to/from the ini file
	//! \param cszSection	ini file section
	//! \param cszName		element name at section
	//! \param nValue		value to read/write
	//! \param bWrite		if TRUE value will be written to the ini file
	//!						if FALSE value will be read from the ini file
	//!	\retval				TRUE if succuessfull
	//!	\retval				FALSE if failed
	BOOL	Update( CString cszSection, CString cszName, int& nValue, BOOL bWrite);

	//! \brief Read/Write an SHORT value to/from the ini file
	//! \param cszSection	ini file section
	//! \param cszName		element name at section
	//! \param nValue		value to read/write
	//! \param bWrite		if TRUE value will be written to the ini file
	//!						if FALSE value will be read from the ini file
	//!	\retval				TRUE if succuessfull
	//!	\retval				FALSE if failed
	BOOL	Update( CString cszSection, CString cszName, SHORT& nValue, BOOL bWrite);

	//! \brief Read/Write an DOUBLE WORD value to/from the ini file
	//! \param cszSection	ini file section
	//! \param cszName		element name at section
	//! \param dwValue		value to read/write
	//! \param bWrite		if TRUE value will be written to the ini file
	//!						if FALSE value will be read from the ini file
	//!	\retval				TRUE if succuessfull
	//!	\retval				FALSE if failed
	BOOL	Update( CString cszSection, CString cszName, DWORD& dwValue, BOOL bWrite);

	//! \brief Read/Write an UINT value to/from the ini file
	//! \param cszSection	ini file section
	//! \param cszName		element name at section
	//! \param dwValue		value to read/write
	//! \param bWrite		if TRUE value will be written to the ini file
	//!						if FALSE value will be read from the ini file
	//!	\retval				TRUE if succuessfull
	//!	\retval				FALSE if failed
	BOOL	Update( CString cszSection, CString cszName, UINT& dwValue, BOOL bWrite);

	//! \brief Read/Write an WORD value to/from the ini file
	//! \param cszSection	ini file section
	//! \param cszName		element name at section
	//! \param wValue		value to read/write
	//! \param bWrite		if TRUE value will be written to the ini file
	//!						if FALSE value will be read from the ini file
	//!	\retval				TRUE if succuessfull
	//!	\retval				FALSE if failed
	BOOL	Update( CString cszSection, CString cszName, WORD& wValue, BOOL bWrite);

	//! \brief Read/Write an BYTE value to/from the ini file
	//! \param cszSection	ini file section
	//! \param cszName		element name at section
	//! \param nValue		value to read/write
	//! \param bWrite		if TRUE value will be written to the ini file
	//!						if FALSE value will be read from the ini file
	//!	\retval				TRUE if succuessfull
	//!	\retval				FALSE if failed
	BOOL	Update( CString cszSection, CString cszName, BYTE& nValue, BOOL bWrite);

	//! \brief Read/Write an DOUBLE value to/from the ini file
	//! \param cszSection	ini file section
	//! \param cszName		element name at section
	//! \param fValue		value to read/write
	//! \param bWrite		if TRUE value will be written to the ini file
	//!						if FALSE value will be read from the ini file
	//!	\retval				TRUE if succuessfull
	//!	\retval				FALSE if failed
	BOOL	Update( CString cszSection, CString cszName, double& fValue, BOOL bWrite);

	//! \brief Read/Write an FLOAT value to/from the ini file
	//! \param cszSection	ini file section
	//! \param cszName		element name at section
	//! \param fValue		value to read/write
	//! \param bWrite		if TRUE value will be written to the ini file
	//!						if FALSE value will be read from the ini file
	//!	\retval				TRUE if succuessfull
	//!	\retval				FALSE if failed
	BOOL	Update( CString cszSection, CString cszName, float& fValue, BOOL bWrite);

	//! \brief Read/Write an FLOAT array to/from the ini file
	//! \param cszSection	ini file section
	//! \param cszName		element name at section
	//! \param pfArray		pointer to the array to read/write
	//! \param dwElements	Count array elements
	//! \param bWrite		if TRUE value will be written to the ini file
	//!						if FALSE value will be read from the ini file
	//!	\retval				TRUE if succuessfull
	//!	\retval				FALSE if failed
	BOOL	UpdateArray( CString cszSection, CString cszName, 
						 float *pfArray, DWORD dwElements, BOOL bWrite);

    //! \brief Read/Write an WORD array to/from the ini file
	//! \param cszSection	ini file section
	//! \param cszName		element name at section
	//! \param pwArray		pointer to the array to read/write
	//! \param dwElements	Count array elements
	//! \param bWrite		if TRUE value will be written to the ini file
	//!						if FALSE value will be read from the ini file
	//!	\retval				TRUE if succuessfull
	//!	\retval				FALSE if failed
    BOOL    UpdateArray( CString cszSection, CString cszName, 
						 WORD *pwArray, DWORD dwElements, BOOL bWrite);

	//! \brief Read/Write an INI-File section
	//! \param cszSection	ini file section	
	//! \param cszValue		value to read/write	
	//! \param bWrite		if TRUE value will be written to the ini file
	//!						if FALSE value will be read from the ini file
	//!	\retval				TRUE if succuessfull
	//!	\retval				FALSE if failed
	BOOL	UpdateSection( CString cszSection, CString &cszValue, BOOL bWrite);

	//! \brief Get all Sectionnames
	//! \param cszSectionNameList	list of available sections
	//!	\retval				TRUE if succuessfull
	//!	\retval				FALSE if failed
	BOOL	GetSectionNames( CStringList &cszSectionNameList);


	//! \brief Set the ini file name and path, if this function isn't called
	//! \brief the application path and name + ".ini" will be used
	//! \param cszIniFileName name and path of the ini file
	//!
	void		SetIniFile( CString cszIniFileName );

	//! \brief Get the ini file name and path
	//! \retval name and path of the ini file
	//!
	CString		GetIniFile( void ) {return m_cszIniFile;};

	//! \brief Perform a check if the file exist. (see SetIniFile)
	//!
	BOOL		IsFileExisting(void);

	//! \brief Perform a check if the file hast write access. (see SetIniFile)
	//!
	BOOL		IsFileWriteAccess(void);

	//! \brief Perform a check if the file path exist. (see SetIniFile)
	//!
	BOOL		IsPathExisting(void);

protected:

			
	// Extern imported Functions
    HINSTANCE					m_hShell32;
    LPSHGetFolderPath           fnSHGetFolderPath;
	void    ImportFunctions( BOOL bImport );
	
	//! \brief Read/Write an FLOAT array to/from the ini file
	//! \param cszSection	ini file section
	//! \param cszName		element name at section
	//! \param pfArray		pointer to the array to read/write
	//! \param dwElements	Count array elements
	//! \param bWrite		if TRUE value will be written to the ini file
	//!						if FALSE value will be read from the ini file
	//!	\retval				TRUE if succuessfull
	//!	\retval				FALSE if failed
	BOOL	UpdateArray( CString cszSection, CString cszName, 
						 PVOID pArray, DWORD dwSize, BOOL bWrite);
	
	//! \brief Returns the application path and name
	//! \retval string with the application path and name
	//!
	void		InitIniFilePath( void );

	CString		m_cszIniFile;		//!< ini filename and path
};

#endif // !defined(AFX_INIFILE_H__012A8565_549D_4B6D_A371_BE005E5C771C__INCLUDED_)


