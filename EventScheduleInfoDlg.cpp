// EventScheduleInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDlg.h"
#include "EventScheduleInfoDlg.h"


// CEventScheduleInfoDlg dialog

IMPLEMENT_DYNCREATE(CEventScheduleInfoDlg, CDialog)

CEventScheduleInfoDlg::CEventScheduleInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEventScheduleInfoDlg::IDD, pParent)
{

}

CEventScheduleInfoDlg::~CEventScheduleInfoDlg()
{
}

void CEventScheduleInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL CEventScheduleInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

#define CHECK_MON_HOUR1		321
#define CHECK_TUE_HOUR1		421
#define CHECK_WED_HOUR1		521
#define CHECK_THU_HOUR1		621
#define CHECK_FRI_HOUR1		721
#define CHECK_SAT_HOUR1		821
#define CHECK_SUN_HOUR1		921

	CRect rect;

	for(int nhour = 0; nhour < 24; nhour++)
	{
		rect.left = 85 + (nhour*20);
		rect.right = rect.left + 18;

		rect.top = 110;
		rect.bottom = rect.top + 18;

		if(TRUE == butMonHour[nhour].Create((""), BS_AUTOCHECKBOX | WS_VISIBLE | WS_CHILD, rect, this, CHECK_MON_HOUR1 + nhour))
			butMonHour[nhour].ShowWindow(true);

		rect.top += 25;
		rect.bottom = rect.top + 18;

		if(TRUE == butTueHour[nhour].Create((""), BS_AUTOCHECKBOX | WS_VISIBLE | WS_CHILD, rect, this, CHECK_TUE_HOUR1 + nhour))
			butTueHour[nhour].ShowWindow(true);

		rect.top += 25;
		rect.bottom = rect.top + 18;

		if(TRUE == butWedHour[nhour].Create((""), BS_AUTOCHECKBOX | WS_VISIBLE | WS_CHILD, rect, this, CHECK_WED_HOUR1 + nhour))
			butWedHour[nhour].ShowWindow(true);

		rect.top += 25;
		rect.bottom = rect.top + 18;

		if(TRUE == butThuHour[nhour].Create((""), BS_AUTOCHECKBOX | WS_VISIBLE | WS_CHILD, rect, this, CHECK_THU_HOUR1 + nhour))
			butThuHour[nhour].ShowWindow(true);

		rect.top += 25;
		rect.bottom = rect.top + 18;

		if(TRUE == butFriHour[nhour].Create((""), BS_AUTOCHECKBOX | WS_VISIBLE | WS_CHILD, rect, this, CHECK_FRI_HOUR1 + nhour))
			butFriHour[nhour].ShowWindow(true);

		rect.top += 25;
		rect.bottom = rect.top + 18;

		if(TRUE == butSatHour[nhour].Create((""), BS_AUTOCHECKBOX | WS_VISIBLE | WS_CHILD, rect, this, CHECK_SAT_HOUR1 + nhour))
			butSatHour[nhour].ShowWindow(true);

		rect.top += 25;
		rect.bottom = rect.top + 18;

		if(TRUE == butSunHour[nhour].Create((""), BS_AUTOCHECKBOX | WS_VISIBLE | WS_CHILD, rect, this, CHECK_SUN_HOUR1 + nhour))
			butSunHour[nhour].ShowWindow(true);
	}


	m_vInfo.clear();

	long lret = SPIDER_GetEventScheduleInfo(theApp.m_hSelectCamera, &m_stInfo);
	if(lret != E_CTRL_OK)
	{
		MessageBox(GetErrorString(lret), ("Fail"));
	}
	else
	{
		CString sztext;
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_BEGIN_DATE), m_stInfo.strBeginTime, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_END_DATE), m_stInfo.strEndTime, sztext);


		long nCount = SPIDER_GetEventScheduleTimeCount(theApp.m_hSelectCamera);
		for(int i = 0; i < nCount; i++)
		{
			ST_SPIDER_EVENT_SCHEDULE_TIME_INFO stInfo = {0};
			long lret = SPIDER_GetEventScheduleTimeInfo(theApp.m_hSelectCamera, i, &stInfo);
			if(lret != E_CTRL_OK)
			{
				MessageBox(GetErrorString(lret), ("Fail"));
				break;
			}

			m_vInfo.push_back(stInfo);



			UINT uID = 0;
			switch(stInfo.nDayOfWeek)
			{
			case E_DAYWEEK_MON:		uID = CHECK_MON_HOUR1; break;
			case E_DAYWEEK_TUE:		uID = CHECK_TUE_HOUR1; break;
			case E_DAYWEEK_WED:		uID = CHECK_WED_HOUR1; break;
			case E_DAYWEEK_THU:		uID = CHECK_THU_HOUR1; break;
			case E_DAYWEEK_FRI:		uID = CHECK_FRI_HOUR1; break;
			case E_DAYWEEK_SAT:		uID = CHECK_SAT_HOUR1; break;
			case E_DAYWEEK_SUN:		uID = CHECK_SUN_HOUR1; break;
			}


			if(uID)
			{
				//bitstring
				{
					int nMaxHour = strlen(stInfo.strBitString);
					if(nMaxHour > 24) nMaxHour = 24;
					for(int nhour = 0; nhour < nMaxHour; nhour++)
					{
						if(stInfo.strBitString[nhour] == '1')
						{
							GetDlgItem(uID+nhour)->SendMessage(BM_SETCHECK, BST_CHECKED);
						}
					}
				}

				//begintime ~ endtime
				{
					int nMinHour = 0;
					int nMaxHour = 23;
					if(strlen(stInfo.strBeginTime))
					{
						int nMin; int nSec;
						sscanf(stInfo.strBeginTime, "%d:%d:%d", &nMinHour, &nMin, &nSec);

						if(strlen(stInfo.strEndTime))
							sscanf(stInfo.strEndTime, "%d:%d:%d", &nMaxHour, &nMin, &nSec);
							
						if(nMaxHour > 24) nMaxHour = 24;
						for(int nhour = nMinHour; nhour <= nMaxHour; nhour++)
						{
							GetDlgItem(uID+nhour)->SendMessage(BM_SETCHECK, BST_CHECKED);
						}
					}
				}
			}	
		}
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CEventScheduleInfoDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY_SCHEDULE, &CEventScheduleInfoDlg::OnBnClickedButtonModifySchedule)
	ON_BN_CLICKED(IDC_CHECK_ALL_SCHEDULE, &CEventScheduleInfoDlg::OnBnClickedCheckAllSchedule)
	ON_BN_CLICKED(IDC_CHECK_BUSSINESS_SCHEDULE, &CEventScheduleInfoDlg::OnBnClickedCheckBussinessSchedule)
	ON_BN_CLICKED(IDC_CHECK_WEEKEND_SCHEDULE, &CEventScheduleInfoDlg::OnBnClickedCheckWeekendSchedule)
