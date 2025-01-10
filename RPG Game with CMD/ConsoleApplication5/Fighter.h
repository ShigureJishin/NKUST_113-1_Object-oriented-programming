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
	/* ���m���� */
	void addDefense(int);
	void delDefense(int);
	int getDefense() {return Defense; };
	
	/* ���� */
	void addMoney(int);
	void reduceMoney(int);
	int getMoney();
	/* ���Ŭ��� */
	void addXP(int);
	int getXP() { return XP; };
	int getLevel() { return Level; };
	/* �I�ƺ޲z */
	int getProperty_Point() { return Property_Point; };
	int getSkill_Point() { return Skill_Point; };
	/* �ޯ���� */
	void learnSkill(int skillID);
	void upgradeSkill(int skillID);
	string displaySkills() const;
	/* �d���t�� */
	void addPet(CPet *pet);         // �s�W�d��
	void showPets() const;          // ��ܩҦ��d��
	bool setCurrentPet(const int indexPet);  // �]�w��e�԰��d��
	string getCurrentPet_String() const;    // �����e�԰��d��
	CPet *getCurrentPet() const { return currentPet; };    // �����e�԰��d��
	/* �԰����� */
	int physicaldamage ();	
	int petAttack(CLifeEntity* l);
	virtual int attack (CLifeEntity *);
	virtual int defense (CLifeEntity *);	
	virtual int isA ();
	/* �I�]���� */
	void captureItem (CItem *);
	void buyItem(CItem*);
	int showAllBagItems ();
	bool useBagItems (int no);
	void applySetBonus();
	void getCurrentSet() const;
	/* ���ʬ��� */
	int goto_next_city (int next_dir);
	int moveto_city(string next_city_name);
	int get_current_city ();
	bool addProperty (const int);
	/* ¾�~���� */
	void changeProfession(Profession newProfession);
	int getProfession() const { return static_cast<int>(profession);  };
	string getProfession_String() const;

	/* �s�ɥ� */
	string serializeSkills() const;        // �N�ޯ�ǦC�Ƭ��r��
	string serializePets() const;          // �N�d���ǦC�Ƭ��r��
	string serializeArror() const;         // �N�˳ƧǦC�Ƭ��r��
	string serializeBag() const;           // �N��e�d���ǦC�Ƭ��r��
	string serializeCurrentPet() const;

	/* Ū�ɥ� */
	void deserializePets(const string& data);   // �q�r���٭��d��
	void deserializeSkills(const string& data); // �q�r���٭�ޯ�
	void deserializeArror(const string& data);  // �q�r���٭�˳�
	void deserializeBag(const string& data);    // �q�r���٭�I�]
	void deserializeCurrentPet(const string& data);    // �q�r���٭��e�d��

private:
	int cur_city;            // ��e�Ҧb�������s��
	int Lucky;               // ���B��
	int Defense;             // ���m�ȡA��֨��쪺�ˮ`�q
	int Money;               // ���a�����������A�Ω��ʶR���~
	int XP, Level;           // �g��ȻP����
	int Property_Point;      // �ݩ��I�ơA�Ω󴣤ɨ����¦�ݩ�
	int Skill_Point;         // �ޯ��I�ơA�Ω����Τɯŧޯ�
	CBag* bag;               // �I�]���СA�Ω�s�񪱮a��o�����~
	vector<CSkill> Skills;	 // �C�Ө���W�ߪ��ޯ�C��
	vector<CPet *> Pets;	 // �d���C��
	CPet* currentPet;        // ��e�ϥΪ��d��
	Profession profession;   // ��e¾�~
	const ArmorEffect* currentSetBonus = nullptr; // ��e�E�����M�ˮĪG
};

#endif