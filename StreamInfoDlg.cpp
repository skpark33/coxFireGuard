// StreamInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDlg.h"
#include "StreamInfoDlg.h"


// CStreamInfoDlg dialog

IMPLEMENT_DYNCREATE(CStreamInfoDlg, CDialog)

CStreamInfoDlg::CStreamInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStreamInfoDlg::IDD, pParent)
{
	ZeroMemory(&m_nlIFrameItv, sizeof(m_nlIFrameItv));
}

CStreamInfoDlg::~CStreamInfoDlg()
{
}

void CStreamInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_STREAM, m_List_Stream);
	DDX_Control(pDX, IDC_COMBO_ENABLE, m_Combo_Enable);
	DDX_Control(pDX, IDC_COMBO_ENABLE_AUDIO, m_Combo_EnableAudio);
	DDX_Control(pDX, IDC_COMBO_AUDIO_COMPRESSION_TYPE, m_Combo_AudioCompressType);
	DDX_Control(pDX, IDC_COMBO_INBOUND_COMPRESSION_TYPE, m_Combo_InboundCompressType);
	DDX_Control(pDX, IDC_CHECK_RTSP, m_Check_Protocol_RTSP);
	DDX_Control(pDX, IDC_CHECK_HTTP, m_Check_Protocol_HTTP);
	DDX_Control(pDX, IDC_CHECK_SECURE_RTP, m_Check_SRTP);
	DDX_Control(pDX, IDC_COMBO_CODEC_TYPE, m_Combo_CodecType);
	DDX_Control(pDX, IDC_COMBO_SCAN_TYPE, m_Combo_ScanType);
	DDX_Control(pDX, IDC_COMBO_QUALITY_CONTROL, m_Combo_QualityControl);
	DDX_Control(pDX, IDC_COMBO_ENABLE_VIDEO, m_Combo_EnableVideo);
	DDX_Control(pDX, IDC_COMBO_MIRROR_ENABLE, m_Combo_MirrorEnable);
	DDX_Control(pDX, IDC_COMBO_SNAPSHOT_TYPE, m_Combo_SnapShotType);
	DDX_Control(pDX, IDC_COMBO_RESOLUTION, m_Combo_Resolution);
	DDX_Control(pDX, IDC_COMBO_FRAME_RATE, m_Combo_FrameRate);
	DDX_Control(pDX, IDC_COMBO_ROTATION, m_Combo_Rotation);
	DDX_Control(pDX, IDC_BUTTON_RESOLUTION_SIZE_CHANGE, m_btnResSizeChange);
	DDX_Control(pDX, IDC_BUTTON_I_FRAME_ITV_CHANGE, m_btnIFrameItvChange);
	DDX_Control(pDX, IDC_COMBO_RESOLUTION_SIZE, m_cbResSize);
	DDX_Control(pDX, IDC_EDIT_I_FRAME_INTERVAL, m_edtIFrameItv);
}

