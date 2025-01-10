#ifndef FIGHTER_H
#define FIGHTER_H

#include <vector>

#include "def.h"
#include "LifeEntity.h"
#include "ArmorEffect.h"

#define FIGHTER_MAXHP 100
#define FIGHTER_MAXSP 100
#define FIGHTER_RANGEMP 100
#define FIGHTER_MAXLUCKY 20
#define FIGHTER_MAXDEFENSE 40
#define FIGHTER_SkillPOINT_PERLEVELUP 2
#define FIGHTER_PropertyPOINT_PERLEVELUP 5

class CFood;
class CBag;
class CPet;
class CItem;
class CSkill;

class CFighter : public CLifeEntity {
public:
	CFighter(string inName="", int initHP = 0, int initSP = 0, int initMP = 0, int initLucky = 0, int initDefense = 0, int in_city = 1, Profession inProfession = Profession::Berserker);
	CFighter(string inName, int initMAXHP, int initHP, int initSP, int initMAXSP, int initMP, int initMAXMP, int initLucky, int initDefense, int inMoney, int inXP, int inLevel, int in_city, Profession inProfession, int point1, int point2);
	~CFighter();
	int getLucky();
	void addLucky(int);
	/* 防禦相關 */
	void addDefense(int);
	void delDefense(int);
	int getDefense() {return Defense; };
	
	/* 金錢 */
	void addMoney(int);
	void reduceMoney(int);
	int getMoney();
	/* 等級相關 */
	void addXP(int);
	int getXP() { return XP; };
	int getLevel() { return Level; };
	/* 點數管理 */
	int getProperty_Point() { return Property_Point; };
	int getSkill_Point() { return Skill_Point; };
	/* 技能相關 */
	void learnSkill(int skillID);
	void upgradeSkill(int skillID);
	string displaySkills() const;
	/* 寵物系統 */
	void addPet(CPet *pet);         // 新增寵物
	void showPets() const;          // 顯示所有寵物
	bool setCurrentPet(const int indexPet);  // 設定當前戰鬥寵物
	string getCurrentPet_String() const;    // 獲取當前戰鬥寵物
	CPet *getCurrentPet() const { return currentPet; };    // 獲取當前戰鬥寵物
	/* 戰鬥相關 */
	int physicaldamage ();	
	int petAttack(CLifeEntity* l);
	virtual int attack (CLifeEntity *);
	virtual int defense (CLifeEntity *);	
	virtual int isA ();
	/* 背包相關 */
	void captureItem (CItem *);
	void buyItem(CItem*);
	int showAllBagItems ();
	bool useBagItems (int no);
	void applySetBonus();
	void getCurrentSet() const;
	/* 移動相關 */
	int goto_next_city (int next_dir);
	int moveto_city(string next_city_name);
	int get_current_city ();
	bool addProperty (const int);
	/* 職業相關 */
	void changeProfession(Profession newProfession);
	int getProfession() const { return static_cast<int>(profession);  };
	string getProfession_String() const;

	/* 存檔用 */
	string serializeSkills() const;        // 將技能序列化為字串
	string serializePets() const;          // 將寵物序列化為字串
	string serializeArror() const;         // 將裝備序列化為字串
	string serializeBag() const;           // 將當前寵物序列化為字串
	string serializeCurrentPet() const;

	/* 讀檔用 */
	void deserializePets(const string& data);   // 從字串還原寵物
	void deserializeSkills(const string& data); // 從字串還原技能
	void deserializeArror(const string& data);  // 從字串還原裝備
	void deserializeBag(const string& data);    // 從字串還原背包
	void deserializeCurrentPet(const string& data);    // 從字串還原當前寵物

private:
	int cur_city;            // 當前所在城市的編號
	int Lucky;               // 幸運值
	int Defense;             // 防禦值，減少受到的傷害量
	int Money;               // 玩家持有的金錢，用於購買物品
	int XP, Level;           // 經驗值與等級
	int Property_Point;      // 屬性點數，用於提升角色基礎屬性
	int Skill_Point;         // 技能點數，用於解鎖或升級技能
	CBag* bag;               // 背包指標，用於存放玩家獲得的物品
	vector<CSkill> Skills;	 // 每個角色獨立的技能列表
	vector<CPet *> Pets;	 // 寵物列表
	CPet* currentPet;        // 當前使用的寵物
	Profession profession;   // 當前職業
	const ArmorEffect* currentSetBonus = nullptr; // 當前激活的套裝效果
};

#endif