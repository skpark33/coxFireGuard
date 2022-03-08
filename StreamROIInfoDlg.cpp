// StreamROIInfoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TestDlg.h"
#include "StreamROIInfoDlg.h"


// CStreamROIInfoDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CStreamROIInfoDlg, CDialog)

CStreamROIInfoDlg::CStreamROIInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStreamROIInfoDlg::IDD, pParent)
{
	ZeroMemory(&m_stStreamROIInfo, sizeof(m_stStreamROIInfo));
}

CStreamROIInfoDlg::~CStreamROIInfoDlg()
{
}

void CStreamROIInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ENABLE_1, m_cbEnable1);
	DDX_Control(pDX, IDC_COMBO_ENABLE_2, m_cbEnable2);
	DDX_Control(pDX, IDC_COMBO_ENABLE_3, m_cbEnable3);
	DDX_CBIndex(pDX, IDC_COMBO_ENABLE_1, m_stStreamROIInfo.nSteamROI[0].bEnable);
	DDX_CBIndex(pDX, IDC_COMBO_ENABLE_2, m_stStreamROIInfo.nSteamROI[1].bEnable);
	DDX_CBIndex(pDX, IDC_COMBO_ENABLE_3, m_stStreamROIInfo.nSteamROI[2].bEnable);
	DDX_Text(pDX, IDC_EDIT_START_X_1, m_stStreamROIInfo.nSteamROI[0].nStartX);
	DDX_Text(pDX, IDC_EDIT_START_X_2, m_stStreamROIInfo.nSteamROI[1].nStartX);
	DDX_Text(pDX, IDC_EDIT_START_X_3, m_stStreamROIInfo.nSteamROI[2].nStartX);
	DDX_Text(pDX, IDC_EDIT_START_Y_1, m_stStreamROIInfo.nSteamROI[0].nStartY);
	DDX_Text(pDX, IDC_EDIT_START_Y_2, m_stStreamROIInfo.nSteamROI[1].nStartY);
	DDX_Text(pDX, IDC_EDIT_START_Y_3, m_stStreamROIInfo.nSteamROI[2].nStartY);
	DDX_Text(pDX, IDC_EDIT_WIDTH_1, m_stStreamROIInfo.nSteamROI[0].nWidth);
	DDX_Text(pDX, IDC_EDIT_WIDTH_2, m_stStreamROIInfo.nSteamROI[1].nWidth);
	DDX_Text(pDX, IDC_EDIT_WIDTH_3, m_stStreamROIInfo.nSteamROI[2].nWidth);
	DDX_Text(pDX, IDC_EDIT_HEIGHT_1, m_stStreamROIInfo.nSteamROI[0].nHeight);
	DDX_Text(pDX, IDC_EDIT_HEIGHT_2, m_stStreamROIInfo.nSteamROI[1].nHeight);
	DDX_Text(pDX, IDC_EDIT_HEIGHT_3, m_stStreamROIInfo.nSteamROI[2].nHeight);
	DDX_Control(pDX, IDC_BUTTON_MODIFY1, m_btnModify1);
	DDX_Control(pDX, IDC_BUTTON_MODIFY2, m_btnModify2);
	DDX_Control(pDX, IDC_BUTTON_MODIFY3, m_btnModify3);
	DDX_Control(pDX, IDC_BUTTON_REFRESH, m_btnRefresh);
}


BEGIN_MESSAGE_MAP(CStreamROIInfoDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY1, &CStreamROIInfoDlg::OnBnClickedButtonModify1)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY2, &CStreamROIInfoDlg::OnBnClickedButtonModify2)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY3, &CStreamROIInfoDlg::OnBnClickedButtonModify3)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &CStreamROIInfoDlg::OnBnClickedButtonRefresh)
END_MESSAGE_MAP()


// CStreamROIInfoDlg 메시지 처리기입니다.




BOOL CStreamROIInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CreateComboBox(&m_cbEnable1);
	CreateComboBox(&m_cbEnable2);
	CreateComboBox(&m_cbEnable3);

	OnBnClickedButtonRefresh();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CStreamROIInfoDlg::CreateComboBox(CComboBox* pcbEnable)
{
	pcbEnable->InsertString(0, _T("false"));
	pcbEnable->InsertString(1, _T("true"));
	pcbEnable->SetCurSel(0);
}


void CStreamROIInfoDlg::OnBnClickedButtonModify1()
{
	UpdateData();
	ModifyStreamROI(&m_stStreamROIInfo.nSteamROI[0]);
}


void CStreamROIInfoDlg::OnBnClickedButtonModify2()
{
	UpdateData();
	ModifyStreamROI(&m_stStreamROIInfo.nSteamROI[1]);
}


void CStreamROIInfoDlg::OnBnClickedButtonModify3()
{
	UpdateData();
	ModifyStreamROI(&m_stStreamROIInfo.nSteamROI[2]);
}

void CStreamROIInfoDlg::ModifyStreamROI(ST_SPIDER_STREAM_ROI* pStreamROI)
{
	long ret = SPIDER_SetStreamROI(theApp.m_hSelectCamera, *pStreamROI);
	if (ret == E_CTRL_OK) {
		MessageBox(_T("Success."));
	} else {
		MessageBox(_T("Could not set stream ROI."));
	}
}

void CStreamROIInfoDlg::OnBnClickedButtonRefresh()
{
	BOOL bIsSuccess = FALSE;

	ZeroMemory(&m_stStreamROIInfo, sizeof(m_stStreamROIInfo));
	long ret = SPIDER_GetStreamROI(theApp.m_hSelectCamera, &m_stStreamROIInfo);
	if (ret == E_CTRL_OK) {
		bIsSuccess = TRUE;
	} else {
		MessageBox(_T("Could not get stream ROI info"));
	}

	UpdateData(FALSE);

	m_btnModify1.EnableWindow(bIsSuccess);
	m_btnModify2.EnableWindow(bIsSuccess);
	m_btnModify3.EnableWindow(bIsSuccess);
}
