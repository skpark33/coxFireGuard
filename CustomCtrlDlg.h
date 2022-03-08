#pragma once
#include "afxwin.h"


// CCustomCtrlDlg dialog

class CCustomCtrlDlg : public CDialog
{
	DECLARE_DYNAMIC(CCustomCtrlDlg)

public:
	CCustomCtrlDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCustomCtrlDlg();

// Dialog Data
	enum { IDD = IDD_CUSTOM_CTRL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	CComboBox m_Combo_AutoClipMode;
	afx_msg void OnBnClickedButtonAutoclipModify();
	CComboBox m_Combo_Enable;
	CComboBox m_Combo_MaxValue;
	afx_msg void OnBnClickedButtonSensorUpModify();
protected:
	UINT m_nChannelCnt;
	CComboBox m_cbChannel;
	int m_nChannel;
	CButton m_btnChannelSync;

protected:
	void CreateChannelComboBox();
	void QueryChannelCount();

public:
	afx_msg void OnBnClickedButtonChannelModify();
	afx_msg void OnBnClickedButtonChannelSync();
protected:
	CButton m_btnChannelModify;
	CComboBox m_cbVideoOutEnable;
	CComboBox m_cbVideoOutType;
	CComboBox m_cbDefog;
	CComboBox m_cbAgcType;
	CComboBox m_cbRecordEnable;
	CComboBox m_cbRecordType;
	CComboBox m_cbStrobeNightOnly;
	CComboBox m_cbStrobeStrength;

protected:
	void InitVideoOut();
	void InitDefog();
	void InitAgc();
	void InitRecord();
	void InitStrobeNightOnly();
	void InitStrobeStrength();

public:
	afx_msg void OnBnClickedButtonVideoOutModify();
	afx_msg void OnBnClickedButtonDefogModify();
	afx_msg void OnBnClickedButtonAgcModify();
	afx_msg void OnBnClickedButtonRecordModify();
	afx_msg void OnBnClickedButtonStrobeNightModify();
	afx_msg void OnBnClickedButtonStrobeStrengthModify();
};
