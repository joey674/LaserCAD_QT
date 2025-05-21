// ZCalibrationDlg.cpp : implementation file
//
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "stdafx.h"
#include "ZCalibrationDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CZCalibrationDlg dialog

CZCalibrationDlg::CZCalibrationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZCalibrationDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZCalibrationDlg)
	m_gotox = 0.0;
	m_gotoy = 0.0;
	m_gotoz = 0.0;
	m_getl = 0.0;
	m_getx = 0.0;
	m_gety = 0.0;
	m_loada = 0.0;
	m_loadb = 0.0;
	m_loadc = 0.0;
	//}}AFX_DATA_INIT
}

void CZCalibrationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZCalibrationDlg)
	DDX_Text(pDX, IDC_EDITGOTOX, m_gotox);
	DDX_Text(pDX, IDC_EDITGOTOY, m_gotoy);
	DDX_Text(pDX, IDC_EDITGOTOZ, m_gotoz);
	DDX_Text(pDX, IDC_EDITGETL, m_getl);
	DDX_Text(pDX, IDC_EDITGETX, m_getx);
	DDX_Text(pDX, IDC_EDITGETY, m_gety);
	DDX_Text(pDX, IDC_EDITZTABLEA, m_loada);
	DDX_Text(pDX, IDC_EDITZTABLEB, m_loadb);
	DDX_Text(pDX, IDC_EDITZTABLEC, m_loadc);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CZCalibrationDlg, CDialog)
	//{{AFX_MSG_MAP(CZCalibrationDlg)
	ON_BN_CLICKED(IDC_LOADTABLE, OnLoadtable)
	ON_BN_CLICKED(IDC_GETL, OnGetl)
	ON_BN_CLICKED(IDC_BUTTONGOTO, OnButtongoto)
	ON_EN_KILLFOCUS(IDC_EDITGOTOX, OnKillfocusEditgotox)
	ON_EN_KILLFOCUS(IDC_EDITGOTOY, OnKillfocusEditgotoy)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZCalibrationDlg message handlers

void CZCalibrationDlg::OnLoadtable() 
{
	UpdateData(TRUE);
	int errorcode=m_Scanner->m_RTC.load_z_table(m_loada, m_loadb, m_loadc);

	switch(errorcode)
	{
	case 0:
		return;
	case 4:
		AfxMessageBox("Verify error!");
		break;
	case 8:
		AfxMessageBox("System driver not found, or locked by another application!");
		break;
	case 10:
		AfxMessageBox("Parameter error!");
		break;
	case 11:
		AfxMessageBox("RTC not found!");
		break;
	case 12:
		AfxMessageBox("3D option not enabled!");
		break;
	}
}

void CZCalibrationDlg::OnGetl() 
{
	m_getl=m_Scanner->m_RTC.get_z_distance(m_gotox, m_gotoy, m_gotoz);
	UpdateData(FALSE);
}

void CZCalibrationDlg::OnButtongoto() 
{
	UpdateData(TRUE);
	m_Scanner->m_RTC.goto_xyz(m_gotox,m_gotoy,m_gotoz);
}


void CZCalibrationDlg::OnKillfocusEditgotox() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_getx=m_gotox;
	UpdateData(FALSE);
}

void CZCalibrationDlg::OnKillfocusEditgotoy() 
{
	UpdateData(TRUE);
	m_gety=m_gotoy;
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
	
}

void CZCalibrationDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CZCalibrationDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CZCalibrationDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if(m_Scanner!=NULL)
	{
		m_loada=m_Scanner->m_GalvoPara.m_zA;
		m_loadb=m_Scanner->m_GalvoPara.m_zB;
		m_loadc=m_Scanner->m_GalvoPara.m_zC;

		UpdateData(FALSE);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CZCalibrationDlg::OnClose() 
{
	CDialog::OnClose();
}

BOOL CZCalibrationDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN)
	{	
		switch(pMsg->wParam)
		{
		case VK_ESCAPE:
			return TRUE;		
		case VK_RETURN:	
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}
