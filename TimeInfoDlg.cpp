// TimeInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDlg.h"
#include "TimeInfoDlg.h"


// CTimeInfoDlg dialog

IMPLEMENT_DYNCREATE(CTimeInfoDlg, CDialog)

CTimeInfoDlg::CTimeInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTimeInfoDlg::IDD, pParent)
{

}

CTimeInfoDlg::~CTimeInfoDlg()
{
}

void CTimeInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TIME_MODE, m_Combo_TimeMode);
	DDX_Control(pDX, IDC_LIST_NTP_SERVER, m_List_NTPServer);
	DDX_Control(pDX, IDC_COMBO_FORMAT_TYPE, m_Combo_NTPServerFormatType);
}

BOOL CTimeInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

		

	m_Combo_TimeMode.ResetContent();
	m_Combo_TimeMode.AddString(("NTP"));
	m_Combo_TimeMode.AddString(("Manual"));
	m_Combo_TimeMode.SetCurSel(0);



	int ncol = 0;
	m_List_NTPServer.SetExtendedStyle( m_List_NTPServer.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	m_List_NTPServer.InsertColumn(ncol++, ("index"), 0, 50);
	m_List_NTPServer.InsertColumn(ncol++, ("ID"), 0, 50);
	m_List_NTPServer.InsertColumn(ncol++, ("Port"), 0, 50);
	m_List_NTPServer.InsertColumn(ncol++, ("Address"), 0, 180);




	m_Combo_NTPServerFormatType.ResetContent();
	m_Combo_NTPServerFormatType.AddString(("IP Address"));
	m_Combo_NTPServerFormatType.AddString(("Host Name"));
	m_Combo_NTPServerFormatType.SetCurSel(0);



	InitInfo();


	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CTimeInfoDlg, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_LIST_NTP_SERVER, &CTimeInfoDlg::OnNMClickListNtpServer)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_NTP_SERVER, &CTimeInfoDlg::OnLvnItemchangedListNtpServer)
	ON_BN_CLICKED(IDC_BUTTON_TIME_MODIFY, &CTimeInfoDlg::OnBnClickedButtonTimeModify)
	ON_BN_CLICKED(IDC_BUTTON_NTP_MODIFY, &CTimeInfoDlg::OnBnClickedButtonNtpModify)
	ON_BN_CLICKED(IDC_BUTTON_NTP_ADD, &CTimeInfoDlg::OnBnClickedButtonNtpAdd)
	ON_BN_CLICKED(IDC_BUTTON_NTP_DELETE, &CTimeInfoDlg::OnBnClickedButtonNtpDelete)
END_MESSAGE_MAP()

// CTimeInfoDlg message handlers


void CTimeInfoDlg::OnNMClickListNtpServer(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE*>(pNMHDR);
	// TODO: Add your control notification handler code here

	DisplayInfo();

	*pResult = 0;
}

void CTimeInfoDlg::DisplayInfo()
{
	int nSel = m_List_NTPServer.GetSelectionMark();

	if(nSel != -1 && nSel < m_vInfo.size())
	{
		ST_SPIDER_TIME_NTPSERVER_INFO stNTP = m_vInfo.at(nSel);

		CString sztext;

		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_NTP_SERVER_ID), stNTP.strID, sztext);
			//XPM_ADDRESS_FORMAT_TYPE_IPADDR = 0,
			//XPM_ADDRESS_FORMAT_TYPE_HOSTNAME 
		_VALID_WND_WITH_VAL(m_Combo_NTPServerFormatType, stNTP.nsFormatType, NULL);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_NTP_SERVER_PORT), stNTP.nsPort, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_NTP_SERVER_HOST_NAME), stNTP.strHostName, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_IPADDRESS_NTP_SERVER), stNTP.strIpAddrV4, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_IPADDRESS_V6_NTP_SERVER), stNTP.strIpAddrV6, sztext);

		if(stNTP.nsFormatType == 0)
		{
			_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_NTP_SERVER_HOST_NAME), 0xFFFF, sztext);
			_VALID_WND_WITH_VAL(GetDlgItem(IDC_IPADDRESS_NTP_SERVER), stNTP.strIpAddrV4, sztext);
			_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_IPADDRESS_V6_NTP_SERVER), stNTP.strIpAddrV6, sztext);
		}
		else if(stNTP.nsFormatType == 1)
		{
			_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_NTP_SERVER_HOST_NAME), stNTP.strHostName, sztext);
			_VALID_WND_WITH_VAL(GetDlgItem(IDC_IPADDRESS_NTP_SERVER), 0xFFFF, sztext);
			_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_IPADDRESS_V6_NTP_SERVER), 0xFFFF, sztext);
		}
		else
		{
			_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_NTP_SERVER_HOST_NAME), 0xFFFF, sztext);
			_VALID_WND_WITH_VAL(GetDlgItem(IDC_IPADDRESS_NTP_SERVER), 0xFFFF, sztext);
			_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_IPADDRESS_V6_NTP_SERVER), 0xFFFF, sztext);
		}

		if(m_Combo_TimeMode.GetCurSel() == 1)	//manual
		{
			GetDlgItem(IDC_EDIT_NTP_SERVER_ID)->EnableWindow(false);
			m_Combo_NTPServerFormatType.EnableWindow(false);
			GetDlgItem(IDC_EDIT_NTP_SERVER_PORT)->EnableWindow(false);
			GetDlgItem(IDC_EDIT_NTP_SERVER_HOST_NAME)->EnableWindow(false);
			GetDlgItem(IDC_IPADDRESS_NTP_SERVER)->EnableWindow(false);
			GetDlgItem(IDC_EDIT_IPADDRESS_V6_NTP_SERVER)->EnableWindow(false);
		}
	}
}

