// NotifyMailingInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDlg.h"
#include "NotifyMailingInfoDlg.h"


// CNotifyMailingInfoDlg dialog

IMPLEMENT_DYNCREATE(CNotifyMailingInfoDlg, CDialog)

CNotifyMailingInfoDlg::CNotifyMailingInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNotifyMailingInfoDlg::IDD, pParent)
{

}

CNotifyMailingInfoDlg::~CNotifyMailingInfoDlg()
{
}

void CNotifyMailingInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MAIL, m_List_Mail);
	DDX_Control(pDX, IDC_COMBO_AUTH_MODE, m_Combo_AuthMode);
	DDX_Control(pDX, IDC_COMBO_ADDRESS_FORMAT, m_Combo_AddressFormat);
	DDX_Control(pDX, IDC_COMBO_POP_ADDRESS_FORMAT, m_Combo_POPAddressFormat);
}

BOOL CNotifyMailingInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();



	int ncol = 0;
	m_List_Mail.SetExtendedStyle( m_List_Mail.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_List_Mail.InsertColumn(ncol++, ("Index"), 0, 50);
	m_List_Mail.InsertColumn(ncol++, ("ID"), 0, 50);
	m_List_Mail.InsertColumn(ncol++, ("Address"), 0, 150);
	m_List_Mail.InsertColumn(ncol++, ("POP Server"), 0, 150);



	m_Combo_AuthMode.AddString(("none"));
	m_Combo_AuthMode.AddString(("SMTP"));
	m_Combo_AuthMode.AddString(("POP/SMTP"));
	m_Combo_AuthMode.SetCurSel(0);


	m_Combo_AddressFormat.AddString(("IP Address"));
	m_Combo_AddressFormat.AddString(("Host Name"));
	m_Combo_AddressFormat.SetCurSel(0);

	m_Combo_POPAddressFormat.AddString(("IP Address"));
	m_Combo_POPAddressFormat.AddString(("Host Name"));
	m_Combo_POPAddressFormat.SetCurSel(0);


	InitInfo();


	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CNotifyMailingInfoDlg, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_LIST_MAIL, &CNotifyMailingInfoDlg::OnNMClickListMail)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY_NOTIFICATION, &CNotifyMailingInfoDlg::OnBnClickedButtonModifyNotification)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CNotifyMailingInfoDlg::OnBnClickedButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CNotifyMailingInfoDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CNotifyMailingInfoDlg::OnBnClickedButtonDelete)
END_MESSAGE_MAP()

// CNotifyMailingInfoDlg message handlers


void CNotifyMailingInfoDlg::OnNMClickListMail(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE*>(pNMHDR);
	// TODO: Add your control notification handler code here
	DisplayInfo();

	*pResult = 0;
}

void CNotifyMailingInfoDlg::DisplayInfo()
{

	int nSel = m_List_Mail.GetSelectionMark();
	if(nSel != -1 && nSel < m_vInfo.size())
	{
		ST_SPIDER_EVENT_NOTIFICATION_MAILING stInfo = m_vInfo.at(nSel);

		CString sztext;

		_VALID_WND_WITH_VAL(m_Combo_AuthMode, stInfo.nsAuthenticMode, NULL);	
		_VALID_WND_WITH_VAL(m_Combo_AddressFormat, stInfo.nsAddrFormatType, NULL);	
		_VALID_WND_WITH_VAL(m_Combo_POPAddressFormat, stInfo.nsPopAddrFormatType, NULL);	
		

		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_ID), stInfo.strID, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_HOSTNAME), stInfo.strHostName, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_IPADDRESS_V4), stInfo.strIpAddr, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_IPADDRESS_V6), stInfo.strIpAddrV6, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_PORT), stInfo.nsPort, sztext);
		
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_POP_HOSTNAME), stInfo.strPopHostName, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_POP_IPADDRESS_V4), stInfo.strPopIpAddr, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_POP_IPADDRESS_V6), stInfo.strPopIpAddrV6, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_ACCOUNT_NAME), stInfo.strAccountName, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_PASSWORD), stInfo.strPassword, sztext);

	}
}

