#if !defined(AFX_CGALVOCARDSETTING_H__BF6BE5E7_5F2E_4875_B64A_86418509A977__INCLUDED_)
#define AFX_CGALVOCARDSETTING_H__BF6BE5E7_5F2E_4875_B64A_86418509A977__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CGalvoCardSetting.h : header file
//
#include "resource.h"
 #include "Scanner.h"
 #include "RTC4expl.h"
 #include "RTC5expl.h"
 #include "RTC6expl.h"

/////////////////////////////////////////////////////////////////////////////
// CGalvoCardRTC4 dialog
class AFX_EXT_CLASS CGalvoCardRTC4 : public CDialog
{
	// Construction
public:
	void UpdateSetting();
	void Apply();
	CGalvoCardRTC4(UINT DLGID = IDD_GALVO_RTC4, CWnd* pParent = NULL);   // standard constructor
	//CGalvoCardRTC4(CWnd* pParent = NULL);   // standard constructor

	RTC4* m_Scanner;
	// Dialog Data
	//{{AFX_DATA(CGalvoCardRTC4)
	enum { IDD = IDD_GALVO_RTC4 };
	CButton	m_VarCheck;
	CStatic	m_strVarPolyFile;
	CStatic	m_PowerCurve;
	CStatic	m_CorFile;
	CEdit	m_Rotate;
	CEdit	m_Scale;
	CEdit	m_OffsetX;
	CEdit	m_OffsetY;
	CEdit	m_CorX;
	CEdit	m_CorY;
	CEdit	m_iListRunGap;
	CEdit	m_iListLoadGap;
	CComboBox	m_LaserMode;
	//}}AFX_DATA
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGalvoCardRTC4)
public:
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:	
	// Generated message map functions
	//{{AFX_MSG(CGalvoCardRTC4)
	virtual BOOL OnInitDialog();
	virtual void OnCorFileLoad();
	void OnPowerFileLoad();
	void OnVaryPolyDelayFileLoad();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGalvoCardRTC5 dialog
class AFX_EXT_CLASS CGalvoCardRTC5 : public CGalvoCardRTC4
{
	// Construction
public:
	CGalvoCardRTC5(UINT DLGID = IDD_GALVO_RTC5, CWnd* pParent = NULL);   // standard constructor
	RTC5* m_Scanner;
	
	void Apply();
	void UpdateSetting();
	// Dialog Data
	//{{AFX_DATA(CGalvoCardRTC5)
	enum { IDD = IDD_GALVO_RTC5 };
	CButton	m_SignalSyncOut;
	CComboBox	m_LaserSignal;
	CComboBox	m_AdvLaserVector;
	CComboBox	m_AdvLaserSignal;
	CComboBox	m_AdvLaserPos;
	CComboBox	m_AdvLaserMode;
	CEdit	m_AdvLaserMax;
	CEdit	m_AdvLaserMin;
	CEdit	m_AdvLaserFile;
	CEdit	m_AdvLaserPosFile;
	//}}AFX_DATA
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGalvoCardRTC5)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:	
	// Generated message map functions
	//{{AFX_MSG(CGalvoCardRTC5)
	virtual BOOL OnInitDialog();
	virtual void OnCorFileLoad();
	virtual void OnAdvSpeedCheck();
	virtual void OnAdvPosCheck();
	virtual void OnAdvLaserFileLoad();
	virtual void OnAdvPosFileLoad();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CGalvoCardRTC6 : public CGalvoCardRTC5
{
	// Construction
public:
	CGalvoCardRTC6(UINT DLGID = IDD_GALVO_RTC6, CWnd* pParent = NULL);   // standard constructor

	RTC6* m_Scanner;	
	void Apply();
	void UpdateSetting();
		
	// Dialog Data
	//{{AFX_DATA(CGalvoCardRTC6)
	enum { IDD = IDD_GALVO_RTC6 };
	CButton  AutoScanAheadDelay;
	CEdit 	CornerScale;
	CEdit   EndScale;
	CEdit   AccScale;
	CEdit	ScanAheadLaserOn;
	CEdit	ScanAheadLaserOff;
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
		
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGalvoCardRTC6)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CGalvoCardRTC6)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGalvoCardSetting dialog
class AFX_EXT_CLASS CGalvoCardSetting : public CDialog
{
// Construction
public:
	void ShowSettings(DriverCard cardtype);
	CGalvoCardSetting(CWnd* pParent = NULL);   // standard constructor
	
	CGalvoCardRTC6 m_RTC6SetDlg;
	CGalvoCardRTC5 m_RTC5SetDlg;
	CGalvoCardRTC4 m_RTC4SetDlg;

	void LoadPowerCurve();
	CScanner* m_Scanner;
	DriverCard cardtype;

	CRect m_InfoRect;

// Dialog Data
	//{{AFX_DATA(CGalvoCardSetting)
	enum { IDD = IDD_GALVOCARDSETTINGS };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGalvoCardSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGalvoCardSetting)
	afx_msg void OnTypertc4();
	virtual BOOL OnInitDialog();
	afx_msg void OnTypertc5();
	afx_msg void OnTypertc6();
	afx_msg void OnDestroy();
	afx_msg void OnApply();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CGalvoCardRTC6 dialog

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CGALVOCARDSETTING_H__BF6BE5E7_5F2E_4875_B64A_86418509A977__INCLUDED_)
