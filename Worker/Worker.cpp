// Worker.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
//DLL��ʼ��,���������ڵ�,�����������ж�ز���
#include <stdint.h>
#include <thread>
#include <process.h>
unsigned int WINAPI ServerThread(void* nListenPort);
//int ServerThread(int nListenPort);

void InitCore()
{
	//��֪��Ϊʲô��׼�̹߳��캯��������,����ԭʼWINDOWS�̰߳�
	//std::thread hThread(testthread, 1000);
	//hThread.detach();
	HANDLE hThread=(HANDLE)_beginthreadex(0, 0, ServerThread, 0, 0, 0);
	CloseHandle(hThread);
}
