#pragma once
#include "afxwin.h"


// CStreamROIInfoDlg 대화 상자입니다.

class CStreamROIInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CStreamROIInfoDlg)

public:
	CStreamROIInfoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CStreamROIInfoDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_STREAM_ROI_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	CComboBox m_cbEnable1;
	CComboBox m_cbEnable2;
	CComboBox m_cbEnable3;

	CButton m_btnModify1;
	CButton m_btnModify2;
	CButton m_btnModify3;
	CButton m_btnRefresh;
	
	ST_SPIDER_STREAM_ROI_INFO m_stStreamROIInfo;

protected:
	void CreateComboBox(CComboBox* pcbEnable);
	void ModifyStreamROI(ST_SPIDER_STREAM_ROI* pStreamROI);

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonModify1();
	afx_msg void OnBnClickedButtonModify2();
	afx_msg void OnBnClickedButtonModify3();
	afx_msg void OnBnClickedButtonRefresh();
	
};
