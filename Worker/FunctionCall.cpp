#include "stdafx.h"
#include "FunctionCall.h"
#include "XCall.h"
#define SUCCESS 0
#define CALL_FAIL 1
#define DEBUGVIEW
#pragma region 更新获取数据
//获取角色信息
void FGetPlayerInfo(PlayerInfo& player)
{
	//取角色地址
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
		player.X = objX;
		player.Y = objY;
		player.HP = nCurBlood;
		player.MaxHP = nMaxBlood;
		player.Level = nLevel;
		player.MP = nCurForce;
		player.MaxMP = nMaxForce;

		char* pName = (char*)objName.c_str();
		int nLen = objName.size() * 2;
		for (int i = 0; i < nLen; ++i)
			player.name.push_back(*(pName + i));

		strTmp.Format(_T("角色地址:%X,属性地址:%X,血:%d/%d,定力:%d/%d,职业:%d,类型:%d,LV:%d,坐标:%f,%f,名字:%s\r\n"),
			ObjAddr, proAddr, nCurBlood, nMaxBlood, nCurForce, nMaxForce, nJob, nType, nLevel, objX, objY, objName.c_str());
		::OutputDebugString(strTmp);
	} while (0);
}

int FGetPlayerPos(PosInfo& pPos)
{
	int nRet = CALL_FAIL;
	//取角色地址
	DWORD ObjAddr = XCall::GetRoleAddr();
	do
	{
		if (IsBadReadPtr((void*)ObjAddr, 4))
			break;
	
		ULONG64 ObjID = *(ULONG64*)(ObjAddr + OBJECT_ID_OS);
		if (ObjID == 0 || ObjID == -1)
			break;

		//float objX = 0;
		//float objY = 0;
		DWORD objPosAddr = XCall::GetCollectItemPos(ObjAddr);
		if (objPosAddr)
		{
			pPos.x = *(float*)objPosAddr;
			pPos.y = *(float*)(objPosAddr + 4);
		}
#ifdef DEBUGVIEW
		CString strTmp;
		strTmp.Format(_T("角色坐标:%f,%f\r\n"),pPos.x, pPos.y);
		::OutputDebugString(strTmp);
#endif
		nRet = SUCCESS;
	} while (0);
	return nRet;
}

