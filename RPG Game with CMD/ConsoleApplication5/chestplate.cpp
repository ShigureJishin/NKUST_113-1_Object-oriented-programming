#include <iostream>
#include "Item.h"
#include "chestplate.h"
#include "LifeEntity.h"
#include "Fighter.h"
#include "def.h"

using namespace std;

CChestplate::CChestplate(string inname, int initSize, int initWeight, int initID, int init_defense) : CItem(inname, initSize, initWeight, initID, Chestplate) {
	bonus_defense = init_defense;
}

int CChestplate::getdefensebonus() {
	return bonus_defense;
}

void CChestplate::beUsed(CLifeEntity* le) {
	CFighter* f = (CFighter*)le;

	cout << "�Ԥh�˳� " << getName() << ", ";
	cout << "���m�O�q�쥻 " << f->getDefense();
	f->addDefense(this->getdefensebonus());
	cout << "�W�ɨ� " << f->getDefense() << endl;
}

void CChestplate::UnUsed(CLifeEntity* le) {
	CFighter* f = (CFighter*)le;

	cout << "�Ԥh���U " << getName() << " ";
	cout << "���m�O�q�쥻 " << f->getDefense();
	f->delDefense(this->getdefensebonus());
	cout << "�U���� " << f->getDefense() << endl;
}

int CChestplate::isA() {
	return echestplate;
}