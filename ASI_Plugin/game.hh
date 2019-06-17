#pragma once

#include <Windows.h>

struct stInputInfo
{
	void* pD3DDevice;
	void* pDXUTDialog;
	void* pDXUTEditBox;
	void* pCMDs[ 144 ];
	char szCMDNames[ 144 ][ 33 ];
	int iCMDCount;
	int iInputEnabled;
	char szInputBuffer[ 129 ];
	char szRecallBufffer[ 10 ][ 129 ];
	char szCurrentBuffer[ 129 ];
	int iCurrentRecall;
	int iTotalRecalls;
	void* pszDefaultCMD;
};

enum
{
	SAMP_DEVICE					= 0xC97C28 ,
	SAMP_MISC_INFO				= 0x21A10C ,
	SAMP_GAMESTATE				= 0xC8D4C0 ,
	SAMP_TOGGLECURSOR			= 0x09BD30 ,
	SAMP_CURSORUNLOCKACTORCAM	= 0x09BC10 ,
	SAMP_CHAT_INPUT				= 0x21A0E8 ,

	DEVICE_ENDSCENE				= 42,
	DEVICE_PRESENT				= 17,
	DEVICE_RESET				= 16,
};

extern DWORD		g_dwSAMP;
extern stInputInfo* g_stInput;

extern auto ToggleCursor( int mode ) -> void;