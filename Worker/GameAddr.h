
#pragma once

//技能
#define GAME_BASE                          0x00209BE50   // 游戏基址
#define LEARNED_SKILL_ARRARY_OS1           0x0098        // 已学技能列表偏移1
#define GET_LEARNED_SKILL_CALL1            0x006F6330    // 取已学技能地址call1
#define LEARNED_SKILL_ARRARY_OS2           0x00A4        // 已学技能列表偏移2
#define GET_LEARNED_SKILL_CALL2            0x00D28290    // 取已学技能地址call2
#define LEARNED_SKILL_ID_LIST_OS           0x002B4       // 已学技能ID列表偏移
#define MAN_PLAYER_ADDR_OS                 0x0080        // ManPlayer地址偏移
#define GET_LEARNED_SKILL_CALL3            0x006F62E0    // 取已学技能地址call3
#define ROLE_STATE_LIST_OS                 0x002F4       // 角色状态列表偏移
#define BUFF_SKILL_LIST_OS                 0x00140       // 辅助技能列表偏移
#define GET_BUFF_SKILL_ADDR_CALL           0x007660F0    // 取辅助技能地址call
//寻路
#define CUR_MAP_ID_BASE                    0x002126528   // 当前地图ID基址
#define FIND_PATH_CALL                     0x00119FAE0   // 地图寻路call
#define MAP_INFO_BASE_CALL                 0x00FA0100    // 地图详细基址call
#define GET_MAP_INFO_ADDR_CALL             0x00F9FF90    // 取地图详细地址call
#define MAP_INFO_NAME_OS                   0x004         // 地图名字偏移
#define MAP_AREA_BASE                      0x002133478   // Area基址
#define GET_MAP_AREA_NAME_CALL             0x0012F6C50   // 取当前城镇名字call
#define FIND_PATH_CALL2                    0x00119D300   // 地图寻路call2
//快捷键
#define GET_KEY_FUNCTION_ADDR_CALL         0x0011B8DF0   // 取快捷键函数地址call
#define KEY_FUNCTION_CALL                  0x00EB0460    // 快捷键call
#define MOVE_SKILL_TO_KEY_CALL             0x0011DB430   // 移动技能到快捷拦call
#define QSSLOT_MANAGER_BASE                0x002132D28   // QSSlotManager基址
#define KEY_ARRARY_OS                      0x002C        // 快捷栏列表偏移
#define KEY_SKILL_ID_OS                    0x003C        // 快捷栏技能ID偏移
#define QSUI_SKILL_PANEL_BASE              0x0021203D4   // QSUISkillPanel基址
#define GAME_MSG_BASE                      0x00209ABBC   // 消息基址
#define PRESS_KEY_DOWN_CALL                0x00C0E570    // 按键按下call
#define PRESS_KEY_UP_CALL                  0x00C0E5B0    // 按键弹起call
#define SUPER_KEY_CALL                     0x00FA8C50    // 超级按键call
#define SUPER_KEY_BASE                     0x0021251C0   // 超级按键基址
//对像
#define OBJECT_BE_FRIEND_CALL              0x001203070   // 对像是否友好call
#define OBJ_PROPERTY_CALL                  0x0010A8A40   // 取对像属性值地址call
#define OBJ_PROPERTY_KEY_VALUE             0x00A59CF5B6  // 对像属性值解密值
#define OBJ_BLOOD_VALUE_OS                 0x00E8        // 对像血值偏移
#define OBJ_INTERNAL_VALUE_OS              0x00F8        // 对像内息偏移
#define OBJ_FORCE_VALUE_OS                 0x0010C       // 对像定力偏移
#define OBJ_JOB_VALUE_OS                   0x00CC        // 对像职业偏移
#define OBJ_MAX_FINESSE_CALL               0x0012489B0   // 取最大机巧call
#define OBJ_CUR_FINESSE_CALL               0x001248980   // 取当前机巧call
#define CHANGE_ROLE_ANGLE_CALL             0x00ED9BE0    // 改变角色面向角call
#define OBJ_LEVEL_OS                       0x00D0        // 对像等级偏移
#define GET_OBJ_TYPE_CALL                  0x0027DD2E7   // 取对像类型call
#define PICK_ALL_ITEM_CALL                 0x00FDC320    // 全捡物品call
#define OBJ_KILLING_VALUE_OS               0x00F0        // 对像杀意偏移
#define OBJECT_CAN_ATTACK_CALL             0x001094050   // 判断对像是否可以攻击
#define SELECT_OBJECT_ID_OS                0x00698       // 被选怪ID偏移
//状态
#define FIGHTING_STATE_OS                  0x005AC       // 战斗状态偏移
#define MOVE_STATE_ADDR_OS                 0x004F0       // 移动状态地址偏移
//会话
#define QUEST_RESPONSE_ITEM_LIST_OS        0x0012C       // 任务会话选项列表偏移
#define GET_SERVER_NPC_ID_CALL             0x0010914A0   // 取NPC的服务器IDcall
#define GET_RESPONSE_ITEM_LIST_CALL        0x00740360    // 任务会话选项列表地址call
#define NOMAL_RESPONSE_ITEM_LIST_OS        0x00770       // 普通会话选项列表偏移
#define PRESS_RESPONSE_ITEM_CALL           0x00FE3810    // 会话选项call
#define SEND_PACKET_CALL                   0x00C9C689    // 明文发包call
#define SEND_PACKET_BASE                   0x002126510   // 发包基址
#define JOYIN_MEMHUI_CALL                  0x00106DC9E   // 加入盟会call
//UI
#define UI_BASE                            0x00209CF88   // UI基址
#define GET_UI_ADDR_CALL                   0x00C93820    // 遍历UI的call
#define NPC_DLG_FLAG_BASE_CALL             0x0021267A0   // 对话框识别基址
#define RESPONSE_DLG_NPC_ID_OS             0x00B8        // 打开对话框的NPC的ID偏移
#define GAME_UI_VISIBLE_OS                 0x0081        // 窗口UI是否显示偏移
//任务
#define ACCEPTED_QUEST_LIST_OS             0x005B0       // 已接任务列表偏移
#define GET_QUEST_ADDR_CALL                0x00E922F0    // 取任务地址call
#define QUEST_TRACK_TEXT_BASE              0x00209B33C   // 任务追踪字串基址
#define TREASURE_POS_HOOK_ADDR             0x001146B10   // 挖宝位置HOOK地址
#define JIANWEN_INFO_LIST_OS               0x00250       // 见闻详细列表偏移
#define GET_JIANWEN_INFO_CALL2             0x00D95C40    // 取见闻详细地址call2
#define JIANGHU_QUEST_LIST_OS              0x00FC        // 江湖任务列表偏移
#define HUABEN_QUEST_PROGRESS_BASE         0x000         // 江湖话本进度基址
#define GET_HUABEN_PROGRESS_CALL           0x000         // 取江湖话本进度地址call
#define IS_JIANWEN_COMPLETED_CALL          0x00118DE00   // 判断见闻任务是否完成call
#define PLOT_EVENT_ADDR_OS                 0x00400       // PlotEvent地址偏移
#define PLOT_EVENT_CAN_ACCECPT_CALL        0x00118A920   // PlotEvent是否可接call
#define PLOT_EVENT_COMPLETED_CALL          0x00118A940   // PlotEvent是否完成call
#define PLOT_EVENT_CAN_ACCEPT_OS           0x00108       // PlotEvent默认可接任务偏移
#define JIANWEN_BASE                       0x002121868   // 见闻基址
#define GET_SHILIAN_BASE                   0x0012D67C0   // 取试练列表基址call
//物品
#define ITEM_IS_GOODS_TYPE_CALL            0x00DFCA4B    // 判断是否是Goods类型call
#define ITEM_IS_EQUIP_TYPE_CALL            0x00DFBFC0    // 判断是否是Equip类型call
#define CAN_EQUIP_ITEM_CALL                0x000         // 判断是否能装上call
#define ITEM_LIST_OS                       0x0078        // 物品链表偏移
#define ITEM_BIND_STATE_OS                 0x0030        // 物品绑定状态偏移
#define EQUIP_MAX_USEAGE_OS                0x00EC        // 装备最大耐久度偏移
#define EQUIP_CUR_USEAGE_CALL_OS           0x00124       // 取装备当前耐久度call
#define BAG_MAX_GRID_OS                    0x00B4        // 背包最大格子数偏移
#define BUY_GOODS_CALL                     0x00D8DCB5    // 购买call
#define SELL_GOODS_CALL                    0x0011AC1E0   // 出售物品call
//传送点
#define GET_TRANSFER_INFO_CALL             0x00118DDB0   // 取传送点详细地址call
#define GET_TRANSFER_FREEZE_TIME_CALL      0x00118AF00   // 传送间隔剩余时间call
#define PRESS_TRANSFER_POINT_CALL          0x000         // 传送点传送call
#define TRANSFER_LIST_OS                   0x00244       // 传送点列表偏移
#define TRANSFER_LIST_MEMBER_SIZE          0x0074        // 传送点数组成员大小
//登入
#define CREAT_CHARACTER_CALL               0x00117AF30   // 创建角色call
#define ENTER_GAME_CALL                    0x0027F0D74   // 登入游戏call
#define CHARACTER_LIST_BASE                0x00212BBE0   // 角色列表基址
#define CHARACTER_LIST_MEMBER_SIZE         0x005FE       // 角色列表成员大小
//邮件
#define MAIL_BASE                          0x00209EF98   // 邮件基址
#define SEIZE_BASE                         0x002133294   // 缉拿基址
//组队
#define ACCEPT_TEAM_BASE                   0x002126848   // 组队接受列表基址
#define TEAM_MEMBER_BASE                   0x00209F7F8   // 队伍基址
#define TEAM_MEMBER_LIST_OS                0x005EE0      // 队伍成员列表偏移
#define TEAM_LEADER_ID_OS                  0x005EB0      // 队长ID偏移
#define TEAM_MEMBER_ONLINE_OS              0x00B25       // 玩家是否在线偏移
#define CUR_THREAD_ID_OS                   0x00B98       // 当前线路偏移









