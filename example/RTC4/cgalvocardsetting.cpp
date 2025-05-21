// CGalvoCardSetting.cpp : implementation file
//
#include "stdafx.h"
#include "CGalvoCardSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CGalvoCardSetting dialog
CGalvoCardSetting::CGalvoCardSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CGalvoCardSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGalvoCardSetting)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_Scanner=NULL;
}

void CGalvoCardSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGalvoCardSetting)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGalvoCardSetting, CDialog)
	//{{AFX_MSG_MAP(CGalvoCardSetting)
	ON_BN_CLICKED(IDC_TYPERTC4, OnTypertc4)
	ON_BN_CLICKED(IDC_TYPERTC5, OnTypertc5)
	ON_BN_CLICKED(IDC_TYPERTC6, OnTypertc6)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_ONAPPLY, OnApply)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGalvoCardSetting message handlers

void CGalvoCardSetting::OnTypertc4() 
{
	cardtype=cardRTC4;
	ShowSettings(cardtype);
}
void CGalvoCardSetting::OnTypertc5() 
{
	cardtype=cardRTC5;
	ShowSettings(cardtype);
}
void CGalvoCardSetting::OnTypertc6() 
{
	cardtype=cardRTC6;
	ShowSettings(cardtype);
}

void CGalvoCardSetting::LoadPowerCurve() 
{
	// TODO: Add your control notification handler code here
	if(m_Scanner==NULL)
		return;
	CString filter=_T("Text File (*.txt)|*.txt||");
	
	CFileDialog	fDlg(TRUE,NULL,NULL,NULL,filter);
	fDlg.m_ofn.lpstrTitle=_T("Load power curve file...");
	
	if(fDlg.DoModal()==IDOK )
	{
		CString filepath;

		m_Scanner->LoadPowerCurve(fDlg.GetPathName());	
		if(m_Scanner->m_powercurvefile.IsEmpty())
			SetDlgItemText(IDC_SCANNER_POWERFILE, "No power curve loaded!");
		else
			SetDlgItemText(IDC_SCANNER_POWERFILE, m_Scanner->m_powercurvefile);	

	}
}

