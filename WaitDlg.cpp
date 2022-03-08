// WaitDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDlg.h"
#include "WaitDlg.h"


#define TIMER_DOT		5478

// CWaitDlg dialog

IMPLEMENT_DYNAMIC(CWaitDlg, CDialog)

CWaitDlg::CWaitDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWaitDlg::IDD, pParent)
{
	m_hEvent_InitDlg = NULL;
}

CWaitDlg::~CWaitDlg()
{
}

void CWaitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWaitDlg, CDialog)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CWaitDlg message handlers

BOOL CWaitDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	SetTimer(TIMER_DOT, 500, NULL);

	if(m_hEvent_InitDlg)
		SetEvent(m_hEvent_InitDlg);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CWaitDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent == TIMER_DOT)
	{
		if(m_szDot.GetLength() > 30)
			m_szDot = "..";

		m_szDot += ".";
		GetDlgItem(IDC_STATIC_DOT)->SetWindowText(m_szDot);
	}
	else if(nIDEvent == TIMER_CLOSE)
	{
		KillTimer(TIMER_CLOSE);

		EndDialog(IDOK);
	}

	CDialog::OnTimer(nIDEvent);
}

void CWaitDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	KillTimer(TIMER_DOT);


	if(m_hEvent_InitDlg)
		CloseHandle(m_hEvent_InitDlg);
	m_hEvent_InitDlg = NULL;

	CDialog::OnOK();
}
