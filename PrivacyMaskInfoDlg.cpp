// PrivacyMaskInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDlg.h"
#include "PrivacyMaskInfoDlg.h"


// CPrivacyMaskInfoDlg dialog

IMPLEMENT_DYNCREATE(CPrivacyMaskInfoDlg, CDialog)

CPrivacyMaskInfoDlg::CPrivacyMaskInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPrivacyMaskInfoDlg::IDD, pParent)
{

}

CPrivacyMaskInfoDlg::~CPrivacyMaskInfoDlg()
{
}

void CPrivacyMaskInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PRIVACY_ID, m_Combo_RegionID);
}

BOOL CPrivacyMaskInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitInfo();


	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CPrivacyMaskInfoDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CPrivacyMaskInfoDlg::OnBnClickedButtonModify)
	ON_CBN_SELCHANGE(IDC_COMBO_PRIVACY_ID, &CPrivacyMaskInfoDlg::OnCbnSelchangeComboPrivacyId)
	ON_BN_CLICKED(IDC_BUTTON_ADD_REGION, &CPrivacyMaskInfoDlg::OnBnClickedButtonAddRegion)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_REGION, &CPrivacyMaskInfoDlg::OnBnClickedButtonDeleteRegion)
END_MESSAGE_MAP()

// CPrivacyMaskInfoDlg message handlers

void CPrivacyMaskInfoDlg::OnCbnSelchangeComboPrivacyId()
{
	// TODO: Add your control notification handler code here

	DisplayInfo();
}

void CPrivacyMaskInfoDlg::DisplayInfo()
{
	int nSel = m_Combo_RegionID.GetCurSel();

	if(nSel != -1 && nSel < m_vInfo.size())
	{
		CString sztext;


		ST_SPIDER_PRIVACYMASK_REGION stInfo = m_vInfo.at(nSel);

		int nCoordinate = 0;

		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_X1), stInfo.Coordinate[nCoordinate].nPositionX, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_Y1), stInfo.Coordinate[nCoordinate].nPositionY, sztext);

		nCoordinate++;
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_X2), stInfo.Coordinate[nCoordinate].nPositionX, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_Y2), stInfo.Coordinate[nCoordinate].nPositionY, sztext);

		nCoordinate++;
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_X3), stInfo.Coordinate[nCoordinate].nPositionX, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_Y3), stInfo.Coordinate[nCoordinate].nPositionY, sztext);

		nCoordinate++;
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_X4), stInfo.Coordinate[nCoordinate].nPositionX, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_Y4), stInfo.Coordinate[nCoordinate].nPositionY, sztext);


		CString szResolution;
		//szResolution.Format(("Resolution : %d x %d"), m_RegionROI.m_uWidth, m_RegionROI.m_uHeight);
		GetDlgItem(IDC_STATIC_RESOLUTION)->SetWindowText(szResolution);


		if(stInfo.nsEnabled == 1)
		{
			GetDlgItem(IDC_CHECK_ENABLE_REGION)->EnableWindow(true);
			GetDlgItem(IDC_CHECK_ENABLE_REGION)->SendMessage(BM_SETCHECK, BST_CHECKED);
		}
		else
		{
			GetDlgItem(IDC_CHECK_ENABLE_REGION)->SendMessage(BM_SETCHECK, BST_UNCHECKED);
			if(stInfo.nsEnabled == 0xFFFF || stInfo.nsEnabled == 0xFFFFFFFF)
			{
				GetDlgItem(IDC_CHECK_ENABLE_REGION)->EnableWindow(false);
			}
			else
			{
				GetDlgItem(IDC_CHECK_ENABLE_REGION)->EnableWindow(true);
			}
		}
	}
}