//获取周围怪物
void VisitMonList(DWORD CurList, std::vector<MonsterInfo>& MonsterList);
void FGetRoundMonsterInfo(std::vector<MonsterInfo>& MonsterList)
{
//	((CEdit *)GetDlgItem(IDC_EDIT1))->SetWindowText(_T(""));
	CString str;
	DWORD GameBase = *(DWORD*)GAME_BASE;
	if (IsBadReadPtr((void*)(GameBase), 4))
		return;
	do
	{
		str += _T("周围npc或怪:\r\n");
		OutputDebugString(L"周围怪物--------------------");
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
			VisitMonList(CurList, MonsterList);
		}
	} while (0);
}
void VisitMonList(DWORD CurList, std::vector<MonsterInfo>& MonsterList)
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

		MonsterInfo monster;
		monster.HP = nCurBlood;

		monster.frd = bFriend;
		monster.level = nLevel;
		monster.force = nCurForce;
		monster.x = objX;
		monster.y = objY;
		char* pName = (char*)objName.c_str();
		int nLen = objName.size() * 2;
		for (int i = 0; i < nLen;++i)
			monster.name.push_back(*(pName+i));

		MonsterList.push_back(monster);

		strTmp.Format(_T("地址:%X,属性地址:%X,友好:%d/%d,血:%d/%d,定力:%d/%d,职业:%d,类型:%d,LV:%d,坐标:%f,%f,名字:%s\r\n"),
			ObjAddr, proAddr, bFriend, bAttack, nCurBlood, nMaxBlood, nCurForce, nMaxForce, nJob, nType, nLevel, objX, objY, objName.c_str());
		::OutputDebugString(strTmp);
		//str += strTmp;

	} while (0);

	DWORD b10 = *(DWORD*)(CurList + 0x10);
	if (!IsBadReadPtr((void*)b10, 4))
		VisitMonList(b10, MonsterList);

}
//获取周围玩家列表
void FGetRoundPlayerInfo()
{
	//	((CEdit *)GetDlgItem(IDC_EDIT1))->SetWindowText(_T(""));
	CString str;
	DWORD GameBase = *(DWORD*)GAME_BASE;
	if (IsBadReadPtr((void*)(GameBase), 4))
		return;
	do
	{
		str += _T("周围玩家:\r\n");
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
		//	VisitMonList(CurList, str);
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
	if (ListHead >= ListEnd)  //没有成员,遍历个P
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
		int nSlotType = *(int*)(CurKeyAddr + 8);   //容器类型
		int nItemType = *(int*)(CurKeyAddr + 0xC);  //数据类型
		do
		{
			if (nSlotType == 5)
			{   //快捷键栏
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
				strTmp.Format(_T("快捷键:%d,key:%X,地址:%X,对像ID:%X,释放:%d,名字:%s\r\n"),
					i, CurKeyAddr, skillAddr1, skillID, canRelease, skillName.c_str());
				::OutputDebugString(strTmp);
			}
		} while (0);
	}
}
int FGetSkillReleaseInfo(std::vector<int>& SkillList) //获取技能的可释放信息,25个,1-0,QERTG,CTRL1-5,F1-5
{
	DWORD GameAddr = *(DWORD*)(QSSLOT_MANAGER_BASE);
	if (IsBadReadPtr((void*)GameAddr, 4))
		return CALL_FAIL;
	DWORD ListHead = *(DWORD*)(GameAddr + KEY_ARRARY_OS);
	if (IsBadReadPtr((void*)ListHead, 4))
		return CALL_FAIL;
	DWORD ListEnd = *(DWORD*)(GameAddr + KEY_ARRARY_OS + 4);
	if (IsBadReadPtr((void*)ListEnd, 4))
		return CALL_FAIL;
	if (ListHead >= ListEnd)  //没有成员,遍历个P
		return CALL_FAIL;
	int maxCount = (ListEnd - ListHead) / 4;
	for (int i = 0; i<maxCount; i++)
	{
		DWORD curList = ListHead + i * 0x4;
		if (IsBadReadPtr((void*)curList, 4) || curList > ListEnd)
			break;
		DWORD CurKeyAddr = *(DWORD*)(curList);
		if (IsBadReadPtr((void*)CurKeyAddr, 4))
			continue;
		int nSlotType = *(int*)(CurKeyAddr + 8);   //容器类型
		int nItemType = *(int*)(CurKeyAddr + 0xC);  //数据类型
		do
		{
			if (nSlotType == 5)
			{   //快捷键栏
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
				strTmp.Format(_T("快捷键:%d,key:%X,地址:%X,对像ID:%X,释放:%d,名字:%s\r\n"),
					i, CurKeyAddr, skillAddr1, skillID, canRelease, skillName.c_str());
				::OutputDebugString(strTmp);
			}
		} while (0);
	}
	return SUCCESS;
}

