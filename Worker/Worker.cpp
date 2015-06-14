// Worker.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
//DLL初始化,进入主窗口等,后面可以增加卸载部分
#include <stdint.h>
#include <thread>
#include <process.h>
unsigned int WINAPI ServerThread(void* nListenPort);
//int ServerThread(int nListenPort);

void InitCore()
{
	//不知道为什么标准线程构造函数会阻塞,先用原始WINDOWS线程吧
	//std::thread hThread(testthread, 1000);
	//hThread.detach();
	HANDLE hThread=(HANDLE)_beginthreadex(0, 0, ServerThread, 0, 0, 0);
	CloseHandle(hThread);
}