void CNotifyMailingInfoDlg::InitInfo()
{

	long lret = SPIDER_GetNotificationInfo(theApp.m_hSelectCamera, &m_stInfo);
	if(lret != E_CTRL_OK)
	{
		MessageBox(GetErrorString(lret), ("Fail"));
	}
	else
	{
		ST_SPIDER_EVENT_NOTIFICATION stInfo = m_stInfo;

		CString sztext;

		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_SENDER_ADDRESS), stInfo.strSenderEmail, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_RECVER_ADDRESS), stInfo.strRecvEmail, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_SUBJECT), stInfo.strSubject, sztext);

		
		if(stInfo.nsAttachedVideoURLEnabled == 1)
		{
			GetDlgItem(IDC_CHECK_ENABLE_VIDEO_URL)->EnableWindow(true);
			GetDlgItem(IDC_CHECK_ENABLE_VIDEO_URL)->SendMessage(BM_SETCHECK, BST_CHECKED);
		}
		else if(stInfo.nsAttachedVideoURLEnabled == 0)
		{
			GetDlgItem(IDC_CHECK_ENABLE_VIDEO_URL)->EnableWindow(true);
			GetDlgItem(IDC_CHECK_ENABLE_VIDEO_URL)->SendMessage(BM_SETCHECK);
		}
		else
		{
			GetDlgItem(IDC_CHECK_ENABLE_VIDEO_URL)->EnableWindow(false);
			GetDlgItem(IDC_CHECK_ENABLE_VIDEO_URL)->SendMessage(BM_SETCHECK);
		}

		if(stInfo.nsAttchedSnapshotEnabled == 1)
		{
			GetDlgItem(IDC_CHECK_ENABLE_SNAPSHOT)->EnableWindow(true);
			GetDlgItem(IDC_CHECK_ENABLE_SNAPSHOT)->SendMessage(BM_SETCHECK, BST_CHECKED);
		}
		else if(stInfo.nsAttchedSnapshotEnabled == 0)
		{
			GetDlgItem(IDC_CHECK_ENABLE_SNAPSHOT)->EnableWindow(true);
			GetDlgItem(IDC_CHECK_ENABLE_SNAPSHOT)->SendMessage(BM_SETCHECK);
		}
		else
		{
			GetDlgItem(IDC_CHECK_ENABLE_SNAPSHOT)->EnableWindow(false);
			GetDlgItem(IDC_CHECK_ENABLE_SNAPSHOT)->SendMessage(BM_SETCHECK);
		}

		if(stInfo.nsAttchedVideoClipEnabled == 1)
		{
			GetDlgItem(IDC_CHECK_ENABLE_VIDEO_CLIP)->EnableWindow(true);
			GetDlgItem(IDC_CHECK_ENABLE_VIDEO_CLIP)->SendMessage(BM_SETCHECK, BST_CHECKED);
		}
		else if(stInfo.nsAttchedVideoClipEnabled == 0)
		{
			GetDlgItem(IDC_CHECK_ENABLE_VIDEO_CLIP)->EnableWindow(true);
			GetDlgItem(IDC_CHECK_ENABLE_VIDEO_CLIP)->SendMessage(BM_SETCHECK);
		}
		else
		{
			GetDlgItem(IDC_CHECK_ENABLE_VIDEO_CLIP)->EnableWindow(false);
			GetDlgItem(IDC_CHECK_ENABLE_VIDEO_CLIP)->SendMessage(BM_SETCHECK);
		}
	}




	m_List_Mail.DeleteAllItems();

	m_vInfo.clear();
	long nCount = SPIDER_GetNotificationMailingCount(theApp.m_hSelectCamera);
	for(int i = 0; i < nCount; i++)
	{
		ST_SPIDER_EVENT_NOTIFICATION_MAILING stInfo = {0};
		lret = SPIDER_GetNotificationMailingInfo(theApp.m_hSelectCamera, i, &stInfo);
		if(lret != E_CTRL_OK)
		{
			MessageBox(GetErrorString(lret), ("Fail"));
			break;
		}

		m_vInfo.push_back(stInfo);
		CString sztext;

		sztext.Format(("%d"), i +1);
		m_List_Mail.InsertItem(i, sztext);


		int ncol = 1;
		sztext = stInfo.strID;
		m_List_Mail.SetItem(i, ncol++, LVIF_TEXT, sztext, 0, 0, 0, 0);

		sztext = stInfo.strIpAddr;
		if(stInfo.nsAddrFormatType == 0)	//ip address
		{
			if(sztext.GetLength() == 0)
				sztext = stInfo.strIpAddrV6;
		}
		else
		{
			sztext = stInfo.strHostName;
		}

		m_List_Mail.SetItem(i, ncol++, LVIF_TEXT, sztext, 0, 0, 0, 0);



		sztext = stInfo.strPopIpAddr;
		if(stInfo.nsPopAddrFormatType == 0)	//ip address
		{
			if(sztext.GetLength() == 0)
				sztext = stInfo.strPopIpAddrV6;
		}
		else
		{
			sztext = stInfo.strPopHostName;
		}

		m_List_Mail.SetItem(i, ncol++, LVIF_TEXT, sztext, 0, 0, 0, 0);

	}

	m_List_Mail.SetSelectionMark(0);

	DisplayInfo();

}

