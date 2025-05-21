// stdafx.cpp : source file that includes just the standard includes
//	GalvoControl.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include "resource.h"
#include "math.h"

void DrawNumber(CEdit* edit, double dNumber, int iPlaces)
{
	CString csFormat;
	CString csTemp;
	
	if(fabs(dNumber)<0.00001 && iPlaces >0)
	{
		dNumber=0;
		iPlaces=1;
	}
	
	csFormat.Format("%%0.%dlf", iPlaces);
	csTemp.Format(csFormat, dNumber);
	
	edit->SetWindowText(csTemp);
}

void DrawNumber(CEdit* edit, int iNumber)
{
	CString csTemp;	
	
	csTemp.Format("%d", iNumber);
	edit->SetWindowText(csTemp);
}

double GetNumber(CEdit* edit)
{
	CString csTemp;
	
	edit->GetWindowText(csTemp);
	
	return  atof(csTemp);
}
