// StreamingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDlg.h"
#include "StreamingDlg.h"
#include "TestDlgDlg.h"
#include <process.h>


// CStreamingDlg dialog

IMPLEMENT_DYNAMIC(CStreamingDlg, CDialog)

CStreamingDlg::CStreamingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStreamingDlg::IDD, pParent)
{
	m_hStream				= NULL;

	m_hStreamEvent			= NULL;
	m_hStreamThread			= NULL;
	m_nStreamThreadID		= 0;
	m_hStreamThreadStopFlag = NULL;

	m_dwWidth				= 0;
	m_dwHeight				= 0;
}

CStreamingDlg::~CStreamingDlg()
{
	StopStreaming();
}

void CStreamingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStreamingDlg, CDialog)
	ON_MESSAGE(WM_STREAM, OnStreaming)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CStreamingDlg message handlers


bool CStreamingDlg::StartStreaming(char* rtspurl)
{
	bool bRet = false;

	m_bAudioPlay = TRUE;

//	int nDecompressType = 0;	//yuv420 = 0
	int nDecompressType = 1;	//rgb = 1
//	int nDecompressType = 0xFF;	//do not decom = 0xFF

	StopStreaming();

#if 0
	//Get Streaming Data through Window Message
	m_hStream = SPIDER_CreateStreamingHandle(GetSafeHwnd(), NULL, rtspurl, NULL, NULL, 0, nDecompressType);
#else
	m_hStreamThread = (HANDLE)_beginthreadex(NULL, 0, StreamThread, this, CREATE_SUSPENDED, &m_nStreamThreadID);
	if (m_hStreamThread) {
		m_hStreamThreadStopFlag = CreateEvent(NULL, TRUE, FALSE, NULL);

		//Get Streaming Data through Event
		m_hStreamEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

		ResumeThread(m_hStreamThread);

		//make sure that call SPIDER_InitStreaming() at beginning of process.
		m_hStream = SPIDER_CreateStreamingHandle(NULL, m_hStreamEvent, rtspurl, NULL, NULL, 0, nDecompressType);
	}
#endif

	if (m_hStream) {
		if (SPIDER_StartStreaming(m_hStream) == E_CTRL_OK) {
			bRet = true;
		} else {
			SPIDER_DestroyStreamingHandle(m_hStream);
			m_hStream = NULL;
		}
	}

	return bRet;
}

void CStreamingDlg::StopStreaming()
{
	if (m_hStreamThreadStopFlag) {
		SetEvent(m_hStreamThreadStopFlag);
	}

	if (m_hStreamThread) {
		WaitForSingleObject(m_hStreamThread, INFINITE);
		CloseHandle(m_hStreamThread);
		m_hStreamThread = NULL;
	}
	m_nStreamThreadID = 0;

	if (m_hStreamThreadStopFlag) {
		CloseHandle(m_hStreamThreadStopFlag);
		m_hStreamThreadStopFlag = NULL;
	}

	if (m_hStream) {
		SPIDER_StopStreaming(m_hStream);
		SPIDER_DestroyStreamingHandle(m_hStream);
		m_hStream = NULL;
	}

	if (m_hStreamEvent) {
		CloseHandle(m_hStreamEvent);
		m_hStreamEvent = NULL;
	}

	m_dwWidth	= 0;
	m_dwHeight	= 0;
}

LRESULT CStreamingDlg::OnStreaming(WPARAM wParam, LPARAM lParam )
{
	HSTREAM hStream = (HSTREAM)wParam;

	if (hStream) {
		GetFrameData(hStream);
	}

	return 0;
}

UINT __stdcall CStreamingDlg::StreamThread(void* pParam)
{
	CStreamingDlg* pStreamingDlg = (CStreamingDlg*)pParam;
	pStreamingDlg->StreamProc();
	_endthreadex(0);
	return 0;
}

void CStreamingDlg::StreamProc()
{
	HANDLE hWaits[2] = {NULL, };
	hWaits[0] = m_hStreamThreadStopFlag;
	hWaits[1] = m_hStreamEvent;

	DWORD dwWaitResult = WAIT_TIMEOUT;

	do {
		dwWaitResult = WaitForMultipleObjects(_countof(hWaits), hWaits, FALSE, INFINITE);
		if (dwWaitResult != WAIT_OBJECT_0) {
			GetFrameData(m_hStream);
		}

	} while (dwWaitResult != WAIT_OBJECT_0);	
}

