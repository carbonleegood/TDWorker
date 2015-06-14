#pragma once

#define  PathVec3 std::vector<XVec3>

enum Obj_Type
{
	OBJ_PLAYER		= 1,     //玩家
	OBJ_NPC			= 4,     //NPC
	OBJ_COLLECT		=0x20,   //采集物  
	OBJ_SPOILS		=0xB0,   //战利品
	OBJ_CAMPFIRE	=0xC0,   //营火

	OBJ_UNKNOW  //未知对像
};

typedef struct tagGAMEDATASTRUCT {
	LRESULT lResult;
	LPARAM  lParam;
	WPARAM  wParam;
} GAMEDATASTRUCT, *LPGAMEDATASTRUCT;

typedef struct tagDATAPARAM {
	DWORD dwParam1;
	DWORD dwParam2;
	DWORD dwParam3;
	DWORD dwParam4;
	ULONG64 ulParam;  //64位
}DATAPARAM,*PDATAPARAM;

struct ItemPos
{
	int nRow;   //横行
	int nLine;  //竖行
};
struct GamePack
{
	int nflag;
	char* pPack;
	int nsize;
};

struct GamePoint
{
	float x;
	float y;
	float z;  //一般为0
	DWORD MapID;
};


struct ObjBlackList
{
	ULONG64 ObjID;
	DWORD AddTime;
};

typedef struct tagROLEANGLE {
	float dwSinAngle;   // SIN
	float dwCosAngle;
	float dwUnknowAngle;
}ROLEANGLE,*PROLEANGLE;


typedef struct tagItemAttr{
	int nMinExAtt;//外攻最小攻击
	int nMaxExAtt; //外功最大攻击
	int nMinInAtt;//内攻最小攻击
	int nMaxInAtt; //内功最大攻击
	int nExDefence;  //外功防御
	int nInDefence;  //内功防御
	int nUnKnow1[2];
	int nStrenght;   //力道
	int nGasStr;    //气劲
	int nRootBone;  //根骨
	int nInsight;   //洞察
	int nBodySpeed; //身法
	int nUnknow2[3];
}ITEMATTRIBUTE,*PITEMATTRIBUTE;


typedef struct tagBUYITEMPACKET {
	BYTE bAction;    //动作标记 购买:2,出售为3
	ULONG64 ulShopNpcID;   //商店npc的64位ID
	DWORD dwShopNpcID;   //商店npc的服务器ID
	int nFlag;         //是物品为2
	DWORD dwItemID;    //物品服务器ID
	int nItemNum;      //购买数量
}BUYITEMPACKET,*PBUYITEMPACKET;


typedef struct tagDELMAILPACKET {
	DWORD UnkowValue[3];
	int nDelNum;
	DWORD MailIDArrary[0x1A0];
}DELMAILPACKET,*PDELMAILPACKET;

typedef struct tagTAKEAPPENDPACKET {
	DWORD dwFlag;   //是否是npc对话打开邮件窗口
	DWORD dwNpcID1;
	DWORD dwNpcID2;  //npc 的ID
	DWORD dwMailID1;
	DWORD dwMailID2;  //邮件的ID
	DWORD dwCountValue;  //常量 2
	DWORD dwUnkow;
}TAKEAPPENDPACKET,*PTAKEAPPENDPACKET;

typedef struct tagINVITETEAMPACKET {
	DWORD dwPlayerID2;
	DWORD dwPlayerID1;
	char szPlayerName[0x20];
}INVITETEAMPACKET,*PINVITETEAMPACKET;






typedef struct tagAUCTIONINFO {
	ULONG64 AuctionItemID;   // 上架拍卖品ID
	int nItemNum;   //数量
	int nItemPrice;  //总价格
	int nAuctionTime;  //拍卖时间(秒)
	int nType;   //拍卖方式(1为竞拍,2为一口价)
}AUCTIONINFO,*PAUCTIONINFO;

typedef struct tagAUCTIONITEM {
	ULONG64 AuctionItemID;   // 上架拍卖品ID
	int nItemNum;   //数量
	DWORD dwParam1;
}AUCTIONITEM,*PAUCTIONITEM;


typedef struct tagSUPERKEYINFO {
	DWORD dwConst;    //常量0
	DWORD dwKeyType;  //一般为5
	DWORD dwKeyUp;    //按下为0,弹起为1
	DWORD dwSupperKey; //按键asc码
	bool  bUnKnow1;		//为0
	bool  bCtrl;      //ctrl是否按下
	bool  bShift;    //shift
	bool  bMenu;    //菜单键是否按下
	bool  bUnKnow2;  //为0
	bool  bKeyW;	//W键
	bool  bKeyS;    //s键
	bool  bKeyA;    //A
	bool  bKeyD;    //D
	bool  bUnKnow3;  //为0
	bool  bUnKnow4;  //为0
	bool  bUnKnow5;  //为0
	DWORD dwUnKnow1;
	DWORD dwUnKnow2;

}SUPERKEYINFO, *PSUPERKEYINFO;

struct vchar
{
	char buffer[100];
	vchar()
	{
		ZeroMemory(buffer, 100);
	}
};