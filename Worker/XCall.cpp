#include "StdAfx.h"
#include "XCall.h"
#include <math.h>
#include "utf8.h"
HWND g_mGhwnd = 0;
XCall::XCall(void)
{
}

XCall::~XCall(void)
{
}
float XCall::Get2P_Dis(float sx,float sy,float dx,float dy)
{
	return sqrt(pow((dx-sx),2) + pow((dy-sy),2));
}
DWORD XCall::SendGameMessage(DWORD dwMsg,WPARAM wParam,LPARAM lParam)  //发送信息到主线程执行
{
	GAMEDATASTRUCT gamedata;
	gamedata.wParam = (WPARAM)wParam;
	gamedata.lParam = (LPARAM)lParam;
	gamedata.lResult = 0;
	::SendMessage(g_mGhwnd,dwMsg,(WPARAM)&gamedata,(LPARAM)0xDEAD);
	return gamedata.lResult;
}

tstring XCall::UTF2T(char* pUtf8)
{
	tstring nRet;
	try
	{
		if (!IsBadReadPtr((void*)pUtf8, 4))
		{
			USES_CONVERSION;
			nRet = UTF82T(pUtf8);
		}
	}
	catch (...){}
	return nRet;
}
DWORD XCall::GetRoleAddr()  //角色地址
{
	DWORD nRet = 0;
	__try
	{
		DWORD roleAddr = *(DWORD*)GAME_BASE;
		if(IsBadReadPtr((void*)roleAddr ,4))
			return nRet;
		nRet = *(DWORD*)(roleAddr + MAN_PLAYER_ADDR_OS);
		if(IsBadReadPtr((void*)nRet ,4))
			nRet = 0;
	}__except(1){};
	return nRet;
}
ULONG64 XCall::GetRoleID()  //取角色id
{
	ULONG64 nRet = 0;
	__try
	{
		DWORD GameAddr = XCall::GetRoleAddr();
		if(GameAddr)
			nRet = *(ULONG64*)(GameAddr + OBJECT_ID_OS);
	}__except(1){};
	return nRet;
}
DWORD XCall::GetRolePropertyAddr()  //取角色属性地址
{
	DWORD nRet = 0;
	__try
	{
		ULONG64 roleID = XCall::GetRoleID();
		if(roleID == 0)
			return nRet;
		nRet = XCall::GetObjProperty(roleID);
	}__except(1){};
	return nRet;
}



BOOL XCall::PressGameKey(DWORD nkey, int nUpDown)  //按键call
{
	BOOL nRet = FALSE;
	__try
	{
		DWORD GameAddr = *(DWORD*)GAME_MSG_BASE;
		if(IsBadReadPtr((void*)GameAddr ,4))
			return nRet;
		DWORD GameHwn = *(DWORD*)(GameAddr + 4);
		if(GameHwn == 0)
			return nRet;

		DWORD lparam  = 0;
		DWORD mapCode = MapVirtualKey(nkey,0);
		lparam = mapCode <<16;
		lparam &= 0x1FF0000;
		++lparam;
		DWORD lparam2 = lparam|0xC0000000;

		DWORD GameCall1 = PRESS_KEY_DOWN_CALL;
		DWORD GameCall2 = PRESS_KEY_UP_CALL;
		if (nUpDown == 1)
		{
			__asm
			{
				push lparam;
				push nkey;
				push 102;
				push GameHwn;
				MOV ECX, GameAddr;
				CALL GameCall2;
			}
		}
		else
		{
			__asm
			{
				push lparam2;
				push nkey;
				push 101;
				push GameHwn;
				MOV ECX, GameAddr;
				CALL GameCall1;
			}
		}
		nRet = TRUE;
	}__except(1){};
	return nRet;
}

//状态
int XCall::GetFightingState()  //打斗状态
{
	int nRet = -1;
	__try
	{
		DWORD roleAddr = XCall::GetRoleAddr();
		if(IsBadReadPtr((void*)roleAddr ,4))
			return nRet;
		nRet = *(int*)(roleAddr + FIGHTING_STATE_OS);
	}__except(1){};
	return nRet;
}
DWORD XCall::GetRoleMoveState()  ///移动状态 返回值＝＝0x20004为在移动。。停止为20001  往上跳为0x20002，往下掉落0x20003
{
	DWORD nRet = 0;
	__try
	{
		DWORD roleAddr = XCall::GetRoleAddr();
		if(IsBadReadPtr((void*)roleAddr ,4))
			return nRet;
		roleAddr = *(int*)(roleAddr + MOVE_STATE_ADDR_OS);
		if(IsBadReadPtr((void*)roleAddr ,4))
			return nRet;
		nRet = *(DWORD*)(roleAddr + 8);
	}__except(1){};
	return nRet;
}
DWORD XCall::GetLearnedSkill1(DWORD skillID)   //取已学技能地址1
{
	DWORD nRet = 0;
	__try
	{
		if(skillID == 0 || skillID == -1)
			return nRet;
		DWORD GameAddr = *(DWORD*)GAME_BASE;
		if(IsBadReadPtr((void*)GameAddr,4))
			return nRet;
		GameAddr = *(DWORD*)(GameAddr + LEARNED_SKILL_ARRARY_OS1);
		if(IsBadReadPtr((void*)GameAddr,4))
			return nRet;

		DWORD GameCall = GET_LEARNED_SKILL_CALL1;
		__asm
		{
			MOV ECX,GameAddr;
			push skillID;
			CALL GameCall;
			MOV nRet,EAX;
		}
		if(IsBadReadPtr((void*)nRet ,4))
			nRet = 0;
	}__except(1){};
	return nRet;
}
DWORD XCall::GetLearnedSkill2(DWORD skillID)   //取已学技能地址2
{
	DWORD nRet = 0;
	__try
	{
		if(skillID == 0 || skillID == -1)
			return nRet;
		DWORD GameAddr = *(DWORD*)GAME_BASE;
		if(IsBadReadPtr((void*)GameAddr,4))
			return nRet;
		GameAddr = *(DWORD*)(GameAddr + LEARNED_SKILL_ARRARY_OS2);
		if(IsBadReadPtr((void*)GameAddr,4))
			return nRet;

		DWORD GameCall = GET_LEARNED_SKILL_CALL2;
		__asm
		{
			MOV ECX,GameAddr;
			push skillID;
			CALL GameCall;
			MOV nRet,EAX;
		}
		if(IsBadReadPtr((void*)nRet ,4))
			nRet = 0;
	}__except(1){};
	return nRet;
}

DWORD XCall::GetLearnedSkill3(DWORD skillID)   //取已学技能地址3
{
	DWORD nRet = 0;
	__try
	{
		if(skillID == 0 || skillID == -1)
			return nRet;
		DWORD GameAddr = *(DWORD*)GAME_BASE;
		if(IsBadReadPtr((void*)GameAddr,4))
			return nRet;
		GameAddr = *(DWORD*)(GameAddr + LEARNED_SKILL_ARRARY_OS1);
		if(IsBadReadPtr((void*)GameAddr,4))
			return nRet;

		DWORD GameCall = GET_LEARNED_SKILL_CALL3;
		__asm
		{
			MOV ECX,GameAddr;
			push skillID;
			CALL GameCall;
			MOV nRet,EAX;
		}
		if(IsBadReadPtr((void*)nRet ,4))
			nRet = 0;
	}__except(1){};
	return nRet;
}

bool XCall::CanReleaseSkill(DWORD slotAddr)		//判断技能是否在以释放
{
	bool nRet = false;
	__try
	{
		if (IsBadReadPtr((void*)slotAddr,4))
			return nRet;
		int freezeflag = (int)*(BYTE*)(slotAddr + SLOT_SKILL_FREEZE_FLAG_OS);   //是否冻结
		int disableFlag = (int)*(BYTE*)(slotAddr + SLOT_SKILL_DISABLE_FLAG_OS);  //是否禁用,(周围没怪,等情况)
		if (freezeflag == 0 && disableFlag == 0)
			nRet = true;

	}
	__except (1){};
	return nRet;
}

