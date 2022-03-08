
// TestDlgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDlg.h"
#include "TestDlgDlg.h"

#include "DeviceInfoDlg.h"
#include "StreamInfoDlg.h"
#include "MotionInfoDlg.h"
#include "FeatureInfoDlg.h"
#include "EventScheduleInfoDlg.h"
#include "EventTriggerInfoDlg.h"
#include "NetworkIPAddrInfoDlg.h"
#include "NotifyMailingInfoDlg.h"
#include "NetworkIPFilterInfoDlg.h"
#include "OverlayTextInfoDlg.h"
#include "PrivacyMaskInfoDlg.h"
#include "TimeInfoDlg.h"
#include "UserInfoDlg.h"
#include "CustomTriggerInfoDlg.h"
#include "CustomStrobeInfoDlg.h"
#include "SerialPortInfoDlg.h"
#include "CustomCtrlDlg.h"
#include "StreamROIInfoDlg.h"
#include "ThermalSpotInfoDlg.h"
#include "ThermalCtrlInfoDlg.h"
#include "DigitalIOInfoDlg.h"
#include "DynamicDNSInfoDlg.h"
#include "SNMPInfoDlg.h"
#include "PPPoEInfoDlg.h"
#include "TraceLog.h"

static char gszCurDir[MAX_PATH] = "";


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTestDlgDlg dialog






CTestDlgDlg::CTestDlgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlgDlg::IDD, pParent)
	, m_foundedCount(0)  //skpark in your area
	, m_initDone(false)
	, m_stopPolling(false)
{
	
	for (int i = 0; i < MAX_CAMERA; i++) {
		theApp.m_allCamera[i] = NULL;
	}


	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_hDiscoveryEvent = NULL;
	m_hThread_Discovery = NULL;
	m_dwThreadID_Discovery = 0;
	m_dwThreadID_Polling = 0;  //skpark in your area

	m_hTrigger = NULL;
	m_hSyslog = NULL;

	m_bInitTriggerServer = false;
	m_bInitSyslogServer = false;


	::GetModuleFileNameA(::AfxGetInstanceHandle(), gszCurDir, MAX_PATH);
	int nfind = strlen(gszCurDir);
	if(nfind)
	{
		nfind -= 1;
		while(gszCurDir[nfind] != '\\' && nfind > 0)
		{
			nfind--;
		}
		gszCurDir[nfind+1] = '\0';
	}

}

void CTestDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CAMERA, m_List_Camera);	
	DDX_Control(pDX, IDC_COMBO_CH_SNAPSHOT, m_cbChSnapShot);
}

BEGIN_MESSAGE_MAP(CTestDlgDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_DISCOVERY, &CTestDlgDlg::OnBnClickedButtonDiscovery)
	ON_NOTIFY(NM_CLICK, IDC_LIST_CAMERA, &CTestDlgDlg::OnNMClickListCamera)
	ON_BN_CLICKED(IDC_BUTTON_DEVICE, &CTestDlgDlg::OnBnClickedButtonDevice)
	ON_BN_CLICKED(IDC_BUTTON_FEATURE, &CTestDlgDlg::OnBnClickedButtonFeature)
	ON_BN_CLICKED(IDC_BUTTON_OVERLAY_TEXT, &CTestDlgDlg::OnBnClickedButtonOverlayText)
	ON_BN_CLICKED(IDC_BUTTON_MOTION, &CTestDlgDlg::OnBnClickedButtonMotion)
	ON_BN_CLICKED(IDC_BUTTON_PRIVACY_MASK, &CTestDlgDlg::OnBnClickedButtonPrivacyMask)
	ON_BN_CLICKED(IDC_BUTTON_STREAM, &CTestDlgDlg::OnBnClickedButtonStream)
	ON_BN_CLICKED(IDC_BUTTON_TIME, &CTestDlgDlg::OnBnClickedButtonTime)
	ON_BN_CLICKED(IDC_BUTTON_USER, &CTestDlgDlg::OnBnClickedButtonUser)
	ON_BN_CLICKED(IDC_BUTTON_NETWORK_IPADDRESS, &CTestDlgDlg::OnBnClickedButtonNetworkIpaddress)
	ON_BN_CLICKED(IDC_BUTTON_NETWORK_IP_FILTER, &CTestDlgDlg::OnBnClickedButtonNetworkIpFilter)
	ON_BN_CLICKED(IDC_BUTTON_NOTIFY_MAILING, &CTestDlgDlg::OnBnClickedButtonNotifyMailing)
	ON_BN_CLICKED(IDC_BUTTON_EVENT_TRIGGER, &CTestDlgDlg::OnBnClickedButtonEventTrigger)
	ON_BN_CLICKED(IDC_BUTTON_EVENT_SCHEDULE, &CTestDlgDlg::OnBnClickedButtonEventSchedule)
	ON_BN_CLICKED(IDC_BUTTON_CUSTOM_TRIGGER, &CTestDlgDlg::OnBnClickedButtonCustomTrigger)
	ON_BN_CLICKED(IDC_BUTTON_CUSTOM_STROBE, &CTestDlgDlg::OnBnClickedButtonCustomStrobe)
	ON_BN_CLICKED(IDC_BUTTON_STORAGE, &CTestDlgDlg::OnBnClickedButtonStorage)
	ON_BN_CLICKED(IDC_BUTTON_CUSTOM_STORAGE, &CTestDlgDlg::OnBnClickedButtonCustomStorage)
	ON_BN_CLICKED(IDC_BUTTON_CUSTOM_CTRL, &CTestDlgDlg::OnBnClickedButtonCustomCtrl)
	ON_MESSAGE(WM_TRIGGER, OnTriggerData)
	ON_MESSAGE(WM_SYSLOG, OnSyslogData)
	ON_BN_CLICKED(IDC_BUTTON_STREAMING, &CTestDlgDlg::OnBnClickedButtonStreaming)
	ON_BN_CLICKED(IDC_BUTTON_REBOOT, &CTestDlgDlg::OnBnClickedButtonReboot)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, &CTestDlgDlg::OnBnClickedButtonExport)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT, &CTestDlgDlg::OnBnClickedButtonImport)	
	ON_BN_CLICKED(IDC_BUTTON_SNAPSHOT, &CTestDlgDlg::OnBnClickedButtonSnapshot)
	ON_BN_CLICKED(IDC_BUTTON_SERIALPORT, &CTestDlgDlg::OnBnClickedButtonSerialport)	
	ON_BN_CLICKED(IDC_BUTTON_CHANNEL_SNAPSHOT, &CTestDlgDlg::OnBnClickedButtonChannelSnapshot)
	ON_BN_CLICKED(IDC_BUTTON_STREAM_ROI_INFO, &CTestDlgDlg::OnBnClickedButtonStreamRoiInfo)
	ON_BN_CLICKED(IDC_BUTTON_THERMAL_SPOT, &CTestDlgDlg::OnBnClickedButtonThermalSpot)
	ON_BN_CLICKED(IDC_BUTTON_DIGITAL_IO, &CTestDlgDlg::OnBnClickedButtonDigitalIo)
	ON_BN_CLICKED(IDC_BUTTON_DDNS, &CTestDlgDlg::OnBnClickedButtonDdns)
	ON_BN_CLICKED(IDC_BUTTON_SNMP, &CTestDlgDlg::OnBnClickedButtonSnmp)
	ON_BN_CLICKED(IDC_BUTTON_PPPOE, &CTestDlgDlg::OnBnClickedButtonPppoe)
END_MESSAGE_MAP()


// CTestDlgDlg message handlers

BOOL CTestDlgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_List_Camera.SetExtendedStyle( m_List_Camera.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	int ncol = 0;
	m_List_Camera.InsertColumn(ncol++, ("index"), 0, 50);
	m_List_Camera.InsertColumn(ncol++, ("vendor name"), 0, 100);
	m_List_Camera.InsertColumn(ncol++, ("ip address"), 0, 100);
	m_List_Camera.InsertColumn(ncol++, ("model name"), 0, 100);
	m_List_Camera.InsertColumn(ncol++, ("mac address"), 0, 100);
	m_List_Camera.InsertColumn(ncol++, ("discovery protocol"), 0, 120);
	
	m_bInitTriggerServer = true;
	SPIDER_InitTriggerServer();

	m_bInitSyslogServer = true;
	SPIDER_InitSyslogServer();

	CString strChannel = _T("");
	for (int i=0; i<4; i++) {
		strChannel.Format(_T("%d"), i+1);
		m_cbChSnapShot.InsertString(i, strChannel);
	}
	m_cbChSnapShot.SetCurSel(0);

	OnBnClickedButtonDiscovery();  //skpark in your area
	m_hThread_Polling = CreateThread(NULL, 0, ThreadProc_Polling, this, 0, &m_dwThreadID_Polling); //skpark in your area

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestDlgDlg::OnClose()
{
	this->m_stopPolling = true;
}

void CTestDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestDlgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTestDlgDlg::OnBnClickedButtonDiscovery()
{
	if(m_hThread_Discovery)
	{
		MessageBox(("Discovery is running..."));
		return;
	}


	if(WaitDlg.m_hEvent_InitDlg == NULL)
		WaitDlg.m_hEvent_InitDlg = CreateEvent(0,0,0,0);

	m_hThread_Discovery = CreateThread(NULL, 0, ThreadProc_Discovery, this, 0, &m_dwThreadID_Discovery );

	WaitDlg.DoModal();

}

DWORD CTestDlgDlg::ThreadProc_Discovery(LPVOID lpParameter)
{
	((CTestDlgDlg*)lpParameter)->StartDiscovery();

	//((CTestDlgDlg*)lpParameter)->m_dwThreadID_Discovery;

	if(((CTestDlgDlg*)lpParameter)->m_hThread_Discovery)
		CloseHandle(((CTestDlgDlg*)lpParameter)->m_hThread_Discovery);
	((CTestDlgDlg*)lpParameter)->m_hThread_Discovery = NULL;

	//skpark in your area start
	((CTestDlgDlg*)lpParameter)->GetAllCamera();
	((CTestDlgDlg*)lpParameter)->m_initDone = true;
	//skpark in your area end

	ExitThread(0x2345);
}

DWORD CTestDlgDlg::ThreadProc_Polling(LPVOID lpParameter)
{
	((CTestDlgDlg*)lpParameter)->Polling();

	//((CTestDlgDlg*)lpParameter)->m_dwThreadID_Polling;
	if (((CTestDlgDlg*)lpParameter)->m_hThread_Polling)
		CloseHandle(((CTestDlgDlg*)lpParameter)->m_hThread_Polling);
	((CTestDlgDlg*)lpParameter)->m_hThread_Polling = NULL;

	ExitThread(0x2345);
}

void CTestDlgDlg::StartDiscovery()
{
	//wait for init dlg
	WaitForSingleObject(WaitDlg.m_hEvent_InitDlg, INFINITE);

	CString sztext;

	if(m_hDiscoveryEvent == NULL)
		SPIDER_InitDiscovery(&m_hDiscoveryEvent);
	
	m_foundedCount = SPIDER_GetDiscoveryCameraCount();

	WaitDlg.SetTimer(TIMER_CLOSE, 100, NULL);


	m_List_Camera.DeleteAllItems();

	//ST_SPIDER_DISCOVERY_CAMEAR_INFO stInfo;
	for (int i = 0; i < m_foundedCount; i++)
	{
		//SPIDER_GetDiscoveryCameraInfo(i, &stInfo);
		memset(&(m_stInfo[i]), 0x00, sizeof(ST_SPIDER_DISCOVERY_CAMEAR_INFO));

		SPIDER_GetDiscoveryCameraInfo(i, &(m_stInfo[i]));

		sztext.Format(("%d"), i+1);
		m_List_Camera.InsertItem(i, sztext);


		int ncol = 1;

		sztext = m_stInfo[i].strVendorName;
		m_List_Camera.SetItemText(i, ncol++, sztext);


		sztext = m_stInfo[i].strIpAddress;
		m_List_Camera.SetItemText(i, ncol++, sztext);


		sztext = m_stInfo[i].strModelName;
		m_List_Camera.SetItemText(i, ncol++, sztext);


		sztext = m_stInfo[i].strMacAddr;
		m_List_Camera.SetItemText(i, ncol++, sztext);

		sztext = "";
		if(m_stInfo[i].nsDiscoverySupport & DISCOVERY_UPNP)
			sztext += "upnp ";
		if(m_stInfo[i].nsDiscoverySupport & DISCOVERY_ZEROCONF)
			sztext += "bonjour ";
		if(m_stInfo[i].nsDiscoverySupport & DISCOVERY_ONVIF)
			sztext += "onvif ";
		m_List_Camera.SetItemText(i, ncol++, sztext);

	}


	sztext.Format(("Total Discovered Camera Count : %d"), m_foundedCount);
	GetDlgItem(IDC_EDIT_CAMERA_INFO)->SetWindowText(sztext);
	//MessageBox(sztext);
}

// skpark in your area
void CTestDlgDlg::Polling()
{
	CString szText;
	int loop = 0;
	while (!m_stopPolling) {
		if (m_initDone) {
			for (int i = 0; i < m_foundedCount; i++) {
				if (theApp.m_allCamera[i]) {
					if (SPIDER_GetThermalRegionTemp(theApp.m_allCamera[i], &m_stTemp[i]) == E_CTRL_OK){
						CString strValid = _T("");
						CString strAlarm = _T("");
						CString strCenter = _T("");
						CString strMin = _T("");
						CString strMax = _T("");
						CString strAvg = _T("");

						strValid.Format(m_stTemp[i].ThermalFullTemp.bValid ? _T("O") : _T("X"));
						strAlarm.Format(m_stTemp[i].ThermalFullTemp.bAlarmOn ? _T("On") : _T("Off"));
						strCenter.Format(_T("%.1f"), m_stTemp[i].ThermalFullTemp.fCenterTempValue);
						strMin.Format(_T("%.1f"), m_stTemp[i].ThermalFullTemp.fMinTempValue);
						strMax.Format(_T("%.1f"), m_stTemp[i].ThermalFullTemp.fMaxTempValue);
						strAvg.Format(_T("%.1f"), m_stTemp[i].ThermalFullTemp.fAvgTempValue);

						TraceLog(("strValid=%s", strValid));
						TraceLog(("strAlarm=%s", strAlarm));
						TraceLog(("strCenter=%s", strCenter));
						TraceLog(("strMin=%s", strMin));
						TraceLog(("strMax=%s", strMax));
						TraceLog(("strAvg=%s", strAvg));

						
						szText.Format("%s\r\nValid=%s, Alarm=%s, Center=%s, Min=%s, Max=%s, Avg=%s", 
							szText, strValid, strAlarm, strCenter, strMin, strMax, strAvg);

						GetDlgItem(IDC_EDIT_CAMERA_INFO)->SetWindowText(szText);
					}
				}
			}
			if (loop == 14) {
				loop = 0;
				szText = "";
			}
			loop++;
		}
		::Sleep(10*1000);
	}
}

//skpark in your area
void CTestDlgDlg::GetAllCamera()  
{
	m_initDone = false;
	for (int i = 0; i < m_foundedCount; i++) {
		SelectOneCamera(i);
	}
	m_initDone = true;
}

void CTestDlgDlg::SelectOneCamera(int nSel)
{
	if (nSel == -1 ||  nSel >= m_foundedCount ) return;

	//ST_SPIDER_DISCOVERY_CAMEAR_INFO stInfo;
	//SPIDER_GetDiscoveryCameraInfo(nSel, &stInfo);

	char szip[100] = "";
	m_List_Camera.GetItemText(nSel, 2, szip, 50);

	if (theApp.m_allCamera[nSel])
		SPIDER_DestroyCameraHandle(theApp.m_allCamera[nSel]);
	theApp.m_allCamera[nSel] = NULL;

	HCAMERA hCamera = SPIDER_CreateCameraHandle(szip, 80, "admin", "-507263a");
	theApp.m_allCamera[nSel] = hCamera;
	if (hCamera)
	{
		CString sztext;
		long lret = E_CTRL_OK;
		long nCount = 0;

		sztext = "Camera Info of ";
		sztext += szip;
		sztext += "\r\n\r\n";


		sztext += "* Device Info ------------------\r\n";
		ST_SPIDER_DEVICE_INFO stDevice = { 0 };
		lret = SPIDER_GetDeviceInfo(hCamera, &stDevice);
		if (lret != E_CTRL_OK)
		{
			sztext += "device info : ";
			sztext += GetErrorString(lret);
			sztext += "\r\n";
		}
		else
		{
			sztext += "name : ";
			sztext += stDevice.device_name;
			sztext += "\r\n";

			sztext += "model name : ";
			sztext += stDevice.model_name;
			sztext += "\r\n";

			sztext += "serial number : ";
			sztext += stDevice.serial_number;
			sztext += "\r\n";

			sztext += "mac address : ";
			sztext += stDevice.mac_address;
			sztext += "\r\n";

			sztext += "firmware version : ";
			sztext += stDevice.firmware_version;
			sztext += "\r\n";
		}
		sztext += "\r\n";

		sztext += "* Stream Info ------------------\r\n";
		ST_SPIDER_STREAM_INFO stStream = { 0 };
		nCount = SPIDER_GetStreamCount(hCamera);

		CString szInfo;
		szInfo.Format(("Stream Count : %d\r\n"), nCount);
		sztext += szInfo;
		for (int i = 0; i < nCount; i++)
		{
			szInfo.Format(("Stream [%d] "), i + 1);
			sztext += szInfo;

			lret = SPIDER_GetStreamInfo(hCamera, i, &stStream);
			if (lret != E_CTRL_OK)
			{
				sztext += "stream info : ";
				sztext += GetErrorString(lret);
				sztext += "\r\n";
			}
			else
			{
				switch (stStream.stVideo.nsVideoCodecType)
				{
				case E_COCEC_MPEG4: sztext += "mpeg4"; break;
				case E_COCEC_MJPEG: sztext += "mjpeg"; break;
				case E_COCEC_H264: sztext += "h.264"; break;
				default: sztext += "unknown"; break;
				}

				szInfo.Format(("( %d x %d )"), stStream.stVideo.nWidth, stStream.stVideo.nHeight);
				sztext += szInfo;

				char szurl[300] = "";
				SPIDER_GetStreamingURL(hCamera, i, szurl);

				sztext += " stream url : ";
				sztext += szurl;
			}
			sztext += "\r\n";
		}
		sztext += "\r\n";

		sztext += "* Time Info ------------------\r\n";
		ST_SPIDER_TIME_INFO stTime = { 0 };
		lret = SPIDER_GetTimeInfo(hCamera, &stTime);
		if (lret != E_CTRL_OK)
		{
			sztext += "time info : ";
			sztext += GetErrorString(lret);
			sztext += "\r\n";
		}
		else
		{
			sztext += "local time : ";
			sztext += stTime.strLocalTime;
			sztext += "\r\n";

			sztext += "time zone : ";
			sztext += stTime.strTimeZone;
			sztext += "\r\n";
		}
		sztext += "\r\n";



		sztext += "* Custom Info ------------------\r\n";
		ENUM_SPIDER_CUSTOM_ASPECTRATIO eAspectRatio;
		lret = SPIDER_GetCustomAspectRatio(hCamera, &eAspectRatio);
		if (lret != E_CTRL_OK)
		{
			sztext += "aspect ratio : ";
			sztext += GetErrorString(lret);
			sztext += "\r\n";
		}
		else
		{
			sztext += "aspect ratio : ";
			switch (eAspectRatio)
			{
			case E_ASPECT_RAIO_CROPPING: sztext += "cropping"; break;
			case E_ASPECT_RAIO_SQUEEZING: sztext += "squeezing"; break;
			default: sztext += "unknown"; break;
			}
			sztext += "\r\n";
		}
		sztext += "\r\n";


		ENUM_SPIDER_CUSTOM_LINKSPEED eLinkSpeed;
		lret = SPIDER_GetCustomLinkSpeed(hCamera, &eLinkSpeed);
		if (lret != E_CTRL_OK)
		{
			sztext += "link speed : ";
			sztext += GetErrorString(lret);
			sztext += "\r\n";
		}
		else
		{
			sztext += "link speed : ";
			switch (eLinkSpeed)
			{
			case E_LINK_SPEED_AUTO: sztext += "auto Nego"; break;
			case E_LINK_SPEED_FULL100: sztext += "100M full"; break;
			case E_LINK_SPEED_HALF100: sztext += "100M half"; break;
			case E_LINK_SPEED_FULL10: sztext += "10M full"; break;
			case E_LINK_SPEED_HALF10: sztext += "10M half"; break;
			default: sztext += "unknown"; break;
			}
			sztext += "\r\n";
		}
		sztext += "\r\n";

		bool bEnable;
		lret = SPIDER_GetCustomSuppressColorNightMode(hCamera, &bEnable);
		if (lret != E_CTRL_OK)
		{
			sztext += "suppress color night mode : ";
			sztext += GetErrorString(lret);
			sztext += "\r\n";
		}
		else
		{
			sztext += "suppress color night mode : ";
			sztext += bEnable ? "enable" : "disable";
			sztext += "\r\n";
		}
		sztext += "\r\n";


		sztext += "* Custom Trigger Info ------------------\r\n";
		ST_SPIDER_CUSTOM_TRIGGER_INFO stCustomTrigger = { 0 };
		lret = SPIDER_GetCustomTriggerInfo(hCamera, &stCustomTrigger);
		if (lret != E_CTRL_OK)
		{
			sztext += GetErrorString(lret);
			sztext += "\r\n";
		}
		else
		{
			sztext += "Source : ";
			if (stCustomTrigger.nsSource == 0)
				sztext += "software";
			else if (stCustomTrigger.nsSource == 1)
				sztext += "hardware";
			else if (stCustomTrigger.nsSource == 2)
				sztext += "periodic";
			else if (stCustomTrigger.nsSource == 3)
				sztext += "filterCtrl";
			else
				sztext += "NA";
			sztext += "\r\n";


			szInfo.Format(("%d"), stCustomTrigger.nDelay);
			sztext += "Delay : ";
			sztext += szInfo;
			sztext += "\r\n";

			sztext += "Polarity : ";
			if (stCustomTrigger.nsPolarity == 0)
				sztext += "high";
			else if (stCustomTrigger.nsPolarity == 1)
				sztext += "low";
			else
				sztext += "NA";
			sztext += "\r\n";

			szInfo.Format(("%d"), stCustomTrigger.nsTriggerNoiseFilter);
			sztext += "Noise Filter : ";
			sztext += szInfo;
			sztext += "\r\n";

			sztext += "Server On/Off : ";
			if (stCustomTrigger.nsOnOff == 0)
				sztext += "Off";
			else if (stCustomTrigger.nsOnOff == 1)
				sztext += "On";
			else
				sztext += "NA";
			sztext += "\r\n";

			sztext += "Server Addr : ";
			sztext += stCustomTrigger.strIpAddr;
			sztext += "\r\n";

			szInfo.Format(("%d"), stCustomTrigger.nsPortNo);
			sztext += "Server Port : ";
			sztext += szInfo;
			sztext += "\r\n";

			//szInfo.Format(("%d"), stCustomTrigger.nsParameter);
			//sztext += "Parameter Number : ";
			//sztext += szInfo; 
			//sztext += "\r\n";

			//compare trigger server ip with my computer ip

			if (stCustomTrigger.strIpAddr)
			{
				CString szIPList;
				static CString szMyComIPList;
				static char m_vHostIP[10][50] = { 0 };
				static int nMyComIPCount = 0;
				if (szMyComIPList.GetLength() == 0)
				{
#pragma comment(lib, "IPHlpAPI.lib")
					//get ip list of this computer.
					PIP_ADAPTER_INFO pAdapterInfo = (IP_ADAPTER_INFO *)malloc(sizeof(IP_ADAPTER_INFO));
					ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
					if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW)
					{
						free(pAdapterInfo);
						pAdapterInfo = (IP_ADAPTER_INFO *)malloc(ulOutBufLen);
					}

					int nIndex = 0;
					DWORD dwRetVal = 0;
					PIP_ADAPTER_INFO pAdapter = NULL;
					if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR)
					{
						pAdapter = pAdapterInfo;
						while (pAdapter)
						{
							CString szip;
							szip.Format(("[%d] %s\r\n"), nIndex++, pAdapter->IpAddressList.IpAddress.String);
							szIPList += szip;
							strcpy(m_vHostIP[nMyComIPCount], pAdapter->IpAddressList.IpAddress.String);
							nMyComIPCount++;

							pAdapter = pAdapter->Next;
						}
					}

					free(pAdapterInfo);

					if (szIPList.GetLength())
					{
						szMyComIPList = "My Computer IP Address is...\r\n\r\n";
						szMyComIPList += szIPList;
					}
					else
					{
						szMyComIPList = "Failed to get IP Address on this system.\r\n\r\n";
					}
				}

				int nFindIP = 0;
				while (nFindIP < nMyComIPCount)
				{
					if (strcmp(stCustomTrigger.strIpAddr, m_vHostIP[nFindIP]) == 0)
					{
						break;
					}

					nFindIP++;
				}

				if (nFindIP < nMyComIPCount)
				{
					if (m_hTrigger == NULL)
					{
						m_hTrigger = SPIDER_StartTriggerServer(GetSafeHwnd(), stCustomTrigger.nsPortNo);
					}
				}
			}
		}
		sztext += "\r\n";



		ST_SPIDER_CUSTOM_TRIGGER_PARAM_INFO stParam = { 0 };
		nCount = SPIDER_GetCustomTriggerParamCount(hCamera);

		szInfo.Format(("Param Count : %d\r\n"), nCount);
		sztext += szInfo;
		for (int i = 0; i < nCount; i++)
		{
			szInfo.Format(("Param [%d] "), i + 1);
			sztext += szInfo;

			lret = SPIDER_GetCustomTriggerParamInfo(hCamera, i, &stParam);
			if (lret != E_CTRL_OK)
			{
				sztext += GetErrorString(lret);
				sztext += "\r\n";
			}
			else
			{
				szInfo.Format(("Gain : %d"), stParam.nGain);
				sztext += szInfo;
				sztext += "\r\n";

				szInfo.Format(("Shutter : %d"), stParam.nShutter);
				sztext += szInfo;
				sztext += "\r\n";

				szInfo.Format(("Increment : %d"), stParam.nsIncrement);
				sztext += szInfo;
				sztext += "\r\n";
			}
			sztext += "\r\n";
		}
		sztext += "\r\n";


		GetDlgItem(IDC_EDIT_CAMERA_INFO)->SetWindowText(sztext);
	}
	else
	{
		GetDlgItem(IDC_EDIT_CAMERA_INFO)->SetWindowText(("Failed to create camera handle"));
	}


}


