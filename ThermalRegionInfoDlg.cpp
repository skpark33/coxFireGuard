// ThermalRegionInfoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TestDlg.h"
#include "ThermalRegionInfoDlg.h"


// CThermalRegionInfoDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CThermalRegionInfoDlg, CDialog)

CThermalRegionInfoDlg::CThermalRegionInfoDlg(ST_SPIDER_THERMAL_COMPONENTS* pThermalComponents, CWnd* pParent /*=NULL*/)
	: CDialog(CThermalRegionInfoDlg::IDD, pParent)
	, m_pThermalComponents(pThermalComponents)
{
	ZeroMemory(&m_MaxRes, sizeof(m_MaxRes));
	ZeroMemory(&m_EntireAlarm, sizeof(m_EntireAlarm));
	ZeroMemory(&m_RegionInfo, sizeof(m_RegionInfo));
}

CThermalRegionInfoDlg::~CThermalRegionInfoDlg()
{
}

void CThermalRegionInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ENABLE_ENTIRE, m_wndEntire.cbEnable);
	DDX_Control(pDX, IDC_EDIT_X_ENTIRE, m_wndEntire.edtX);
	DDX_Control(pDX, IDC_EDIT_Y_ENTIRE, m_wndEntire.edtY);
	DDX_Control(pDX, IDC_EDIT_WIDTH_ENTIRE, m_wndEntire.edtWidth);
	DDX_Control(pDX, IDC_EDIT_HEIGHT_ENTIRE, m_wndEntire.edtHeight);
	DDX_Control(pDX, IDC_COMBO_ALARM_ENABLE_ENTIRE, m_wndEntire.cbAlarmEnable);
	DDX_Control(pDX, IDC_COMBO_ALARM_MODE_ENTIRE, m_wndEntire.cbAlarmMode);
	DDX_Control(pDX, IDC_COMBO_ALARM_CONDITION_ENTIRE, m_wndEntire.cbAlarmCondition);
	DDX_Control(pDX, IDC_COMBO_ALARM_TEMP_ENTIRE, m_wndEntire.edtAlarmTemp);
	DDX_Control(pDX, IDC_COMBO_ALARM_START_DELAY_ENTIRE, m_wndEntire.edtAlarmStartDelay);
	DDX_Control(pDX, IDC_COMBO_ALARM_STOP_DELAY_ENTIRE, m_wndEntire.edtAlarmStopDelay);
	DDX_Control(pDX, IDC_BUTTON_MODIFYENTIRE, m_wndEntire.btnModify);

	DDX_Control(pDX, IDC_COMBO_ENABLE_0, m_wndRegion[0].cbEnable);
	DDX_Control(pDX, IDC_EDIT_X_0, m_wndRegion[0].edtX);
	DDX_Control(pDX, IDC_EDIT_Y_0, m_wndRegion[0].edtY);
	DDX_Control(pDX, IDC_EDIT_WIDTH_0, m_wndRegion[0].edtWidth);
	DDX_Control(pDX, IDC_EDIT_HEIGHT_0, m_wndRegion[0].edtHeight);
	DDX_Control(pDX, IDC_COMBO_ALARM_ENABLE_0, m_wndRegion[0].cbAlarmEnable);
	DDX_Control(pDX, IDC_COMBO_ALARM_MODE_0, m_wndRegion[0].cbAlarmMode);
	DDX_Control(pDX, IDC_COMBO_ALARM_CONDITION_0, m_wndRegion[0].cbAlarmCondition);
	DDX_Control(pDX, IDC_COMBO_ALARM_TEMP_0, m_wndRegion[0].edtAlarmTemp);
	DDX_Control(pDX, IDC_COMBO_ALARM_START_DELAY_0, m_wndRegion[0].edtAlarmStartDelay);
	DDX_Control(pDX, IDC_COMBO_ALARM_STOP_DELAY_0, m_wndRegion[0].edtAlarmStopDelay);
	DDX_Control(pDX, IDC_BUTTON_MODIFY0, m_wndRegion[0].btnModify);

	DDX_Control(pDX, IDC_COMBO_ENABLE_1, m_wndRegion[1].cbEnable);
	DDX_Control(pDX, IDC_EDIT_X_1, m_wndRegion[1].edtX);
	DDX_Control(pDX, IDC_EDIT_Y_1, m_wndRegion[1].edtY);
	DDX_Control(pDX, IDC_EDIT_WIDTH_1, m_wndRegion[1].edtWidth);
	DDX_Control(pDX, IDC_EDIT_HEIGHT_1, m_wndRegion[1].edtHeight);
	DDX_Control(pDX, IDC_COMBO_ALARM_ENABLE_1, m_wndRegion[1].cbAlarmEnable);
	DDX_Control(pDX, IDC_COMBO_ALARM_MODE_1, m_wndRegion[1].cbAlarmMode);
	DDX_Control(pDX, IDC_COMBO_ALARM_CONDITION_1, m_wndRegion[1].cbAlarmCondition);
	DDX_Control(pDX, IDC_COMBO_ALARM_TEMP_1, m_wndRegion[1].edtAlarmTemp);
	DDX_Control(pDX, IDC_COMBO_ALARM_START_DELAY_1, m_wndRegion[1].edtAlarmStartDelay);
	DDX_Control(pDX, IDC_COMBO_ALARM_STOP_DELAY_1, m_wndRegion[1].edtAlarmStopDelay);
	DDX_Control(pDX, IDC_BUTTON_MODIFY1, m_wndRegion[1].btnModify);

	DDX_Control(pDX, IDC_COMBO_ENABLE_2, m_wndRegion[2].cbEnable);
	DDX_Control(pDX, IDC_EDIT_X_2, m_wndRegion[2].edtX);
	DDX_Control(pDX, IDC_EDIT_Y_2, m_wndRegion[2].edtY);
	DDX_Control(pDX, IDC_EDIT_WIDTH_2, m_wndRegion[2].edtWidth);
	DDX_Control(pDX, IDC_EDIT_HEIGHT_2, m_wndRegion[2].edtHeight);
	DDX_Control(pDX, IDC_COMBO_ALARM_ENABLE_2, m_wndRegion[2].cbAlarmEnable);
	DDX_Control(pDX, IDC_COMBO_ALARM_MODE_2, m_wndRegion[2].cbAlarmMode);
	DDX_Control(pDX, IDC_COMBO_ALARM_CONDITION_2, m_wndRegion[2].cbAlarmCondition);
	DDX_Control(pDX, IDC_COMBO_ALARM_TEMP_2, m_wndRegion[2].edtAlarmTemp);
	DDX_Control(pDX, IDC_COMBO_ALARM_START_DELAY_2, m_wndRegion[2].edtAlarmStartDelay);
	DDX_Control(pDX, IDC_COMBO_ALARM_STOP_DELAY_2, m_wndRegion[2].edtAlarmStopDelay);
	DDX_Control(pDX, IDC_BUTTON_MODIFY2, m_wndRegion[2].btnModify);

	DDX_Control(pDX, IDC_COMBO_ENABLE_3, m_wndRegion[3].cbEnable);
	DDX_Control(pDX, IDC_EDIT_X_3, m_wndRegion[3].edtX);
	DDX_Control(pDX, IDC_EDIT_Y_3, m_wndRegion[3].edtY);
	DDX_Control(pDX, IDC_EDIT_WIDTH_3, m_wndRegion[3].edtWidth);
	DDX_Control(pDX, IDC_EDIT_HEIGHT_3, m_wndRegion[3].edtHeight);
	DDX_Control(pDX, IDC_COMBO_ALARM_ENABLE_3, m_wndRegion[3].cbAlarmEnable);
	DDX_Control(pDX, IDC_COMBO_ALARM_MODE_3, m_wndRegion[3].cbAlarmMode);
	DDX_Control(pDX, IDC_COMBO_ALARM_CONDITION_3, m_wndRegion[3].cbAlarmCondition);
	DDX_Control(pDX, IDC_COMBO_ALARM_TEMP_3, m_wndRegion[3].edtAlarmTemp);
	DDX_Control(pDX, IDC_COMBO_ALARM_START_DELAY_3, m_wndRegion[3].edtAlarmStartDelay);
	DDX_Control(pDX, IDC_COMBO_ALARM_STOP_DELAY_3, m_wndRegion[3].edtAlarmStopDelay);
	DDX_Control(pDX, IDC_BUTTON_MODIFY3, m_wndRegion[3].btnModify);

	DDX_Control(pDX, IDC_COMBO_ENABLE_4, m_wndRegion[4].cbEnable);
	DDX_Control(pDX, IDC_EDIT_X_4, m_wndRegion[4].edtX);
	DDX_Control(pDX, IDC_EDIT_Y_4, m_wndRegion[4].edtY);
	DDX_Control(pDX, IDC_EDIT_WIDTH_4, m_wndRegion[4].edtWidth);
	DDX_Control(pDX, IDC_EDIT_HEIGHT_4, m_wndRegion[4].edtHeight);
	DDX_Control(pDX, IDC_COMBO_ALARM_ENABLE_4, m_wndRegion[4].cbAlarmEnable);
	DDX_Control(pDX, IDC_COMBO_ALARM_MODE_4, m_wndRegion[4].cbAlarmMode);
	DDX_Control(pDX, IDC_COMBO_ALARM_CONDITION_4, m_wndRegion[4].cbAlarmCondition);
	DDX_Control(pDX, IDC_COMBO_ALARM_TEMP_4, m_wndRegion[4].edtAlarmTemp);
	DDX_Control(pDX, IDC_COMBO_ALARM_START_DELAY_4, m_wndRegion[4].edtAlarmStartDelay);
	DDX_Control(pDX, IDC_COMBO_ALARM_STOP_DELAY_4, m_wndRegion[4].edtAlarmStopDelay);
	DDX_Control(pDX, IDC_BUTTON_MODIFY4, m_wndRegion[4].btnModify);

	DDX_Control(pDX, IDC_COMBO_ENABLE_5, m_wndRegion[5].cbEnable);
	DDX_Control(pDX, IDC_EDIT_X_5, m_wndRegion[5].edtX);
	DDX_Control(pDX, IDC_EDIT_Y_5, m_wndRegion[5].edtY);
	DDX_Control(pDX, IDC_EDIT_WIDTH_5, m_wndRegion[5].edtWidth);
	DDX_Control(pDX, IDC_EDIT_HEIGHT_5, m_wndRegion[5].edtHeight);
	DDX_Control(pDX, IDC_COMBO_ALARM_ENABLE_5, m_wndRegion[5].cbAlarmEnable);
	DDX_Control(pDX, IDC_COMBO_ALARM_MODE_5, m_wndRegion[5].cbAlarmMode);
	DDX_Control(pDX, IDC_COMBO_ALARM_CONDITION_5, m_wndRegion[5].cbAlarmCondition);
	DDX_Control(pDX, IDC_COMBO_ALARM_TEMP_5, m_wndRegion[5].edtAlarmTemp);
	DDX_Control(pDX, IDC_COMBO_ALARM_START_DELAY_5, m_wndRegion[5].edtAlarmStartDelay);
	DDX_Control(pDX, IDC_COMBO_ALARM_STOP_DELAY_5, m_wndRegion[5].edtAlarmStopDelay);
	DDX_Control(pDX, IDC_BUTTON_MODIFY5, m_wndRegion[5].btnModify);

	DDX_Control(pDX, IDC_COMBO_ENABLE_6, m_wndRegion[6].cbEnable);
	DDX_Control(pDX, IDC_EDIT_X_6, m_wndRegion[6].edtX);
	DDX_Control(pDX, IDC_EDIT_Y_6, m_wndRegion[6].edtY);
	DDX_Control(pDX, IDC_EDIT_WIDTH_6, m_wndRegion[6].edtWidth);
	DDX_Control(pDX, IDC_EDIT_HEIGHT_6, m_wndRegion[6].edtHeight);
	DDX_Control(pDX, IDC_COMBO_ALARM_ENABLE_6, m_wndRegion[6].cbAlarmEnable);
	DDX_Control(pDX, IDC_COMBO_ALARM_MODE_6, m_wndRegion[6].cbAlarmMode);
	DDX_Control(pDX, IDC_COMBO_ALARM_CONDITION_6, m_wndRegion[6].cbAlarmCondition);
	DDX_Control(pDX, IDC_COMBO_ALARM_TEMP_6, m_wndRegion[6].edtAlarmTemp);
	DDX_Control(pDX, IDC_COMBO_ALARM_START_DELAY_6, m_wndRegion[6].edtAlarmStartDelay);
	DDX_Control(pDX, IDC_COMBO_ALARM_STOP_DELAY_6, m_wndRegion[6].edtAlarmStopDelay);
	DDX_Control(pDX, IDC_BUTTON_MODIFY6, m_wndRegion[6].btnModify);

	DDX_Control(pDX, IDC_COMBO_ENABLE_7, m_wndRegion[7].cbEnable);
	DDX_Control(pDX, IDC_EDIT_X_7, m_wndRegion[7].edtX);
	DDX_Control(pDX, IDC_EDIT_Y_7, m_wndRegion[7].edtY);
	DDX_Control(pDX, IDC_EDIT_WIDTH_7, m_wndRegion[7].edtWidth);
	DDX_Control(pDX, IDC_EDIT_HEIGHT_7, m_wndRegion[7].edtHeight);
	DDX_Control(pDX, IDC_COMBO_ALARM_ENABLE_7, m_wndRegion[7].cbAlarmEnable);
	DDX_Control(pDX, IDC_COMBO_ALARM_MODE_7, m_wndRegion[7].cbAlarmMode);
	DDX_Control(pDX, IDC_COMBO_ALARM_CONDITION_7, m_wndRegion[7].cbAlarmCondition);
	DDX_Control(pDX, IDC_COMBO_ALARM_TEMP_7, m_wndRegion[7].edtAlarmTemp);
	DDX_Control(pDX, IDC_COMBO_ALARM_START_DELAY_7, m_wndRegion[7].edtAlarmStartDelay);
	DDX_Control(pDX, IDC_COMBO_ALARM_STOP_DELAY_7, m_wndRegion[7].edtAlarmStopDelay);
	DDX_Control(pDX, IDC_BUTTON_MODIFY7, m_wndRegion[7].btnModify);

	DDX_Control(pDX, IDC_COMBO_ENABLE_8, m_wndRegion[8].cbEnable);
	DDX_Control(pDX, IDC_EDIT_X_8, m_wndRegion[8].edtX);
	DDX_Control(pDX, IDC_EDIT_Y_8, m_wndRegion[8].edtY);
	DDX_Control(pDX, IDC_EDIT_WIDTH_8, m_wndRegion[8].edtWidth);
	DDX_Control(pDX, IDC_EDIT_HEIGHT_8, m_wndRegion[8].edtHeight);
	DDX_Control(pDX, IDC_COMBO_ALARM_ENABLE_8, m_wndRegion[8].cbAlarmEnable);
	DDX_Control(pDX, IDC_COMBO_ALARM_MODE_8, m_wndRegion[8].cbAlarmMode);
	DDX_Control(pDX, IDC_COMBO_ALARM_CONDITION_8, m_wndRegion[8].cbAlarmCondition);
	DDX_Control(pDX, IDC_COMBO_ALARM_TEMP_8, m_wndRegion[8].edtAlarmTemp);
	DDX_Control(pDX, IDC_COMBO_ALARM_START_DELAY_8, m_wndRegion[8].edtAlarmStartDelay);
	DDX_Control(pDX, IDC_COMBO_ALARM_STOP_DELAY_8, m_wndRegion[8].edtAlarmStopDelay);
	DDX_Control(pDX, IDC_BUTTON_MODIFY8, m_wndRegion[8].btnModify);

	DDX_Control(pDX, IDC_COMBO_ENABLE_9, m_wndRegion[9].cbEnable);
	DDX_Control(pDX, IDC_EDIT_X_9, m_wndRegion[9].edtX);
	DDX_Control(pDX, IDC_EDIT_Y_9, m_wndRegion[9].edtY);
	DDX_Control(pDX, IDC_EDIT_WIDTH_9, m_wndRegion[9].edtWidth);
	DDX_Control(pDX, IDC_EDIT_HEIGHT_9, m_wndRegion[9].edtHeight);
	DDX_Control(pDX, IDC_COMBO_ALARM_ENABLE_9, m_wndRegion[9].cbAlarmEnable);
	DDX_Control(pDX, IDC_COMBO_ALARM_MODE_9, m_wndRegion[9].cbAlarmMode);
	DDX_Control(pDX, IDC_COMBO_ALARM_CONDITION_9, m_wndRegion[9].cbAlarmCondition);
	DDX_Control(pDX, IDC_COMBO_ALARM_TEMP_9, m_wndRegion[9].edtAlarmTemp);
	DDX_Control(pDX, IDC_COMBO_ALARM_START_DELAY_9, m_wndRegion[9].edtAlarmStartDelay);
	DDX_Control(pDX, IDC_COMBO_ALARM_STOP_DELAY_9, m_wndRegion[9].edtAlarmStopDelay);
	DDX_Control(pDX, IDC_BUTTON_MODIFY9, m_wndRegion[9].btnModify);
}


