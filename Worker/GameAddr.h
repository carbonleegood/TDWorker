
#pragma once

//����
#define GAME_BASE                          0x002089B70   // ��Ϸ��ַ
#define LEARNED_SKILL_ARRARY_OS1           0x0098        // ��ѧ�����б�ƫ��1
#define GET_LEARNED_SKILL_CALL1            0x00703C30    // ȡ��ѧ���ܵ�ַcall1
#define LEARNED_SKILL_ARRARY_OS2           0x00A4        // ��ѧ�����б�ƫ��2
#define GET_LEARNED_SKILL_CALL2            0x00D72CB0    // ȡ��ѧ���ܵ�ַcall2
#define LEARNED_SKILL_ID_LIST_OS           0x002B0       // ��ѧ����ID�б�ƫ��
#define MAN_PLAYER_ADDR_OS                 0x0080        // ManPlayer��ַƫ��
#define GET_LEARNED_SKILL_CALL3            0x00703BE0    // ȡ��ѧ���ܵ�ַcall3
#define ROLE_STATE_LIST_OS                 0x002F4       // ��ɫ״̬�б�ƫ��
#define BUFF_SKILL_LIST_OS                 0x00140       // ���������б�ƫ��
#define GET_BUFF_SKILL_ADDR_CALL           0x00749D90    // ȡ�������ܵ�ַcall
//Ѱ·
#define CUR_MAP_ID_BASE                    0x002110BF8   // ��ǰ��ͼID��ַ
#define FIND_PATH_CALL                     0x0011AA6C0   // ��ͼѰ·call
#define MAP_INFO_BASE_CALL                 0x00FEAED0    // ��ͼ��ϸ��ַcall
#define GET_MAP_INFO_ADDR_CALL             0x00FEAD60    // ȡ��ͼ��ϸ��ַcall
#define MAP_INFO_NAME_OS                   0x004         // ��ͼ����ƫ��
#define MAP_AREA_BASE                      0x00211B598   // Area��ַ
#define GET_MAP_AREA_NAME_CALL             0x0012F45A0   // ȡ��ǰ��������call
#define FIND_PATH_CALL2                    0x0011A8080   // ��ͼѰ·call2
//��ݼ�
#define GET_KEY_FUNCTION_ADDR_CALL         0x001202AD0   // ȡ��ݼ�������ַcall
#define KEY_FUNCTION_CALL                  0x00F0F470    // ��ݼ�call
#define MOVE_SKILL_TO_KEY_CALL             0x0011DBA90   // �ƶ����ܵ������call
#define QSSLOT_MANAGER_BASE                0x00211B250   // QSSlotManager��ַ
#define KEY_ARRARY_OS                      0x002C        // ������б�ƫ��
#define KEY_SKILL_ID_OS                    0x003C        // ���������IDƫ��
#define QSUI_SKILL_PANEL_BASE              0x00210B4FC   // QSUISkillPanel��ַ
#define GAME_MSG_BASE                      0x0020888DC   // ��Ϣ��ַ
#define PRESS_KEY_DOWN_CALL                0x00C0CCA0    // ��������call
#define PRESS_KEY_UP_CALL                  0x00C0CCE0    // ��������call
#define SUPER_KEY_CALL                     0x001134680   // ��������call
#define SUPER_KEY_BASE                     0x002113CCC   // ����������ַ
//����
#define OBJECT_BE_FRIEND_CALL              0x0011B7720   // �����Ƿ��Ѻ�call
#define OBJ_PROPERTY_CALL                  0x00109A1B0   // ȡ��������ֵ��ַcall
#define OBJ_PROPERTY_KEY_VALUE             0x00A59CF5B6  // ��������ֵ����ֵ
#define OBJ_BLOOD_VALUE_OS                 0x00E8        // ����Ѫֵƫ��
#define OBJ_INTERNAL_VALUE_OS              0x00F8        // ������Ϣƫ��
#define OBJ_FORCE_VALUE_OS                 0x0010C       // ������ƫ��
#define OBJ_JOB_VALUE_OS                   0x00CC        // ����ְҵƫ��
#define OBJ_MAX_FINESSE_CALL               0x00123F230   // ȡ������call
#define OBJ_CUR_FINESSE_CALL               0x00123F200   // ȡ��ǰ����call
#define CHANGE_ROLE_ANGLE_CALL             0x00F4BF40    // �ı��ɫ�����call
#define OBJ_LEVEL_OS                       0x00D0        // ����ȼ�ƫ��
#define GET_OBJ_TYPE_CALL                  0x0027432DC   // ȡ��������call
#define PICK_ALL_ITEM_CALL                 0x001028CA0   // ȫ����Ʒcall
#define OBJ_KILLING_VALUE_OS               0x00F0        // ����ɱ��ƫ��
#define OBJECT_CAN_ATTACK_CALL             0x0010853D0   // �ж϶����Ƿ���Թ���
#define SELECT_OBJECT_ID_OS                0x00698       // ��ѡ��IDƫ��
//״̬
#define FIGHTING_STATE_OS                  0x005AC       // ս��״̬ƫ��
#define MOVE_STATE_ADDR_OS                 0x004F0       // �ƶ�״̬��ַƫ��
//�Ự
#define QUEST_RESPONSE_ITEM_LIST_OS        0x0012C       // ����Ựѡ���б�ƫ��
#define GET_SERVER_NPC_ID_CALL             0x001082830   // ȡNPC�ķ�����IDcall
#define GET_RESPONSE_ITEM_LIST_CALL        0x006F4340    // ����Ựѡ���б��ַcall
#define NOMAL_RESPONSE_ITEM_LIST_OS        0x00768       // ��ͨ�Ựѡ���б�ƫ��
#define PRESS_RESPONSE_ITEM_CALL           0x001039D20   // �Ựѡ��call
#define SEND_PACKET_CALL                   0x002697D4E   // ���ķ���call
#define SEND_PACKET_BASE                   0x002110BE0   // ������ַ
#define JOYIN_MEMHUI_CALL                  0x001135D60   // �����˻�call
//UI
#define UI_BASE                            0x00208CF18   // UI��ַ
#define GET_UI_ADDR_CALL                   0x00CC5960    // ����UI��call
#define NPC_DLG_FLAG_BASE_CALL             0x002110DC8   // �Ի���ʶ���ַ
#define RESPONSE_DLG_NPC_ID_OS             0x00B8        // �򿪶Ի����NPC��IDƫ��
#define GAME_UI_VISIBLE_OS                 0x0081        // ����UI�Ƿ���ʾƫ��
//����
#define ACCEPTED_QUEST_LIST_OS             0x005A8       // �ѽ������б�ƫ��
#define GET_QUEST_ADDR_CALL                0x00EE65C0    // ȡ�����ַcall
#define QUEST_TRACK_TEXT_BASE              0x00208905C   // ����׷���ִ���ַ
#define TREASURE_POS_HOOK_ADDR             0x001140040   // �ڱ�λ��HOOK��ַ
#define JIANWEN_INFO_LIST_OS               0x00250       // ������ϸ�б�ƫ��
#define GET_JIANWEN_INFO_CALL2             0x00EC7110    // ȡ������ϸ��ַcall2
#define JIANGHU_QUEST_LIST_OS              0x00FC        // ���������б�ƫ��
#define HUABEN_QUEST_PROGRESS_BASE         0x000         // �����������Ȼ�ַ
#define GET_HUABEN_PROGRESS_CALL           0x000         // ȡ�����������ȵ�ַcall
#define IS_JIANWEN_COMPLETED_CALL          0x001198C90   // �жϼ��������Ƿ����call
#define PLOT_EVENT_ADDR_OS                 0x003FC       // PlotEvent��ַƫ��
#define PLOT_EVENT_CAN_ACCECPT_CALL        0x0011957C0   // PlotEvent�Ƿ�ɽ�call
#define PLOT_EVENT_COMPLETED_CALL          0x0011957E0   // PlotEvent�Ƿ����call
#define PLOT_EVENT_CAN_ACCEPT_OS           0x00108       // PlotEventĬ�Ͽɽ�����ƫ��
#define JIANWEN_BASE                       0x00210C8F0   // ���Ż�ַ
//��Ʒ
#define ITEM_IS_GOODS_TYPE_CALL            0x0026EB331   // �ж��Ƿ���Goods����call
#define ITEM_IS_EQUIP_TYPE_CALL            0x00DE1620    // �ж��Ƿ���Equip����call
#define CAN_EQUIP_ITEM_CALL                0x000         // �ж��Ƿ���װ��call
#define ITEM_LIST_OS                       0x0078        // ��Ʒ����ƫ��
#define ITEM_BIND_STATE_OS                 0x0030        // ��Ʒ��״̬ƫ��
#define EQUIP_MAX_USEAGE_OS                0x00EC        // װ������;ö�ƫ��
#define EQUIP_CUR_USEAGE_CALL_OS           0x00124       // ȡװ����ǰ�;ö�call
#define BAG_MAX_GRID_OS                    0x00B4        // ������������ƫ��
#define BUY_GOODS_CALL                     0x0026EB76A   // ����call
#define SELL_GOODS_CALL                    0x0011F59C0   // ������Ʒcall
//���͵�
#define GET_TRANSFER_INFO_CALL             0x000         // ȡ���͵���ϸ��ַcall
#define GET_TRANSFER_FREEZE_TIME_CALL      0x000         // ���ͼ��ʣ��ʱ��call
#define PRESS_TRANSFER_POINT_CALL          0x000         // ���͵㴫��call
#define TRANSFER_LIST_OS                   0x000         // ���͵��б�ƫ��
#define TRANSFER_LIST_MEMBER_SIZE          0x000         // ���͵������Ա��С
//����
#define CREAT_CHARACTER_CALL               0x001173C20   // ������ɫcall
#define ENTER_GAME_CALL                    0x00277598D   // ������Ϸcall
#define CHARACTER_LIST_BASE                0x002113E00   // ��ɫ�б��ַ
#define CHARACTER_LIST_MEMBER_SIZE         0x005FE       // ��ɫ�б��Ա��С
//�ʼ�
#define MAIL_BASE                          0x000         // �ʼ���ַ
#define SEIZE_BASE                         0x000         // ���û�ַ
//���
#define ACCEPT_TEAM_BASE                   0x000         // ��ӽ����б��ַ
#define TEAM_MEMBER_BASE                   0x000         // �����ַ
#define TEAM_MEMBER_LIST_OS                0x000         // �����Ա�б�ƫ��
#define TEAM_LEADER_ID_OS                  0x005EB0      // �ӳ�IDƫ��
#define TEAM_MEMBER_ONLINE_OS              0x000         // ����Ƿ�����ƫ��
#define CUR_THREAD_ID_OS                   0x000         // ��ǰ��·ƫ��





//////////////////////���Э��///////////////////////////////////////////////////////////////////
#define  MSG_REVIVE_PACKET						0x0688		// ����Э����ͷ
#define  MSG_BUY_ITEM_PACKET					0x37DE		// ������ƷЭ����ͷ
#define  MSG_DEL_MAIL_PACKET					0x14DE		// ɾ���ʼ�Э����ͷ
#define  MSG_TAKE_MAIL_APPEND_PACKET			0x1420		// ɾ���ʼ�Э����ͷ
#define  MSG_INVITE_TEAM_PACKET					0x232F		// �������Э����ͷ
#define  MSG_ACCEPT_TEAM_PACKET					0x2332		// �������Э����ͷ
#define  MSG_QUIT_TEAM_PACKET					0x233D		// �뿪���Э����ͷ
#define  MSG_CHANGE_TEAM_LEADER_PACKET			0x232C		// ת�öӳ�Э����ͷ
#define  MSG_KICK_OUT_TEAM_PACKET				0x2335		// �������Э����ͷ
#define  MSG_CHANGE_THREAD_ID_PACKET			0x4E21		// �л���·Э����ͷ

//////////////////////��Χ/////////////////////////////////////////////////////////////////////

#define NEARLY_OBJECT_LIST_OS1                      0x018        // ��Χ��������ƫ��1
#define NEARLY_OBJECT_LIST_OS2                      0x01C        // ��Χ��������ƫ��2
#define NEARLY_OBJECT_LIST_OS3                      0x020        // ��Χ��������ƫ��3
#define NEARLY_OBJECT_LIST_OS4                      0x024        // ��Χ��������ƫ��4
#define NEARLY_OBJECT_LIST_OS5                      0x070        // ��Χ�ɼ�������ƫ��


#define NEARLY_OBJ_LIST_POINT_OS                      0x058        // ��������ָ��

#define ITEM_LIST_POINT_OS                      0x020        // ��Ʒ����ָ��

#define GET_OBJ_POSITION_CALL              0x068        // ȡ���������ַcall

#define OBJECT_ID_OS                        0x00E0        // ����IDƫ��
#define OBJECT_NAME_OS                      0x01A0        // ��������ƫ��
#define COLLECT_ITEM_NAME_OS				0x1F0		  // �ɼ�������ƫ��
#define OBJECT_POS_OS                       0x03B4        // ��������

/////////////////////////��ɫ״̬�б�(buff List)/////////////////////////////////////////////////////////////
#define ROLE_STATE_LIST_MEMBER_SIZE           0x080       // ��ɫ״̬�б��Ա��С

/////////////////////////��ͨ�Ự/////////////////////////////////////////////////////////////
#define  NOMAL_RESPONSE_LIST_OS				0x04C		//����Ự��������ƫ��
/////////////////////////����Ự/////////////////////////////////////////////////////////////
#define  QUEST_RESPONSE_LIST_SIZE				0x0A8		//����Ự�����С
#define  QUEST_RESPONSE_STEP_LIST_OS			0x098		//����Ự��������ƫ��

#define  QUEST_RESPONSE_STEP_LIST_SIZE			0x048		//����Ự���������С
#define  QUEST_RESPONSE_STEP_ITEM_OS			0x034		//����Ự������Ŀ����ƫ��
#define  QUEST_RESPONSE_STEP_ITEM_LIST_SIZE		0x020		//����Ự������Ŀ�����С

////////////////////////�ѽ�����////////////////////////////////////////////////////////////////
#define  ACCEPTED_QUEST_ID_LIST_OS				0x4C		//�ѽ�����ID����ƫ��
#define  QUEST_STEP_LIST_OS						0x2C		//�ѽ������ַ������������ƫ��

#define  QUEST_STEP_NAME_OS						0x08		//����������ƫ��
#define  QUEST_STEP_TYPE_OS						0x10		//����������ƫ��(0x10Ϊ��������,+20�ĵط�Ϊ����ID)

#define  QUEST_INFO_OS1							0x24		// ������ϸ��ַƫ��1
#define  QUEST_INFO_OS2							0x0C		// ������ϸ��ַƫ��2

#define  QUEST_NAME_OS							0x2C		// ��������ƫ��(������ϸ��)

#define  JIANWEN_LIST_OS						0x50		//���������б�ƫ��

#define  JIANGHU_QUEST_ARRARY_0S				0x14		// ������������ƫ��
#define  JIANGHU_QUEST_MEMBER_SIZE				0xC0		// �������������Ա��С
#define  JIANGHU_QUEST_NAME_OS					0x28		// ������������ƫ��
#define  JIANGHU_QUEST_LEVEL_OS					0x4C		// ��������ȼ�ƫ��
#define  JIANGHU_QUEST_INDEX_OS					0x64		// ���������±�ƫ��

#define  JIANWEN_QUEST_ARRARY_OS				0x0C		// ���м��������б�ƫ��
#define  JIANWEN_QUEST_MEMBER_SIZE				0x1FC		// ���м�����ϸ�����Ա��С
#define  JIANWEN_QUEST_MAP_ID_OS				0x20		// ���м����������ڵ�ͼIDƫ��

#define  PLOT_EVENT_ARRARY_OS				0x40		// PLOT EVENT����ƫ��
#define  PLOT_EVENT_MEMBER_SIZE				0x23C		// PLOT EVENT�����Ա��С
#define  PLOT_EVENT_MAP_ID_OS				0x08		// PLOT EVENT���ڵ�ͼIDƫ��
#define  PLOT_EVENT_NPC_POS_OS				0x0C		// PLOT EVENT ��npc����ƫ��
#define  PLOT_EVENT_TYPE_OS					0x38		// PLOT EVENT ������ƫ��
#define  PLOT_EVENT_NAME_OS					0x44		// PLOT EVENT ������ƫ��


///////////////////////����///////////////////////////////////////////////////////////////////
#define ITEM_LIST_OS2							0x1C		// ��Ʒ�б�ƫ��2
#define ITEM_ADDR_ID_OS							0x18		// ��Ʒ��ַ��IDƫ��

#define  SLOT_ITEM_ID_OS						0x30		// ��������Ʒ64λIDƫ��
#define  ITEM_INFO_ADDR_OS						0x0C		// ��Ʒ��ϸ��ַƫ��

#define  ITEM_COLOR_OS							0x08		// ��Ʒ��ɫƫ��
#define  ITEM_SERVER_ID_OS						0x20		// ��Ʒ��ַ�е���Ʒ������IDƫ��
#define  EQUIP_TYPE_OS							0x18C		//  װ������ƫ��

////////////////////////////��ݼ�����/////////////////////////////////////////////////////////////
#define SLOT_SKILL_FREEZE_FLAG_OS                     0x02C        // �Ƿ񶳽���
#define SLOT_SKILL_DISABLE_FLAG_OS                    0x06D        // �Ƿ���ñ��

///////////////////////����UI///////////////////////////////////////////////////////////////////

#define  GAME_UI_LIST_OS						0x3C		//����UI�б�ƫ��
#define  GAME_UI_NAME_OS						0x1C		//����UI����ƫ��

#define SHOP_GOODS_LIST_OS                 0x0093C      // �̵�������Ʒ�б�ƫ��

//////////////////////���͵�///////////////////////////////////////////////////////////////////
#define  TRANSFER_POINT_VECTOR_OS				0x10		//���͵�����ƫ��
#define  TRANSFER_MAP_ID_OS						0x08		//���͵�������ͼ��ID
#define  TRANSFER_POSITION_OS					0x18		//���͵�����ƫ��
#define  TRANSFER_NAME_OS						0x28		//���͵�����ƫ��

//////////////////////���͵�///////////////////////////////////////////////////////////////////

#define  MAIL_NAME_OS						0x2C		// �ʼ�����
#define  MAIL_HAS_APPEND_OS					0x50		// �ʼ��Ƿ��и���
#define  MAIL_TYPE_OS						0x54		// �ʼ�����ƫ��



/////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////





///////////////////////////////��Ϣ///////////////////////////////////////////////////
#define WM_CLOSE_MAINFORM       WM_USER+7729   // �P�]������
#define WM_UPDATA_INFO	        WM_USER+7730   //�l����Ϣ�o�����_
#define WM_CREATE_MAINFORM	    WM_USER+7731   //


#define WM_PRESS_KEY_CALL		WM_USER+5299   //����call 
#define WM_PRESS_QUEST_BTN		WM_USER+5300   //����ťѡ��call  
#define WM_NEXT_TEXT			WM_USER+5301   //�Ի���һ��call
#define WM_COMPLETE_QUEST		WM_USER+5302   //�������call
#define WM_OPEN_TALK_DLG		WM_USER+5303   //�򿪶Ի���(���������)
#define WM_SEND_KEY_DOWN		WM_USER+5304   //���̰�����Ϣ
#define WM_SEND_KEY_UP			WM_USER+5305   //���̵�����Ϣ
#define WM_TALK_TO_NPC			WM_USER+5306   //��npc�Ի�
#define WM_DECOMPOSE_ITEM		WM_USER+5307   //�ֽ���Ʒ
#define WM_REDEFINE_ITEM		WM_USER+5308   //������Ʒ
#define WM_PICK_LOOTS1			WM_USER+5309   //����Ʒ1
#define WM_PICK_LOOTS2			WM_USER+5310   //����Ʒ2
#define WM_RELEASE_SKILL		WM_USER+5311   //�ͷż���
