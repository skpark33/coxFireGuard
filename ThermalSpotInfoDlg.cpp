// ThermalSpotInfoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TestDlg.h"
#include "ThermalSpotInfoDlg.h"


// CThermalSpotInfoDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CThermalSpotInfoDlg, CDialog)

CThermalSpotInfoDlg::CThermalSpotInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CThermalSpotInfoDlg::IDD, pParent)
	, m_strMinCoordinate(_T(""))
	, m_strMaxCoordinate(_T(""))
{
	ZeroMemory(&m_stThermalSpotInfo, sizeof(m_stThermalSpotInfo));
}

CThermalSpotInfoDlg::~CThermalSpotInfoDlg()
{
}

void CThermalSpotInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MIN_TEMPERATURE, m_stThermalSpotInfo.fMinTemperature);
	DDX_Text(pDX, IDC_EDIT_MIN_COOR, m_strMinCoordinate);
	DDX_Text(pDX, IDC_EDIT_MAX_TEMPERATURE, m_stThermalSpotInfo.fMaxTemperature);
	DDX_Text(pDX, IDC_EDIT_MAX_COOR, m_strMaxCoordinate);
	DDX_Text(pDX, IDC_EDIT_CENTER_TEMPERATURE, m_stThermalSpotInfo.fCenterTemperature);
	DDX_Text(pDX, IDC_EDIT_AVR_TEMPERATURE, m_stThermalSpotInfo.fAverageTemperature);

	DDX_Control(pDX, IDC_COMBO_ENABLE_1, m_cbEnable[0]);
	DDX_CBIndex(pDX, IDC_COMBO_ENABLE_1, m_stThermalSpotInfo.spotInfo[0].bEnable);
	DDX_Text(pDX, IDC_EDIT_X_1, m_stThermalSpotInfo.spotInfo[0].posSpot.nPositionX);
	DDX_Text(pDX, IDC_EDIT_Y_1, m_stThermalSpotInfo.spotInfo[0].posSpot.nPositionY);
	DDX_Text(pDX, IDC_EDIT_TEMPERATURE_1, m_stThermalSpotInfo.spotInfo[0].fTemperature);
	DDX_Control(pDX, IDC_BUTTON_MODIFY1, m_btnModify[0]);

	DDX_Control(pDX, IDC_COMBO_ENABLE_2, m_cbEnable[1]);
	DDX_CBIndex(pDX, IDC_COMBO_ENABLE_2, m_stThermalSpotInfo.spotInfo[1].bEnable);
	DDX_Text(pDX, IDC_EDIT_X_2, m_stThermalSpotInfo.spotInfo[1].posSpot.nPositionX);
	DDX_Text(pDX, IDC_EDIT_Y_2, m_stThermalSpotInfo.spotInfo[1].posSpot.nPositionY);
	DDX_Text(pDX, IDC_EDIT_TEMPERATURE_2, m_stThermalSpotInfo.spotInfo[1].fTemperature);
	DDX_Control(pDX, IDC_BUTTON_MODIFY2, m_btnModify[1]);

	DDX_Control(pDX, IDC_COMBO_ENABLE_3, m_cbEnable[2]);
	DDX_CBIndex(pDX, IDC_COMBO_ENABLE_3, m_stThermalSpotInfo.spotInfo[2].bEnable);
	DDX_Text(pDX, IDC_EDIT_X_3, m_stThermalSpotInfo.spotInfo[2].posSpot.nPositionX);
	DDX_Text(pDX, IDC_EDIT_Y_3, m_stThermalSpotInfo.spotInfo[2].posSpot.nPositionY);
	DDX_Text(pDX, IDC_EDIT_TEMPERATURE_3, m_stThermalSpotInfo.spotInfo[2].fTemperature);
	DDX_Control(pDX, IDC_BUTTON_MODIFY3, m_btnModify[2]);

	DDX_Control(pDX, IDC_COMBO_ENABLE_4, m_cbEnable[3]);
	DDX_CBIndex(pDX, IDC_COMBO_ENABLE_4, m_stThermalSpotInfo.spotInfo[3].bEnable);
	DDX_Text(pDX, IDC_EDIT_X_4, m_stThermalSpotInfo.spotInfo[3].posSpot.nPositionX);
	DDX_Text(pDX, IDC_EDIT_Y_4, m_stThermalSpotInfo.spotInfo[3].posSpot.nPositionY);
	DDX_Text(pDX, IDC_EDIT_TEMPERATURE_4, m_stThermalSpotInfo.spotInfo[3].fTemperature);
	DDX_Control(pDX, IDC_BUTTON_MODIFY4, m_btnModify[3]);

	DDX_Control(pDX, IDC_COMBO_ENABLE_5, m_cbEnable[4]);
	DDX_CBIndex(pDX, IDC_COMBO_ENABLE_5, m_stThermalSpotInfo.spotInfo[4].bEnable);
	DDX_Text(pDX, IDC_EDIT_X_5, m_stThermalSpotInfo.spotInfo[4].posSpot.nPositionX);
	DDX_Text(pDX, IDC_EDIT_Y_5, m_stThermalSpotInfo.spotInfo[4].posSpot.nPositionY);
	DDX_Text(pDX, IDC_EDIT_TEMPERATURE_5, m_stThermalSpotInfo.spotInfo[4].fTemperature);
	DDX_Control(pDX, IDC_BUTTON_MODIFY5, m_btnModify[4]);

	DDX_Control(pDX, IDC_COMBO_ENABLE_6, m_cbEnable[5]);
	DDX_CBIndex(pDX, IDC_COMBO_ENABLE_6, m_stThermalSpotInfo.spotInfo[5].bEnable);
	DDX_Text(pDX, IDC_EDIT_X_6, m_stThermalSpotInfo.spotInfo[5].posSpot.nPositionX);
	DDX_Text(pDX, IDC_EDIT_Y_6, m_stThermalSpotInfo.spotInfo[5].posSpot.nPositionY);
	DDX_Text(pDX, IDC_EDIT_TEMPERATURE_6, m_stThermalSpotInfo.spotInfo[5].fTemperature);
	DDX_Control(pDX, IDC_BUTTON_MODIFY6, m_btnModify[5]);

	DDX_Control(pDX, IDC_COMBO_ENABLE_7, m_cbEnable[6]);
	DDX_CBIndex(pDX, IDC_COMBO_ENABLE_7, m_stThermalSpotInfo.spotInfo[6].bEnable);
	DDX_Text(pDX, IDC_EDIT_X_7, m_stThermalSpotInfo.spotInfo[6].posSpot.nPositionX);
	DDX_Text(pDX, IDC_EDIT_Y_7, m_stThermalSpotInfo.spotInfo[6].posSpot.nPositionY);
	DDX_Text(pDX, IDC_EDIT_TEMPERATURE_7, m_stThermalSpotInfo.spotInfo[6].fTemperature);
	DDX_Control(pDX, IDC_BUTTON_MODIFY7, m_btnModify[6]);

	DDX_Control(pDX, IDC_COMBO_ENABLE_8, m_cbEnable[7]);
	DDX_CBIndex(pDX, IDC_COMBO_ENABLE_8, m_stThermalSpotInfo.spotInfo[7].bEnable);
	DDX_Text(pDX, IDC_EDIT_X_8, m_stThermalSpotInfo.spotInfo[7].posSpot.nPositionX);
	DDX_Text(pDX, IDC_EDIT_Y_8, m_stThermalSpotInfo.spotInfo[7].posSpot.nPositionY);
	DDX_Text(pDX, IDC_EDIT_TEMPERATURE_8, m_stThermalSpotInfo.spotInfo[7].fTemperature);
	DDX_Control(pDX, IDC_BUTTON_MODIFY8, m_btnModify[7]);

	DDX_Control(pDX, IDC_COMBO_ENABLE_9, m_cbEnable[8]);
	DDX_CBIndex(pDX, IDC_COMBO_ENABLE_9, m_stThermalSpotInfo.spotInfo[8].bEnable);
	DDX_Text(pDX, IDC_EDIT_X_9, m_stThermalSpotInfo.spotInfo[8].posSpot.nPositionX);
	DDX_Text(pDX, IDC_EDIT_Y_9, m_stThermalSpotInfo.spotInfo[8].posSpot.nPositionY);
	DDX_Text(pDX, IDC_EDIT_TEMPERATURE_9, m_stThermalSpotInfo.spotInfo[8].fTemperature);
	DDX_Control(pDX, IDC_BUTTON_MODIFY9, m_btnModify[8]);

	DDX_Control(pDX, IDC_COMBO_ENABLE_10, m_cbEnable[9]);
	DDX_CBIndex(pDX, IDC_COMBO_ENABLE_10, m_stThermalSpotInfo.spotInfo[9].bEnable);
	DDX_Text(pDX, IDC_EDIT_X_10, m_stThermalSpotInfo.spotInfo[9].posSpot.nPositionX);
	DDX_Text(pDX, IDC_EDIT_Y_10, m_stThermalSpotInfo.spotInfo[9].posSpot.nPositionY);
	DDX_Text(pDX, IDC_EDIT_TEMPERATURE_10, m_stThermalSpotInfo.spotInfo[9].fTemperature);
	DDX_Control(pDX, IDC_BUTTON_MODIFY10, m_btnModify[9]);
}


