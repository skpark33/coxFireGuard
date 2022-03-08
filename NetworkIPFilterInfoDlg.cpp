// NetworkIPFilterInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDlg.h"
#include "NetworkIPFilterInfoDlg.h"


// CNetworkIPFilterInfoDlg dialog

IMPLEMENT_DYNCREATE(CNetworkIPFilterInfoDlg, CDialog)

CNetworkIPFilterInfoDlg::CNetworkIPFilterInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNetworkIPFilterInfoDlg::IDD, pParent)
{

}

CNetworkIPFilterInfoDlg::~CNetworkIPFilterInfoDlg()
{
}

void CNetworkIPFilterInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_NETWORK_ID, m_Combo_NetworkID);
	DDX_Control(pDX, IDC_COMBO_PERMISSION, m_Combo_Permission);
	DDX_Control(pDX, IDC_LIST_IPFILTER, m_List_Address);
	DDX_Control(pDX, IDC_COMBO_ADDRESS_PERMISSION, m_Combo_AddressPermission);
}

BOOL CNetworkIPFilterInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	int ncol = 0;
	m_List_Address.SetExtendedStyle( m_List_Address.GetExtendedStyle() | LVS_EX_FULLROWSELECT );
	m_List_Address.InsertColumn(ncol++, ("Index"), 0, 50);
	m_List_Address.InsertColumn(ncol++, ("ID"), 0, 50);
	m_List_Address.InsertColumn(ncol++, ("Permission"), 0, 70);
	m_List_Address.InsertColumn(ncol++, ("Address"), 0, 250);



	m_Combo_Permission.ResetContent();
	m_Combo_Permission.AddString(("deny"));
	m_Combo_Permission.AddString(("allow"));
	m_Combo_Permission.SetCurSel(0);


	m_Combo_AddressPermission.ResetContent();
	m_Combo_AddressPermission.AddString(("deny"));
	m_Combo_AddressPermission.AddString(("allow"));
	m_Combo_AddressPermission.SetCurSel(0);



	m_Combo_NetworkID.ResetContent();

	m_vNetwork.clear();
	m_vInfo.clear();
	long nCount = SPIDER_GetNetworkCount(theApp.m_hSelectCamera);
	for(int i = 0; i < nCount; i++)
	{
		ST_SPIDER_NETWORK_INFO stNetwork = {0};
		long lret = SPIDER_GetNetworkInfo(theApp.m_hSelectCamera, i, &stNetwork);
		if(lret != E_CTRL_OK)
		{
			MessageBox(GetErrorString(lret), ("Fail"));
			break;
		}

		m_vNetwork.push_back(stNetwork);

		CString sztext;

		sztext = stNetwork.strID;
		m_Combo_NetworkID.AddString(sztext);

	}


	m_Combo_NetworkID.SetCurSel(0);

	DisplayInfo();



	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CNetworkIPFilterInfoDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_NETWORK_ID, &CNetworkIPFilterInfoDlg::OnCbnSelchangeComboNetworkId)
	ON_NOTIFY(NM_CLICK, IDC_LIST_IPFILTER, &CNetworkIPFilterInfoDlg::OnNMClickListIpfilter)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY_IPFILTER, &CNetworkIPFilterInfoDlg::OnBnClickedButtonModifyIpfilter)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY_ADDRESS, &CNetworkIPFilterInfoDlg::OnBnClickedButtonModifyAddress)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CNetworkIPFilterInfoDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CNetworkIPFilterInfoDlg::OnBnClickedButtonDelete)
END_MESSAGE_MAP()

// CNetworkIPFilterInfoDlg message handlers

void CNetworkIPFilterInfoDlg::OnCbnSelchangeComboNetworkId()
{
	// TODO: Add your control notification handler code here

	DisplayInfo();
}

