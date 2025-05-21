// Scanner.cpp: implementation of the CScanner class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#include "Scanner.h"
#include "cgalvocardsetting.h"

CScanner::CScanner(CWnd* pOwner)
{
	m_pOwner=pOwner;	
	gLibRTC=NULL;
	m_State=DEVICE_STATE_NOT_INSTALLED;
}	


CScanner::~CScanner()
{
	gLibRTC=NULL;
}
/*
bool CScanner::LoadSetting()
{

	CString loadpath=filepath+"\\config.ini";
	//////////////////////////////////////////////////////////////////////////
	CString str;

	GetPrivateProfileString("GalvoSettings", "GalvoCardType", "0", str.GetBuffer(MAX_PATH), MAX_PATH, loadpath);
	str.ReleaseBuffer();
	m_CardType=(DriverCard)atoi(str);

// 	GetPrivateProfileString("GalvoSettings","ZDriverType","2", str.GetBuffer(MAX_PATH), MAX_PATH, loadpath);
// 	str.ReleaseBuffer();
// 	m_ZDriver=(DriverDim)atoi(str);

	GetPrivateProfileString("GalvoSettings","LaserMode","0", str.GetBuffer(MAX_PATH), MAX_PATH, loadpath);
	str.ReleaseBuffer();
	m_GalvoPara.m_lasermode=atoi(str);

	::GetPrivateProfileString("GalvoSettings","CorFile","Cor_1to1.ctb", m_corfile.GetBuffer(MAX_PATH),MAX_PATH,loadpath);
	m_corfile.ReleaseBuffer();

	::GetPrivateProfileString("GalvoSettings","Scale","945", str.GetBuffer(MAX_PATH),MAX_PATH,filepath);
	str.ReleaseBuffer();
	m_RTC.m_Scale=atof(str);

	::GetPrivateProfileString("Field","XOffset","0",str.GetBuffer(MAX_PATH),MAX_PATH,loadpath);
	str.ReleaseBuffer();
	m_GalvoPara.m_offsetx=atof(str);
	::GetPrivateProfileString("Field","YOffset","0",str.GetBuffer(MAX_PATH),MAX_PATH,loadpath);
	str.ReleaseBuffer();
	m_GalvoPara.m_offsety=atof(str);
	::GetPrivateProfileString("Field","Angle","0",str.GetBuffer(MAX_PATH),MAX_PATH,loadpath);
	str.ReleaseBuffer();
	m_GalvoPara.m_rotationangle=atof(str);

	::GetPrivateProfileString("ZCalibrate","ZUserDefined","0",str.GetBuffer(MAX_PATH),MAX_PATH,loadpath);
	str.ReleaseBuffer();
	m_bUserDefinedZ=atoi(str);

	::GetPrivateProfileString("ZCalibrate","ZA","801.33",str.GetBuffer(MAX_PATH),MAX_PATH,loadpath);
	str.ReleaseBuffer();
	m_GalvoPara.m_zA=atof(str);

	::GetPrivateProfileString("ZCalibrate","ZB","12.106",str.GetBuffer(MAX_PATH),MAX_PATH,loadpath);
	str.ReleaseBuffer();
	m_GalvoPara.m_zB=atof(str);

	::GetPrivateProfileString("ZCalibrate","ZC","-0.00013274",str.GetBuffer(MAX_PATH),MAX_PATH,loadpath);
	str.ReleaseBuffer();
	m_GalvoPara.m_zC=atof(str);


	//[Laser Signal]
	::GetPrivateProfileString("Laser Signal","LaserMode","0",str.GetBuffer(MAX_PATH),MAX_PATH,loadpath);
	str.ReleaseBuffer();
	m_lasermode=str;

	::GetPrivateProfileString("Laser Signal","Frequency","100000",str.GetBuffer(MAX_PATH),MAX_PATH,loadpath);
	str.ReleaseBuffer();
	m_ScannerPara.m_signalfreq=atof(str);

	::GetPrivateProfileString("Laser Signal","TriggerDuration","2",str.GetBuffer(MAX_PATH),MAX_PATH,loadpath);
	str.ReleaseBuffer();
	m_ScannerPara.m_signalwidth=atof(str);

	return true;

}

bool CScanner::SaveSetting()
{
	CString loadpath;
	loadpath=filepath +"\\config.ini";

	CString str;

	str.Format("%d", m_CardType);
	WritePrivateProfileString("GalvoSettings", "GalvoCardType", str, loadpath);
// 
// 	str.Format("%d", m_ZDriver);
// 	WritePrivateProfileString("GalvoSettings","ZDriverType",str,loadpath);

	WritePrivateProfileString("GalvoSettings","CorFile", m_corfile, loadpath);

	str.Format("%d", m_GalvoPara.m_lasermode);
	WritePrivateProfileString("GalvoSettings","LaserMode",str, loadpath);

	str.Format("%f",m_RTC.m_Scale);
	WritePrivateProfileString("GalvoSettings","Scale",str,loadpath);

	str.Format("%f",m_GalvoPara.m_offsetx);
	WritePrivateProfileString("GalvoSettings","XOffset",str,loadpath);
	str.Format("%f",m_GalvoPara.m_offsety);
	WritePrivateProfileString("GalvoSettings","YOffset",str,loadpath);

	str.Format("%f",m_GalvoPara.m_rotationangle);
	WritePrivateProfileString("GalvoSettings","Angle",str,loadpath);

	str.Format("%d",(int)m_bUserDefinedZ);
	WritePrivateProfileString("ZCalibrate","ZUserDefined",str,loadpath);

	str.Format("%f",m_GalvoPara.m_zA);
	WritePrivateProfileString("ZCalibrate","ZA",str,loadpath);

	str.Format("%f",m_GalvoPara.m_zB);
	WritePrivateProfileString("ZCalibrate","ZB",str,loadpath);
	
	str.Format("%f",m_GalvoPara.m_zC);
	WritePrivateProfileString("ZCalibrate","ZC",str,loadpath);
	
///////////////////////////
	//[Laser]
	WritePrivateProfileString("Laser Signal","LaserMode",m_lasermode,loadpath);
	str.Format("%f",m_ScannerPara.m_signalfreq);
	WritePrivateProfileString("Laser Signal","Frequency",str,loadpath);
	str.Format("%f",m_ScannerPara.m_signalwidth);
	WritePrivateProfileString("Laser Signal","TriggerDuration",str,loadpath);

  
	return true;
}

/*

void CScanner::StopExcute()
{
	if(m_State>=DEVICE_STATE_BUSY)
		while(busy)
		{
			m_RTC.stop_execution();		
			Sleep(1);
		}
}

bool CScanner::AddCmdToExcute(unsigned CurList, CString *CMDline, unsigned long& listcount)
{
	BOOL checkbusy;

	m_RTC.get_status(&busy, &position);

	checkbusy= busy & 1;

	if(checkbusy)
	{
		if(position >= m_RTC.m_MaxList && CurList==1) checkbusy=false;    //list 2 is busy, list 1 can be written 
		if(position < m_RTC.m_MaxList && CurList==2) checkbusy=false;
	}				

	if(checkbusy)
		return false;
	
	CMDtype tmpCMD;
	CString str;

	CString para[5];	
	int iFound, iStart;
	
	iFound=CMDline->Find(" ");
	str=CMDline->Left(iFound);		
	tmpCMD=(CMDtype)atoi(str);
	
	iStart=iFound+1;
	iFound=CMDline->Find(",",iStart);
	
	for(int i=0;iFound>0;i++)
	{
		para[i]=CMDline->Mid(iStart, iFound-iStart);
		iStart=iFound+1;
		iFound=CMDline->Find(",",iStart);
	}
	
	para[i++]=CMDline->Right(CMDline->GetLength()-iStart);

 	switch(tmpCMD)
	{
	case SPoint:
		listcount+=1;
		if(listcount>=m_RTC.m_MaxList-2)
			return false;

		m_RTC.jump_abs_3d(atof(para[0]),atof(para[1]),0);
		m_RTC.laser_on_list(atof(para[2]));
		break;
	case SetLaserDelays:
		m_RTC.set_laser_delays(atof(para[0]),atof(para[1]));
		m_ScannerPara.m_laserondelay= atof(para[0]);
		m_ScannerPara.m_laseroffdelay= atof(para[1]);
		break;
	case SetScannerDelay:			//in ms 
		m_RTC.set_scanner_delays(atof(para[0]),atof(para[1]),atof(para[2]));
		m_ScannerPara.m_jumpdelay=atof(para[0]);
		m_ScannerPara.m_markdelay=atof(para[1]);
		m_ScannerPara.m_polygondelay=atof(para[2]);
		break;
	case SetJumpSpeed:
		m_RTC.set_jump_speed(atof(para[0]));
		m_ScannerPara.m_jumpspeed=atof(para[0]);
		break;
	case SetMarkSpeed:
		m_RTC.set_mark_speed(atof(para[0]));
		m_ScannerPara.m_markspeed=atof(para[0]);
		break;
	case SetWobbel:
		m_RTC.set_wobbel(atof(para[0]),atof(para[1]));
		m_ScannerPara.m_wobelamp=atof(para[0]);
		m_ScannerPara.m_wobelfreq=atof(para[1]);
		break;
	case SMarkTo:
		m_RTC.mark_abs(atof(para[0]),atof(para[1]));
		break;
	case SJumpTo:
		m_RTC.jump_abs(atof(para[0]),atof(para[1]));
		break;
	case SMark3DTo:
		m_RTC.mark_abs_3d(atof(para[0]),atof(para[1]),atof(para[2]));
		break;
	case SJump3DTo:
		m_RTC.jump_abs_3d(atof(para[0]),atof(para[1]),atof(para[2]));
		break;
	case SMarkRelTo:
		m_RTC.mark_rel(atof(para[0]),atof(para[1]));
		break;
	case SJumpRelTo:
		m_RTC.jump_rel(atof(para[0]),atof(para[1]));
		break;
	case SMark3DRelTo:
		m_RTC.mark_rel_3d(atof(para[0]),atof(para[1]),atof(para[2]));
		break;
	case SJump3DRelTo:
		m_RTC.jump_rel_3d(atof(para[0]),atof(para[1]),atof(para[2]));
		break;
	case SArcTo:
		m_RTC.arc_abs(atof(para[0]),atof(para[1]),atof(para[2]));
		break;
	case SArc3DTo:
		m_RTC.arc_abs_3d(atof(para[0]),atof(para[1]),atof(para[2]),atof(para[3]));
		break;
	case SArcRelTo:
		m_RTC.arc_rel(atof(para[0]),atof(para[1]),atof(para[2]));
		break;
	case SArc3DRelTo:
		m_RTC.arc_rel_3d(atof(para[0]),atof(para[1]),atof(para[2]),atof(para[3]));
		break;
	case SZPosition:
		m_RTC.jump_rel_3d(0,0, atof(para[0]));
		break;
	case SSetPixelLine:  //occupied 2 entries for RTC4
		if(m_CardType==cardRTC4)
		{
			listcount++;
			if(listcount>=m_RTC.m_MaxList-1)
				return false;		
		}	
	
 		m_PixelPara.pixel_period=atof(para[0]);
		m_PixelPara.pixel_dx=atof(para[1]);
		m_PixelPara.pixel_dy=atof(para[2]);	

		m_RTC.set_pixel_line(atof(para[0]),atof(para[1]),atof(para[2]));		
		break;
	case SSetPixel:			
 		if(listcount==0)
		{
 			m_RTC.set_pixel_line(m_PixelPara.pixel_period,m_PixelPara.pixel_dx,m_PixelPara.pixel_dy);	
			listcount++;

			if(m_CardType==cardRTC4)
				listcount++;
		}

		m_RTC.set_pixel(atof(para[0]));
		break;
	case SAnologOut1List:
		m_RTC.write_da_1_list(atof(para[0])); //us
		break;
	case SAnologOut1:
		m_RTC.write_da_1(atof(para[0])); //us
		break;
	case SLaserOnList:
		m_RTC.laser_on_list(atof(para[0])); //us
		break; 
	case SLongDelay:
		m_RTC.long_delay(atof(para[0]));	//us
		break;
	}

	listcount++;
	return true;
}


void CScanner::ExcuteCMDFunc(CString CMDline)
{
	////////////////////////////////////////////////////////////////	
	if(bListStart)
	{
		CurList=1;
		iListCounter=0;			
		
		m_RTC.set_start_list(CurList);
		m_RTC.save_and_restart_timer();		//record time;
	
		m_State=DEVICE_STATE_BUSY;

		bListStart=false;
		bListTriggered=false;
	}

	do{
		if(iListCounter>= m_RTC.m_MaxList - 1) 
		{	
			m_RTC.set_end_of_list();			//list if full	
			iListCounter=0; 
			
			if(!bListTriggered && !m_Quit)
			{	
				m_RTC.execute_list(1);	//if first time start excute list 1				
				bListTriggered=true;
			}
			else 
				m_RTC.auto_change();
			
			CurList=(CurList&1) + 1;		//change list				
			m_RTC.set_start_list(CurList);		
		}

		MSG msg;
		if(PeekMessage(&msg, (HWND)NULL, 0,0,PM_REMOVE))
		{
			::SendMessage(msg.hwnd, msg.message,msg.wParam, msg.lParam);
		}

	}while(!AddCmdToExcute(CurList,&CMDline, iListCounter) && !m_Quit);

}


void CScanner::EndOfList()
{
	m_RTC.save_and_restart_timer();
	m_RTC.set_end_of_list();	

	if(!bListTriggered&& !m_Quit)
	{
		m_RTC.execute_list(1);
		bListTriggered=true;
	}
	else
		m_RTC.auto_change();	

	m_State=DEVICE_STATE_OK;
}


double CScanner::GetScanField()
{

}

bool CScanner::InitialRTC() 
{
	m_State=DEVICE_STATE_NOT_INITIALIZED;
	m_RTC.m_CardType=m_CardType;

	//load dll
	if(m_RTC.RTCopen()<DEVICE_STATE_OK)
	{
		m_State=DEVICE_STATE_ERROR;
		return false;
	}

	//load files
	SetCurrentDirectory(filepath);

	if(!LoadFile(".\\Correction Files\\" + m_corfile))
	{
		m_State=DEVICE_STATE_ERROR;
		return false;
	}

	if(!SetRTC())
	{
		m_State=DEVICE_STATE_ERROR;
		return false;
	};
	
	m_State=DEVICE_STATE_OK;
	return true;
}

*/
CScanner* CScanner::ShowSettingDlg()
{
  	CGalvoCardSetting setdlg;
 
	setdlg.m_Scanner=this;
	setdlg.DoModal();

	return setdlg.m_Scanner;
}

