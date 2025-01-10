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
		cout << "Ū�ɥ���: food.txt" << endl;
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
		cout << "Ū�ɥ���: potion.txt" << endl;
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
		cout << "Ū�ɥ���: weapon.txt" << endl;
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
		cout << "Ū�ɥ���: chestplate.txt" << endl;
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
		cout << "Ū�ɥ���: helmet.txt" << endl;
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
		cout << "Ū�ɥ���: boots.txt" << endl;
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
				return weapon->getattackbonus(); // ���]�Z�����[���O�ˮ`
			}
		}
		break;
	}
	case Chestplate: {
		// �b���������j�M���� ID
		for (const auto& chestplate : chestplate_array) {
			if (chestplate->getID() == ID) {
				return chestplate->getdefensebonus(); // ���]�ݥҪ��[���O���m
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
				return food->gethpbonus(); // ���]�������[���O��_��
			}
		}
		break;
	}
	case Other:
	default:
		return 0; // �p�G�O���������A��^ 0 �[��
	}
	// �䤣����� ID �����~
	return 0;
}

CWeapon* CItemData::findWeaponByID(int id) {
	for (const auto& weapon : weapon_array) {
		if (weapon->getID() == id) { // ���] CWeapon ���� getID() ��k
			return weapon; // ���ǰt���Z��
		}
	}
	return nullptr; // �����Z��
}