void CNotifyMailingInfoDlg::OnBnClickedButtonModifyNotification()
{
	ST_SPIDER_EVENT_NOTIFICATION stNew = m_stInfo;

	CString sztext;

	GetDlgItem(IDC_EDIT_SENDER_ADDRESS)->GetWindowText(sztext);
	if(strcmp(stNew.strSenderEmail, "NA"))
		StringCopyTo(sztext, stNew.strSenderEmail);

	GetDlgItem(IDC_EDIT_RECVER_ADDRESS)->GetWindowText(sztext);
	if(strcmp(stNew.strRecvEmail, "NA"))
		StringCopyTo(sztext, stNew.strRecvEmail);

	GetDlgItem(IDC_EDIT_SUBJECT)->GetWindowText(sztext);
	if(strcmp(stNew.strSubject, "NA"))
		StringCopyTo(sztext, stNew.strSubject);


	if(stNew.nsAttachedVideoURLEnabled != 0xFFFF && stNew.nsAttachedVideoURLEnabled != 0xFFFFFFFF)
		stNew.nsAttachedVideoURLEnabled = GetDlgItem(IDC_CHECK_ENABLE_VIDEO_URL)->SendMessage(BM_GETCHECK);

	if(stNew.nsAttchedSnapshotEnabled != 0xFFFF && stNew.nsAttchedSnapshotEnabled != 0xFFFFFFFF)
		stNew.nsAttchedSnapshotEnabled = GetDlgItem(IDC_CHECK_ENABLE_SNAPSHOT)->SendMessage(BM_GETCHECK);

	if(stNew.nsAttchedVideoClipEnabled != 0xFFFF && stNew.nsAttchedVideoClipEnabled != 0xFFFFFFFF)
		stNew.nsAttchedVideoClipEnabled = GetDlgItem(IDC_CHECK_ENABLE_VIDEO_CLIP)->SendMessage(BM_GETCHECK);


	long lret = SPIDER_SetNotificationInfo(theApp.m_hSelectCamera, stNew);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));
}

void CNotifyMailingInfoDlg::OnBnClickedButtonModify()
{
	int nModifyIndex = m_List_Mail.GetSelectionMark();
	if(nModifyIndex >= m_vInfo.size())
		return;

	ST_SPIDER_EVENT_NOTIFICATION_MAILING stNew = m_vInfo.at(nModifyIndex);

	CString sztext;

	if(stNew.nsAuthenticMode != 0xFFFF && stNew.nsAuthenticMode != 0xFFFFFFFF)
		stNew.nsAuthenticMode = m_Combo_AuthMode.GetCurSel();

	if(stNew.nsAddrFormatType != 0xFFFF && stNew.nsAddrFormatType != 0xFFFFFFFF)
		stNew.nsAddrFormatType = m_Combo_AddressFormat.GetCurSel();

	if(stNew.nsPopAddrFormatType != 0xFFFF && stNew.nsPopAddrFormatType != 0xFFFFFFFF)
		stNew.nsPopAddrFormatType = m_Combo_POPAddressFormat.GetCurSel();


	GetDlgItem(IDC_EDIT_HOSTNAME)->GetWindowText(sztext);
	if(strcmp(stNew.strHostName, "NA"))
		StringCopyTo(sztext, stNew.strHostName);

	GetDlgItem(IDC_EDIT_IPADDRESS_V4)->GetWindowText(sztext);
	if(strcmp(stNew.strIpAddr, "NA"))
		StringCopyTo(sztext, stNew.strIpAddr);

	GetDlgItem(IDC_EDIT_IPADDRESS_V6)->GetWindowText(sztext);
	if(strcmp(stNew.strIpAddrV6, "NA"))
		StringCopyTo(sztext, stNew.strIpAddrV6);

	GetDlgItem(IDC_EDIT_POP_HOSTNAME)->GetWindowText(sztext);
	if(strcmp(stNew.strPopHostName, "NA"))
		StringCopyTo(sztext, stNew.strPopHostName);

	GetDlgItem(IDC_EDIT_POP_IPADDRESS_V4)->GetWindowText(sztext);
	if(strcmp(stNew.strPopIpAddr, "NA"))
		StringCopyTo(sztext, stNew.strPopIpAddr);

	GetDlgItem(IDC_EDIT_POP_IPADDRESS_V6)->GetWindowText(sztext);
	if(strcmp(stNew.strPopIpAddrV6, "NA"))
		StringCopyTo(sztext, stNew.strPopIpAddrV6);

	GetDlgItem(IDC_EDIT_ACCOUNT_NAME)->GetWindowText(sztext);
	if(strcmp(stNew.strAccountName, "NA"))
		StringCopyTo(sztext, stNew.strAccountName);

	GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowText(sztext);
	if(strcmp(stNew.strPassword, "NA"))
		StringCopyTo(sztext, stNew.strPassword);


	int nValue = 0;
	GetDlgItem(IDC_EDIT_PORT)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nsPort != 0xFFFF && stNew.nsPort != 0xFFFFFFFF)
		stNew.nsPort = nValue;



	long lret = SPIDER_SetNotificationMailingInfo(theApp.m_hSelectCamera, stNew);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));


	InitInfo();
}

void CNotifyMailingInfoDlg::OnBnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here

	ST_SPIDER_EVENT_NOTIFICATION_MAILING stNew = {0};

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

	if(stNew.nsAuthenticMode != 0xFFFF && stNew.nsAuthenticMode != 0xFFFFFFFF)
		stNew.nsAuthenticMode = m_Combo_AuthMode.GetCurSel();

	if(stNew.nsAddrFormatType != 0xFFFF && stNew.nsAddrFormatType != 0xFFFFFFFF)
		stNew.nsAddrFormatType = m_Combo_AddressFormat.GetCurSel();

	if(stNew.nsPopAddrFormatType != 0xFFFF && stNew.nsPopAddrFormatType != 0xFFFFFFFF)
		stNew.nsPopAddrFormatType = m_Combo_POPAddressFormat.GetCurSel();


	GetDlgItem(IDC_EDIT_HOSTNAME)->GetWindowText(sztext);
	if(strcmp(stNew.strHostName, "NA"))
		StringCopyTo(sztext, stNew.strHostName);

	GetDlgItem(IDC_EDIT_IPADDRESS_V4)->GetWindowText(sztext);
	if(strcmp(stNew.strIpAddr, "NA"))
		StringCopyTo(sztext, stNew.strIpAddr);

	GetDlgItem(IDC_EDIT_IPADDRESS_V6)->GetWindowText(sztext);
	if(strcmp(stNew.strIpAddrV6, "NA"))
		StringCopyTo(sztext, stNew.strIpAddrV6);

	GetDlgItem(IDC_EDIT_POP_HOSTNAME)->GetWindowText(sztext);
	if(strcmp(stNew.strPopHostName, "NA"))
		StringCopyTo(sztext, stNew.strPopHostName);

	GetDlgItem(IDC_EDIT_POP_IPADDRESS_V4)->GetWindowText(sztext);
	if(strcmp(stNew.strPopIpAddr, "NA"))
		StringCopyTo(sztext, stNew.strPopIpAddr);

	GetDlgItem(IDC_EDIT_POP_IPADDRESS_V6)->GetWindowText(sztext);
	if(strcmp(stNew.strPopIpAddrV6, "NA"))
		StringCopyTo(sztext, stNew.strPopIpAddrV6);

	GetDlgItem(IDC_EDIT_ACCOUNT_NAME)->GetWindowText(sztext);
	if(strcmp(stNew.strAccountName, "NA"))
		StringCopyTo(sztext, stNew.strAccountName);

	GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowText(sztext);
	if(strcmp(stNew.strPassword, "NA"))
		StringCopyTo(sztext, stNew.strPassword);


	int nValue = 0;
	GetDlgItem(IDC_EDIT_PORT)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nsPort != 0xFFFF && stNew.nsPort != 0xFFFFFFFF)
		stNew.nsPort = nValue;



	long lret = SPIDER_AddNotificationMailingInfo(theApp.m_hSelectCamera, stNew);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));




	InitInfo();

}

void CNotifyMailingInfoDlg::OnBnClickedButtonDelete()
{
	// TODO: Add your control notification handler code here

	int nDeleteIndex = m_List_Mail.GetSelectionMark();
	if(nDeleteIndex >= m_vInfo.size())
		return;

	long lret = SPIDER_DeleteNotificationMailingInfo(theApp.m_hSelectCamera, nDeleteIndex);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));



	InitInfo();
}