BOOL CStreamInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	LONG nlRet = SPIDER_GetResolutionChange(theApp.m_hSelectCamera, &m_emResSize);
	if (nlRet == E_CTRL_OK) {
		m_cbResSize.AddString(_T("2M"));
		m_cbResSize.AddString(_T("3M"));
		m_cbResSize.AddString(_T("5M"));
		int nSel = -1;
		switch (m_emResSize) {
		case RESOLUTION_SIZE_2M: nSel = 0; break;
		case RESOLUTION_SIZE_3M: nSel = 1; break;
		case RESOLUTION_SIZE_5M: nSel = 2; break;
		}
		if (nSel != -1) {
			m_cbResSize.SetCurSel(nSel);
		}
	} else {
		m_cbResSize.EnableWindow(FALSE);
		m_btnResSizeChange.EnableWindow(FALSE);
	}

	nlRet = SPIDER_GetIFrameItv(theApp.m_hSelectCamera, &m_nlIFrameItv[0], &m_nlIFrameItv[1], &m_nlIFrameItv[2], &m_nlIFrameItv[3]);
	if (nlRet != E_CTRL_OK) {
		m_edtIFrameItv.EnableWindow(FALSE);
		m_btnIFrameItvChange.EnableWindow(FALSE);
	}

	

	m_List_Stream.SetExtendedStyle( m_List_Stream.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	int ncol = 0;
	m_List_Stream.InsertColumn(ncol++, ("Index"), 0, 50);
	m_List_Stream.InsertColumn(ncol++, ("ID"), 0, 30);
	m_List_Stream.InsertColumn(ncol++, ("Channel Name"), 0, 100);
	m_List_Stream.InsertColumn(ncol++, ("Enable"), 0, 50);
	m_List_Stream.InsertColumn(ncol++, ("Video Enable"), 0, 80);
	m_List_Stream.InsertColumn(ncol++, ("Video Channel ID"), 0, 100);
	m_List_Stream.InsertColumn(ncol++, ("Codec"), 0, 50);
	m_List_Stream.InsertColumn(ncol++, ("Resolution"), 0, 80);
	//m_List_Stream.InsertColumn(ncol++, ("Max FPS"), 0, 60);
	

	m_Combo_Enable.ResetContent();
	m_Combo_Enable.AddString(("Disable"));
	m_Combo_Enable.AddString(("Enable"));
	m_Combo_Enable.SetCurSel(0);



	m_Combo_EnableAudio.ResetContent();
	m_Combo_EnableAudio.AddString(("Disable"));
	m_Combo_EnableAudio.AddString(("Enable"));
	m_Combo_EnableAudio.SetCurSel(0);


	m_Combo_EnableVideo.ResetContent();
	m_Combo_EnableVideo.AddString(("Disable"));
	m_Combo_EnableVideo.AddString(("Enable"));
	m_Combo_EnableVideo.SetCurSel(0);


	m_Combo_AudioCompressType.ResetContent();
	m_Combo_AudioCompressType.AddString(("G.711alaw"));
	m_Combo_AudioCompressType.AddString(("G.711ulaw"));
	m_Combo_AudioCompressType.AddString(("G.726"));
	m_Combo_AudioCompressType.AddString(("G.729"));
	m_Combo_AudioCompressType.AddString(("G.729a"));
	m_Combo_AudioCompressType.AddString(("G.729b"));
	m_Combo_AudioCompressType.AddString(("PCM"));
	m_Combo_AudioCompressType.AddString(("MP3"));
	m_Combo_AudioCompressType.AddString(("AC3"));
	m_Combo_AudioCompressType.AddString(("AAC"));
	m_Combo_AudioCompressType.AddString(("ADPCM"));
	m_Combo_AudioCompressType.SetCurSel(0);

	m_Combo_InboundCompressType.ResetContent();
	m_Combo_InboundCompressType.AddString(("G.711alaw"));
	m_Combo_InboundCompressType.AddString(("G.711ulaw"));
	m_Combo_InboundCompressType.AddString(("G.726"));
	m_Combo_InboundCompressType.AddString(("G.729"));
	m_Combo_InboundCompressType.AddString(("G.729a"));
	m_Combo_InboundCompressType.AddString(("G.729b"));
	m_Combo_InboundCompressType.AddString(("PCM"));
	m_Combo_InboundCompressType.AddString(("MP3"));
	m_Combo_InboundCompressType.AddString(("AC3"));
	m_Combo_InboundCompressType.AddString(("AAC"));
	m_Combo_InboundCompressType.AddString(("ADPCM"));
	m_Combo_InboundCompressType.SetCurSel(0);







	m_Combo_CodecType.ResetContent();
	m_Combo_CodecType.AddString(("MPEG4"));
	m_Combo_CodecType.AddString(("MJPEG"));
	m_Combo_CodecType.AddString(("3GP"));
	m_Combo_CodecType.AddString(("H.264"));
	m_Combo_CodecType.AddString(("MPNG"));
	m_Combo_CodecType.SetCurSel(0);

	m_Combo_ScanType.ResetContent();
	m_Combo_ScanType.AddString(("progressive"));
	m_Combo_ScanType.AddString(("interlaced"));
	m_Combo_ScanType.SetCurSel(0);

	m_Combo_QualityControl.ResetContent();
	m_Combo_QualityControl.AddString(("cbr"));
	m_Combo_QualityControl.AddString(("vbr"));
	m_Combo_QualityControl.SetCurSel(0);

	m_Combo_Rotation.ResetContent();
	m_Combo_Rotation.AddString(("0"));
	m_Combo_Rotation.AddString(("90"));
	m_Combo_Rotation.AddString(("180"));
	m_Combo_Rotation.AddString(("270"));
	m_Combo_Rotation.SetCurSel(0);

	m_Combo_MirrorEnable.ResetContent();
	m_Combo_MirrorEnable.AddString(("Disable"));
	m_Combo_MirrorEnable.AddString(("Enable"));
	m_Combo_MirrorEnable.SetCurSel(0);

	m_Combo_SnapShotType.ResetContent();
	m_Combo_SnapShotType.AddString(("JPEG"));
	m_Combo_SnapShotType.AddString(("GIF"));
	m_Combo_SnapShotType.AddString(("PNG"));
	m_Combo_SnapShotType.SetCurSel(0);





	m_Combo_Resolution.ResetContent();
	m_vResolution.clear();
	long nCount = SPIDER_GetStreamCapaResolutionCount(theApp.m_hSelectCamera);
	for(int i = 0; i < nCount; i++)
	{
		ST_SPIDER_STREAM_RESOLUTION_INFO stInfo = {0};
		long lret = SPIDER_GetStreamCapaResolutionInfo(theApp.m_hSelectCamera, i, &stInfo);
		if(lret != E_CTRL_OK)
		{
			MessageBox(GetErrorString(lret), ("Fail"));
			break;
		}

		m_vResolution.push_back(stInfo);
	}

	if(m_vResolution.size())
	{
		CString sztext;
		for(unsigned int nres = 0; nres < m_vResolution.size(); nres++)
		{
			sztext.Format(("%d x %d"), m_vResolution.at(nres).width, m_vResolution.at(nres).height);
			m_Combo_Resolution.AddString(sztext);
		}

		m_Combo_Resolution.ShowWindow(true);
		GetDlgItem(IDC_EDIT_WIDTH)->ShowWindow(false);
		GetDlgItem(IDC_EDIT_HEIGHT)->ShowWindow(false);
		GetDlgItem(IDC_STATIC_W)->ShowWindow(false);
		GetDlgItem(IDC_STATIC_H)->ShowWindow(false);
	}
	else
	{
		m_Combo_Resolution.ShowWindow(false);
		GetDlgItem(IDC_EDIT_WIDTH)->ShowWindow(true);
		GetDlgItem(IDC_EDIT_HEIGHT)->ShowWindow(true);
		GetDlgItem(IDC_STATIC_W)->ShowWindow(true);
		GetDlgItem(IDC_STATIC_H)->ShowWindow(true);
	}





	m_List_Stream.DeleteAllItems();

	m_vInfo.clear();
	nCount = SPIDER_GetStreamCount(theApp.m_hSelectCamera);
	for(int i = 0; i < nCount; i++)
	{
		ST_SPIDER_STREAM_INFO stInfo = {0};
		long lret = SPIDER_GetStreamInfo(theApp.m_hSelectCamera, i, &stInfo);
		if(lret != E_CTRL_OK)
		{
			MessageBox(GetErrorString(lret), ("Fail"));
			break;
		}

		m_vInfo.push_back(stInfo);
		CString sztext;


		sztext.Format(("%d"), i+1);
		m_List_Stream.InsertItem(i, sztext);


		int ncol = 1;				
		sztext = stInfo.strID;
		m_List_Stream.SetItemText(i, ncol++, sztext);

		sztext = stInfo.strChannelName;
		m_List_Stream.SetItemText(i, ncol++, sztext);

		if(stInfo.nsEnable == 0)
			sztext = "Disable";
		else if(stInfo.nsEnable == 1)
			sztext = "Enable";
		else
			sztext = "NA";
		m_List_Stream.SetItemText(i, ncol++, sztext);

		if(stInfo.stVideo.nsVideoEnable == 0)
			sztext = "Disable";
		else if(stInfo.stVideo.nsVideoEnable == 1)
			sztext = "Enable";
		else
			sztext = "NA";
		m_List_Stream.SetItemText(i, ncol++, sztext);

		sztext = stInfo.stVideo.strVideoChannelID;
		m_List_Stream.SetItemText(i, ncol++, sztext);



		CString szcodec;
		//XPM_STREAM_CODEC_TYPE_MPEG4 = 0,
		//XPM_STREAM_CODEC_TYPE_MJPEG,
		//XPM_STREAM_CODEC_TYPE_3GP,
		//XPM_STREAM_CODEC_TYPE_H264,
		//XPM_STREAM_CODEC_TYPE_MPNG
		switch(stInfo.stVideo.nsVideoCodecType)
		{
		case E_COCEC_MPEG4: szcodec = "MPEG4"; break;
		case E_COCEC_MJPEG: szcodec = "MJPEG"; break;
		case E_COCEC_3GP: szcodec = "3GP"; break;
		case E_COCEC_H264: szcodec = "H264"; break;
		case E_COCEC_MPNG: szcodec = "MPNG"; break;
		default: szcodec = "undefined"; break;
		}

		m_List_Stream.SetItem(i, ncol++, LVIF_TEXT, szcodec, 0, 0, 0, 0);
		

		sztext.Format(("%dx%d"), stInfo.stVideo.nWidth, stInfo.stVideo.nHeight);
		m_List_Stream.SetItemText(i, ncol++, sztext);
	}

	m_List_Stream.SetSelectionMark(0);
	m_List_Stream.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);

	DisplayInfo();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CStreamInfoDlg, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_LIST_STREAM, &CStreamInfoDlg::OnNMClickListStream)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_STREAM, &CStreamInfoDlg::OnLvnItemchangedListStream)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CStreamInfoDlg::OnBnClickedButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_RESOLUTION_SIZE_CHANGE, &CStreamInfoDlg::OnBnClickedButtonResolutionSizeChange)
	ON_BN_CLICKED(IDC_BUTTON_I_FRAME_ITV_CHANGE, &CStreamInfoDlg::OnBnClickedButtonIFrameItvChange)
END_MESSAGE_MAP()

// CStreamInfoDlg message handlers

void CStreamInfoDlg::OnNMClickListStream(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE*>(pNMHDR);
	// TODO: Add your control notification handler code here

	DisplayInfo();

	*pResult = 0;
}

