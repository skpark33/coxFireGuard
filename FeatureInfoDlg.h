#pragma once

#ifdef _WIN32_WCE
#error "CDialog is not supported for Windows CE."
#endif 

// CFeatureInfoDlg dialog

class CFeatureInfoDlg : public CDialog
{
	DECLARE_DYNCREATE(CFeatureInfoDlg)

public:
	CFeatureInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFeatureInfoDlg();


// Dialog Data
	enum { IDD = IDD_FEATURE_INFO, IDH = IDR_HTML_FEATUREINFODLG };


	ST_SPIDER_FEATURE_INFO		m_stInfo;
	void _DisplayInfo();


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	CComboBox m_Combo_PowerFrequency;
	CComboBox m_Combo_WBMode;
	CComboBox m_Combo_ExposureMode;
	CComboBox m_Combo_DayNightType;
	CButton m_Check_DayNightSchedule;
	CSliderCtrl m_Slider_Gamma;
	CSliderCtrl m_Slider_Hue;
	CSliderCtrl m_Slider_Saturation;
	CSliderCtrl m_Slider_Sharpness;
	CSliderCtrl m_Slider_Contrast;
	CSliderCtrl m_Slider_Brightness;
	CSliderCtrl m_Slider_Gain;

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButtonApply();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedCheckGamma();
	afx_msg void OnCbnSelchangeComboExposureMode();
};
