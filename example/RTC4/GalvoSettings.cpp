// GalvoSettings.cpp : implementation file
//

#include "stdafx.h"
#include "GalvoSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGalvoSettings dialog

#include "RTC4expl.h"
#include "RTC5expl.h"
#include "RTC6expl.h"

CGalvoSettings::CGalvoSettings(CWnd* pParent /*=NULL*/)
: CDialog(CGalvoSettings::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGalvoSettings)
	//}}AFX_DATA_INIT
}

void CGalvoSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGalvoSettings)
//	DDX_Control(pDX, IDC_CHECKZUSERDEFINED, m_bUserDefinedZ);
//	DDX_Control(pDX, IDC_ZTABLEB, m_ZCalibB);
//	DDX_Control(pDX, IDC_ZTABLEC, m_ZCalibC);
//	DDX_Control(pDX, IDC_ZTABLEA, m_ZCalibA);
// 	DDX_Control(pDX, IDC_COMBOLASERMODE, m_LaserMode);
// 	DDX_Control(pDX, IDC_COMBOCORRECTIONFILE, m_CorCtrl);
// 	DDX_Text(pDX, IDC_RTCINFO, m_CardInfo);
// 	DDX_Text(pDX, IDC_SCANNER_XYFACTOR, m_Scalefactor);
// 	DDX_Text(pDX, IDC_SCANNER_ROTATION, m_roationangle);
// 	DDX_Text(pDX, IDC_STATICAUTOCONTROL, m_strAutoScaleFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGalvoSettings, CDialog)
	//{{AFX_MSG_MAP(CGalvoSettings)
	ON_BN_CLICKED(IDC_TYPERTC4, OnTypertc4)
	ON_BN_CLICKED(IDC_TYPERTC5, OnTypertc5)
	ON_BN_CLICKED(IDC_TYPERTC6, OnTypertc6)
	ON_BN_CLICKED(IDC_TYPEPMC2, OnTypepmc2)
	ON_BN_CLICKED(IDC_OPENCOR, OnOpencor)
	ON_BN_CLICKED(IDC_OPENAUTOSCALE, OnLoadAutoScaleFile)
	ON_BN_CLICKED(IDC_ONAPPLY, OnApply)
	ON_BN_CLICKED(IDC_OPENPOWERCURVE, OnOpenpowercurve)
	ON_BN_CLICKED(IDC_SHOWPOWERCURVE, OnShowpowercurve)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGalvoSettings message handlers

