// UserInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDlg.h"
#include "UserInfoDlg.h"


// CUserInfoDlg dialog

IMPLEMENT_DYNCREATE(CUserInfoDlg, CDialog)

CUserInfoDlg::CUserInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserInfoDlg::IDD, pParent)
{

}

CUserInfoDlg::~CUserInfoDlg()
{
}

void CUserInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_USER, m_List_User);
}

BOOL CUserInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	m_List_User.SetExtendedStyle( m_List_User.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	m_List_User.InsertColumn(0, ("index"), 0, 50);
	m_List_User.InsertColumn(1, ("ID"), 0, 50);
	m_List_User.InsertColumn(2, ("User Name"), 0, 100);


	InitInfo();

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CUserInfoDlg, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_LIST_USER, &CUserInfoDlg::OnNMClickListUser)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &CUserInfoDlg::OnBnClickedButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CUserInfoDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CUserInfoDlg::OnBnClickedButtonDelete)
END_MESSAGE_MAP()

// CUserInfoDlg message handlers


void CUserInfoDlg::OnNMClickListUser(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE*>(pNMHDR);
	// TODO: Add your control notification handler code here

	DisplayInfo();

	*pResult = 0;
}

void CUserInfoDlg::DisplayInfo()
{
	int nSel = m_List_User.GetSelectionMark();
	if(nSel != -1 && nSel < m_vInfo.size())
	{
		ST_SPIDER_USER_ACCOUNT_INFO stUser = m_vInfo.at(nSel);

		CString sztext;
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_ID), stUser.strID, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_USER_NAME), stUser.strUserName, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_PASSWORD), stUser.strUserPw, sztext);
	}
}

void CUserInfoDlg::InitInfo()
{

	m_List_User.DeleteAllItems();

	m_vInfo.clear();
	long nCount = SPIDER_GetUserAccountCount(theApp.m_hSelectCamera);
	for(int i = 0; i < nCount; i++)
	{
		ST_SPIDER_USER_ACCOUNT_INFO stInfo = {0};
		long lret = SPIDER_GetUserAccountInfo(theApp.m_hSelectCamera, i, &stInfo);
		if(lret != E_CTRL_OK)
		{
			MessageBox(GetErrorString(lret), ("Fail"));
			break;
		}

		m_vInfo.push_back(stInfo);
		CString sztext;

	
		int nSubItem = 1;
		sztext.Format(("%d"), i+1);
		m_List_User.InsertItem(i, sztext);

		sztext = stInfo.strID;
		m_List_User.SetItemText(i, nSubItem++, sztext);

		sztext = stInfo.strUserName;
		m_List_User.SetItemText(i, nSubItem++, sztext);
	}

	m_List_User.SetSelectionMark(0);
	m_List_User.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);

	DisplayInfo();
}

void CUserInfoDlg::OnBnClickedButtonApply()
{
	int nModifyIndex = m_List_User.GetSelectionMark();
	if(nModifyIndex >= m_vInfo.size())
		return;

	ST_SPIDER_USER_ACCOUNT_INFO stNew = m_vInfo.at(nModifyIndex);

	CString sztext;

	GetDlgItem(IDC_EDIT_USER_NAME)->GetWindowText(sztext);
	if(strcmp(stNew.strUserName, "NA"))
		StringCopyTo(sztext, stNew.strUserName);

	GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowText(sztext);
	if(strcmp(stNew.strUserPw, "NA"))
		StringCopyTo(sztext, stNew.strUserPw);

	long lret = SPIDER_SetUserAccountInfo(theApp.m_hSelectCamera, stNew);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));

	InitInfo();
}

void CUserInfoDlg::OnBnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here
	ST_SPIDER_USER_ACCOUNT_INFO stNew = {0};

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

	GetDlgItem(IDC_EDIT_USER_NAME)->GetWindowText(sztext);
	if(strcmp(stNew.strUserName, "NA"))
		StringCopyTo(sztext, stNew.strUserName);

	GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowText(sztext);
	if(strcmp(stNew.strUserPw, "NA"))
		StringCopyTo(sztext, stNew.strUserPw);

	long lret = SPIDER_AddUserAccountInfo(theApp.m_hSelectCamera, stNew);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));

	InitInfo();
}

void CUserInfoDlg::OnBnClickedButtonDelete()
{
	// TODO: Add your control notification handler code here
	int nDeleteIndex = m_List_User.GetSelectionMark();
	if(nDeleteIndex >= m_vInfo.size())
		return;

	long lret = SPIDER_DeleteUserAccountInfo(theApp.m_hSelectCamera, nDeleteIndex);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));

	InitInfo();

}
