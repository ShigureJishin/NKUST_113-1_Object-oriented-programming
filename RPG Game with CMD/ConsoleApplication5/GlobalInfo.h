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
	static CItemData *itm_data;			// ���~���
	static CMapData *map_data;			// �a�ϸ��
	static CCmdParser *parser;			// �C���t�Ϋ���
	static CUser *user;
	static CMonsterData *monster_data;	// �Ǫ����
	static CSkillData *skillManager;	// �ޯ�޲z������
	static CAccountData *accountManager;// �n�J�t�Ϋ���
	static CArmorEffectData *armor_effect_data;// �n�J�t�Ϋ���
};

#endif