BOOL CGalvoCardSetting::OnInitDialog() 
{
	CRect rect;
	GetClientRect(&rect);	
	rect.DeflateRect(20,100,10, 50);
	
	GetClientRect(m_InfoRect);
	m_InfoRect.DeflateRect(10, 50, 10, 10);
	m_InfoRect.bottom=m_InfoRect.top+40;

	if(m_Scanner==NULL)
		cardtype=cardRTC4;
	else
		cardtype=m_Scanner->GetCardType();

	m_RTC4SetDlg.Create(IDD_GALVO_RTC4, this);
	m_RTC4SetDlg.MoveWindow(rect);
	m_RTC5SetDlg.Create(IDD_GALVO_RTC5, this);
	m_RTC5SetDlg.MoveWindow(rect);
	m_RTC6SetDlg.Create(IDD_GALVO_RTC6, this);
	m_RTC6SetDlg.MoveWindow(rect);

	ShowSettings(cardtype);
	Invalidate();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGalvoCardSetting::ShowSettings(DriverCard cardtype)
{
	CButton* pbtn;
	switch(cardtype)
	{
		case cardRTC4 :	
			pbtn=(CButton*)GetDlgItem(IDC_TYPERTC4);
			pbtn->SetCheck(true);
			m_RTC4SetDlg.m_Scanner=(RTC4*)m_Scanner;
 	 		m_RTC4SetDlg.ShowWindow(SW_SHOW);
			m_RTC4SetDlg.UpdateSetting();
			m_RTC5SetDlg.ShowWindow(SW_HIDE);
			m_RTC6SetDlg.ShowWindow(SW_HIDE);
			break;
		case  cardRTC5:
			pbtn=(CButton*)GetDlgItem(IDC_TYPERTC5);
			pbtn->SetCheck(true);
			m_RTC5SetDlg.m_Scanner=(RTC5*)m_Scanner;
			m_RTC5SetDlg.ShowWindow(SW_SHOW);
 			m_RTC5SetDlg.UpdateSetting();
 			m_RTC4SetDlg.ShowWindow(SW_HIDE);
			m_RTC6SetDlg.ShowWindow(SW_HIDE);
 			break;
		case cardRTC6:
			pbtn=(CButton*)GetDlgItem(IDC_TYPERTC6);
			pbtn->SetCheck(true);
			m_RTC6SetDlg.m_Scanner=(RTC6*)m_Scanner;
			m_RTC6SetDlg.ShowWindow(SW_SHOW);
			m_RTC6SetDlg.UpdateSetting();
			m_RTC4SetDlg.ShowWindow(SW_HIDE);
			m_RTC5SetDlg.ShowWindow(SW_HIDE);
 			break;
		break;
	}
	Invalidate();
}

void CGalvoCardSetting::OnDestroy() 
{
	CDialog::OnDestroy();
}

void CGalvoCardSetting::OnApply() 
{
	switch(cardtype)
	{
		case cardRTC4:
			if(m_Scanner==NULL || cardtype!=m_Scanner->GetCardType())
			{
				delete m_Scanner;
				m_Scanner=new RTC4(NULL);
		 		m_RTC4SetDlg.m_Scanner=(RTC4*)m_Scanner;
			}			
			m_RTC4SetDlg.Apply();
			
			BeginWaitCursor();			
			if(!m_Scanner->InitialRTC())
			{
				delete m_Scanner;
				m_Scanner=NULL;
			}
			EndWaitCursor();
			break;
		case cardRTC5:
			if(m_Scanner==NULL || cardtype!=m_Scanner->GetCardType())
			{
				delete m_Scanner;
				m_Scanner=new RTC5(NULL);
				m_RTC5SetDlg.m_Scanner=(RTC5*)m_Scanner;
			}
			m_RTC5SetDlg.Apply();
			BeginWaitCursor();
			if(!m_Scanner->InitialRTC())
			{
				delete m_Scanner;
				m_Scanner=NULL;
				EndWaitCursor();
				break;
			}
			EndWaitCursor();
			DrawNumber(&m_RTC5SetDlg.m_Scale, m_Scanner->GetScaleFactor(), 1);
			break;
		case cardRTC6:
			if(m_Scanner==NULL || cardtype!=m_Scanner->GetCardType())
			{
				delete m_Scanner;
				m_Scanner=new RTC6(NULL);
				m_RTC6SetDlg.m_Scanner=(RTC6*)m_Scanner;
			}
			m_RTC6SetDlg.Apply();
			BeginWaitCursor();			
			if(!m_Scanner->InitialRTC())
			{
				delete m_Scanner;
				m_Scanner=NULL;
				EndWaitCursor();
				break;
			}
			EndWaitCursor();
			DrawNumber(&m_RTC6SetDlg.m_Scale, m_Scanner->GetScaleFactor(), 1);		
			break;
		default:
			break;	
	}
	Invalidate();
}

// 
BOOL CGalvoCardRTC5::OnInitDialog() 
{
//	CGalvoCardRTC4::m_Scanner=(RTC4*)m_Scanner;
	CGalvoCardRTC4::OnInitDialog();	
	//UpdateSetting();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CGalvoCardRTC5::CGalvoCardRTC5(UINT DLGID, CWnd* pParent /*=NULL*/)
	: CGalvoCardRTC4(DLGID, pParent)
{
	//{{AFX_DATA_INIT(CGalvoCardRTC5)
	//}}AFX_DATA_INIT
	m_Scanner=NULL;

}

void CGalvoCardRTC5::DoDataExchange(CDataExchange* pDX)
{
	CGalvoCardRTC4::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGalvoCardRTC5)
	DDX_Control(pDX, IDC_AUTOSYNCPULSEOUT, m_SignalSyncOut);
	DDX_Control(pDX, IDC_COMBOLASERSIGNALOUT, m_LaserSignal);
	DDX_Control(pDX, IDC_COMBOLASERAUTOSIGNAL, m_AdvLaserSignal);
	DDX_Control(pDX, IDC_AUTOLASERCONTROLMAX, m_AdvLaserMax);
	DDX_Control(pDX, IDC_AUTOLASERCONTROLMIN, m_AdvLaserMin);
	DDX_Control(pDX, IDC_SCANNER_AUTOLASERFILE, m_AdvLaserFile);
	DDX_Control(pDX, IDC_SCANNER_AUTOLASERPOSFILE, m_AdvLaserPosFile);
	//}}AFX_DATA_MAP
}
BEGIN_MESSAGE_MAP(CGalvoCardRTC5, CGalvoCardRTC4)
	//{{AFX_MSG_MAP(CGalvoCardRTC5)
	ON_BN_CLICKED(IDC_AUTOLASERSPEEDCHECK, OnAdvSpeedCheck)
    ON_BN_CLICKED(IDC_AUTOLASERPOSCHECK, OnAdvPosCheck)
	ON_STN_DBLCLK(IDC_SCANNER_AUTOLASERFILE, OnAdvLaserFileLoad)
	ON_STN_DBLCLK(IDC_SCANNER_AUTOLASERPOSFILE, OnAdvPosFileLoad)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGalvoCardRTC5 message handlers
BOOL CGalvoCardRTC4::OnInitDialog() 
{
	CDialog::OnInitDialog();	
//	UpdateSetting();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGalvoCardRTC4::OnCorFileLoad()
{
	CString filepath;
	::GetModuleFileName(NULL, filepath.GetBuffer(MAX_PATH), MAX_PATH);
	filepath.ReleaseBuffer();

	CFileDialog dlg(TRUE,_T("ctb"),_T("*.ctb"),OFN_FILEMUSTEXIST|OFN_HIDEREADONLY,_T("Correct File(*.ctb)|*.ctb|"));
		
	CString str=filepath+"\\Correction Files";
	dlg.m_ofn.lpstrInitialDir=str;
	
	if (dlg.DoModal()==IDOK)
	{
		m_CorFile.SetWindowText(dlg.GetFileName());

		filepath=filepath+"\\Correction Files\\"+ dlg.GetFileName(); 	
		CopyFile(dlg.GetPathName(), filepath,false);

	}
	return;
}

void CGalvoCardRTC5::OnCorFileLoad()
{
	CString filepath;
	::GetModuleFileName(NULL, filepath.GetBuffer(MAX_PATH), MAX_PATH);
	filepath.ReleaseBuffer();

	CFileDialog dlg(TRUE,_T("ct5"),_T("*.ct5"),OFN_FILEMUSTEXIST|OFN_HIDEREADONLY,_T("Correct File(*.ct5)|*.ct5|"));
		
	dlg.m_ofn.lpstrInitialDir=filepath+"\\Correction Files";
	
	if (dlg.DoModal()==IDOK)
	{
		m_CorFile.SetWindowText(dlg.GetFileName());

		filepath=filepath+"\\Correction Files\\"+ dlg.GetFileName(); 	
		CopyFile(dlg.GetPathName(), filepath,false);

	}
	return;
}

void CGalvoCardRTC5::OnAdvLaserFileLoad()
{
	CString filepath;
	::GetModuleFileName(NULL, filepath.GetBuffer(MAX_PATH), MAX_PATH);
	filepath.ReleaseBuffer();
	
	CFileDialog dlg(TRUE,_T("text"),_T("*.txt"),OFN_FILEMUSTEXIST|OFN_HIDEREADONLY,_T("Advanced Laser Control Scale File(*.txt)|*.txt|"));
	
	dlg.m_ofn.lpstrInitialDir=filepath;
	
	if (dlg.DoModal()==IDOK)
	{
		m_AdvLaserFile.SetWindowText(dlg.GetFileName());		
		filepath=filepath+ "\\Advanced Laser Scale File.txt"; 	
		CopyFile(dlg.GetPathName(), filepath,false);		
	}
	return;
}



void CGalvoCardRTC5::OnAdvPosFileLoad()
{
	CString filepath;
	::GetModuleFileName(NULL, filepath.GetBuffer(MAX_PATH), MAX_PATH);
	filepath.ReleaseBuffer();
	
	CFileDialog dlg(TRUE,_T("text"),_T("*.txt"),OFN_FILEMUSTEXIST|OFN_HIDEREADONLY,_T("Advanced Laser Control Position File(*.txt)|*.txt|"));
	
	dlg.m_ofn.lpstrInitialDir=filepath;
	
	if (dlg.DoModal()==IDOK)
	{
		m_AdvLaserPosFile.SetWindowText(dlg.GetFileName());		
		filepath=filepath+ "\\Advanced Laser Position Control Scale.txt"; 	
		CopyFile(dlg.GetPathName(), filepath,false);		
	}
	return;
}



void CGalvoCardRTC4:: OnPowerFileLoad()
{
	CString filepath;
	::GetModuleFileName(NULL, filepath.GetBuffer(MAX_PATH), MAX_PATH);
	filepath.ReleaseBuffer();

	CFileDialog dlg(TRUE,_T("text"),_T("*.txt"),OFN_FILEMUSTEXIST|OFN_HIDEREADONLY,_T("Power Scale File(*.txt)|*.text|"));
	dlg.m_ofn.lpstrInitialDir=filepath;
	
	if (dlg.DoModal()==IDOK)
	{
		m_PowerCurve.SetWindowText(dlg.GetFileName());

		filepath=filepath+"PowerCurve.txt"; 	

		if(!CopyFile(dlg.GetPathName(),filepath,false))
			AfxMessageBox("Copy power file to folder failed!");	
	}
}


void CGalvoCardRTC4:: OnVaryPolyDelayFileLoad()
{
	CString filepath;
	::GetModuleFileName(NULL, filepath.GetBuffer(MAX_PATH), MAX_PATH);
	filepath.ReleaseBuffer();

	CFileDialog dlg(TRUE,_T("dat"),_T("*.dat"),OFN_FILEMUSTEXIST|OFN_HIDEREADONLY,_T("Vary Polygon Delay File(*.dat)|*.dat|"));
	
	dlg.m_ofn.lpstrInitialDir=filepath;
	
	if (dlg.DoModal()==IDOK)
	{
		m_strVarPolyFile.SetWindowText(dlg.GetFileName());
		filepath=filepath+"VaryPolyDelay.txt"; 	
	
		if(!CopyFile(dlg.GetPathName(), filepath,false))
			AfxMessageBox("Copy vary Polygon delay file to folder failed!");	
	}
}


void CGalvoCardRTC5::Apply()
{
	if(m_Scanner==NULL)
		return;

	CGalvoCardRTC4::m_Scanner=m_Scanner;
	CGalvoCardRTC4::Apply();

	m_Scanner->m_LaserSignal=0x24 + m_LaserSignal.GetCurSel();

	CButton* pbtn=(CButton*)GetDlgItem(IDC_AUTOSYNCPULSEOUT);
	m_Scanner->m_bFirstPulseSync=pbtn->GetCheck();

	pbtn=(CButton*)GetDlgItem(IDC_AUTOLASERSPEEDCHECK);
	m_Scanner->m_bSpeedDepend=pbtn->GetCheck();

	pbtn=(CButton*)GetDlgItem(IDC_AUTOLASERPOSCHECK);
	m_Scanner->m_bPositionDepend=pbtn->GetCheck();
		
	m_Scanner->m_iAutoDependCtrl=m_AdvLaserSignal.GetCurSel();

 	m_AdvLaserFile.GetWindowText(m_Scanner->strAutoControlScale);
	m_AdvLaserPosFile.GetWindowText(m_Scanner->strAutoPosScale);
	
	m_Scanner->m_AdvLaserMax=GetNumber(&m_AdvLaserMax);
	m_Scanner->m_AdvLaserMin=GetNumber(&m_AdvLaserMin);
}

void CGalvoCardRTC4::Apply()
{
	if(m_Scanner==NULL)
		return ;
	
	CButton* pbtn=(CButton*)GetDlgItem(IDC_VARPOLYDELAYCHECK);
	m_Scanner->m_bVarPolyDelay=pbtn->GetCheck();

	pbtn=(CButton*)GetDlgItem(IDC_SCANNER_FLIPX);
	m_Scanner->bFlipx=pbtn->GetCheck();
	pbtn=(CButton*)GetDlgItem(IDC_SCANNER_FLIPY);
	m_Scanner->bFlipy=pbtn->GetCheck();

	m_PowerCurve.GetWindowText(m_Scanner->m_powercurvefile);
	m_strVarPolyFile.GetWindowText(m_Scanner->m_varpolyfile);

	m_CorFile.GetWindowText(m_Scanner->m_corfile);

	m_Scanner->m_lasermode= m_LaserMode.GetCurSel();
	
	m_Scanner->m_Scale=GetNumber(&m_Scale);
    m_Scanner->xcor=GetNumber(&m_CorX);
	m_Scanner->ycor=GetNumber(&m_CorY);
	m_Scanner->xoffset=GetNumber(&m_OffsetX);
	m_Scanner->yoffset=GetNumber(&m_OffsetY);
	m_Scanner->xyrotate=GetNumber(&m_Rotate);
	
	m_Scanner->LoadGap=GetNumber(&m_iListLoadGap);
	m_Scanner->RunGap=GetNumber(&m_iListRunGap);
}
void CGalvoCardRTC5::OnAdvSpeedCheck()
{
	CButton* pbtn=(CButton*)GetDlgItem(IDC_AUTOLASERSPEEDCHECK);
	CButton* pbtn1=(CButton*)GetDlgItem(IDC_AUTOLASERPOSCHECK);

	m_AdvLaserSignal.EnableWindow(pbtn->GetCheck() || pbtn1->GetCheck());
	m_AdvLaserFile.EnableWindow(pbtn->GetCheck() || pbtn1->GetCheck());
	m_AdvLaserMin.EnableWindow(pbtn->GetCheck() || pbtn1->GetCheck());
	m_AdvLaserMax.EnableWindow(pbtn->GetCheck() || pbtn1->GetCheck());
}

void CGalvoCardRTC5::OnAdvPosCheck()
{
	CButton* pbtn=(CButton*)GetDlgItem(IDC_AUTOLASERSPEEDCHECK);
	CButton* pbtn1=(CButton*)GetDlgItem(IDC_AUTOLASERPOSCHECK);

	m_AdvLaserSignal.EnableWindow(pbtn->GetCheck() || pbtn1->GetCheck());
	m_AdvLaserFile.EnableWindow(pbtn->GetCheck() || pbtn1->GetCheck());

	m_AdvLaserPosFile.EnableWindow(pbtn1->GetCheck());
	m_AdvLaserMin.EnableWindow(pbtn->GetCheck() || pbtn1->GetCheck());
	m_AdvLaserMax.EnableWindow(pbtn->GetCheck() || pbtn1->GetCheck());
}


void CGalvoCardRTC5::UpdateSetting()
{
	CGalvoCardRTC4::m_Scanner=(RTC4*)m_Scanner;		
	CGalvoCardRTC4::UpdateSetting();	

	if(m_Scanner==NULL)
	{
		m_LaserMode.SetCurSel(0);		
		m_CorFile.SetWindowText("Load Correction File!");
		m_LaserSignal.SetCurSel(0);		

		m_AdvLaserSignal.EnableWindow(false);
		m_AdvLaserMin.EnableWindow(false);
		m_AdvLaserMax.EnableWindow(false);

		return;
	}
	
	m_LaserSignal.SetCurSel(m_Scanner->m_LaserSignal-0x24);
	CButton* pbtn=(CButton*)GetDlgItem(IDC_AUTOLASERSPEEDCHECK);
	pbtn->SetCheck(m_Scanner->m_bSpeedDepend);

	pbtn=(CButton*)GetDlgItem(IDC_AUTOLASERPOSCHECK);
	pbtn->SetCheck(m_Scanner->m_bPositionDepend);
	
	pbtn=(CButton*)GetDlgItem(IDC_AUTOSYNCPULSEOUT);
	pbtn->SetCheck(m_Scanner->m_bFirstPulseSync);

	m_AdvLaserSignal.SetCurSel(m_Scanner->m_iAutoDependCtrl);

	m_AdvLaserFile.SetWindowText(m_Scanner->strAutoControlScale);
	m_AdvLaserPosFile.SetWindowText(m_Scanner->strAutoPosScale);

	m_AdvLaserSignal.EnableWindow(m_Scanner->m_bPositionDepend || m_Scanner->m_bSpeedDepend);
	m_AdvLaserFile.EnableWindow(m_Scanner->m_bPositionDepend || m_Scanner->m_bSpeedDepend);
	m_AdvLaserPosFile.EnableWindow(m_Scanner->m_bPositionDepend);

	DrawNumber(&m_AdvLaserMax, m_Scanner->m_AdvLaserMax,1);
	DrawNumber(&m_AdvLaserMin, m_Scanner->m_AdvLaserMin, 1);

	m_AdvLaserMin.EnableWindow(m_Scanner->m_bPositionDepend || m_Scanner->m_bSpeedDepend);
	m_AdvLaserMax.EnableWindow(m_Scanner->m_bPositionDepend || m_Scanner->m_bSpeedDepend);

	UpdateWindow();
}

void CGalvoCardRTC4::UpdateSetting()
{
	if(m_Scanner==NULL)
	{
		DrawNumber(&m_Scale, 945, 1);
		DrawNumber(&m_CorX, 1, 1);
		DrawNumber(&m_CorY, 1, 1);
		DrawNumber(&m_OffsetX, 0, 1);
		DrawNumber(&m_OffsetY, 0, 1);
		DrawNumber(&m_Rotate, 0, 1);
		
		DrawNumber(&m_iListRunGap, 4000);
//		DrawNumber(&m_iListLoadGap, 4000);

		m_LaserMode.SetCurSel(0);	
		m_CorFile.SetWindowText("Load Correction File!");	
		return;
	}

	if(!m_Scanner->m_corfile.IsEmpty())
		m_CorFile.SetWindowText(m_Scanner->m_corfile);	
	if(!m_Scanner->m_powercurvefile.IsEmpty())
		m_PowerCurve.SetWindowText(m_Scanner->m_powercurvefile);
	if(!m_Scanner->m_varpolyfile.IsEmpty())
		m_strVarPolyFile.SetWindowText(m_Scanner->m_varpolyfile);

	m_LaserMode.SetCurSel(m_Scanner->m_lasermode);
	
	CButton* pbtn=(CButton*)GetDlgItem(IDC_VARPOLYDELAYCHECK);
	pbtn->SetCheck(m_Scanner->m_bVarPolyDelay);
	pbtn=(CButton*)GetDlgItem(IDC_SCANNER_FLIPX);

	pbtn->SetCheck(m_Scanner->bFlipx);
	pbtn=(CButton*)GetDlgItem(IDC_SCANNER_FLIPY);
	pbtn->SetCheck(m_Scanner->bFlipy);

	DrawNumber(&m_Scale, m_Scanner->m_Scale, 1);
    DrawNumber(&m_CorX, m_Scanner->xcor, 1);
	DrawNumber(&m_CorY, m_Scanner->ycor, 1);
	DrawNumber(&m_OffsetX, m_Scanner->xoffset, 1);
	DrawNumber(&m_OffsetY, m_Scanner->yoffset, 1);
	DrawNumber(&m_Rotate, m_Scanner->xyrotate, 1);

	DrawNumber(&m_iListRunGap, m_Scanner->RunGap);
	DrawNumber(&m_iListLoadGap, m_Scanner->LoadGap);

	UpdateWindow();
}


/////////////////////////////////////////////////////////////////////////////
// CGalvoCardRTC4 dialog
CGalvoCardRTC4::CGalvoCardRTC4( UINT DLGID ,CWnd* pParent /*=NULL*/)
: CDialog(DLGID, pParent)
{
	//{{AFX_DATA_INIT(CGalvoCardRTC4)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_Scanner=NULL;
}

void CGalvoCardRTC4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGalvoCardRTC4)
	DDX_Control(pDX, IDC_VARPOLYDELAYCHECK, m_VarCheck);
	DDX_Control(pDX, IDC_SCANNER_ROTATION, m_Rotate);
	DDX_Control(pDX, IDC_SCANNER_XYFACTOR, m_Scale);
	DDX_Control(pDX, IDC_SCANNER_OFFSETX, m_OffsetX);
	DDX_Control(pDX, IDC_SCANNER_OFFSETY, m_OffsetY);
	DDX_Control(pDX, IDC_SCANNER_XSCALECOR, m_CorX);
	DDX_Control(pDX, IDC_SCANNER_YSCALECOR, m_CorY);
	DDX_Control(pDX, IDC_SCANNER_LOADGAP, m_iListLoadGap);
	DDX_Control(pDX, IDC_SCANNER_RUNGAP, m_iListRunGap);
	DDX_Control(pDX, IDC_COMBOLASERMODE, m_LaserMode);
	DDX_Control(pDX, IDC_SCANNER_CORFILE, m_CorFile);
	DDX_Control(pDX, IDC_SCANNER_POWERFILE, m_PowerCurve);
	DDX_Control(pDX, IDC_SCANNER_VARPOLYFILE, m_strVarPolyFile);

	//}}AFX_DATA_MAP
}
BEGIN_MESSAGE_MAP(CGalvoCardRTC4, CDialog)
	//{{AFX_MSG_MAP(CGalvoCardRTC4)
	 ON_STN_DBLCLK(IDC_SCANNER_CORFILE, OnCorFileLoad)
	 ON_STN_DBLCLK(IDC_SCANNER_POWERFILE, OnPowerFileLoad)
	 ON_STN_DBLCLK(IDC_SCANNER_VARPOLYFILE, OnVaryPolyDelayFileLoad)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CGalvoCardRTC6 dialog


