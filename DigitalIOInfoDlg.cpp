// DigitalIOInfoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TestDlg.h"
#include "DigitalIOInfoDlg.h"


// CDigitalIOInfoDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDigitalIOInfoDlg, CDialog)

CDigitalIOInfoDlg::CDigitalIOInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDigitalIOInfoDlg::IDD, pParent)
	, m_nlOutputDuration(0)
	, m_nlToggleInterval(200)
	, m_nlMaxDuration(1)
{
	ZeroMemory(&m_DigitalInputInfo, sizeof(m_DigitalInputInfo));
	ZeroMemory(&m_DigitalOutputInfo, sizeof(m_DigitalOutputInfo));
}

CDigitalIOInfoDlg::~CDigitalIOInfoDlg()
{
}

void CDigitalIOInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_INPUT, m_lstCtrlInput);
	DDX_Control(pDX, IDC_EDIT_INPUT_ID, m_edtInputID);
	DDX_Control(pDX, IDC_COMBO_INPUT_ENABLE, m_cbInputEnable);
	DDX_Control(pDX, IDC_COMBO_INPUT_ACTIVE, m_cbInputActive);
	DDX_Control(pDX, IDC_LIST_OUTPUT, m_lstCtrlOutput);
	DDX_Control(pDX, IDC_EDIT_OUTPUT_ID, m_edtOutputID);
	DDX_Control(pDX, IDC_COMBO_OUTPUT_ENABLE, m_cbOutputEnable);
	DDX_Control(pDX, IDC_COMBO_OUTPUT_ACTIVE, m_cbOutputActive);
	DDX_Control(pDX, IDC_EDIT_OUTPUT_DURATION, m_edtOutputDuration);
	DDX_Text(pDX, IDC_EDIT_OUTPUT_DURATION, m_nlOutputDuration);
	DDV_MinMaxLong(pDX, m_nlOutputDuration, 0, 10000);
	DDX_Control(pDX, IDC_BUTTON_INPUT_MODIFY, m_btnInputModify);
	DDX_Control(pDX, IDC_BUTTON_OUTPUT_MODIFY, m_btnOutputModify);
	DDX_Control(pDX, IDC_EDIT_OUTPUT_TOGGLE_ID, m_edtOutputToggleID);
	DDX_Control(pDX, IDC_COMBO_OUTPUT_TOGGLE_ENABLE, m_cbOuputToggleEnable);
	DDX_Control(pDX, IDC_EDIT_OUTPUT_TOGGLE_INTERVAL, m_edtOutputToggleInterval);
	DDX_Text(pDX, IDC_EDIT_OUTPUT_TOGGLE_INTERVAL, m_nlToggleInterval);
	DDV_MinMaxLong(pDX, m_nlToggleInterval, 200, 5000);
	DDX_Text(pDX, IDC_EDIT_OUTPUT_MAX_DURATION, m_nlMaxDuration);
	DDV_MinMaxLong(pDX, m_nlMaxDuration, 1, 86400);
}


BEGIN_MESSAGE_MAP(CDigitalIOInfoDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_INPUT_MODIFY, &CDigitalIOInfoDlg::OnBnClickedButtonInputModify)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT_MODIFY, &CDigitalIOInfoDlg::OnBnClickedButtonOutputModify)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_INPUT, &CDigitalIOInfoDlg::OnLvnItemchangedListInput)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_OUTPUT, &CDigitalIOInfoDlg::OnLvnItemchangedListOutput)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT_TOGGLE_SET, &CDigitalIOInfoDlg::OnBnClickedButtonOutputToggleSet)
	ON_CBN_SELCHANGE(IDC_COMBO_OUTPUT_TOGGLE_ENABLE, &CDigitalIOInfoDlg::OnCbnSelchangeComboOutputToggleEnable)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT_EXECUTE, &CDigitalIOInfoDlg::OnBnClickedButtonOutputExecute)
END_MESSAGE_MAP()


// CDigitalIOInfoDlg 메시지 처리기입니다.


