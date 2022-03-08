// NetworkIPAddrInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDlg.h"
#include "NetworkIPAddrInfoDlg.h"


// CNetworkIPAddrInfoDlg dialog

IMPLEMENT_DYNCREATE(CNetworkIPAddrInfoDlg, CDialog)

CNetworkIPAddrInfoDlg::CNetworkIPAddrInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNetworkIPAddrInfoDlg::IDD, pParent)
{

}

CNetworkIPAddrInfoDlg::~CNetworkIPAddrInfoDlg()
{
}

void CNetworkIPAddrInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_NETWORK_ID, m_Combo_NetworkID);
	DDX_Control(pDX, IDC_COMBO_IP_VERSION, m_Combo_IPVersion);
	DDX_Control(pDX, IDC_COMBO_IP_ADDRESS_TYPE, m_Combo_IPAddressType);
	DDX_Control(pDX, IDC_CHECK_UPNP, m_Check_Upnp);
	DDX_Control(pDX, IDC_CHECK_ZEROCONF, m_Check_ZeroConf);
	DDX_Control(pDX, IDC_CHECK_MULTI_CAST, m_Check_MultiCast);
}

BOOL CNetworkIPAddrInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();





	m_Combo_IPVersion.ResetContent();
	m_Combo_IPVersion.AddString(("V4"));
	m_Combo_IPVersion.AddString(("V6"));
	m_Combo_IPVersion.AddString(("Dual (V4 & V6)"));
	m_Combo_IPVersion.SetCurSel(0);
				
	m_Combo_IPAddressType.ResetContent();
	m_Combo_IPAddressType.AddString(("Static"));
	m_Combo_IPAddressType.AddString(("Dynamic"));
	m_Combo_IPAddressType.AddString(("APIPA"));
	m_Combo_IPAddressType.SetCurSel(0);







	m_Combo_NetworkID.ResetContent();

	m_vNetwork.clear();
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

	OnCbnSelchangeComboNetworkId();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CNetworkIPAddrInfoDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_APPLY_IPADDRESS, &CNetworkIPAddrInfoDlg::OnBnClickedButtonApplyIpaddress)
	ON_CBN_SELCHANGE(IDC_COMBO_NETWORK_ID, &CNetworkIPAddrInfoDlg::OnCbnSelchangeComboNetworkId)
	ON_BN_CLICKED(IDC_BUTTON_APPLY_DISCOVERY, &CNetworkIPAddrInfoDlg::OnBnClickedButtonApplyDiscovery)
END_MESSAGE_MAP()

// CNetworkIPAddrInfoDlg message handlers

