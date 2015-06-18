#include "stdafx.h"
#include "FunctionCall.h"
#include "XCall.h"

#pragma region ���»�ȡ����
//��ȡ��ɫ��Ϣ
void FGetPlayerInfo(PlayerInfo& player)
{
	//ȡ��ɫ��ַ
	DWORD ObjAddr = XCall::GetRoleAddr();
	do
	{
		if (IsBadReadPtr((void*)ObjAddr, 4))
			break;
		int nCurBlood = 0, nMaxBlood = 0, nCurForce = 0, nMaxForce = 0;
		int nJob = -1, nLevel = -1;
		tstring objName;
		CString strTmp;

		ULONG64 ObjID = *(ULONG64*)(ObjAddr + OBJECT_ID_OS);
		if (ObjID == 0 || ObjID == -1)
			break;


		float objX = 0;
		float objY = 0;
		DWORD objPosAddr = XCall::GetCollectItemPos(ObjAddr);
		if (objPosAddr)
		{
			objX = *(float*)objPosAddr;
			objY = *(float*)(objPosAddr + 4);
		}

		DWORD NameAddr = XCall::GetObjNameAddr(ObjAddr);
		if (NameAddr)
			objName = XCall::UTF2T((char*)NameAddr);

		DWORD proAddr = XCall::GetObjProperty(ObjID);
		if (proAddr)
		{
			nCurBlood = XCall::GetObjCurBlood(proAddr);
			nMaxBlood = XCall::GetObjMaxBlood(proAddr);
			nCurForce = XCall::GetObjCurForce(proAddr);
			nMaxForce = XCall::GetObjMaxForce(proAddr);
			nJob = XCall::GetObjJob(proAddr);
			nLevel = XCall::GetObjLevel(proAddr);
		}
		int nType = XCall::GetObjType(ObjID);
		//BOOL bFriend = (BOOL)XCall::ObjectIsFriend(ObjID);
		//BOOL bAttack = XCall::ObjectCanAttack(ObjID);
		player.HP = nCurBlood;
		player.Level = nLevel;
		player.MaxHP = nMaxBlood;
		player.MP = nCurForce;
		player.MaxMP = nMaxForce;
		player.X = objX;
		player.Y = objY;
		strTmp.Format(_T("��ɫ��ַ:%X,���Ե�ַ:%X,Ѫ:%d/%d,����:%d/%d,ְҵ:%d,����:%d,LV:%d,����:%f,%f,����:%s\r\n"),
			ObjAddr, proAddr, nCurBlood, nMaxBlood, nCurForce, nMaxForce, nJob, nType, nLevel, objX, objY, objName.c_str());
		::OutputDebugString(strTmp);
	} while (0);

}

