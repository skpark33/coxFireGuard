#include "StdAfx.h"
#include "AudioPlayer.h"


CAudioPlayer::CAudioPlayer(void)
{
	ZeroMemory(m_stHeader, sizeof(m_stHeader));
	m_nPlayIndex = 0;
	m_hWaveOut = NULL;	
	ZeroMemory(&m_stFormat, sizeof(m_stFormat));



	pAudioBuf = new BYTE[MAX_DECSIZE];
	memset(pAudioBuf, 0, MAX_DECSIZE);

}

CAudioPlayer::~CAudioPlayer(void)
{
	if(m_hWaveOut)
	{
		for (int i = 0; i < MAX_AUDIO_BUFFERS; i++)
		{			
			if(m_stHeader[i].dwUser)
				waveOutUnprepareHeader(m_hWaveOut, &m_stHeader[i], sizeof(WAVEHDR));
			m_stHeader[i].dwUser = 0;
		}
		
		waveOutClose(m_hWaveOut);
		m_hWaveOut = NULL;
	}


	for (int i = 0; i < MAX_AUDIO_BUFFERS; i++)
	{
		if(m_stHeader[i].lpData)
			delete [] m_stHeader[i].lpData;
		m_stHeader[i].lpData = NULL;
	}


	if(pAudioBuf)
		delete [] pAudioBuf;
	pAudioBuf = NULL;

}

void CAudioPlayer::PlayAudio(ENUM_DATA_TYPE eAudioFormat, BYTE* pInput, DWORD dwFrameSize)
{
	if(dwFrameSize*2 > MAX_DECSIZE)
		return;

	MMRESULT re;
	
	//init
	if(m_hWaveOut == NULL || m_stHeader[0].lpData == NULL)
	{
		if(m_hWaveOut)
		{
			for (int i = 0; i < MAX_AUDIO_BUFFERS; i++)
			{			
				if(m_stHeader[i].dwUser)
					waveOutUnprepareHeader(m_hWaveOut, &m_stHeader[i], sizeof(WAVEHDR));
				m_stHeader[i].dwUser = 0;
			}
			
			waveOutClose(m_hWaveOut);
			m_hWaveOut = NULL;
		}

		for (int i = 0; i < MAX_AUDIO_BUFFERS; i++)
		{
			if(m_stHeader[i].lpData)
				delete [] m_stHeader[i].lpData;
			m_stHeader[i].lpData = NULL;

			ZeroMemory(&m_stHeader[i], sizeof(WAVEHDR));
			m_stHeader[i].lpData = new char[MAX_DECSIZE];
			m_stHeader[i].dwBufferLength = MAX_DECSIZE;
			m_stHeader[i].dwFlags = WHDR_DONE;
			m_stHeader[i].dwLoops = 3;
		}

		m_stFormat.wFormatTag = WAVE_FORMAT_PCM;
		m_stFormat.nChannels = 1;
		m_stFormat.cbSize = 0;
		m_stFormat.nSamplesPerSec = 8000;
		m_stFormat.wBitsPerSample = 16;
		m_stFormat.nBlockAlign = (WORD)(m_stFormat.wBitsPerSample * m_stFormat.nChannels / 8);
		m_stFormat.nAvgBytesPerSec = m_stFormat.nSamplesPerSec * m_stFormat.nBlockAlign;
					
		re = waveOutOpen(&m_hWaveOut, WAVE_MAPPER, &m_stFormat, (DWORD)0, (DWORD)0, CALLBACK_NULL);
		if(re != MMSYSERR_NOERROR )
		{
			int k = 0;
		}
	}

	//playing
	if(pAudioBuf)
		delete [] pAudioBuf;
	pAudioBuf = NULL;

	pAudioBuf = new BYTE[MAX_DECSIZE];
	if(pAudioBuf == NULL)
		return;

	short sdata;
	if(eAudioFormat == E_DATA_AUDIO_ALAW)
	{
		for (ULONG i=0; i< dwFrameSize; i++) 
		{
			sdata = Player_alaw2linear(pInput[i]);	//g.711 alaw

			if(i<<1 >= MAX_DECSIZE)
				break;

			memcpy(&pAudioBuf[i*2], &sdata, 2);
		}
	}
	else if(eAudioFormat == E_DATA_AUDIO_ULAW)
	{
		for (ULONG i=0; i< dwFrameSize; i++) 
		{
			sdata = Player_ulaw2linear(pInput[i]);	//g.711 ulaw

			if(i<<1 >= MAX_DECSIZE)
				break;

			memcpy(&pAudioBuf[i*2], &sdata, 2);
		}
	}
	else
	{
		return;
	}


	DWORD dwDecSize = dwFrameSize*2;

	if (m_nPlayIndex>=MAX_AUDIO_BUFFERS
	||  m_nPlayIndex < 0) 
		m_nPlayIndex = 0;


	if(m_nPlayIndex - 1 < 0)
	{
		if(m_stHeader[MAX_AUDIO_BUFFERS - 1].dwUser)
			waveOutUnprepareHeader(m_hWaveOut, &m_stHeader[MAX_AUDIO_BUFFERS - 1], sizeof(WAVEHDR) );
	}
	else
	{
		if(m_stHeader[m_nPlayIndex - 1].dwUser)
			waveOutUnprepareHeader(m_hWaveOut, &m_stHeader[m_nPlayIndex - 1], sizeof(WAVEHDR) );
	}

	if(m_stHeader[m_nPlayIndex].lpData)
	{
		memcpy((char*)m_stHeader[m_nPlayIndex].lpData, pAudioBuf, dwDecSize);
		m_stHeader[m_nPlayIndex].dwBufferLength = dwDecSize;	
		m_stHeader[m_nPlayIndex].dwUser = 1;
		re = waveOutPrepareHeader(m_hWaveOut, &m_stHeader[m_nPlayIndex], sizeof(WAVEHDR) );
		if(re != MMSYSERR_NOERROR )
		{
			TRACE(L"waveOutPrepareHeader return error\r\n");
		}
		re = waveOutWrite(m_hWaveOut, &m_stHeader[m_nPlayIndex], sizeof(WAVEHDR));
		if(re != MMSYSERR_NOERROR )
		{
			TRACE(L"waveOutWrite return error\r\n");
		}
	}
	m_nPlayIndex++;
}