/*
bool CScanner::LoadFile(CString file)
{
	if(m_CardType==cardRTC4 && 
		m_RTC.m_RTC4->LoadFiles(file))
	{
		m_State=DEVICE_STATE_OK;
		return true;
	}
	else if(m_CardType==cardRTC5 &&
		m_RTC.m_RTC5->LoadFiles(file))
	{
		m_State=DEVICE_STATE_OK;
		return true;
	}

	m_State=DEVICE_STATE_ERROR;
	return false;
}

bool CScanner::SetRTC()
{
	m_RTC.set_laser_mode(m_GalvoPara.m_lasermode);

	unsigned short rtcversion;
	unsigned short rtcsn;
	unsigned short hexversion;
	
	//set delays
	if(m_CardType==cardRTC4)
	{	

		m_RTC.m_RTC4->stop_execution();
		m_RTC.set_start_list(1);
		m_RTC.m_RTC4->set_laser_timing(1000000*8/2/m_ScannerPara.m_signalfreq,    // half of the standby period in 1/8 microseconds
			m_ScannerPara.m_signalwidth*8, m_ScannerPara.m_signalwidth*8,		//signal 1 as pulse triger, signal 2 as gate for pulse number
			1);																// pulse width in 1/8 microseconds
		m_RTC.set_end_of_list();
		m_RTC.execute_list(1);
		
		rtcversion=m_RTC.m_RTC4->get_rtc_version();
		rtcsn	= m_RTC.m_RTC4->get_serial_number();
		hexversion=m_RTC.m_RTC4->get_hex_version();
		
		m_RTC.m_RTC4->set_offset(m_GalvoPara.m_offsetx*m_RTC.m_Scale,m_GalvoPara.m_offsety*m_RTC.m_Scale);
		m_RTC.m_RTC4->set_matrix(cos(m_GalvoPara.m_rotationangle*PI/180),-sin(m_GalvoPara.m_rotationangle*PI/180),
			sin(m_GalvoPara.m_rotationangle*PI/180),cos(m_GalvoPara.m_rotationangle*PI/180));
		
		m_CardInfo.Format("RTC4 card:\nVersion: %i\tSN: %i\tHex Version: %i", 
			rtcversion, rtcsn, hexversion);
		
	}
	else if(m_CardType==cardRTC5)	
	{	
		m_RTC.m_RTC5->stop_execution();
		m_RTC.m_RTC5->select_cor_table(1, 0); //  table #1 at primary connector (default)
		m_RTC.m_RTC5->reset_error(UINT_MAX);
		m_RTC.m_RTC5->set_laser_control(0x00);

		m_RTC.m_RTC5->config_list(m_RTC.m_MaxList,m_RTC.m_MaxList);

		rtcversion=m_RTC.m_RTC5->get_rtc_version();
		rtcsn	= m_RTC.m_RTC5->get_serial_number();
		hexversion=m_RTC.m_RTC5->get_hex_version();		
		m_RTC.m_Scale=m_RTC.m_RTC5->get_head_para(1,1);		

		m_RTC.m_RTC5->set_offset(0,m_GalvoPara.m_offsetx*m_RTC.m_Scale,m_GalvoPara.m_offsety*m_RTC.m_Scale,0);
		m_RTC.m_RTC5->set_matrix(0,cos(m_GalvoPara.m_rotationangle*PI/180),-sin(m_GalvoPara.m_rotationangle*PI/180),
			sin(m_GalvoPara.m_rotationangle*PI/180),cos(m_GalvoPara.m_rotationangle*PI/180), 0);

		m_RTC.m_RTC5->set_laser_pulses_ctrl(int(1/m_ScannerPara.m_signalfreq*1000000*64/2),     // half of the standby period in 1/64 microseconds
			int(m_ScannerPara.m_signalwidth*64));

		m_CardInfo.Format("RTC5 card:\nVersion: %i\tSN: %i \tHex Version: %i", 
			rtcversion, rtcsn, hexversion);
	}

	if(m_bUserDefinedZ)
		m_RTC.load_z_table(m_GalvoPara.m_zA,m_GalvoPara.m_zB,m_GalvoPara.m_zC);

	return true;
}

void CScanner::ShowZCalibrateDlg()
{
	if(m_zCaliDlg!=NULL)
	{
		m_zCaliDlg->ShowWindow(SW_SHOW);
	}
	else
	{
		m_zCaliDlg=new CZCalibrationDlg;
		m_zCaliDlg->m_Scanner=this;

		m_zCaliDlg->Create(IDD_DIALOG_ZCALIBRATION);
		m_zCaliDlg->ShowWindow(SW_SHOW);
	}
}


void CScanner::RunStateMachine()
{
	int i=0;
	MSG msg;
	
	while(!m_Quit)
	{
		i++;

		m_RTC.get_status(&busy, &position);

		CurX=(double)m_RTC.get_value(7)/m_RTC.m_Scale;			
		CurY=(double)m_RTC.get_value(8)/m_RTC.m_Scale;	
		CurZ=(double)m_RTC.get_value(9)/m_RTC.m_Scale;					

		if(i%100==0)
		{
			::PostMessage(m_pOwner->GetSafeHwnd(), WM_SCANPOS_MESSAGE,NULL,NULL);	//send message to status tar
			i=0;
		}

		if(PeekMessage(&msg, (HWND)NULL, 0,0,PM_REMOVE))
		{
			::SendMessage(msg.hwnd, msg.message,msg.wParam, msg.lParam);
		}
	}
}

UINT CScanner::StartStateMachineThread(LPVOID pParam)
{
	CScanner* pScanner=(CScanner*)pParam;
		pScanner->RunStateMachine();
	return 0;
}

*/