BEGIN_MESSAGE_MAP(CThermalRegionInfoDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_MODIFYENTIRE, &CThermalRegionInfoDlg::OnBnClickedButtonModifyentire)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY0, &CThermalRegionInfoDlg::OnBnClickedButtonModify0)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY1, &CThermalRegionInfoDlg::OnBnClickedButtonModify1)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY2, &CThermalRegionInfoDlg::OnBnClickedButtonModify2)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY3, &CThermalRegionInfoDlg::OnBnClickedButtonModify3)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY4, &CThermalRegionInfoDlg::OnBnClickedButtonModify4)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY5, &CThermalRegionInfoDlg::OnBnClickedButtonModify5)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY6, &CThermalRegionInfoDlg::OnBnClickedButtonModify6)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY7, &CThermalRegionInfoDlg::OnBnClickedButtonModify7)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY8, &CThermalRegionInfoDlg::OnBnClickedButtonModify8)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY9, &CThermalRegionInfoDlg::OnBnClickedButtonModify9)
	ON_CBN_SELCHANGE(IDC_COMBO_ENABLE_0, &CThermalRegionInfoDlg::OnCbnSelchangeComboEnable0)
	ON_CBN_SELCHANGE(IDC_COMBO_ENABLE_1, &CThermalRegionInfoDlg::OnCbnSelchangeComboEnable1)
	ON_CBN_SELCHANGE(IDC_COMBO_ENABLE_2, &CThermalRegionInfoDlg::OnCbnSelchangeComboEnable2)
	ON_CBN_SELCHANGE(IDC_COMBO_ENABLE_3, &CThermalRegionInfoDlg::OnCbnSelchangeComboEnable3)
	ON_CBN_SELCHANGE(IDC_COMBO_ENABLE_4, &CThermalRegionInfoDlg::OnCbnSelchangeComboEnable4)
	ON_CBN_SELCHANGE(IDC_COMBO_ENABLE_5, &CThermalRegionInfoDlg::OnCbnSelchangeComboEnable5)
	ON_CBN_SELCHANGE(IDC_COMBO_ENABLE_6, &CThermalRegionInfoDlg::OnCbnSelchangeComboEnable6)
	ON_CBN_SELCHANGE(IDC_COMBO_ENABLE_7, &CThermalRegionInfoDlg::OnCbnSelchangeComboEnable7)
	ON_CBN_SELCHANGE(IDC_COMBO_ENABLE_8, &CThermalRegionInfoDlg::OnCbnSelchangeComboEnable8)
	ON_CBN_SELCHANGE(IDC_COMBO_ENABLE_9, &CThermalRegionInfoDlg::OnCbnSelchangeComboEnable9)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARM_ENABLE_ENTIRE, &CThermalRegionInfoDlg::OnCbnSelchangeComboAlarmEnableEntire)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARM_ENABLE_0, &CThermalRegionInfoDlg::OnCbnSelchangeComboAlarmEnable0)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARM_ENABLE_1, &CThermalRegionInfoDlg::OnCbnSelchangeComboAlarmEnable1)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARM_ENABLE_2, &CThermalRegionInfoDlg::OnCbnSelchangeComboAlarmEnable2)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARM_ENABLE_3, &CThermalRegionInfoDlg::OnCbnSelchangeComboAlarmEnable3)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARM_ENABLE_4, &CThermalRegionInfoDlg::OnCbnSelchangeComboAlarmEnable4)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARM_ENABLE_5, &CThermalRegionInfoDlg::OnCbnSelchangeComboAlarmEnable5)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARM_ENABLE_6, &CThermalRegionInfoDlg::OnCbnSelchangeComboAlarmEnable6)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARM_ENABLE_7, &CThermalRegionInfoDlg::OnCbnSelchangeComboAlarmEnable7)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARM_ENABLE_8, &CThermalRegionInfoDlg::OnCbnSelchangeComboAlarmEnable8)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARM_ENABLE_9, &CThermalRegionInfoDlg::OnCbnSelchangeComboAlarmEnable9)
