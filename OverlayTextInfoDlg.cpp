// OverlayTextInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDlg.h"
#include "OverlayTextInfoDlg.h"


// COverlayTextInfoDlg dialog

IMPLEMENT_DYNCREATE(COverlayTextInfoDlg, CDialog)

COverlayTextInfoDlg::COverlayTextInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COverlayTextInfoDlg::IDD, pParent)
{

}

COverlayTextInfoDlg::~COverlayTextInfoDlg()
{
}

void COverlayTextInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_OVERLAY, m_List_Overlay);
}

BOOL COverlayTextInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	m_List_Overlay.SetExtendedStyle( m_List_Overlay.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	int ncol = 0;
	m_List_Overlay.InsertColumn(ncol++, ("Index"), 0, 50);
	m_List_Overlay.InsertColumn(ncol++, ("ID"), 0, 50);
	m_List_Overlay.InsertColumn(ncol++, ("Display Text"), 0, 250);


	InitInfo();

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(COverlayTextInfoDlg, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_OVERLAY, &COverlayTextInfoDlg::OnLvnItemchangedListOverlay)
	ON_NOTIFY(NM_CLICK, IDC_LIST_OVERLAY, &COverlayTextInfoDlg::OnNMClickListOverlay)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY_OVERLAY, &COverlayTextInfoDlg::OnBnClickedButtonModifyOverlay)
	ON_BN_CLICKED(IDC_BUTTON_ADD_OVERLAY, &COverlayTextInfoDlg::OnBnClickedButtonAddOverlay)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_OVERLAY, &COverlayTextInfoDlg::OnBnClickedButtonDeleteOverlay)
END_MESSAGE_MAP()

// COverlayTextInfoDlg message handlers