void CStreamInfoDlg::DisplayInfo()
{
	int nSel = m_List_Stream.GetSelectionMark();

	if(nSel != -1 && nSel < m_vInfo.size())
	{
		//get stream capabilities.. 
		_GetCapabilityOfStream(nSel);







		ST_SPIDER_STREAM_INFO stStream = m_vInfo.at(nSel);


		CString sztext;
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_ID), stStream.strID, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_NAME), stStream.strChannelName, sztext);

		bool bEnable = true;
		if(stStream.nsEnable == 1)
		{
			m_Combo_Enable.SetCurSel(stStream.nsEnable);
			m_Combo_Enable.EnableWindow(true);
			bEnable = true;
		}
		else if(stStream.nsEnable == 0)
		{
			m_Combo_Enable.SetCurSel(stStream.nsEnable);
			m_Combo_Enable.EnableWindow(true);
			bEnable = false;
		}
		else 
		{
			m_Combo_Enable.EnableWindow(false);
			m_Combo_Enable.SetCurSel(0);
			bEnable = false;
		}	


		//audio
		{

			ST_SPIDER_STREAM_AUDIO stInfo = stStream.stAudio;


			if(stInfo.nsAudioEnable == 0)
			{
				m_Combo_EnableAudio.SetCurSel(stInfo.nsAudioEnable);
				m_Combo_EnableAudio.EnableWindow(true);
			}
			else if(stInfo.nsAudioEnable == 1)
			{
				m_Combo_EnableAudio.SetCurSel(stInfo.nsAudioEnable);
				m_Combo_EnableAudio.EnableWindow(true);
			}
			else 
			{
				m_Combo_EnableAudio.EnableWindow(false);
				m_Combo_EnableAudio.SetCurSel(0);
			}

			_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_INPUT_CHANNEL_ID), stInfo.strAudioChannelID, sztext);

			_VALID_WND_WITH_VAL(m_Combo_AudioCompressType, stInfo.nsAudioCompressType, NULL);
			_VALID_WND_WITH_VAL(m_Combo_InboundCompressType, stInfo.nsAudioInboundCompressType, NULL);

			_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_BITRATE), stInfo.nsAudioBitRate, sztext);
			_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_SAMPLING_RATE), stInfo.nsAudioSampleRate, sztext);
			_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_AUDIO_RESOLUTION), stInfo.nsAudioResolution, sztext);



			if(stInfo.nsAudioEnable != 1)
			{
				GetDlgItem(IDC_EDIT_INPUT_CHANNEL_ID)->EnableWindow(false);

				m_Combo_AudioCompressType.EnableWindow(false);
				m_Combo_InboundCompressType.EnableWindow(false);

				GetDlgItem(IDC_EDIT_BITRATE)->EnableWindow(false);
				GetDlgItem(IDC_EDIT_SAMPLING_RATE)->EnableWindow(false);
				GetDlgItem(IDC_EDIT_AUDIO_RESOLUTION)->EnableWindow(false);
			}

			if(bEnable == false)
			{
				m_Combo_EnableAudio.EnableWindow(false);
				GetDlgItem(IDC_EDIT_INPUT_CHANNEL_ID)->EnableWindow(false);

				m_Combo_AudioCompressType.EnableWindow(false);
				m_Combo_InboundCompressType.EnableWindow(false);

				GetDlgItem(IDC_EDIT_BITRATE)->EnableWindow(false);
				GetDlgItem(IDC_EDIT_SAMPLING_RATE)->EnableWindow(false);
				GetDlgItem(IDC_EDIT_AUDIO_RESOLUTION)->EnableWindow(false);
			}		
		}




		//transport
		{
			ST_SPIDER_STREAM_TRANSPORT stInfo = stStream.stTransport;

			_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_RTSP_PORT), stInfo.nsRtspPortNo, sztext);
			_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_MAX_PACKET_SIZE), stInfo.nMaxPacketSize, sztext);
			_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_AUDIO_PAKCET_LENGTH), stInfo.nAudioPacketLength, sztext);
			_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_AUDIO_INBOUND_PAKCET_LENGTH), stInfo.nAudioInboundPacketLength, sztext);
			_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_AUDIO_INBOUND_PORT), stInfo.nsAudioInboundPortNo, sztext);
			_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_VIDEO_SOURCE_PORT), stInfo.nsVideoSrcPortNo, sztext);
			_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_AUDIO_SOURCE_PORT), stInfo.nsAudioSrcPortNo, sztext);



			if(stInfo.nsTransportProtocolMask >= 0xFFFF)
			{
				m_Check_Protocol_RTSP.EnableWindow(false);
				m_Check_Protocol_HTTP.EnableWindow(false);
				GetDlgItem(IDC_EDIT_HTTP_PORT)->SetWindowText((""));
				GetDlgItem(IDC_EDIT_HTTP_PORT)->EnableWindow(false);

				GetDlgItem(IDC_EDIT_RTSP_PORT)->SetWindowText((""));
				GetDlgItem(IDC_EDIT_RTSP_PORT)->EnableWindow(false);

			}
			else
			{
				sztext.Format(("%d"), 80);
				GetDlgItem(IDC_EDIT_HTTP_PORT)->SetWindowText(sztext);
				GetDlgItem(IDC_EDIT_HTTP_PORT)->EnableWindow(true);
				
				m_Check_Protocol_RTSP.EnableWindow(true);
				m_Check_Protocol_HTTP.EnableWindow(true);
				//XPM_STREAM_TRANSPORT_HTTP = 1<<1,
				//XPM_STREAM_TRANSPORT_RTSP = 1<<2

				m_Check_Protocol_RTSP.SetCheck(false);
				m_Check_Protocol_HTTP.SetCheck(false);

				if(stInfo.nsTransportProtocolMask & (1<<0))
				{			
					m_Check_Protocol_HTTP.SetCheck(true);	
					GetDlgItem(IDC_EDIT_RTSP_PORT)->EnableWindow(false);
				}
				
				if(stInfo.nsTransportProtocolMask & (1<<1))
				{
					m_Check_Protocol_RTSP.SetCheck(true);	
					GetDlgItem(IDC_EDIT_RTSP_PORT)->EnableWindow(true);
				}

			}



			if(stInfo.nsMultiEnable >= 0xFFFF)
			{
				//not supported
				GetDlgItem(IDC_RADIO_MULTICAST)->SendMessage(BM_SETCHECK, 0, 0);
				GetDlgItem(IDC_RADIO_MULTICAST)->EnableWindow(false);
				sztext.Format((""));
				GetDlgItem(IDC_EDIT_USER_TRIGGER_THRESHOLD)->SetWindowText(sztext);
				GetDlgItem(IDC_EDIT_USER_TRIGGER_THRESHOLD)->EnableWindow(false);
				GetDlgItem(IDC_EDIT_VIDEO_DEST_PORT)->SetWindowText(sztext);
				GetDlgItem(IDC_EDIT_VIDEO_DEST_PORT)->EnableWindow(false);
				GetDlgItem(IDC_EDIT_AUDIO_DEST_PORT)->SetWindowText(sztext);
				GetDlgItem(IDC_EDIT_AUDIO_DEST_PORT)->EnableWindow(false);
				GetDlgItem(IDC_EDIT_DEST_IPADDR)->SetWindowText(sztext);
				GetDlgItem(IDC_EDIT_DEST_IPADDR)->EnableWindow(false);
				GetDlgItem(IDC_EDIT_TTL)->SetWindowText(sztext);
				GetDlgItem(IDC_EDIT_TTL)->EnableWindow(false);
			}
			else 
			{
				GetDlgItem(IDC_RADIO_MULTICAST)->EnableWindow(true);
				if(stInfo.nsMultiEnable)
				{
					//multicast
					GetDlgItem(IDC_RADIO_MULTICAST)->SendMessage(BM_SETCHECK, BST_CHECKED, 0);

					_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_USER_TRIGGER_THRESHOLD), stInfo.nsUserTriggerThreshold, sztext);
					_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_VIDEO_DEST_PORT), stInfo.nsMultiVideoDestPortNo, sztext);
					_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_AUDIO_DEST_PORT), stInfo.nsMultiAudioDestPortNo, sztext);
					_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_DEST_IPADDR), stInfo.strMultiDestIpAddr, sztext);
					_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_TTL), stInfo.nsTTL, sztext);
				}
				else
				{
					GetDlgItem(IDC_RADIO_MULTICAST)->SendMessage(BM_SETCHECK, 0, 0);
					sztext.Format((""));
					GetDlgItem(IDC_EDIT_USER_TRIGGER_THRESHOLD)->SetWindowText(sztext);
					GetDlgItem(IDC_EDIT_USER_TRIGGER_THRESHOLD)->EnableWindow(false);
					GetDlgItem(IDC_EDIT_VIDEO_DEST_PORT)->SetWindowText(sztext);
					GetDlgItem(IDC_EDIT_VIDEO_DEST_PORT)->EnableWindow(false);
					GetDlgItem(IDC_EDIT_AUDIO_DEST_PORT)->SetWindowText(sztext);
					GetDlgItem(IDC_EDIT_AUDIO_DEST_PORT)->EnableWindow(false);
					GetDlgItem(IDC_EDIT_DEST_IPADDR)->SetWindowText(sztext);
					GetDlgItem(IDC_EDIT_DEST_IPADDR)->EnableWindow(false);
					GetDlgItem(IDC_EDIT_TTL)->SetWindowText(sztext);
					GetDlgItem(IDC_EDIT_TTL)->EnableWindow(false);
				}
			}
			
			if(stInfo.nsUniEnble >= 0xFFFF)
			{
				GetDlgItem(IDC_RADIO_UNICAST)->SendMessage(BM_SETCHECK, 0, 0);
				GetDlgItem(IDC_RADIO_UNICAST_UDP)->SendMessage(BM_SETCHECK, 0, 0);
				GetDlgItem(IDC_RADIO_UNICAST_TCP)->SendMessage(BM_SETCHECK, 0, 0);
				_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_UNICAST_INTERFACE_ID), stInfo.strInterfaceID, sztext);
			
				GetDlgItem(IDC_RADIO_UNICAST)->EnableWindow(false);
				GetDlgItem(IDC_RADIO_UNICAST_UDP)->EnableWindow(false);
				GetDlgItem(IDC_RADIO_UNICAST_TCP)->EnableWindow(false);
				GetDlgItem(IDC_EDIT_UNICAST_INTERFACE_ID)->EnableWindow(false);
			}
			else
			{
				GetDlgItem(IDC_RADIO_UNICAST)->EnableWindow(true);
				if(stInfo.nsUniEnble)
				{
					//unicast
					GetDlgItem(IDC_RADIO_UNICAST)->SendMessage(BM_SETCHECK, BST_CHECKED, 0);

					_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_UNICAST_INTERFACE_ID), stInfo.strInterfaceID, sztext);

					GetDlgItem(IDC_RADIO_UNICAST_UDP)->EnableWindow(true);
					GetDlgItem(IDC_RADIO_UNICAST_TCP)->EnableWindow(true);
					//XPM_STREAM_RTP_PROTO_TYPE_UDP = 0,
					//XPM_STREAM_RTP_PROTO_TYPE_TCP
					if(stInfo.nsUniRtpType == 0)
					{
						GetDlgItem(IDC_RADIO_UNICAST_UDP)->SendMessage(BM_SETCHECK, BST_CHECKED, 0);
						GetDlgItem(IDC_RADIO_UNICAST_TCP)->SendMessage(BM_SETCHECK, 0, 0);
					}
					else
					{
						GetDlgItem(IDC_RADIO_UNICAST_UDP)->SendMessage(BM_SETCHECK, 0, 0);
						GetDlgItem(IDC_RADIO_UNICAST_TCP)->SendMessage(BM_SETCHECK, BST_CHECKED, 0);
					}
				}
				else
				{
					GetDlgItem(IDC_RADIO_UNICAST)->SendMessage(BM_SETCHECK, 0, 0);

					_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_UNICAST_INTERFACE_ID), stInfo.strInterfaceID, sztext);
					GetDlgItem(IDC_EDIT_UNICAST_INTERFACE_ID)->EnableWindow(false);

					GetDlgItem(IDC_RADIO_UNICAST_UDP)->EnableWindow(false);
					GetDlgItem(IDC_RADIO_UNICAST_TCP)->EnableWindow(false);
					//XPM_STREAM_RTP_PROTO_TYPE_UDP = 0,
					//XPM_STREAM_RTP_PROTO_TYPE_TCP
					if(stInfo.nsUniRtpType == 0)
					{
						GetDlgItem(IDC_RADIO_UNICAST_UDP)->SendMessage(BM_SETCHECK, BST_CHECKED, 0);
						GetDlgItem(IDC_RADIO_UNICAST_TCP)->SendMessage(BM_SETCHECK, 0, 0);
					}
					else
					{
						GetDlgItem(IDC_RADIO_UNICAST_UDP)->SendMessage(BM_SETCHECK, 0, 0);
						GetDlgItem(IDC_RADIO_UNICAST_TCP)->SendMessage(BM_SETCHECK, BST_CHECKED, 0);
					}
				}
			}


			if(stInfo.nsSecuEnable >= 0xFFFF)
			{
				m_Check_SRTP.SetCheck(false);
				m_Check_SRTP.EnableWindow(false);
			}
			else
			{
				m_Check_SRTP.SetCheck(true);
				if(stInfo.nsSecuEnable)
					m_Check_SRTP.SetCheck(true);
				else
					m_Check_SRTP.SetCheck(false);
			}		
		}


		//video
		{
			_Init_Capability_Ctrl();

			ST_SPIDER_STREAM_VIDEO stInfo = stStream.stVideo;

			if(stInfo.nsVideoEnable == 1)
			{
				m_Combo_EnableVideo.SetCurSel(stInfo.nsVideoEnable);
				m_Combo_EnableVideo.EnableWindow(true);
			}
			else if(stInfo.nsVideoEnable == 0)
			{
				m_Combo_EnableVideo.SetCurSel(stInfo.nsVideoEnable);
				m_Combo_EnableVideo.EnableWindow(true);
			}
			else 
			{
				m_Combo_EnableVideo.EnableWindow(false);
				m_Combo_EnableVideo.SetCurSel(0);
			}

			CString text;
			_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_VIDEO_INPUT_CHANNEL_ID), stInfo.strVideoChannelID, text);

			//switch(stInfo.nsVideoCodecType)
			//{
			//XPM_STREAM_CODEC_TYPE_MPEG4
			//XPM_STREAM_CODEC_TYPE_MJPEG,
			//XPM_STREAM_CODEC_TYPE_3GP,
			//XPM_STREAM_CODEC_TYPE_H264,
			//XPM_STREAM_CODEC_TYPE_MPNG
			//}
			_VALID_WND_WITH_VAL(m_Combo_CodecType, stInfo.nsVideoCodecType, true);


			
			//XPM_STREAM_SCAN_TYPE_PROG = 0,
			//XPM_STREAM_SCAN_TYPE_INTER,
			_VALID_WND_WITH_VAL(m_Combo_ScanType, stInfo.nsVideoScanType, true);


			_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_WIDTH), stInfo.nWidth, text);
			_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_HEIGHT), stInfo.nHeight, text);

			m_Combo_Resolution.EnableWindow(true);
			CString sztext;
			sztext.Format(("%d x %d"), stInfo.nWidth, stInfo.nHeight);
			unsigned int ncount = m_Combo_Resolution.GetCount();
			for(unsigned int nres = 0; nres < ncount; nres++)
			{
				m_Combo_Resolution.GetLBText(nres, text);
				if(text == sztext)
				{
					m_Combo_Resolution.SetCurSel(nres);
					break;
				}
			}

			_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_POSITION_X), stInfo.nOffsetX, text);
			_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_POSITION_Y), stInfo.nOffsetY, text);

			_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_MAX_FRAME_RATE), ((float)stInfo.nsMaxFrameRate)*(float)0.01, text);

			m_Combo_FrameRate.EnableWindow(true);
			sztext.Format(("%.2f"), ((float)stInfo.nsMaxFrameRate)*(float)0.01);
			ncount = m_Combo_FrameRate.GetCount();
			for(unsigned int nres = 0; nres < ncount; nres++)
			{
				m_Combo_FrameRate.GetLBText(nres, text);
				if(text == sztext)
				{
					m_Combo_FrameRate.SetCurSel(nres);
					break;
				}
			}

			_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_KEY_FRAME_INTERVAL), stInfo.nsKeyFrameItv, text);
			
			m_Combo_Rotation.EnableWindow(true);
			TRACE("rotation %d\r\n", stInfo.nsRotationDegree);
			if(stInfo.nsRotationDegree == 0)
			{
				m_Combo_Rotation.SetCurSel(0);
			}
			else if(stInfo.nsRotationDegree == 90)
			{
				m_Combo_Rotation.SetCurSel(1);
			}
			else if(stInfo.nsRotationDegree == 180)
			{
				m_Combo_Rotation.SetCurSel(2);
			}
			else if(stInfo.nsRotationDegree == 270)
			{
				m_Combo_Rotation.SetCurSel(3);
			}
			else if(stInfo.nsRotationDegree < 360)
			{
				text.Format(("%d"), stInfo.nsRotationDegree);
				m_Combo_Rotation.SetWindowText(text);
			}
			else
			{
				m_Combo_Rotation.SetCurSel(0);
				m_Combo_Rotation.EnableWindow(false);
			}


			if(stInfo.nsMirrorEnable == -1
			|| stInfo.nsMirrorEnable >= 0xFFFF)
			{
				m_Combo_MirrorEnable.EnableWindow(false);
			}
			else
			{
				m_Combo_MirrorEnable.EnableWindow(true);
				m_Combo_MirrorEnable.SetCurSel(stInfo.nsMirrorEnable);
			}


			_VALID_WND_WITH_VAL(m_Combo_SnapShotType, stInfo.nsSnapshotImageType, true);
			


			_VALID_WND_WITH_VAL(m_Combo_QualityControl, stInfo.nsVideoQCType, true);

			_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_CONSTANT_BITRATE), stInfo.nsConstBitRate, text);

			_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_FIXED_QUALITY), stInfo.nsFixedQuality, text);
			_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_VBR_UPPER), stInfo.nsvbrUpCap, text);
			_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_VBR_LOWER), stInfo.nsvbrLowCap, text);

			if(stInfo.nsVideoQCType == 0)
			{
				GetDlgItem(IDC_EDIT_CONSTANT_BITRATE)->EnableWindow(true);

				GetDlgItem(IDC_EDIT_FIXED_QUALITY)->EnableWindow(false);
				GetDlgItem(IDC_EDIT_VBR_UPPER)->EnableWindow(false);
				GetDlgItem(IDC_EDIT_VBR_LOWER)->EnableWindow(false);
			}
			else if(stInfo.nsVideoQCType == 1)
			{
				GetDlgItem(IDC_EDIT_CONSTANT_BITRATE)->EnableWindow(false);
				
				GetDlgItem(IDC_EDIT_FIXED_QUALITY)->EnableWindow(true);
				GetDlgItem(IDC_EDIT_VBR_UPPER)->EnableWindow(true);
				GetDlgItem(IDC_EDIT_VBR_LOWER)->EnableWindow(true);
			}
			else
			{
				GetDlgItem(IDC_EDIT_CONSTANT_BITRATE)->EnableWindow(false);
				GetDlgItem(IDC_EDIT_FIXED_QUALITY)->EnableWindow(false);
				GetDlgItem(IDC_EDIT_VBR_UPPER)->EnableWindow(false);
				GetDlgItem(IDC_EDIT_VBR_LOWER)->EnableWindow(false);
			}
		}

		if (m_edtIFrameItv.IsWindowEnabled()) {
			CString strIFrameItv = _T("");
			strIFrameItv.Format(_T("%d"), m_nlIFrameItv[nSel]);
			m_edtIFrameItv.SetWindowText(strIFrameItv);
		}
	}
}

