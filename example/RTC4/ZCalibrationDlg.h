#if !defined(AFX_ZCALIBRATIONDLG_H__9C6D9E79_B73E_406F_8F89_CD70829A7FFB__INCLUDED_)
#define AFX_ZCALIBRATIONDLG_H__9C6D9E79_B73E_406F_8F89_CD70829A7FFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZCalibrationDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CZCalibrationDlg dialog



#include "Scanner.h"

class CScanner;

class AFX_CLASS_EXPORT CZCalibrationDlg : public CDialog
{
// Construction
public:
	CZCalibrationDlg(CWnd* pParent = NULL);   // standard constructor
	CScanner* m_Scanner;

// Dialog Data
	//{{AFX_DATA(CZCalibrationDlg)
	enum { IDD = IDD_DIALOG_ZCALIBRATION };
	double	m_gotox;
	double	m_gotoy;
	double	m_gotoz;
	double	m_getl;
	double	m_getx;
	double	m_gety;
	double	m_loada;
	double	m_loadb;
	double	m_loadc;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZCalibrationDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CZCalibrationDlg)
	afx_msg void OnLoadtable();
	afx_msg void OnGetl();
	afx_msg void OnButtongoto();
 	afx_msg void OnKillfocusEditgotox();
 	afx_msg void OnKillfocusEditgotoy();
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZCALIBRATIONDLG_H__9C6D9E79_B73E_406F_8F89_CD70829A7FFB__INCLUDED_)