void COverlayTextInfoDlg::OnLvnItemchangedListOverlay(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void COverlayTextInfoDlg::OnNMClickListOverlay(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE*>(pNMHDR);
	// TODO: Add your control notification handler code here

	DisplayInfo();

	*pResult = 0;
}

void COverlayTextInfoDlg::DisplayInfo()
{
	int nSel = m_List_Overlay.GetSelectionMark();

	if(nSel != -1 && nSel < m_vInfo.size())
	{

		ST_SPIDER_TEXT_INFO stInfo = m_vInfo.at(nSel);

		CString sztext;

		sztext = stInfo.strID;
		GetDlgItem(IDC_EDIT_OVERLAY_ID)->SetWindowText(sztext);


		GetDlgItem(IDC_CHECK_OVERLAY_ENABLE)->EnableWindow(true);
		if(stInfo.nsEnable == 1)
			GetDlgItem(IDC_CHECK_OVERLAY_ENABLE)->SendMessage(BM_SETCHECK, 1, 0);
		else if(stInfo.nsEnable == 0)
			GetDlgItem(IDC_CHECK_OVERLAY_ENABLE)->SendMessage(BM_SETCHECK, 0, 0);
		else
		{
			GetDlgItem(IDC_CHECK_OVERLAY_ENABLE)->EnableWindow(false);
			GetDlgItem(IDC_CHECK_OVERLAY_ENABLE)->SendMessage(BM_SETCHECK, 0, 0);
		}


		GetDlgItem(IDC_CHECK_TIMESTAMP_ENABLE)->EnableWindow(true);
		if(stInfo.nsTimeStampEnable == 1)
			GetDlgItem(IDC_CHECK_TIMESTAMP_ENABLE)->SendMessage(BM_SETCHECK, 1, 0);
		else if(stInfo.nsTimeStampEnable == 0)
			GetDlgItem(IDC_CHECK_TIMESTAMP_ENABLE)->SendMessage(BM_SETCHECK, 0, 0);
		else
		{
			GetDlgItem(IDC_CHECK_TIMESTAMP_ENABLE)->EnableWindow(false);
			GetDlgItem(IDC_CHECK_TIMESTAMP_ENABLE)->SendMessage(BM_SETCHECK, 0, 0);
		}




		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_DATETIME_FORMAT), stInfo.strDateTimeFormat, sztext);
		if(stInfo.nsTimeStampEnable == 0)
			GetDlgItem(IDC_EDIT_DATETIME_FORMAT)->EnableWindow(false);


		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_BACK_COLOR), stInfo.strBackColor, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_FONT_COLOR), stInfo.strFontColor, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_FONT_SIZE), stInfo.nsFontSize, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_DISPLAY_TEXT), stInfo.strDisplayText, sztext);

		if(strcmp(stInfo.strBackColor, "NA") == 0)
			GetDlgItem(IDC_BUTTON_BACK_COLORDLG)->EnableWindow(false);
		else
			GetDlgItem(IDC_BUTTON_BACK_COLORDLG)->EnableWindow(true);

		if(strcmp(stInfo.strFontColor, "NA") == 0)
			GetDlgItem(IDC_BUTTON_FONT_COLORDLG)->EnableWindow(false);
		else
			GetDlgItem(IDC_BUTTON_FONT_COLORDLG)->EnableWindow(true);



		//XPM_ALIGN_TYPE_LEFT = 0, // "left"
		//XPM_ALIGN_TYPE_RIGHT,	 // "right"
		//XPM_ALIGN_TYPE_CENTER,	 // "center"
		//XPM_ALIGN_TYPE_TOP,		 // "top"
		//XPM_ALIGN_TYPE_BOTTOM	 // "bottom"
		GetDlgItem(IDC_RADIO_HORIZENTAL_LEFT)->EnableWindow(true);
		GetDlgItem(IDC_RADIO_HORIZENTAL_RIGHT)->EnableWindow(true);
		GetDlgItem(IDC_RADIO_HORIZENTAL_CENTER)->EnableWindow(true);
		switch(stInfo.nsHoriAlignType)
		{
		case 0:
			{
				GetDlgItem(IDC_RADIO_HORIZENTAL_LEFT)->SendMessage(BM_SETCHECK, 1, 0);
				GetDlgItem(IDC_RADIO_HORIZENTAL_RIGHT)->SendMessage(BM_SETCHECK, 0, 0);
				GetDlgItem(IDC_RADIO_HORIZENTAL_CENTER)->SendMessage(BM_SETCHECK, 0, 0);
			}
			break;
		case 1:
			{
				GetDlgItem(IDC_RADIO_HORIZENTAL_LEFT)->SendMessage(BM_SETCHECK, 0, 0);
				GetDlgItem(IDC_RADIO_HORIZENTAL_RIGHT)->SendMessage(BM_SETCHECK, 1, 0);
				GetDlgItem(IDC_RADIO_HORIZENTAL_CENTER)->SendMessage(BM_SETCHECK, 0, 0);
			}
			break;
		case 2:
			{
				GetDlgItem(IDC_RADIO_HORIZENTAL_LEFT)->SendMessage(BM_SETCHECK, 0, 0);
				GetDlgItem(IDC_RADIO_HORIZENTAL_RIGHT)->SendMessage(BM_SETCHECK, 0, 0);
				GetDlgItem(IDC_RADIO_HORIZENTAL_CENTER)->SendMessage(BM_SETCHECK, 1, 0);
			}
			break;
		default:
			{
				GetDlgItem(IDC_RADIO_HORIZENTAL_LEFT)->EnableWindow(false);
				GetDlgItem(IDC_RADIO_HORIZENTAL_RIGHT)->EnableWindow(false);
				GetDlgItem(IDC_RADIO_HORIZENTAL_CENTER)->EnableWindow(false);
				GetDlgItem(IDC_RADIO_HORIZENTAL_LEFT)->SendMessage(BM_SETCHECK, 0, 0);
				GetDlgItem(IDC_RADIO_HORIZENTAL_RIGHT)->SendMessage(BM_SETCHECK, 0, 0);
				GetDlgItem(IDC_RADIO_HORIZENTAL_CENTER)->SendMessage(BM_SETCHECK, 0, 0);
			}
			break;
		}




		GetDlgItem(IDC_RADIO_VERTICAL_TOP)->EnableWindow(true);
		GetDlgItem(IDC_RADIO_VERTICAL_BOTTOM)->EnableWindow(true);
		switch(stInfo.nsVertAlignType)
		{
		case 3:
			{
				GetDlgItem(IDC_RADIO_VERTICAL_TOP)->SendMessage(BM_SETCHECK, 1, 0);
				GetDlgItem(IDC_RADIO_VERTICAL_BOTTOM)->SendMessage(BM_SETCHECK, 0, 0);
			}
			break;
		case 4:
			{
				GetDlgItem(IDC_RADIO_VERTICAL_TOP)->SendMessage(BM_SETCHECK, 0, 0);
				GetDlgItem(IDC_RADIO_VERTICAL_BOTTOM)->SendMessage(BM_SETCHECK, 1, 0);
			}
			break;
		default:
			{
				GetDlgItem(IDC_RADIO_VERTICAL_TOP)->EnableWindow(false);
				GetDlgItem(IDC_RADIO_VERTICAL_BOTTOM)->EnableWindow(false);
				GetDlgItem(IDC_RADIO_VERTICAL_TOP)->SendMessage(BM_SETCHECK, 0, 0);
				GetDlgItem(IDC_RADIO_VERTICAL_BOTTOM)->SendMessage(BM_SETCHECK, 0, 0);
			}
			break;
		}

	}
}