void CStreamInfoDlg::_Init_Capability_Ctrl()
{
	//long nCount = m_vTransportProtocol.size();
	//for(int i = 0; i < nCount; i++)
	//{
	//	int nOption = m_vTransportProtocol.at(i);

	//	//http = 1<<0, rtsp = 1<<1
	//	
	//	if(nOption == (1<<0))
	//		m_Combo_Protocol.AddString(("HTTP"));
	//	else if(nOption == (1<<1))
	//		m_Combo_Protocol.AddString(("RTSP"));
	//}


	//long nCount = m_vRotation.size();
	//for(int i = 0; i < nCount; i++)
	//{
	//	int nOption = m_vRotation.at(i);

		//CString sztext;
		//sztext.Format(("%d degree"), nOption);
		//m_Combo_Rotation.AddString(sztext);
	//}





	int ndata = 0;
	CString sztext;
	unsigned int i = 0;

	{
		m_Combo_FrameRate.ResetContent();
		if(m_vMaxFrameRate.size())
		{
			CString sztext;
			for(unsigned int nres = 0; nres < m_vMaxFrameRate.size(); nres++)
			{
				sztext.Format(("%.2f"), ((float)m_vMaxFrameRate.at(nres))*(float)0.01);
				m_Combo_FrameRate.AddString(sztext);
			}

			m_Combo_FrameRate.ShowWindow(true);
			GetDlgItem(IDC_EDIT_MAX_FRAME_RATE)->ShowWindow(false);
		}
		else
		{
			m_Combo_FrameRate.ShowWindow(false);
			GetDlgItem(IDC_EDIT_MAX_FRAME_RATE)->ShowWindow(true);
		}
	}



	{
		m_Combo_CodecType.ResetContent();
		while(i < m_vVideoCodecType.size())
		{
			sztext = "";
			ndata = m_vVideoCodecType.at(i);
			switch(ndata)
			{
			case E_COCEC_MPEG4: sztext = "MPEG4"; break;
			case E_COCEC_MJPEG: sztext = "MJPEG"; break;
			case E_COCEC_3GP: sztext = "3GP"; break;
			case E_COCEC_H264: sztext = "H.264"; break;
			case E_COCEC_MPNG: sztext = "MPNG"; break;
			}

			if(sztext.GetLength())
			{
				int nAdded = m_Combo_CodecType.AddString(sztext);
				m_Combo_CodecType.SetItemData(nAdded, ndata);
			}

			i++;
		}
	}

	
	ndata = 0;
	i = 0;
	{
		m_Combo_ScanType.ResetContent();
		while(i < m_vVideoScanType.size())
		{
			sztext = "";
			ndata = m_vVideoScanType.at(i);
			switch(ndata)
			{
			//XPM_STREAM_SCAN_TYPE_PROG = 0,			// "progressive"
			//XPM_STREAM_SCAN_TYPE_INTER,				// "interlaced"
			case E_STREAM_SCAN_TYPE_PROG: sztext = "progressive"; break;
			case E_STREAM_SCAN_TYPE_INTER: sztext = "interlaced"; break;
			}

			if(sztext.GetLength())
			{
				int nAdded = m_Combo_ScanType.AddString(sztext);
				m_Combo_ScanType.SetItemData(nAdded, ndata);
			}

			i++;
		}
	}


	
	ndata = 0;
	i = 0;
	{
		m_Combo_QualityControl.ResetContent();
		while(i < m_vVideoQualityType.size())
		{
			sztext = "";
			ndata = m_vVideoQualityType.at(i);
			switch(ndata)
			{
			case E_STREAM_QC_TYPE_CBR: sztext = "cbr"; break;
			case E_STREAM_QC_TYPE_VBR: sztext = "vbr"; break;
			}

			if(sztext.GetLength())
			{
				int nAdded = m_Combo_QualityControl.AddString(sztext);
				m_Combo_QualityControl.SetItemData(nAdded, ndata);
			}

			i++;
		}
	}


	ndata = 0;
	i = 0;
	{
		m_Combo_SnapShotType.ResetContent();
		while(i < m_vSnapImageType.size())
		{
			sztext = "";
			ndata = m_vSnapImageType.at(i);
			switch(ndata)
			{
			case E_STREAM_SNAP_TYPE_JPEG: sztext = "JPEG"; break;
			case E_STREAM_SNAP_TYPE_GIF: sztext = "GIF"; break;
			case E_STREAM_SNAP_TYPE_PNG: sztext = "PNG"; break;
			}

			if(sztext.GetLength())
			{
				int nAdded = m_Combo_SnapShotType.AddString(sztext);
				m_Combo_SnapShotType.SetItemData(nAdded, ndata);
			}

			i++;
		}
	}

}

