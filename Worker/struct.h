#pragma once

#define  PathVec3 std::vector<XVec3>

enum Obj_Type
{
	OBJ_PLAYER		= 1,     //���
	OBJ_NPC			= 4,     //NPC
	OBJ_COLLECT		=0x20,   //�ɼ���  
	OBJ_SPOILS		=0xB0,   //ս��Ʒ
	OBJ_CAMPFIRE	=0xC0,   //Ӫ��

	OBJ_UNKNOW  //δ֪����
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
	ULONG64 ulParam;  //64λ
}DATAPARAM,*PDATAPARAM;

struct ItemPos
{
	int nRow;   //����
	int nLine;  //����
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
	float z;  //һ��Ϊ0
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
	int nMinExAtt;//�⹥��С����
	int nMaxExAtt; //�⹦��󹥻�
	int nMinInAtt;//�ڹ���С����
	int nMaxInAtt; //�ڹ���󹥻�
	int nExDefence;  //�⹦����
	int nInDefence;  //�ڹ�����
	int nUnKnow1[2];
	int nStrenght;   //����
	int nGasStr;    //����
	int nRootBone;  //����
	int nInsight;   //����
	int nBodySpeed; //��
	int nUnknow2[3];
}ITEMATTRIBUTE,*PITEMATTRIBUTE;


typedef struct tagBUYITEMPACKET {
	BYTE bAction;    //������� ����:2,����Ϊ3
	ULONG64 ulShopNpcID;   //�̵�npc��64λID
	DWORD dwShopNpcID;   //�̵�npc�ķ�����ID
	int nFlag;         //����ƷΪ2
	DWORD dwItemID;    //��Ʒ������ID
	int nItemNum;      //��������
}BUYITEMPACKET,*PBUYITEMPACKET;


typedef struct tagDELMAILPACKET {
	DWORD UnkowValue[3];
	int nDelNum;
	DWORD MailIDArrary[0x1A0];
}DELMAILPACKET,*PDELMAILPACKET;

typedef struct tagTAKEAPPENDPACKET {
	DWORD dwFlag;   //�Ƿ���npc�Ի����ʼ�����
	DWORD dwNpcID1;
	DWORD dwNpcID2;  //npc ��ID
	DWORD dwMailID1;
	DWORD dwMailID2;  //�ʼ���ID
	DWORD dwCountValue;  //���� 2
	DWORD dwUnkow;
}TAKEAPPENDPACKET,*PTAKEAPPENDPACKET;

typedef struct tagINVITETEAMPACKET {
	DWORD dwPlayerID2;
	DWORD dwPlayerID1;
	char szPlayerName[0x20];
}INVITETEAMPACKET,*PINVITETEAMPACKET;






typedef struct tagAUCTIONINFO {
	ULONG64 AuctionItemID;   // �ϼ�����ƷID
	int nItemNum;   //����
	int nItemPrice;  //�ܼ۸�
	int nAuctionTime;  //����ʱ��(��)
	int nType;   //������ʽ(1Ϊ����,2Ϊһ�ڼ�)
}AUCTIONINFO,*PAUCTIONINFO;

typedef struct tagAUCTIONITEM {
	ULONG64 AuctionItemID;   // �ϼ�����ƷID
	int nItemNum;   //����
	DWORD dwParam1;
}AUCTIONITEM,*PAUCTIONITEM;


typedef struct tagSUPERKEYINFO {
	DWORD dwConst;    //����0
	DWORD dwKeyType;  //һ��Ϊ5
	DWORD dwKeyUp;    //����Ϊ0,����Ϊ1
	DWORD dwSupperKey; //����asc��
	bool  bUnKnow1;		//Ϊ0
	bool  bCtrl;      //ctrl�Ƿ���
	bool  bShift;    //shift
	bool  bMenu;    //�˵����Ƿ���
	bool  bUnKnow2;  //Ϊ0
	bool  bKeyW;	//W��
	bool  bKeyS;    //s��
	bool  bKeyA;    //A
	bool  bKeyD;    //D
	bool  bUnKnow3;  //Ϊ0
	bool  bUnKnow4;  //Ϊ0
	bool  bUnKnow5;  //Ϊ0
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