//////////////////////封包协义///////////////////////////////////////////////////////////////////
#define  MSG_REVIVE_PACKET						0x0688		// 复活协义封包头
#define  MSG_BUY_ITEM_PACKET					0x37DE		// 购买物品协义封包头
#define  MSG_DEL_MAIL_PACKET					0x14DE		// 删除邮件协义封包头
#define  MSG_TAKE_MAIL_APPEND_PACKET			0x1420		// 删除邮件协义封包头
#define  MSG_INVITE_TEAM_PACKET					0x232F		// 邀请组队协义封包头
#define  MSG_ACCEPT_TEAM_PACKET					0x2332		// 接受组队协义封包头
#define  MSG_QUIT_TEAM_PACKET					0x233D		// 离开组队协义封包头
#define  MSG_CHANGE_TEAM_LEADER_PACKET			0x232C		// 转让队长协义封包头
#define  MSG_KICK_OUT_TEAM_PACKET				0x2335		// 请离队伍协义封包头
#define  MSG_CHANGE_THREAD_ID_PACKET			0x4E21		// 切换线路协义封包头

//////////////////////周围/////////////////////////////////////////////////////////////////////

#define NEARLY_OBJECT_LIST_OS1                      0x018        // 周围对像链表偏移1
#define NEARLY_OBJECT_LIST_OS2                      0x01C        // 周围对像链表偏移2
#define NEARLY_OBJECT_LIST_OS3                      0x020        // 周围对像链表偏移3
#define NEARLY_OBJECT_LIST_OS4                      0x024        // 周围对像链表偏移4
#define NEARLY_OBJECT_LIST_OS5                      0x070        // 周围采集物链表偏移