void CTestDlgDlg::OnNMClickListCamera(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE*>(pNMHDR);
	// TODO: Add your control notification handler code here

	int nSel = m_List_Camera.GetSelectionMark();
	if (nSel == -1) return;
	

		//ST_SPIDER_DISCOVERY_CAMEAR_INFO stInfo;
		//SPIDER_GetDiscoveryCameraInfo(nSel, &stInfo);

		
		char szip[100] = "";
		m_List_Camera.GetItemText(nSel, 2, szip, 50);		

		if(theApp.m_hSelectCamera)
			SPIDER_DestroyCameraHandle(theApp.m_hSelectCamera);
		theApp.m_hSelectCamera = NULL;

		theApp.m_hSelectCamera = theApp.m_allCamera[nSel];
		/*
		HCAMERA hCamera = SPIDER_CreateCameraHandle(szip, 80, "admin", "-507263a");
		theApp.m_hSelectCamera = hCamera;
		if(hCamera)
		{
			CString sztext;
			long lret = E_CTRL_OK;
			long nCount = 0;

			sztext = "Camera Info of ";
			sztext += szip;
			sztext += "\r\n\r\n";


			sztext += "* Device Info ------------------\r\n";
			ST_SPIDER_DEVICE_INFO stDevice = {0};
			lret = SPIDER_GetDeviceInfo(hCamera, &stDevice);
			if(lret != E_CTRL_OK)
			{
				sztext += "device info : ";
				sztext += GetErrorString(lret);
				sztext += "\r\n";
			}
			else
			{
				sztext += "name : ";
				sztext += stDevice.device_name;
				sztext += "\r\n";

				sztext += "model name : ";
				sztext += stDevice.model_name;
				sztext += "\r\n";

				sztext += "serial number : ";
				sztext += stDevice.serial_number;
				sztext += "\r\n";

				sztext += "mac address : ";
				sztext += stDevice.mac_address;
				sztext += "\r\n";

				sztext += "firmware version : ";
				sztext += stDevice.firmware_version;
				sztext += "\r\n";
			}
			sztext += "\r\n";

			sztext += "* Stream Info ------------------\r\n";
			ST_SPIDER_STREAM_INFO stStream = {0};
			nCount = SPIDER_GetStreamCount(hCamera);

			CString szInfo;
			szInfo.Format(("Stream Count : %d\r\n"), nCount);
			sztext += szInfo;
			for(int i = 0; i < nCount; i++)
			{
				szInfo.Format(("Stream [%d] "), i+1);
				sztext += szInfo;

				lret = SPIDER_GetStreamInfo(hCamera, i, &stStream);
				if(lret != E_CTRL_OK)
				{
					sztext += "stream info : ";
					sztext += GetErrorString(lret);
					sztext += "\r\n";
				}
				else
				{
					switch(stStream.stVideo.nsVideoCodecType)
					{
					case E_COCEC_MPEG4: sztext += "mpeg4"; break;
					case E_COCEC_MJPEG: sztext += "mjpeg"; break;
					case E_COCEC_H264: sztext += "h.264"; break;
					default: sztext += "unknown"; break;
					}

					szInfo.Format(("( %d x %d )"), stStream.stVideo.nWidth, stStream.stVideo.nHeight);
					sztext += szInfo;

					char szurl[300] = "";
					SPIDER_GetStreamingURL(hCamera, i, szurl);

					sztext += " stream url : ";
					sztext += szurl;
				}
				sztext += "\r\n";
			}
			sztext += "\r\n";

			sztext += "* Time Info ------------------\r\n";
			ST_SPIDER_TIME_INFO stTime = {0};
			lret = SPIDER_GetTimeInfo(hCamera, &stTime);
			if(lret != E_CTRL_OK)
			{
				sztext += "time info : ";
				sztext += GetErrorString(lret);
				sztext += "\r\n";
			}
			else
			{
				sztext += "local time : ";
				sztext += stTime.strLocalTime;
				sztext += "\r\n";

				sztext += "time zone : ";
				sztext += stTime.strTimeZone;
				sztext += "\r\n";
			}
			sztext += "\r\n";



			sztext += "* Custom Info ------------------\r\n";
			ENUM_SPIDER_CUSTOM_ASPECTRATIO eAspectRatio;
			lret = SPIDER_GetCustomAspectRatio(hCamera, &eAspectRatio);
			if(lret != E_CTRL_OK)
			{
				sztext += "aspect ratio : ";
				sztext += GetErrorString(lret);
				sztext += "\r\n";
			}
			else
			{
				sztext += "aspect ratio : ";
				switch(eAspectRatio)
				{
				case E_ASPECT_RAIO_CROPPING: sztext += "cropping"; break;
				case E_ASPECT_RAIO_SQUEEZING: sztext += "squeezing"; break;
				default: sztext += "unknown"; break;
				}
				sztext += "\r\n";
			}
			sztext += "\r\n";


			ENUM_SPIDER_CUSTOM_LINKSPEED eLinkSpeed;
			lret = SPIDER_GetCustomLinkSpeed(hCamera, &eLinkSpeed);
			if(lret != E_CTRL_OK)
			{
				sztext += "link speed : ";
				sztext += GetErrorString(lret);
				sztext += "\r\n";
			}
			else
			{
				sztext += "link speed : ";
				switch(eLinkSpeed)
				{
				case E_LINK_SPEED_AUTO: sztext += "auto Nego"; break;
				case E_LINK_SPEED_FULL100: sztext += "100M full"; break;
				case E_LINK_SPEED_HALF100: sztext += "100M half"; break;
				case E_LINK_SPEED_FULL10: sztext += "10M full"; break;
				case E_LINK_SPEED_HALF10: sztext += "10M half"; break;
				default: sztext += "unknown"; break;
				}
				sztext += "\r\n";
			}
			sztext += "\r\n";

			bool bEnable;
			lret = SPIDER_GetCustomSuppressColorNightMode(hCamera, &bEnable);
			if(lret != E_CTRL_OK)
			{
				sztext += "suppress color night mode : ";
				sztext += GetErrorString(lret);
				sztext += "\r\n";
			}
			else
			{
				sztext += "suppress color night mode : ";
				sztext += bEnable?"enable":"disable";
				sztext += "\r\n";
			}
			sztext += "\r\n";


			sztext += "* Custom Trigger Info ------------------\r\n";
			ST_SPIDER_CUSTOM_TRIGGER_INFO stCustomTrigger = {0};
			lret = SPIDER_GetCustomTriggerInfo(hCamera, &stCustomTrigger);
			if(lret != E_CTRL_OK)
			{
				sztext += GetErrorString(lret);
				sztext += "\r\n";
			}
			else
			{
				sztext += "Source : ";
				if(stCustomTrigger.nsSource == 0)
					sztext += "software";
				else if(stCustomTrigger.nsSource == 1)
					sztext += "hardware";
				else if(stCustomTrigger.nsSource == 2)
					sztext += "periodic";
				else if(stCustomTrigger.nsSource == 3)
					sztext += "filterCtrl";
				else
					sztext += "NA";
				sztext += "\r\n";


				szInfo.Format(("%d"), stCustomTrigger.nDelay);
				sztext += "Delay : ";
				sztext += szInfo; 
				sztext += "\r\n";

				sztext += "Polarity : ";
				if(stCustomTrigger.nsPolarity == 0)
					sztext += "high";
				else if(stCustomTrigger.nsPolarity == 1)
					sztext += "low";
				else 
					sztext += "NA";
				sztext += "\r\n";

				szInfo.Format(("%d"), stCustomTrigger.nsTriggerNoiseFilter);
				sztext += "Noise Filter : ";
				sztext += szInfo; 
				sztext += "\r\n";

				sztext += "Server On/Off : ";
				if(stCustomTrigger.nsOnOff == 0)
					sztext += "Off";
				else if(stCustomTrigger.nsOnOff == 1)
					sztext += "On";
				else
					sztext += "NA";
				sztext += "\r\n";

				sztext += "Server Addr : ";
				sztext += stCustomTrigger.strIpAddr;
				sztext += "\r\n";

				szInfo.Format(("%d"), stCustomTrigger.nsPortNo);
				sztext += "Server Port : ";
				sztext += szInfo; 
				sztext += "\r\n";

				//szInfo.Format(("%d"), stCustomTrigger.nsParameter);
				//sztext += "Parameter Number : ";
				//sztext += szInfo; 
				//sztext += "\r\n";

				//compare trigger server ip with my computer ip

				if(stCustomTrigger.strIpAddr)
				{
					CString szIPList;
					static CString szMyComIPList;
					static char m_vHostIP[10][50] = {0};
					static int nMyComIPCount = 0;
					if(szMyComIPList.GetLength() == 0)
					{
#pragma comment(lib, "IPHlpAPI.lib")
						//get ip list of this computer.
						PIP_ADAPTER_INFO pAdapterInfo = (IP_ADAPTER_INFO *) malloc( sizeof(IP_ADAPTER_INFO) );
						ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
						if (GetAdaptersInfo( pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) 
						{
							free(pAdapterInfo);
							pAdapterInfo = (IP_ADAPTER_INFO *) malloc (ulOutBufLen); 
						}			

						int nIndex = 0;
						DWORD dwRetVal = 0;
						PIP_ADAPTER_INFO pAdapter = NULL;
						if ((dwRetVal = GetAdaptersInfo( pAdapterInfo, &ulOutBufLen)) == NO_ERROR) 
						{				
							pAdapter = pAdapterInfo;
							while (pAdapter) 
							{		
								CString szip;
								szip.Format(("[%d] %s\r\n"), nIndex++, pAdapter->IpAddressList.IpAddress.String);
								szIPList += szip;
								strcpy(m_vHostIP[nMyComIPCount], pAdapter->IpAddressList.IpAddress.String);
								nMyComIPCount++;

								pAdapter = pAdapter->Next;
							}
						}

						free(pAdapterInfo);	

						if(szIPList.GetLength())
						{
							szMyComIPList = "My Computer IP Address is...\r\n\r\n";
							szMyComIPList += szIPList;
						}
						else
						{
							szMyComIPList = "Failed to get IP Address on this system.\r\n\r\n";
						}
					}

					int nFindIP = 0;
					while(nFindIP < nMyComIPCount)
					{
						if(strcmp(stCustomTrigger.strIpAddr, m_vHostIP[nFindIP]) == 0)
						{
							break;
						}

						nFindIP++;
					}

					if(nFindIP < nMyComIPCount)
					{
						if(m_hTrigger == NULL)
						{
							m_hTrigger = SPIDER_StartTriggerServer(GetSafeHwnd(), stCustomTrigger.nsPortNo);
						}
					}
				}
			}
			sztext += "\r\n";

			

			ST_SPIDER_CUSTOM_TRIGGER_PARAM_INFO stParam = {0};
			nCount = SPIDER_GetCustomTriggerParamCount(hCamera);

			szInfo.Format(("Param Count : %d\r\n"), nCount);
			sztext += szInfo;
			for(int i = 0; i < nCount; i++)
			{
				szInfo.Format(("Param [%d] "), i+1);
				sztext += szInfo;

				lret = SPIDER_GetCustomTriggerParamInfo(hCamera, i, &stParam);
				if(lret != E_CTRL_OK)
				{
					sztext += GetErrorString(lret);
					sztext += "\r\n";
				}
				else
				{
					szInfo.Format(("Gain : %d"), stParam.nGain);
					sztext += szInfo; 
					sztext += "\r\n";

					szInfo.Format(("Shutter : %d"), stParam.nShutter);
					sztext += szInfo; 
					sztext += "\r\n";

					szInfo.Format(("Increment : %d"), stParam.nsIncrement);
					sztext += szInfo; 
					sztext += "\r\n";
				}
				sztext += "\r\n";
			}
			sztext += "\r\n";

			
			GetDlgItem(IDC_EDIT_CAMERA_INFO)->SetWindowText(sztext);
		}
		else
		{
			GetDlgItem(IDC_EDIT_CAMERA_INFO)->SetWindowText(("Failed to create camera handle"));
		}
	
	*/
	*pResult = 0;
}

