#pragma once

#ifdef _WIN32_WCE
#error "CDialog is not supported for Windows CE."
#endif 

// CEventScheduleInfoDlg dialog

class CEventScheduleInfoDlg : public CDialog
{
	DECLARE_DYNCREATE(CEventScheduleInfoDlg)

public:
	CEventScheduleInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEventScheduleInfoDlg();


// Dialog Data
	enum { IDD = IDD_EVENT_SCHEDULE_INFO, IDH = IDR_HTML_EVENTSCHEDULEINFODLG };


	ST_SPIDER_EVENT_SCHEDULE_INFO	m_stInfo;
	vector<ST_SPIDER_EVENT_SCHEDULE_TIME_INFO>		m_vInfo;

	CButton butMonHour[24];
	CButton butTueHour[24];
	CButton butWedHour[24];
	CButton butThuHour[24];
	CButton butFriHour[24];
	CButton butSatHour[24];
	CButton butSunHour[24];


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonModifySchedule();
	afx_msg void OnBnClickedCheckAllSchedule();
	afx_msg void OnBnClickedCheckBussinessSchedule();
	afx_msg void OnBnClickedCheckWeekendSchedule();
};
