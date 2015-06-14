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
DWORD XCall::SendGameMessage(DWORD dwMsg,WPARAM wParam,LPARAM lParam)  //������Ϣ�����߳�ִ��
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
DWORD XCall::GetRoleAddr()  //��ɫ��ַ
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
ULONG64 XCall::GetRoleID()  //ȡ��ɫid
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
DWORD XCall::GetRolePropertyAddr()  //ȡ��ɫ���Ե�ַ
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



BOOL XCall::PressGameKey(DWORD nkey, int nUpDown)  //����call
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

//״̬
int XCall::GetFightingState()  //��״̬
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
DWORD XCall::GetRoleMoveState()  ///�ƶ�״̬ ����ֵ����0x20004Ϊ���ƶ�����ֹͣΪ20001  ������Ϊ0x20002�����µ���0x20003
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
DWORD XCall::GetLearnedSkill1(DWORD skillID)   //ȡ��ѧ���ܵ�ַ1
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
DWORD XCall::GetLearnedSkill2(DWORD skillID)   //ȡ��ѧ���ܵ�ַ2
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

DWORD XCall::GetLearnedSkill3(DWORD skillID)   //ȡ��ѧ���ܵ�ַ3
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

bool XCall::CanReleaseSkill(DWORD slotAddr)		//�жϼ����Ƿ������ͷ�
{
	bool nRet = false;
	__try
	{
		if (IsBadReadPtr((void*)slotAddr,4))
			return nRet;
		int freezeflag = (int)*(BYTE*)(slotAddr + SLOT_SKILL_FREEZE_FLAG_OS);   //�Ƿ񶳽�
		int disableFlag = (int)*(BYTE*)(slotAddr + SLOT_SKILL_DISABLE_FLAG_OS);  //�Ƿ����,(��Χû��,�����)
		if (freezeflag == 0 && disableFlag == 0)
			nRet = true;

	}
	__except (1){};
	return nRet;
}

//bool XCall::CanReleaseSkill2(DWORD skillID)		//�жϼ����Ƿ������ͷ�
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
DWORD XCall::GetBuffSkillAddr(DWORD buffID)    // �������ܵ�ַ
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

BOOL XCall::PressSkillKey(int nIndex)  //��ݼ�
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
BOOL XCall::MoveSkillToKey(DWORD keyAddr,DWORD skillID)  //�ƶ����ܵ������
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

//����
bool XCall::ObjectIsFriend(ULONG64 ulObjID)     //�����Ƿ��Ѻ�
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
DWORD XCall::GetObjNameAddr(DWORD objAddr)    //ȡ�������ֵ�ַ
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
DWORD XCall::GetCollectNameAddr(DWORD objAddr)    //ȡ�ɼ������ֵ�ַ
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
DWORD XCall::GetObjProperty(ULONG64 ulObjID)  //ȡ�������Ե�ַ
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

int XCall::GetObjMaxFinesse(DWORD proAddr,int nIndex/*=0*/)  //ȡ������
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
int XCall::GetObjCurFinesse(DWORD proAddr,int nIndex/*=0*/)  //ȡ��ǰ����
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


int XCall::GetObjMaxBlood(DWORD proAddr)   //���Ѫֵ
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
int XCall::GetObjCurBlood(DWORD proAddr)	//��ǰѪֵ
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


int XCall::GetObjMaxInternal(DWORD proAddr)   //�����Ϣ
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
int XCall::GetObjCurInternal(DWORD proAddr)	//��ǰ��Ϣ
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

int XCall::GetObjMaxForce(DWORD proAddr)   //�����
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
int XCall::GetObjCurForce(DWORD proAddr)	//��ǰ����
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

int XCall::GetObjJob(DWORD proAddr)  //����ְҵ
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
int XCall::GetObjLevel(DWORD proAddr)  //����ȼ�
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
DWORD XCall::GetCollectItemPos(DWORD collectAddr) //ȡ�ɼ���Ʒ����
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

BOOL XCall::ChangeRoleAngle(PROLEANGLE pChangeAngle)  //�ı��ɫ�����call
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
		GameAddr += 0x10;  //��0x10�Ĳ���
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
//BOOL XCall::TalkNpc(ULONG64 ulNpcID)   //��npc�Ի�
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
BOOL XCall::ObjectCanAttack(ULONG64 ulObjID)  //�����Ƿ��ܹ���
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
BOOL XCall::ObjectCanAttack2(ULONG64 ulObjID)  //�����Ƿ��ܹ���
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
int XCall::GetObjType(ULONG64 ulObjID)  //ȡ��������call
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
BOOL XCall::PickAllItem()   //ȫ����Ʒcall
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