void CTestDlgDlg::OnBnClickedButtonDevice()
{
	// TODO: Add your control notification handler code here
	if(theApp.m_hSelectCamera == NULL)
		return;

	CDeviceInfoDlg dlg;
	dlg.DoModal();
}

void CTestDlgDlg::OnBnClickedButtonFeature()
{
	// TODO: Add your control notification handler code here
	if(theApp.m_hSelectCamera == NULL)
		return;

	CFeatureInfoDlg dlg;
	dlg.DoModal();
}

void CTestDlgDlg::OnBnClickedButtonOverlayText()
{
	// TODO: Add your control notification handler code here
	if(theApp.m_hSelectCamera == NULL)
		return;

	COverlayTextInfoDlg dlg;
	dlg.DoModal();
}

void CTestDlgDlg::OnBnClickedButtonMotion()
{
	// TODO: Add your control notification handler code here
	if(theApp.m_hSelectCamera == NULL)
		return;

	CMotionInfoDlg dlg;
	dlg.DoModal();
}

void CTestDlgDlg::OnBnClickedButtonPrivacyMask()
{
	// TODO: Add your control notification handler code here
	if(theApp.m_hSelectCamera == NULL)
		return;

	CPrivacyMaskInfoDlg dlg;
	dlg.DoModal();
}

