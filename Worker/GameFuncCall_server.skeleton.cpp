// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.
#include <tchar.h>
#include "GameFuncCall.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include <thrift/transport/TPipeServer.h>
#include <thrift/TProcessor.h>
#include <thrift/Server/TThreadPoolServer.h>
#include <thrift/concurrency/PlatformThreadFactory.h>
#include "XCall.h"
#include "FunctionCall.h"
using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::thrift::GameCall;
TServer* pServer = nullptr;
extern HMODULE g_hDll;
class GameFuncCallHandler : virtual public GameFuncCallIf 
{
 public:
  GameFuncCallHandler() 
  {
    // Your initialization goes here
  }
  int32_t Test(const int32_t p1, const double p2) 
  {
	  // Your implementation goes here
	//  printf("Test\n");
	  pServer->stop();
	
	//  ::OutputDebugString(L"ggggggggggggggggggggggg");
	  return 0;
  }
#pragma region ��½
  void EnterGame(const int32_t Index) 
  {
    // Your implementation goes here
  //  printf("EnterGame\n");
//	Beep(1000, 1000);
	//  FEnterGame(Index);
	  XCall::EnterGame(Index);
  }
#pragma endregion comment
#pragma region ����
  void GetPlayerInfo(PlayerInfo& _return)
  {
    // Your implementation goes here
   // printf("GetPlayerInfo\n");
	  FGetPlayerInfo(_return);
	//_return.Level = 10;
  }
  void GetMonsterList(std::vector<MonsterInfo> & _return) 
  {
	  // Your implementation goes here
	 // printf("GetMonsterList\n");
	  FGetRoundMonsterInfo();
	  FGetRoundPlayerInfo();
  }
  void GetSkillInfo() 
  {
	  // Your implementation goes here
	 // printf("GetSkillInfo\n");
	  FGetSkillInfo();
  }
#pragma endregion comment
#pragma region ����
  void ChangeAngle(const double angle)
  {
    // Your implementation goes here
   // printf("ChangeAngle\n");
	  FChangeAngle(angle);
  }

  int32_t FindPath(const double x, const double y)
  {
	  // Your implementation goes here
	  //printf("FindPath\n");
	  XCall::FindPath(x, y);
	  return 0;
  }

 // void PressKey(const int32_t msg, const int32_t key)
 // {
	//  // Your implementation goes here
	//  //printf("PressKey\n");
	//  /*
	//  * VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
	//  * 0x40 : unassigned
	//  * VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
	//  */
	//  XCall::PressGameKey(0, key);
	////  VK_LSHIFT;
 // }
  //int32_t PressKey(const int32_t key)
  //{
	 // // Your implementation goes here
	 //// printf("PressKey\n");
	 // XCall::PressGameKey(0,key);
	 // return 0;
  //}
  int32_t PressKey(const int32_t key, const int32_t upordown)
  {
	  // Your implementation goes here//1��UP
	  //printf("PressKey\n");
	  XCall::PressGameKey(key, upordown);
	  return 0;
  }

  int32_t ClickKey(const int32_t key, const int32_t ctrl) 
  {
	  // Your implementation goes here
	 // printf("ClickKey\n");
	  XCall::ClickGameKey(key, ctrl);
	  return 0;
  }
#pragma endregion comment
#pragma region ����
  int32_t LeftPressSlot(const int32_t SlotAddr) 
  {
	  // Your implementation goes here
	 // printf("LeftPressSlot\n");
	  XCall::LeftPressSlot(SlotAddr);
	  return 0;
  }

  int32_t RightPressSlot(const int32_t SlotAddr) 
  {
	  // Your implementation goes here
	 // printf("RightPressSlot\n");
	  XCall::RightPressSlot(SlotAddr);
	  return 0;
  }
#pragma endregion comment
};
#define EVENT_STRING _T("lglglg")
HANDLE hEvent = NULL;

//int ServerThread(int nListenPort)
unsigned int WINAPI ServerThread(void* nListenPort)
{
	DWORD  dwPID = GetCurrentProcessId();
	char buff[] = "GGGG";
	//char buff[32] = { 0 };
	//sprintf(buff, "%dGGGG", dwPID);

	boost::shared_ptr<GameFuncCallHandler> handler(new GameFuncCallHandler());
	boost::shared_ptr<TProcessor> processor(new GameFuncCallProcessor(handler));

	boost::shared_ptr<TServerTransport> serverTransport(new TPipeServer(buff));


	boost::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
	boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

	TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
	pServer = &server;
	//hEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, EVENT_STRING);
	//if (hEvent != NULL)
	//{
	//	SetEvent(hEvent);
	//	CloseHandle(hEvent);
	//}
	Beep(1000, 500);
	server.serve();
	Beep(500, 500);
	::FreeLibraryAndExitThread(g_hDll, 0);
  return 0;
}
