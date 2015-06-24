#pragma once
#include <string>
#include <tchar.h>
#include "GameAddr.h"
#include "struct.h"
#include "XVec3.h"

#define MAKEULONG64(a, b)      ((ULONG64)(((DWORD)(((ULONG64)(a)) & 0xffffffff)) | ((ULONG64)((DWORD)(((ULONG64)(b)) & 0xffffffff))) << 32))
#define LOWULONG64(l)           ((DWORD)(((ULONG64)(l)) & 0xffffffff))
#define HIWULONG64(l)           ((DWORD)((((ULONG64)(l)) >> 32) & 0xffffffff))


#ifdef _UNICODE
#define tstring std::wstring
#else	
#define tstring string
#endif


typedef struct tagRecursiveParam{
	DWORD mRetValue;
	float mRange;
	float mCenterRange;
	tstring mObjName;
	int mRecCount;
	int mRecType;
	XVec3* pCenterPos;
	ULONG64 mObjectID;
	DWORD Unknow1;  //����
	DWORD Unknow2;
}RECURSIVEPARAM, *PRECURSIVEPARAM;


class XCall
{
public:
	XCall(void);
	~XCall(void);
public:
	static float Get2P_Dis(float sx,float sy,float dx,float dy);
	
	static DWORD SendGameMessage(DWORD dwMsg,WPARAM wParam,LPARAM lParam);  //������Ϣ�����߳�ִ��

	static tstring UTF2T(char* pUtf8);
public:
	static DWORD GetRoleAddr();  //��ɫ��ַ
	static ULONG64 GetRoleID();  //ȡ��ɫid
	static DWORD GetRolePropertyAddr();  //ȡ��ɫ���Ե�ַ

	static BOOL PressGameKey(DWORD nkey, int nUpDown);  //����call

public: //״̬
	static int GetFightingState();  //��״̬
	static DWORD GetRoleMoveState();  ///�ƶ�״̬����ֵ����0x20004Ϊ���ƶ�����ֹͣΪ20001  ������Ϊ0x20002�����µ���0x20003
public:  //����
	static DWORD GetLearnedSkill1(DWORD skillID);   //ȡ��ѧ���ܵ�ַ1(ȡ��һ�ȼ�����ID)
	static DWORD GetLearnedSkill2(DWORD skillID);   //ȡ��ѧ���ܵ�ַ2
	static DWORD GetLearnedSkill3(DWORD skillID);   //ȡ��ѧ���ܵ�ַ3

	static bool CanReleaseSkill(DWORD slotAddr);		//�жϼ����Ƿ������ͷ�
	//static bool CanReleaseSkill2(DWORD skillID);		//�жϼ����Ƿ������ͷ�

	static DWORD GetBuffSkillAddr(DWORD buffID);    // �������ܵ�ַ

	static BOOL PressSkillKey(int nIndex);  //��ݼ�

	static BOOL MoveSkillToKey(DWORD keyAddr,DWORD skillID);  //�ƶ����ܵ������
	//����CALL
	static BOOL ClickGameKey(DWORD nkey, int nCtrl/* = 0*/);
	static BOOL PressKey(PSUPERKEYINFO pKeyInfo);//�±���������2��,�����ͷ������Ṧ

public:  //����
	static bool ObjectIsFriend(ULONG64 ulObjID);     //�����Ƿ��Ѻ�
	static DWORD GetObjNameAddr(DWORD objAddr);      //ȡ�������ֵ�ַ
	static DWORD GetCollectNameAddr(DWORD objAddr);    //ȡ�ɼ������ֵ�ַ

	static DWORD GetObjProperty(ULONG64 ulObjID);  //ȡ�������Ե�ַ

	static int GetObjMaxFinesse(DWORD proAddr,int nIndex=0);  //ȡ������
	static int GetObjCurFinesse(DWORD proAddr,int nIndex=0);  //ȡ��ǰ����

	static int GetObjMaxBlood(DWORD proAddr);   //���Ѫֵ
	static int GetObjCurBlood(DWORD proAddr);	//��ǰѪֵ

	static int GetObjMaxInternal(DWORD proAddr);   //�����Ϣ
	static int GetObjCurInternal(DWORD proAddr);	//��ǰ��Ϣ

	static int GetObjMaxForce(DWORD proAddr);   //�����
	static int GetObjCurForce(DWORD proAddr);	//��ǰ����

	static int GetObjJob(DWORD proAddr);  //����ְҵ
	static int GetObjLevel(DWORD proAddr);  //����ȼ�

	static DWORD GetCollectItemPos(DWORD collectAddr);  //ȡ�ɼ���Ʒ����

	static BOOL ChangeRoleAngle(PROLEANGLE pChangeAngle);  //�ı��ɫ�����call

	//static BOOL TalkNpc(ULONG64 ulNpcID);   //��npc�Ի�
	static BOOL ObjectCanAttack(ULONG64 ulObjID);   //�����Ƿ��ܹ���
	static BOOL ObjectCanAttack2(ULONG64 ulObjID);   //�����Ƿ��ܹ���

	static int GetObjType(ULONG64 ulObjID);   //ȡ��������call

	static BOOL PickAllItem();   //ȫ����Ʒcall

public:  //Ѱ·
	static BOOL FindPath(float desX,float desY);  //Ѱ·call

