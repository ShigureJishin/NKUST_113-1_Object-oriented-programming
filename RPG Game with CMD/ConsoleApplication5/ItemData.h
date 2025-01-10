#ifndef ITEMDATA_H
#define ITEMDATA_H

#include <vector>
#include "def.h"

class CPotion;
class CFood;
class CWeapon;
class CChestplate;
class CHelmet;
class CBoots;
class CItem;

struct SetBonus {
	int HelmetID;
	int BootsID;
	int ChestplateID;
	int ATKBonus;
	int DefenseBonus;
};
class CItemData {
public:
	CItemData() {};
	~CItemData ();
	void Initialize ();
	int totalsize ();
	CItem *getRand ();
	int getBouns(ItemType, int);
	CWeapon* findWeaponByID(int id);
	
	vector <CFood *> food_array;	
	vector <CWeapon *> weapon_array;
	vector <CChestplate *> chestplate_array;
	vector <CHelmet *> helmet_array;
	vector <CBoots *> boots_array;
	vector <CPotion *> potion_array;
	vector <SetBonus> bonuses;
private:
	void LoadFoodData ();
	void LoadPotionData();
	void LoadWeaponData();
	void LoadChestplateData();
	void LoadHelmetData();
	void LoadBootsData();
};

#endif