END_MESSAGE_MAP()

// CEventScheduleInfoDlg message handlers

void CEventScheduleInfoDlg::OnBnClickedCheckAllSchedule()
{
	LRESULT lcheck = 0;
	if(GetDlgItem(IDC_CHECK_ALL_SCHEDULE)->SendMessage(BM_GETCHECK) == BST_CHECKED)
		lcheck = BST_CHECKED;

	int nMaxHour = 24;
	for(int nhour = 0; nhour < nMaxHour; nhour++)
	{
		GetDlgItem(CHECK_MON_HOUR1+nhour)->SendMessage(BM_SETCHECK, lcheck);
		GetDlgItem(CHECK_TUE_HOUR1+nhour)->SendMessage(BM_SETCHECK, lcheck);
		GetDlgItem(CHECK_WED_HOUR1+nhour)->SendMessage(BM_SETCHECK, lcheck);
		GetDlgItem(CHECK_THU_HOUR1+nhour)->SendMessage(BM_SETCHECK, lcheck);
		GetDlgItem(CHECK_FRI_HOUR1+nhour)->SendMessage(BM_SETCHECK, lcheck);
		GetDlgItem(CHECK_SAT_HOUR1+nhour)->SendMessage(BM_SETCHECK, lcheck);
		GetDlgItem(CHECK_SUN_HOUR1+nhour)->SendMessage(BM_SETCHECK, lcheck);
	}
}

void CEventScheduleInfoDlg::OnBnClickedCheckBussinessSchedule()
{
	LRESULT lcheck = 0;
	if(GetDlgItem(IDC_CHECK_BUSSINESS_SCHEDULE)->SendMessage(BM_GETCHECK) == BST_CHECKED)
		lcheck = BST_CHECKED;

	for(int nhour = 9; nhour < 19; nhour++)
	{
		GetDlgItem(CHECK_MON_HOUR1+nhour)->SendMessage(BM_SETCHECK, lcheck);
		GetDlgItem(CHECK_TUE_HOUR1+nhour)->SendMessage(BM_SETCHECK, lcheck);
		GetDlgItem(CHECK_WED_HOUR1+nhour)->SendMessage(BM_SETCHECK, lcheck);
		GetDlgItem(CHECK_THU_HOUR1+nhour)->SendMessage(BM_SETCHECK, lcheck);
		GetDlgItem(CHECK_FRI_HOUR1+nhour)->SendMessage(BM_SETCHECK, lcheck);
	}
}