// void CScanner::ShowCardSettings()
// {
// 	CCardSetting dlg;
// 	
// 	dlg.m_Scanner=this;
// 	
// 	dlg.DoModal();
// 
// }

double CScanner::GetScaleFactor()
{
	return m_Scale;
}

void CScanner::SetScaleFactor(double dScale)
{
	m_Scale=dScale;
}

void CScanner::SetCorFile(CString corfile)
{
	m_corfile=corfile;
}

void CLaserPara::IsEqual(CLaserPara *pLaserPara)
{

}

void CLaserPara::SetPara(CLaserPara *pPara)
{
	SetMarkPara(pPara);
	SetDelayPara(pPara);
}

void CLaserPara::SetMarkPara(CLaserPara *pPara)
{
	m_dPower=pPara->m_dPower;

	m_dMarkSpeed=pPara->m_dMarkSpeed;
	m_dJumpSpeed=pPara->m_dJumpSpeed;
	
	m_dWobelAmpl=pPara->m_dWobelAmpl;
	m_dWobelFreq=pPara->m_dWobelFreq;

	if(pPara->m_dPulseWidth>(1/pPara->m_dFrequency*1000000)) //us
		AfxMessageBox("The pulse width is wider than frequency setting, are you sure?");

	m_dFrequency=pPara->m_dFrequency;
	m_dPulseWidth=pPara->m_dPulseWidth;

// 	m_bVectorDepend=pPara->m_bVectorDepend;
// 	m_bPositionDepend=pPara->m_bPositionDepend;
// 	m_bSpeedDepend=pPara->m_bSpeedDepend;
// 
// 	m_iSpeedDependMode=pPara->m_iSpeedDependMode;
// 	m_iDependCtrl=pPara->m_iDependCtrl;
// 	m_iVectorDependCtrl= pPara->m_iVectorDependCtrl;
// 	m_dVectorDependValue =pPara->m_dVectorDependValue;
// 	m_iPosDependScaleNr  =pPara->m_iPosDependScaleNr;

}

