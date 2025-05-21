// Scanner.h: interface for the CScanner class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCANNER_H__08060DB8_7C71_4634_AC7C_EBF518F0DE9D__INCLUDED_)
#define AFX_SCANNER_H__08060DB8_7C71_4634_AC7C_EBF518F0DE9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "defs.h"
#include "IniFile.h"

class AFX_EXT_CLASS CScanner: public CIniFile
{
public:	
	CScanner(CWnd* pOwner);	
	virtual ~CScanner();
	
	CScanner* ShowSettingDlg();	

	double Power2Volt(double dPower);
	void LoadPowerCurve(CString filepath);

	void SetCorFile(CString corfile);	
	void SetScaleFactor(double dScale);
	double GetScaleFactor();

	virtual	void ResetTimer(){};
	virtual double GetMarkTime(){ return 0;};

	virtual void ExcuteGalvoPara(CLaserPara* pPara, bool bJudge=true, bool bSet=true)=0;
	virtual WORD GetHeadStatus()=0;
	virtual int GetSerielNr()=0;
	virtual void LaserOn()=0;
	virtual void LaserOff()=0;
	virtual void SetPulse(double freq, double pwidth)=0;
	virtual void SetAnalog1(double Volt)=0;

	virtual	DriverCard GetCardType(){return CardNULL;}
	virtual void EndOfList(bool bWait=false)=0;
	virtual bool SetRTC()=0;
	virtual bool LoadFile(CString filepath)=0;
	virtual void StopExcute()=0;
	virtual bool InitialRTC(){return false;};
	virtual void WaitForStop()=0;

	virtual	void StartList()=0;
	virtual int GetState(){ return m_State;}	
	virtual UINT GetPosition()=0; 
	virtual bool GetBusy()=0;
	virtual void GetCurPos()=0;
	virtual double GetScanField()=0;	

	virtual void SetTrigger(UINT Period, UINT Signal1,UINT Signal2)=0;
	virtual void MeasurementStatus( UINT* busy, UINT* position )=0;	
	virtual int GetDLLVersion()=0;
	virtual void SetOffsetList(double dx, double dy)=0;


	bool m_bTriggered;
	bool m_Quit;

	unsigned long iLoadPos;
	unsigned long iMaxListPos;
	unsigned long iMaxBits;

	UINT RunGap, LoadGap;
	UINT RecordPos;	
	UINT GapLoad, GapRun;

	//special for bitmap, store these parameters to recall in case set-pixel in list head.
	int iBmpChanel;
	double dBmpPeriod, dBmpx, dBmpy, dBmpz;

	CWnd* m_pOwner;
	double CurX, CurY, CurZ;

	int m_State;
	CLaserPara	m_GalvoPara;	
	HINSTANCE gLibRTC;

	double m_Scale;
	int	m_lasermode;
	
	double xyrotate;
	double xoffset, yoffset;
	double xcor, ycor;
	bool bFlipx, bFlipy;
	
	double xhome, yhome;

	bool m_bVarPolyDelay;
	////
	CString m_prgmfile;
	CString m_corfile;	
	CString m_powercurvefile;
	CString m_varpolyfile;
	
	CList <PowerVolt, PowerVolt&> PowerCurve;

	/////////////////////////////////
//	CCriticalSection m_critcalSec;
//protected:
	//recorded

	//////////////////////////////////////////////////////////////////////////
	//All list command
	virtual void WaitForListSpace(int iGap)=0;
	///	
	virtual void SetLaserDelays(double dlaserondelay, double dlaseroffdelay)=0;		//laser on and off delays
	virtual void SetScannerDelay(double dmarkdelay, double djumpdelay, double dpolygondelay)=0;	//jump,mark and polygon delays
	virtual void SetJumpSpeed(double djumpspeed)=0;
	virtual void SetMarkSpeed(double dmarkspeed)=0;
	virtual void SetLaserPara(double dfreq, double dpulsewidth)=0; 		//freq, p
	virtual void SetWobbel(double dampl, double dfreq)=0;
	virtual void SPoint(double dx, double dy, double dz, double dtime)=0;
	///	
	virtual void SMarkTo(double dx, double dy)=0;
	virtual void SJumpTo(double dx, double dy)=0;
	virtual void SArcTo(double dx, double dy, double dangle)=0;
	virtual void SMark3DTo(double dx, double dy, double dz)=0;
	virtual void SJump3DTo(double dx, double dy, double dz)=0;
	virtual void SArc3DTo(double dx, double dy, double dz, double dangle)=0;
	virtual void SMarkRelTo(double dx, double dy)=0;
	virtual void SJumpRelTo(double dx, double dy)=0;	
	virtual void SArcRelTo(double dx, double dy, double dangle)=0;
	virtual void SMark3DRelTo(double dx, double dy, double dz)=0;
	virtual void SJump3DRelTo(double dx, double dy, double dz)=0;
	virtual void SArc3DRelTo(double dx, double dy, double dz, double dangle)=0;
		///	
	virtual void SParaMarkTo(double dx, double dy, double dpara)=0;
	virtual void SParaJumpTo(double dx, double dy, double dpara)=0;
	virtual void SParaMark3DTo(double dx, double dy, double dz, double dpara)=0;
	virtual void SParaJump3DTo(double dx, double dy, double dz, double dpara)=0;

//	virtual void SetAutoSpeedPosCtrl()=0;	
	virtual void SetAutoLaserParaList()=0;
	virtual void SetAutoVectorCtrl(int ictrl, double dvalue)=0;
			
	//microvector
	virtual void SMicroVector(double dx, double dy, double laseron, double laseroff)=0;
	virtual void SMicroVector3D(double dx, double dy, double dz, double laseron, double laseroff)=0;
	virtual void SMicroVectorRel(double dx, double dy, double laseron, double laseroff)=0;
	virtual void SMicroVectorRel3D(double dx, double dy, double dz, double laseron, double laseroff)=0;
	//Bitmap
	virtual void SSetZPosition(double dz)=0;	
	virtual void SSetPixelLine(int ichanel, double dperiod, double dx, double dy, double dz=0)=0;
	virtual void SSetPixel(double dpulsewidth, double dvoltage, int npixel=1)=0;
	
	//LaserControl
	virtual void SSetLaserOnList(double dt)=0;
	virtual void SSetDelayOnList(double dt)=0;
	//	SAnologOut1List,// power
	virtual void SSetAnologOut1(double dvoltage)=0; 
	virtual void SSetLongDelay(double dt)=0;

	//SkyWriting
	virtual void SSetSkyWritingMode(int imode)=0;
	virtual void SSetSkyWritingPara(double dtimeleg, double dlaseronshift, double nprev, double npost)=0;
		//
	virtual void SListContinue()=0;
	virtual void SSetFirstKiller(double dlength)=0;

};

#endif // !defined(AFX_SCANNER_H__08060DB8_7C71_4634_AC7C_EBF518F0DE9D__INCLUDED_)