void CPrivacyMaskInfoDlg::InitInfo()
{

	m_Combo_RegionID.ResetContent();
		
	m_vInfo.clear();

	long lret = SPIDER_GetPrivacyMaskInfo(theApp.m_hSelectCamera, &m_stInfo);
	if(lret != E_CTRL_OK)
	{
		MessageBox(GetErrorString(lret), ("Fail"));
	}
	else
	{
		CString sztext;

		if(m_stInfo.nsEnabled == 1)
		{
			GetDlgItem(IDC_BUTTON_ADD_REGION)->EnableWindow(true);
			GetDlgItem(IDC_BUTTON_DELETE_REGION)->EnableWindow(true);
			m_Combo_RegionID.EnableWindow(true);

			GetDlgItem(IDC_CHECK_ENABLE_PRIVACY)->EnableWindow(true);
			GetDlgItem(IDC_CHECK_ENABLE_PRIVACY)->SendMessage(BM_SETCHECK, BST_CHECKED);
		}
		else
		{
			GetDlgItem(IDC_BUTTON_ADD_REGION)->EnableWindow(true);
			GetDlgItem(IDC_BUTTON_DELETE_REGION)->EnableWindow(true);

			GetDlgItem(IDC_CHECK_ENABLE_PRIVACY)->SendMessage(BM_SETCHECK);

			if(m_stInfo.nsEnabled == false)
			{
				GetDlgItem(IDC_BUTTON_MODIFY)->EnableWindow(true);
				m_Combo_RegionID.EnableWindow(true);

				GetDlgItem(IDC_CHECK_ENABLE_PRIVACY)->EnableWindow(true);
			}
			else
			{
				GetDlgItem(IDC_BUTTON_MODIFY)->EnableWindow(false);
				m_Combo_RegionID.EnableWindow(false);

				GetDlgItem(IDC_CHECK_ENABLE_PRIVACY)->EnableWindow(false);			 
			}
		}


		m_vInfo.clear();
		long nCount = SPIDER_GetPrivacyMaskRegionCount(theApp.m_hSelectCamera);
		for(int i = 0; i < nCount; i++)
		{
			ST_SPIDER_PRIVACYMASK_REGION stInfo = {0};
			long lret = SPIDER_GetPrivacyMaskRegionInfo(theApp.m_hSelectCamera, i, &stInfo);
			if(lret != E_CTRL_OK)
			{
				MessageBox(GetErrorString(lret), ("Fail"));
				break;
			}

			m_vInfo.push_back(stInfo);


			sztext = stInfo.strID;
			m_Combo_RegionID.AddString(sztext);

		}
		m_Combo_RegionID.SetCurSel(0);

		DisplayInfo();

	}
	
}

void CPrivacyMaskInfoDlg::OnBnClickedButtonModify()
{
	{
		ST_SPIDER_PRIVACYMASK stNew = m_stInfo;

		CString sztext;
			
		if(stNew.nsEnabled != 0xFFFF && stNew.nsEnabled != 0xFFFFFFFF)
			stNew.nsEnabled = GetDlgItem(IDC_CHECK_ENABLE_PRIVACY)->SendMessage(BM_GETCHECK);

		long lret = SPIDER_SetPrivacyMaskInfo(theApp.m_hSelectCamera, stNew);
		if(lret != E_CTRL_OK)
		{
			MessageBox(GetErrorString(lret), ("Fail"));
			return;
		}
	}

	{
		int nModifyIndex = m_Combo_RegionID.GetCurSel();
		if(nModifyIndex >= m_vInfo.size())
			return;

		ST_SPIDER_PRIVACYMASK_REGION stNew = m_vInfo.at(nModifyIndex);

		CString sztext;


		int nValue = 0;

		int nCoordinate = 0;
		GetDlgItem(IDC_EDIT_X1)->GetWindowText(sztext);
		nValue = _ttoi(sztext);
		if(stNew.Coordinate[nCoordinate].nPositionX != 0xFFFF && stNew.Coordinate[nCoordinate].nPositionX != 0xFFFFFFFF)
			stNew.Coordinate[nCoordinate].nPositionX = nValue;

		GetDlgItem(IDC_EDIT_Y1)->GetWindowText(sztext);
		nValue = _ttoi(sztext);
		if(stNew.Coordinate[nCoordinate].nPositionY != 0xFFFF && stNew.Coordinate[nCoordinate].nPositionY != 0xFFFFFFFF)
			stNew.Coordinate[nCoordinate].nPositionY = nValue;

		nCoordinate++;
		GetDlgItem(IDC_EDIT_X2)->GetWindowText(sztext);
		nValue = _ttoi(sztext);
		if(stNew.Coordinate[nCoordinate].nPositionX != 0xFFFF && stNew.Coordinate[nCoordinate].nPositionX != 0xFFFFFFFF)
			stNew.Coordinate[nCoordinate].nPositionX = nValue;

		GetDlgItem(IDC_EDIT_Y2)->GetWindowText(sztext);
		nValue = _ttoi(sztext);
		if(stNew.Coordinate[nCoordinate].nPositionY != 0xFFFF && stNew.Coordinate[nCoordinate].nPositionY != 0xFFFFFFFF)
			stNew.Coordinate[nCoordinate].nPositionY = nValue;

		nCoordinate++;
		GetDlgItem(IDC_EDIT_X3)->GetWindowText(sztext);
		nValue = _ttoi(sztext);
		if(stNew.Coordinate[nCoordinate].nPositionX != 0xFFFF && stNew.Coordinate[nCoordinate].nPositionX != 0xFFFFFFFF)
			stNew.Coordinate[nCoordinate].nPositionX = nValue;

		GetDlgItem(IDC_EDIT_Y3)->GetWindowText(sztext);
		nValue = _ttoi(sztext);
		if(stNew.Coordinate[nCoordinate].nPositionY != 0xFFFF && stNew.Coordinate[nCoordinate].nPositionY != 0xFFFFFFFF)
			stNew.Coordinate[nCoordinate].nPositionY = nValue;

		nCoordinate++;
		GetDlgItem(IDC_EDIT_X4)->GetWindowText(sztext);
		nValue = _ttoi(sztext);
		if(stNew.Coordinate[nCoordinate].nPositionX != 0xFFFF && stNew.Coordinate[nCoordinate].nPositionX != 0xFFFFFFFF)
			stNew.Coordinate[nCoordinate].nPositionX = nValue;

		GetDlgItem(IDC_EDIT_Y4)->GetWindowText(sztext);
		nValue = _ttoi(sztext);
		if(stNew.Coordinate[nCoordinate].nPositionY != 0xFFFF && stNew.Coordinate[nCoordinate].nPositionY != 0xFFFFFFFF)
			stNew.Coordinate[nCoordinate].nPositionY = nValue;

		if(stNew.nsEnabled != 0xFFFF && stNew.nsEnabled != 0xFFFFFFFF)
			stNew.nsEnabled = GetDlgItem(IDC_CHECK_ENABLE_REGION)->SendMessage(BM_GETCHECK);

		long lret = SPIDER_SetPrivacyMaskRegionInfo(theApp.m_hSelectCamera, stNew);
		if(lret != E_CTRL_OK)
			MessageBox(GetErrorString(lret), ("Fail"));
		else
			MessageBox(("Success."));
	}

	InitInfo();
}

