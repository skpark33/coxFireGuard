// SerialPortInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDlg.h"
#include "SerialPortInfoDlg.h"


// SerialPortInfoDlg dialog

IMPLEMENT_DYNAMIC(CSerialPortInfoDlg, CDialog)

CSerialPortInfoDlg::CSerialPortInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSerialPortInfoDlg::IDD, pParent)
{
	ZeroMemory(&m_stInfo, sizeof(m_stInfo));
	m_hSerial = NULL;
}

CSerialPortInfoDlg::~CSerialPortInfoDlg()
{
}

void CSerialPortInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ENABLE, m_Combo_Enable);
	DDX_Control(pDX, IDC_COMBO_PORT_TYPE, m_Combo_PortType);
	DDX_Control(pDX, IDC_COMBO_DUPLEX_MODE, m_Combo_DuplexMode);
	DDX_Control(pDX, IDC_COMBO_DIRECTION, m_Combo_Direction);
	DDX_Control(pDX, IDC_COMBO_PARITY_TYPE, m_Combo_ParityType);
	DDX_Control(pDX, IDC_COMBO_STOP_BITS, m_Combo_StopBits);
	DDX_Control(pDX, IDC_COMBO_PROTOCOL, m_Combo_Protocol);
}


BEGIN_MESSAGE_MAP(CSerialPortInfoDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CSerialPortInfoDlg::OnBnClickedButtonModify)
	ON_CBN_SELCHANGE(IDC_COMBO_ENABLE, &CSerialPortInfoDlg::OnCbnSelchangeComboEnable)
	ON_CBN_SELCHANGE(IDC_COMBO_PORT_TYPE, &CSerialPortInfoDlg::OnCbnSelchangeComboPortType)
	ON_CBN_SELCHANGE(IDC_COMBO_DIRECTION, &CSerialPortInfoDlg::OnCbnSelchangeComboDirection)
	ON_CBN_SELCHANGE(IDC_COMBO_STOP_BITS, &CSerialPortInfoDlg::OnCbnSelchangeComboStopBits)
	ON_CBN_SELCHANGE(IDC_COMBO_DUPLEX_MODE, &CSerialPortInfoDlg::OnCbnSelchangeComboDuplexMode)
	ON_CBN_SELCHANGE(IDC_COMBO_PARITY_TYPE, &CSerialPortInfoDlg::OnCbnSelchangeComboParityType)
	ON_EN_CHANGE(IDC_EDIT_DATA_BITS, &CSerialPortInfoDlg::OnEnChangeEditDataBits)
	ON_EN_CHANGE(IDC_EDIT_BAUD_RATE, &CSerialPortInfoDlg::OnEnChangeEditBaudRate)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CSerialPortInfoDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY2, &CSerialPortInfoDlg::OnBnClickedButtonModify2)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CSerialPortInfoDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CSerialPortInfoDlg::OnBnClickedButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_WRITE, &CSerialPortInfoDlg::OnBnClickedButtonWrite)
	ON_BN_CLICKED(IDC_BUTTON_READ, &CSerialPortInfoDlg::OnBnClickedButtonRead)
END_MESSAGE_MAP()


// CSerialPortInfoDlg message handlers