END_MESSAGE_MAP()


// CThermalRegionInfoDlg 메시지 처리기입니다.


BOOL CThermalRegionInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CreateCtrl();
	Initialize();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CThermalRegionInfoDlg::CreateCtrl()
{
	CreateRegionCtrl(&m_wndEntire);
	m_wndEntire.cbEnable.SetCurSel(1);
	m_wndEntire.cbEnable.EnableWindow(FALSE);
	m_wndEntire.edtX.EnableWindow(FALSE);
	m_wndEntire.edtY.EnableWindow(FALSE);
	m_wndEntire.edtWidth.EnableWindow(FALSE);
	m_wndEntire.edtHeight.EnableWindow(FALSE);

	for (size_t i=0; i<_countof(m_wndRegion); i++) {
		CreateRegionCtrl(&m_wndRegion[i]);
	}
}

void CThermalRegionInfoDlg::CreateRegionCtrl(THERMAL_REGION_WND* pRegionWnd)
{
	int nIndex = pRegionWnd->cbEnable.InsertString(pRegionWnd->cbEnable.GetCount(), _T("Disable"));
	if (nIndex != CB_ERR) {
		pRegionWnd->cbEnable.SetItemData(nIndex, FALSE);
	}
	nIndex = pRegionWnd->cbEnable.InsertString(pRegionWnd->cbEnable.GetCount(), _T("Enable"));
	if (nIndex != CB_ERR) {
		pRegionWnd->cbEnable.SetItemData(nIndex, TRUE);
	}
	
	nIndex = pRegionWnd->cbAlarmEnable.InsertString(pRegionWnd->cbAlarmEnable.GetCount(), _T("Disable"));
	if (nIndex != CB_ERR) {
		pRegionWnd->cbAlarmEnable.SetItemData(nIndex, FALSE);
	}
	nIndex = pRegionWnd->cbAlarmEnable.InsertString(pRegionWnd->cbAlarmEnable.GetCount(), _T("Enable"));
	if (nIndex != CB_ERR) {
		pRegionWnd->cbAlarmEnable.SetItemData(nIndex, TRUE);
	}
	
	nIndex = pRegionWnd->cbAlarmMode.InsertString(pRegionWnd->cbAlarmMode.GetCount(), _T("Center"));
	if (nIndex != CB_ERR) {
		pRegionWnd->cbAlarmMode.SetItemData(nIndex, AlarmCenter);
	}
	nIndex = pRegionWnd->cbAlarmMode.InsertString(pRegionWnd->cbAlarmMode.GetCount(), _T("Average"));
	if (nIndex != CB_ERR) {
		pRegionWnd->cbAlarmMode.SetItemData(nIndex, AlarmAverage);
	}
	nIndex = pRegionWnd->cbAlarmMode.InsertString(pRegionWnd->cbAlarmMode.GetCount(), _T("Min"));
	if (nIndex != CB_ERR) {
		pRegionWnd->cbAlarmMode.SetItemData(nIndex, AlarmMin);
	}
	nIndex = pRegionWnd->cbAlarmMode.InsertString(pRegionWnd->cbAlarmMode.GetCount(), _T("Max"));
	if (nIndex != CB_ERR) {
		pRegionWnd->cbAlarmMode.SetItemData(nIndex, AlarmMax);
	}
	
	nIndex = pRegionWnd->cbAlarmCondition.InsertString(pRegionWnd->cbAlarmCondition.GetCount(), _T("Above"));
	if (nIndex != CB_ERR) {
		pRegionWnd->cbAlarmCondition.SetItemData(nIndex, 0);
	}
	nIndex = pRegionWnd->cbAlarmCondition.InsertString(pRegionWnd->cbAlarmCondition.GetCount(), _T("Below"));
	if (nIndex != CB_ERR) {
		pRegionWnd->cbAlarmCondition.SetItemData(nIndex, 1);
	}
}