void CTestDlgDlg::OnBnClickedButtonStream()
{
	// TODO: Add your control notification handler code here
	if(theApp.m_hSelectCamera == NULL)
		return;

	CStreamInfoDlg dlg;
	dlg.DoModal();
}

void CTestDlgDlg::OnBnClickedButtonTime()
{
	// TODO: Add your control notification handler code here
	if(theApp.m_hSelectCamera == NULL)
		return;

	CTimeInfoDlg dlg;
	dlg.DoModal();
}

void CTestDlgDlg::OnBnClickedButtonUser()
{
	// TODO: Add your control notification handler code here
	if(theApp.m_hSelectCamera == NULL)
		return;

	CUserInfoDlg dlg;
	dlg.DoModal();
}

void CTestDlgDlg::OnBnClickedButtonNetworkIpaddress()
{
	// TODO: Add your control notification handler code here
	if(theApp.m_hSelectCamera == NULL)
		return;

	CNetworkIPAddrInfoDlg dlg;
	dlg.DoModal();
}

void CTestDlgDlg::OnBnClickedButtonNetworkIpFilter()
{
	// TODO: Add your control notification handler code here
	if(theApp.m_hSelectCamera == NULL)
		return;

	CNetworkIPFilterInfoDlg dlg;
	dlg.DoModal();
}