void CNetworkIPAddrInfoDlg::OnCbnSelchangeComboNetworkId()
{
	// TODO: Add your control notification handler code here
	int nSel = m_Combo_NetworkID.GetCurSel();

	if(nSel != -1 && nSel < m_vNetwork.size())
	{
		long lret = SPIDER_GetNetworkIPAddrInfo(theApp.m_hSelectCamera, nSel, &m_stIPAddr);
		if(lret != E_CTRL_OK)
		{
			MessageBox(GetErrorString(lret), ("Fail"));
			return;
		}

		lret = SPIDER_GetNetworkDiscoveryInfo(theApp.m_hSelectCamera, nSel, &m_stDiscovery);
		if(lret != E_CTRL_OK)
		{
			MessageBox(GetErrorString(lret), ("Fail"));
			return;
		}

		

		CString sztext;

		ST_SPIDER_NETWORK_IPADDR_INFO stIPAddr = m_stIPAddr;
		ST_SPIDER_NETWORK_DISCOVERY_INFO stDiscovery = m_stDiscovery;


		//XPM_IP_VERSION_V4 = 0,
		//XPM_IP_VERSION_V6,
		//XPM_IP_VERSION_DUAL
		_VALID_WND_WITH_VAL(m_Combo_IPVersion, stIPAddr.nsIpVers, NULL);

		//XPM_IP_ADDRESS_TYPE_STATIC = 0,
		//XPM_IP_ADDRESS_TYPE_DYNAMIC,
		//XPM_IP_ADDRESS_TYPE_APIPA
		_VALID_WND_WITH_VAL(m_Combo_IPAddressType, stIPAddr.nsType, NULL);


		_VALID_WND_WITH_VAL(GetDlgItem(IDC_IPADDRESS1), stIPAddr.strIpAddr, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_SUBNET_MASK), stIPAddr.strIpMask, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_GATEWAY), stIPAddr.strGwIp, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_PRIMARY_DNS), stIPAddr.strFirstDns, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_SECOND_DNS), stIPAddr.strSecDns, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_IPADDRESS_V6), stIPAddr.strIpAddrV6, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_IPV6_BITMASK), stIPAddr.nBitMask, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_GATEWAY_V6), stIPAddr.strGwIpV6, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_PRIMARY_DNS_V6), stIPAddr.strFirstDnsV6, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_SECONDARY_DNS_V6), stIPAddr.strSecDnsV6, sztext);



		if(stDiscovery.bEnableUpnp >= 0xFFFF)
		{
			m_Check_Upnp.EnableWindow(false);
			m_Check_Upnp.SetCheck(0);
		}
		else
		{
			m_Check_Upnp.SetCheck(stDiscovery.bEnableUpnp);
			m_Check_Upnp.EnableWindow(true);
		}

		if(stDiscovery.bEnableZeroConf >= 0xFFFF)
		{
			m_Check_ZeroConf.EnableWindow(false);
			m_Check_ZeroConf.SetCheck(0);
		}
		else
		{
			m_Check_ZeroConf.SetCheck(stDiscovery.bEnableZeroConf);
			m_Check_ZeroConf.EnableWindow(true);
		}



		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_MULTICAST_PORT), stDiscovery.nsMulticastPortNum, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_MULTICAST_TTL), stDiscovery.nsMulticastTTL, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_MULTICAST_IPADDRESS), stDiscovery.strMulticastIpAddr, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_MULTICAST_IPADDRESS_V6), stDiscovery.strMulticastIpAddrV6, sztext);

		if(stDiscovery.bMulticastEnble >= 0xFFFF)
		{
			m_Check_MultiCast.EnableWindow(false);
			m_Check_MultiCast.SetCheck(0);

			GetDlgItem(IDC_MULTICAST_IPADDRESS)->EnableWindow(false);
			GetDlgItem(IDC_MULTICAST_IPADDRESS_V6)->EnableWindow(false);
			GetDlgItem(IDC_EDIT_MULTICAST_PORT)->EnableWindow(false);
			GetDlgItem(IDC_EDIT_MULTICAST_TTL)->EnableWindow(false);
		}
		else
		{
			m_Check_MultiCast.SetCheck(stDiscovery.bMulticastEnble);
			m_Check_MultiCast.EnableWindow(true);
		}
	}
}

