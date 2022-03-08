
// TestDlgDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "WaitDlg.h"
#include "StreamingDlg.h"
#include "afxwin.h"




// CTestDlgDlg dialog
class CTestDlgDlg : public CDialog
{
// Construction
public:
	CTestDlgDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TESTDLG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


public:
	
	CStreamingDlg m_StreamingDlg;


	HANDLE m_hDiscoveryEvent;
	

	CWaitDlg	WaitDlg;
	HANDLE m_hThread_Discovery;
	HANDLE m_hThread_Polling;  //skpark in your area
	DWORD m_dwThreadID_Discovery;
	DWORD m_dwThreadID_Polling;//skpark in your area
	static DWORD WINAPI ThreadProc_Discovery(LPVOID lpParameter);
	static DWORD WINAPI ThreadProc_Polling(LPVOID lpParameter);  //skpark in your area
	void StartDiscovery();
	
	void Polling();			//skpark in your area
	void GetAllCamera();	//skaprk in your area
	void SelectOneCamera(int nSel);
	ST_SPIDER_THERMAL_REGION_TEMP_INFO m_stTemp[MAX_CAMERA];
	ST_SPIDER_DISCOVERY_CAMEAR_INFO m_stInfo[MAX_CAMERA];
	int m_foundedCount;
	bool m_initDone;
	bool m_stopPolling;
	afx_msg void OnClose();
	//skpark in your area end

	bool m_bInitTriggerServer;
	bool m_bInitSyslogServer;

	HTRIGGER m_hTrigger;
	HSYSLOG	m_hSyslog;


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_List_Camera;
	afx_msg void OnBnClickedButtonDiscovery();
	afx_msg void OnNMClickListCamera(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonDevice();
	afx_msg void OnBnClickedButtonFeature();
	afx_msg void OnBnClickedButtonOverlayText();
	afx_msg void OnBnClickedButtonMotion();
	afx_msg void OnBnClickedButtonPrivacyMask();
	afx_msg void OnBnClickedButtonStream();
	afx_msg void OnBnClickedButtonTime();
	afx_msg void OnBnClickedButtonUser();
	afx_msg void OnBnClickedButtonNetworkIpaddress();
	afx_msg void OnBnClickedButtonNetworkIpFilter();
	afx_msg void OnBnClickedButtonNotifyMailing();
	afx_msg void OnBnClickedButtonEventTrigger();
	afx_msg void OnBnClickedButtonEventSchedule();
	afx_msg void OnBnClickedButtonCustomTrigger();
	afx_msg void OnBnClickedButtonCustomStrobe();
	afx_msg void OnBnClickedButtonStorage();
	afx_msg void OnBnClickedButtonCustomStorage();
	afx_msg void OnBnClickedButtonCustomCtrl();
	afx_msg LRESULT OnTriggerData(WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnSyslogData(WPARAM wParam, LPARAM lParam );
	afx_msg void OnBnClickedButtonStreaming();
	afx_msg void OnBnClickedButtonReboot();	
	afx_msg void OnBnClickedButtonExport();
	afx_msg void OnBnClickedButtonImport();
	afx_msg void OnBnClickedButtonSnapshot();
	afx_msg void OnBnClickedButtonSerialport();	
protected:
	CComboBox m_cbChSnapShot;
public:
	afx_msg void OnBnClickedButtonChannelSnapshot();
	afx_msg void OnBnClickedButtonStreamRoiInfo();
	afx_msg void OnBnClickedButtonThermalSpot();
	afx_msg void OnBnClickedButtonDigitalIo();
	afx_msg void OnBnClickedButtonDdns();
	afx_msg void OnBnClickedButtonSnmp();
	afx_msg void OnBnClickedButtonPppoe();
};