void CNetworkIPFilterInfoDlg::DisplayInfo()
{
	int nSel = m_Combo_NetworkID.GetCurSel();

	m_vInfo.clear();
	m_List_Address.DeleteAllItems();

	if(nSel != -1 && nSel < m_vNetwork.size())
	{
		long lret = SPIDER_GetNetworkIPFilterInfo(theApp.m_hSelectCamera, nSel, &m_stInfo);
		if(lret != E_CTRL_OK)
		{
			MessageBox(GetErrorString(lret), ("Fail"));
		}
		else
		{

			CString sztext;

			ST_SPIDER_NETWORK_IPFILTER stFilter = m_stInfo;

			_VALID_WND_WITH_VAL(m_Combo_Permission, stFilter.nsPermissionType, NULL);

			if(stFilter.nsEnabled == TRUE)
			{
				GetDlgItem(IDC_CHECK_ENABLE)->EnableWindow(true);
				GetDlgItem(IDC_CHECK_ENABLE)->SendMessage(BM_SETCHECK, BST_CHECKED);
			}
			else
			{
				GetDlgItem(IDC_CHECK_ENABLE)->EnableWindow(true);
				GetDlgItem(IDC_CHECK_ENABLE)->SendMessage(BM_SETCHECK);
			}

			



			m_vInfo.clear();
			long nCount = SPIDER_GetNetworkIPFilterAddressCount(theApp.m_hSelectCamera, nSel);
			for(int i = 0; i < nCount; i++)
			{
				ST_SPIDER_NETWORK_IPFILTER_ADDRESS stInfo = {0};
				long lret = SPIDER_GetNetworkIPFilterAddressInfo(theApp.m_hSelectCamera, nSel, i, &stInfo);
				if(lret != E_CTRL_OK)
				{
					MessageBox(GetErrorString(lret), ("Fail"));
					break;
				}

				m_vInfo.push_back(stInfo);




				sztext.Format(("%d"), i+1);
				m_List_Address.InsertItem(i, sztext);


				int ncol = 1;

				sztext = stInfo.strID;
				m_List_Address.SetItem(i, ncol++, LVIF_TEXT, sztext, 0, 0, 0, 0);

				if(stInfo.nsPermissionType == 0)
					sztext = "deny";
				else if(stInfo.nsPermissionType == 1)
					sztext = "allow";
				else
					sztext = "";
				m_List_Address.SetItem(i, ncol++, LVIF_TEXT, sztext, 0, 0, 0, 0);


				sztext = _GetAddressText(stInfo);
				m_List_Address.SetItem(i, ncol++, LVIF_TEXT, sztext, 0, 0, 0, 0);


			}

			m_List_Address.SetSelectionMark(0);

			DisplayInfo_Address();
		}
	}
}

void CNetworkIPFilterInfoDlg::OnNMClickListIpfilter(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE*>(pNMHDR);
	// TODO: Add your control notification handler code here

	DisplayInfo_Address();

	*pResult = 0;
}

void CNetworkIPFilterInfoDlg::DisplayInfo_Address()
{

	int nSel = m_List_Address.GetSelectionMark();

	if(nSel != -1 && nSel < m_vInfo.size())
	{

		ST_SPIDER_NETWORK_IPFILTER_ADDRESS stAddress = m_vInfo.at(nSel);

		CString sztext;

		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_ID), stAddress.strID, sztext);

		_VALID_WND_WITH_VAL(m_Combo_AddressPermission, stAddress.nsPermissionType, NULL);

		

		_VALID_WND_WITH_VAL(GetDlgItem(IDC_IPADDRESS_MASK), stAddress.strIpMaskV4, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_IPADDRESS_V6_MASK), stAddress.strIpMaskV6, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_BITMASK), stAddress.strBitMask, sztext);
			
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_IPADDRESS_START_RANGE), stAddress.strStartIpAddrV4, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_IPADDRESS_END_RANGE), stAddress.strEndIpAddrV4, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_START_IPADDRESS_V6_RANGE), stAddress.strStartIpAddrV6, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_END_IPADDRESS_V6_RANGE), stAddress.strEndIpAddrV6, sztext);

		if(stAddress.nsFilterType == 0) // mask
		{
			GetDlgItem(IDC_RADIO_MASK)->SendMessage(BM_SETCHECK, BST_CHECKED);
			GetDlgItem(IDC_RADIO_RANGE)->SendMessage(BM_SETCHECK);
		}
		else if(stAddress.nsFilterType == 1) // range
		{
			GetDlgItem(IDC_RADIO_MASK)->SendMessage(BM_SETCHECK);
			GetDlgItem(IDC_RADIO_RANGE)->SendMessage(BM_SETCHECK, BST_CHECKED);
		}
		else
		{
			GetDlgItem(IDC_RADIO_MASK)->SendMessage(BM_SETCHECK);
			GetDlgItem(IDC_RADIO_RANGE)->SendMessage(BM_SETCHECK);
		}
	}
}

