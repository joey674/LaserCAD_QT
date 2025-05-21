#if !defined(AFX_GALVOSETTINGS_H__5FD94C31_2552_414E_9C4C_E085E12470EC__INCLUDED_)
#define AFX_GALVOSETTINGS_H__5FD94C31_2552_414E_9C4C_E085E12470EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GalvoSettings.h : header file
//
#include "resource.h"
#include "defs.h"
#include "Scanner.h"

/////////////////////////////////////////////////////////////////////////////
// CGalvoSettings dialog

class CScanner;

class AFX_EXT_CLASS CGalvoSettings : public CDialog
{
// Construction
public:
	void AddCorFiles(LPCTSTR Sourcepath);
	void AddCorFiles();

	CGalvoSettings(CWnd* pParent = NULL);   // standard constructor
 
 	CString filepath;
 	CString strAutoControlScale;

	DriverCard m_CardType;
	CScanner* m_Scanner;
	HICON hIcon_red,hIcon_green;

	void OnApply();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGalvoSettings)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGalvoSettings)
	virtual BOOL OnInitDialog();
	afx_msg void OnTypertc4();
	afx_msg void OnTypertc5();
	afx_msg void OnTypertc6();
	afx_msg void OnTypepmc2();
	afx_msg void OnOpencor();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnLoadAutoScaleFile();
	afx_msg void OnOpenpowercurve();
	afx_msg void OnShowpowercurve();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GALVOSETTINGS_H__5FD94C31_2552_414E_9C4C_E085E12470EC__INCLUDED_)