//bool XCall::CanReleaseSkill2(DWORD skillID)		//判断技能是否在以释放
//{
//	bool nRet = false;
//	__try
//	{
//		if(skillID == 0 || skillID == -1)
//			return nRet;
//		DWORD GameAddr = *(DWORD*)GAME_BASE;
//		if(IsBadReadPtr((void*)GameAddr,4))
//			return nRet;
//		GameAddr = *(DWORD*)(GameAddr + MAN_PLAYER_ADDR_OS);
//		if(IsBadReadPtr((void*)GameAddr,4))
//			return nRet;
//
//		DWORD GameCall = CAN_RELEASE_SKILL_CALL;
//		__asm
//		{
//			MOV ECX,GameAddr;
//			push skillID;
//			CALL GameCall;
//			MOV nRet,AL;
//		}
//
//	}__except(1){};
//	return nRet;
//}
DWORD XCall::GetBuffSkillAddr(DWORD buffID)    // 辅助技能地址
{
	DWORD nRet = 0;
	__try
	{
		if(buffID == 0 || buffID == -1)
			return nRet;
		DWORD GameAddr = *(DWORD*)GAME_BASE;
		if(IsBadReadPtr((void*)GameAddr,4))
			return nRet;
		GameAddr = *(DWORD*)(GameAddr + BUFF_SKILL_LIST_OS);
		if(IsBadReadPtr((void*)GameAddr,4))
			return nRet;

		DWORD GameCall = GET_BUFF_SKILL_ADDR_CALL;
		__asm
		{
			MOV ECX,GameAddr;
			push buffID;
			CALL GameCall;
			MOV nRet,EAX;
		}
		if(IsBadReadPtr((void*)nRet ,4))
			nRet = 0;
	}__except(1){};
	return nRet;
}

BOOL XCall::PressSkillKey(int nIndex)  //快捷键
{
	BOOL nRet = FALSE;
	__try
	{
		if( nIndex < 0)
			return nRet;
		DWORD tmpKey[0x50]={0};


		DWORD GameCall1 = GET_KEY_FUNCTION_ADDR_CALL;
		DWORD GameCall2 = KEY_FUNCTION_CALL;
		__asm
		{
			MOV ECX,tmpKey;
			push ECX;
			CALL GameCall1;
			ADD ESP,4;
			MOV ECX,tmpKey;
			MOV ECX,DWORD PTR [ECX];
			TEST ECX,ECX;
			JE PressSkillKey_Exit;
			push 0;
			push 1;
			push nIndex;
			CALL GameCall2;

			MOV ECX,tmpKey;
			push ECX;
			CALL GameCall1;
			ADD ESP,4;
			MOV ECX,tmpKey;
			MOV ECX,DWORD PTR [ECX];
			TEST ECX,ECX;
			JE PressSkillKey_Exit;
			push 0;
			push 0;
			push nIndex;
			CALL GameCall2;
			MOV nRet,1;
PressSkillKey_Exit:;
		}
	}__except(1){};
	return nRet;
}
BOOL XCall::MoveSkillToKey(DWORD keyAddr,DWORD skillID)  //移动技能到快捷栏
{
	BOOL nRet = FALSE;
	__try
	{
		if(skillID == 0 || skillID == -1)
			return nRet;
		if(IsBadReadPtr((void*)keyAddr,4))
			return nRet;

		DWORD GameCall = MOVE_SKILL_TO_KEY_CALL;
		__asm
		{
			MOV ECX,keyAddr;
			push 3;
			push skillID;
			CALL GameCall;
		}
		nRet = TRUE;
	}__except(1){};
	return nRet;
}

//对像
bool XCall::ObjectIsFriend(ULONG64 ulObjID)     //对像是否友好
{
	bool nRet = false;
	__try
	{
		if(ulObjID == 0 || ulObjID == -1)
			return nRet;
		DWORD ObjID1 = LOWULONG64(ulObjID);
		DWORD ObjID2 = HIWULONG64(ulObjID);

		DWORD GameCall = OBJECT_BE_FRIEND_CALL;
		__asm
		{
			push ObjID2;
			push ObjID1;
			CALL GameCall;
			ADD ESP,0x8;
			MOV nRet,AL;
		}

	}__except(1){};
	return nRet;
}
DWORD XCall::GetObjNameAddr(DWORD objAddr)    //取对像名字地址
{
	DWORD nRet = 0;
	__try
	{
		if(IsBadReadPtr((void*)objAddr,4))
			return nRet;
		nRet = *(DWORD*)(objAddr + OBJECT_NAME_OS);
		if(IsBadReadPtr((void*)nRet ,4))
			nRet = 0;
	}__except(1){};
	return nRet;
}
DWORD XCall::GetCollectNameAddr(DWORD objAddr)    //取采集物名字地址
{
	DWORD nRet = 0;
	__try
	{
		if(IsBadReadPtr((void*)objAddr,4))
			return nRet;
		nRet = *(DWORD*)(objAddr + COLLECT_ITEM_NAME_OS);
		if(IsBadReadPtr((void*)nRet ,4))
			nRet = 0;
	}__except(1){};
	return nRet;
}
DWORD XCall::GetObjProperty(ULONG64 ulObjID)  //取对像属性地址
{
	DWORD nRet = 0;
	__try
	{
		if(ulObjID == 0 || ulObjID == -1)
			return nRet;
		DWORD ObjID1 = LOWULONG64(ulObjID);
		DWORD ObjID2 = HIWULONG64(ulObjID);

		DWORD GameCall = OBJ_PROPERTY_CALL;
		__asm
		{
			push ObjID2;
			push ObjID1;
			CALL GameCall;
			ADD ESP,8;
			MOV nRet,EAX;
		}
		if(IsBadReadPtr((void*)nRet ,4))
			nRet = 0;
	}__except(1){};
	return nRet;
}

int XCall::GetObjMaxFinesse(DWORD proAddr,int nIndex/*=0*/)  //取最大机巧
{
	DWORD nRet = 0;
	__try
	{
		if(IsBadReadPtr((void*)proAddr,4))
			return nRet;
		if(nIndex > 3)
			return nRet;

		DWORD GameCall = OBJ_MAX_FINESSE_CALL;
		__asm
		{
			push nIndex;
			MOV ECX,proAddr;
			CALL GameCall;
			ADD ESP,8;
			MOV nRet,EAX;
		}
	}__except(1){};
	return nRet;
}
int XCall::GetObjCurFinesse(DWORD proAddr,int nIndex/*=0*/)  //取当前机巧
{
	DWORD nRet = 0;
	__try
	{
		if(IsBadReadPtr((void*)proAddr,4))
			return nRet;
		if(nIndex > 3)
			return nRet;

		DWORD GameCall = OBJ_CUR_FINESSE_CALL;
		__asm
		{
			push nIndex;
			MOV ECX,proAddr;
			CALL GameCall;
			ADD ESP,8;
			MOV nRet,EAX;
		}
	}__except(1){};
	return nRet;
}