BEGIN_MESSAGE_MAP(CThermalSpotInfoDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_GET, &CThermalSpotInfoDlg::OnBnClickedButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY1, &CThermalSpotInfoDlg::OnBnClickedButtonModify1)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY2, &CThermalSpotInfoDlg::OnBnClickedButtonModify2)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY3, &CThermalSpotInfoDlg::OnBnClickedButtonModify3)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY4, &CThermalSpotInfoDlg::OnBnClickedButtonModify4)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY5, &CThermalSpotInfoDlg::OnBnClickedButtonModify5)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY6, &CThermalSpotInfoDlg::OnBnClickedButtonModify6)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY7, &CThermalSpotInfoDlg::OnBnClickedButtonModify7)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY8, &CThermalSpotInfoDlg::OnBnClickedButtonModify8)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY9, &CThermalSpotInfoDlg::OnBnClickedButtonModify9)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY10, &CThermalSpotInfoDlg::OnBnClickedButtonModify10)
END_MESSAGE_MAP()


// CThermalSpotInfoDlg 메시지 처리기입니다.


BOOL CThermalSpotInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CreateEnableComboBox();
	OnBnClickedButtonGet();

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CThermalSpotInfoDlg::CreateEnableComboBox()
{
	size_t nComboBoxCnt = _countof(m_cbEnable);
	for (size_t i=0; i<nComboBoxCnt; i++) {
		m_cbEnable[i].InsertString(0, _T("false"));
		m_cbEnable[i].InsertString(1, _T("true"));
		m_cbEnable[i].SetCurSel(0);
	}
}