#define NEARLY_OBJ_LIST_POINT_OS                      0x058        // 对像链表指针

#define ITEM_LIST_POINT_OS                      0x020        // 物品链表指针

#define GET_OBJ_POSITION_CALL              0x068        // 取对像坐标地址call

#define OBJECT_ID_OS                        0x00E0        // 对像ID偏移
#define OBJECT_NAME_OS                      0x01A0        // 对像名字偏移
#define COLLECT_ITEM_NAME_OS				0x1F0		  // 采集物名字偏移
#define OBJECT_POS_OS                       0x03B4        // 对像坐标

/////////////////////////角色状态列表(buff List)/////////////////////////////////////////////////////////////
#define ROLE_STATE_LIST_MEMBER_SIZE           0x080       // 角色状态列表成员大小

/////////////////////////普通会话/////////////////////////////////////////////////////////////
#define  NOMAL_RESPONSE_LIST_OS				0x04C		//任务会话步骤数组偏移
/////////////////////////任务会话/////////////////////////////////////////////////////////////
#define  QUEST_RESPONSE_LIST_SIZE				0x0A8		//任务会话数组大小
#define  QUEST_RESPONSE_STEP_LIST_OS			0x098		//任务会话步骤数组偏移

#define  QUEST_RESPONSE_STEP_LIST_SIZE			0x048		//任务会话步骤数组大小
#define  QUEST_RESPONSE_STEP_ITEM_OS			0x034		//任务会话步骤项目数组偏移
#define  QUEST_RESPONSE_STEP_ITEM_LIST_SIZE		0x020		//任务会话步骤项目数组大小

