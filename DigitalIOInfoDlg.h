#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CDigitalIOInfoDlg 대화 상자입니다.

class CDigitalIOInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CDigitalIOInfoDlg)

public:
	CDigitalIOInfoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDigitalIOInfoDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIGITAL_IO_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

protected:
	ST_SPIDER_DIGITAL_INPUTS	m_DigitalInputInfo;
	ST_SPIDER_DIGITAL_OUTPUTS	m_DigitalOutputInfo;

	CListCtrl m_lstCtrlInput;
	CEdit m_edtInputID;
	CComboBox m_cbInputEnable;
	CComboBox m_cbInputActive;
	CButton m_btnInputModify;
	CListCtrl m_lstCtrlOutput;
	CEdit m_edtOutputID;
	CComboBox m_cbOutputEnable;
	CComboBox m_cbOutputActive;
	CEdit m_edtOutputDuration;
	long m_nlOutputDuration;
	CButton m_btnOutputModify;
	CEdit m_edtOutputToggleID;
	CComboBox m_cbOuputToggleEnable;
	CEdit m_edtOutputToggleInterval;
	long m_nlToggleInterval;

protected:
	void InitDigitalInput();
	void InitDigitalOutput();

	void UpdateDigitalInputInfo(ST_SPIDER_DIGITAL_INPUT_INFO* pDigitalInputInfo);
	void UpdateDigitalOutputInfo(ST_SPIDER_DIGITAL_OUTPUT_INFO* pDigitalOutputInfo);

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonInputModify();
	afx_msg void OnBnClickedButtonOutputModify();
	afx_msg void OnLvnItemchangedListInput(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListOutput(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonOutputToggleSet();
	afx_msg void OnCbnSelchangeComboOutputToggleEnable();
	long m_nlMaxDuration;
	afx_msg void OnBnClickedButtonOutputExecute();
};
