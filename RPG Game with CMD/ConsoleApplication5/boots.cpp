#include <iostream>
#include "Item.h"
#include "boots.h"
#include "LifeEntity.h"
#include "Fighter.h"
#include "def.h"

using namespace std;

CBoots::CBoots(string inname, int initSize, int initWeight, int initID, int init_defense) : CItem(inname, initSize, initWeight, initID, Boots) {
	bonus_defense = init_defense;
}

int CBoots::getdefensebonus() {
	return bonus_defense;
}

void CBoots::beUsed(CLifeEntity* le) {
	CFighter* f = (CFighter*)le;

	cout << "�Ԥh�˳� " << getName() << ", ";
	cout << "���m�O�q�쥻 " << f->getDefense();
	f->addDefense(this->getdefensebonus());
	cout << "�W�ɨ� " << f->getDefense() << endl;
}

void CBoots::UnUsed(CLifeEntity* le) {
	CFighter* f = (CFighter*)le;

	cout << "�Ԥh���U " << getName() << " ";
	cout << "���m�O�q�쥻 " << f->getDefense();
	f->delDefense(this->getdefensebonus());
	cout << "�U���� " << f->getDefense() << endl;
}


int CBoots::isA() {
	return eboots;
}