void CStreamInfoDlg::_GetCapabilityOfStream(int nStreamIndex)
{
	//get stream capabilities.. 
	long lret = SPIDER_GetStreamCapabilityRangeInfo(theApp.m_hSelectCamera, nStreamIndex, &m_stCapa);
	if(lret != E_CTRL_OK)
	{
		MessageBox(GetErrorString(lret), ("Fail"));
		return;
	}

	m_vTransportProtocol.clear();
	long nCount = SPIDER_GetStreamCapaProtocolCount(theApp.m_hSelectCamera, nStreamIndex);
	for(int i = 0; i < nCount; i++)
	{
		int nOption = 0;
		long lret = SPIDER_GetStreamCapaProtocolInfo(theApp.m_hSelectCamera, nStreamIndex, i, &nOption);
		if(lret != E_CTRL_OK)
		{
			MessageBox(GetErrorString(lret), ("Fail"));
			break;
		}

		m_vTransportProtocol.push_back(nOption);
	}

	m_vRTPTransportType.clear();
	nCount = SPIDER_GetStreamCapaRTPTransportTypeCount(theApp.m_hSelectCamera, nStreamIndex);
	for(int i = 0; i < nCount; i++)
	{
		int nOption = 0;
		long lret = SPIDER_GetStreamCapaRTPTransportTypeInfo(theApp.m_hSelectCamera, nStreamIndex, i, &nOption);
		if(lret != E_CTRL_OK)
		{
			MessageBox(GetErrorString(lret), ("Fail"));
			break;
		}

		m_vRTPTransportType.push_back(nOption);
	}

	m_vVideoInputChID.clear();
	nCount = SPIDER_GetStreamCapaVideoInputChIDCount(theApp.m_hSelectCamera, nStreamIndex);
	for(int i = 0; i < nCount; i++)
	{
		char szID[64] = "";
		long lret = SPIDER_GetStreamCapaVideoInputChIDInfo(theApp.m_hSelectCamera, nStreamIndex, i, szID);
		if(lret != E_CTRL_OK)
		{
			MessageBox(GetErrorString(lret), ("Fail"));
			break;
		}

		m_vVideoInputChID.push_back(szID);
	}

	m_vVideoCodecType.clear();
	nCount = SPIDER_GetStreamCapaVideoCodecTypeCount(theApp.m_hSelectCamera, nStreamIndex);
	for(int i = 0; i < nCount; i++)
	{
		int nOption = 0;
		long lret = SPIDER_GetStreamCapaVideoCodecTypeInfo(theApp.m_hSelectCamera, nStreamIndex, i, &nOption);
		if(lret != E_CTRL_OK)
		{
			MessageBox(GetErrorString(lret), ("Fail"));
			break;
		}

		m_vVideoCodecType.push_back(nOption);
	}

	m_vVideoScanType.clear();
	nCount = SPIDER_GetStreamCapaVideoScanTypeCount(theApp.m_hSelectCamera, nStreamIndex);
	for(int i = 0; i < nCount; i++)
	{
		int nOption = 0;
		long lret = SPIDER_GetStreamCapaVideoScanTypeInfo(theApp.m_hSelectCamera, nStreamIndex, i, &nOption);
		if(lret != E_CTRL_OK)
		{
			MessageBox(GetErrorString(lret), ("Fail"));
			break;
		}

		m_vVideoScanType.push_back(nOption);
	}

	m_vVideoQualityType.clear();
	nCount = SPIDER_GetStreamCapaVideoQualityTypeCount(theApp.m_hSelectCamera, nStreamIndex);
	for(int i = 0; i < nCount; i++)
	{
		int nOption = 0;
		long lret = SPIDER_GetStreamCapaVideoQualityTypeInfo(theApp.m_hSelectCamera, nStreamIndex, i, &nOption);
		if(lret != E_CTRL_OK)
		{
			MessageBox(GetErrorString(lret), ("Fail"));
			break;
		}

		m_vVideoQualityType.push_back(nOption);
	}

	m_vMaxFrameRate.clear();
	nCount = SPIDER_GetStreamCapaMaxFrameRateCount(theApp.m_hSelectCamera, nStreamIndex);
	for(int i = 0; i < nCount; i++)
	{
		int nOption = 0;
		long lret = SPIDER_GetStreamCapaMaxFrameRateInfo(theApp.m_hSelectCamera, nStreamIndex, i, &nOption);
		if(lret != E_CTRL_OK)
		{
			MessageBox(GetErrorString(lret), ("Fail"));
			break;
		}

		m_vMaxFrameRate.push_back(nOption);
	}

	m_vRotation.clear();
	nCount = SPIDER_GetStreamCapaRotationCount(theApp.m_hSelectCamera, nStreamIndex);
	for(int i = 0; i < nCount; i++)
	{
		int nOption = 0;
		long lret = SPIDER_GetStreamCapaRotationInfo(theApp.m_hSelectCamera, nStreamIndex, i, &nOption);
		if(lret != E_CTRL_OK)
		{
			MessageBox(GetErrorString(lret), ("Fail"));
			break;
		}

		m_vRotation.push_back(nOption);
	}

	m_vSnapImageType.clear();
	nCount = SPIDER_GetStreamCapaSnapImageTypeCount(theApp.m_hSelectCamera, nStreamIndex);
	for(int i = 0; i < nCount; i++)
	{
		int nOption = 0;
		long lret = SPIDER_GetStreamCapaSnapImageTypeInfo(theApp.m_hSelectCamera, nStreamIndex, i, &nOption);
		if(lret != E_CTRL_OK)
		{
			MessageBox(GetErrorString(lret), ("Fail"));
			break;
		}

		m_vSnapImageType.push_back(nOption);
	}

	m_vAudioInputChID.clear();
	nCount = SPIDER_GetStreamCapaAudioInputChIDCount(theApp.m_hSelectCamera, nStreamIndex);
	for(int i = 0; i < nCount; i++)
	{
		char szID[64] = "";
		long lret = SPIDER_GetStreamCapaAudioInputChIDInfo(theApp.m_hSelectCamera, nStreamIndex, i, szID);
		if(lret != E_CTRL_OK)
		{
			MessageBox(GetErrorString(lret), ("Fail"));
			break;
		}

		m_vAudioInputChID.push_back(szID);
	}

	m_vAudioCompressType.clear();
	nCount = SPIDER_GetStreamCapaAudioCompressTypeCount(theApp.m_hSelectCamera, nStreamIndex);
	for(int i = 0; i < nCount; i++)
	{
		int nOption = 0;
		long lret = SPIDER_GetStreamCapaAudioCompressTypeInfo(theApp.m_hSelectCamera, nStreamIndex, i, &nOption);
		if(lret != E_CTRL_OK)
		{
			MessageBox(GetErrorString(lret), ("Fail"));
			break;
		}

		m_vAudioCompressType.push_back(nOption);
	}

	m_vAudioBitRate.clear();
	nCount = SPIDER_GetStreamCapaAudioBitRateCount(theApp.m_hSelectCamera, nStreamIndex);
	for(int i = 0; i < nCount; i++)
	{
		int nOption = 0;
		long lret = SPIDER_GetStreamCapaAudioBitRateInfo(theApp.m_hSelectCamera, nStreamIndex, i, &nOption);
		if(lret != E_CTRL_OK)
		{
			MessageBox(GetErrorString(lret), ("Fail"));
			break;
		}

		m_vAudioBitRate.push_back(nOption);
	}

	m_vAudioSampleRate.clear();
	nCount = SPIDER_GetStreamCapaAudioSampleRateCount(theApp.m_hSelectCamera, nStreamIndex);
	for(int i = 0; i < nCount; i++)
	{
		int nOption = 0;
		long lret = SPIDER_GetStreamCapaAudioSampleRateInfo(theApp.m_hSelectCamera, nStreamIndex, i, &nOption);
		if(lret != E_CTRL_OK)
		{
			MessageBox(GetErrorString(lret), ("Fail"));
			break;
		}

		m_vAudioSampleRate.push_back(nOption);
	}

	m_vAudioResolution.clear();
	nCount = SPIDER_GetStreamCapaAudioResolutionCount(theApp.m_hSelectCamera, nStreamIndex);
	for(int i = 0; i < nCount; i++)
	{
		int nOption = 0;
		long lret = SPIDER_GetStreamCapaAudioResolutionInfo(theApp.m_hSelectCamera, nStreamIndex, i, &nOption);
		if(lret != E_CTRL_OK)
		{
			MessageBox(GetErrorString(lret), ("Fail"));
			break;
		}

		m_vAudioResolution.push_back(nOption);
	}
}