CString CNetworkIPFilterInfoDlg::_GetAddressText(ST_SPIDER_NETWORK_IPFILTER_ADDRESS stAddress)
{
	CString szAddress;

	if(stAddress.nsFilterType == 0)	//mask
	{
		if(strlen(stAddress.strIpMaskV4))
			szAddress = stAddress.strIpMaskV4;
		else
			szAddress = stAddress.strIpMaskV6;
	}
	else if(stAddress.nsFilterType == 1)	//range
	{
		if(strcmp(stAddress.strStartIpAddrV6, "NA")
		&& strlen(stAddress.strStartIpAddrV6) 
		&& strcmp(stAddress.strEndIpAddrV6, "NA")
		&& strlen(stAddress.strEndIpAddrV6))
		{
			szAddress = stAddress.strStartIpAddrV6;
			szAddress += " - ";
			szAddress += stAddress.strEndIpAddrV6;
		}
		else //if(strlen(stAddress.strStartIpAddrV4) || strlen(stAddress.strEndIpAddrV4))
		{
			szAddress = stAddress.strStartIpAddrV4;
			szAddress += " - ";
			szAddress += stAddress.strEndIpAddrV4;
		}
	}
	else
		szAddress = "";

	return szAddress;
}

void CNetworkIPFilterInfoDlg::OnBnClickedButtonModifyIpfilter()
{
	// TODO: Add your control notification handler code here
	ST_SPIDER_NETWORK_IPFILTER stNew = m_stInfo;

	if(stNew.nsPermissionType != 0xFFFF && stNew.nsPermissionType != 0xFFFFFFFF)
		stNew.nsPermissionType = m_Combo_Permission.GetCurSel();

	if(stNew.nsEnabled != 0xFFFF && stNew.nsEnabled != 0xFFFFFFFF)
		stNew.nsEnabled = GetDlgItem(IDC_CHECK_ENABLE)->SendMessage(BM_GETCHECK);

	int nSel = m_Combo_NetworkID.GetCurSel();
	long lret = SPIDER_SetNetworkIPFilterInfo(theApp.m_hSelectCamera, nSel, stNew);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));
}

void CNetworkIPFilterInfoDlg::OnBnClickedButtonModifyAddress()
{
	int nModifyIndex = m_List_Address.GetSelectionMark();
	if(nModifyIndex >= m_vInfo.size())
		return;

	ST_SPIDER_NETWORK_IPFILTER_ADDRESS stNew = m_vInfo.at(nModifyIndex);

	CString sztext;
	

	if(stNew.nsPermissionType != 0xFFFF && stNew.nsPermissionType != 0xFFFFFFFF)
		stNew.nsPermissionType = m_Combo_AddressPermission.GetCurSel();


	GetDlgItem(IDC_IPADDRESS_MASK)->GetWindowText(sztext);
	if(strcmp(stNew.strIpMaskV4, "NA"))
		StringCopyTo(sztext, stNew.strIpMaskV4);

	GetDlgItem(IDC_EDIT_IPADDRESS_V6_MASK)->GetWindowText(sztext);
	if(strcmp(stNew.strIpMaskV6, "NA"))
		StringCopyTo(sztext, stNew.strIpMaskV6);

	GetDlgItem(IDC_EDIT_BITMASK)->GetWindowText(sztext);
	if(strcmp(stNew.strBitMask, "NA"))
		StringCopyTo(sztext, stNew.strBitMask);

	if(strlen(stNew.strBitMask) == 0)
		strcpy(stNew.strBitMask, "32");

	GetDlgItem(IDC_IPADDRESS_START_RANGE)->GetWindowText(sztext);
	if(strcmp(stNew.strStartIpAddrV4, "NA"))
		StringCopyTo(sztext, stNew.strStartIpAddrV4);

	GetDlgItem(IDC_IPADDRESS_END_RANGE)->GetWindowText(sztext);
	if(strcmp(stNew.strEndIpAddrV4, "NA"))
		StringCopyTo(sztext, stNew.strEndIpAddrV4);

	GetDlgItem(IDC_EDIT_START_IPADDRESS_V6_RANGE)->GetWindowText(sztext);
	if(strcmp(stNew.strStartIpAddrV6, "NA"))
		StringCopyTo(sztext, stNew.strStartIpAddrV6);

	GetDlgItem(IDC_EDIT_END_IPADDRESS_V6_RANGE)->GetWindowText(sztext);
	if(strcmp(stNew.strEndIpAddrV6, "NA"))
		StringCopyTo(sztext, stNew.strEndIpAddrV6);

	if(stNew.nsFilterType != 0xFFFF && stNew.nsFilterType != 0xFFFFFFFF)
	{
		if(BST_CHECKED == GetDlgItem(IDC_RADIO_MASK)->SendMessage(BM_GETCHECK))
			stNew.nsFilterType = 0;
		else if(BST_CHECKED == GetDlgItem(IDC_RADIO_RANGE)->SendMessage(BM_GETCHECK))
			stNew.nsFilterType = 1;
	}

	int nSel = m_Combo_NetworkID.GetCurSel();
	long lret = SPIDER_SetNetworkIPFilterAddressInfo(theApp.m_hSelectCamera, nSel, stNew);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));

}

