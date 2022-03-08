// DynamicDNSInfoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TestDlg.h"
#include "DynamicDNSInfoDlg.h"


// CDynamicDNSInfoDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDynamicDNSInfoDlg, CDialog)

CDynamicDNSInfoDlg::CDynamicDNSInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDynamicDNSInfoDlg::IDD, pParent)
	, m_strHostName(_T(""))
	, m_strUserName(_T(""))
	, m_strPwd(_T(""))
	, m_strHashCode(_T(""))
	, m_nlPeriod(0)
{

}

CDynamicDNSInfoDlg::~CDynamicDNSInfoDlg()
{
}

void CDynamicDNSInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ENABLE, m_cbEnable);
	DDX_Control(pDX, IDC_COMBO_SVC_NAME, m_cbDNSSvcName);
	DDX_Control(pDX, IDC_EDIT_HOST_NAME, m_edtHostName);
	DDX_Control(pDX, IDC_EDIT_USER_NAME, m_edtUserName);
	DDX_Control(pDX, IDC_EDIT_PWD, m_edtPwd);
	DDX_Control(pDX, IDC_EDIT_HASH_CODE, m_edtHashCode);
	DDX_Control(pDX, IDC_EDIT_PERIOD, m_edtPeriod);
	DDX_Control(pDX, IDC_BUTTON_INPUT_MODIFY, m_edtModify);
	DDX_Text(pDX, IDC_EDIT_HOST_NAME, m_strHostName);
	DDV_MaxChars(pDX, m_strHostName, 31);
	DDX_Text(pDX, IDC_EDIT_USER_NAME, m_strUserName);
	DDV_MaxChars(pDX, m_strUserName, 15);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strPwd);
	DDV_MaxChars(pDX, m_strPwd, 15);
	DDX_Text(pDX, IDC_EDIT_HASH_CODE, m_strHashCode);
	DDV_MaxChars(pDX, m_strHashCode, 127);
	DDX_Text(pDX, IDC_EDIT_PERIOD, m_nlPeriod);
	DDV_MinMaxLong(pDX, m_nlPeriod, 10, 86400);
}


BEGIN_MESSAGE_MAP(CDynamicDNSInfoDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_INPUT_MODIFY, &CDynamicDNSInfoDlg::OnBnClickedButtonInputModify)
	ON_CBN_SELCHANGE(IDC_COMBO_ENABLE, &CDynamicDNSInfoDlg::OnCbnSelchangeComboEnable)
END_MESSAGE_MAP()


// CDynamicDNSInfoDlg 메시지 처리기입니다.


BOOL CDynamicDNSInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitDDNS();

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CDynamicDNSInfoDlg::InitDDNS()
{
	m_cbEnable.AddString(_T("disable"));
	m_cbEnable.AddString(_T("enable"));

	m_cbDNSSvcName.AddString(_T("freedns.afraid.org"));
	m_cbDNSSvcName.AddString(_T("dyndns.org"));
	m_cbDNSSvcName.AddString(_T("zoneeidt.com"));
	m_cbDNSSvcName.AddString(_T("no_ip.com"));

	ST_SPIDER_CUSTOM_DDNS stInfo = {NULL, };
	long ret = SPIDER_GetDDNS(theApp.m_hSelectCamera, &stInfo);
	if (ret == E_CTRL_OK) {
		m_cbEnable.SetCurSel(stInfo.bEnabled ? 1:0);
		int nSel = -1;
		switch (stInfo.dnsName) {
		case FREEDNS:	nSel = 0; break;
		case DYNDNS:	nSel = 1; break;
		case ZONEEIDT:	nSel = 2; break;
		case NOIP:		nSel = 3; break;
		}
		m_cbDNSSvcName.SetCurSel(nSel);
		
		USES_CONVERSION;
		m_strHostName	= A2T(stInfo.strHostName);
		m_strUserName	= A2T(stInfo.strUserName);
		m_strPwd		= A2T(stInfo.strUserPwd);
		m_strHashCode	= A2T(stInfo.strHashCode);
		m_nlPeriod		= stInfo.nUpdatePeriod;
		UpdateData(FALSE);
		OnCbnSelchangeComboEnable();
	} else {
		m_cbEnable.EnableWindow(FALSE);
		m_cbDNSSvcName.EnableWindow(FALSE);
		m_edtHostName.EnableWindow(FALSE);
		m_edtUserName.EnableWindow(FALSE);
		m_edtPwd.EnableWindow(FALSE);
		m_edtHashCode.EnableWindow(FALSE);
		m_edtPeriod.EnableWindow(FALSE);
		m_edtModify.EnableWindow(FALSE);
	}
}

void CDynamicDNSInfoDlg::OnBnClickedButtonInputModify()
{
	UpdateData();

	ST_SPIDER_CUSTOM_DDNS stInfo = {NULL, };
	stInfo.bEnabled = (m_cbEnable.GetCurSel() == 1) ? TRUE:FALSE;
	
	int nSel = m_cbDNSSvcName.GetCurSel();
	switch (nSel) {
	case 0: stInfo.dnsName = FREEDNS;	break;
	case 1: stInfo.dnsName = DYNDNS;	break;
	case 2: stInfo.dnsName = ZONEEIDT;	break;
	case 3: stInfo.dnsName = NOIP;		break;
	}

	USES_CONVERSION;
	strcpy(stInfo.strHostName, T2A(m_strHostName.GetBuffer(0)));
	strcpy(stInfo.strUserName, T2A(m_strUserName.GetBuffer(0)));
	strcpy(stInfo.strUserPwd, T2A(m_strPwd.GetBuffer(0)));
	strcpy(stInfo.strHashCode, T2A(m_strHashCode.GetBuffer(0)));
	stInfo.nUpdatePeriod = m_nlPeriod;
	
	long nlRet = SPIDER_SetDDNS(theApp.m_hSelectCamera, stInfo);
	if (nlRet != E_CTRL_OK) {
		MessageBox(GetErrorString(nlRet), _T("Fail"));
	} else {
		MessageBox(_T("Success."));
		OnOK();
	}
}


void CDynamicDNSInfoDlg::OnCbnSelchangeComboEnable()
{
	int nSel = m_cbEnable.GetCurSel();
	m_cbDNSSvcName.EnableWindow((nSel == 1) ? TRUE:FALSE);
	m_edtHostName.EnableWindow((nSel == 1) ? TRUE:FALSE);
	m_edtUserName.EnableWindow((nSel == 1) ? TRUE:FALSE);
	m_edtPwd.EnableWindow((nSel == 1) ? TRUE:FALSE);
	m_edtHashCode.EnableWindow((nSel == 1) ? TRUE:FALSE);
	m_edtPeriod.EnableWindow((nSel == 1) ? TRUE:FALSE);
}