void CThermalRegionInfoDlg::EnableRegionCtrl(THERMAL_REGION_WND* pRegionWnd, BOOL bEnable /*= TRUE*/)
{
	pRegionWnd->cbEnable.EnableWindow(bEnable);
	pRegionWnd->edtX.EnableWindow(bEnable);
	pRegionWnd->edtY.EnableWindow(bEnable);
	pRegionWnd->edtWidth.EnableWindow(bEnable);
	pRegionWnd->edtHeight.EnableWindow(bEnable);
	pRegionWnd->cbAlarmEnable.EnableWindow(bEnable);
	pRegionWnd->cbAlarmMode.EnableWindow(bEnable);
	pRegionWnd->cbAlarmCondition.EnableWindow(bEnable);
	pRegionWnd->edtAlarmTemp.EnableWindow(bEnable);
	pRegionWnd->edtAlarmStartDelay.EnableWindow(bEnable);
	pRegionWnd->edtAlarmStopDelay.EnableWindow(bEnable);
	pRegionWnd->btnModify.EnableWindow(bEnable);
}

void CThermalRegionInfoDlg::Initialize()
{
	ZeroMemory(&m_MaxRes, sizeof(m_MaxRes));
	ZeroMemory(&m_EntireAlarm, sizeof(m_EntireAlarm));
	ZeroMemory(&m_RegionInfo, sizeof(m_RegionInfo));

	long ret = SPIDER_GetStreamCapaMaxResolution(theApp.m_hSelectCamera, &m_MaxRes);
	if (ret == E_CTRL_OK) {
		ret = SPIDER_GetThermalEntireRegionAlarm(theApp.m_hSelectCamera, &m_EntireAlarm);
		if (ret == E_CTRL_OK) {			
			long ret = SPIDER_GetThermalRegionInfo(theApp.m_hSelectCamera, &m_RegionInfo);
			if (ret == E_CTRL_OK) {
				SetCtrlValue();
			} else {
				MessageBox(_T("Could not get thermal region info"));
			}
		} else {
			MessageBox(_T("Could not get thermal entire alarm info"));
		}
	} else {
		MessageBox(_T("Could not get max resolution"));
	}
}

void CThermalRegionInfoDlg::SetCtrlValue()
{
	SetRegionCtrlValue(TRUE, CPoint(0, 0), CSize(m_MaxRes.width, m_MaxRes.height), &m_EntireAlarm, &m_wndEntire);
	m_wndEntire.cbEnable.EnableWindow(FALSE);
	m_wndEntire.edtX.EnableWindow(FALSE);
	m_wndEntire.edtY.EnableWindow(FALSE);
	m_wndEntire.edtWidth.EnableWindow(FALSE);
	m_wndEntire.edtHeight.EnableWindow(FALSE);

	for (size_t i=0; i<_countof(m_wndRegion); i++) {
		if (i < m_RegionInfo.nMaxRegionCnt) {
			EnableRegionCtrl(&m_wndRegion[i], TRUE);

			CPoint pt(m_RegionInfo.ThermalRegion[i].ptRegion.nPositionX, m_RegionInfo.ThermalRegion[i].ptRegion.nPositionY);
			CSize size(m_RegionInfo.ThermalRegion[i].sizeRegion.nWidth, m_RegionInfo.ThermalRegion[i].sizeRegion.nHeight);
			SetRegionCtrlValue(m_RegionInfo.ThermalRegion[i].bEnable , pt, size, &m_RegionInfo.ThermalRegion[i].RegionAlaramInfo, &m_wndRegion[i]);
		} else {
			EnableRegionCtrl(&m_wndRegion[i], FALSE);
		}
	}
}

