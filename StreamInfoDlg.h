#pragma once
#include "afxwin.h"

#ifdef _WIN32_WCE
#error "CDialog is not supported for Windows CE."
#endif 

// CStreamInfoDlg dialog

class CStreamInfoDlg : public CDialog
{
	DECLARE_DYNCREATE(CStreamInfoDlg)

public:
	CStreamInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CStreamInfoDlg();


// Dialog Data
	enum { IDD = IDD_STREAM_INFO, IDH = IDR_HTML_STREAMINFODLG };


	vector<ST_SPIDER_STREAM_INFO>		m_vInfo;


	vector<ST_SPIDER_STREAM_RESOLUTION_INFO>		m_vResolution;

	void DisplayInfo();


	void _Init_Capability_Ctrl();
	void _GetCapabilityOfStream(int nStreamIndex);
	ST_SPIDER_STREAM_CAPABILITY			m_stCapa;
	vector<int>				m_vTransportProtocol;
	vector<int>				m_vRTPTransportType;	//nsUniRtpType
	vector<string>			m_vVideoInputChID;
	vector<int>				m_vVideoCodecType;		//nsVideoCodecType (ENUM_SV_CODEC_TYPE)
	vector<int>				m_vVideoScanType;
	vector<int>				m_vVideoQualityType;
	vector<int>				m_vMaxFrameRate;
	vector<int>				m_vRotation;
	vector<int>				m_vSnapImageType;
	vector<string>			m_vAudioInputChID;
	vector<int>				m_vAudioCompressType;
	vector<int>				m_vAudioBitRate;
	vector<int>				m_vAudioSampleRate;
	vector<int>				m_vAudioResolution;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	CListCtrl m_List_Stream;
	CComboBox m_Combo_Enable;

	CComboBox	m_Combo_EnableAudio;
	CComboBox	m_Combo_AudioCompressType;
	CComboBox	m_Combo_InboundCompressType;

	CComboBox m_Combo_CodecType;
	CComboBox m_Combo_ScanType;
	CComboBox m_Combo_QualityControl;
	CComboBox m_Combo_EnableVideo;
	CComboBox m_Combo_MirrorEnable;
	CComboBox m_Combo_SnapShotType;
	CComboBox m_Combo_Resolution;
	CComboBox m_Combo_FrameRate;
	CComboBox m_Combo_Rotation;

	CButton m_Check_Protocol_RTSP;
	CButton m_Check_Protocol_HTTP;
	CButton m_Check_SRTP;

	RESOLUTION_SIZE m_emResSize;

	CButton m_btnResSizeChange;
	CButton m_btnIFrameItvChange;
	CComboBox m_cbResSize;
	CEdit m_edtIFrameItv;
	LONG m_nlIFrameItv[4];

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMClickListStream(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListStream(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonModify();
	afx_msg void OnBnClickedButtonResolutionSizeChange();
	afx_msg void OnBnClickedButtonIFrameItvChange();
};