BOOL CSerialPortInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here



	m_Combo_Enable.ResetContent();
	m_Combo_Enable.AddString(("Enable"));
	m_Combo_Enable.AddString(("Disable"));
	m_Combo_Enable.SetCurSel(0);

	m_Combo_PortType.ResetContent();
	m_Combo_PortType.AddString(("RS485"));
	m_Combo_PortType.AddString(("RS422"));
	m_Combo_PortType.AddString(("RS232"));
	m_Combo_PortType.SetCurSel(0);

	m_Combo_DuplexMode.ResetContent();
	m_Combo_DuplexMode.AddString(("half"));
	m_Combo_DuplexMode.AddString(("full"));
	m_Combo_DuplexMode.SetCurSel(0);

	m_Combo_Direction.ResetContent();
	m_Combo_Direction.AddString(("mono"));
	m_Combo_Direction.AddString(("bdirect"));
	m_Combo_Direction.SetCurSel(0);

	m_Combo_ParityType.ResetContent();
	m_Combo_ParityType.AddString(("none"));
	m_Combo_ParityType.AddString(("even"));
	m_Combo_ParityType.AddString(("odd"));
	m_Combo_ParityType.AddString(("mark"));
	m_Combo_ParityType.AddString(("space"));
	m_Combo_ParityType.SetCurSel(0);

	m_Combo_StopBits.ResetContent();
	m_Combo_StopBits.AddString(("1"));
	m_Combo_StopBits.AddString(("1.5"));
	m_Combo_StopBits.AddString(("2"));
	m_Combo_StopBits.SetCurSel(0);



	


	ST_SPIDER_SERIAL_PORT_INFO stInfo = {0};
	long lret = SPIDER_GetSerialPortInfo(theApp.m_hSelectCamera, &stInfo);
	if(lret != E_CTRL_OK)
	{
		MessageBox(GetErrorString(lret), ("Fail"));
		EndDialog(IDOK);
		return FALSE;
	}

	m_stInfo = stInfo;

	_DisplayDlgInfo();







	SetDlgItemText(IDC_EDIT_PORT, ("4083"));
	m_Combo_Protocol.ResetContent();
	m_Combo_Protocol.AddString(("pelcod"));
	m_Combo_Protocol.AddString(("pelcop"));
	m_Combo_Protocol.AddString(("path (path-through)"));
	m_Combo_Protocol.SetCurSel(0);

	_DisplayRS485Info();






	bool bEnable = false;
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(bEnable?false:true);
	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_WRITE)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_READ)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_WRITE)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_READ)->EnableWindow(bEnable);



	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSerialPortInfoDlg::OnBnClickedButtonModify()
{
	ST_SPIDER_SERIAL_PORT_INFO stInfo = m_stInfo;

	stInfo.nsEnable = 1;
	long lret = SPIDER_SetSerialPortInfo(theApp.m_hSelectCamera, stInfo);
	if(lret != E_CTRL_OK)
	{
		MessageBox(GetErrorString(lret), ("Fail"));
		return;
	}

	m_stInfo = stInfo;
}