BOOL CDigitalIOInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitDigitalInput();
	InitDigitalOutput();

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CDigitalIOInfoDlg::InitDigitalInput()
{
	CRect rect;
	m_lstCtrlInput.GetClientRect(rect);

	m_lstCtrlInput.InsertColumn(0, _T("ID"),		LVCFMT_LEFT, rect.Width()/3);
	m_lstCtrlInput.InsertColumn(1, _T("Enable"),	LVCFMT_LEFT, rect.Width()/3);
	m_lstCtrlInput.InsertColumn(2, _T("Active"),	LVCFMT_LEFT, rect.Width()/3);
	m_lstCtrlInput.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_cbInputEnable.AddString(_T("disable"));
	m_cbInputEnable.AddString(_T("enable"));

	m_cbInputActive.AddString(_T("inactive"));
	m_cbInputActive.AddString(_T("active"));

	m_cbOuputToggleEnable.AddString(_T("disable"));
	m_cbOuputToggleEnable.AddString(_T("enable"));
	m_cbOuputToggleEnable.SetCurSel(1);

	ZeroMemory(&m_DigitalInputInfo, sizeof(m_DigitalInputInfo));
	long ret = SPIDER_GetDigitalInput(theApp.m_hSelectCamera, &m_DigitalInputInfo);
	if (ret == E_CTRL_OK) {
		CString strText = _T("");
		for (size_t i=0; i<m_DigitalInputInfo.nTotalCnt; i++) {
			ST_SPIDER_DIGITAL_INPUT_INFO* pDigitalInputInfo = &m_DigitalInputInfo.stDigitalInputInfo[i];
			strText.Format(_T("%d"), pDigitalInputInfo->nID);
			int nItem = m_lstCtrlInput.InsertItem(LVIF_TEXT|LVIF_PARAM, m_lstCtrlInput.GetItemCount(), strText, 0, 0, -1, (LPARAM)pDigitalInputInfo);
			if (nItem != -1) {
				m_lstCtrlInput.SetItemText(nItem, 1, pDigitalInputInfo->bEnabled ? _T("enable"):_T("disable"));
				m_lstCtrlInput.SetItemText(nItem, 2, pDigitalInputInfo->bActived ? _T("active"):_T("inactive"));
			}
		}
		m_lstCtrlInput.SetItemState(0, LVIS_SELECTED ,LVIS_SELECTED);
	} else {
		m_btnInputModify.EnableWindow(FALSE);
	}
}

void CDigitalIOInfoDlg::OnBnClickedButtonInputModify()
{
	POSITION pos = m_lstCtrlInput.GetFirstSelectedItemPosition();
	if (pos) {
		int nItem = m_lstCtrlInput.GetNextSelectedItem(pos);
		ST_SPIDER_DIGITAL_INPUT_INFO* pDigitalInputInfo = (ST_SPIDER_DIGITAL_INPUT_INFO*)m_lstCtrlInput.GetItemData(nItem);
		if (pDigitalInputInfo) {
			ST_SPIDER_DIGITAL_INPUT_INFO stInfo = {NULL, };
			memcpy(&stInfo, pDigitalInputInfo, sizeof(ST_SPIDER_DIGITAL_INPUT_INFO));
			stInfo.bEnabled = (m_cbInputEnable.GetCurSel() == 1) ? TRUE:FALSE;
			stInfo.bActived = (m_cbInputActive.GetCurSel() == 1) ? TRUE:FALSE;

			long nlRet = SPIDER_SetDigitalInput(theApp.m_hSelectCamera, stInfo);
			if (nlRet != E_CTRL_OK) {
				MessageBox(GetErrorString(nlRet), _T("Fail"));
			} else {
				MessageBox(_T("Success."));
				memcpy(pDigitalInputInfo, &stInfo, sizeof(ST_SPIDER_DIGITAL_INPUT_INFO));
				UpdateDigitalInputInfo(pDigitalInputInfo);

				m_lstCtrlInput.SetItemText(nItem, 1, pDigitalInputInfo->bEnabled ? _T("enable"):_T("disable"));
				m_lstCtrlInput.SetItemText(nItem, 2, pDigitalInputInfo->bActived ? _T("active"):_T("inactive"));
			}
		}	
	}
}