void CEventScheduleInfoDlg::OnBnClickedCheckWeekendSchedule()
{
	LRESULT lcheck = 0;
	if(GetDlgItem(IDC_CHECK_WEEKEND_SCHEDULE)->SendMessage(BM_GETCHECK) == BST_CHECKED)
		lcheck = BST_CHECKED;

	int nMaxHour = 24;
	for(int nhour = 0; nhour < nMaxHour; nhour++)
	{
		GetDlgItem(CHECK_SAT_HOUR1+nhour)->SendMessage(BM_SETCHECK, lcheck);
		GetDlgItem(CHECK_SUN_HOUR1+nhour)->SendMessage(BM_SETCHECK, lcheck);
	}
}

void CEventScheduleInfoDlg::OnBnClickedButtonModifySchedule()
{
	ST_SPIDER_EVENT_SCHEDULE_INFO stNew = m_stInfo;

	CString sztext;

	GetDlgItem(IDC_EDIT_BEGIN_DATE)->GetWindowText(sztext);
	if(strcmp(stNew.strBeginTime, "NA"))
		StringCopyTo(sztext, stNew.strBeginTime);

	GetDlgItem(IDC_EDIT_END_DATE)->GetWindowText(sztext);
	if(strcmp(stNew.strEndTime, "NA"))
		StringCopyTo(sztext, stNew.strEndTime);




	ST_SPIDER_EVENT_SCHEDULE_TIME_INFO WeekList[7] = {0};
	WeekList[0].nDayOfWeek = E_DAYWEEK_MON;
	WeekList[1].nDayOfWeek = E_DAYWEEK_TUE;
	WeekList[2].nDayOfWeek = E_DAYWEEK_WED;
	WeekList[3].nDayOfWeek = E_DAYWEEK_THU;
	WeekList[4].nDayOfWeek = E_DAYWEEK_FRI;
	WeekList[5].nDayOfWeek = E_DAYWEEK_SAT;
	WeekList[6].nDayOfWeek = E_DAYWEEK_SUN;

	int nMaxHour = 24;
	for(int nhour = 0; nhour < nMaxHour; nhour++)
	{
		if(GetDlgItem(CHECK_MON_HOUR1+nhour)->SendMessage(BM_GETCHECK) == BST_CHECKED)
			WeekList[0].strBitString[nhour] = '1';
		else
			WeekList[0].strBitString[nhour] = '0';

		if(GetDlgItem(CHECK_TUE_HOUR1+nhour)->SendMessage(BM_GETCHECK) == BST_CHECKED)
			WeekList[1].strBitString[nhour] = '1';
		else
			WeekList[1].strBitString[nhour] = '0';

		if(GetDlgItem(CHECK_WED_HOUR1+nhour)->SendMessage(BM_GETCHECK) == BST_CHECKED)
			WeekList[2].strBitString[nhour] = '1';
		else
			WeekList[2].strBitString[nhour] = '0';

		if(GetDlgItem(CHECK_THU_HOUR1+nhour)->SendMessage(BM_GETCHECK) == BST_CHECKED)
			WeekList[3].strBitString[nhour] = '1';
		else
			WeekList[3].strBitString[nhour] = '0';

		if(GetDlgItem(CHECK_FRI_HOUR1+nhour)->SendMessage(BM_GETCHECK) == BST_CHECKED)
			WeekList[4].strBitString[nhour] = '1';
		else
			WeekList[4].strBitString[nhour] = '0';

		if(GetDlgItem(CHECK_SAT_HOUR1+nhour)->SendMessage(BM_GETCHECK) == BST_CHECKED)
			WeekList[5].strBitString[nhour] = '1';
		else
			WeekList[5].strBitString[nhour] = '0';

		if(GetDlgItem(CHECK_SUN_HOUR1+nhour)->SendMessage(BM_GETCHECK) == BST_CHECKED)
			WeekList[6].strBitString[nhour] = '1';
		else
			WeekList[6].strBitString[nhour] = '0';
	}

	stNew.nNumTimeBlock = 7;
	long lret = SPIDER_SetEventScheduleInfo(theApp.m_hSelectCamera, stNew, stNew.nNumTimeBlock, WeekList);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));


}