void CSerialPortInfoDlg::_DisplayDlgInfo()
{
	ST_SPIDER_SERIAL_PORT_INFO stInfo = m_stInfo;

	CString sztext;

	_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_SERIAL_PORT_ID), stInfo.strID, sztext);
	bool bEnable = false;
	if(stInfo.nsEnable == 1)
	{
		bEnable = true;
		m_Combo_Enable.SetCurSel(0);
		m_Combo_Enable.EnableWindow(true);
	}
	else if(stInfo.nsEnable == 0)
	{
		m_Combo_Enable.SetCurSel(1);
		m_Combo_Enable.EnableWindow(true);
	}
	else
	{
		m_Combo_Enable.SetCurSel(0);
		m_Combo_Enable.EnableWindow(false);
	}

	if(bEnable == false)
	{
		_VALID_WND_WITH_VAL(m_Combo_PortType, 0xFFFF, NULL);
		_VALID_WND_WITH_VAL(m_Combo_DuplexMode, 0xFFFF, NULL);
		_VALID_WND_WITH_VAL(m_Combo_Direction,  0xFFFF, NULL);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_BAUD_RATE), 0xFFFF, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_DATA_BITS), 0xFFFF, sztext);
		_VALID_WND_WITH_VAL(m_Combo_ParityType,  0xFFFF, NULL);
		_VALID_WND_WITH_VAL(m_Combo_StopBits,  0xFFFF, NULL);
	}
	else
	{
		//enum ENUM_SPIDER_SERIAL_PORT_TYPE
			//E_SERIAL_PORT_TYPE_RS485 = 0,
			//E_SERIAL_PORT_TYPE_RS422 = 1,
			//E_SERIAL_PORT_TYPE_RS232 = 2,
		_VALID_WND_WITH_VAL(m_Combo_PortType, stInfo.nsPortType, NULL);

		//enum ENUM_SPIDER_SERIAL_DUPLEX_MODE
		//	E_SERIAL_DUPLEX_MODE_HALF = 0,
		//	E_SERIAL_DUPLEX_MODE_FULL = 1,	
		_VALID_WND_WITH_VAL(m_Combo_DuplexMode, stInfo.nsDuplexMode, NULL);

		//enum ENUM_SPIDER_SERIAL_DIRECTION
		//	E_SERIAL_DIRECTION_MONO = 0,
		//	E_SERIAL_DIRECTION_BDIRECT = 1,	
		_VALID_WND_WITH_VAL(m_Combo_Direction, stInfo.nsDirection, NULL);

		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_BAUD_RATE), stInfo.nBaudRate, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_DATA_BITS), stInfo.nDataBits, sztext);

		//enum ENUM_SPIDER_SERIAL_PARITY
		//	E_SERIAL_PARITY_NONE = 0,
		//	E_SERIAL_PARITY_EVEN = 1,
		//	E_SERIAL_PARITY_ODD = 2,
		//	E_SERIAL_PARITY_MARK = 3,
		//	E_SERIAL_PARITY_SPACE = 4,
		_VALID_WND_WITH_VAL(m_Combo_ParityType, stInfo.nsParityType, NULL);

		//enum ENUM_SPIDER_SERIAL_STOPBITS
		//	E_SERIAL_STOPBITS_1 = 0,	// "1"
		//	E_SERIAL_STOPBITS_1_5 = 1,	// "1.5"
		//	E_SERIAL_STOPBITS_2 = 2,	// "2"
		_VALID_WND_WITH_VAL(m_Combo_StopBits, stInfo.nsStopBits, NULL);
	}
}


void CSerialPortInfoDlg::OnCbnSelchangeComboEnable()
{
	if(m_Combo_Enable.GetCurSel() == 0)
		m_stInfo.nsEnable = 1;
	else
		m_stInfo.nsEnable = 0;

	_DisplayDlgInfo();
}

void CSerialPortInfoDlg::OnCbnSelchangeComboPortType()
{
	m_stInfo.nsPortType = m_Combo_PortType.GetCurSel();

	_DisplayDlgInfo();
}

void CSerialPortInfoDlg::OnCbnSelchangeComboDirection()
{
	m_stInfo.nsDirection = m_Combo_Direction.GetCurSel();
	_DisplayDlgInfo();
}

void CSerialPortInfoDlg::OnCbnSelchangeComboStopBits()
{
	m_stInfo.nsStopBits = m_Combo_StopBits.GetCurSel();

	_DisplayDlgInfo();
}

void CSerialPortInfoDlg::OnCbnSelchangeComboDuplexMode()
{
	m_stInfo.nsDuplexMode = m_Combo_DuplexMode.GetCurSel();

	_DisplayDlgInfo();
}

void CSerialPortInfoDlg::OnCbnSelchangeComboParityType()
{
	m_stInfo.nsParityType = m_Combo_ParityType.GetCurSel();

	_DisplayDlgInfo();
}

void CSerialPortInfoDlg::OnEnChangeEditBaudRate()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString sztext;

	GetDlgItem(IDC_EDIT_BAUD_RATE)->GetWindowText(sztext);
	m_stInfo.nBaudRate = atoi(sztext);
}

void CSerialPortInfoDlg::OnEnChangeEditDataBits()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString sztext;

	GetDlgItem(IDC_EDIT_DATA_BITS)->GetWindowText(sztext);
	m_stInfo.nDataBits = atoi(sztext);
}