	static DWORD GetMapInfoAddr(DWORD mapID);  //ȡ ��ͼ��ϸ��ַ
	static tstring GetMapName(DWORD mapID);   //ȡ��ͼ����
	static DWORD GetAreaNameAddr(DWORD mapID,float desX,float desY);  //ȡ�������ֵ�ַ
	static tstring GetMapAreaName(DWORD mapID,float desX,float desY);   //ȡ��ͼ��������

public:  //�Ự
	static ULONG64 GetResponseNpcID();   //ȡ�Ի�npc��ID
	static DWORD GetObjServerID(ULONG64 objID);  //ȡ���������ID
	
	static DWORD GetResponseItemList();  //ȡ��ǰ�Ựѡ���б��ַ
	static BOOL GetResponseItemState(DWORD responseAddr);  //ȡ�Ựѡ��״̬call

	//��ͨ�ỰnType=4,responseID1��ȡ,responseID2=0,nIndex=npcID1;
	//����ỰnType=3,responseID1-2��ȡ,nIndex=0
	static BOOL PressResponseItem(int nType,DWORD responseID1,DWORD responseID2,int nIndex);  //�Ựѡ��call

public:   //UI
	static DWORD GetUIAddr(DWORD dwFlagAddr);  //ȡUI��ַ
	static DWORD GetUIAddr(TCHAR* szUIName);   //����UI��ַ

	static DWORD GetResponseDlg();    //ȡnpc�Ի��� ��ַ

public:  //����
	static DWORD GetQuestAddr(DWORD questID);  //ȡ�����ַ
	static DWORD GetQuestName(DWORD questID);  //ȡ��������ַ

	static DWORD GetJianWenInfo(DWORD questID);  //ȡ����������ϸ��ַ
	
	static DWORD GetHuaBenProgress(int nQuestIndex);   //ȡ������ɽ��ȵ�ַ

	static BOOL GetJianWenQuest(DWORD questID);   //ȡ��������״̬call


	static BOOL GetPlotEventAcceptState(DWORD EventID);   //Plot Event�Ƿ��ܽ���
	static BOOL GetPlotEventCompleteState(DWORD EventID);   //Plot Event�Ƿ������

public:  //��Ʒ
	static DWORD GetItemAddr(ULONG64 itemID);  //ȡ��Ʒ��ַ
	static void VisitItemList(DWORD CurList, PRECURSIVEPARAM pRecParam);

	static BOOL RightPressSlot(DWORD SlotAddr);   //�����������(������)
	static BOOL LeftPressSlot(DWORD SlotAddr);   //�Ҽ���������(�Ҽ�ʹ����Ʒ,װ��,�������Ʒ)

	//static DWORD GetItemAddr2(ULONG64 itemID);  //ȡ��Ʒ��ַ
	//static BOOL UseGoods(ULONG64 itemID,int nIndex);  //ʹ����Ʒ
	//static BOOL UseEquip(int nIndex);  //ʹ��װ��  index=�����±�

	static BOOL ItemIsGoodsType(DWORD itemAddr);  //��Ʒ�Ƿ��ǻ���
	static BOOL ItemIsEquipType(DWORD itemAddr);  //��Ʒ�Ƿ���װ��
	
	static BOOL EquipCanUse(DWORD itemServerID);  //װ���Ƿ���װ��

	static int GetEquipCurUseAge(DWORD itemAddr);  //��Ʒ��ǰ�;ö�
	static int GetEquipMaxUseAge(DWORD itemAddr);  //��Ʒ����;ö�

	static BOOL GetEquipAttribute(DWORD itemAddr,PITEMATTRIBUTE pItemAttri);  //ȡװ������

	//static DWORD GetItemInfoAddr(DWORD itemID);   //ȡ��Ʒ��ϸ��ַ by������ID

	static BOOL SellItemCall(int nIndex);  //������Ʒcall
	static BOOL BuyItemCall(DWORD ItemId,int nNum);   //����call

public: //���͵�
	static DWORD GetTransferInfoAddr(DWORD transferID);   //ȡ���͵���ϸ��ַ
	static float GetTransferFreezeTime();   //ȡ���͵㶳��ʣ��ʱ��
	static BOOL PressTransferPoint(int transferIndex,DWORD mapID);   //���͵㴫��

public:  //���
	static BOOL InvitePlayerInTeam(DWORD PlayerID1,DWORD PlayerID2,char* szPlayerName);  //������ӷ���
	static BOOL AcceptPlayerInTeam(DWORD PlayerID1,DWORD PlayerID2);  //������ӷ���
	static BOOL PlayerQuitTeam();  //�뿪��ӷ���
	static BOOL ChangeTeamLeader(DWORD PlayerID1,DWORD PlayerID2);  //ת�öӳ�����
	static BOOL KickOutTeam(DWORD PlayerID1,DWORD PlayerID2);		//������鷢��

	static BOOL ChangeThread(DWORD threadID1,DWORD threadID2);   //�л���·

public:  //����
	//��ɫְҵ:1Ϊ̫��,2Ϊ����,3Ϊؤ��,4Ϊ����,0Ϊ����,7Ϊ����
	static BOOL CreateCharacter(char* szCharacterName,int nJob,int nFemale,BYTE* pCharacterData);  //������ɫcall
	static BOOL EnterGame(int nIndex);   //������Ϸ


public:   //����
	static BOOL SendPacket(DWORD dwMsg,char* pData,int nLen);   //����call

	static BOOL RevivePacket(BOOL bSamePlace=FALSE);  //����

	static BOOL JoinMengHui(int nID);  //�����˻�call

	static BOOL DellMail(DWORD mailID1,DWORD mailID2);   //ɾ���ʼ�
	static BOOL TakeAppend(DWORD mailID1,DWORD mailID2);   //��ȡ�ʼ�����
};

extern HWND g_mGhwnd;