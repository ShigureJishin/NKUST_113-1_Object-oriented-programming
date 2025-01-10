#include <fstream>
#include <iostream>
#include "Item.h"
#include "food.h"
#include "weapon.h"
#include "chestplate.h"
#include "helmet.h"
#include "boots.h"
#include "Potion.h"
#include "ItemData.h"
#include "GlobalInfo.h"
#include "def.h"

using namespace std;

void CItemData::Initialize (){
	LoadFoodData ();
	LoadWeaponData ();
	LoadChestplateData ();
	LoadHelmetData ();
	LoadBootsData ();
}

int CItemData::totalsize (){
	return food_array.size () + weapon_array.size () + chestplate_array.size() + helmet_array.size() + boots_array.size();
}

CItem *CItemData::getRand (){
	unsigned int randnum = rand () % totalsize ();
	if (randnum < food_array.size()) {
		return food_array[randnum];
	}
	randnum -= food_array.size ();
	if (randnum < weapon_array.size ()){
		return weapon_array[randnum];
	}

	randnum -= weapon_array.size();
	if (randnum < chestplate_array.size()) {
		return chestplate_array[randnum];
	}

	randnum -= chestplate_array.size();
	if (randnum < helmet_array.size()) {
		return helmet_array[randnum];
	}

	randnum -= helmet_array.size();
	if (randnum < boots_array.size()) {
		return boots_array[randnum];
	}
	return NULL;
}

void CItemData::LoadFoodData (){
	ifstream fin("food.txt");	
	if (!fin){
		cout << "讀檔失敗: food.txt" << endl;
		return;
	}
	string name;
	int hp_bonus;
	int inID;
	CFood *food;
	while (!fin.eof ()){
		fin >> inID >> name >> hp_bonus;
		food = new CFood (name, 0, 0, inID, hp_bonus);
		CGlobalInfo::itm_data->food_array.push_back (food);		
		//cout << name << " " << hp_bonus << endl;
	}
	fin.close ();
}

void CItemData::LoadPotionData() {
	ifstream fin("potion.txt");
	if (!fin) {
		cout << "讀檔失敗: potion.txt" << endl;
		return;
	}
	string name;
	int bonus;
	int inID;
	CPotion* potion;
	while (!fin.eof()) {
		fin >> inID >> name >> bonus;
		potion = new CPotion(name, 0, 0, inID, bonus);
		CGlobalInfo::itm_data->potion_array.push_back(potion);
	}
	fin.close();
}

void CItemData::LoadWeaponData (){
	ifstream fin("weapon.txt");	
	if (!fin){
		cout << "讀檔失敗: weapon.txt" << endl;
		return;
	}
	string name;
	int attack_bonus;
	int inID, JobType;
	CWeapon *weapon;
	while (!fin.eof ()){
		fin >> inID >> name >> attack_bonus >> JobType;
		weapon = new CWeapon(name, 0, 0, inID, attack_bonus, static_cast<Profession>(JobType));
		CGlobalInfo::itm_data->weapon_array.push_back (weapon);		
		//cout << name << " " << hp_bonus << endl;
	}
	fin.close ();
}

void CItemData::LoadChestplateData() {
	ifstream fin("chestplate.txt");
	if (!fin) {
		cout << "讀檔失敗: chestplate.txt" << endl;
		return;
	}
	string name;
	int defense_bonus;
	int inID;
	CChestplate* chestplate;
	while (!fin.eof()) {
		fin >> inID >> name >> defense_bonus;
		chestplate = new CChestplate(name, 0, 0, inID, defense_bonus);
		CGlobalInfo::itm_data->chestplate_array.push_back(chestplate);
		//cout << name << " " << hp_bonus << endl;
	}
	fin.close();
}

void CItemData::LoadHelmetData() {
	ifstream fin("helmet.txt");
	if (!fin) {
		cout << "讀檔失敗: helmet.txt" << endl;
		return;
	}
	string name;
	int defense_bonus;
	int inID;
	CHelmet* helmet;
	while (!fin.eof()) {
		fin >> inID >> name >> defense_bonus;
		helmet = new CHelmet(name, 0, 0, inID, defense_bonus);
		CGlobalInfo::itm_data->helmet_array.push_back(helmet);
		//cout << name << " " << defense_bonus << endl;
	}
	fin.close();
}

void CItemData::LoadBootsData() {
	ifstream fin("boots.txt");
	if (!fin) {
		cout << "讀檔失敗: boots.txt" << endl;
		return;
	}
	string name;
	int defense_bonus;
	int inID;
	CBoots* boots;
	while (!fin.eof()) {
		fin >> inID >> name >> defense_bonus;
		boots = new CBoots(name, 0, 0, inID, defense_bonus);
		CGlobalInfo::itm_data->boots_array.push_back(boots);
		//cout << name << " " << hp_bonus << endl;
	}
	fin.close();
}

int CItemData::getBouns(ItemType type, int ID) {
	switch (type) {
	case Weapon: {
		for (const auto& weapon : weapon_array) {
			if (weapon->getID() == ID) {
				return weapon->getattackbonus(); // 假設武器的加成是傷害
			}
		}
		break;
	}
	case Chestplate: {
		// 在防具類中搜尋對應 ID
		for (const auto& chestplate : chestplate_array) {
			if (chestplate->getID() == ID) {
				return chestplate->getdefensebonus(); // 假設胸甲的加成是防禦
			}
		}
		break;
	}
	case Helmet: {
		for (const auto& helmet : helmet_array) {
			if (helmet->getID() == ID) {
				return helmet->getdefensebonus();
			}
		}
		break;
	}
	case Boots: {
		for (const auto& boots : boots_array) {
			if (boots->getID() == ID) {
				return boots->getdefensebonus();
			}
		}
		break;
	}
	case Food: {
		for (const auto& food : food_array) {
			if (food->getID() == ID) {
				return food->gethpbonus(); // 假設食物的加成是恢復值
			}
		}
		break;
	}
	case Other:
	default:
		return 0; // 如果是未知類型，返回 0 加成
	}
	// 找不到對應 ID 的物品
	return 0;
}

CWeapon* CItemData::findWeaponByID(int id) {
	for (const auto& weapon : weapon_array) {
		if (weapon->getID() == id) { // 假設 CWeapon 類有 getID() 方法
			return weapon; // 找到匹配的武器
		}
	}
	return nullptr; // 未找到武器
}