void CSerialPortInfoDlg::OnBnClickedButtonSend()
{
	CString sztext;
	GetDlgItem(IDC_EDIT_COMMAND)->GetWindowText(sztext);

	char szcmd[150] = "";
	StringCopyTo(sztext, szcmd);
	
	long lret = SPIDER_SetSerialPortCommand(theApp.m_hSelectCamera, szcmd);
	if(lret != E_CTRL_OK)
	{
		MessageBox(GetErrorString(lret), ("Fail"));
		return;
	}

	MessageBox(("Success"));
}






void CSerialPortInfoDlg::_DisplayRS485Info()
{
	int nAddress;
	char strProtocol[50];
	long lret = SPIDER_GetRS485Info(theApp.m_hSelectCamera, &nAddress, strProtocol);
	if(lret != E_CTRL_OK)
	{
		MessageBox(GetErrorString(lret), ("Fail"));
		GetDlgItem(IDC_EDIT_ADDRESS)->EnableWindow(false);
		m_Combo_Protocol.EnableWindow(false);
		return;
	}

	GetDlgItem(IDC_EDIT_ADDRESS)->EnableWindow(true);
	SetDlgItemInt(IDC_EDIT_ADDRESS, nAddress);

	CString text;
	text = strProtocol;
	m_Combo_Protocol.EnableWindow(true);
	m_Combo_Protocol.SetWindowText(text);
}

void CSerialPortInfoDlg::OnBnClickedButtonModify2()
{
	int nAddress;
	char strProtocol[100] = "";
	nAddress = GetDlgItemInt(IDC_EDIT_ADDRESS);	
	m_Combo_Protocol.GetWindowText(strProtocol, 50);	
	strProtocol[strlen(strProtocol)-2] = '\0';
	if(strstr(strProtocol, "path-through") == 0)
		strcpy(strProtocol, "path");
	
	long lret = SPIDER_SetRS485Info(theApp.m_hSelectCamera, nAddress, strProtocol);
	if(lret != E_CTRL_OK)
	{
		MessageBox(GetErrorString(lret), ("Fail"));
		return;
	}

	MessageBox(("Success"));
}

void CSerialPortInfoDlg::OnBnClickedButtonConnect()
{
	int nPort = GetDlgItemInt(IDC_EDIT_PORT);

	char ipaddr[100];
	SPIDER_GetCameraConnectParameter(theApp.m_hSelectCamera, ipaddr, 0,0,0);

	bool bEnable = false;
	m_hSerial = SPIDER_ConnectSerialPort(ipaddr, nPort);
	if(m_hSerial)
	{
		bEnable = true;
	}

	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(bEnable?false:true);
	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_WRITE)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_READ)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_WRITE)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_READ)->EnableWindow(bEnable);		
}

void CSerialPortInfoDlg::OnBnClickedButtonDisconnect()
{
	if(m_hSerial)
		SPIDER_DisconnectSerialPort(m_hSerial);
	m_hSerial = NULL;

	bool bEnable = false;
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(bEnable?false:true);
	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_WRITE)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_READ)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_WRITE)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_READ)->EnableWindow(bEnable);
}

void CSerialPortInfoDlg::OnBnClickedButtonWrite()
{
	int nWritten = 0;

	char strBuf[500] = "";
	GetDlgItemText(IDC_EDIT_WRITE, strBuf, 200);
	long lret = SPIDER_WriteSerialData(m_hSerial, strBuf, strlen(strBuf), &nWritten);
	if(lret != E_CTRL_OK)
	{
		MessageBox(GetErrorString(lret), ("Fail"));
		return;
	}
	MessageBox(("Success"));
}

void CSerialPortInfoDlg::OnBnClickedButtonRead()
{
	int nRead = 0;
	char strBuf[101] = "";
	long lret = SPIDER_ReadSerialData(m_hSerial, 100, strBuf, &nRead);
	
	SetDlgItemText(IDC_EDIT_READ, strBuf);

	if(lret != E_CTRL_OK)
	{
		MessageBox(GetErrorString(lret), ("Fail"));
		return;
	}
}