int XCall::GetObjMaxBlood(DWORD proAddr)   //最大血值
{
	int nRet = 0;
	__try
	{
		if(IsBadReadPtr((void*)proAddr,4))
			return nRet;
		nRet = *(DWORD*)(proAddr + OBJ_BLOOD_VALUE_OS +4);
		nRet ^= OBJ_PROPERTY_KEY_VALUE;
	}__except(1){nRet = 0;};
	return nRet;
}
int XCall::GetObjCurBlood(DWORD proAddr)	//当前血值
{
	int nRet = 0;
	__try
	{
		if(IsBadReadPtr((void*)proAddr,4))
			return nRet;
		nRet = *(DWORD*)(proAddr + OBJ_BLOOD_VALUE_OS);
		nRet ^= OBJ_PROPERTY_KEY_VALUE;
	}__except(1){nRet = 0;};
	return nRet;
}


int XCall::GetObjMaxInternal(DWORD proAddr)   //最大内息
{
	int nRet = 0;
	__try
	{
		if(IsBadReadPtr((void*)proAddr,4))
			return nRet;
		nRet = *(DWORD*)(proAddr + OBJ_INTERNAL_VALUE_OS +4);
		nRet ^= OBJ_PROPERTY_KEY_VALUE;
	}__except(1){nRet = 0;};
	return nRet;
}
int XCall::GetObjCurInternal(DWORD proAddr)	//当前内息
{
	int nRet = 0;
	__try
	{
		if(IsBadReadPtr((void*)proAddr,4))
			return nRet;
		nRet = *(DWORD*)(proAddr + OBJ_INTERNAL_VALUE_OS);
		nRet ^= OBJ_PROPERTY_KEY_VALUE;
	}__except(1){nRet = 0;};
	return nRet;
}

int XCall::GetObjMaxForce(DWORD proAddr)   //最大定力
{
	int nRet = 0;
	__try
	{
		if(IsBadReadPtr((void*)proAddr,4))
			return nRet;
		nRet = *(DWORD*)(proAddr + OBJ_FORCE_VALUE_OS +4);
		nRet ^= OBJ_PROPERTY_KEY_VALUE;
	}__except(1){nRet = 0;};
	return nRet;
}
int XCall::GetObjCurForce(DWORD proAddr)	//当前定力
{
	int nRet = 0;
	__try
	{
		if(IsBadReadPtr((void*)proAddr,4))
			return nRet;
		nRet = *(DWORD*)(proAddr + OBJ_FORCE_VALUE_OS);
		nRet ^= OBJ_PROPERTY_KEY_VALUE;
	}__except(1){nRet = 0;};
	return nRet;
}

int XCall::GetObjJob(DWORD proAddr)  //对像职业
{
	int nRet = 0;
	__try
	{
		if(IsBadReadPtr((void*)proAddr,4))
			return nRet;
		nRet = *(DWORD*)(proAddr + OBJ_JOB_VALUE_OS);
		nRet ^= OBJ_PROPERTY_KEY_VALUE;
	}__except(1){nRet = 0;};
	return nRet;
}
int XCall::GetObjLevel(DWORD proAddr)  //对像等级
{
	int nRet = 0;
	__try
	{
		if(IsBadReadPtr((void*)proAddr,4))
			return nRet;
		BYTE bLevel = *(BYTE*)(proAddr + OBJ_LEVEL_OS);
		bLevel += 0x25;
		nRet = (int)(bLevel&0xFF);
	}__except(1){nRet = 0;};
	return nRet;
}
DWORD XCall::GetCollectItemPos(DWORD collectAddr) //取采集物品坐标
{
	DWORD nRet = 0;
	__try
	{
		if(IsBadReadPtr((void*)collectAddr,4))
			return nRet;
		collectAddr +=0x10;
		if(IsBadReadPtr((void*)collectAddr,4))
			return nRet;
		__asm
		{
			MOV ECX,collectAddr;
			MOV EDX,DWORD PTR DS:[ECX];
			MOV EDX,DWORD PTR DS:[EDX + GET_OBJ_POSITION_CALL];
			CALL EDX;
			MOV nRet,EAX;
		}
		if(IsBadReadPtr((void*)nRet,4))
			nRet = 0;
	}__except(1){};
	return nRet;
}

BOOL XCall::ChangeRoleAngle(PROLEANGLE pChangeAngle)  //改变角色面向角call
{
	BOOL nRet = FALSE;
	__try
	{
		if(IsBadReadPtr((void*)pChangeAngle,4))
			return nRet;
		DWORD GameAddr = *(DWORD*)GAME_BASE;
		if(IsBadReadPtr((void*)GameAddr,4))
			return nRet;
		GameAddr = *(DWORD*)(GameAddr + MAN_PLAYER_ADDR_OS);
		GameAddr += 0x10;  //加0x10的才是
		if(IsBadReadPtr((void*)GameAddr,4))
			return nRet;

		DWORD GameCall = CHANGE_ROLE_ANGLE_CALL;
		__asm
		{
			MOV ECX,GameAddr;
			push 0;
			push pChangeAngle;
			CALL GameCall;
		}
		nRet = TRUE;
	}__except(1){nRet = FALSE;};
	return nRet;
}
//
//BOOL XCall::TalkNpc(ULONG64 ulNpcID)   //和npc对话
//{
//	BOOL nRet = FALSE;
//	__try
//	{
//		if(ulNpcID == 0 || ulNpcID == -1)
//			return nRet;
//		DWORD GameAddr = *(DWORD*)GAME_BASE;
//		if(IsBadReadPtr((void*)GameAddr,4))
//			return nRet;
//		GameAddr = *(DWORD*)(GameAddr + MAN_PLAYER_ADDR_OS);
//		if(IsBadReadPtr((void*)GameAddr,4))
//			return nRet;
//
//		DWORD ObjID1 = LOWULONG64(ulNpcID);
//		DWORD ObjID2 = HIWULONG64(ulNpcID);
//
//		DWORD GameCall = TALK_NPC_CALL;
//		__asm
//		{
//			push ObjID2;
//			push ObjID1;
//			MOV ECX,GameAddr;
//			CALL GameCall;
//		}
//		nRet = TRUE;
//	}__except(1){};
//	return nRet;
//}
BOOL XCall::ObjectCanAttack(ULONG64 ulObjID)  //对像是否能攻击
{
	BOOL nRet = FALSE;
	__try
	{
		if(ulObjID == 0 || ulObjID == -1)
			return nRet;

		DWORD ObjID1 = LOWULONG64(ulObjID);
		DWORD ObjID2 = HIWULONG64(ulObjID);
		bool nVal = false;

		DWORD GameCall = OBJECT_CAN_ATTACK_CALL;
		__asm
		{
			push ObjID2;
			push ObjID1;
			CALL GameCall;
			ADD ESP, 0x8;
			MOV nVal, AL;
		}
		nRet = (BOOL)nVal;
	}__except(1){};
	return nRet;
}
BOOL XCall::ObjectCanAttack2(ULONG64 ulObjID)  //对像是否能攻击
{
	BOOL nRet = FALSE;
	__try
	{
		if (ulObjID == 0 || ulObjID == -1)
			return nRet;
		ULONG64 roleID = XCall::GetRoleID();

		DWORD RoleID1 = LOWULONG64(roleID);
		DWORD RoleID2 = HIWULONG64(roleID);

		DWORD ObjID1 = LOWULONG64(ulObjID);
		DWORD ObjID2 = HIWULONG64(ulObjID);

		DWORD GameCall = OBJECT_CAN_ATTACK_CALL;
		__asm
		{
			push ObjID2;
			push ObjID1;
			push RoleID2;
			push RoleID1;
			CALL GameCall;
			MOV nRet, EAX;
		}
	}
	__except (1){};
	return nRet;
}
int XCall::GetObjType(ULONG64 ulObjID)  //取对像类型call
{
	int nRet = -1;
	__try
	{
		if(ulObjID == 0 || ulObjID == -1)
			return nRet;

		DWORD ObjID1 = LOWULONG64(ulObjID);
		DWORD ObjID2 = HIWULONG64(ulObjID);

		DWORD GameCall = GET_OBJ_TYPE_CALL;
		
		__asm
		{
			LEA EAX,nRet;
			push eax;
			push ObjID2;
			push ObjID1;
			CALL GameCall;
			ADD ESP,0xC;
		}
	}__except(1){};
	return nRet;
}
BOOL XCall::PickAllItem()   //全捡物品call
{
	BOOL nRet = FALSE;
	__try
	{
		DWORD PickUIAddr = XCall::GetUIAddr(_T("QSUIPickListPanel"));
		if(!PickUIAddr)
			return nRet;
		BOOL bVisible = (BOOL)*(bool*)(PickUIAddr + GAME_UI_VISIBLE_OS);
		if(!bVisible)
			return nRet;

		DWORD GameCall = PICK_ALL_ITEM_CALL;
		__asm
		{
			MOV ECX,PickUIAddr;
			CALL GameCall;
		}
		nRet = TRUE;
	}__except(1){}
	return nRet;
}