BOOL CGalvoSettings::OnInitDialog() 
{
	CDialog::OnInitDialog();	

	CButton* pbtn;
	HINSTANCE hInst=GetModuleHandle("GalvoControl.dll");

	hIcon_red=::LoadIcon(hInst, MAKEINTRESOURCE(IDI_LED_REDSCANNER));
	hIcon_green=::LoadIcon(hInst, MAKEINTRESOURCE(IDI_LED_GREENSCANNER));

	m_LaserMode.SetCurSel(0);

	if(m_Scanner!=NULL)
	{
		m_Scanner->StopExcute();
		m_CardType=m_Scanner->GetCardType();

		pbtn=(CButton*)GetDlgItem(IDC_TYPERTC4);
		pbtn->SetCheck(m_CardType==cardRTC4);
		
		pbtn=(CButton*)GetDlgItem(IDC_TYPERTC5);
		pbtn->SetCheck(m_CardType==cardRTC5);
		
		pbtn=(CButton*)GetDlgItem(IDC_TYPERTC6);
		pbtn->SetCheck(m_CardType==cardRTC6);
		
		pbtn=(CButton*)GetDlgItem(IDC_TYPEPMC2);
		pbtn->SetCheck(m_CardType==cardPMC2);
			
		pbtn=(CButton*)GetDlgItem(IDC_SIGNALGATE);
		pbtn->SetCheck(!(m_Scanner->m_LaserSignal&0x11));

		pbtn=(CButton*)GetDlgItem(IDC_SIGNALPULSE1);
		pbtn->SetCheck(m_Scanner->m_LaserSignal&0x01);

		pbtn=(CButton*)GetDlgItem(IDC_SIGNALPULSE2);
		pbtn->SetCheck(m_Scanner->m_LaserSignal&0x10);

		m_roationangle=m_Scanner->m_dRotationAngle;
		m_Scalefactor=m_Scanner->GetScaleFactor();

		AddCorFiles();	

		m_CorCtrl.SetWindowText(m_Scanner->m_corfile);
		m_LaserMode.SetCurSel(m_Scanner->m_lasermode);

		m_strAutoScaleFile=m_Scanner->strAutoControlScale.Mid(m_Scanner->strAutoControlScale.ReverseFind('\\')+1);
		
		m_CardInfo.Format("SN: %i, DLL: %d", m_Scanner->GetSerielNr(), m_Scanner->GetDLLVersion());

		CStatic* ppbtn=(CStatic*)GetDlgItem(IDC_SCANNERPOWER);
		WORD dStatus=m_Scanner->GetHeadStatus();

		if(((dStatus & 0x80) && m_Scanner->GetCardType()==cardRTC4)
			|| ((dStatus & 0x08) && m_Scanner->GetCardType()==cardRTC5)
			|| ((dStatus & 0x08) && m_Scanner->GetCardType()==cardRTC6))
			ppbtn->SetIcon(hIcon_green);
		else
			ppbtn->SetIcon(hIcon_red);

	    SetDlgItemText(IDC_SCANNER_POWERFILE, m_Scanner->m_powercurvefile);
	
	// 		m_bUserDefinedZ.SetCheck(m_Scanner->m_bUserDefinedZ);
// 		OnCheckzuserdefined();
// 		CString str;
// 		str.Format("%.2f",m_Scanner->m_GalvoPara.m_zA);
// 		m_ZCalibA.SetWindowText(str);
// 		str.Format("%.4f",m_Scanner->m_GalvoPara.m_zB);
// 		m_ZCalibB.SetWindowText(str);		
// 		str.Format("%.5f",m_Scanner->m_GalvoPara.m_zC);
// 		m_ZCalibC.SetWindowText(str);
		
		UpdateData(FALSE);
	}
	
	// TODO: Add extra initialization here	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGalvoSettings::OnTypertc4() 
{
 	m_CardType=cardRTC4;
 	AddCorFiles();
}

void CGalvoSettings::OnTypertc5() 
{
 	// TODO: Add your control notification handler code here
 	m_CardType=cardRTC5;
 	AddCorFiles();
}

void CGalvoSettings::OnTypertc6() 
{
	// TODO: Add your control notification handler code here
	m_CardType=cardRTC6;	
	AddCorFiles();
}

void CGalvoSettings::OnTypepmc2() 
{
	m_CardType=cardPMC2;	
}

void CGalvoSettings::OnOpencor() 
{
	if(m_CardType==cardRTC4)
	{
		CFileDialog dlg(TRUE,_T("ctb"),_T("*.ctb"),OFN_FILEMUSTEXIST|OFN_HIDEREADONLY,_T("Correct File(*.ctb)|*.ctb|"));
	
		CString str=filepath+"\\Correction Files";
		dlg.m_ofn.lpstrInitialDir=str;

		if (dlg.DoModal()==IDOK)
		{
			AddCorFiles(dlg.GetPathName());				
			UpdateData(false);		
		}
		return;
	}
	if(m_CardType==cardRTC5)
	{
		CFileDialog dlg(TRUE,_T("ct5"),_T("*.ct5"),OFN_FILEMUSTEXIST|OFN_HIDEREADONLY, _T("Correct File(*.ct5)|*.ct5|"));

		CString str=filepath+"\\Correction Files";
		dlg.m_ofn.lpstrInitialDir=str;
	
		if (dlg.DoModal()==IDOK)
		{
			AddCorFiles(dlg.GetPathName());
			UpdateData(false);	
		}				

		return;
	}		

 }
void CGalvoSettings::AddCorFiles(LPCTSTR Sourcepath)
{
	CFileFind finder;

	BOOL bWorking =finder.FindFile(filepath + "\\Correction Files\\" + "*.*");

	if(!bWorking)
	{
		if(!CreateDirectory(filepath + "\\Correction Files\\", NULL))
			AfxMessageBox("Create correction file failed!");
	}

	CString filename(Sourcepath);

	int pos;
	pos=filename.ReverseFind('\\');
	filename=filename.Mid(pos+1);


	m_CorCtrl.SetWindowText(filename);

	if(CopyFile(Sourcepath, filepath + "\\Correction Files\\" + filename,TRUE))
		m_CorCtrl.AddString(filename);
}

void CGalvoSettings::AddCorFiles()
{
	CFileFind finder;
	bool bWorking;
	
	m_CorCtrl.ResetContent();

	if(m_CardType==cardRTC4) 
		bWorking =finder.FindFile(filepath + "\\Correction Files\\" + "*.ctb");
	else if(m_CardType==cardRTC5 || m_CardType==cardRTC6)
		bWorking =finder.FindFile(filepath + "\\Correction Files\\" + "*.ct5");
	
	CString str;

	while (bWorking==true)
	{
		bWorking = finder.FindNextFile();
		
		str = (LPCTSTR) finder.GetFileName();
		m_CorCtrl.AddString((LPCTSTR) finder.GetFileName());
	}

	m_CorCtrl.SetCurSel(0);
	
}

void CGalvoSettings::OnApply()
{
	BeginWaitCursor();

	SetCapture();				

	if(m_Scanner!=NULL)
	{
		m_Scanner->StopExcute();
		delete m_Scanner;
		m_Scanner=NULL;
	}

	CString m_corfile;

	UpdateData(true);
	m_CorCtrl.GetWindowText(m_corfile);	

	switch(m_CardType)
	{
	case cardRTC4:
		m_Scanner=(RTC4*)new RTC4(NULL);
		break;
	case cardRTC5:
		m_Scanner=(RTC5*)new RTC5(NULL);
		break;	
	case cardRTC6:
		m_Scanner=(RTC6*)new RTC6(NULL);
		break;	
	default:
		return;
	}
	
	CEdit* pedit=(CEdit*)GetDlgItem(IDC_SCANNER_POWERFILE);
	pedit->GetWindowText(m_Scanner->m_powercurvefile);
	
	m_Scanner->m_Scale=m_Scalefactor;
	m_Scanner->m_dRotationAngle=m_roationangle;
	m_Scanner->m_lasermode=m_LaserMode.GetCurSel();

	CButton* pbtn=(CButton*)GetDlgItem(IDC_SIGNALGATE);
	
	if(pbtn->GetCheck())
		m_Scanner->m_LaserSignal=36;
	
	pbtn=(CButton*)GetDlgItem(IDC_SIGNALPULSE1);
	if(pbtn->GetCheck())
		m_Scanner->m_LaserSignal=37;

	pbtn=(CButton*)GetDlgItem(IDC_SIGNALPULSE2);
	if(pbtn->GetCheck())
		m_Scanner->m_LaserSignal=38;

	m_Scanner->SetCorFile(m_corfile);

	if(!m_Scanner->InitialRTC())
	{
		delete m_Scanner;
		m_Scanner=NULL;
		return;
	}		

	m_Scanner->strAutoControlScale=strAutoControlScale;

	m_Scalefactor=m_Scanner->GetScaleFactor();
	m_CardInfo.Format("SN: %i, DLL: %d", m_Scanner->GetSerielNr(), m_Scanner->GetDLLVersion());
	
	WORD dStatus=m_Scanner->GetHeadStatus();
	CStatic* ppbtn=(CStatic*)GetDlgItem(IDC_SCANNERPOWER);		

	if(((dStatus & 0x80) && m_Scanner->GetCardType()==cardRTC4)
			|| ((dStatus & 0x08) && m_Scanner->GetCardType()==cardRTC5)
			|| ((dStatus & 0x08) && m_Scanner->GetCardType()==cardRTC6))
			ppbtn->SetIcon(hIcon_green);
		else
			ppbtn->SetIcon(hIcon_red);

	UpdateData(false);
	Sleep(1000);

	ReleaseCapture();
	EndWaitCursor();
}

void CGalvoSettings::OnOK()
{
 	OnApply();

	CDialog::OnOK();
}
// 

void CGalvoSettings::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}


void CGalvoSettings::OnLoadAutoScaleFile() 
{
	CFileDialog dlg(TRUE,_T("txt"),_T("*.txt"),OFN_FILEMUSTEXIST|OFN_HIDEREADONLY,_T("Auto Control Scale File(*.txt)|*.txt|"));
	
	if(dlg.DoModal()==IDOK)
	{
		strAutoControlScale=dlg.GetPathName();

		CStdioFile fi;
		if(!fi.Open(strAutoControlScale,CFile::modeRead))		//打开文件
		{
			AfxMessageBox(_T("Load AutoScale file failed!"));
			return;							
		}

		CString str;
	
		
		int FileLen=fi.GetLength();
		if(FileLen==0)return;

		int curLine=0;
			
		
		while(fi.ReadString(str))
		{
		   	if(str.Find("[PositionCtrlTable")>=0)
				curLine++;
		}

		m_Scanner->m_iPosCorrectTalbe=curLine;

		m_strAutoScaleFile=strAutoControlScale.Mid(strAutoControlScale.ReverseFind('\\')+1);
		UpdateData(false);
	}	
}


void CGalvoSettings::OnShowpowercurve() 
{

	
}
void CGalvoSettings::OnOpenpowercurve() 
{
	
	
}