void CNetworkIPAddrInfoDlg::OnBnClickedButtonApplyIpaddress()
{
	ST_SPIDER_NETWORK_IPADDR_INFO stNew = m_stIPAddr;

	CString sztext;

	if(stNew.nsIpVers != 0xFFFF && stNew.nsIpVers != 0xFFFFFFFF)
		stNew.nsIpVers = m_Combo_IPVersion.GetCurSel();

	if(stNew.nsType != 0xFFFF && stNew.nsType != 0xFFFFFFFF)
		stNew.nsType = m_Combo_IPAddressType.GetCurSel();

	GetDlgItem(IDC_IPADDRESS1)->GetWindowText(sztext);
	if(strcmp(stNew.strIpAddr, "NA"))
		StringCopyTo(sztext, stNew.strIpAddr);

	GetDlgItem(IDC_SUBNET_MASK)->GetWindowText(sztext);
	if(strcmp(stNew.strIpMask, "NA"))
		StringCopyTo(sztext, stNew.strIpMask);

	GetDlgItem(IDC_GATEWAY)->GetWindowText(sztext);
	if(strcmp(stNew.strGwIp, "NA"))
		StringCopyTo(sztext, stNew.strGwIp);

	GetDlgItem(IDC_PRIMARY_DNS)->GetWindowText(sztext);
	if(strcmp(stNew.strFirstDns, "NA"))
		StringCopyTo(sztext, stNew.strFirstDns);

	GetDlgItem(IDC_SECOND_DNS)->GetWindowText(sztext);
	if(strcmp(stNew.strSecDns, "NA"))
		StringCopyTo(sztext, stNew.strSecDns);

	GetDlgItem(IDC_EDIT_IPADDRESS_V6)->GetWindowText(sztext);
	if(strcmp(stNew.strIpAddrV6, "NA"))
		StringCopyTo(sztext, stNew.strIpAddrV6);

	GetDlgItem(IDC_EDIT_GATEWAY_V6)->GetWindowText(sztext);
	if(strcmp(stNew.strGwIpV6, "NA"))
		StringCopyTo(sztext, stNew.strGwIpV6);

	GetDlgItem(IDC_EDIT_PRIMARY_DNS_V6)->GetWindowText(sztext);
	if(strcmp(stNew.strFirstDnsV6, "NA"))
		StringCopyTo(sztext, stNew.strFirstDnsV6);

	GetDlgItem(IDC_EDIT_SECONDARY_DNS_V6)->GetWindowText(sztext);
	if(strcmp(stNew.strSecDnsV6, "NA"))
		StringCopyTo(sztext, stNew.strSecDnsV6);


	int nValue = 0;
	GetDlgItem(IDC_EDIT_IPV6_BITMASK)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nBitMask != 0xFFFF && stNew.nBitMask != 0xFFFFFFFF)
		stNew.nBitMask = nValue;


	int nSel = m_Combo_NetworkID.GetCurSel();
	long lret = SPIDER_SetNetworkIPAddrInfo(theApp.m_hSelectCamera, nSel, stNew);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));
}

void CNetworkIPAddrInfoDlg::OnBnClickedButtonApplyDiscovery()
{
	ST_SPIDER_NETWORK_DISCOVERY_INFO stNew = m_stDiscovery;

	CString sztext;

	if(stNew.bEnableUpnp != 0xFFFF && stNew.bEnableUpnp != 0xFFFFFFFF)
		stNew.bEnableUpnp = m_Check_Upnp.GetCheck();

	if(stNew.bEnableZeroConf != 0xFFFF && stNew.bEnableZeroConf != 0xFFFFFFFF)
		stNew.bEnableZeroConf = m_Check_ZeroConf.GetCheck();

	if(stNew.bMulticastEnble != 0xFFFF && stNew.bMulticastEnble != 0xFFFFFFFF)
		stNew.bMulticastEnble = m_Check_MultiCast.GetCheck();

	int nValue = 0;
	GetDlgItem(IDC_EDIT_MULTICAST_PORT)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nsMulticastPortNum != 0xFFFF && stNew.nsMulticastPortNum != 0xFFFFFFFF)
		stNew.nsMulticastPortNum = nValue;

	GetDlgItem(IDC_EDIT_MULTICAST_TTL)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nsMulticastTTL != 0xFFFF && stNew.nsMulticastTTL != 0xFFFFFFFF)
		stNew.nsMulticastTTL = nValue;

	GetDlgItem(IDC_MULTICAST_IPADDRESS)->GetWindowText(sztext);
	if(strcmp(stNew.strMulticastIpAddr, "NA"))
		StringCopyTo(sztext, stNew.strMulticastIpAddr);

	GetDlgItem(IDC_MULTICAST_IPADDRESS_V6)->GetWindowText(sztext);
	if(strcmp(stNew.strMulticastIpAddrV6, "NA"))
		StringCopyTo(sztext, stNew.strMulticastIpAddrV6);


	int nSel = m_Combo_NetworkID.GetCurSel();
	long lret = SPIDER_SetNetworkDiscoveryInfo(theApp.m_hSelectCamera, nSel, stNew);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));

}