void CDigitalIOInfoDlg::InitDigitalOutput()
{
	CRect rect;
	m_lstCtrlOutput.GetClientRect(rect);

	m_lstCtrlOutput.InsertColumn(0, _T("ID"),		LVCFMT_LEFT, rect.Width()/4);
	m_lstCtrlOutput.InsertColumn(1, _T("Enable"),	LVCFMT_LEFT, rect.Width()/4);
	m_lstCtrlOutput.InsertColumn(2, _T("Active"),	LVCFMT_LEFT, rect.Width()/4);
	m_lstCtrlOutput.InsertColumn(3, _T("Duration"),	LVCFMT_LEFT, rect.Width()/4);
	m_lstCtrlOutput.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_cbOutputEnable.AddString(_T("disable"));
	m_cbOutputEnable.AddString(_T("enable"));

	m_cbOutputActive.AddString(_T("inactive"));
	m_cbOutputActive.AddString(_T("active"));

	ZeroMemory(&m_DigitalOutputInfo, sizeof(m_DigitalOutputInfo));
	long ret = SPIDER_GetDigitalOutput(theApp.m_hSelectCamera, &m_DigitalOutputInfo);
	if (ret == E_CTRL_OK) {
		CString strText = _T("");
		CString strDuration = _T("");
		for (size_t i=0; i<m_DigitalOutputInfo.nTotalCnt; i++) {
			ST_SPIDER_DIGITAL_OUTPUT_INFO* pDigitalOutputInfo = &m_DigitalOutputInfo.stDigitalOutputInfo[i];
			strText.Format(_T("%d"), pDigitalOutputInfo->nID);
			int nItem = m_lstCtrlOutput.InsertItem(LVIF_TEXT|LVIF_PARAM, m_lstCtrlOutput.GetItemCount(), strText, 0, 0, -1, (LPARAM)pDigitalOutputInfo);
			if (nItem != -1) {
				m_lstCtrlOutput.SetItemText(nItem, 1, pDigitalOutputInfo->bEnabled ? _T("enable"):_T("disable"));
				m_lstCtrlOutput.SetItemText(nItem, 2, pDigitalOutputInfo->bActived ? _T("active"):_T("inactive"));
				strDuration.Format(_T("%d"), pDigitalOutputInfo->nlDuration);
				m_lstCtrlOutput.SetItemText(nItem, 3, strDuration);
			}
		}
		m_lstCtrlOutput.SetItemState(0, LVIS_SELECTED ,LVIS_SELECTED);
	} else {
		m_btnOutputModify.EnableWindow(FALSE);
	}
}

void CDigitalIOInfoDlg::OnBnClickedButtonOutputModify()
{
	UpdateData();

	if (m_nlOutputDuration >= 0 && m_nlOutputDuration <= 10000) {
		POSITION pos = m_lstCtrlOutput.GetFirstSelectedItemPosition();
		if (pos) {
			int nItem = m_lstCtrlOutput.GetNextSelectedItem(pos);
			ST_SPIDER_DIGITAL_OUTPUT_INFO* pDigitalOutputInfo = (ST_SPIDER_DIGITAL_OUTPUT_INFO*)m_lstCtrlOutput.GetItemData(nItem);
			if (pDigitalOutputInfo) {
				ST_SPIDER_DIGITAL_OUTPUT_INFO stInfo = {NULL, };
				memcpy(&stInfo, pDigitalOutputInfo, sizeof(ST_SPIDER_DIGITAL_OUTPUT_INFO));
				stInfo.bEnabled = (m_cbOutputEnable.GetCurSel() == 1) ? TRUE:FALSE;
				stInfo.bActived = (m_cbOutputActive.GetCurSel() == 1) ? TRUE:FALSE;
				stInfo.nlDuration = m_nlOutputDuration;

				long nlRet = SPIDER_SetDigitalOutput(theApp.m_hSelectCamera, stInfo);
				if (nlRet != E_CTRL_OK) {
					MessageBox(GetErrorString(nlRet), _T("Fail"));
				} else {
					MessageBox(_T("Success."));
					memcpy(pDigitalOutputInfo, &stInfo, sizeof(ST_SPIDER_DIGITAL_OUTPUT_INFO));
					UpdateDigitalOutputInfo(pDigitalOutputInfo);

					m_lstCtrlOutput.SetItemText(nItem, 1, pDigitalOutputInfo->bEnabled ? _T("enable"):_T("disable"));
					m_lstCtrlOutput.SetItemText(nItem, 2, pDigitalOutputInfo->bActived ? _T("active"):_T("inactive"));
					CString strDuration = _T("");
					strDuration.Format(_T("%d"), pDigitalOutputInfo->nlDuration);
					m_lstCtrlOutput.SetItemText(nItem, 3, strDuration);
				}
			}	
		}
	}
}


void CDigitalIOInfoDlg::OnLvnItemchangedListInput(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	ST_SPIDER_DIGITAL_INPUT_INFO* pDigitalInputInfo = (ST_SPIDER_DIGITAL_INPUT_INFO*)pNMLV->lParam;
	if (pDigitalInputInfo) {
		UpdateDigitalInputInfo(pDigitalInputInfo);
	}

	*pResult = 0;
}

