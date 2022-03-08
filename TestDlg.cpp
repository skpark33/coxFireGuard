
// TestDlg.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TestDlg.h"
#include "TestDlgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestDlgApp

BEGIN_MESSAGE_MAP(CTestDlgApp, CWinApp)
END_MESSAGE_MAP()


// CTestDlgApp construction

CTestDlgApp::CTestDlgApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance

	m_hSelectCamera = NULL;
}


// The one and only CTestDlgApp object

CTestDlgApp theApp;


// CTestDlgApp initialization

BOOL CTestDlgApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T(""));


	SPIDER_InitStreaming();

	for (int i = 0; i < MAX_CAMERA; i++)
	{
		m_allCamera[i] = NULL;
	}


	CTestDlgDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}



	if(dlg.m_hDiscoveryEvent)
	{
		SPIDER_UninitDiscovery();
		dlg.m_hDiscoveryEvent = 0;
	}

	if(m_hSelectCamera)
	{
		SPIDER_DestroyCameraHandle(m_hSelectCamera);
		m_hSelectCamera = NULL;
	}

	for (int i = 0; i < MAX_CAMERA; i++) 
	{
		if (m_allCamera[i])
		{
			SPIDER_DestroyCameraHandle(m_allCamera[i]);
			m_allCamera[i] = NULL;
		}
	}

	if(dlg.m_hTrigger)
	{
		SPIDER_StopTriggerServer(dlg.m_hTrigger);
		dlg.m_hTrigger = NULL;
	}

	if(dlg.m_bInitTriggerServer)
	{
		SPIDER_UninitTriggerServer();
		dlg.m_bInitTriggerServer = false;
	}




	if(dlg.m_hSyslog)
	{
		SPIDER_StopSyslogServer(dlg.m_hSyslog);
		dlg.m_hSyslog = NULL;
	}

	if(dlg.m_bInitSyslogServer)
	{
		SPIDER_UninitSyslogServer();
		dlg.m_bInitSyslogServer = false;
	}






	SPIDER_UninitStreaming();


	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


void _VALID_WND_WITH_VAL(CWnd* pWnd, int ival, CString& sztext)
{
	if(pWnd)
	{
		if(ival >= 0xFFFFFFFF
		|| ival == 0xFFFF)
		{
			pWnd->SetWindowText((""));
			pWnd->EnableWindow(false);
		}
		else
		{
			sztext.Format(("%d"), ival);
			pWnd->SetWindowText(sztext);
			pWnd->EnableWindow(true);
		}
	}
}

void _VALID_WND_WITH_VAL(CWnd* pWnd, ULONG ulval, CString& sztext)
{
	if(pWnd)
	{
		if(ulval >= 0xFFFFFFFF
		|| ulval == 0xFFFF)
		{
			pWnd->SetWindowText((""));
			pWnd->EnableWindow(false);
		}
		else
		{
			sztext.Format(("%d"), ulval);
			pWnd->SetWindowText(sztext);
			pWnd->EnableWindow(true);
		}
	}
}

void _VALID_WND_WITH_VAL(CWnd* pWnd, USHORT usval, CString& sztext)
{
	if(pWnd)
	{
		if(usval >= 0xFFFF)
		{
			pWnd->SetWindowText((""));
			pWnd->EnableWindow(false);
		}
		else
		{
			sztext.Format(("%d"), usval);
			pWnd->SetWindowText(sztext);
			pWnd->EnableWindow(true);
		}
	}
}


void _VALID_WND_WITH_VAL(CWnd* pWnd, float usval, CString& sztext)
{
	if(pWnd)
	{
		if(usval >= 0xFFFF)
		{
			pWnd->SetWindowText((""));
			pWnd->EnableWindow(false);
		}
		else
		{
			sztext.Format(("%.2f"), usval);
			pWnd->SetWindowText(sztext);
			pWnd->EnableWindow(true);
		}
	}
}

void _VALID_WND_WITH_VAL(CWnd* pWnd, char* szval, CString& sztext)
{
	if(pWnd)
	{
		if(szval == NULL)
		{
			pWnd->SetWindowText((""));
			pWnd->EnableWindow(false);
		}
		else if(strcmp(szval, "NA") ==0)
		{
			pWnd->SetWindowText((""));
			pWnd->EnableWindow(false);
		}
		else
		{
			sztext = szval;
			pWnd->SetWindowText(sztext);
			pWnd->EnableWindow(true);
		}
	}
}

void _VALID_WND_WITH_VAL(CComboBox& Wnd, USHORT usval, bool bCompareItemData)
{
	if(Wnd.GetSafeHwnd())
	{
		if(bCompareItemData)
		{
			for(int i = 0; i < Wnd.GetCount(); i++)
			{
				if(Wnd.GetItemData(i) == usval)
				{
					Wnd.SetCurSel(i);
					Wnd.EnableWindow(true);
					return;
				}
			}

			Wnd.SetCurSel(0);
			Wnd.EnableWindow(false);
		}
		else
		{
			if(usval >= 0xFFFF)
			{
				Wnd.SetCurSel(0);
				Wnd.EnableWindow(false);
			}
			else if(usval >= Wnd.GetCount())
			{
				Wnd.SetCurSel(0);
				Wnd.EnableWindow(false);
			}
			else
			{
				Wnd.SetCurSel(usval);
				Wnd.EnableWindow(true);
			}
		}
	}
}
