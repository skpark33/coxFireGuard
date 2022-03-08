// ThermalTempInfoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TestDlg.h"
#include "ThermalTempInfoDlg.h"


// CThermalTempInfoDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CThermalTempInfoDlg, CDialog)

CThermalTempInfoDlg::CThermalTempInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CThermalTempInfoDlg::IDD, pParent)
	, m_nlMinXEntire(0)
	, m_nlMinYEntire(0)
	, m_nlMaxXEntire(0)
	, m_nlMaxYEntire(0)
{
	ZeroMemory(m_nlMinX, sizeof(m_nlMinX));
	ZeroMemory(m_nlMinY, sizeof(m_nlMinY));
	ZeroMemory(m_nlMaxX, sizeof(m_nlMaxX));
	ZeroMemory(m_nlMaxY, sizeof(m_nlMaxY));
}

CThermalTempInfoDlg::~CThermalTempInfoDlg()
{
}

void CThermalTempInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TEMP_VALID_ENTIRE, m_wndTempValidEntire);
	DDX_Control(pDX, IDC_STATIC_TEMP_ALARM_ENTIRE, m_wndTempAlarmEntire);
	DDX_Control(pDX, IDC_EDIT_TEMP_CENTER_ENTIRE, m_edtTempCenterEntire);
	DDX_Control(pDX, IDC_EDIT_TEMP_MIN_ENTIRE, m_edtTempMinEntire);
	DDX_Control(pDX, IDC_EDIT_TEMP_MAX_ENTIRE, m_edtTempMaxEntire);
	DDX_Control(pDX, IDC_EDIT_TEMP_AVG_ENTIRE, m_edtTempAvgEntire);
	DDX_Text(pDX, IDC_EDIT_MIN_X_ENTIRE, m_nlMinXEntire);
	DDX_Text(pDX, IDC_EDIT_MIN_Y_ENTIRE, m_nlMinYEntire);
	DDX_Text(pDX, IDC_EDIT_MAX_X_ENTIRE, m_nlMaxXEntire);
	DDX_Text(pDX, IDC_EDIT_MAX_Y_ENTIRE, m_nlMaxYEntire);

	DDX_Control(pDX, IDC_STATIC_TEMP_VALID_0, m_wndTempValid[0]);
	DDX_Control(pDX, IDC_STATIC_TEMP_ALARM_0, m_wndTempAlarm[0]);
	DDX_Control(pDX, IDC_EDIT_TEMP_CENTER_0, m_edtTempCenter[0]);
	DDX_Control(pDX, IDC_EDIT_TEMP_MIN_0, m_edtTempMin[0]);
	DDX_Control(pDX, IDC_EDIT_TEMP_MAX_0, m_edtTempMax[0]);
	DDX_Control(pDX, IDC_EDIT_TEMP_AVG_0, m_edtTempAvg[0]);
	DDX_Text(pDX, IDC_EDIT_MIN_X_0, m_nlMinX[0]);
	DDX_Text(pDX, IDC_EDIT_MIN_Y_0, m_nlMinY[0]);
	DDX_Text(pDX, IDC_EDIT_MAX_X_0, m_nlMaxX[0]);
	DDX_Text(pDX, IDC_EDIT_MAX_Y_0, m_nlMaxY[0]);

	DDX_Control(pDX, IDC_STATIC_TEMP_VALID_1, m_wndTempValid[1]);
	DDX_Control(pDX, IDC_STATIC_TEMP_ALARM_1, m_wndTempAlarm[1]);
	DDX_Control(pDX, IDC_EDIT_TEMP_CENTER_1, m_edtTempCenter[1]);
	DDX_Control(pDX, IDC_EDIT_TEMP_MIN_1, m_edtTempMin[1]);
	DDX_Control(pDX, IDC_EDIT_TEMP_MAX_1, m_edtTempMax[1]);
	DDX_Control(pDX, IDC_EDIT_TEMP_AVG_1, m_edtTempAvg[1]);
	DDX_Text(pDX, IDC_EDIT_MIN_X_1, m_nlMinX[1]);
	DDX_Text(pDX, IDC_EDIT_MIN_Y_1, m_nlMinY[1]);
	DDX_Text(pDX, IDC_EDIT_MAX_X_1, m_nlMaxX[1]);
	DDX_Text(pDX, IDC_EDIT_MAX_Y_1, m_nlMaxY[1]);

	DDX_Control(pDX, IDC_STATIC_TEMP_VALID_2, m_wndTempValid[2]);
	DDX_Control(pDX, IDC_STATIC_TEMP_ALARM_2, m_wndTempAlarm[2]);
	DDX_Control(pDX, IDC_EDIT_TEMP_CENTER_2, m_edtTempCenter[2]);
	DDX_Control(pDX, IDC_EDIT_TEMP_MIN_2, m_edtTempMin[2]);
	DDX_Control(pDX, IDC_EDIT_TEMP_MAX_2, m_edtTempMax[2]);
	DDX_Control(pDX, IDC_EDIT_TEMP_AVG_2, m_edtTempAvg[2]);
	DDX_Text(pDX, IDC_EDIT_MIN_X_2, m_nlMinX[2]);
	DDX_Text(pDX, IDC_EDIT_MIN_Y_2, m_nlMinY[2]);
	DDX_Text(pDX, IDC_EDIT_MAX_X_2, m_nlMaxX[2]);
	DDX_Text(pDX, IDC_EDIT_MAX_Y_2, m_nlMaxY[2]);

	DDX_Control(pDX, IDC_STATIC_TEMP_VALID_3, m_wndTempValid[3]);
	DDX_Control(pDX, IDC_STATIC_TEMP_ALARM_3, m_wndTempAlarm[3]);
	DDX_Control(pDX, IDC_EDIT_TEMP_CENTER_3, m_edtTempCenter[3]);
	DDX_Control(pDX, IDC_EDIT_TEMP_MIN_3, m_edtTempMin[3]);
	DDX_Control(pDX, IDC_EDIT_TEMP_MAX_3, m_edtTempMax[3]);
	DDX_Control(pDX, IDC_EDIT_TEMP_AVG_3, m_edtTempAvg[3]);
	DDX_Text(pDX, IDC_EDIT_MIN_X_3, m_nlMinX[3]);
	DDX_Text(pDX, IDC_EDIT_MIN_Y_3, m_nlMinY[3]);
	DDX_Text(pDX, IDC_EDIT_MAX_X_3, m_nlMaxX[3]);
	DDX_Text(pDX, IDC_EDIT_MAX_Y_3, m_nlMaxY[3]);

	DDX_Control(pDX, IDC_STATIC_TEMP_VALID_4, m_wndTempValid[4]);
	DDX_Control(pDX, IDC_STATIC_TEMP_ALARM_4, m_wndTempAlarm[4]);
	DDX_Control(pDX, IDC_EDIT_TEMP_CENTER_4, m_edtTempCenter[4]);
	DDX_Control(pDX, IDC_EDIT_TEMP_MIN_4, m_edtTempMin[4]);
	DDX_Control(pDX, IDC_EDIT_TEMP_MAX_4, m_edtTempMax[4]);
	DDX_Control(pDX, IDC_EDIT_TEMP_AVG_4, m_edtTempAvg[4]);
	DDX_Text(pDX, IDC_EDIT_MIN_X_4, m_nlMinX[4]);
	DDX_Text(pDX, IDC_EDIT_MIN_Y_4, m_nlMinY[4]);
	DDX_Text(pDX, IDC_EDIT_MAX_X_4, m_nlMaxX[4]);
	DDX_Text(pDX, IDC_EDIT_MAX_Y_4, m_nlMaxY[4]);

	DDX_Control(pDX, IDC_STATIC_TEMP_VALID_5, m_wndTempValid[5]);
	DDX_Control(pDX, IDC_STATIC_TEMP_ALARM_5, m_wndTempAlarm[5]);
	DDX_Control(pDX, IDC_EDIT_TEMP_CENTER_5, m_edtTempCenter[5]);
	DDX_Control(pDX, IDC_EDIT_TEMP_MIN_5, m_edtTempMin[5]);
	DDX_Control(pDX, IDC_EDIT_TEMP_MAX_5, m_edtTempMax[5]);
	DDX_Control(pDX, IDC_EDIT_TEMP_AVG_5, m_edtTempAvg[5]);
	DDX_Text(pDX, IDC_EDIT_MIN_X_5, m_nlMinX[5]);
	DDX_Text(pDX, IDC_EDIT_MIN_Y_5, m_nlMinY[5]);
	DDX_Text(pDX, IDC_EDIT_MAX_X_5, m_nlMaxX[5]);
	DDX_Text(pDX, IDC_EDIT_MAX_Y_5, m_nlMaxY[5]);

	DDX_Control(pDX, IDC_STATIC_TEMP_VALID_6, m_wndTempValid[6]);
	DDX_Control(pDX, IDC_STATIC_TEMP_ALARM_6, m_wndTempAlarm[6]);
	DDX_Control(pDX, IDC_EDIT_TEMP_CENTER_6, m_edtTempCenter[6]);
	DDX_Control(pDX, IDC_EDIT_TEMP_MIN_6, m_edtTempMin[6]);
	DDX_Control(pDX, IDC_EDIT_TEMP_MAX_6, m_edtTempMax[6]);
	DDX_Control(pDX, IDC_EDIT_TEMP_AVG_6, m_edtTempAvg[6]);
	DDX_Text(pDX, IDC_EDIT_MIN_X_6, m_nlMinX[6]);
	DDX_Text(pDX, IDC_EDIT_MIN_Y_6, m_nlMinY[6]);
	DDX_Text(pDX, IDC_EDIT_MAX_X_6, m_nlMaxX[6]);
	DDX_Text(pDX, IDC_EDIT_MAX_Y_6, m_nlMaxY[6]);

	DDX_Control(pDX, IDC_STATIC_TEMP_VALID_7, m_wndTempValid[7]);
	DDX_Control(pDX, IDC_STATIC_TEMP_ALARM_7, m_wndTempAlarm[7]);
	DDX_Control(pDX, IDC_EDIT_TEMP_CENTER_7, m_edtTempCenter[7]);
	DDX_Control(pDX, IDC_EDIT_TEMP_MIN_7, m_edtTempMin[7]);
	DDX_Control(pDX, IDC_EDIT_TEMP_MAX_7, m_edtTempMax[7]);
	DDX_Control(pDX, IDC_EDIT_TEMP_AVG_7, m_edtTempAvg[7]);
	DDX_Text(pDX, IDC_EDIT_MIN_X_7, m_nlMinX[7]);
	DDX_Text(pDX, IDC_EDIT_MIN_Y_7, m_nlMinY[7]);
	DDX_Text(pDX, IDC_EDIT_MAX_X_7, m_nlMaxX[7]);
	DDX_Text(pDX, IDC_EDIT_MAX_Y_7, m_nlMaxY[7]);

	DDX_Control(pDX, IDC_STATIC_TEMP_VALID_8, m_wndTempValid[8]);
	DDX_Control(pDX, IDC_STATIC_TEMP_ALARM_8, m_wndTempAlarm[8]);
	DDX_Control(pDX, IDC_EDIT_TEMP_CENTER_8, m_edtTempCenter[8]);
	DDX_Control(pDX, IDC_EDIT_TEMP_MIN_8, m_edtTempMin[8]);
	DDX_Control(pDX, IDC_EDIT_TEMP_MAX_8, m_edtTempMax[8]);
	DDX_Control(pDX, IDC_EDIT_TEMP_AVG_8, m_edtTempAvg[8]);
	DDX_Text(pDX, IDC_EDIT_MIN_X_8, m_nlMinX[8]);
	DDX_Text(pDX, IDC_EDIT_MIN_Y_8, m_nlMinY[8]);
	DDX_Text(pDX, IDC_EDIT_MAX_X_8, m_nlMaxX[8]);
	DDX_Text(pDX, IDC_EDIT_MAX_Y_8, m_nlMaxY[8]);

	DDX_Control(pDX, IDC_STATIC_TEMP_VALID_9, m_wndTempValid[9]);
	DDX_Control(pDX, IDC_STATIC_TEMP_ALARM_9, m_wndTempAlarm[9]);
	DDX_Control(pDX, IDC_EDIT_TEMP_CENTER_9, m_edtTempCenter[9]);
	DDX_Control(pDX, IDC_EDIT_TEMP_MIN_9, m_edtTempMin[9]);
	DDX_Control(pDX, IDC_EDIT_TEMP_MAX_9, m_edtTempMax[9]);
	DDX_Control(pDX, IDC_EDIT_TEMP_AVG_9, m_edtTempAvg[9]);
	DDX_Text(pDX, IDC_EDIT_MIN_X_9, m_nlMinX[9]);
	DDX_Text(pDX, IDC_EDIT_MIN_Y_9, m_nlMinY[9]);
	DDX_Text(pDX, IDC_EDIT_MAX_X_9, m_nlMaxX[9]);
	DDX_Text(pDX, IDC_EDIT_MAX_Y_9, m_nlMaxY[9]);
}