void CStreamInfoDlg::OnLvnItemchangedListStream(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CStreamInfoDlg::OnBnClickedButtonModify()
{
	int nModifyIndex = m_List_Stream.GetSelectionMark();
	if(nModifyIndex >= m_vInfo.size())
		return;

	ST_SPIDER_STREAM_INFO stNew = m_vInfo.at(nModifyIndex);

	CString sztext;

	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(sztext);
	if(strcmp(stNew.strChannelName, "NA"))
		StringCopyTo(sztext, stNew.strChannelName);

	if(stNew.nsEnable != 0xFFFF && stNew.nsEnable != 0xFFFFFFFF)
		stNew.nsEnable = m_Combo_Enable.GetCurSel();

	if(stNew.stVideo.nsVideoEnable != 0xFFFF && stNew.stVideo.nsVideoEnable != 0xFFFFFFFF)
		stNew.stVideo.nsVideoEnable = m_Combo_EnableVideo.GetCurSel();

	if(stNew.stAudio.nsAudioEnable != 0xFFFF && stNew.stAudio.nsAudioEnable != 0xFFFFFFFF)
		stNew.stAudio.nsAudioEnable = m_Combo_EnableAudio.GetCurSel();



	//audio
	{
		GetDlgItem(IDC_EDIT_INPUT_CHANNEL_ID)->GetWindowText(sztext);
		if(strcmp(stNew.stAudio.strAudioChannelID, "NA"))
			StringCopyTo(sztext, stNew.stAudio.strAudioChannelID);


		if(stNew.stAudio.nsAudioCompressType != 0xFFFF && stNew.stAudio.nsAudioCompressType != 0xFFFFFFFF)
			stNew.stAudio.nsAudioCompressType = m_Combo_AudioCompressType.GetCurSel();

		if(stNew.stAudio.nsAudioInboundCompressType != 0xFFFF && stNew.stAudio.nsAudioInboundCompressType != 0xFFFFFFFF)
			stNew.stAudio.nsAudioInboundCompressType = m_Combo_InboundCompressType.GetCurSel();


		int nValue = 0;
		GetDlgItem(IDC_EDIT_BITRATE)->GetWindowText(sztext);
		nValue = _ttoi(sztext);
		if(stNew.stAudio.nsAudioBitRate != 0xFFFF && stNew.stAudio.nsAudioBitRate != 0xFFFFFFFF)
			stNew.stAudio.nsAudioBitRate = nValue;

		GetDlgItem(IDC_EDIT_SAMPLING_RATE)->GetWindowText(sztext);
		nValue = _ttoi(sztext);
		if(stNew.stAudio.nsAudioSampleRate != 0xFFFF && stNew.stAudio.nsAudioSampleRate != 0xFFFFFFFF)
			stNew.stAudio.nsAudioSampleRate = nValue;

		GetDlgItem(IDC_EDIT_AUDIO_RESOLUTION)->GetWindowText(sztext);
		nValue = _ttoi(sztext);
		if(stNew.stAudio.nsAudioResolution != 0xFFFF && stNew.stAudio.nsAudioResolution != 0xFFFFFFFF)
			stNew.stAudio.nsAudioResolution = nValue;

	}



	//transport
	{
		int nValue = 0;
		GetDlgItem(IDC_EDIT_RTSP_PORT)->GetWindowText(sztext);
		nValue = _ttoi(sztext);
		if(stNew.stTransport.nsRtspPortNo != 0xFFFF && stNew.stTransport.nsRtspPortNo != 0xFFFFFFFF)
			stNew.stTransport.nsRtspPortNo = nValue;

		GetDlgItem(IDC_EDIT_MAX_PACKET_SIZE)->GetWindowText(sztext);
		nValue = _ttoi(sztext);
		if(stNew.stTransport.nMaxPacketSize != 0xFFFF && stNew.stTransport.nMaxPacketSize != 0xFFFFFFFF)
			stNew.stTransport.nMaxPacketSize = nValue;

		GetDlgItem(IDC_EDIT_AUDIO_PAKCET_LENGTH)->GetWindowText(sztext);
		nValue = _ttoi(sztext);
		if(stNew.stTransport.nAudioPacketLength != 0xFFFF && stNew.stTransport.nAudioPacketLength != 0xFFFFFFFF)
			stNew.stTransport.nAudioPacketLength = nValue;

		GetDlgItem(IDC_EDIT_AUDIO_INBOUND_PAKCET_LENGTH)->GetWindowText(sztext);
		nValue = _ttoi(sztext);
		if(stNew.stTransport.nAudioInboundPacketLength != 0xFFFF && stNew.stTransport.nAudioInboundPacketLength != 0xFFFFFFFF)
			stNew.stTransport.nAudioInboundPacketLength = nValue;

		GetDlgItem(IDC_EDIT_AUDIO_INBOUND_PORT)->GetWindowText(sztext);
		nValue = _ttoi(sztext);
		if(stNew.stTransport.nsAudioInboundPortNo != 0xFFFF && stNew.stTransport.nsAudioInboundPortNo != 0xFFFFFFFF)
			stNew.stTransport.nsAudioInboundPortNo = nValue;

		GetDlgItem(IDC_EDIT_VIDEO_SOURCE_PORT)->GetWindowText(sztext);
		nValue = _ttoi(sztext);
		if(stNew.stTransport.nsVideoSrcPortNo != 0xFFFF && stNew.stTransport.nsVideoSrcPortNo != 0xFFFFFFFF)
			stNew.stTransport.nsVideoSrcPortNo = nValue;

		GetDlgItem(IDC_EDIT_AUDIO_SOURCE_PORT)->GetWindowText(sztext);
		nValue = _ttoi(sztext);
		if(stNew.stTransport.nsAudioSrcPortNo != 0xFFFF && stNew.stTransport.nsAudioSrcPortNo != 0xFFFFFFFF)
			stNew.stTransport.nsAudioSrcPortNo = nValue;



		if(stNew.stTransport.nsTransportProtocolMask != 0xFFFF && stNew.stTransport.nsTransportProtocolMask != 0xFFFFFFFF)
		{
			stNew.stTransport.nsTransportProtocolMask = 0;

			if(m_Check_Protocol_HTTP.GetCheck())
				stNew.stTransport.nsTransportProtocolMask |= (1<<0);
			if(m_Check_Protocol_RTSP.GetCheck())
				stNew.stTransport.nsTransportProtocolMask |= (1<<1);
		}

		if(stNew.stTransport.nsMultiEnable != 0xFFFF && stNew.stTransport.nsMultiEnable != 0xFFFFFFFF)
			stNew.stTransport.nsMultiEnable = GetDlgItem(IDC_RADIO_MULTICAST)->SendMessage(BM_GETCHECK);



		GetDlgItem(IDC_EDIT_USER_TRIGGER_THRESHOLD)->GetWindowText(sztext);
		nValue = _ttoi(sztext);
		if(stNew.stTransport.nsUserTriggerThreshold != 0xFFFF && stNew.stTransport.nsUserTriggerThreshold != 0xFFFFFFFF)
			stNew.stTransport.nsUserTriggerThreshold = nValue;

		GetDlgItem(IDC_EDIT_VIDEO_DEST_PORT)->GetWindowText(sztext);
		nValue = _ttoi(sztext);
		if(stNew.stTransport.nsMultiVideoDestPortNo != 0xFFFF && stNew.stTransport.nsMultiVideoDestPortNo != 0xFFFFFFFF)
			stNew.stTransport.nsMultiVideoDestPortNo = nValue;

		GetDlgItem(IDC_EDIT_AUDIO_DEST_PORT)->GetWindowText(sztext);
		nValue = _ttoi(sztext);
		if(stNew.stTransport.nsMultiAudioDestPortNo != 0xFFFF && stNew.stTransport.nsMultiAudioDestPortNo != 0xFFFFFFFF)
			stNew.stTransport.nsMultiAudioDestPortNo = nValue;

		GetDlgItem(IDC_EDIT_TTL)->GetWindowText(sztext);
		nValue = _ttoi(sztext);
		if(stNew.stTransport.nsTTL != 0xFFFF && stNew.stTransport.nsTTL != 0xFFFFFFFF)
			stNew.stTransport.nsTTL = nValue;

		GetDlgItem(IDC_EDIT_DEST_IPADDR)->GetWindowText(sztext);
		if(strcmp(stNew.stTransport.strMultiDestIpAddr, "NA"))
			StringCopyTo(sztext, stNew.stTransport.strMultiDestIpAddr);


					
		if(stNew.stTransport.nsUniEnble != 0xFFFF && stNew.stTransport.nsUniEnble != 0xFFFFFFFF)
			stNew.stTransport.nsUniEnble = GetDlgItem(IDC_RADIO_UNICAST)->SendMessage(BM_GETCHECK);


		GetDlgItem(IDC_EDIT_UNICAST_INTERFACE_ID)->GetWindowText(sztext);
		if(strcmp(stNew.stTransport.strInterfaceID, "NA"))
			StringCopyTo(sztext, stNew.stTransport.strInterfaceID);


		if(stNew.stTransport.nsUniRtpType != 0xFFFF && stNew.stTransport.nsUniRtpType != 0xFFFFFFFF)
		{
			if(GetDlgItem(IDC_RADIO_UNICAST_UDP)->SendMessage(BM_GETCHECK))
				stNew.stTransport.nsUniRtpType = 0;
			else if(GetDlgItem(IDC_RADIO_UNICAST_TCP)->SendMessage(BM_GETCHECK))
				stNew.stTransport.nsUniRtpType = 1;
		}

		if(stNew.stTransport.nsSecuEnable != 0xFFFF && stNew.stTransport.nsSecuEnable != 0xFFFFFFFF)
			stNew.stTransport.nsSecuEnable = m_Check_SRTP.GetCheck();
	}


	//video
	{
		GetDlgItem(IDC_EDIT_VIDEO_INPUT_CHANNEL_ID)->GetWindowText(sztext);
		if(strcmp(stNew.stVideo.strVideoChannelID, "NA"))
			StringCopyTo(sztext, stNew.stVideo.strVideoChannelID);

		if(stNew.stVideo.nsVideoCodecType != 0xFFFF && stNew.stVideo.nsVideoCodecType != 0xFFFFFFFF) {
			int nSel = m_Combo_CodecType.GetCurSel();
			if (nSel != CB_ERR) {
				stNew.stVideo.nsVideoCodecType = (USHORT)m_Combo_CodecType.GetItemData(nSel);
			}
		}

		if(stNew.stVideo.nsVideoScanType != 0xFFFF && stNew.stVideo.nsVideoScanType != 0xFFFFFFFF) {
			int nSel = m_Combo_ScanType.GetCurSel();
			if (nSel != CB_ERR) {
				stNew.stVideo.nsVideoScanType = (USHORT)m_Combo_ScanType.GetItemData(nSel);
			}
		}


		int nValue = 0;

		int nResolution = m_Combo_Resolution.GetCurSel();
		if(nResolution < m_vResolution.size())
		{
			if(stNew.stVideo.nWidth != 0xFFFF && stNew.stVideo.nWidth != 0xFFFFFFFF)
				stNew.stVideo.nWidth = m_vResolution.at(nResolution).width;

			if(stNew.stVideo.nHeight != 0xFFFF && stNew.stVideo.nHeight != 0xFFFFFFFF)
				stNew.stVideo.nHeight = m_vResolution.at(nResolution).height;
		}




		GetDlgItem(IDC_EDIT_POSITION_X)->GetWindowText(sztext);
		nValue = _ttoi(sztext);
		if(stNew.stVideo.nOffsetX != 0xFFFF && stNew.stVideo.nOffsetX != 0xFFFFFFFF)
			stNew.stVideo.nOffsetX = nValue;

		GetDlgItem(IDC_EDIT_POSITION_Y)->GetWindowText(sztext);
		nValue = _ttoi(sztext);
		if(stNew.stVideo.nOffsetY != 0xFFFF && stNew.stVideo.nOffsetY != 0xFFFFFFFF)
			stNew.stVideo.nOffsetY = nValue;



		int nFrameRate = m_Combo_FrameRate.GetCurSel();
		if(nFrameRate < m_vMaxFrameRate.size())
		{
			if(stNew.stVideo.nsMaxFrameRate != 0xFFFF && stNew.stVideo.nsMaxFrameRate != 0xFFFFFFFF)
				stNew.stVideo.nsMaxFrameRate = m_vMaxFrameRate.at(nFrameRate);
		}
		else
		{
			GetDlgItem(IDC_EDIT_MAX_FRAME_RATE)->GetWindowText(sztext);
			float fvalue = atof(sztext);
			if(stNew.stVideo.nsMaxFrameRate != 0xFFFF && stNew.stVideo.nsMaxFrameRate != 0xFFFFFFFF)
				stNew.stVideo.nsMaxFrameRate = fvalue * 100;
		}


		GetDlgItem(IDC_EDIT_KEY_FRAME_INTERVAL)->GetWindowText(sztext);
		nValue = _ttoi(sztext);
		if(stNew.stVideo.nsKeyFrameItv != 0xFFFF && stNew.stVideo.nsKeyFrameItv != 0xFFFFFFFF)
			stNew.stVideo.nsKeyFrameItv = nValue;

		int nRotation = m_Combo_Rotation.GetCurSel();
		if(nRotation < m_vRotation.size())
		{
			if(stNew.stVideo.nsRotationDegree != 0xFFFF && stNew.stVideo.nsRotationDegree != 0xFFFFFFFF)
				stNew.stVideo.nsRotationDegree = m_vRotation.at(nRotation);
		}




		if(stNew.stVideo.nsMirrorEnable != 0xFFFF && stNew.stVideo.nsMirrorEnable != 0xFFFFFFFF)
			stNew.stVideo.nsMirrorEnable = m_Combo_MirrorEnable.GetCurSel();



		if(stNew.stVideo.nsSnapshotImageType != 0xFFFF && stNew.stVideo.nsSnapshotImageType != 0xFFFFFFFF) {
			int nSel = m_Combo_SnapShotType.GetCurSel();
			if (nSel != CB_ERR) {
				stNew.stVideo.nsSnapshotImageType = (USHORT)m_Combo_SnapShotType.GetItemData(nSel);
			}
		}

		if(stNew.stVideo.nsVideoQCType != 0xFFFF && stNew.stVideo.nsVideoQCType != 0xFFFFFFFF) {
			int nSel = m_Combo_QualityControl.GetCurSel();
			if (nSel != CB_ERR) {
				stNew.stVideo.nsVideoQCType = (USHORT)m_Combo_QualityControl.GetItemData(nSel);
			}
		}



		GetDlgItem(IDC_EDIT_CONSTANT_BITRATE)->GetWindowText(sztext);
		nValue = _ttoi(sztext);
		if(stNew.stVideo.nsConstBitRate != 0xFFFF && stNew.stVideo.nsConstBitRate != 0xFFFFFFFF)
			stNew.stVideo.nsConstBitRate = nValue;

		GetDlgItem(IDC_EDIT_FIXED_QUALITY)->GetWindowText(sztext);
		nValue = _ttoi(sztext);
		if(stNew.stVideo.nsFixedQuality != 0xFFFF && stNew.stVideo.nsFixedQuality != 0xFFFFFFFF)
			stNew.stVideo.nsFixedQuality = nValue;

		GetDlgItem(IDC_EDIT_VBR_UPPER)->GetWindowText(sztext);
		nValue = _ttoi(sztext);
		if(stNew.stVideo.nsvbrUpCap != 0xFFFF && stNew.stVideo.nsvbrUpCap != 0xFFFFFFFF)
			stNew.stVideo.nsvbrUpCap = nValue;

		GetDlgItem(IDC_EDIT_VBR_LOWER)->GetWindowText(sztext);
		nValue = _ttoi(sztext);
		if(stNew.stVideo.nsvbrLowCap != 0xFFFF && stNew.stVideo.nsvbrLowCap != 0xFFFFFFFF)
			stNew.stVideo.nsvbrLowCap = nValue;

	}



	long lret = SPIDER_SetStreamInfo(theApp.m_hSelectCamera, stNew);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));
}