void CNetworkIPFilterInfoDlg::OnBnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here

	ST_SPIDER_NETWORK_IPFILTER_ADDRESS stNew = {0};

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
	

	if(stNew.nsPermissionType != 0xFFFF && stNew.nsPermissionType != 0xFFFFFFFF)
		stNew.nsPermissionType = m_Combo_AddressPermission.GetCurSel();


	GetDlgItem(IDC_IPADDRESS_MASK)->GetWindowText(sztext);
	if(strcmp(stNew.strIpMaskV4, "NA"))
		StringCopyTo(sztext, stNew.strIpMaskV4);

	GetDlgItem(IDC_EDIT_IPADDRESS_V6_MASK)->GetWindowText(sztext);
	if(strcmp(stNew.strIpMaskV6, "NA"))
		StringCopyTo(sztext, stNew.strIpMaskV6);

	GetDlgItem(IDC_EDIT_BITMASK)->GetWindowText(sztext);
	if(strcmp(stNew.strBitMask, "NA"))
		StringCopyTo(sztext, stNew.strBitMask);

	if(strlen(stNew.strBitMask) == 0)
		strcpy(stNew.strBitMask, "32");

	GetDlgItem(IDC_IPADDRESS_START_RANGE)->GetWindowText(sztext);
	if(strcmp(stNew.strStartIpAddrV4, "NA"))
		StringCopyTo(sztext, stNew.strStartIpAddrV4);

	GetDlgItem(IDC_IPADDRESS_END_RANGE)->GetWindowText(sztext);
	if(strcmp(stNew.strEndIpAddrV4, "NA"))
		StringCopyTo(sztext, stNew.strEndIpAddrV4);

	GetDlgItem(IDC_EDIT_START_IPADDRESS_V6_RANGE)->GetWindowText(sztext);
	if(strcmp(stNew.strStartIpAddrV6, "NA"))
		StringCopyTo(sztext, stNew.strStartIpAddrV6);

	GetDlgItem(IDC_EDIT_END_IPADDRESS_V6_RANGE)->GetWindowText(sztext);
	if(strcmp(stNew.strEndIpAddrV6, "NA"))
		StringCopyTo(sztext, stNew.strEndIpAddrV6);

	if(stNew.nsFilterType != 0xFFFF && stNew.nsFilterType != 0xFFFFFFFF)
	{
		if(BST_CHECKED == GetDlgItem(IDC_RADIO_MASK)->SendMessage(BM_GETCHECK))
			stNew.nsFilterType = 0;
		else if(BST_CHECKED == GetDlgItem(IDC_RADIO_RANGE)->SendMessage(BM_GETCHECK))
			stNew.nsFilterType = 1;
	}

	int nSel = m_Combo_NetworkID.GetCurSel();
	long lret = SPIDER_AddNetworkIPFilterAddressInfo(theApp.m_hSelectCamera, nSel, stNew);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));

	DisplayInfo();
}

void CNetworkIPFilterInfoDlg::OnBnClickedButtonDelete()
{
	// TODO: Add your control notification handler code here
	int nDeleteIndex = m_List_Address.GetSelectionMark();
	if(nDeleteIndex >= m_vInfo.size())
		return;

	int nSel = m_Combo_NetworkID.GetCurSel();
	long lret = SPIDER_DeleteNetworkIPFilterAddressInfo(theApp.m_hSelectCamera, nSel, nDeleteIndex);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));

	DisplayInfo();
}
