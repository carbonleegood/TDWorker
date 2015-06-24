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
	DWORD Unknow1;  //备用
	DWORD Unknow2;
}RECURSIVEPARAM, *PRECURSIVEPARAM;


class XCall
{
public:
	XCall(void);
	~XCall(void);
public:
	static float Get2P_Dis(float sx,float sy,float dx,float dy);
	
	static DWORD SendGameMessage(DWORD dwMsg,WPARAM wParam,LPARAM lParam);  //发送信息到主线程执行

	static tstring UTF2T(char* pUtf8);
public:
	static DWORD GetRoleAddr();  //角色地址
	static ULONG64 GetRoleID();  //取角色id
	static DWORD GetRolePropertyAddr();  //取角色属性地址

	static BOOL PressGameKey(DWORD nkey, int nUpDown);  //按键call

public: //状态
	static int GetFightingState();  //打斗状态
	static DWORD GetRoleMoveState();  ///移动状态返回值＝＝0x20004为在移动。。停止为20001  往上跳为0x20002，往下掉落0x20003
public:  //技能
	static DWORD GetLearnedSkill1(DWORD skillID);   //取已学技能地址1(取下一等级技能ID)
	static DWORD GetLearnedSkill2(DWORD skillID);   //取已学技能地址2
	static DWORD GetLearnedSkill3(DWORD skillID);   //取已学技能地址3

	static bool CanReleaseSkill(DWORD slotAddr);		//判断技能是否在以释放
	//static bool CanReleaseSkill2(DWORD skillID);		//判断技能是否在以释放

	static DWORD GetBuffSkillAddr(DWORD buffID);    // 辅助技能地址

	static BOOL PressSkillKey(int nIndex);  //快捷键

	static BOOL MoveSkillToKey(DWORD keyAddr,DWORD skillID);  //移动技能到快捷栏
	//按键CALL
	static BOOL ClickGameKey(DWORD nkey, int nCtrl/* = 0*/);
	static BOOL PressKey(PSUPERKEYINFO pKeyInfo);//陈斌新增的那2个,用于释放闪避轻功

public:  //对像
	static bool ObjectIsFriend(ULONG64 ulObjID);     //对像是否友好
	static DWORD GetObjNameAddr(DWORD objAddr);      //取对像名字地址
	static DWORD GetCollectNameAddr(DWORD objAddr);    //取采集物名字地址

	static DWORD GetObjProperty(ULONG64 ulObjID);  //取对像属性地址

	static int GetObjMaxFinesse(DWORD proAddr,int nIndex=0);  //取最大机巧
	static int GetObjCurFinesse(DWORD proAddr,int nIndex=0);  //取当前机巧

	static int GetObjMaxBlood(DWORD proAddr);   //最大血值
	static int GetObjCurBlood(DWORD proAddr);	//当前血值

	static int GetObjMaxInternal(DWORD proAddr);   //最大内息
	static int GetObjCurInternal(DWORD proAddr);	//当前内息

	static int GetObjMaxForce(DWORD proAddr);   //最大定力
	static int GetObjCurForce(DWORD proAddr);	//当前定力

	static int GetObjJob(DWORD proAddr);  //对像职业
	static int GetObjLevel(DWORD proAddr);  //对像等级

	static DWORD GetCollectItemPos(DWORD collectAddr);  //取采集物品坐标

	static BOOL ChangeRoleAngle(PROLEANGLE pChangeAngle);  //改变角色面向角call

	//static BOOL TalkNpc(ULONG64 ulNpcID);   //和npc对话
	static BOOL ObjectCanAttack(ULONG64 ulObjID);   //对像是否能攻击
	static BOOL ObjectCanAttack2(ULONG64 ulObjID);   //对像是否能攻击

	static int GetObjType(ULONG64 ulObjID);   //取对像类型call

	static BOOL PickAllItem();   //全捡物品call

public:  //寻路
	static BOOL FindPath(float desX,float desY);  //寻路call

	static DWORD GetMapInfoAddr(DWORD mapID);  //取 地图详细地址
	static tstring GetMapName(DWORD mapID);   //取地图名字
	static DWORD GetAreaNameAddr(DWORD mapID,float desX,float desY);  //取城镇名字地址
	static tstring GetMapAreaName(DWORD mapID,float desX,float desY);   //取地图城镇名字

public:  //会话
	static ULONG64 GetResponseNpcID();   //取对话npc的ID
	static DWORD GetObjServerID(ULONG64 objID);  //取对像服务器ID
	
	static DWORD GetResponseItemList();  //取当前会话选项列表地址
	static BOOL GetResponseItemState(DWORD responseAddr);  //取会话选项状态call