//寻路
BOOL XCall::FindPath(float desX,float desY)  //寻路call
{
	BOOL nRet = FALSE;
	__try
	{
		if(desX == 0 && desY == 0)
			return nRet;
		DWORD CurMapID = *(DWORD*)CUR_MAP_ID_BASE;
		if(CurMapID == 0 || CurMapID == -1)
			return nRet;

		DWORD GameCall = FIND_PATH_CALL;
		__asm
		{
			push 0;
			push desY;
			push desX;
			push CurMapID;
			CALL GameCall;
			ADD ESP,0x10;
		}
		nRet = TRUE;
	}__except(1){};
	return nRet;
}
DWORD XCall::GetMapInfoAddr(DWORD mapID)  //取 地图详细地址
{
	DWORD nRet = 0;
	__try
	{
		if(mapID == 0 || mapID == -1)
			return nRet;
		DWORD GameCall1 = MAP_INFO_BASE_CALL;
		DWORD GameCall2 = GET_MAP_INFO_ADDR_CALL;
		__asm
		{
			push mapID;;
			CALL GameCall1;
			MOV ECX,EAX;
			CALL GameCall2;
			MOV nRet,EAX;
		}
		if(IsBadReadPtr((void*)nRet,4))
			nRet = 0;
	}__except(1){};
	return nRet;
}
tstring XCall::GetMapName(DWORD mapID)   //取地图名字
{
	tstring mapName;
	try
	{
		DWORD MapInfo = XCall::GetMapInfoAddr(mapID);
		if(MapInfo)
		{
			char* szMapName = (char*)*(DWORD*)(MapInfo + MAP_INFO_NAME_OS);
			if(!IsBadReadPtr((void*)szMapName,4))
				mapName = XCall::UTF2T(szMapName);
		}
	}
	catch (...){}
	return mapName;
}
DWORD XCall::GetAreaNameAddr(DWORD mapID,float desX,float desY)  //取城镇名字地址
{
	DWORD nRet = 0;
	__try
	{
		if(mapID == 0 || mapID == -1)
			return nRet;
		DWORD mapInfoAddr = XCall::GetMapInfoAddr(mapID);
		if(IsBadReadPtr((void*)mapInfoAddr,4))
			return nRet;
		DWORD GameAddr = *(DWORD*)MAP_AREA_BASE;
		if(IsBadReadPtr((void*)GameAddr,4))
			return nRet;

		DWORD GameCall = GET_MAP_AREA_NAME_CALL;
		__asm
		{
			push mapInfoAddr;;
			push desY;
			push desX;
			push mapID;
			MOV ECX,GameAddr;
			CALL GameCall;
			MOV nRet,EAX;
		}
		if(IsBadReadPtr((void*)nRet,4))
			nRet = 0;
	}__except(1){};
	return nRet;
}
tstring XCall::GetMapAreaName(DWORD mapID,float desX,float desY)   //取地图城镇名字
{
	tstring mapName;
	try
	{
		DWORD AreaName = XCall::GetAreaNameAddr(mapID,desX,desY);
		if(AreaName)
			mapName = XCall::UTF2T((char*)AreaName);
	}
	catch (...){}
	return mapName;
}

//会话
ULONG64 XCall::GetResponseNpcID()   //取对话npc的ID
{
	ULONG64 nRet = 0;
	__try
	{
		DWORD responseDlg = XCall::GetResponseDlg();
		if(responseDlg)
			nRet = *(ULONG64*)(responseDlg + RESPONSE_DLG_NPC_ID_OS);
	}__except(1){};
	return nRet;
}

DWORD XCall::GetObjServerID(ULONG64 objID)  //取对像服务器ID
{
	DWORD nRet = 0;
	__try
	{
		if(objID ==0 || objID== -1)
			return nRet;
		DWORD ObjID1 = LOWULONG64(objID);
		DWORD ObjID2 = HIWULONG64(objID);

		DWORD GameCall = GET_SERVER_NPC_ID_CALL;
		__asm
		{
			push ObjID2;
			push ObjID1;
			CALL GameCall;
			ADD ESP,8;
			MOV nRet,EAX;
		}	
	}__except(1){};
	return nRet;
}
DWORD XCall::GetResponseItemList()  //取当前会话选项列表地址
{
	DWORD nRet = 0;
	__try
	{
		ULONG64 curNpcID = XCall::GetResponseNpcID();
		//DbgLog(_T("当前对话NPC的ID:%llX"),curNpcID);
		if(curNpcID == 0 || curNpcID == -1)
			return nRet;
		DWORD npcServerID = XCall::GetObjServerID(curNpcID);
		//DbgLog(_T("当前对话NPC的服务器ID:%X"),npcServerID);
		if(npcServerID == 0)
			return nRet;
		DWORD GameAddr = *(DWORD*)GAME_BASE;
		if(IsBadReadPtr((void*)GameAddr,4))
			return nRet;
		GameAddr = *(DWORD*)(GameAddr + QUEST_RESPONSE_ITEM_LIST_OS);
		if(IsBadReadPtr((void*)GameAddr,4))
			return nRet;

		DWORD GameCall = GET_RESPONSE_ITEM_LIST_CALL;
		__asm
		{
			push npcServerID;
			MOV ECX,GameAddr;
			CALL GameCall;
			MOV nRet,EAX;
		}	
		if(IsBadReadPtr((void*)nRet,4))
			nRet = 0;
	}__except(1){};
	return nRet;
}
BOOL XCall::GetResponseItemState(DWORD responseAddr)  //取会话选项状态call
{
	BOOL nRet = FALSE;
	__try
	{
		if(IsBadReadPtr((void*)responseAddr,4))
			return nRet;
		BYTE bValue = 0;
		__asm
		{
			MOV ECX,responseAddr;
			MOV EDX,DWORD PTR DS:[ECX];
			MOV EAX,DWORD PTR DS:[EDX + 8];
			CALL EAX;
			MOV bValue,AL;
		}	
		nRet = (BOOL)bValue;
	}__except(1){};
	return nRet;
}



BOOL XCall::PressResponseItem(int nType,DWORD responseID1,DWORD responseID2,int nIndex)  //会话选项call
{
	BOOL nRet = FALSE;
	__try
	{
		DWORD responseDlg = XCall::GetResponseDlg();

		DWORD GameCall = PRESS_RESPONSE_ITEM_CALL;
		__asm
		{
			push nIndex;
			push responseID2;
			push responseID1;
			push nType;
			MOV ECX,responseDlg;
			CALL GameCall;
			MOV nRet,EAX;
		}	
		nRet = TRUE;
	}__except(1){};
	return nRet;
}

//UI
DWORD XCall::GetUIAddr(DWORD dwFlagAddr)  //取UI地址
{
	DWORD nRet = 0;
	__try
	{
		//if(IsBadReadPtr((void*)dwFlagAddr,4))
		//	return nRet;
		DWORD GameAddr = *(DWORD*)UI_BASE;
		if(IsBadReadPtr((void*)GameAddr,4))
			return nRet;

		DWORD GameCall = GET_UI_ADDR_CALL;
		__asm
		{
			push dwFlagAddr;
			MOV ECX,GameAddr;
			CALL GameCall;
			MOV nRet,EAX;
		}
		if(IsBadReadPtr((void*)nRet,4))
			nRet = 0;
	}__except(1){};
	return nRet;
}
DWORD XCall::GetUIAddr(TCHAR* szUIName)   //查找UI地址
{
	DWORD nRet = 0;
	try
	{
		DWORD GameAddr = *(DWORD*)UI_BASE;
		if(IsBadReadPtr((void*)GameAddr,4))
			return nRet;
		DWORD ListHead = GameAddr + GAME_UI_LIST_OS;
		if(IsBadReadPtr((void*)ListHead,4))
			return nRet;
		DWORD curList = *(DWORD*)(ListHead);
		if(IsBadReadPtr((void*)curList,4))
			return nRet;
		while(curList != ListHead)
		{
			DWORD GameUIAddr = *(DWORD*)(curList + 8);
			if(!IsBadReadPtr((void*)GameUIAddr,4))
			{
				BOOL bVisible = (BOOL)*(bool*)(GameUIAddr + GAME_UI_VISIBLE_OS);
				if(bVisible)
				{
					tstring strGameUiName;
					char* GameUIName = (char*)*(DWORD*)(GameUIAddr + GAME_UI_NAME_OS);
					if(!IsBadReadPtr((void*)GameUIName,4))
						strGameUiName = XCall::UTF2T(GameUIName);

					if(!strGameUiName.empty() && strGameUiName.find(szUIName)!=tstring::npos)
					{
						nRet = GameUIAddr;
						break;
					}
				}
			}
			curList = *(DWORD*)curList;
			if(IsBadReadPtr((void*)curList,4))
				break ;
		}
	}catch(...){};
	return nRet;
}

DWORD XCall::GetResponseDlg()    //取npc对话框 地址
{
	DWORD nRet = 0;
	__try
	{
		nRet = XCall::GetUIAddr(NPC_DLG_FLAG_BASE_CALL);
		if(IsBadReadPtr((void*)nRet,4))
			nRet = 0;
	}__except(1){};
	return nRet;
}

//任务
DWORD XCall::GetQuestAddr(DWORD questID)  //取任务地址
{
	DWORD nRet = 0;
	__try
	{
		if(questID == 0 || questID== -1)
			return nRet;

		DWORD GameCall = GET_QUEST_ADDR_CALL;
		__asm
		{
			push questID;
			CALL GameCall;
			ADD ESP,4;
			MOV nRet,EAX;
		}
		if(IsBadReadPtr((void*)nRet,4))
			nRet = 0;
	}__except(1){};
	return nRet;
}

DWORD XCall::GetQuestName(DWORD questID)  //取任务名地址
{
	DWORD nRet = 0;
	__try
	{
		if(questID == 0 || questID== -1)
			return nRet;
		DWORD QuestAddr = XCall::GetQuestAddr(questID);
		if(QuestAddr)
		{
			DWORD QuestInfo = *(DWORD*)(QuestAddr + QUEST_INFO_OS1);
			if(IsBadReadPtr((void*)QuestInfo,4))
				return nRet;
			QuestInfo = *(DWORD*)(QuestInfo + QUEST_INFO_OS2);
			if(IsBadReadPtr((void*)QuestInfo,4))
				return nRet;
			nRet = *(DWORD*)(QuestInfo + QUEST_NAME_OS);
		}
	}__except(1){};
	return nRet;
}
DWORD XCall::GetJianWenInfo(DWORD questID)  //取见闻任务详细地址
{
	DWORD nRet = 0;
	__try
	{
		if(questID == 0 || questID== -1)
			return nRet;
		DWORD GameAddr = *(DWORD*)GAME_BASE;
		if(IsBadReadPtr((void*)GameAddr,4))
			return nRet;
		GameAddr = *(DWORD*)(GameAddr + JIANWEN_INFO_LIST_OS);
		if(IsBadReadPtr((void*)GameAddr,4))
			return nRet;


		DWORD GameCall2 = GET_JIANWEN_INFO_CALL2;
		__asm
		{
			push questID;
			MOV ECX,GameAddr;
			CALL GameCall2;
			MOV nRet,EAX;
		}
		if(IsBadReadPtr((void*)nRet,4))
			nRet = 0;
	}__except(1){};
	return nRet;
}
DWORD XCall::GetHuaBenProgress(int nQuestIndex)   //取话本完成进度地址
{
	DWORD nRet = 0;
	__try
	{
		if(nQuestIndex == 0 || nQuestIndex== -1)
			return nRet;
		DWORD GameAddr = *(DWORD*)HUABEN_QUEST_PROGRESS_BASE;
		if(IsBadReadPtr((void*)GameAddr,4))
			return nRet;

		DWORD GameCall = GET_HUABEN_PROGRESS_CALL;
		__asm
		{
			push nQuestIndex;
			MOV ECX,GameAddr;
			CALL GameCall;
			MOV nRet,EAX;
		}
		if(IsBadReadPtr((void*)nRet,4))
			nRet = 0;
	}__except(1){};
	return nRet;
}
BOOL XCall::GetJianWenQuest(DWORD questID)   //取见闻任务状态call
{
	BOOL nRet = FALSE;
	__try
	{
		if(questID == 0 || questID== -1 )
			return nRet;

		DWORD GameCall = IS_JIANWEN_COMPLETED_CALL;
		int nValue = 0;
		__asm
		{
			push questID;
			CALL GameCall;
			ADD ESP,0x4;
			MOV nValue,EAX;
		}
		nRet = (BOOL)nValue;
	}__except(1){};
	return nRet;
}
BOOL XCall::GetPlotEventAcceptState(DWORD EventID)   //Plot Event是否能接受
{
	BOOL nRet = FALSE;
	__try
	{
		if(EventID == 0 || EventID== -1 )
			return nRet;

		DWORD GameCall = PLOT_EVENT_CAN_ACCECPT_CALL;
		int nValue = 0;
		__asm
		{
			push EventID;
			CALL GameCall;
			ADD ESP,0x4;
			MOV nValue,EAX;
		}
		nRet = (BOOL)nValue;
	}__except(1){};
	return nRet;
}
BOOL XCall::GetPlotEventCompleteState(DWORD EventID)   //Plot Event是否能完成
{
	BOOL nRet = FALSE;
	__try
	{
		if(EventID == 0 || EventID== -1 )
			return nRet;

		DWORD GameCall = PLOT_EVENT_COMPLETED_CALL;
		int nValue = 0;
		__asm
		{
			push EventID;
			CALL GameCall;
			ADD ESP,0x4;
			MOV nValue,EAX;
		}
		nRet = (BOOL)nValue;
	}__except(1){};
	return nRet;
}