void CThermalRegionInfoDlg::SetRegionCtrlValue(BOOL bEnable, CPoint pt, CSize size, ST_SPIDER_THERMAL_ALARM* pAlaramInfo, THERMAL_REGION_WND* pRegionWnd)
{
	CString strText = _T("");

	for (int i=0; i<pRegionWnd->cbEnable.GetCount(); i++) {
		if (pRegionWnd->cbEnable.GetItemData(i) == bEnable) {
			pRegionWnd->cbEnable.SetCurSel(i);
			break;
		}
	}

	strText.Format(_T("%d"), pt.x);
	pRegionWnd->edtX.SetWindowText(strText);
	strText.Format(_T("%d"), pt.y);
	pRegionWnd->edtY.SetWindowText(strText);
	strText.Format(_T("%d"), size.cx);
	pRegionWnd->edtWidth.SetWindowText(strText);
	strText.Format(_T("%d"), size.cy);
	pRegionWnd->edtHeight.SetWindowText(strText);
	
	for (int i=0; i<pRegionWnd->cbAlarmEnable.GetCount(); i++) {
		if (pRegionWnd->cbAlarmEnable.GetItemData(i) == pAlaramInfo->bAlarmEnable) {
			pRegionWnd->cbAlarmEnable.SetCurSel(i);
			break;
		}
	}

	for (int i=0; i<pRegionWnd->cbAlarmMode.GetCount(); i++) {
		if ((EM_THERMAL_ALARM_MODE)pRegionWnd->cbAlarmMode.GetItemData(i) == pAlaramInfo->emAlarmMode) {
			pRegionWnd->cbAlarmMode.SetCurSel(i);
			break;
		}
	}

	for (int i=0; i<pRegionWnd->cbAlarmCondition.GetCount(); i++) {
		if (pRegionWnd->cbAlarmCondition.GetItemData(i) == pAlaramInfo->nlAlarmCondition) {
			pRegionWnd->cbAlarmCondition.SetCurSel(i);
			break;
		}
	}

	strText.Format(_T("%.1f"), pAlaramInfo->fAlarmTemp);
	pRegionWnd->edtAlarmTemp.SetWindowText(strText);
	strText.Format(_T("%d"), pAlaramInfo->nlAlarmStartDelay);
	pRegionWnd->edtAlarmStartDelay.SetWindowText(strText);
	strText.Format(_T("%d"), pAlaramInfo->nlAlarmStopDelay);
	pRegionWnd->edtAlarmStopDelay.SetWindowText(strText);

	RegionCtrl(pRegionWnd);
}

