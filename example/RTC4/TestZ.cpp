// TestZ.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "TestZ.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestZ dialog


CTestZ::CTestZ(CWnd* pParent /*=NULL*/)
	: CDialog(CTestZ::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestZ)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTestZ::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestZ)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestZ, CDialog)
	//{{AFX_MSG_MAP(CTestZ)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestZ message handlers