//Ѱ·
BOOL XCall::FindPath(float desX,float desY)  //Ѱ·call
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
DWORD XCall::GetMapInfoAddr(DWORD mapID)  //ȡ ��ͼ��ϸ��ַ
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
tstring XCall::GetMapName(DWORD mapID)   //ȡ��ͼ����
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
DWORD XCall::GetAreaNameAddr(DWORD mapID,float desX,float desY)  //ȡ�������ֵ�ַ
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
tstring XCall::GetMapAreaName(DWORD mapID,float desX,float desY)   //ȡ��ͼ��������
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

//�Ự
ULONG64 XCall::GetResponseNpcID()   //ȡ�Ի�npc��ID
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

DWORD XCall::GetObjServerID(ULONG64 objID)  //ȡ���������ID
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
DWORD XCall::GetResponseItemList()  //ȡ��ǰ�Ựѡ���б��ַ
{
	DWORD nRet = 0;
	__try
	{
		ULONG64 curNpcID = XCall::GetResponseNpcID();
		//DbgLog(_T("��ǰ�Ի�NPC��ID:%llX"),curNpcID);
		if(curNpcID == 0 || curNpcID == -1)
			return nRet;
		DWORD npcServerID = XCall::GetObjServerID(curNpcID);
		//DbgLog(_T("��ǰ�Ի�NPC�ķ�����ID:%X"),npcServerID);
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
BOOL XCall::GetResponseItemState(DWORD responseAddr)  //ȡ�Ựѡ��״̬call
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



BOOL XCall::PressResponseItem(int nType,DWORD responseID1,DWORD responseID2,int nIndex)  //�Ựѡ��call
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
DWORD XCall::GetUIAddr(DWORD dwFlagAddr)  //ȡUI��ַ
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
DWORD XCall::GetUIAddr(TCHAR* szUIName)   //����UI��ַ
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

DWORD XCall::GetResponseDlg()    //ȡnpc�Ի��� ��ַ
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

//����
DWORD XCall::GetQuestAddr(DWORD questID)  //ȡ�����ַ
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

DWORD XCall::GetQuestName(DWORD questID)  //ȡ��������ַ
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
DWORD XCall::GetJianWenInfo(DWORD questID)  //ȡ����������ϸ��ַ
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
DWORD XCall::GetHuaBenProgress(int nQuestIndex)   //ȡ������ɽ��ȵ�ַ
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
BOOL XCall::GetJianWenQuest(DWORD questID)   //ȡ��������״̬call
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
BOOL XCall::GetPlotEventAcceptState(DWORD EventID)   //Plot Event�Ƿ��ܽ���
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
BOOL XCall::GetPlotEventCompleteState(DWORD EventID)   //Plot Event�Ƿ������
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

//��Ʒ
DWORD XCall::GetItemAddr(ULONG64 itemID)  //ȡ��Ʒ��ַ
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
	if (pRecParam->mRetValue != 0)   //���ҵ��˾�ֱ�ӷ���
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

BOOL XCall::RightPressSlot(DWORD SlotAddr)   //�����������(������)
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
BOOL XCall::LeftPressSlot(DWORD SlotAddr)   //�Ҽ���������(�Ҽ�ʹ����Ʒ,װ��,�������Ʒ)
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

//DWORD XCall::GetItemAddr2(ULONG64 itemID)  //ȡ��Ʒ��ַ  ��� vm����.   �����Լ�дһ��. 
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
//BOOL XCall::UseGoods(ULONG64 itemID,int nIndex)  //ʹ����Ʒ
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
//BOOL XCall::UseEquip(int nIndex)  //ʹ��װ��  index=�����±�
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


BOOL XCall::ItemIsGoodsType(DWORD itemAddr)  //��Ʒ�Ƿ��ǻ���
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
BOOL XCall::ItemIsEquipType(DWORD itemAddr)  //��Ʒ�Ƿ���װ��
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
BOOL XCall::EquipCanUse(DWORD itemServerID)  //װ���Ƿ���װ��
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

int XCall::GetEquipCurUseAge(DWORD itemAddr) //��Ʒ�;ö�
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
int XCall::GetEquipMaxUseAge(DWORD itemAddr)  //��Ʒ����;ö�
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
BOOL XCall::GetEquipAttribute(DWORD itemAddr,PITEMATTRIBUTE pItemAttri)  //ȡװ������
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

//DWORD XCall::GetItemInfoAddr(DWORD itemID)  //ȡ��Ʒ��ϸ��ַ by������ID
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
BOOL XCall::SellItemCall(int nIndex)  //������Ʒcall
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
BOOL XCall::BuyItemCall(DWORD ItemId,int nNum)   //����call
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
//���͵�
DWORD XCall::GetTransferInfoAddr(DWORD transferID)   //ȡ���͵���ϸ��ַ
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
float XCall::GetTransferFreezeTime()   //ȡ���͵㶳��ʣ��ʱ��
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
BOOL XCall::PressTransferPoint(int transferIndex,DWORD mapID)   //���͵㴫��
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

//���
BOOL XCall::InvitePlayerInTeam(DWORD PlayerID1,DWORD PlayerID2,char* szPlayerName)  //������ӷ���
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
BOOL XCall::AcceptPlayerInTeam(DWORD PlayerID1,DWORD PlayerID2)  //������ӷ���
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

BOOL XCall::PlayerQuitTeam()  //�뿪��ӷ���
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
BOOL XCall::ChangeTeamLeader(DWORD PlayerID1,DWORD PlayerID2) //ת�öӳ�����
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
BOOL XCall::KickOutTeam(DWORD PlayerID1,DWORD PlayerID2)		//������鷢��
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
BOOL XCall::ChangeThread(DWORD threadID1,DWORD threadID2)   //�л���·
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

//����
BOOL XCall::CreateCharacter(char* szCharacterName,int nJob,BOOL nFemale,BYTE* pCharacterData)  //������ɫcall
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

BOOL XCall::EnterGame(int nIndex)   //������Ϸ
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


//����
BOOL XCall::SendPacket(DWORD dwMsg,char* pData,int nLen)   //����call
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
BOOL XCall::RevivePacket(BOOL bSamePlace/*=FALSE*/)  //����
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

BOOL XCall::JoinMengHui(int nID)  //�����˻�call
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

BOOL XCall::DellMail(DWORD mailID1,DWORD mailID2)   //ɾ���ʼ�
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
BOOL XCall::TakeAppend(DWORD mailID1,DWORD mailID2)   //��ȡ�ʼ�����
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

BOOL XCall::ClickGameKey(DWORD nkey, int nCtrl/* = 0*/)  //����call
{
	SUPERKEYINFO keyInfo, ctrlInfo;
	ZeroMemory(&keyInfo, sizeof(SUPERKEYINFO));
	ZeroMemory(&ctrlInfo, sizeof(SUPERKEYINFO));

	keyInfo.dwKeyType = 5;
	keyInfo.dwSupperKey = nkey;
	keyInfo.dwKeyUp = 0;   //����
	if (nCtrl == 1)
	{
		ctrlInfo.dwKeyType = 5;
		ctrlInfo.dwSupperKey = VK_CONTROL;
		ctrlInfo.dwKeyUp = 0;   //����

		keyInfo.bCtrl = true;
	}
	else if (nCtrl == 2)
	{
		ctrlInfo.dwKeyType = 5;
		ctrlInfo.dwSupperKey = VK_SHIFT;
		ctrlInfo.dwKeyUp = 0;   //����

		keyInfo.bShift = true;
	}
	else if (nCtrl == 3)
	{
		ctrlInfo.dwKeyType = 5;
		ctrlInfo.dwSupperKey = VK_MENU;
		ctrlInfo.dwKeyUp = 0;   //����

		keyInfo.bMenu = true;
	}

	if (nkey == 0x57)
	{  //W��
		keyInfo.bKeyW = true;
	}
	else if (nkey == 0x53)
	{  //S��
		keyInfo.bKeyS = true;
	}
	else if (nkey == 0x41)
	{  //A��
		keyInfo.bKeyA = true;
	}
	else if (nkey == 0x43)
	{  //D��
		keyInfo.bKeyD = true;
	}
	if (nCtrl > 0)  
		XCall::PressKey(&ctrlInfo);

	XCall::PressKey(&keyInfo);   //����

	keyInfo.dwKeyUp = 1;
	XCall::PressKey(&keyInfo);   //����

	ctrlInfo.dwKeyUp = 1;
	if (nCtrl > 0) 
		XCall::PressKey(&ctrlInfo);  //ctrl����
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