void CTimeInfoDlg::InitInfo()
{


	m_vInfo.clear();

	long lret = SPIDER_GetTimeInfo(theApp.m_hSelectCamera, &m_stInfo);
	if(lret != E_CTRL_OK)
	{
		MessageBox(GetErrorString(lret), ("Fail"));
	}
	else
	{
		CString sztext;


		ST_SPIDER_TIME_INFO stTime = m_stInfo;

		_VALID_WND_WITH_VAL(m_Combo_TimeMode, stTime.nsTimeMode, NULL);

		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_LOCAL_TIME), stTime.strLocalTime, sztext);

		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_TIME_ZONE), stTime.strTimeZone, sztext);


		if(stTime.nsTimeMode == 0)
		{
			m_List_NTPServer.EnableWindow(true);
			GetDlgItem(IDC_BUTTON_NTP_ADD)->EnableWindow(true);
			GetDlgItem(IDC_BUTTON_NTP_DELETE)->EnableWindow(true);
			GetDlgItem(IDC_BUTTON_NTP_MODIFY)->EnableWindow(true);

			GetDlgItem(IDC_EDIT_NTP_SERVER_PORT)->EnableWindow(true);		
		}
		else if(stTime.nsTimeMode == 1)
		{
			m_List_NTPServer.EnableWindow(false);
			GetDlgItem(IDC_BUTTON_NTP_ADD)->EnableWindow(false);
			GetDlgItem(IDC_BUTTON_NTP_DELETE)->EnableWindow(false);
			GetDlgItem(IDC_BUTTON_NTP_MODIFY)->EnableWindow(false);

			GetDlgItem(IDC_EDIT_NTP_SERVER_PORT)->EnableWindow(false);
			GetDlgItem(IDC_EDIT_NTP_SERVER_HOST_NAME)->EnableWindow(false);
			_VALID_WND_WITH_VAL(m_Combo_NTPServerFormatType, 0xFFFF, NULL);
		}
		else
		{
			m_List_NTPServer.EnableWindow(false);
			GetDlgItem(IDC_BUTTON_NTP_ADD)->EnableWindow(false);
			GetDlgItem(IDC_BUTTON_NTP_DELETE)->EnableWindow(false);
			GetDlgItem(IDC_BUTTON_NTP_MODIFY)->EnableWindow(false);

			GetDlgItem(IDC_EDIT_NTP_SERVER_PORT)->EnableWindow(false);
			GetDlgItem(IDC_EDIT_NTP_SERVER_HOST_NAME)->EnableWindow(false);
			_VALID_WND_WITH_VAL(m_Combo_NTPServerFormatType, 0xFFFF, NULL);
		}




		m_List_NTPServer.DeleteAllItems();

		m_vInfo.clear();
		long nCount = SPIDER_GetTimeNTPServerCount(theApp.m_hSelectCamera);
		for(int i = 0; i < nCount; i++)
		{
			ST_SPIDER_TIME_NTPSERVER_INFO stInfo = {0};
			long lret = SPIDER_GetTimeNTPServerInfo(theApp.m_hSelectCamera, i, &stInfo);
			if(lret != E_CTRL_OK)
			{
				MessageBox(GetErrorString(lret), ("Fail"));
				break;
			}

			m_vInfo.push_back(stInfo);

	

			int nSubItem = 1;
			sztext.Format(("%d"), i+1);
			m_List_NTPServer.InsertItem(i, sztext);

			sztext = stInfo.strID;
			m_List_NTPServer.SetItemText(i, nSubItem++, sztext);

			if(stInfo.nsPort >= 0xFFFF)
				sztext = "";
			else
				sztext.Format(("%d"), stInfo.nsPort);
			m_List_NTPServer.SetItemText(i, nSubItem++, sztext);

			if(stInfo.nsFormatType == 0)
			{
				sztext = stInfo.strIpAddrV4;
				if(sztext.GetLength() < 1)
					sztext = stInfo.strIpAddrV6;
			}
			else if(stInfo.nsFormatType == 1)
			{
				sztext = stInfo.strHostName;
			}
			else
				sztext = "";

			if(sztext.GetLength())
				m_List_NTPServer.SetItemText(i, nSubItem++, sztext);

		}

		m_List_NTPServer.SetSelectionMark(0);
		m_List_NTPServer.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);

		DisplayInfo();

	}
}

void CTimeInfoDlg::OnLvnItemchangedListNtpServer(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CTimeInfoDlg::OnBnClickedButtonTimeModify()
{
	ST_SPIDER_TIME_INFO stNew = m_stInfo;

	CString sztext;

	if(stNew.nsTimeMode != 0xFFFF && stNew.nsTimeMode != 0xFFFFFFFF)
		stNew.nsTimeMode = m_Combo_TimeMode.GetCurSel();

	GetDlgItem(IDC_EDIT_LOCAL_TIME)->GetWindowText(sztext);
	if(strcmp(stNew.strLocalTime, "NA"))
		StringCopyTo(sztext, stNew.strLocalTime);

	GetDlgItem(IDC_EDIT_TIME_ZONE)->GetWindowText(sztext);
	if(strcmp(stNew.strTimeZone, "NA"))
		StringCopyTo(sztext, stNew.strTimeZone);


	long lret = SPIDER_SetTimeInfo(theApp.m_hSelectCamera, stNew);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));
}

void CTimeInfoDlg::OnBnClickedButtonNtpModify()
{
	int nModifyIndex = m_List_NTPServer.GetSelectionMark();
	if(nModifyIndex >= m_vInfo.size())
		return;

	ST_SPIDER_TIME_NTPSERVER_INFO stNew = m_vInfo.at(nModifyIndex);

	CString sztext;

	if(stNew.nsFormatType != 0xFFFF && stNew.nsFormatType != 0xFFFFFFFF)
		stNew.nsFormatType = m_Combo_NTPServerFormatType.GetCurSel();


	int nValue = 0;
	GetDlgItem(IDC_EDIT_NTP_SERVER_PORT)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nsPort != 0xFFFF && stNew.nsPort != 0xFFFFFFFF)
		stNew.nsPort = nValue;

	GetDlgItem(IDC_EDIT_NTP_SERVER_HOST_NAME)->GetWindowText(sztext);
	if(strcmp(stNew.strHostName, "NA"))
		StringCopyTo(sztext, stNew.strHostName);

	GetDlgItem(IDC_IPADDRESS_NTP_SERVER)->GetWindowText(sztext);
	if(strcmp(stNew.strIpAddrV4, "NA"))
		StringCopyTo(sztext, stNew.strIpAddrV4);

	GetDlgItem(IDC_EDIT_IPADDRESS_V6_NTP_SERVER)->GetWindowText(sztext);
	if(strcmp(stNew.strIpAddrV6, "NA"))
		StringCopyTo(sztext, stNew.strIpAddrV6);


	long lret = SPIDER_SetTimeNTPServerInfo(theApp.m_hSelectCamera, stNew);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));


	InitInfo();
}

void CTimeInfoDlg::OnBnClickedButtonNtpAdd()
{
	// TODO: Add your control notification handler code here

	ST_SPIDER_TIME_NTPSERVER_INFO stNew = {0};

	if(m_vInfo.size())
		stNew = m_vInfo.at(0);

	//make new id
	bool bNext = true;
	int nID = 0;
	while(bNext == true)
	{
		sprintf(stNew.strID, "%d", nID);

		bNext = false;
		int nIndex = 0;
		while(nIndex < m_vInfo.size())
		{
			if(strcmp(stNew.strID, m_vInfo.at(nIndex).strID) == 0)
			{
				bNext = true;
				break;
			}

			nIndex++;
		}

		nID++;
	}


	CString sztext;

	if(stNew.nsFormatType != 0xFFFF && stNew.nsFormatType != 0xFFFFFFFF)
		stNew.nsFormatType = m_Combo_NTPServerFormatType.GetCurSel();


	int nValue = 0;
	GetDlgItem(IDC_EDIT_NTP_SERVER_PORT)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nsPort != 0xFFFF && stNew.nsPort != 0xFFFFFFFF)
		stNew.nsPort = nValue;

	GetDlgItem(IDC_EDIT_NTP_SERVER_HOST_NAME)->GetWindowText(sztext);
	if(strcmp(stNew.strHostName, "NA"))
		StringCopyTo(sztext, stNew.strHostName);

	GetDlgItem(IDC_IPADDRESS_NTP_SERVER)->GetWindowText(sztext);
	if(strcmp(stNew.strIpAddrV4, "NA"))
		StringCopyTo(sztext, stNew.strIpAddrV4);

	GetDlgItem(IDC_EDIT_IPADDRESS_V6_NTP_SERVER)->GetWindowText(sztext);
	if(strcmp(stNew.strIpAddrV6, "NA"))
		StringCopyTo(sztext, stNew.strIpAddrV6);


	long lret = SPIDER_AddTimeNTPServerInfo(theApp.m_hSelectCamera, stNew);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));


	InitInfo();
}

void CTimeInfoDlg::OnBnClickedButtonNtpDelete()
{
	// TODO: Add your control notification handler code here
	int nDeleteIndex = m_List_NTPServer.GetSelectionMark();
	if(nDeleteIndex >= m_vInfo.size())
		return;

	long lret = SPIDER_DeleteTimeNTPServerInfo(theApp.m_hSelectCamera, nDeleteIndex);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));


	InitInfo();
}
