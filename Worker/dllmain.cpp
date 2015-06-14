// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include <tchar.h>
void InitCore();
HMODULE g_hDll;
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		g_hDll =hModule;
		InitCore();
		break;
	//	MessageBox(NULL, _T("hello world"), NULL, MB_OK);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		Beep(2000, 500);
		break;
	}
	return TRUE;
}