void CPrivacyMaskInfoDlg::OnBnClickedButtonAddRegion()
{
	// TODO: Add your control notification handler code here

	ST_SPIDER_PRIVACYMASK_REGION stNew = {0};

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


	int nValue = 0;

	int nCoordinate = 0;
	GetDlgItem(IDC_EDIT_X1)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.Coordinate[nCoordinate].nPositionX != 0xFFFF && stNew.Coordinate[nCoordinate].nPositionX != 0xFFFFFFFF)
		stNew.Coordinate[nCoordinate].nPositionX = nValue;

	GetDlgItem(IDC_EDIT_Y1)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.Coordinate[nCoordinate].nPositionY != 0xFFFF && stNew.Coordinate[nCoordinate].nPositionY != 0xFFFFFFFF)
		stNew.Coordinate[nCoordinate].nPositionY = nValue;

	nCoordinate++;
	GetDlgItem(IDC_EDIT_X2)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.Coordinate[nCoordinate].nPositionX != 0xFFFF && stNew.Coordinate[nCoordinate].nPositionX != 0xFFFFFFFF)
		stNew.Coordinate[nCoordinate].nPositionX = nValue;

	GetDlgItem(IDC_EDIT_Y2)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.Coordinate[nCoordinate].nPositionY != 0xFFFF && stNew.Coordinate[nCoordinate].nPositionY != 0xFFFFFFFF)
		stNew.Coordinate[nCoordinate].nPositionY = nValue;

	nCoordinate++;
	GetDlgItem(IDC_EDIT_X3)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.Coordinate[nCoordinate].nPositionX != 0xFFFF && stNew.Coordinate[nCoordinate].nPositionX != 0xFFFFFFFF)
		stNew.Coordinate[nCoordinate].nPositionX = nValue;

	GetDlgItem(IDC_EDIT_Y3)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.Coordinate[nCoordinate].nPositionY != 0xFFFF && stNew.Coordinate[nCoordinate].nPositionY != 0xFFFFFFFF)
		stNew.Coordinate[nCoordinate].nPositionY = nValue;

	nCoordinate++;
	GetDlgItem(IDC_EDIT_X4)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.Coordinate[nCoordinate].nPositionX != 0xFFFF && stNew.Coordinate[nCoordinate].nPositionX != 0xFFFFFFFF)
		stNew.Coordinate[nCoordinate].nPositionX = nValue;

	GetDlgItem(IDC_EDIT_Y4)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.Coordinate[nCoordinate].nPositionY != 0xFFFF && stNew.Coordinate[nCoordinate].nPositionY != 0xFFFFFFFF)
		stNew.Coordinate[nCoordinate].nPositionY = nValue;

	if(stNew.nsEnabled != 0xFFFF && stNew.nsEnabled != 0xFFFFFFFF)
		stNew.nsEnabled = GetDlgItem(IDC_CHECK_ENABLE_REGION)->SendMessage(BM_GETCHECK);

	long lret = SPIDER_AddPrivacyMaskRegionInfo(theApp.m_hSelectCamera, stNew);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));


	InitInfo();
}

void CPrivacyMaskInfoDlg::OnBnClickedButtonDeleteRegion()
{
	// TODO: Add your control notification handler code here
	int nDeleteIndex = m_Combo_RegionID.GetCurSel();
	if(nDeleteIndex >= m_vInfo.size())
		return;

	long lret = SPIDER_DeletePrivacyMaskRegionInfo(theApp.m_hSelectCamera, nDeleteIndex);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));

	InitInfo();
}
