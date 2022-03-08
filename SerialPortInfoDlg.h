#pragma once

#include "resource.h"
#include "afxwin.h"


// SerialPortInfoDlg dialog

class CSerialPortInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CSerialPortInfoDlg)

public:
	CSerialPortInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSerialPortInfoDlg();

// Dialog Data
	enum { IDD = IDD_SERIAL_INFO };



	ST_SPIDER_SERIAL_PORT_INFO	m_stInfo;
	void _DisplayDlgInfo();
	void _DisplayRS485Info();


	HSERIAL m_hSerial;



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonModify();
	CComboBox m_Combo_Enable;
	CComboBox m_Combo_PortType;
	CComboBox m_Combo_DuplexMode;
	CComboBox m_Combo_Direction;
	CComboBox m_Combo_ParityType;
	CComboBox m_Combo_StopBits;
	afx_msg void OnCbnSelchangeComboEnable();
	afx_msg void OnCbnSelchangeComboPortType();
	afx_msg void OnCbnSelchangeComboDirection();
	afx_msg void OnCbnSelchangeComboStopBits();
	afx_msg void OnCbnSelchangeComboDuplexMode();
	afx_msg void OnCbnSelchangeComboParityType();
	afx_msg void OnEnChangeEditDataBits();
	afx_msg void OnEnChangeEditBaudRate();
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonModify2();
	afx_msg void OnBnClickedButtonConnect();
	CComboBox m_Combo_Protocol;
	afx_msg void OnBnClickedButtonDisconnect();
	afx_msg void OnBnClickedButtonWrite();
	afx_msg void OnBnClickedButtonRead();
};