int FGetSlotSkill(std::vector<SlotSkillInfo>& SkillList) //面板技能，带按键槽地址,25个,1-0,QERTG,CTRL1-5,F1-5
{
	return SUCCESS;
}
int FGetLearnedSkill(std::vector<SkillInfo>& SkillList)  //已学技能
{
	//((CEdit *)GetDlgItem(IDC_EDIT1))->SetWindowText(_T(""));
	CString str, strTmp;

	DWORD GameAddr = *(DWORD*)(GAME_BASE);
	if (IsBadReadPtr((void*)GameAddr, 4))
		return CALL_FAIL;
	GameAddr = *(DWORD*)(GameAddr + LEARNED_SKILL_ID_LIST_OS);
	if (IsBadReadPtr((void*)GameAddr, 4))
		return CALL_FAIL;
	DWORD ListHead = *(DWORD*)(GameAddr + 0);
	if (IsBadReadPtr((void*)ListHead, 4))
		return CALL_FAIL;
	DWORD ListEnd = *(DWORD*)(GameAddr + 4);
	if (IsBadReadPtr((void*)ListEnd, 4))
		return CALL_FAIL;
	if (ListHead >= ListEnd)  //没有成员,遍历个P
		return CALL_FAIL;
	int maxCount = (ListEnd - ListHead) / 0xC;
	for (int i = 0; i<maxCount; i++)
	{
		DWORD curList = ListHead + i * 0xC;
		if (IsBadReadPtr((void*)curList, 4))
			break;
		DWORD skillID = *(DWORD*)curList;

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

		BOOL canRelease = 0;// (BOOL)XCall::CanReleaseSkill(skillID);
		SkillInfo temp;
		char* pName = (char*)skillName.c_str();
		int nLen = skillName.size() * 2;
		for (int i = 0; i < nLen; ++i)
			temp.name.push_back(*(pName + i));
		temp.SkillID = skillID;
		temp.CanRelease = canRelease;
		SkillList.push_back(temp);
#ifdef DEBUGVIEW
		CString strTmp;
		strTmp.Format(_T("ListLearnedSkill地址:%X/%X,对像ID:%X,释放:%d,名字:%s\r\n"),
			skillAddr1, skillAddr2, skillID, canRelease, skillName.c_str());
		::OutputDebugString(strTmp);
#endif
		//str += strTmp;
	}
	//((CEdit *)GetDlgItem(IDC_EDIT1))->SetWindowText(str);
	return SUCCESS;
}
void FListBuffSkill() //辅助技能列表
{
//	((CEdit *)GetDlgItem(IDC_EDIT1))->SetWindowText(_T(""));
//	CString str;
	DWORD GameAddr = XCall::GetRolePropertyAddr();
	if (IsBadReadPtr((void*)GameAddr, 4))
		return;
	DWORD CurList = *(DWORD*)(GameAddr + ROLE_STATE_LIST_OS);
	if (IsBadReadPtr((void*)CurList, 4))
		return;
	DWORD ListEnd = *(DWORD*)(GameAddr + ROLE_STATE_LIST_OS + 4);
	if (IsBadReadPtr((void*)ListEnd, 4))
		return;
	CString strTmp;
	while (CurList < ListEnd)
	{
		do
		{
			DWORD buffID = *(DWORD*)(CurList + 0);
			if (buffID == 0 || buffID == -1)
				break;
			DWORD buffAddr = XCall::GetBuffSkillAddr(buffID);
			if (!buffAddr)
				break;
			tstring strBuffName;
			char* buffName = (char*)*(DWORD*)(buffAddr + 4);
			if (!IsBadReadPtr((void*)buffName, 4))
				strBuffName = XCall::UTF2T(buffName);

			strTmp.Format(_T("辅助技能地址:%X,ID:%X,名:%s \r\n"),
				buffAddr, buffID, strBuffName.c_str());
			::OutputDebugString(strTmp);
		//	str += strTmp;
		} while (0);

		CurList += ROLE_STATE_LIST_MEMBER_SIZE;
		if (IsBadReadPtr((void*)CurList, 4))
			break;
	}
//	((CEdit *)GetDlgItem(IDC_EDIT1))->SetWindowText(str);
}
//任务
void FListAcceptedQuest()  //已接任务
{
//	((CEdit *)GetDlgItem(IDC_EDIT1))->SetWindowText(_T(""));
	CString str;
	DWORD GameBase = *(DWORD*)GAME_BASE;
	if (IsBadReadPtr((void*)(GameBase), 4))
		return;
	DWORD ListHead = *(DWORD*)(GameBase + ACCEPTED_QUEST_LIST_OS);
	if (IsBadReadPtr((void*)(ListHead), 4))
		return;
	DWORD CurList = *(DWORD*)(ListHead + ACCEPTED_QUEST_ID_LIST_OS);
	if (IsBadReadPtr((void*)(CurList), 4))
		return;
	DWORD ListEnd = *(DWORD*)(ListHead + ACCEPTED_QUEST_ID_LIST_OS + 4);
	if (IsBadReadPtr((void*)(ListEnd), 4))
		return;
	CString strTmp;
	while (CurList < ListEnd)
	{
		if (IsBadReadPtr((void*)(CurList), 4))
			break;
		DWORD QuestID = *(DWORD*)CurList;
		DWORD curQuestAddr = XCall::GetQuestAddr(QuestID);
		if (curQuestAddr)
		{
			tstring strQuestName;
			char* questName = (char*)XCall::GetQuestName(QuestID);
			if (questName)
				strQuestName = XCall::UTF2T(questName);

			strTmp.Format(_T("地址:%X,任务ID:%X,任务名:%s \r\n"),
				curQuestAddr, QuestID, strQuestName.c_str());
			::OutputDebugString(strTmp);
			//str += strTmp;

			DWORD CurStepList = *(DWORD*)(curQuestAddr + QUEST_STEP_LIST_OS);
			DWORD StepListEnd = *(DWORD*)(curQuestAddr + QUEST_STEP_LIST_OS + 4);
			if (!IsBadReadPtr((void*)CurStepList, 4) && !IsBadReadPtr((void*)StepListEnd, 4)
				&& CurStepList < StepListEnd)
			{
				while (CurStepList < StepListEnd)
				{
					if (IsBadReadPtr((void*)(CurStepList), 4))
						break;
					DWORD curQuestStep = *(DWORD*)(CurStepList);
					if (!IsBadReadPtr((void*)(curQuestStep), 4))
					{
						int nType = *(DWORD*)(curQuestStep + QUEST_STEP_TYPE_OS);
						DWORD storyID = *(DWORD*)(curQuestStep + QUEST_STEP_TYPE_OS + 4);
						int curNum = *(DWORD*)(curQuestStep + 0);
						int maxNum = *(DWORD*)(curQuestStep + 4);
						if (nType != 0x10/* && nType != 0x14 */)
						{
							tstring strStepName;
							char* stepName = (char*)*(DWORD*)(curQuestStep + QUEST_STEP_NAME_OS);
							if (!IsBadReadPtr((void*)stepName, 4))
								strStepName = XCall::UTF2T(stepName);

							strTmp.Format(_T("	地址:%X,类型:%X,状态:%d/%d,名:%s \r\n"),
								curQuestAddr, nType, curNum, maxNum, strStepName.c_str());
							::OutputDebugString(strTmp);
							//str += strTmp;

							if (nType == 0x14) //此为剧情任务
							{
								//ShowAcceptedQuest(storyID,str);

								tstring strStoryQuest;
								char* storyQuest = (char*)*(DWORD*)(QUEST_TRACK_TEXT_BASE);
								if (!IsBadReadPtr((void*)storyQuest, 4))
									strStoryQuest = XCall::UTF2T(storyQuest);

								strTmp.Format(_T("		剧情字串:%s \r\n"), strStoryQuest.c_str());
								::OutputDebugString(strTmp);
								//str += strTmp;
							}
						}//else ShowAcceptedQuest(storyID,str);
					}
					CurStepList += 4;
				}
			}
			else
			{
			//	str += _T("	状态:已完成或未接任务\r\n");
				::OutputDebugString(_T("	状态:已完成或未接任务\r\n"));
			//	::OutputDebugString(strTmp);
			}
		}
		CurList += 4;
	}

	//((CEdit *)GetDlgItem(IDC_EDIT1))->SetWindowText(str);
}
void FVisitNomalResponse(DWORD CurList, CString &str);
void FListNomalResponse()  //当前普通会话
{

	CString str, strTmp;;
//	((CEdit *)GetDlgItem(IDC_EDIT1))->GetWindowText(str);
	str += _T("\r\n普通会话,类型4 \r\n");
	::OutputDebugString(str);
	DWORD GameAddr = *(DWORD*)GAME_BASE;
	if (IsBadReadPtr((void*)(GameAddr), 4))
		return;
	GameAddr = *(DWORD*)(GameAddr + NOMAL_RESPONSE_ITEM_LIST_OS);
	if (IsBadReadPtr((void*)(GameAddr), 4))
		return;

	DWORD CurList = *(DWORD*)(GameAddr + NOMAL_RESPONSE_LIST_OS);
	if (IsBadReadPtr((void*)(CurList), 4))
		return;

	int nCount = *(int*)(GameAddr + NOMAL_RESPONSE_LIST_OS + 4);
	if (nCount > 0 && nCount < 50)
	for (int i = 0; i < nCount; i++)
	{
		DWORD curAddr = CurList + i * 4;
		if (IsBadReadPtr((void*)curAddr, 4))
			break;
		DWORD NodeAddr = *(DWORD*)curAddr;
		if (IsBadReadPtr((void*)NodeAddr, 4))
			continue;
		do
		{
			DWORD DataAddr = *(DWORD*)(NodeAddr + 0x4);
			if (IsBadReadPtr((void*)DataAddr, 4))
				break;
			DWORD responseID = *(DWORD*)(DataAddr + 8);  //会话id
			DWORD NpcID1 = *(DWORD*)(DataAddr + 0x10);
			DWORD NpcID2 = *(DWORD*)(DataAddr + 0x14);

			BOOL bState = XCall::GetResponseItemState(DataAddr);


			char* responseText = (char*)*(DWORD*)(DataAddr + 0x1C);
			tstring strResponse;
			if (!IsBadReadPtr((void*)responseText, 4))
				strResponse = XCall::UTF2T(responseText);

			strTmp.Format(_T("地址:%X,会话ID:%X,状态:%d,npcID1:%X/%X,字串:%s\r\n"),
				DataAddr, responseID, bState, NpcID1, NpcID2, strResponse.c_str());
			::OutputDebugString(strTmp);
			//str += strTmp;

		} while (0);
		DWORD b8 = *(DWORD*)(CurList + 8);
		if (!IsBadReadPtr((void*)b8, 4))
			FVisitNomalResponse(b8, str);
	}

	//((CEdit *)GetDlgItem(IDC_EDIT1))->SetWindowText(str);
}
void FVisitNomalResponse(DWORD CurList, CString &str)
{
	if (IsBadReadPtr((void*)(CurList), 4))
		return;
	if (IsBadReadPtr((void*)CurList, 4))
		return;
	CString strTmp;

	do
	{
		DWORD DataAddr = *(DWORD*)(CurList + 0x4);
		if (IsBadReadPtr((void*)DataAddr, 4))
			break;
		DWORD responseID = *(DWORD*)(DataAddr + 8);  //会话id
		DWORD NpcID1 = *(DWORD*)(DataAddr + 0x10);
		DWORD NpcID2 = *(DWORD*)(DataAddr + 0x14);

		BOOL bState = XCall::GetResponseItemState(DataAddr);


		char* responseText = (char*)*(DWORD*)(DataAddr + 0x1C);
		tstring strResponse;
		if (!IsBadReadPtr((void*)responseText, 4))
			strResponse = XCall::UTF2T(responseText);

		strTmp.Format(_T("地址:%X,会话ID:%X,状态:%d,npcID1:%X/%X,字串:%s\r\n"),
			DataAddr, responseID, bState, NpcID1, NpcID2, strResponse.c_str());
		::OutputDebugString(strTmp);
		//str += strTmp;

	} while (0);

	DWORD b8 = *(DWORD*)(CurList + 8);
	if (!IsBadReadPtr((void*)b8, 4))
		FVisitNomalResponse(b8, str);
}

