#ifndef GLOBALINFO_H
#define GLOBALINFO_H

class CItemData;
class CMapData;
class CCmdParser;
class CUser;
class CMonsterData;
class CSkillData;
class CAccountData;
class CArmorEffectData;

class CGlobalInfo {
public:
	static CItemData *itm_data;			// 物品資料
	static CMapData *map_data;			// 地圖資料
	static CCmdParser *parser;			// 遊戲系統指標
	static CUser *user;
	static CMonsterData *monster_data;	// 怪物資料
	static CSkillData *skillManager;	// 技能管理器指標
	static CAccountData *accountManager;// 登入系統指標
	static CArmorEffectData *armor_effect_data;// 登入系統指標
};

#endif