void CTestDlgDlg::OnBnClickedButtonNotifyMailing()
{
	// TODO: Add your control notification handler code here
	if(theApp.m_hSelectCamera == NULL)
		return;

	CNotifyMailingInfoDlg dlg;
	dlg.DoModal();
}

void CTestDlgDlg::OnBnClickedButtonEventTrigger()
{
	// TODO: Add your control notification handler code here
	if(theApp.m_hSelectCamera == NULL)
		return;

	CEventTriggerInfoDlg dlg;
	dlg.DoModal();
}

void CTestDlgDlg::OnBnClickedButtonEventSchedule()
{
	// TODO: Add your control notification handler code here
	if(theApp.m_hSelectCamera == NULL)
		return;

	CEventScheduleInfoDlg dlg;
	dlg.DoModal();
}

void CTestDlgDlg::OnBnClickedButtonCustomTrigger()
{
	// TODO: Add your control notification handler code here
	if(theApp.m_hSelectCamera == NULL)
		return;

	CCustomTriggerInfoDlg dlg;
	dlg.DoModal();
}

void CTestDlgDlg::OnBnClickedButtonCustomStrobe()
{
	// TODO: Add your control notification handler code here
	if(theApp.m_hSelectCamera == NULL)
		return;

	CCustomStrobeInfoDlg dlg;
	dlg.DoModal();
}

void CTestDlgDlg::OnBnClickedButtonStorage()
{
	CString sztext;
	long lcount = SPIDER_GetStorageVolumeCount(theApp.m_hSelectCamera);

	sztext.Format(("Storage Volume Count : %d\r\n"), lcount);

	if(lcount == 0)
	{
		GetDlgItem(IDC_EDIT_CAMERA_INFO)->SetWindowText(sztext);
		return;
	}

	ST_SPIDER_STORAGE_VOLUME_INFO stInfo;
	CString szVolume;
	long lret = 0;
	for(int nStorage = 0; nStorage < lcount; nStorage++)
	{
		lret = SPIDER_GetStorageVolumeInfo(theApp.m_hSelectCamera, nStorage, &stInfo);
		if(lret != E_CTRL_OK)
		{
			szVolume.Format(("[%d] Failed to get info\r\n"), nStorage+1);
			sztext += szVolume;
			//MessageBox(GetErrorString(lret), ("Fail"));
		}
		else
		{
			CString szName, szType, szDesc;
			szName = stInfo.strVolumeName;
			szType = stInfo.strStorageType;
			szDesc = stInfo.strStorageDesc;
			szVolume.Format(("[%d] Name : %s, Type : %s, Desc : %s\r\n"), nStorage+1, szName, szType, szDesc);
			sztext += szVolume;
		}
	}

	GetDlgItem(IDC_EDIT_CAMERA_INFO)->SetWindowText(sztext);
}

void CTestDlgDlg::OnBnClickedButtonCustomStorage()
{
	CString sztext;

	ST_SPIDER_CUSTOM_STORAGE_VOLUME stInfo;
	CString szVolume;
	long lret = 0;
	lret = SPIDER_GetCustomStorageVolume(theApp.m_hSelectCamera, &stInfo);
	if(lret != E_CTRL_OK)
	{
		szVolume.Format(("Failed to get info\r\n"));
		sztext += szVolume;
		//MessageBox(GetErrorString(lret), ("Fail"));
	}
	else
	{
		CString szStatus;
		switch(stInfo.nsStatus)
		{
		case E_STORAGE_STATUS_OK: szStatus = "SD_OK"; break;
		case E_STORAGE_STATUS_DETACH: szStatus = "detached"; break;
		case E_STORAGE_STATUS_FULL: szStatus = "storageFull"; break;
		case E_STORAGE_STATUS_PROTECT: szStatus = "writeProtected"; break;
		case E_STORAGE_STATUS_UNMOUNT: szStatus = "unMounted"; break;
		}
		szVolume.Format(("Status : %s\r\nCapacity %.2f MB, Free %.2f MB, Used %.2f MB (%.2f%%)\r\n"), szStatus, stInfo.fCapacity, stInfo.fFreeSize, stInfo.fUsedSize, stInfo.fUsedPercentage);
		sztext += szVolume;
	}


	sztext += "\r\n";


	ST_SPIDER_CUSTOM_STORAGE_CTRL stCtrl;
	lret = SPIDER_GetCustomStorageCtrl(theApp.m_hSelectCamera, &stCtrl);
	if(lret != E_CTRL_OK)
	{
		szVolume.Format(("Failed to get info\r\n"));
		sztext += szVolume;
		//MessageBox(GetErrorString(lret), ("Fail"));
	}
	else
	{
		CString szPrefix;
		szPrefix = stCtrl.strPrefix;
		szVolume.Format(("Prefix : %s\r\nCyclic : %s\r\nRecording : %s\r\nAudio Recording : %s\r\nSave Time (5 ~ 300) : %d (seconds)\r\n"),
			szPrefix, 
			stCtrl.bCyclicEnabled? ("Enable") : ("Disable"), 
			stCtrl.bRecord? ("On") : ("Off"),  
			stCtrl.bAudioEnabled? ("On") : ("Off"), 
			stCtrl.nSaveTime);
		sztext += szVolume;
	}

	GetDlgItem(IDC_EDIT_CAMERA_INFO)->SetWindowText(sztext);
}