void COverlayTextInfoDlg::InitInfo()
{

	m_List_Overlay.DeleteAllItems();

	m_vInfo.clear();
	long nCount = SPIDER_GetTextOverlayCount(theApp.m_hSelectCamera);
	for(int i = 0; i < nCount; i++)
	{
		ST_SPIDER_TEXT_INFO stInfo = {0};
		long lret = SPIDER_GetTextOverlayInfo(theApp.m_hSelectCamera, i, &stInfo);
		if(lret != E_CTRL_OK)
		{
			MessageBox(GetErrorString(lret), ("Fail"));
			break;
		}

		m_vInfo.push_back(stInfo);
		CString sztext;
			
		sztext.Format(("%d"), i+1);
		m_List_Overlay.InsertItem(i, sztext);


		int ncol = 1;

		sztext = stInfo.strID;
		m_List_Overlay.SetItemText(i, ncol++, sztext);

		sztext = stInfo.strDisplayText;
		m_List_Overlay.SetItemText(i, ncol++, sztext);
	}

	m_List_Overlay.SetSelectionMark(0);
	m_List_Overlay.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);

	DisplayInfo();
}

void COverlayTextInfoDlg::OnBnClickedButtonModifyOverlay()
{
	int nModifyIndex = m_List_Overlay.GetSelectionMark();
	if(nModifyIndex >= m_vInfo.size())
		return;

	ST_SPIDER_TEXT_INFO stNew = m_vInfo.at(nModifyIndex);

	CString sztext;


	if(stNew.nsEnable != 0xFFFF && stNew.nsEnable != 0xFFFFFFFF)
		stNew.nsEnable = GetDlgItem(IDC_CHECK_OVERLAY_ENABLE)->SendMessage(BM_GETCHECK);

	if(stNew.nsTimeStampEnable != 0xFFFF && stNew.nsTimeStampEnable != 0xFFFFFFFF)
		stNew.nsTimeStampEnable = GetDlgItem(IDC_CHECK_TIMESTAMP_ENABLE)->SendMessage(BM_GETCHECK);


	GetDlgItem(IDC_EDIT_DATETIME_FORMAT)->GetWindowText(sztext);
	if(strcmp(stNew.strDateTimeFormat, "NA"))
		StringCopyTo(sztext, stNew.strDateTimeFormat);

	GetDlgItem(IDC_EDIT_BACK_COLOR)->GetWindowText(sztext);
	if(strcmp(stNew.strBackColor, "NA"))
		StringCopyTo(sztext, stNew.strBackColor);

	GetDlgItem(IDC_EDIT_FONT_COLOR)->GetWindowText(sztext);
	if(strcmp(stNew.strFontColor, "NA"))
		StringCopyTo(sztext, stNew.strFontColor);

	GetDlgItem(IDC_EDIT_DISPLAY_TEXT)->GetWindowText(sztext);
	if(strcmp(stNew.strDisplayText, "NA"))
		StringCopyTo(sztext, stNew.strDisplayText);


	int nValue = 0;
	GetDlgItem(IDC_EDIT_FONT_SIZE)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nsFontSize != 0xFFFF && stNew.nsFontSize != 0xFFFFFFFF)
		stNew.nsFontSize = nValue;


	if(stNew.nsHoriAlignType != 0xFFFF && stNew.nsHoriAlignType != 0xFFFFFFFF)
	{
		if(GetDlgItem(IDC_RADIO_HORIZENTAL_LEFT)->SendMessage(BM_GETCHECK) == BST_CHECKED)
			stNew.nsHoriAlignType = 0;
		else if(GetDlgItem(IDC_RADIO_HORIZENTAL_RIGHT)->SendMessage(BM_GETCHECK) == BST_CHECKED)
			stNew.nsHoriAlignType = 1;
		else if(GetDlgItem(IDC_RADIO_HORIZENTAL_CENTER)->SendMessage(BM_GETCHECK) == BST_CHECKED)
			stNew.nsHoriAlignType = 2;
	}

	if(stNew.nsVertAlignType != 0xFFFF && stNew.nsVertAlignType != 0xFFFFFFFF)
	{
		if(GetDlgItem(IDC_RADIO_VERTICAL_TOP)->SendMessage(BM_GETCHECK) == BST_CHECKED)
			stNew.nsHoriAlignType = 3;
		else if(GetDlgItem(IDC_RADIO_VERTICAL_BOTTOM)->SendMessage(BM_GETCHECK) == BST_CHECKED)
			stNew.nsHoriAlignType = 4;
	}

	long lret = SPIDER_SetTextOverlayInfo(theApp.m_hSelectCamera, stNew);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));

	InitInfo();
}

