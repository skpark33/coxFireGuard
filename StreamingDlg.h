#pragma once

#include "AudioPlayer.h" // GON
// CStreamingDlg dialog

class CStreamingDlg : public CDialog
{
	DECLARE_DYNAMIC(CStreamingDlg)

public:
	CStreamingDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CStreamingDlg();

// Dialog Data
	enum { IDD = IDD_STREAMING };


	bool StartStreaming(char* rtspurl);
	void StopStreaming();
	void StreamProc();

protected:
	static UINT __stdcall StreamThread(void* pParam);

	void GetFrameData(HSTREAM hStream);

	void _AddDataToDraw(int dwLen, PBYTE pFrameData);
	void _RecvFrameData(HSTREAM hStream, int nType, unsigned int len, PBYTE pFrameData, bool bAudio);

public:
	HSTREAM		m_hStream;

protected:
	HANDLE		m_hStreamEvent;
	HANDLE		m_hStreamThread;
	UINT		m_nStreamThreadID;
	HANDLE		m_hStreamThreadStopFlag;

	UINT		m_dwWidth;
	UINT		m_dwHeight;

	CAudioPlayer m_AudioPlayer; // GON
	BOOL		m_bAudioPlay;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
	afx_msg LRESULT OnStreaming(WPARAM wParam, LPARAM lParam );
	afx_msg void OnDestroy();
	afx_msg void OnClose();
};