void FListQuestResponse()  //当前任务会话
{
	CString str;
	//((CEdit *)GetDlgItem(IDC_EDIT1))->GetWindowText(str);
	str += _T("\r\n任务会话,类型2 \r\n");
	::OutputDebugString(str);
	DWORD ListAddr = XCall::GetResponseItemList();
	//DbgLog(_T("当前对话NPC的会话列表地址:%X"), ListAddr);
	if (IsBadReadPtr((void*)(ListAddr), 4))
		return;
	DWORD CurList = *(DWORD*)(ListAddr + 0);
	if (IsBadReadPtr((void*)(CurList), 4))
		return;
	DWORD ListEnd = *(DWORD*)(ListAddr + 4);
	if (IsBadReadPtr((void*)(CurList), 4))
		return;
	CString strTmp;
	while (CurList < ListEnd)
	{
		if (IsBadReadPtr((void*)CurList, 4))
			break;
		DWORD questID = *(DWORD*)(CurList + 0);

		DWORD CurStepList = *(DWORD*)(CurList + QUEST_RESPONSE_STEP_LIST_OS);
		DWORD StepListEnd = *(DWORD*)(CurList + QUEST_RESPONSE_STEP_LIST_OS + 4);
		if (!IsBadReadPtr((void*)CurStepList, 4) && !IsBadReadPtr((void*)StepListEnd, 4)
			&& CurStepList < StepListEnd)
		{
			while (CurStepList < StepListEnd)
			{
				if (IsBadReadPtr((void*)CurStepList, 4))
					break;
				DWORD ResponseID1 = *(DWORD*)(CurStepList + 0);
				DWORD ResponseID2 = *(DWORD*)(CurStepList + 4);

				DWORD CurItemList = *(DWORD*)(CurStepList + QUEST_RESPONSE_STEP_ITEM_OS);
				DWORD ItemListEnd = *(DWORD*)(CurStepList + QUEST_RESPONSE_STEP_ITEM_OS + 4);
				if (!IsBadReadPtr((void*)CurItemList, 4) && !IsBadReadPtr((void*)ItemListEnd, 4)
					&& CurItemList < ItemListEnd)
				{
					int nStep = 0;
					while (CurItemList < ItemListEnd)
					{
						if (IsBadReadPtr((void*)CurItemList, 4))
							break;
						tstring strItem;
						char* ItemName = (char*)*(DWORD*)CurItemList;
						if (!IsBadReadPtr((void*)ItemName, 4))
							strItem = XCall::UTF2T(ItemName);

						strTmp.Format(_T("下标:%d,地址:%X,会话ID:%X/%X,任务ID:%X,字串:%s\r\n"),
							nStep, CurList, ResponseID1, ResponseID2, questID, strItem.c_str());
						::OutputDebugString(strTmp);
						//str += strTmp;

						nStep++;
						CurItemList += QUEST_RESPONSE_STEP_ITEM_LIST_SIZE;
					}
				}
				CurStepList += QUEST_RESPONSE_STEP_LIST_SIZE;
			}
		}
		CurList += QUEST_RESPONSE_LIST_SIZE;
	}
	//((CEdit *)GetDlgItem(IDC_EDIT1))->SetWindowText(str);
}
#pragma endregion comment

#pragma region 控制
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//转向
void FChangeAngle(double angle)
{
	ROLEANGLE face;
	face.dwSinAngle = sin(angle);
	face.dwCosAngle = cos(angle);
	face.dwUnknowAngle = 0;
	XCall::ChangeRoleAngle(&face);
}
#pragma endregion comment

#pragma region 操作

#pragma endregion comment