void COverlayTextInfoDlg::OnBnClickedButtonAddOverlay()
{
	// TODO: Add your control notification handler code here


	//reserved.


	//ST_SPIDER_TEXT_INFO stNew = {0};

	//if(m_vInfo.size())
	//	stNew = m_vInfo.at(0);

	////make new id
	//bool bNext = true;
	//int nID = 0;
	//while(bNext == true)
	//{
	//	sprintf(stNew.strID, "%d", nID);

	//	bNext = false;
	//	int nIndex = 0;
	//	while(nIndex < m_vInfo.size())
	//	{
	//		if(strcmp(stNew.strID, m_vInfo.at(nIndex).strID) == 0)
	//		{
	//			bNext = true;
	//			break;
	//		}

	//		nIndex++;
	//	}

	//	nID++;
	//}


	//CString sztext;


	//if(stNew.nsEnable != 0xFFFF && stNew.nsEnable != 0xFFFFFFFF)
	//	stNew.nsEnable = GetDlgItem(IDC_CHECK_OVERLAY_ENABLE)->SendMessage(BM_GETCHECK);

	//if(stNew.nsTimeStampEnable != 0xFFFF && stNew.nsTimeStampEnable != 0xFFFFFFFF)
	//	stNew.nsTimeStampEnable = GetDlgItem(IDC_CHECK_TIMESTAMP_ENABLE)->SendMessage(BM_GETCHECK);


	//GetDlgItem(IDC_EDIT_DATETIME_FORMAT)->GetWindowText(sztext);
	//if(strcmp(stNew.strDateTimeFormat, "NA"))
	//	StringCopyTo(sztext, stNew.strDateTimeFormat);

	//GetDlgItem(IDC_EDIT_BACK_COLOR)->GetWindowText(sztext);
	//if(strcmp(stNew.strBackColor, "NA"))
	//	StringCopyTo(sztext, stNew.strBackColor);

	//GetDlgItem(IDC_EDIT_FONT_COLOR)->GetWindowText(sztext);
	//if(strcmp(stNew.strFontColor, "NA"))
	//	StringCopyTo(sztext, stNew.strFontColor);

	//GetDlgItem(IDC_EDIT_DISPLAY_TEXT)->GetWindowText(sztext);
	//if(strcmp(stNew.strDisplayText, "NA"))
	//	StringCopyTo(sztext, stNew.strDisplayText);


	//int nValue = 0;
	//GetDlgItem(IDC_EDIT_FONT_SIZE)->GetWindowText(sztext);
	//nValue = _ttoi(sztext);
	//if(stNew.nsFontSize != 0xFFFF && stNew.nsFontSize != 0xFFFFFFFF)
	//	stNew.nsFontSize = nValue;


	//if(stNew.nsHoriAlignType != 0xFFFF && stNew.nsHoriAlignType != 0xFFFFFFFF)
	//{
	//	if(GetDlgItem(IDC_RADIO_HORIZENTAL_LEFT)->SendMessage(BM_GETCHECK) == BST_CHECKED)
	//		stNew.nsHoriAlignType = 0;
	//	else if(GetDlgItem(IDC_RADIO_HORIZENTAL_RIGHT)->SendMessage(BM_GETCHECK) == BST_CHECKED)
	//		stNew.nsHoriAlignType = 1;
	//	else if(GetDlgItem(IDC_RADIO_HORIZENTAL_CENTER)->SendMessage(BM_GETCHECK) == BST_CHECKED)
	//		stNew.nsHoriAlignType = 2;
	//}

	//if(stNew.nsVertAlignType != 0xFFFF && stNew.nsVertAlignType != 0xFFFFFFFF)
	//{
	//	if(GetDlgItem(IDC_RADIO_VERTICAL_TOP)->SendMessage(BM_GETCHECK) == BST_CHECKED)
	//		stNew.nsHoriAlignType = 3;
	//	else if(GetDlgItem(IDC_RADIO_VERTICAL_BOTTOM)->SendMessage(BM_GETCHECK) == BST_CHECKED)
	//		stNew.nsHoriAlignType = 4;
	//}

	//long lret = SPIDER_AddTextOverlayInfo(theApp.m_hSelectCamera, stNew);
	//if(lret != E_CTRL_OK)
	//	MessageBox(GetErrorString(lret), ("Fail"));
	//else
	//	MessageBox(("Success."));


	//InitInfo();
}

void COverlayTextInfoDlg::OnBnClickedButtonDeleteOverlay()
{
	// TODO: Add your control notification handler code here


	//reserved.



	//int nDeleteIndex = m_List_Overlay.GetSelectionMark();
	//if(nDeleteIndex >= m_vInfo.size())
	//	return;

	//long lret = SPIDER_DeleteTextOverlayInfo(theApp.m_hSelectCamera, nDeleteIndex);
	//if(lret != E_CTRL_OK)
	//	MessageBox(GetErrorString(lret), ("Fail"));
	//else
	//	MessageBox(("Success."));


	//InitInfo();
}