void CLaserPara::SetDelayPara(CLaserPara *pPara)
{
	m_dPolygonDelay	=pPara->m_dPolygonDelay;
	m_dMarkDelay=pPara->m_dMarkDelay;
	m_dJumpDelay=pPara->m_dJumpDelay;

	m_dLaserOnDelay	=pPara->m_dLaserOnDelay;
	m_dLaserOffDelay=pPara->m_dLaserOffDelay;

	m_iSkywritingMode=pPara->m_iSkywritingMode;
	m_dSkywritingLaserOnShift=pPara->m_dSkywritingLaserOnShift;
	m_dSkywritingTimeleg=pPara->m_dSkywritingTimeleg;
	m_dSkywritingNprev=pPara->m_dSkywritingNprev;
	m_dSkywritingNpost=pPara->m_dSkywritingNpost;
}

CLaserPara::CLaserPara()
{
	m_dPower= 0.0;



	m_iSkywritingMode=0;
	m_dSkywritingTimeleg=1;
	m_dSkywritingLaserOnShift=10;
	m_dSkywritingNprev=10;
	m_dSkywritingNpost=10;


	m_dMarkSpeed= 1000.0;
	m_dJumpSpeed= 3000.0;
	
	m_dPolygonDelay= 0;
	m_dMarkDelay= 10;
	m_dJumpDelay= 20;
	
	m_dWobelAmpl= 0;
	m_dWobelFreq= 100;
	
	m_dLaserOnDelay= 100;
	m_dLaserOffDelay= 120;
	
	m_dFrequency= 100000;
	m_dPulseWidth= 2;

	m_bVectorDepend=false;
}