//物品
DWORD XCall::GetItemAddr(ULONG64 itemID)  //取物品地址
{
	DWORD GameBase = *(DWORD*)GAME_BASE;
	if (IsBadReadPtr((void*)(GameBase), 4))
		return 0;
	GameBase = *(DWORD*)(GameBase + ITEM_LIST_OS);
	if (IsBadReadPtr((void*)(GameBase), 4))
		return 0;
	DWORD CurList = *(DWORD*)(GameBase + ITEM_LIST_OS2);
	if (IsBadReadPtr((void*)(CurList), 4))
		return 0;
	RECURSIVEPARAM RecParam;

	RecParam.mObjectID = itemID;
	RecParam.mRetValue = 0;

	VisitItemList(CurList, &RecParam);
	return RecParam.mRetValue;
}
void XCall::VisitItemList(DWORD CurList, PRECURSIVEPARAM pRecParam)
{
	if (pRecParam->mRetValue != 0)   //有找到了就直接返回
		return;
	if (IsBadReadPtr((void*)CurList, 4))
		return;
	do 
	{
		DWORD ItemAddr = *(DWORD*)(CurList + 0x14);
		if (IsBadReadPtr((void*)ItemAddr, 4))
			break;
		ULONG64 itemID = *(ULONG64*)(ItemAddr + ITEM_ADDR_ID_OS);
		if (itemID && itemID == pRecParam->mObjectID){
			pRecParam->mRetValue = ItemAddr;
			return;
		}
	} while (0);

	DWORD b0 = *(DWORD*)CurList;
	if (!IsBadReadPtr((void*)b0, 4))
		XCall::VisitItemList(b0, pRecParam);
	DWORD b4 = *(DWORD*)(CurList + 4);
	if (!IsBadReadPtr((void*)b4, 4))
		XCall::VisitItemList(b4, pRecParam);
}

BOOL XCall::RightPressSlot(DWORD SlotAddr)   //左键操作容器(左键点击)
{
	BOOL nRet = 0;
	__try
	{
		if (IsBadReadPtr((void*)SlotAddr, 4))
			return nRet;
		__asm
		{
			MOV ESI, SlotAddr;
			MOV EDX, DWORD PTR DS : [ESI];
			MOV EDX, DWORD PTR DS : [EDX + 0x0C];
			MOV ECX, ESI;
			CALL EDX;
		}
		nRet = TRUE;
	}
	__except (1){};
	return nRet;
}
BOOL XCall::LeftPressSlot(DWORD SlotAddr)   //右键操作容器(右键使用物品,装备,或出售物品)
{
	BOOL nRet = 0;
	__try
	{
		if (IsBadReadPtr((void*)SlotAddr, 4))
			return nRet;
		__asm
		{
			MOV ESI, SlotAddr;
			MOV EDX, DWORD PTR DS : [ESI];
			MOV EDX, DWORD PTR DS : [EDX + 0x08];
			MOV ECX, ESI;
			CALL EDX;
		}
		nRet = TRUE;
	}
	__except (1){};
	return nRet;
}

//DWORD XCall::GetItemAddr2(ULONG64 itemID)  //取物品地址  妈的 vm掉了.   上面自己写一个. 
//{
//	DWORD nRet = 0;
//	__try
//	{
//		if(itemID == 0 || itemID== -1)
//			return nRet;
//		DWORD GameAddr = *(DWORD*)GAME_BASE;
//		if(IsBadReadPtr((void*)GameAddr,4))
//			return nRet;
//		GameAddr = *(DWORD*)(GameAddr + ITEM_LIST_OS);
//		if(IsBadReadPtr((void*)GameAddr,4))
//			return nRet;
//		DWORD itemID1 = LOWULONG64(itemID);
//		DWORD itemID2 = HIWULONG64(itemID);
//
//		DWORD GameCall = GET_ITEM_ADDR_CALL;
//		__asm
//		{
//			MOV ECX,GameAddr;
//			push itemID2;
//			push itemID1;
//			CALL GameCall;
//			MOV nRet,EAX;
//		}
//		if(IsBadReadPtr((PVOID)nRet,4))
//			nRet = 0;
//	}__except(1){};
//	return nRet;
//}
//BOOL XCall::UseGoods(ULONG64 itemID,int nIndex)  //使用物品
//{
//	BOOL nRet = FALSE;
//	__try
//	{
//		if(itemID == 0 || itemID== -1 || nIndex<0)
//			return nRet;
//		DWORD itemID1 = LOWULONG64(itemID);
//		DWORD itemID2 = HIWULONG64(itemID);
//
//		DWORD GameCall = USE_GOODS_CALL;
//		int nValue = 0;
//		__asm
//		{
//			push nIndex;
//			push 2;
//			push itemID2;
//			push itemID1;
//			CALL GameCall;
//			ADD ESP,0x10;
//			MOV nValue,EAX;
//		}
//		if(nValue == 0)
//			nRet = TRUE;
//	}__except(1){};
//	return nRet;
//}
//BOOL XCall::UseEquip(int nIndex)  //使用装备  index=容器下标
//{
//	BOOL nRet = FALSE;
//	__try
//	{
//		if( nIndex<0)
//			return nRet;
//
//		DWORD GameCall = EQUIP_ITEM_CALL;
//		int nValue = 0;
//		__asm
//		{
//			push nIndex;
//			CALL GameCall;
//			ADD ESP,0x4;
//			MOV nValue,EAX;
//		}
//		if(nValue == 0)
//			nRet = TRUE;
//	}__except(1){};
//	return nRet;
//}


BOOL XCall::ItemIsGoodsType(DWORD itemAddr)  //物品是否是货物
{
	BOOL nRet = FALSE;
	__try
	{
		if(IsBadReadPtr((void*)itemAddr,4))
			return nRet;

		DWORD GameCall = ITEM_IS_GOODS_TYPE_CALL;
		bool bValue = false;
		__asm
		{
			push itemAddr;
			CALL GameCall;
			ADD ESP,4;
			MOV bValue,AL;
		}
			nRet = (BOOL)bValue;
	}__except(1){};
	return nRet;
}
BOOL XCall::ItemIsEquipType(DWORD itemAddr)  //物品是否是装备
{
	BOOL nRet = FALSE;
	__try
	{
		if(IsBadReadPtr((void*)itemAddr,4))
			return nRet;

		DWORD GameCall = ITEM_IS_EQUIP_TYPE_CALL;
		bool bValue = false;
		__asm
		{
			push itemAddr;
			CALL GameCall;
			ADD ESP,4;
			MOV bValue,AL;
		}
		nRet = (BOOL)bValue;
	}__except(1){};
	return nRet;
}
BOOL XCall::EquipCanUse(DWORD itemServerID)  //装备是否能装备
{
	BOOL nRet = FALSE;
	__try
	{
		if(itemServerID == 0)
			return nRet;
		DWORD GameCall = CAN_EQUIP_ITEM_CALL;
		__asm
		{
			push 1;
			push itemServerID;
			CALL GameCall;
			ADD ESP,8;
			MOV nRet,EAX;
		}
	}__except(1){};
	return nRet;
}

int XCall::GetEquipCurUseAge(DWORD itemAddr) //物品耐久度
{
	int nRet = 0;
	__try
	{
		if(IsBadReadPtr((void*)itemAddr,4))
			return nRet;
		__asm
		{
			MOV ESI,itemAddr;
			MOV EDX,DWORD PTR DS:[ESI];
			MOV EDX,DWORD PTR DS:[EDX + EQUIP_CUR_USEAGE_CALL_OS];
			MOV ECX,ESI;
			CALL EDX;
			MOV nRet,EAX;
		}
	}__except(1){};
	return nRet;
}
int XCall::GetEquipMaxUseAge(DWORD itemAddr)  //物品最大耐久度
{
	int nRet = 0;
	__try
	{
		if(IsBadReadPtr((void*)itemAddr,4))
			return nRet;
		DWORD itemInfoAddr = *(DWORD*)(itemAddr + ITEM_INFO_ADDR_OS);
		if(IsBadReadPtr((void*)itemInfoAddr,4))
			return nRet;
		nRet = *(int*)(itemInfoAddr + EQUIP_MAX_USEAGE_OS);
	}__except(1){};
	return nRet;
}
BOOL XCall::GetEquipAttribute(DWORD itemAddr,PITEMATTRIBUTE pItemAttri)  //取装备属性
{
	BOOL nRet = FALSE;
	__try
	{
		if(!pItemAttri)
			return nRet;
		if(IsBadReadPtr((void*)itemAddr,4))
			return nRet;
		DWORD itemInfoAddr = *(DWORD*)(itemAddr + ITEM_INFO_ADDR_OS);
		if(IsBadReadPtr((void*)itemInfoAddr,4))
			return nRet;
		DWORD pCurAttri = (itemInfoAddr + EQUIP_MAX_USEAGE_OS + 4);
		if(IsBadReadPtr((void*)(pCurAttri+ sizeof(ITEMATTRIBUTE)),4))
			return nRet;
		memcpy(pItemAttri,(PVOID)pCurAttri,sizeof(ITEMATTRIBUTE));
		nRet = TRUE;
	}__except(1){};
	return nRet;
}