void CThermalSpotInfoDlg::OnBnClickedButtonGet()
{
	BOOL bIsSuccess = FALSE;

	ZeroMemory(&m_stThermalSpotInfo, sizeof(m_stThermalSpotInfo));
	m_strMinCoordinate = _T("");
	m_strMaxCoordinate = _T("");

	long ret = SPIDER_GetThermalSpotInfo(theApp.m_hSelectCamera, &m_stThermalSpotInfo);
	if (ret == E_CTRL_OK) {
		m_strMinCoordinate.Format(_T("%d, %d"), m_stThermalSpotInfo.posMinTemperature.nPositionX, m_stThermalSpotInfo.posMinTemperature.nPositionY);
		m_strMaxCoordinate.Format(_T("%d, %d"), m_stThermalSpotInfo.posMaxTemperature.nPositionX, m_stThermalSpotInfo.posMinTemperature.nPositionY);
		bIsSuccess = TRUE;
	} else {
		MessageBox(_T("Could not get thermal spot info"));
	}

	UpdateData(FALSE);
	size_t nModifyBntCnt = _countof(m_btnModify);
	for (size_t i=0; i<nModifyBntCnt; i++) {
		m_btnModify[i].EnableWindow(bIsSuccess);
	}
}


void CThermalSpotInfoDlg::OnBnClickedButtonModify1()
{
	UpdateData();
	ModifyThermalSpot(&m_stThermalSpotInfo.spotInfo[0]);
}


void CThermalSpotInfoDlg::OnBnClickedButtonModify2()
{
	UpdateData();
	ModifyThermalSpot(&m_stThermalSpotInfo.spotInfo[1]);
}


void CThermalSpotInfoDlg::OnBnClickedButtonModify3()
{
	UpdateData();
	ModifyThermalSpot(&m_stThermalSpotInfo.spotInfo[2]);
}


void CThermalSpotInfoDlg::OnBnClickedButtonModify4()
{
	UpdateData();
	ModifyThermalSpot(&m_stThermalSpotInfo.spotInfo[3]);
}


void CThermalSpotInfoDlg::OnBnClickedButtonModify5()
{
	UpdateData();
	ModifyThermalSpot(&m_stThermalSpotInfo.spotInfo[4]);
}


void CThermalSpotInfoDlg::OnBnClickedButtonModify6()
{
	UpdateData();
	ModifyThermalSpot(&m_stThermalSpotInfo.spotInfo[5]);
}


void CThermalSpotInfoDlg::OnBnClickedButtonModify7()
{
	UpdateData();
	ModifyThermalSpot(&m_stThermalSpotInfo.spotInfo[6]);
}


void CThermalSpotInfoDlg::OnBnClickedButtonModify8()
{
	UpdateData();
	ModifyThermalSpot(&m_stThermalSpotInfo.spotInfo[7]);
}


void CThermalSpotInfoDlg::OnBnClickedButtonModify9()
{
	UpdateData();
	ModifyThermalSpot(&m_stThermalSpotInfo.spotInfo[8]);
}


void CThermalSpotInfoDlg::OnBnClickedButtonModify10()
{
	UpdateData();
	ModifyThermalSpot(&m_stThermalSpotInfo.spotInfo[9]);
}


void CThermalSpotInfoDlg::ModifyThermalSpot(ST_SPIDER_THERMAL_SPOT* pSpot)
{
	long ret = SPIDER_SetThermalSpot(theApp.m_hSelectCamera, *pSpot);
	if (ret == E_CTRL_OK) {
		MessageBox(_T("Success."));
	} else {
		MessageBox(_T("Could not set thermal spot."));
	}
}