BEGIN_MESSAGE_MAP(CThermalTempInfoDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CThermalTempInfoDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


void CThermalTempInfoDlg::OnBnClickedButton1()
{
	ST_SPIDER_THERMAL_REGION_TEMP_INFO stInfo = {NULL, };
	if (SPIDER_GetThermalRegionTemp(theApp.m_hSelectCamera, &stInfo) == E_CTRL_OK)
	{
		CString strValid	= _T("");
		CString strAlarm	= _T("");
		CString strCenter	= _T("");
		CString strMin		= _T("");
		CString strMax		= _T("");
		CString strAvg		= _T("");

		strValid.Format(stInfo.ThermalFullTemp.bValid ? _T("O"):_T("X"));
		strAlarm.Format(stInfo.ThermalFullTemp.bAlarmOn ? _T("On"):_T("Off"));
		strCenter.Format(_T("%.1f"), stInfo.ThermalFullTemp.fCenterTempValue);
		strMin.Format(_T("%.1f"), stInfo.ThermalFullTemp.fMinTempValue);
		strMax.Format(_T("%.1f"), stInfo.ThermalFullTemp.fMaxTempValue);
		strAvg.Format(_T("%.1f"), stInfo.ThermalFullTemp.fAvgTempValue);

		m_wndTempValidEntire.SetWindowText(strValid);
		m_wndTempAlarmEntire.SetWindowText(strAlarm);
		m_edtTempCenterEntire.SetWindowText(strCenter);
		m_edtTempMinEntire.SetWindowText(strMin);
		m_edtTempMaxEntire.SetWindowText(strMax);
		m_edtTempAvgEntire.SetWindowText(strAvg);
		
		m_nlMinXEntire = stInfo.ThermalFullTemp.ptMinTemp.nPositionX;
		m_nlMinYEntire = stInfo.ThermalFullTemp.ptMinTemp.nPositionY;
		m_nlMaxXEntire = stInfo.ThermalFullTemp.ptMaxTemp.nPositionX;
		m_nlMaxYEntire = stInfo.ThermalFullTemp.ptMaxTemp.nPositionY;
		
		
		for (int i = 0; i < _countof(stInfo.ThermalRegionTemp); i++)
		{
			strValid.Format(stInfo.ThermalRegionTemp[i].bValid ? _T("O"):_T("X"));
			strAlarm.Format(stInfo.ThermalRegionTemp[i].bAlarmOn ? _T("On"):_T("Off"));
			strCenter.Format(_T("%.1f"), stInfo.ThermalRegionTemp[i].fCenterTempValue);
			strMin.Format(_T("%.1f"), stInfo.ThermalRegionTemp[i].fMinTempValue);
			strMax.Format(_T("%.1f"), stInfo.ThermalRegionTemp[i].fMaxTempValue);
			strAvg.Format(_T("%.1f"), stInfo.ThermalRegionTemp[i].fAvgTempValue);

			m_wndTempValid[i].SetWindowText(strValid);
			m_wndTempAlarm[i].SetWindowText(strAlarm);
			m_edtTempCenter[i].SetWindowText(strCenter);
			m_edtTempMin[i].SetWindowText(strMin);
			m_edtTempMax[i].SetWindowText(strMax);
			m_edtTempAvg[i].SetWindowText(strAvg);

			m_nlMinX[i] = stInfo.ThermalRegionTemp[i].ptMinTemp.nPositionX;
			m_nlMinY[i] = stInfo.ThermalRegionTemp[i].ptMinTemp.nPositionY;
			m_nlMaxX[i] = stInfo.ThermalRegionTemp[i].ptMaxTemp.nPositionX;
			m_nlMaxY[i] = stInfo.ThermalRegionTemp[i].ptMaxTemp.nPositionY;
		}

		UpdateData(FALSE);
	}
}


BOOL CThermalTempInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	OnBnClickedButton1();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