//DWORD XCall::GetItemInfoAddr(DWORD itemID)  //取物品详细地址 by服务器ID
//{
//	DWORD nRet = 0;
//	__try
//	{
//		if(itemID == 0 || itemID== -1)
//			return nRet;
//
//		DWORD GameCall = GET_ITEM_INFO_CALL;
//		__asm
//		{
//			push 1;
//			push itemID;
//			CALL GameCall;
//			ADD ESP,0x8;
//			MOV nRet,EAX;
//		}
//		if(IsBadReadPtr((PVOID)nRet,4))
//			nRet = 0;
//	}__except(1){};
//	return nRet;
//}
BOOL XCall::SellItemCall(int nIndex)  //出售物品call
{
	BOOL nRet = FALSE;
	__try
	{
		if(nIndex < 0)
			return nRet;
		DWORD paramEcx[3]={0};
		paramEcx[0] = 2;
		paramEcx[1] = nIndex;

		DWORD GameCall = SELL_GOODS_CALL;
		__asm
		{
			LEA ECX,paramEcx;
			CALL GameCall;
		}
		nRet = TRUE;
	}__except(1){};
	return nRet;
}
BOOL XCall::BuyItemCall(DWORD ItemId,int nNum)   //购买call
{
	BOOL nRet = FALSE;
	__try
	{
		if(ItemId == 0 || ItemId==-1 || nNum <1)
			return nRet;
		DWORD ShopDlgUI = XCall::GetUIAddr(_T("QSUINpcShopPanel"));
		if(IsBadReadPtr((void*)ShopDlgUI,4))
			return nRet;

		BUYITEMPACKET dwData;
		ZeroMemory(&dwData,sizeof(BUYITEMPACKET));
		dwData.bAction = 2;
		dwData.ulShopNpcID = *(ULONG64*)(ShopDlgUI + RESPONSE_DLG_NPC_ID_OS);
		dwData.dwShopNpcID = *(DWORD*)(ShopDlgUI + RESPONSE_DLG_NPC_ID_OS + 8);
		dwData.dwItemID = ItemId;
		dwData.nFlag = 2;
		dwData.nItemNum = nNum;

		nRet = XCall::SendPacket(MSG_BUY_ITEM_PACKET,(char*)&dwData,0x19);
	}__except(1){};
	return nRet;
}
//传送点
DWORD XCall::GetTransferInfoAddr(DWORD transferID)   //取传送点详细地址
{
	DWORD nRet = 0;
	__try
	{
		if(transferID == 0 || transferID== -1)
			return nRet;

		DWORD GameCall = GET_TRANSFER_INFO_CALL;
		__asm
		{
			push transferID;
			CALL GameCall;
			ADD ESP,4;
			MOV nRet,EAX;
		}
		if(IsBadReadPtr((PVOID)nRet,4))
			nRet = 0;
	}__except(1){};
	return nRet;
}
float XCall::GetTransferFreezeTime()   //取传送点冻结剩余时间
{
	float nRet = 0;
	__try
	{
		DWORD GameCall = GET_TRANSFER_FREEZE_TIME_CALL;
		__asm
		{
			CALL GameCall;
			LEA ECX,nRet;
			MOV DWORD PTR DS:[ECX],EAX;
		}
	}__except(1){};
	return nRet;
}
BOOL XCall::PressTransferPoint(int transferIndex,DWORD mapID)   //传送点传送
{
	BOOL nRet = FALSE;
	__try
	{
		if(transferIndex == 0 || transferIndex== -1)
			return nRet;
		if(mapID == 0 || mapID== -1)
			return nRet;

		DWORD GameCall = PRESS_TRANSFER_POINT_CALL;
		__asm
		{
			push transferIndex;
			push mapID;
			CALL GameCall;
			ADD ESP,0x8;
		}
		nRet = TRUE;
	}__except(1){};
	return nRet;
}

//组队
BOOL XCall::InvitePlayerInTeam(DWORD PlayerID1,DWORD PlayerID2,char* szPlayerName)  //邀请组队发包
{
	BOOL nRet = FALSE;
	__try
	{
		if(PlayerID1 == 0 || PlayerID1== -1 
			|| PlayerID2==0||PlayerID2==-1)
			return nRet;
		INVITETEAMPACKET teamPacket;
		ZeroMemory(&teamPacket,sizeof(INVITETEAMPACKET));
		teamPacket.dwPlayerID1 = PlayerID1;
		teamPacket.dwPlayerID2 = PlayerID2;
		strncpy_s(teamPacket.szPlayerName,0x20,szPlayerName,0x1F);

		nRet = XCall::SendPacket(MSG_INVITE_TEAM_PACKET,(char*)&teamPacket,0x28);
	}__except(1){};
	return nRet;
}
BOOL XCall::AcceptPlayerInTeam(DWORD PlayerID1,DWORD PlayerID2)  //接受组队发包
{
	BOOL nRet = FALSE;
	__try
	{
		if(PlayerID1 == 0 || PlayerID1== -1 
			|| PlayerID2==0||PlayerID2==-1)
			return nRet;
		DWORD teamPacket[6] = {0};
		teamPacket[1] = PlayerID1;
		teamPacket[2] = PlayerID2;

		nRet = XCall::SendPacket(MSG_ACCEPT_TEAM_PACKET,(char*)&teamPacket,0x14);
	}__except(1){};
	return nRet;
}

BOOL XCall::PlayerQuitTeam()  //离开组队发包
{
	BOOL nRet = FALSE;
	__try
	{
		ULONG64 roleID = XCall::GetRoleID();
		if(roleID==0 || roleID ==-1)
			return nRet;
		DWORD teamPacket[3] = {0};
		teamPacket[0] = LOWULONG64(roleID);
		teamPacket[1] = HIWULONG64(roleID);

		nRet = XCall::SendPacket(MSG_QUIT_TEAM_PACKET,(char*)&teamPacket,0x08);
	}__except(1){};
	return nRet;
}
BOOL XCall::ChangeTeamLeader(DWORD PlayerID1,DWORD PlayerID2) //转让队长发包
{
	BOOL nRet = FALSE;
	__try
	{
		if( (PlayerID1==0&&PlayerID2==0) 
			|| (PlayerID1 ==-1&& PlayerID2==-1) )
			return nRet;

		DWORD teamPacket[3] = {0};
		teamPacket[0] = PlayerID1;
		teamPacket[1] = PlayerID2;

		nRet = XCall::SendPacket(MSG_CHANGE_TEAM_LEADER_PACKET,(char*)&teamPacket,0x08);
	}__except(1){};
	return nRet;
}
BOOL XCall::KickOutTeam(DWORD PlayerID1,DWORD PlayerID2)		//请离队伍发包
{
	BOOL nRet = FALSE;
	__try
	{
		if( (PlayerID1==0&&PlayerID2==0) 
			|| (PlayerID1 ==-1&& PlayerID2==-1) )
			return nRet;

		DWORD teamPacket[3] = {0};
		teamPacket[0] = PlayerID1;
		teamPacket[1] = PlayerID2;

		nRet = XCall::SendPacket(MSG_KICK_OUT_TEAM_PACKET,(char*)&teamPacket,0x08);
	}__except(1){};
	return nRet;
}
BOOL XCall::ChangeThread(DWORD threadID1,DWORD threadID2)   //切换线路
{
	BOOL nRet = FALSE;
	__try
	{
		if( threadID1 ==-1&& threadID2==-1)
			return nRet;

		DWORD teamPacket[3] = {0};
		teamPacket[0] = threadID1;
		teamPacket[1] = threadID2;

		nRet = XCall::SendPacket(MSG_CHANGE_THREAD_ID_PACKET,(char*)&teamPacket,0x08);
	}__except(1){};
	return nRet;
}

