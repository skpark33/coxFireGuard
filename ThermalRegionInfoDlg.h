#pragma once
#include "afxwin.h"

typedef struct _tagThermalRegionWnd {
	CComboBox cbEnable;
	CEdit edtX;
	CEdit edtY;
	CEdit edtWidth;
	CEdit edtHeight;
	CComboBox cbAlarmEnable;
	CComboBox cbAlarmMode;
	CComboBox cbAlarmCondition;
	CEdit edtAlarmTemp;
	CEdit edtAlarmStartDelay;
	CEdit edtAlarmStopDelay;
	CButton btnModify;
} THERMAL_REGION_WND, *PTHERMAL_REGION_WND;

// CThermalRegionInfoDlg 대화 상자입니다.

class CThermalRegionInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CThermalRegionInfoDlg)

public:
	CThermalRegionInfoDlg(ST_SPIDER_THERMAL_COMPONENTS* pThermalComponents, CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CThermalRegionInfoDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_THERMAL_REGION_INFO };

protected:
	ST_SPIDER_THERMAL_COMPONENTS* m_pThermalComponents;

	ST_SPIDER_STREAM_RESOLUTION_INFO m_MaxRes;
	ST_SPIDER_THERMAL_ALARM m_EntireAlarm;
	ST_SPIDER_THERMAL_REGION_INFO m_RegionInfo;

	THERMAL_REGION_WND m_wndEntire;
	THERMAL_REGION_WND m_wndRegion[10];

protected:
	void CreateCtrl();
	void CreateRegionCtrl(THERMAL_REGION_WND* pRegionWnd);
	void EnableRegionCtrl(THERMAL_REGION_WND* pRegionWnd, BOOL bEnable = TRUE);

	void RegionCtrl(THERMAL_REGION_WND* pRegionWnd);
	void RegionAlarmCtrl(THERMAL_REGION_WND* pRegionWnd);

	void Initialize();
	void SetCtrlValue();

	void SetRegionCtrlValue(BOOL bEnable, CPoint pt, CSize size, ST_SPIDER_THERMAL_ALARM* pAlaramInfo, THERMAL_REGION_WND* pRegionWnd);

	void ModifyRegionInfo(UINT uiID);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	CComboBox m_cbEnable;
	CEdit m_edtX;
	CEdit m_edtY;
	CEdit m_edtWidth;
	CEdit m_edtHeight;
	CComboBox m_cbAlarmEnable;
	CComboBox m_cbAlarmMode;
	CComboBox m_cbAlarmCondition;
	CEdit m_edtAlarmTemp;
	CEdit m_edtAlarmStartDelay;
	CEdit m_edtAlarmStopDelay;
	CButton m_btnModify;
	afx_msg void OnBnClickedButtonModifyentire();
	afx_msg void OnBnClickedButtonModify0();
	afx_msg void OnBnClickedButtonModify1();
	afx_msg void OnBnClickedButtonModify2();
	afx_msg void OnBnClickedButtonModify3();
	afx_msg void OnBnClickedButtonModify4();
	afx_msg void OnBnClickedButtonModify5();
	afx_msg void OnBnClickedButtonModify6();
	afx_msg void OnBnClickedButtonModify7();
	afx_msg void OnBnClickedButtonModify8();
	afx_msg void OnBnClickedButtonModify9();

	void UpdateRegionInfo(ST_SPIDER_THERMAL_REGION& stInfo, UINT uiID);
	afx_msg void OnCbnSelchangeComboEnable0();
	afx_msg void OnCbnSelchangeComboEnable1();
	afx_msg void OnCbnSelchangeComboEnable2();
	afx_msg void OnCbnSelchangeComboEnable3();
	afx_msg void OnCbnSelchangeComboEnable4();
	afx_msg void OnCbnSelchangeComboEnable5();
	afx_msg void OnCbnSelchangeComboEnable6();
	afx_msg void OnCbnSelchangeComboEnable7();
	afx_msg void OnCbnSelchangeComboEnable8();
	afx_msg void OnCbnSelchangeComboEnable9();
	afx_msg void OnCbnSelchangeComboAlarmEnableEntire();
	afx_msg void OnCbnSelchangeComboAlarmEnable0();
	afx_msg void OnCbnSelchangeComboAlarmEnable1();
	afx_msg void OnCbnSelchangeComboAlarmEnable2();
	afx_msg void OnCbnSelchangeComboAlarmEnable3();
	afx_msg void OnCbnSelchangeComboAlarmEnable4();
	afx_msg void OnCbnSelchangeComboAlarmEnable5();
	afx_msg void OnCbnSelchangeComboAlarmEnable6();
	afx_msg void OnCbnSelchangeComboAlarmEnable7();
	afx_msg void OnCbnSelchangeComboAlarmEnable8();
	afx_msg void OnCbnSelchangeComboAlarmEnable9();
};
