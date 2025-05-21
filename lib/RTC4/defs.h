
#if !defined(AFX_SCANNER_H__08060DB8_7C71_4634_AC7C_EBF518F0DE9D__INCLUDED_4)
#define AFX_SCANNER_H__08060DB8_7C71_4634_AC7C_EBF518F0DE9D__INCLUDED_4



#if _MSC_VER > 1000
 #pragma once
#endif // _MSC_VER > 1000

#include "afxtempl.h"

#define MaxBitRTC (1048576/16)
#define LASERCONTROL 0x00
#define MaxListCMD	4000
#define PI	3.14159265359

#define WM_SCANPOS_MESSAGE				(WM_USER+110)
#define WM_FABPOS_MESSAGE				(WM_USER+111)
#define WM_PROCESSFILEFINISH_MESSAGE	(WM_USER+112)
#define WM_AXISPOS_MESSAGE				(WM_USER+113)

#define WP_UPDATEALL	1
#define WP_UPDATEVIEW	2
#define WP_UPDATEPROP	3
#define WP_UPDATETREE	4

#define MAIN_STATE_OK				0
#define MAIN_STATE_ERROR_RTC		1	
#define MAIN_STATE_ERROR_LASER		2	

//Scanner states
#define DEVICE_STATE_NOT_INSTALLED	 0
#define DEVICE_STATE_NOT_INITIALIZED 1
#define DEVICE_STATE_ERROR			 2
#define DEVICE_STATE_BUSY			 3
#define DEVICE_STATE_OK			 	 4


#define SAFE_DELETE_ARRAY(Pointer)		{if (Pointer != NULL) delete [] Pointer; Pointer = NULL;}
#define SAFE_CLOSEHANDLE(Handle)		{if ((Handle!=0) && (Handle != INVALID_HANDLE_VALUE)) CloseHandle(Handle); Handle = INVALID_HANDLE_VALUE;}
#define CNT_ELEMENTS(pElements)			(sizeof(pElements) / sizeof(pElements[0]))

/*
enum ScannerCMD{

	///	
	SetLaserDelays,		//laser on and off delays
	SetScannerDelay,	//jump,mark and polygon delays
	SetJumpSpeed,
	SetMarkSpeed,
	SetLaserPara,		//freq, p
	SetWobbel,
	SPoint,
	///	
	SMarkTo,
	SJumpTo,
	SArcTo,	
	SMark3DTo,
	SJump3DTo,
	SArc3DTo,
	SMarkRelTo,
	SJumpRelTo,	
	SArcRelTo,
	SMark3DRelTo,
	SJump3DRelTo,
	SArc3DRelTo,
	///	
	SParaMarkTo,
	SParaJumpTo,
	SParaMark3DTo,
	SParaJump3DTo,
	//microvector
	SMicroVector,
	SMicroVector3D,
	SMicroVectorRel,
	SMicroVectorRel3D,
	//Bitmap
	SZPosition,	
	SSetPixelLine,
	SSetPixel,
	SSetNPixel,
	//LaserControl
	SLaserOnList,
	SDelayOnList,
//	SAnologOut1List,// power
	SAnologOut1, 
	SLongDelay,
	SSetAutoLaserPara,
	SSetAutoVectorCtrl,	

	//SkyWriting
	SSetSkyWritingMode,
	SSetSkyWritingPara,
	//
	SListContinue,
	SSetFirstKiller,
};
*/
enum DriverCard{
	CardNULL,
	cardRTC4,
	cardRTC5,
	cardRTC6,
	cardPMC2,
};


#define PreViewJpSpeed  1000
#define PreViewSpeed	1000 

typedef struct _tagGALVOPARA{	
	float	m_xyfactor;
	float	m_zfactor;
	float	m_offsetx;
	float	m_offsety;
	float	m_rotationangle;
	float	m_zoom;
	float	m_zA;
	float	m_zB;
	float	m_zC;
	int m_lasermode;
}GalvoData;

typedef struct _tagSCANPIXELPARA{
	unsigned short pixel_mode;
	unsigned short pixel_period;
	unsigned short pixel_dx;
	unsigned short pixel_dy;

	unsigned short pulse_width;
	unsigned short da_value;
	unsigned short channel;	
}PixelData;


typedef struct _tagPOWERCURVE{

	double dPower;
	double dVolt;
}PowerVolt;


enum FILLType{
	NONFill,	
	CRECTFill,
	CPARAFill,
	CTRIFill,
	BitmapPulseFill,
	BitmapJumpFill,
	BitmapLineFill,	
};

class AFX_EXT_CLASS CLaserPara
{
public:	
	void Serialize(CArchive &ar);
	CLaserPara();

	void SetPara(CLaserPara* pPara);
	void SetMarkPara(CLaserPara* pPara);
	void SetDelayPara(CLaserPara* pPara);
	void IsEqual(CLaserPara* pLaserPara);	

	//skywriting setting
	int m_iSkywritingMode;
	double m_dSkywritingTimeleg;
	double m_dSkywritingLaserOnShift;
	double m_dSkywritingNprev;
	double m_dSkywritingNpost;

	//////	
	BOOL m_bVectorDepend;
	int m_iVectorDependCtrl;
	double m_dVectorDependValue;

	/////////
	double m_dPower;	
	double m_dMarkSpeed;
	double m_dJumpSpeed;

	double m_dFrequency;
	double m_dPulseWidth;
		
	double m_dWobelAmpl;
	double m_dWobelFreq;

	double m_dPolygonDelay;
	double m_dMarkDelay;
	double m_dJumpDelay;
		
	double m_dLaserOnDelay;
	double m_dLaserOffDelay;
	
	virtual ~CLaserPara();
};


//typedef CList<CString, CString&> CMyCmdList;


#endif 
// !defined(AFX_GALVOSETTINGS_H__5FD94C31_2552_414E_9C4C_E085E12470EC__INCLUDED_4)