//登入
BOOL XCall::CreateCharacter(char* szCharacterName,int nJob,BOOL nFemale,BYTE* pCharacterData)  //创建角色call
{
	BOOL nRet = FALSE;
	__try
	{
		if(nJob < 0 || IsBadReadPtr((void*)szCharacterName,4))
			return nRet;
		if(pCharacterData == NULL)
			return nRet;

		DWORD GameCall = CREAT_CHARACTER_CALL;
		__asm
		{
			push pCharacterData;
			push nJob;
			push nFemale;
			push szCharacterName;
			CALL GameCall;
			ADD ESP,0x10;
		}
		nRet = TRUE;
	}__except(1){};
	return nRet;
}

BOOL XCall::EnterGame(int nIndex)   //登入游戏
{

	BOOL nRet = FALSE;
	__try
	{
		if(nIndex < 0 )
			return nRet;

		DWORD GameCall = ENTER_GAME_CALL;
		__asm
		{
			push nIndex;
			CALL GameCall;
			ADD ESP,0x4;
		}
		nRet = TRUE;
	}__except(1){};
	return nRet;
}


//发包
BOOL XCall::SendPacket(DWORD dwMsg,char* pData,int nLen)   //发包call
{
	BOOL nRet = FALSE;
	__try
	{
		if(dwMsg == 0 || dwMsg== -1)
			return nRet;
		if(nLen<1 || pData == NULL)
			return nRet;

		DWORD GameAddr = *(DWORD*)SEND_PACKET_BASE;
		if(IsBadReadPtr((void*)GameAddr,4))
			return nRet;

		DWORD GameCall = SEND_PACKET_CALL;
		bool bValue = false;
		__asm
		{
			push nLen;
			MOV EAX,pData;
			push eax;
			push dwMsg;
			MOV ECX,GameAddr;
			CALL GameCall;
			MOV bValue,AL;
		}
		nRet = (BOOL)bValue;
	}__except(1){};
	return nRet;
}
BOOL XCall::RevivePacket(BOOL bSamePlace/*=FALSE*/)  //复活
{
	BOOL nRet = FALSE;
	__try
	{
		ULONG64 roleID = XCall::GetRoleID();
		if(roleID == 0 || roleID==-1)
			return nRet;
		DWORD dwData[5] = {0};
		dwData[0] = LOWULONG64(roleID);
		dwData[1] = HIWULONG64(roleID);
		if(bSamePlace)
			dwData[2] = 0x3EA;
		else
			dwData[2] = 0x3EB;

		nRet = XCall::SendPacket(MSG_REVIVE_PACKET,(char*)dwData,0xC);
	}__except(1){};
	return nRet;
}

BOOL XCall::JoinMengHui(int nID)  //加入盟会call
{
	BOOL nRet = FALSE;
	__try
	{
		DWORD GameCall = JOYIN_MEMHUI_CALL;
		__asm
		{
			push nID;
			CALL GameCall;
			ADD ESP,4;
		}
		nRet = TRUE;
	}__except(1){};
	return nRet;
}

BOOL XCall::DellMail(DWORD mailID1,DWORD mailID2)   //删除邮件
{
	BOOL nRet = FALSE;
	__try
	{
		DELMAILPACKET MailPacket;
		ZeroMemory(&MailPacket,sizeof(DELMAILPACKET));
		MailPacket.nDelNum = 1;
		MailPacket.MailIDArrary[0] = mailID1;
		MailPacket.MailIDArrary[1] = mailID2;


		nRet = XCall::SendPacket(MSG_DEL_MAIL_PACKET,(char*)&MailPacket,0x1A0);
	}__except(1){};
	return nRet;
}
BOOL XCall::TakeAppend(DWORD mailID1,DWORD mailID2)   //提取邮件附件
{
	BOOL nRet = FALSE;
	__try
	{
		TAKEAPPENDPACKET MailPacket;
		ZeroMemory(&MailPacket,sizeof(TAKEAPPENDPACKET));
		MailPacket.dwFlag = 2;
		MailPacket.dwMailID1 = mailID1;
		MailPacket.dwMailID2 = mailID2;
		MailPacket.dwCountValue = 2;

		nRet = XCall::SendPacket(MSG_TAKE_MAIL_APPEND_PACKET,(char*)&MailPacket,0x1C);
	}__except(1){};
	return nRet;
}

BOOL XCall::ClickGameKey(DWORD nkey, int nCtrl/* = 0*/)  //按键call
{
	SUPERKEYINFO keyInfo, ctrlInfo;
	ZeroMemory(&keyInfo, sizeof(SUPERKEYINFO));
	ZeroMemory(&ctrlInfo, sizeof(SUPERKEYINFO));

	keyInfo.dwKeyType = 5;
	keyInfo.dwSupperKey = nkey;
	keyInfo.dwKeyUp = 0;   //按下
	if (nCtrl == 1)
	{
		ctrlInfo.dwKeyType = 5;
		ctrlInfo.dwSupperKey = VK_CONTROL;
		ctrlInfo.dwKeyUp = 0;   //按下

		keyInfo.bCtrl = true;
	}
	else if (nCtrl == 2)
	{
		ctrlInfo.dwKeyType = 5;
		ctrlInfo.dwSupperKey = VK_SHIFT;
		ctrlInfo.dwKeyUp = 0;   //按下

		keyInfo.bShift = true;
	}
	else if (nCtrl == 3)
	{
		ctrlInfo.dwKeyType = 5;
		ctrlInfo.dwSupperKey = VK_MENU;
		ctrlInfo.dwKeyUp = 0;   //按下

		keyInfo.bMenu = true;
	}

	if (nkey == 0x57)
	{  //W键
		keyInfo.bKeyW = true;
	}
	else if (nkey == 0x53)
	{  //S键
		keyInfo.bKeyS = true;
	}
	else if (nkey == 0x41)
	{  //A键
		keyInfo.bKeyA = true;
	}
	else if (nkey == 0x43)
	{  //D键
		keyInfo.bKeyD = true;
	}
	if (nCtrl > 0)  
		XCall::PressKey(&ctrlInfo);

	XCall::PressKey(&keyInfo);   //按下

	keyInfo.dwKeyUp = 1;
	XCall::PressKey(&keyInfo);   //弹起

	ctrlInfo.dwKeyUp = 1;
	if (nCtrl > 0) 
		XCall::PressKey(&ctrlInfo);  //ctrl弹起
	return TRUE;
}

BOOL XCall::PressKey(PSUPERKEYINFO pKeyInfo)
{
	BOOL nRet = FALSE;
	__try
	{
		if (!pKeyInfo)
			return nRet;
		DWORD GameCall = SUPER_KEY_CALL;
		__asm
		{
			push pKeyInfo;
			MOV ECX, DWORD PTR DS : [SUPER_KEY_BASE];
			CALL GameCall;
		}
		nRet = TRUE;
	}
	__except (1){};
	return nRet;
}