CGalvoCardRTC6::CGalvoCardRTC6(UINT DLGID, CWnd* pParent /*=NULL*/)
	: CGalvoCardRTC5(DLGID, pParent)
{
	//{{AFX_DATA_INIT(CGalvoCardRTC6)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CGalvoCardRTC6::DoDataExchange(CDataExchange* pDX)
{
	CGalvoCardRTC5::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_AUTOLASERDELAYCHECK, AutoScanAheadDelay);
	DDX_Control(pDX, IDC_SCANAHEADCORNER, CornerScale);
	DDX_Control(pDX, IDC_SCANAHEADEND, EndScale);
	DDX_Control(pDX, IDC_SCANAHEADACC, AccScale);
	DDX_Control(pDX, IDC_SCANAHEADLASERON, ScanAheadLaserOn);
	DDX_Control(pDX, IDC_SCANAHEADLASEROFF, ScanAheadLaserOff);
	//{{AFX_DATA_MAP(CGalvoCardRTC6)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CGalvoCardRTC6::UpdateSetting()
{
	CGalvoCardRTC5::m_Scanner=(RTC5*)m_Scanner;
	CGalvoCardRTC5::UpdateSetting();

	if(m_Scanner==NULL)
	{
		AutoScanAheadDelay.SetCheck(false);
		DrawNumber(&CornerScale, 0, 1);
		DrawNumber(&EndScale, 0, 1);
		DrawNumber(&AccScale, 0, 1);
		
		DrawNumber(&ScanAheadLaserOn, 10, 1);
		DrawNumber(&ScanAheadLaserOff, 10, 1);

		return;
	}

	AutoScanAheadDelay.SetCheck(m_Scanner->m_bAdvScanAheadDelay);
	DrawNumber(&CornerScale, m_Scanner->m_dCornerScale, 1);
	DrawNumber(&EndScale, m_Scanner->m_dEndScale, 1);
	DrawNumber(&AccScale, m_Scanner->m_dAccScale, 1);

	DrawNumber(&ScanAheadLaserOn, m_Scanner->m_dAdvScanAheadLaserOn, 1);
	DrawNumber(&ScanAheadLaserOff, m_Scanner->m_dAdvScanAheadLaserOff, 1);

	UpdateWindow();
}

void CGalvoCardRTC6::Apply()
{
	CGalvoCardRTC5::m_Scanner=m_Scanner;
	CGalvoCardRTC5::Apply();

	m_Scanner->m_bAdvScanAheadDelay=AutoScanAheadDelay.GetCheck();

	m_Scanner->m_dCornerScale=GetNumber(&CornerScale);
	m_Scanner->m_dEndScale= GetNumber(&EndScale);
	m_Scanner->m_dAccScale=GetNumber(&AccScale);
	
	m_Scanner->m_dAdvScanAheadLaserOn=GetNumber(&ScanAheadLaserOn);
	m_Scanner->m_dAdvScanAheadLaserOff=GetNumber(&ScanAheadLaserOff);
}


BEGIN_MESSAGE_MAP(CGalvoCardRTC6, CGalvoCardRTC5)
	//{{AFX_MSG_MAP(CGalvoCardRTC6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGalvoCardRTC6 message handlers

BOOL CGalvoCardRTC6::OnInitDialog() 
{
//	CGalvoCardRTC5::m_Scanner=(RTC5*)m_Scanner;
	CGalvoCardRTC5::OnInitDialog();
	
//	UpdateSetting();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CGalvoCardSetting::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CString str;
	CString	m_strCardInfo;
	if(m_Scanner!=NULL && m_Scanner->GetState()>=1)	
	{
		if(m_Scanner->GetCardType()==cardRTC4)
			m_strCardInfo.Format("| RTC4 SN %d , DLL %d  |", m_Scanner->GetSerielNr(), m_Scanner->GetDLLVersion());
		else if((m_Scanner->GetCardType()==cardRTC5))
			m_strCardInfo.Format("| RTC5 SN %d , DLL %d  |", m_Scanner->GetSerielNr(), m_Scanner->GetDLLVersion());
		else if((m_Scanner->GetCardType()==cardRTC6))
			m_strCardInfo.Format("| RTC6 SN %d , DLL %d  |", m_Scanner->GetSerielNr(), m_Scanner->GetDLLVersion());
		
		int istatus=m_Scanner->GetHeadStatus();		
		int istand;
		
		istand=(m_Scanner->GetCardType()==cardRTC4)?0x8000:0x80;			
		if(istatus&&istand)
			str.Format("  Power OK   |");
		else
			str.Format("  Power NOK  |");
		
		m_strCardInfo+=str;
		
		istand=(m_Scanner->GetCardType()==cardRTC4)?0x4000:0x40;			
		
		if(istatus&istand)
			str.Format("  Temp OK   |");
		else
			str.Format("  Temp NOK  |");
		
		m_strCardInfo+=str;
		
		istand=(m_Scanner->GetCardType()==cardRTC4)?0x1000:0x10;
		
		if(istatus&istand)
			str.Format("  XPos OK   |");
		else
			str.Format("  XPos NOK  |");
		
		m_strCardInfo+=str;
		
		istand=(m_Scanner->GetCardType()==cardRTC4)?0x800:0x8;			
		
		if(istatus&istand)
			str.Format("  YPos OK  |");
		else
			str.Format("  YPos NOK |");
		
		m_strCardInfo+=str;

		if(m_Scanner->GetCardType()!=cardtype)
			dc.FillSolidRect(m_InfoRect, RGB(200,100,155));
		else	
			dc.FillSolidRect(m_InfoRect, RGB(0,200,155));

		dc.TextOut(15,50, m_strCardInfo);
	}		
	else
	{
		dc.FillSolidRect(m_InfoRect, RGB(200,100,155));
		dc.TextOut(15,50, "No RTC card connected!");
	}
}
