// DeviceInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDlg.h"
#include "DeviceInfoDlg.h"
#include "TestDlgDlg.h"



// CDeviceInfoDlg dialog

IMPLEMENT_DYNCREATE(CDeviceInfoDlg, CDialog)

CDeviceInfoDlg::CDeviceInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeviceInfoDlg::IDD, pParent)
{

}

CDeviceInfoDlg::~CDeviceInfoDlg()
{
}

void CDeviceInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL CDeviceInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();



	long lret = SPIDER_GetDeviceInfo(theApp.m_hSelectCamera, &m_stInfo);
	if(lret != E_CTRL_OK)
	{
		MessageBox(GetErrorString(lret), ("Fail"));
	}
	else
	{
		CString sztext;

		sztext = m_stInfo.device_name;
		GetDlgItem(IDC_EDIT_NAME)->SetWindowText(sztext);

		sztext = m_stInfo.device_id;
		GetDlgItem(IDC_EDIT_ID)->SetWindowText(sztext);

		sztext = m_stInfo.model_name;
		GetDlgItem(IDC_EDIT_MODEL)->SetWindowText(sztext);

		sztext = m_stInfo.serial_number;
		GetDlgItem(IDC_EDIT_SERIALNUMBER)->SetWindowText(sztext);

		sztext = m_stInfo.mac_address;
		GetDlgItem(IDC_EDIT_MACADDRESS)->SetWindowText(sztext);

		sztext = m_stInfo.firmware_version;
		GetDlgItem(IDC_EDIT_FIRMWAREVERSION)->SetWindowText(sztext);
	}


	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CDeviceInfoDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CDeviceInfoDlg::OnBnClickedButtonModify)
END_MESSAGE_MAP()

// CDeviceInfoDlg message handlers

void CDeviceInfoDlg::OnBnClickedButtonModify()
{
	// TODO: Add your control notification handler code here
	CString sztext;

	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(sztext);
	StringCopyTo(sztext.GetBuffer(), m_stInfo.device_name);
	sztext.ReleaseBuffer();


	long lret = SPIDER_SetDeviceName(theApp.m_hSelectCamera, m_stInfo.device_name, strlen(m_stInfo.device_name));
	if(lret != E_CTRL_OK)
	{
		MessageBox(GetErrorString(lret), ("Fail"));
	}
	else
	{
		MessageBox(("Success!"));
	}
}
