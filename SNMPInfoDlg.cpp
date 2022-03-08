// SNMPInfoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TestDlg.h"
#include "SNMPInfoDlg.h"


// CSNMPInfoDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSNMPInfoDlg, CDialog)

CSNMPInfoDlg::CSNMPInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSNMPInfoDlg::IDD, pParent)
{

}

CSNMPInfoDlg::~CSNMPInfoDlg()
{
}

void CSNMPInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SNMP_ENABLE, m_cbSNMPEnable);
	DDX_Control(pDX, IDC_COMBO_CST_ENABLE, m_cbCstEnable);
	DDX_Control(pDX, IDC_IPADDRESS_CST, m_ipctrlCst);
	DDX_Control(pDX, IDC_BUTTON_MODIFY, m_btnModify);
}


BEGIN_MESSAGE_MAP(CSNMPInfoDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CSNMPInfoDlg::OnBnClickedButtonModify)
	ON_CBN_SELCHANGE(IDC_COMBO_SNMP_ENABLE, &CSNMPInfoDlg::OnCbnSelchangeComboSnmpEnable)
	ON_CBN_SELCHANGE(IDC_COMBO_CST_ENABLE, &CSNMPInfoDlg::OnCbnSelchangeComboCstEnable)
END_MESSAGE_MAP()


// CSNMPInfoDlg 메시지 처리기입니다.


BOOL CSNMPInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitSNMP();

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CSNMPInfoDlg::InitSNMP()
{
	m_cbSNMPEnable.AddString(_T("disable"));
	m_cbSNMPEnable.AddString(_T("enable"));

	m_cbCstEnable.AddString(_T("disable"));
	m_cbCstEnable.AddString(_T("enable"));

	BOOL bEnabled = FALSE;
	BOOL bCstEnable = FALSE;
	CHAR szCstIP[16] = {NULL, };
	long ret = SPIDER_GetSNMP(theApp.m_hSelectCamera, &bEnabled, &bCstEnable, szCstIP);
	if (ret == E_CTRL_OK) {
		m_cbSNMPEnable.SetCurSel(bEnabled ? 1:0);
		m_cbCstEnable.SetCurSel(bCstEnable ? 1:0);
		USES_CONVERSION;
		CString strIP = A2T(szCstIP);
		m_ipctrlCst.SetWindowText(strIP);
		OnCbnSelchangeComboSnmpEnable();
	} else {
		m_cbSNMPEnable.EnableWindow(FALSE);
		m_cbCstEnable.EnableWindow(FALSE);
		m_ipctrlCst.EnableWindow(FALSE);
		m_btnModify.EnableWindow(FALSE);
	}
}

void CSNMPInfoDlg::OnBnClickedButtonModify()
{
	int nSelSNMPEnable	= m_cbSNMPEnable.GetCurSel();
	int nSelCstEnable	= m_cbCstEnable.GetCurSel();
	if (nSelSNMPEnable != -1 && nSelCstEnable != -1) {
		CString strIP = _T("");
		m_ipctrlCst.GetWindowText(strIP);
		USES_CONVERSION;
		PCHAR pszCstIP = T2A(strIP.GetBuffer(0));
		long nlRet = SPIDER_SetSNMP(theApp.m_hSelectCamera, 
								   (nSelSNMPEnable == 1) ? TRUE:FALSE, 
								   (nSelCstEnable == 1) ? TRUE:FALSE, 
								   pszCstIP);
		if (nlRet != E_CTRL_OK) {
			MessageBox(GetErrorString(nlRet), _T("Fail"));
		} else {
			MessageBox(_T("Success."));
			OnOK();
		}
	}
}


void CSNMPInfoDlg::OnCbnSelchangeComboSnmpEnable()
{
	int nSel = m_cbSNMPEnable.GetCurSel();
	m_cbCstEnable.EnableWindow((nSel == 1) ? TRUE:FALSE);
	if (nSel == 1) {
		OnCbnSelchangeComboCstEnable();
	} else {
		m_ipctrlCst.EnableWindow(FALSE);
	}
}


void CSNMPInfoDlg::OnCbnSelchangeComboCstEnable()
{
	int nSel = m_cbCstEnable.GetCurSel();
	m_ipctrlCst.EnableWindow((nSel == 1) ? TRUE:FALSE);
}
