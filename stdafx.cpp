
// stdafx.cpp : source file that includes just the standard includes
// TestDlg.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"



CString GetErrorString(long lret)
{
	CString sztext;

	switch(lret)
	{
	case E_CTRL_INVALID_CAMERA_HANDLE:		sztext = "INVALID_CAMERA_HANDLE		"; break;
	case E_CTRL_NULL_ID:					sztext = "NULL_ID					"; break;
	case E_CTRL_NULL_ARGUMENT:				sztext = "NULL_ARGUMENT				"; break;
	case E_CTRL_FAILED_FIND_ID:				sztext = "FAILED_FIND_ID			"; break;
	case E_CTRL_FAILED_FIND_INDEX:			sztext = "FAILED_FIND_INDEX			"; break;
	case E_CTRL_FAILED_SEND_PACKET:			sztext = "FAILED_SEND_PACKET		"; break;
	case E_CTRL_FAILED_PARSING_RESPONSE:	sztext = "FAILED_PARSING_RESPONSE	"; break;
	case E_CTRL_FAILED_AUTH_USER:			sztext = "FAILED_AUTH_USER	(not authorized user info. check user id & password)"; break;
	case E_CTRL_NOT_SUPPORTED:				sztext = "NOT_SUPPORTED				"; break;
	case E_CTRL_BAD_REQUEST:				sztext = "BAD_REQUEST				"; break;
	case E_CTRL_FAIL:						sztext = "FAIL						"; break;
	case E_CTRL_FAILED_UPDATE_CAMERA	:	sztext = "FAILED_UPDATE_CAMERA		"; break;
	case E_CTRL_INVALID_SERVER_HANDLE	:	sztext = "INVALID_SERVER_HANDLE		"; break;
	case E_CTRL_FAILED_CREATE_SOCK		:	sztext = "FAILED_CREATE_SOCK (check network status of camera or pc.)"; break;
	case E_CTRL_NODATA					:	sztext = "NODATA						"; break;
	case E_CTRL_FAILED_CONNECT			:	sztext = "FAILED_CONNECT	(or disconnected)"; break;
	case E_CTRL_FAILED_WAIT_RESPONSE:		sztext = "FAILED_WAIT_RESPONSE	(time-out)	"; break;
	default:								sztext.Format(("FAIL (undefined code %d)"), lret); break;
	}

	return sztext;
}

bool StringCopyTo(CString str, LPSTR szDest)
{
	strcpy(szDest, str.GetBuffer());
	str.ReleaseBuffer();
	return true;
}

////유니코드에서 ANSI 문자열로 변환
//bool StringCopyTo(LPCWSTR szUniStr, LPSTR szAnsi)
//{ 
//	if(szAnsi == NULL)
//		return false;
//
//	int nLen = WideCharToMultiByte(CP_ACP, 0, szUniStr, -1, NULL, 0, NULL, NULL);
//
//	memset(szAnsi,0,nLen+1);
//	
//	WideCharToMultiByte(CP_ACP, 0, szUniStr, -1, szAnsi, nLen, NULL, NULL);
//	
//	return true;
//}

//
//bool StringCopyTo(LPWSTR szUniStr, LPSTR szAnsi, DWORD dwAnsiBufferLen)
//{ 
//	if(szAnsi == NULL)
//		return false;
//
//	int nLen = WideCharToMultiByte(CP_ACP, 0, szUniStr, -1, NULL, 0, NULL, NULL);
//
//	memset(szAnsi,0,dwAnsiBufferLen);
//	
//	WideCharToMultiByte(CP_ACP, 0, szUniStr, -1, szAnsi, dwAnsiBufferLen, NULL, NULL);
//	
//	return true;
//}