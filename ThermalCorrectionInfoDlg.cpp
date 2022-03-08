// ThermalCorrectionInfoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TestDlg.h"
#include "ThermalCorrectionInfoDlg.h"


// CThermalCorrectionInfoDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CThermalCorrectionInfoDlg, CDialog)

CThermalCorrectionInfoDlg::CThermalCorrectionInfoDlg(ST_SPIDER_THERMAL_COMPONENTS* pThermalComponents, CWnd* pParent /*=NULL*/)
	: CDialog(CThermalCorrectionInfoDlg::IDD, pParent)
	, m_pThermalComponents(pThermalComponents)
	, m_fEmissivity(0)
	, m_fTransmission(0)
	, m_fAtmosphere(0)
	, m_fZeroOffset(0)
	, m_nlDistCorr(0)
	, m_bEnable(FALSE)
{
	ZeroMemory(&m_thermalCorrectInfo, sizeof(m_thermalCorrectInfo));
}

CThermalCorrectionInfoDlg::~CThermalCorrectionInfoDlg()
{
}

void CThermalCorrectionInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_ENABLE, m_btnEnable);
	DDX_Control(pDX, IDC_EDIT_EMISSIVITY, m_edtEmissivity);
	DDX_Control(pDX, IDC_EDIT_TRANSMISSION, m_edtTransmission);
	DDX_Control(pDX, IDC_EDIT_ATMOSPHERE, m_edtAtmosphere);
	DDX_Control(pDX, IDC_EDIT_ZERO_OFFSET, m_edtZeroOffset);
	DDX_Control(pDX, IDC_EDIT_DIST_CORR, m_edtDistCorr);
	DDX_Text(pDX, IDC_EDIT_EMISSIVITY, m_fEmissivity);
	DDV_MinMaxFloat(pDX, m_fEmissivity, 0.00, 1.00);
	DDX_Text(pDX, IDC_EDIT_TRANSMISSION, m_fTransmission);
	DDV_MinMaxFloat(pDX, m_fTransmission, 0.00, 1.00);
	DDX_Text(pDX, IDC_EDIT_ATMOSPHERE, m_fAtmosphere);
	DDV_MinMaxFloat(pDX, m_fAtmosphere, -50.0, 100.0);
	DDX_Text(pDX, IDC_EDIT_ZERO_OFFSET, m_fZeroOffset);
	DDV_MinMaxFloat(pDX, m_fZeroOffset, -20.0, 20.0);
	DDX_Text(pDX, IDC_EDIT_DIST_CORR, m_nlDistCorr);
	DDV_MinMaxLong(pDX, m_nlDistCorr, 0, 100);
	DDX_Check(pDX, IDC_CHECK_ENABLE, m_bEnable);
}


BEGIN_MESSAGE_MAP(CThermalCorrectionInfoDlg, CDialog)
	ON_BN_CLICKED(IDC_CHECK_ENABLE, &CThermalCorrectionInfoDlg::OnBnClickedCheckEnable)
	ON_BN_CLICKED(IDC_BUTTON_THERMAL_MODIFY, &CThermalCorrectionInfoDlg::OnBnClickedButtonThermalModify)
END_MESSAGE_MAP()


// CThermalCorrectionInfoDlg 메시지 처리기입니다.


BOOL CThermalCorrectionInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	Initialize();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CThermalCorrectionInfoDlg::Initialize()
{
	m_edtDistCorr.EnableWindow(m_pThermalComponents->bEnableDCE ? TRUE:FALSE);

	ZeroMemory(&m_thermalCorrectInfo, sizeof(m_thermalCorrectInfo));
	long ret = SPIDER_GetThermalCorrectInfo(theApp.m_hSelectCamera, &m_thermalCorrectInfo);
	if (ret == E_CTRL_OK) {
		SetCtrlValue();
	} else {
		MessageBox(_T("Could not get thermal correct info"));
	}
}

void CThermalCorrectionInfoDlg::SetCtrlValue()
{
	m_bEnable		= m_thermalCorrectInfo.bEnable;
	m_fEmissivity	= m_thermalCorrectInfo.fEmissivity;
	m_fTransmission = m_thermalCorrectInfo.fTransmission;
	m_fAtmosphere	= m_thermalCorrectInfo.fAtmosphere;
	m_fZeroOffset	= m_thermalCorrectInfo.fZeroOffset;
	m_nlDistCorr	= m_thermalCorrectInfo.nlDistCorrection;

	UpdateData(FALSE);
	OnBnClickedCheckEnable();
}


void CThermalCorrectionInfoDlg::OnBnClickedCheckEnable()
{
	BOOL bEnable = (m_btnEnable.GetCheck() == BST_CHECKED) ? TRUE:FALSE;
	m_edtEmissivity.EnableWindow(bEnable);
	m_edtTransmission.EnableWindow(bEnable);
	m_edtAtmosphere.EnableWindow(bEnable);
	m_edtZeroOffset.EnableWindow(bEnable);
	m_edtDistCorr.EnableWindow(bEnable && m_pThermalComponents->bEnableDCE);
}



void CThermalCorrectionInfoDlg::OnBnClickedButtonThermalModify()
{
	if (!UpdateData()) {
		return;
	}

	ST_SPIDER_THERMAL_CORRECT_INFO prevThermalCorrectInfo = {NULL, };
	memcpy(&prevThermalCorrectInfo, &m_thermalCorrectInfo, sizeof(ST_SPIDER_THERMAL_CORRECT_INFO));

	m_thermalCorrectInfo.bEnable			= m_bEnable;
	m_thermalCorrectInfo.fEmissivity		= m_fEmissivity;
	m_thermalCorrectInfo.fTransmission		= m_fTransmission;
	m_thermalCorrectInfo.fAtmosphere		= m_fAtmosphere;
	m_thermalCorrectInfo.fZeroOffset		= m_fZeroOffset;
	m_thermalCorrectInfo.nlDistCorrection	= m_nlDistCorr;

	long nlResult = SPIDER_SetThermalCorrectInfo(theApp.m_hSelectCamera, m_thermalCorrectInfo);
	if (nlResult == E_CTRL_OK) {
		MessageBox(_T("Success."));
	} else {
		MessageBox(GetErrorString(nlResult), ("Fail"));
		memcpy(&m_thermalCorrectInfo, &prevThermalCorrectInfo, sizeof(ST_SPIDER_THERMAL_CORRECT_INFO));
		SetCtrlValue();
	}
}