////////////////////////已接任务////////////////////////////////////////////////////////////////
#define  ACCEPTED_QUEST_ID_LIST_OS				0x4C		//已接任务ID数组偏移
#define  QUEST_STEP_LIST_OS						0x2C		//已接任务地址的任务步骤数组偏移

#define  QUEST_STEP_NAME_OS						0x08		//任务步骤名字偏移
#define  QUEST_STEP_TYPE_OS						0x10		//任务步骤类型偏移(0x10为副本任务,+20的地方为任务ID)

#define  QUEST_INFO_OS1							0x24		// 任务详细地址偏移1
#define  QUEST_INFO_OS2							0x0C		// 任务详细地址偏移2

#define  QUEST_NAME_OS							0x2C		// 任务名字偏移(任务详细里)

#define  JIANWEN_LIST_OS						0x50		//见闻任务列表偏移

#define  JIANGHU_QUEST_ARRARY_0S				0x14		// 江湖任务数组偏移
#define  JIANGHU_QUEST_MEMBER_SIZE				0xC0		// 江湖任务数组成员大小
#define  JIANGHU_QUEST_NAME_OS					0x28		// 江湖任务名字偏移
#define  JIANGHU_QUEST_LEVEL_OS					0x4C		// 江湖任务等级偏移
#define  JIANGHU_QUEST_INDEX_OS					0x64		// 江湖任务下标偏移

#define  JIANWEN_QUEST_ARRARY_OS				0x0C		// 所有见闻任务列表偏移
#define  JIANWEN_QUEST_MEMBER_SIZE				0x1FC		// 所有见闻详细数组成员大小
#define  JIANWEN_QUEST_MAP_ID_OS				0x20		// 所有见闻任务所在地图ID偏移