	//普通会话nType=4,responseID1可取,responseID2=0,nIndex=npcID1;
	//任务会话nType=3,responseID1-2可取,nIndex=0
	static BOOL PressResponseItem(int nType,DWORD responseID1,DWORD responseID2,int nIndex);  //会话选项call

public:   //UI
	static DWORD GetUIAddr(DWORD dwFlagAddr);  //取UI地址
	static DWORD GetUIAddr(TCHAR* szUIName);   //查找UI地址

	static DWORD GetResponseDlg();    //取npc对话框 地址

public:  //任务
	static DWORD GetQuestAddr(DWORD questID);  //取任务地址
	static DWORD GetQuestName(DWORD questID);  //取任务名地址

	static DWORD GetJianWenInfo(DWORD questID);  //取见闻任务详细地址
	
	static DWORD GetHuaBenProgress(int nQuestIndex);   //取话本完成进度地址

	static BOOL GetJianWenQuest(DWORD questID);   //取见闻任务状态call


	static BOOL GetPlotEventAcceptState(DWORD EventID);   //Plot Event是否能接受
	static BOOL GetPlotEventCompleteState(DWORD EventID);   //Plot Event是否能完成

public:  //物品
	static DWORD GetItemAddr(ULONG64 itemID);  //取物品地址
	static void VisitItemList(DWORD CurList, PRECURSIVEPARAM pRecParam);

	static BOOL RightPressSlot(DWORD SlotAddr);   //左键操作容器(左键点击)
	static BOOL LeftPressSlot(DWORD SlotAddr);   //右键操作容器(右键使用物品,装备,或出售物品)

	//static DWORD GetItemAddr2(ULONG64 itemID);  //取物品地址
	//static BOOL UseGoods(ULONG64 itemID,int nIndex);  //使用物品
	//static BOOL UseEquip(int nIndex);  //使用装备  index=容器下标

	static BOOL ItemIsGoodsType(DWORD itemAddr);  //物品是否是货物
	static BOOL ItemIsEquipType(DWORD itemAddr);  //物品是否是装备
	
	static BOOL EquipCanUse(DWORD itemServerID);  //装备是否能装备

	static int GetEquipCurUseAge(DWORD itemAddr);  //物品当前耐久度
	static int GetEquipMaxUseAge(DWORD itemAddr);  //物品最大耐久度

	static BOOL GetEquipAttribute(DWORD itemAddr,PITEMATTRIBUTE pItemAttri);  //取装备属性

	//static DWORD GetItemInfoAddr(DWORD itemID);   //取物品详细地址 by服务器ID

	static BOOL SellItemCall(int nIndex);  //出售物品call
	static BOOL BuyItemCall(DWORD ItemId,int nNum);   //购买call

public: //传送点
	static DWORD GetTransferInfoAddr(DWORD transferID);   //取传送点详细地址
	static float GetTransferFreezeTime();   //取传送点冻结剩余时间
	static BOOL PressTransferPoint(int transferIndex,DWORD mapID);   //传送点传送

public:  //组队
	static BOOL InvitePlayerInTeam(DWORD PlayerID1,DWORD PlayerID2,char* szPlayerName);  //邀请组队发包
	static BOOL AcceptPlayerInTeam(DWORD PlayerID1,DWORD PlayerID2);  //接受组队发包
	static BOOL PlayerQuitTeam();  //离开组队发包
	static BOOL ChangeTeamLeader(DWORD PlayerID1,DWORD PlayerID2);  //转让队长发包
	static BOOL KickOutTeam(DWORD PlayerID1,DWORD PlayerID2);		//请离队伍发包

	static BOOL ChangeThread(DWORD threadID1,DWORD threadID2);   //切换线路

public:  //登入
	//角色职业:1为太白,2为神威,3为丐帮,4为唐门,0为真武,7为天香
	static BOOL CreateCharacter(char* szCharacterName,int nJob,int nFemale,BYTE* pCharacterData);  //创建角色call
	static BOOL EnterGame(int nIndex);   //登入游戏


public:   //发包
	static BOOL SendPacket(DWORD dwMsg,char* pData,int nLen);   //发包call

	static BOOL RevivePacket(BOOL bSamePlace=FALSE);  //复活

	static BOOL JoinMengHui(int nID);  //加入盟会call

	static BOOL DellMail(DWORD mailID1,DWORD mailID2);   //删除邮件
	static BOOL TakeAppend(DWORD mailID1,DWORD mailID2);   //提取邮件附件
};

extern HWND g_mGhwnd;