void CDigitalIOInfoDlg::UpdateDigitalInputInfo(ST_SPIDER_DIGITAL_INPUT_INFO* pDigitalInputInfo)
{
	CString strInputID = _T("");
	strInputID.Format(_T("%d"), pDigitalInputInfo->nID);

	m_edtInputID.SetWindowText(strInputID);
	m_cbInputEnable.SetCurSel(pDigitalInputInfo->bEnabled ? 1:0);
	m_cbInputActive.SetCurSel(pDigitalInputInfo->bActived ? 1:0);
}

void CDigitalIOInfoDlg::OnLvnItemchangedListOutput(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	ST_SPIDER_DIGITAL_OUTPUT_INFO* pDigitalOutputInfo = (ST_SPIDER_DIGITAL_OUTPUT_INFO*)pNMLV->lParam;
	if (pDigitalOutputInfo) {
		UpdateDigitalOutputInfo(pDigitalOutputInfo);
	}
	*pResult = 0;
}

void CDigitalIOInfoDlg::UpdateDigitalOutputInfo(ST_SPIDER_DIGITAL_OUTPUT_INFO* pDigitalOutputInfo)
{
	CString strOutputID = _T("");
	strOutputID.Format(_T("%d"), pDigitalOutputInfo->nID);

	m_edtOutputID.SetWindowText(strOutputID);
	m_cbOutputEnable.SetCurSel(pDigitalOutputInfo->bEnabled ? 1:0);
	m_cbOutputActive.SetCurSel(pDigitalOutputInfo->bActived ? 1:0);

	CString strDuration = _T("");
	strDuration.Format(_T("%d"), pDigitalOutputInfo->nlDuration);
	m_edtOutputDuration.SetWindowText(strDuration);

	m_edtOutputToggleID.SetWindowText(strOutputID);
}

void CDigitalIOInfoDlg::OnBnClickedButtonOutputToggleSet()
{
	UpdateData();

	if (m_nlToggleInterval >= 200 && m_nlToggleInterval <= 5000) {
		if (m_nlMaxDuration >= 1 && m_nlMaxDuration <= 86400) {
			POSITION pos = m_lstCtrlOutput.GetFirstSelectedItemPosition();
			if (pos) {
				int nItem = m_lstCtrlOutput.GetNextSelectedItem(pos);
				ST_SPIDER_DIGITAL_OUTPUT_INFO* pDigitalOutputInfo = (ST_SPIDER_DIGITAL_OUTPUT_INFO*)m_lstCtrlOutput.GetItemData(nItem);
				if (pDigitalOutputInfo) {
					bool bEnable = (m_cbOuputToggleEnable.GetCurSel() == 1) ? true:false;

					long nlRet = SPIDER_SetDigitalOutputToggling(theApp.m_hSelectCamera, pDigitalOutputInfo->nID, bEnable, m_nlToggleInterval, m_nlMaxDuration);
					if (nlRet != E_CTRL_OK) {
						MessageBox(GetErrorString(nlRet), _T("Fail"));
					} else {
						MessageBox(_T("Success."));
					}
				}
			}
		}
	}
}


void CDigitalIOInfoDlg::OnCbnSelchangeComboOutputToggleEnable()
{
	BOOL bEnable = (m_cbOuputToggleEnable.GetCurSel() == 1) ? TRUE:FALSE;
	m_edtOutputToggleInterval.EnableWindow(bEnable);
}


void CDigitalIOInfoDlg::OnBnClickedButtonOutputExecute()
{
	POSITION pos = m_lstCtrlOutput.GetFirstSelectedItemPosition();
	if (pos) {
		int nItem = m_lstCtrlOutput.GetNextSelectedItem(pos);
		ST_SPIDER_DIGITAL_OUTPUT_INFO* pDigitalOutputInfo = (ST_SPIDER_DIGITAL_OUTPUT_INFO*)m_lstCtrlOutput.GetItemData(nItem);
		if (pDigitalOutputInfo) {
			BOOL bActive = (m_cbOutputActive.GetCurSel() == 1) ? TRUE:FALSE;

			long nlRet = SPIDER_ExeDigitalOutput(theApp.m_hSelectCamera, pDigitalOutputInfo->nID, bActive);
			if (nlRet != E_CTRL_OK) {
				MessageBox(GetErrorString(nlRet), _T("Fail"));
			} else {
				MessageBox(_T("Success."));
				pDigitalOutputInfo->bActived = bActive;
				m_lstCtrlOutput.SetItemText(nItem, 2, pDigitalOutputInfo->bActived ? _T("active"):_T("inactive"));
			}
		}	
	}
}