#define  PLOT_EVENT_ARRARY_OS				0x40		// PLOT EVENT数组偏移
#define  PLOT_EVENT_MEMBER_SIZE				0x23C		// PLOT EVENT数组成员大小
#define  PLOT_EVENT_MAP_ID_OS				0x08		// PLOT EVENT所在地图ID偏移
#define  PLOT_EVENT_NPC_POS_OS				0x0C		// PLOT EVENT 的npc坐标偏移
#define  PLOT_EVENT_TYPE_OS					0x38		// PLOT EVENT 的类型偏移
#define  PLOT_EVENT_NAME_OS					0x44		// PLOT EVENT 的名字偏移


///////////////////////背包///////////////////////////////////////////////////////////////////
#define ITEM_LIST_OS2							0x1C		// 物品列表偏移2
#define ITEM_ADDR_ID_OS							0x18		// 物品地址的ID偏移

#define  SLOT_ITEM_ID_OS						0x30		// 容器中物品64位ID偏移
#define  ITEM_INFO_ADDR_OS						0x0C		// 物品详细地址偏移

#define  ITEM_COLOR_OS							0x08		// 物品颜色偏移
#define  ITEM_SERVER_ID_OS						0x20		// 物品地址中的物品服务器ID偏移
#define  EQUIP_TYPE_OS							0x18C		//  装备类型偏移

////////////////////////////快捷键技能/////////////////////////////////////////////////////////////
#define SLOT_SKILL_FREEZE_FLAG_OS                     0x02C        // 是否冻结标记
#define SLOT_SKILL_DISABLE_FLAG_OS                    0x06D        // 是否禁用标记

///////////////////////窗口UI///////////////////////////////////////////////////////////////////

#define  GAME_UI_LIST_OS						0x3C		//窗口UI列表偏移
#define  GAME_UI_NAME_OS						0x1C		//窗口UI名字偏移

#define SHOP_GOODS_LIST_OS                 0x0093C      // 商店所有物品列表偏移

//////////////////////传送点///////////////////////////////////////////////////////////////////
#define  TRANSFER_POINT_VECTOR_OS				0x10		//传送点数组偏移
#define  TRANSFER_MAP_ID_OS						0x08		//传送点所属地图的ID
#define  TRANSFER_POSITION_OS					0x18		//传送点坐标偏移
#define  TRANSFER_NAME_OS						0x28		//传送点名字偏移

//////////////////////传送点///////////////////////////////////////////////////////////////////

#define  MAIL_NAME_OS						0x2C		// 邮件标题
#define  MAIL_HAS_APPEND_OS					0x50		// 邮件是否有附件
#define  MAIL_TYPE_OS						0x54		// 邮件类型偏移



/////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////





///////////////////////////////消息///////////////////////////////////////////////////
#define WM_CLOSE_MAINFORM       WM_USER+7729   // 關閉主窗口
#define WM_UPDATA_INFO	        WM_USER+7730   //發送信息給控制臺
#define WM_CREATE_MAINFORM	    WM_USER+7731   //


#define WM_PRESS_KEY_CALL		WM_USER+5299   //按键call 
#define WM_PRESS_QUEST_BTN		WM_USER+5300   //任务按钮选择call  
#define WM_NEXT_TEXT			WM_USER+5301   //对话下一步call
#define WM_COMPLETE_QUEST		WM_USER+5302   //完成任务call
#define WM_OPEN_TALK_DLG		WM_USER+5303   //打开对话框(完成任务用)
#define WM_SEND_KEY_DOWN		WM_USER+5304   //键盘按下消息
#define WM_SEND_KEY_UP			WM_USER+5305   //键盘弹起消息
#define WM_TALK_TO_NPC			WM_USER+5306   //和npc对话
#define WM_DECOMPOSE_ITEM		WM_USER+5307   //分解物品
#define WM_REDEFINE_ITEM		WM_USER+5308   //提炼物品
#define WM_PICK_LOOTS1			WM_USER+5309   //捡物品1
#define WM_PICK_LOOTS2			WM_USER+5310   //捡物品2
#define WM_RELEASE_SKILL		WM_USER+5311   //释放技能