void CThermalRegionInfoDlg::UpdateRegionInfo(ST_SPIDER_THERMAL_REGION& stInfo, UINT uiID)
{
	CString str = _T("");
	stInfo.nID = uiID;
	stInfo.bEnable = (BOOL)m_wndRegion[uiID].cbEnable.GetItemData(m_wndRegion[uiID].cbEnable.GetCurSel());
	m_wndRegion[uiID].edtX.GetWindowText(str);
	ULONG ul = _ttoi(str);
	if (ul < 0)
	{
		ul = 0;
	}
	else if (ul > m_MaxRes.width - 20)
	{
		ul = m_MaxRes.width - 20;
	}
	stInfo.ptRegion.nPositionX = ul;
	m_wndRegion[uiID].edtY.GetWindowText(str);
	ul = _ttoi(str);
	if (ul < 0)
	{
		ul = 0;
	}
	else if (ul > m_MaxRes.height - 20)
	{
		ul = m_MaxRes.height - 20;
	}
	stInfo.ptRegion.nPositionY = ul;
	m_wndRegion[uiID].edtWidth.GetWindowText(str);
	ul = _ttoi(str);
	if (ul < 20)
	{
		ul = 20;
	}
	else if (ul > m_MaxRes.width - stInfo.ptRegion.nPositionX)
	{
		ul = m_MaxRes.width - stInfo.ptRegion.nPositionX;
	}
	stInfo.sizeRegion.nWidth = ul;
	m_wndRegion[uiID].edtHeight.GetWindowText(str);
	ul = _ttoi(str);
	if (ul < 20)
	{
		ul = 20;
	}
	else if (ul > m_MaxRes.height - stInfo.ptRegion.nPositionY)
	{
		ul = m_MaxRes.height - stInfo.ptRegion.nPositionY;
	}
	stInfo.sizeRegion.nHeight = ul;
	stInfo.RegionAlaramInfo.bAlarmEnable = (BOOL)m_wndRegion[uiID].cbAlarmEnable.GetItemData(m_wndRegion[uiID].cbAlarmEnable.GetCurSel());
	stInfo.RegionAlaramInfo.emAlarmMode = (EM_THERMAL_ALARM_MODE)m_wndRegion[uiID].cbAlarmMode.GetItemData(m_wndRegion[uiID].cbAlarmMode.GetCurSel());
	stInfo.RegionAlaramInfo.nlAlarmCondition = (LONG)m_wndRegion[uiID].cbAlarmCondition.GetItemData(m_wndRegion[uiID].cbAlarmCondition.GetCurSel());
	m_wndRegion[uiID].edtAlarmTemp.GetWindowText(str);
	FLOAT fTemp = _tstof(str);
	if (fTemp < -20)
	{
		fTemp = -20;
	}
	else if (fTemp > 650)
	{
		fTemp = 650;
	}
	stInfo.RegionAlaramInfo.fAlarmTemp = fTemp;

	m_wndRegion[uiID].edtAlarmStartDelay.GetWindowText(str);
	LONG nl = _ttoi(str);
	if (nl < 0) {
		nl = 0;
	} else if (nl > 1800) {
		nl = 1800;
	}
	stInfo.RegionAlaramInfo.nlAlarmStartDelay = nl;

	m_wndRegion[uiID].edtAlarmStopDelay.GetWindowText(str);
	nl = _ttoi(str);
	if (nl < 0) {
		nl = 0;
	} else if (nl > 1800) {
		nl = 1800;
	}
	stInfo.RegionAlaramInfo.nlAlarmStopDelay = nl;

	SetRegionCtrlValue(stInfo.bEnable, CPoint(stInfo.ptRegion.nPositionX, stInfo.ptRegion.nPositionY), CSize(stInfo.sizeRegion.nWidth, stInfo.sizeRegion.nHeight), &stInfo.RegionAlaramInfo, &m_wndRegion[uiID]);
}

void CThermalRegionInfoDlg::OnBnClickedButtonModifyentire()
{
	ST_SPIDER_THERMAL_ALARM stInfo = {NULL, };
	stInfo.bAlarmEnable = m_wndEntire.cbAlarmEnable.GetItemData(m_wndEntire.cbAlarmEnable.GetCurSel());
	stInfo.emAlarmMode = (EM_THERMAL_ALARM_MODE)m_wndEntire.cbAlarmMode.GetItemData(m_wndEntire.cbAlarmMode.GetCurSel());
	stInfo.nlAlarmCondition = (LONG)m_wndEntire.cbAlarmCondition.GetItemData(m_wndEntire.cbAlarmCondition.GetCurSel());
	CString str = _T("");
	m_wndEntire.edtAlarmTemp.GetWindowText(str);
	FLOAT fTemp = _tstof(str);
	if (fTemp < -20)
	{
		fTemp = -20;
	}
	else if (fTemp > 650)
	{
		fTemp = 650;
	}
	stInfo.fAlarmTemp = fTemp;

	m_wndEntire.edtAlarmStartDelay.GetWindowText(str);
	LONG nl = _ttoi(str);
	if (nl < 0) {
		nl = 0;
	} else if (nl > 1800) {
		nl = 1800;
	}
	stInfo.nlAlarmStartDelay = nl;

	m_wndEntire.edtAlarmStopDelay.GetWindowText(str);
	nl = _ttoi(str);
	if (nl < 0) {
		nl = 0;
	} else if (nl > 1800) {
		nl = 1800;
	}
	stInfo.nlAlarmStopDelay = nl;

	LONG nlRet = SPIDER_SetThermalEntireRegionAlarm(theApp.m_hSelectCamera, stInfo);
	CString strText = _T("");
	strText.Format(_T("Modify result : %s"), (nlRet == E_CTRL_OK) ? _T("success"):_T("fail"));
	MessageBox(strText);
}

void CThermalRegionInfoDlg::OnBnClickedButtonModify0()
{
	ModifyRegionInfo(0);
}

void CThermalRegionInfoDlg::OnBnClickedButtonModify1()
{
	ModifyRegionInfo(1);
}

void CThermalRegionInfoDlg::OnBnClickedButtonModify2()
{
	ModifyRegionInfo(2);
}

void CThermalRegionInfoDlg::OnBnClickedButtonModify3()
{
	ModifyRegionInfo(3);
}

void CThermalRegionInfoDlg::OnBnClickedButtonModify4()
{
	ModifyRegionInfo(4);
}

void CThermalRegionInfoDlg::OnBnClickedButtonModify5()
{
	ModifyRegionInfo(5);
}

void CThermalRegionInfoDlg::OnBnClickedButtonModify6()
{
	ModifyRegionInfo(6);
}

void CThermalRegionInfoDlg::OnBnClickedButtonModify7()
{
	ModifyRegionInfo(7);
}

void CThermalRegionInfoDlg::OnBnClickedButtonModify8()
{
	ModifyRegionInfo(8);
}

void CThermalRegionInfoDlg::OnBnClickedButtonModify9()
{
	ModifyRegionInfo(9);
}

