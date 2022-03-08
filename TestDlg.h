
// SetupDlg.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTestDlgApp:
// See TestDlg.cpp for the implementation of this class
//

#define MAX_CAMERA 8

class CTestDlgApp : public CWinApp
{
public:
	CTestDlgApp();

// Overrides
	public:
	virtual BOOL InitInstance();


	HCAMERA		m_hSelectCamera;
	HCAMERA		m_allCamera[MAX_CAMERA];  //skpark in your area



// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CTestDlgApp theApp;




void _VALID_WND_WITH_VAL(CWnd* pWnd, USHORT usval, CString& sztext);
void _VALID_WND_WITH_VAL(CWnd* pWnd, ULONG ulval, CString& sztext);
void _VALID_WND_WITH_VAL(CWnd* pWnd, int ival, CString& sztext);
void _VALID_WND_WITH_VAL(CWnd* pWnd, char* szval, CString& sztext);
void _VALID_WND_WITH_VAL(CComboBox& Wnd, USHORT usval, bool bCompareItemData);
void _VALID_WND_WITH_VAL(CWnd* pWnd, float usval, CString& sztext);