void CStreamInfoDlg::OnBnClickedButtonResolutionSizeChange()
{
	RESOLUTION_SIZE emResSize = RESOLUTION_SIZE_2M;

	int nSel = m_cbResSize.GetCurSel();
	switch (nSel) {
	case 0: emResSize = RESOLUTION_SIZE_2M; break;
	case 1: emResSize = RESOLUTION_SIZE_3M; break;
	case 2: emResSize = RESOLUTION_SIZE_5M; break;
	}
	long nlRet = SPIDER_SetResolutionChange(theApp.m_hSelectCamera, emResSize);
	if (nlRet != E_CTRL_OK) {
		MessageBox(GetErrorString(nlRet), _T("Fail"));
	} else {
		MessageBox(_T("Success."));
		OnOK();
	}
}


void CStreamInfoDlg::OnBnClickedButtonIFrameItvChange()
{
	int nSel = m_List_Stream.GetSelectionMark();
	if (nSel != -1) {
		CString strIFrameItv = _T("");
		m_edtIFrameItv.GetWindowText(strIFrameItv);

		LONG nlTemp[4] = {NULL, };
		nlTemp[nSel] = _ttol(strIFrameItv);

		long nlRet = SPIDER_SetIFrameItv(theApp.m_hSelectCamera, nlTemp[0], nlTemp[1], nlTemp[2], nlTemp[3]);
		if (nlRet != E_CTRL_OK) {
			MessageBox(GetErrorString(nlRet), _T("Fail"));
		} else {
			MessageBox(_T("Success."));
			m_nlIFrameItv[nSel] = nlTemp[nSel];
		}
	}
}