CLaserPara::~CLaserPara()
{
	
}



void CLaserPara::Serialize(CArchive &ar)
{
	if(ar.IsStoring())
	{
		ar<<m_dJumpSpeed<<m_dMarkSpeed;
		ar<<m_dJumpDelay<<m_dMarkDelay<<m_dPolygonDelay;
		ar<<m_dLaserOnDelay<<m_dLaserOffDelay;
		ar<<m_dPower<<m_dFrequency<<m_dPulseWidth;
		ar<<m_dWobelAmpl<<m_dWobelFreq;
		ar<<m_iSkywritingMode<<m_dSkywritingLaserOnShift<<m_dSkywritingTimeleg<<m_dSkywritingNprev<<m_dSkywritingNpost;	
		ar<<m_bVectorDepend<<m_iVectorDependCtrl<<m_dVectorDependValue;
	}
	else{
		ar>>m_dJumpSpeed>>m_dMarkSpeed;
		ar>>m_dJumpDelay>>m_dMarkDelay>>m_dPolygonDelay;
		ar>>m_dLaserOnDelay>>m_dLaserOffDelay;
		ar>>m_dPower>>m_dFrequency>>m_dPulseWidth;
		ar>>m_dWobelAmpl>>m_dWobelFreq;
		ar>>m_iSkywritingMode>>m_dSkywritingLaserOnShift>>m_dSkywritingTimeleg>>m_dSkywritingNprev>>m_dSkywritingNpost;	
		ar>>m_bVectorDepend>>m_iVectorDependCtrl>>m_dVectorDependValue;
	}
}



