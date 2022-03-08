#pragma once


#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")



#include "Player_g711c.h"
#define MAX_AUDIO_BUFFERS			4
#define MAX_DECSIZE					4096


class CAudioPlayer
{
public:
	CAudioPlayer(void);
	virtual ~CAudioPlayer(void);
	
	
	void PlayAudio(ENUM_DATA_TYPE eAudioFormat, BYTE* pInput, DWORD dwFrameSize);
	
	
	BYTE*			pAudioBuf;
	WAVEHDR			m_stHeader[MAX_AUDIO_BUFFERS];
	INT				m_nPlayIndex;
	HWAVEOUT		m_hWaveOut;	
	WAVEFORMATEX	m_stFormat;
	
	
};