void CThermalRegionInfoDlg::ModifyRegionInfo(UINT uiID)
{
	ST_SPIDER_THERMAL_REGION stRegion = {NULL, };
	UpdateRegionInfo(stRegion, uiID);
	LONG nlRet = SPIDER_SetThermalRegion(theApp.m_hSelectCamera, stRegion);
	CString strText = _T("");
	strText.Format(_T("[%d] Modify result : %s"), uiID, (nlRet == E_CTRL_OK) ? _T("success"):_T("fail"));
	MessageBox(strText);
}

void CThermalRegionInfoDlg::OnCbnSelchangeComboEnable0()
{
	RegionCtrl(&m_wndRegion[0]);
}

void CThermalRegionInfoDlg::OnCbnSelchangeComboEnable1()
{
	RegionCtrl(&m_wndRegion[1]);
}

void CThermalRegionInfoDlg::OnCbnSelchangeComboEnable2()
{
	RegionCtrl(&m_wndRegion[2]);
}

void CThermalRegionInfoDlg::OnCbnSelchangeComboEnable3()
{
	RegionCtrl(&m_wndRegion[3]);
}

void CThermalRegionInfoDlg::OnCbnSelchangeComboEnable4()
{
	RegionCtrl(&m_wndRegion[4]);
}

void CThermalRegionInfoDlg::OnCbnSelchangeComboEnable5()
{
	RegionCtrl(&m_wndRegion[5]);
}

void CThermalRegionInfoDlg::OnCbnSelchangeComboEnable6()
{
	RegionCtrl(&m_wndRegion[6]);
}

void CThermalRegionInfoDlg::OnCbnSelchangeComboEnable7()
{
	RegionCtrl(&m_wndRegion[7]);
}

void CThermalRegionInfoDlg::OnCbnSelchangeComboEnable8()
{
	RegionCtrl(&m_wndRegion[8]);
}

void CThermalRegionInfoDlg::OnCbnSelchangeComboEnable9()
{
	RegionCtrl(&m_wndRegion[9]);
}

void CThermalRegionInfoDlg::RegionCtrl(THERMAL_REGION_WND* pRegionWnd)
{
	BOOL bEnable = (BOOL)pRegionWnd->cbEnable.GetItemData(pRegionWnd->cbEnable.GetCurSel());

	pRegionWnd->edtX.EnableWindow(bEnable);
	pRegionWnd->edtY.EnableWindow(bEnable);
	pRegionWnd->edtWidth.EnableWindow(bEnable);
	pRegionWnd->edtHeight.EnableWindow(bEnable);
	pRegionWnd->cbAlarmEnable.EnableWindow(bEnable);
	RegionAlarmCtrl(pRegionWnd);
}

void CThermalRegionInfoDlg::OnCbnSelchangeComboAlarmEnableEntire()
{
	RegionAlarmCtrl(&m_wndEntire);
}

void CThermalRegionInfoDlg::OnCbnSelchangeComboAlarmEnable0()
{
	RegionAlarmCtrl(&m_wndRegion[0]);
}

void CThermalRegionInfoDlg::OnCbnSelchangeComboAlarmEnable1()
{
	RegionAlarmCtrl(&m_wndRegion[1]);
}

void CThermalRegionInfoDlg::OnCbnSelchangeComboAlarmEnable2()
{
	RegionAlarmCtrl(&m_wndRegion[2]);
}

void CThermalRegionInfoDlg::OnCbnSelchangeComboAlarmEnable3()
{
	RegionAlarmCtrl(&m_wndRegion[3]);
}

void CThermalRegionInfoDlg::OnCbnSelchangeComboAlarmEnable4()
{
	RegionAlarmCtrl(&m_wndRegion[4]);
}

void CThermalRegionInfoDlg::OnCbnSelchangeComboAlarmEnable5()
{
	RegionAlarmCtrl(&m_wndRegion[5]);
}

void CThermalRegionInfoDlg::OnCbnSelchangeComboAlarmEnable6()
{
	RegionAlarmCtrl(&m_wndRegion[6]);
}

void CThermalRegionInfoDlg::OnCbnSelchangeComboAlarmEnable7()
{
	RegionAlarmCtrl(&m_wndRegion[7]);
}

void CThermalRegionInfoDlg::OnCbnSelchangeComboAlarmEnable8()
{
	RegionAlarmCtrl(&m_wndRegion[8]);
}

void CThermalRegionInfoDlg::OnCbnSelchangeComboAlarmEnable9()
{
	RegionAlarmCtrl(&m_wndRegion[9]);
}

void CThermalRegionInfoDlg::RegionAlarmCtrl(THERMAL_REGION_WND* pRegionWnd)
{
	BOOL bIsAlarmWindowEnabled = pRegionWnd->cbAlarmEnable.IsWindowEnabled();
	BOOL bAlarmEnable = (BOOL)pRegionWnd->cbAlarmEnable.GetItemData(pRegionWnd->cbAlarmEnable.GetCurSel());
	
	pRegionWnd->cbAlarmMode.EnableWindow(bIsAlarmWindowEnabled && bAlarmEnable);
	pRegionWnd->cbAlarmCondition.EnableWindow(bIsAlarmWindowEnabled && bAlarmEnable);
	pRegionWnd->edtAlarmTemp.EnableWindow(bIsAlarmWindowEnabled && bAlarmEnable);
	pRegionWnd->edtAlarmStartDelay.EnableWindow(bIsAlarmWindowEnabled && bAlarmEnable);
	pRegionWnd->edtAlarmStopDelay.EnableWindow(bIsAlarmWindowEnabled && bAlarmEnable);
}