void CScanner::LoadPowerCurve(CString filepath)
{
	CStdioFile fi;
	
	if(!fi.Open(filepath,CFile::modeRead))		//打开文件
	{
		PowerCurve.RemoveAll();
		m_powercurvefile="";		
		return;										//退出函数体
	}
	
	CString str,substr;
	int ifound;
	
	PowerCurve.RemoveAll();		
	PowerVolt tmpData;	
	while(fi.ReadString(str))
	{
		if(str.IsEmpty())
			continue;
		
		if(str[0]=='#')
			continue;
		
		ifound=str.Find(',', 0);
		
		if(ifound>=0)
		{
			substr=str.Left(ifound);			
			tmpData.dVolt=atof(substr);				
					
			substr=str.Mid(ifound+1);
			tmpData.dPower=atof(substr);
			
			PowerCurve.AddTail(tmpData);
		}
	}

	int Pos=filepath.ReverseFind('\\');	
	m_powercurvefile=filepath.Mid(Pos+1);;
}

double CScanner::Power2Volt(double dPower)
{
	if(PowerCurve.IsEmpty())
		return dPower;

	PowerVolt tmpData,tmpData1;

	double dVolt=0;

	POSITION pos=PowerCurve.GetHeadPosition();	
	tmpData=PowerCurve.GetNext(pos);

	while(pos!=NULL)
	{
		tmpData1=PowerCurve.GetAt(pos);

		if(dPower>=tmpData.dPower && dPower<=tmpData1.dPower)
		{
			if(tmpData.dPower==tmpData1.dPower)
				return tmpData.dVolt;
			else
			{
				dVolt=tmpData.dVolt+(dPower-tmpData.dPower)*(tmpData.dVolt-tmpData1.dVolt)/(tmpData.dPower-tmpData1.dPower);
				return dVolt;
			}
		}
		else
			tmpData=PowerCurve.GetNext(pos);
	}

	return tmpData.dVolt;
}