void CTestDlgDlg::OnBnClickedButtonCustomCtrl()
{
	if(theApp.m_hSelectCamera == NULL)
	{
		MessageBox(("Select camera to setup custom ctrl info."));
		return;
	}

	CCustomCtrlDlg dlg;
	dlg.DoModal();
}


LRESULT CTestDlgDlg::OnTriggerData(WPARAM wParam, LPARAM lParam )
{
	char szCameraIP[30] = "";
	char szFileName[MAX_PATH] = "";
	DWORD dwFileSize = 0;

	HTRIGGER hTrigger = (HTRIGGER)wParam;
	if(hTrigger)
	{
		switch(lParam)
		{
		case E_SERVER_RECVDATA:
			{
				SPIDER_GetTriggerImage(hTrigger, szCameraIP, szFileName, (unsigned int*)&dwFileSize, NULL);
				BYTE* pSaveFile = new BYTE[dwFileSize];
				if(pSaveFile)
				{
					SPIDER_GetTriggerImage(hTrigger, szCameraIP, szFileName, (unsigned int*)&dwFileSize, pSaveFile);
					TRACE("Save Trigger File %s %s\r\n", szCameraIP, szFileName);

					CFile file;
					CString cName;
					cName = gszCurDir;
					cName += szCameraIP;
					cName += "_";
					cName += szFileName;
					file.Open(cName, file.modeCreate|file.modeWrite);
					file.Write(pSaveFile, dwFileSize);
					file.Close();


					//if trigger data is yuv format, save as bitmap
					if(strstr(szFileName, ".yuv"))
					{
						char* pszPos = strstr(szFileName, "Cap");
						if(pszPos)
						{
							int width = 0;
							int height = 0;
							sscanf(pszPos, "Cap%dx%d", &width, &height);
							if(width && height)
							{
								DWORD dwRGBLen = width*height*3;
								BYTE* pRGB = new BYTE[dwRGBLen];
								if(pRGB)
								{
									if(E_CTRL_OK == SPIDER_ConvertYUV420ToRGB24(pSaveFile, dwFileSize, width, height, pRGB))
									{
										cName += ".bmp";

										BITMAPFILEHEADER	fHeader = {0};
										BITMAPINFOHEADER	InfoHeader = {0};

										fHeader.bfType = ((WORD)('M'<<8) | 'B');
										fHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
										fHeader.bfSize = dwRGBLen + fHeader.bfOffBits;

										InfoHeader.biSize = sizeof(BITMAPINFOHEADER);
										InfoHeader.biWidth = width;
										InfoHeader.biHeight = height;
										InfoHeader.biPlanes = 1;
										InfoHeader.biBitCount = 24;
										InfoHeader.biCompression = BI_RGB;
										InfoHeader.biSizeImage = dwRGBLen;

										file.Open(cName, file.modeCreate|file.modeWrite);
										file.Write(&fHeader, sizeof(BITMAPFILEHEADER));
										file.Write(&InfoHeader, sizeof(BITMAPINFOHEADER));
										file.Write(pRGB, dwRGBLen);

										file.Close();
									}
									delete [] pRGB;
								}
							}
						}
					}


					delete [] pSaveFile;
				}
			}
			break;
		case E_SERVER_CLOSED:
		case E_SERVER_FAIL_CREATE_SOCKET:
		case E_SERVER_FAIL_OPEN_PORT:
		case E_SERVER_FAIL_START:
			{
				int nPort = 0;
				SPIDER_GetTriggerPortNumber(hTrigger, &nPort);
				TRACE("close trigger server %d\r\n", nPort);

				SPIDER_StopTriggerServer(hTrigger);

				if(hTrigger == m_hTrigger)
				{					
					m_hTrigger = NULL;
				}
			}
			break;
		}
	}
	return 0;
}

LRESULT CTestDlgDlg::OnSyslogData(WPARAM wParam, LPARAM lParam )
{
	char szCameraIP[30] = "";
	ENUM_SYSLOG_FACILITY fac;
	ENUM_SYSLOG_SEVERITY svr;
	DWORD msglen = 0;
	char* pszMsg = NULL;

	HSYSLOG hSyslog = (HSYSLOG)wParam;
	if(hSyslog)
	{
	switch(lParam)
	{
	case E_SERVER_RECVDATA:
		{
			SPIDER_GetSyslogData(hSyslog, szCameraIP, &fac, &svr, (unsigned int*)&msglen, &pszMsg);	//pszMsg is valid in OnSyslogData() only.
			TRACE("syslog : %s %s\r\n", szCameraIP, pszMsg);
		}
		break;
	case E_SERVER_CLOSED:
	case E_SERVER_FAIL_CREATE_SOCKET:
	case E_SERVER_FAIL_OPEN_PORT:
	case E_SERVER_FAIL_START:
		{
			int nPort = 0;
			SPIDER_GetSyslogPortNumber(hSyslog, &nPort);
			TRACE("close syslog server %d\r\n", nPort);

			SPIDER_StopSyslogServer(hSyslog);

			if(hSyslog == m_hSyslog)
			{					
				m_hSyslog = NULL;
			}
		}
		break;
	}
	}
	return 0;
}

void CTestDlgDlg::OnBnClickedButtonStreaming()
{
	if(m_StreamingDlg.m_hStream)
	{
		if(IDYES != MessageBox(("Stop Streaming?"), ("Streaming"), MB_YESNO))
			return;

		m_StreamingDlg.StopStreaming();

		if(m_StreamingDlg.GetSafeHwnd())
			m_StreamingDlg.EndDialog(IDOK);

		GetDlgItem(IDC_BUTTON_STREAMING)->SetWindowText(("화면 시작"));
		return;
	}


	if(theApp.m_hSelectCamera == NULL)
	{
		MessageBox(("Select camera to play stream"));
		return;
	}

	int nChannelIndex = 0;

	char rtspurl[500] = "";
	SPIDER_GetStreamingURL(theApp.m_hSelectCamera, nChannelIndex, rtspurl);

	if(strlen(rtspurl) == 0)
	{
		MessageBox(("Failed to get url address."));
		return;
	}


	if (m_StreamingDlg.GetSafeHwnd() == NULL) {
		m_StreamingDlg.Create(CStreamingDlg::IDD, this);
	}
	m_StreamingDlg.ShowWindow(SW_SHOW);

	if(false == m_StreamingDlg.StartStreaming(rtspurl))
	{
		m_StreamingDlg.StopStreaming();
		m_StreamingDlg.EndDialog(IDOK);

		MessageBox(("Failed to start streaming."));
	}
	else
	{
		GetDlgItem(IDC_BUTTON_STREAMING)->SetWindowText(("화면 종료"));
	}
}


void CTestDlgDlg::OnBnClickedButtonReboot()
{
	if(theApp.m_hSelectCamera == NULL)
	{
		MessageBox(("Select camera to reboot."));
		return;
	}

	int nSel = m_List_Camera.GetSelectionMark();
	if(nSel != -1)
	{
		char szaddr[100] = ("");
		m_List_Camera.GetItemText(nSel, 2, szaddr, 50);

		CString msg;
		msg.Format(("Reboot Camera %s ?"), szaddr);
		if(IDYES != MessageBox(msg, ("Reboot"), MB_YESNO))
			return;

		long lret = SPIDER_Reboot(theApp.m_hSelectCamera);
		if(lret != E_CTRL_OK)
		{
			MessageBox(GetErrorString(lret), ("Failed to reboot."));
		}
		else
		{
			MessageBox(("Reboot success. \r\n\r\nCamera will be accessable after complete to reboot."));
		}
	}
}



