#if !defined(AFX_TESTZ_H__0BF5A891_D3F9_49DC_8706_101A42E5E700__INCLUDED_)
#define AFX_TESTZ_H__0BF5A891_D3F9_49DC_8706_101A42E5E700__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestZ.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestZ dialog
class CTestZ : public CDialog
{
// Construction
public:
	CTestZ(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTestZ)
	enum { IDD = IDD_DIALOG_ZCALIBRATION };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestZ)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTestZ)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTZ_H__0BF5A891_D3F9_49DC_8706_101A42E5E700__INCLUDED_)