//��ȡ��Χ����
void VisitMonList(DWORD CurList, CString &str);
void FGetRoundMonsterInfo(std::vector<MonsterInfo>& monsterList)
{
//	((CEdit *)GetDlgItem(IDC_EDIT1))->SetWindowText(_T(""));
	CString str;
	DWORD GameBase = *(DWORD*)GAME_BASE;
	if (IsBadReadPtr((void*)(GameBase), 4))
		return;
	do
	{
		str += _T("��Χnpc���:\r\n");
		OutputDebugString(L"��Χ����--------------------");
		DWORD ListAddr = *(DWORD*)(GameBase + NEARLY_OBJECT_LIST_OS1);
		if (IsBadReadPtr((void*)(ListAddr), 4))
			break;
		DWORD ListHead = *(DWORD*)(ListAddr + NEARLY_OBJ_LIST_POINT_OS);
		if (IsBadReadPtr((void*)(ListHead), 4))
			break;
		int nMaxCount = *(int*)(ListAddr + NEARLY_OBJ_LIST_POINT_OS + 4);
		if (nMaxCount > 0x0FFF)
			break;
		for (int i = 0; i<nMaxCount; i++)
		{
			DWORD CurList = ListHead + i * 4;
			if (IsBadReadPtr((void*)CurList, 4))
				break;
			CurList = *(DWORD*)(CurList);
			if (IsBadReadPtr((void*)CurList, 4))
				continue;
			VisitMonList(CurList, monsterList);
		}
	} while (0);
}
void VisitMonList(DWORD CurList, std::vector<MonsterInfo>& monsterList)
{
	if (IsBadReadPtr((void*)CurList, 4))
		return;

	DWORD ObjAddr = *(DWORD*)(CurList + 0x8);

	do
	{
		if (IsBadReadPtr((void*)ObjAddr, 4))
			break;
		int nCurBlood = 0, nMaxBlood = 0, nCurForce = 0, nMaxForce = 0;
		int nJob = -1, nLevel = -1;
		tstring objName;
		CString strTmp;

		ULONG64 ObjID = *(ULONG64*)(ObjAddr + OBJECT_ID_OS);
		if (ObjID == 0 || ObjID == -1)
			break;

		//float objX = *(float*)(ObjAddr + OBJECT_POS_OS);
		//float objY = *(float*)(ObjAddr + OBJECT_POS_OS + 4);
		float objX = 0;
		float objY = 0;
		DWORD objPosAddr = XCall::GetCollectItemPos(ObjAddr);
		if (objPosAddr)
		{
			objX = *(float*)objPosAddr;
			objY = *(float*)(objPosAddr + 4);
		}

		DWORD NameAddr = XCall::GetObjNameAddr(ObjAddr);
		if (NameAddr)
			objName = XCall::UTF2T((char*)NameAddr);

		DWORD proAddr = XCall::GetObjProperty(ObjID);
		if (proAddr)
		{
			nCurBlood = XCall::GetObjCurBlood(proAddr);
			nMaxBlood = XCall::GetObjMaxBlood(proAddr);
			nCurForce = XCall::GetObjCurForce(proAddr);
			nMaxForce = XCall::GetObjMaxForce(proAddr);
			nJob = XCall::GetObjJob(proAddr);
			nLevel = XCall::GetObjLevel(proAddr);
		}
		int nType = XCall::GetObjType(ObjID);
		BOOL bFriend = (BOOL)XCall::ObjectIsFriend(ObjID);
		BOOL bAttack = XCall::ObjectCanAttack(ObjID);
		MonsterInfo	monster;
		monster.HP = nCurBlood;
		monster.x = objX;
		monster.y = objY;
		monster.level = nLevel;
		monster.frd = bFriend;
		monster.name = objName
		monsterList.push_back(monster);
		strTmp.Format(_T("��ַ:%X,���Ե�ַ:%X,�Ѻ�:%d/%d,Ѫ:%d/%d,����:%d/%d,ְҵ:%d,����:%d,LV:%d,����:%f,%f,����:%s\r\n"),
			ObjAddr, proAddr, bFriend, bAttack, nCurBlood, nMaxBlood, nCurForce, nMaxForce, nJob, nType, nLevel, objX, objY, objName.c_str());
		::OutputDebugString(strTmp);
		//str += strTmp;

	} while (0);

	DWORD b10 = *(DWORD*)(CurList + 0x10);
	if (!IsBadReadPtr((void*)b10, 4))
		VisitMonList(b10, str);

}
//��ȡ��Χ����б�
void FGetRoundPlayerInfo()
{
	//	((CEdit *)GetDlgItem(IDC_EDIT1))->SetWindowText(_T(""));
	CString str;
	DWORD GameBase = *(DWORD*)GAME_BASE;
	if (IsBadReadPtr((void*)(GameBase), 4))
		return;
	do
	{
		str += _T("��Χ���:\r\n");
		DWORD ListAddr = *(DWORD*)(GameBase + NEARLY_OBJECT_LIST_OS2);
		if (IsBadReadPtr((void*)(ListAddr), 4))
			break;
		DWORD ListHead = *(DWORD*)(ListAddr + NEARLY_OBJ_LIST_POINT_OS);
		if (IsBadReadPtr((void*)(ListHead), 4))
			break;
		int nMaxCount = *(int*)(ListAddr + NEARLY_OBJ_LIST_POINT_OS + 4);
		if (nMaxCount > 0x0FFF)
			break;
		for (int i = 0; i<nMaxCount; i++)
		{
			DWORD CurList = ListHead + i * 4;
			if (IsBadReadPtr((void*)CurList, 4))
				break;
			CurList = *(DWORD*)(CurList);
			if (IsBadReadPtr((void*)CurList, 4))
				continue;
			VisitMonList(CurList, str);
		}
	} while (0);
}
void FGetSkillInfo()
{
	DWORD GameAddr = *(DWORD*)(QSSLOT_MANAGER_BASE);
	if (IsBadReadPtr((void*)GameAddr, 4))
		return;
	DWORD ListHead = *(DWORD*)(GameAddr + KEY_ARRARY_OS);
	if (IsBadReadPtr((void*)ListHead, 4))
		return;
	DWORD ListEnd = *(DWORD*)(GameAddr + KEY_ARRARY_OS + 4);
	if (IsBadReadPtr((void*)ListEnd, 4))
		return;
	if (ListHead >= ListEnd)  //û�г�Ա,������P
		return;
	int maxCount = (ListEnd - ListHead) / 4;
	for (int i = 0; i<maxCount; i++)
	{
		DWORD curList = ListHead + i * 0x4;
		if (IsBadReadPtr((void*)curList, 4) || curList > ListEnd)
			break;
		DWORD CurKeyAddr = *(DWORD*)(curList);
		if (IsBadReadPtr((void*)CurKeyAddr, 4))
			continue;
		int nSlotType = *(int*)(CurKeyAddr + 8);   //��������
		int nItemType = *(int*)(CurKeyAddr + 0xC);  //��������
		do
		{
			if (nSlotType == 5)
			{   //��ݼ���
				DWORD skillID = *(DWORD*)(CurKeyAddr + KEY_SKILL_ID_OS);
				DWORD skillAddr1 = XCall::GetLearnedSkill3(skillID);
				DWORD skillAddr2 = XCall::GetLearnedSkill2(skillID);
				tstring skillName;
				if (skillAddr2)
				{
					char* putf8Name = (char*)*(DWORD*)(skillAddr2 + 4);
					if (!IsBadReadPtr((void*)putf8Name, 4))
					{
						skillName = XCall::UTF2T(putf8Name);
					}
				}
				BOOL canRelease = (BOOL)XCall::CanReleaseSkill(CurKeyAddr);
				CString strTmp;
				strTmp.Format(_T("��ݼ�:%d,key:%X,��ַ:%X,����ID:%X,�ͷ�:%d,����:%s\r\n"),
					i, CurKeyAddr, skillAddr1, skillID, canRelease, skillName.c_str());
				::OutputDebugString(strTmp);
			}
		} while (0);
	}
}
#pragma endregion comment

#pragma region ����
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ת��
void FChangeAngle(double angle)
{
	ROLEANGLE face;
	face.dwSinAngle = sin(angle);
	face.dwCosAngle = cos(angle);
	face.dwUnknowAngle = 0;
	XCall::ChangeRoleAngle(&face);
}
#pragma endregion comment

#pragma region ����

#pragma endregion comment