void CTestDlgDlg::OnBnClickedButtonExport()
{
	if(theApp.m_hSelectCamera == NULL)
	{
		MessageBox(("Select camera to export configuration."));
		return;
	}

	int nSel = m_List_Camera.GetSelectionMark();
	if(nSel != -1)
	{
		char szaddr[100] = ("");
		m_List_Camera.GetItemText(nSel, 2, szaddr, 50);

		CString msg;
		msg.Format(("Export Config of Camera %s ?"), szaddr);
		if(IDYES != MessageBox(msg, ("Export"), MB_YESNO))
			return;

		BYTE* pFileData = new BYTE[1024 * 30];
		if(pFileData == NULL)
			return;

		int nFileLen = 0;
		long lret = SPIDER_ExportConfig(theApp.m_hSelectCamera, &nFileLen, pFileData);
		if(lret != E_CTRL_OK)
		{
			MessageBox(GetErrorString(lret), ("Failed to export."));
		}
		else
		{
			//save file data... 
			CString filename;
			filename += szaddr;
			filename += "_cfg.dat";
			CFileDialog FileDlg(FALSE, ("*.*"), filename, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, ("*.*(*.*)|*.*||"));//OFN_HIDEREADONLY|
			if(IDOK == FileDlg.DoModal())
			{
				filename = FileDlg.GetPathName();

				CFile file;
				file.Open(filename, file.modeCreate|file.modeWrite);
				file.Write(pFileData, nFileLen);
				file.Close();

				msg = ("Success to export : ");
				msg += filename;
				MessageBox(msg);
			}
		}
		delete [] pFileData;
	}
}



void CTestDlgDlg::OnBnClickedButtonImport()
{
	if(theApp.m_hSelectCamera == NULL)
	{
		MessageBox(("Select camera to be imported configuration."));
		return;
	}

	int nSel = m_List_Camera.GetSelectionMark();
	if(nSel != -1)
	{
		char szaddr[100] = ("");
		m_List_Camera.GetItemText(nSel, 2, szaddr, 50);



		CString filename;

		CFileDialog FileDlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, ("cfg file (*.*)|*.*||"));
		int nRet = FileDlg.DoModal();
		if(IDOK != nRet)
			return;
		
		filename = FileDlg.GetPathName();
		
		CFile file;
		if(false == file.Open(filename, file.modeRead))
		{
			CString msg;
			msg.Format(("The file is not exist. : %s"), filename);

			MessageBox(msg);
			return;
		}

		CString msg;
		msg.Format(("Import the cfg file below into camera %s?\r\n\r\n%s"), szaddr, filename);
		if(IDYES != MessageBox(msg, ("Import config"), MB_YESNO))
			return;

		int nFileLen = (int)file.GetLength();
		BYTE* pFileData = new BYTE[nFileLen];
		if(pFileData == NULL)
			return;

		nFileLen = file.Read(pFileData, nFileLen);
		file.Close();

		long lret = SPIDER_ImportConfig(theApp.m_hSelectCamera, nFileLen, pFileData);
		if(lret != E_CTRL_OK)
		{
			MessageBox(GetErrorString(lret), ("Failed to import."));
		}
		else
		{
			MessageBox(("Success to import."));
		}

		delete [] pFileData;
	}
}

void CTestDlgDlg::OnBnClickedButtonSnapshot()
{
	if(theApp.m_hSelectCamera == NULL)
	{
		MessageBox(("Select camera."));
		return;
	}

	int nSel = m_List_Camera.GetSelectionMark();
	if(nSel != -1)
	{
		char szaddr[100] = ("");
		m_List_Camera.GetItemText(nSel, 2, szaddr, 50);

		int nLen = 0;
		BYTE* pFileData = new BYTE[3000*3000*4];
		long lret = SPIDER_GetSnapShotImage(theApp.m_hSelectCamera, &nLen, pFileData);
		if(lret != E_CTRL_OK)
		{
			delete [] pFileData;
			MessageBox(GetErrorString(lret), ("Fail"));
			return;
		}

		CFile file;
		CString cName;
		cName = gszCurDir;
		cName += szaddr;
		cName += "_";
		cName += "Snapshot.jpg";
		file.Open(cName, file.modeCreate|file.modeWrite);
		file.Write(pFileData, nLen);
		file.Close();

		delete [] pFileData;


		CString sztext;
		sztext = "SnapShot saved!!\r\n";
		sztext += cName;
		MessageBox(sztext);
	}
}

void CTestDlgDlg::OnBnClickedButtonSerialport()
{
	if(theApp.m_hSelectCamera == NULL)
	{
		MessageBox(("Select camera to connect serial port."));
		return;
	}

	CSerialPortInfoDlg dlg;
	dlg.DoModal();
}


void CTestDlgDlg::OnBnClickedButtonChannelSnapshot()
{
	if (theApp.m_hSelectCamera == NULL) {
		MessageBox(("Select camera."));
		return;
	}

	int nSel = m_List_Camera.GetSelectionMark();
	if (nSel != -1) {
		char szaddr[100] = ("");
		m_List_Camera.GetItemText(nSel, 2, szaddr, 50);

		int nItem = m_cbChSnapShot.GetCurSel();
		if (nItem != CB_ERR) {
			int nLen = 0;
			BYTE* pFileData = new BYTE[3000*3000*4];
			long lret = SPIDER_GetChannelSnapShotImage(theApp.m_hSelectCamera, &nLen, pFileData, nItem+1);
			if (lret != E_CTRL_OK) {
				delete [] pFileData;
				MessageBox(GetErrorString(lret), ("Fail"));
				return;
			}

			CFile file;
			CString cName;
			cName = gszCurDir;
			cName += szaddr;
			cName += "_";
			cName += "Snapshot.jpg";
			file.Open(cName, file.modeCreate|file.modeWrite);
			file.Write(pFileData, nLen);
			file.Close();

			delete [] pFileData;


			CString sztext;
			sztext = "SnapShot saved!!\r\n";
			sztext += cName;
			MessageBox(sztext);
		}
	}
}


void CTestDlgDlg::OnBnClickedButtonStreamRoiInfo()
{
	if (theApp.m_hSelectCamera == NULL) {
		MessageBox(("Select camera."));
		return;
	}
	int nSel = m_List_Camera.GetSelectionMark();
	if (nSel != -1) {
		CStreamROIInfoDlg Dlg;
		Dlg.DoModal();
	}
}


void CTestDlgDlg::OnBnClickedButtonThermalSpot()
{
	if (theApp.m_hSelectCamera == NULL) {
		MessageBox(("Select camera."));
		return;
	}
	int nSel = m_List_Camera.GetSelectionMark();
	if (nSel != -1) {
//		CThermalSpotInfoDlg Dlg; // for IMT-812N
		CThermalCtrlInfoDlg Dlg; // for IMT-813N
		Dlg.DoModal();
	}
}


void CTestDlgDlg::OnBnClickedButtonDigitalIo()
{
	if (theApp.m_hSelectCamera == NULL) {
		MessageBox(("Select camera."));
		return;
	}
	int nSel = m_List_Camera.GetSelectionMark();
	if (nSel != -1) {
		CDigitalIOInfoDlg Dlg;
		Dlg.DoModal();
	}
}


void CTestDlgDlg::OnBnClickedButtonDdns()
{
	if (theApp.m_hSelectCamera == NULL) {
		MessageBox(("Select camera."));
		return;
	}
	int nSel = m_List_Camera.GetSelectionMark();
	if (nSel != -1) {
		CDynamicDNSInfoDlg Dlg;
		Dlg.DoModal();
	}
}


void CTestDlgDlg::OnBnClickedButtonSnmp()
{
	if (theApp.m_hSelectCamera == NULL) {
		MessageBox(("Select camera."));
		return;
	}
	int nSel = m_List_Camera.GetSelectionMark();
	if (nSel != -1) {
		CSNMPInfoDlg Dlg;
		Dlg.DoModal();
	}
}


void CTestDlgDlg::OnBnClickedButtonPppoe()
{
	if (theApp.m_hSelectCamera == NULL) {
		MessageBox(("Select camera."));
		return;
	}
	int nSel = m_List_Camera.GetSelectionMark();
	if (nSel != -1) {
		CPPPoEInfoDlg Dlg;
		Dlg.DoModal();
	}
}