void CStreamingDlg::GetFrameData(HSTREAM hStream)
{
	int nType	= 0;
	UINT nLen	= 0;
	bool bAudio	= 0;
	PBYTE pFrame = NULL;

	long nlResult = SPIDER_GetFrameData(m_hStream, &nType, &nLen, pFrame, &bAudio);
	if (nlResult == E_CTRL_INSUFFICIENT_BUFFER) {
		if (nLen > 0) {
			pFrame = new BYTE[nLen];
		}
		nlResult = SPIDER_GetFrameData(m_hStream, &nType, &nLen, pFrame, &bAudio);
	}

	if (nlResult == E_CTRL_OK) {
		_RecvFrameData(hStream, nType, nLen, pFrame, bAudio);
	} else if (nlResult == E_CTRL_NODATA) {
		ResetEvent(m_hStreamEvent);
	}

	if (pFrame) {
		delete [] pFrame;
	}
}

void CStreamingDlg::_RecvFrameData(HSTREAM hStream, int nType, unsigned int len, PBYTE pFrameData, bool bAudio)
{
	CString sztype;
	if(nType == E_DATA_CHANGERESOLUTION)
	{
		SPIDER_GetResolution(hStream, &m_dwWidth, &m_dwHeight);
		TRACE("Change Resolution %d, %d\r\n", m_dwWidth, m_dwHeight);
	}
	else if(nType == E_DATA_DISCONNECTED)
	{
		TRACE("Disconnected.....\r\n");

		if(m_hStream == hStream)
		{
			SPIDER_StopStreaming(m_hStream);
			SPIDER_DestroyStreamingHandle(m_hStream);
			m_hStream = NULL;
		}

		MessageBox(("Streaming Stopped. Disconnected."));
		if(theApp.m_pMainWnd)
			((CTestDlgDlg*)theApp.m_pMainWnd)->GetDlgItem(IDC_BUTTON_STREAMING)->SetWindowText(("Start Streaming"));
	}
	else
	{
		if( (nType == E_DATA_AUDIO_UNDEFINED)||
			(nType == E_DATA_AUDIO_ALAW)	||
			(nType == E_DATA_AUDIO_ULAW)	||
			(nType == E_DATA_AUDIO_G726)
			)
		{			
			if ( m_bAudioPlay )
			{
				if(nType == E_DATA_AUDIO_UNDEFINED)
					m_AudioPlayer.PlayAudio(E_DATA_AUDIO_ALAW, pFrameData, len);
				else
					m_AudioPlayer.PlayAudio((ENUM_DATA_TYPE)nType, pFrameData, len);
			}
		}	
		else
		{
			_AddDataToDraw(len, pFrameData);
		}		
	}
}

void CStreamingDlg::_AddDataToDraw(int dwLen, PBYTE pFrameData)
{
	if(GetSafeHwnd() == NULL)
		return;

	if (pFrameData) {
		RECT rc;
		GetClientRect(&rc);
		CDC* pDC = GetDC();
		HDC hdc = pDC->GetSafeHdc();


		BITMAPINFO bmi = {0};
		bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth       = m_dwWidth;
		bmi.bmiHeader.biHeight      = m_dwHeight;
		bmi.bmiHeader.biPlanes      = 1;
		bmi.bmiHeader.biBitCount    = 24;
		bmi.bmiHeader.biCompression = BI_RGB;
		bmi.bmiHeader.biSizeImage   = dwLen;

		HDC hComDC = ::CreateCompatibleDC(hdc);
		HBITMAP hBitmap = ::CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
		HBITMAP hOld = (HBITMAP)SelectObject(hComDC, hBitmap);

		SetStretchBltMode(hComDC, HALFTONE);
		int iRet = ::StretchDIBits(hComDC, 0, 0, rc.right, rc.bottom,
			0, 0, bmi.bmiHeader.biWidth, bmi.bmiHeader.biHeight, pFrameData, &bmi, DIB_RGB_COLORS, SRCCOPY);

		if (iRet == GDI_ERROR)
			TRACE("Failed to draw video stream...\r\n");


		BOOL bret = BitBlt(hdc, 0, 0, rc.right, rc.bottom, hComDC, 0, 0, SRCCOPY);

		SelectObject(hComDC, hOld);
		DeleteDC(hComDC);
		DeleteObject(hBitmap);

		ReleaseDC(pDC);
	}
}

void CStreamingDlg::OnDestroy()
{
	StopStreaming();
	CDialog::OnDestroy();
}


void CStreamingDlg::OnClose()
{
	CWnd* pwndParent = GetParent();
	if (pwndParent) {
		pwndParent->SendMessage(WM_COMMAND, MAKEWPARAM(IDC_BUTTON_STREAMING, BN_CLICKED), (LPARAM)GetSafeHwnd());
	}
}
