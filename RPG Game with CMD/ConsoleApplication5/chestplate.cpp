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

	cout << "戰士裝備 " << getName() << ", ";
	cout << "防禦力從原本 " << f->getDefense();
	f->addDefense(this->getdefensebonus());
	cout << "上升到 " << f->getDefense() << endl;
}

void CChestplate::UnUsed(CLifeEntity* le) {
	CFighter* f = (CFighter*)le;

	cout << "戰士卸下 " << getName() << " ";
	cout << "防禦力從原本 " << f->getDefense();
	f->delDefense(this->getdefensebonus());
	cout << "下降到 " << f->getDefense() << endl;
}

int CChestplate::isA() {
	return echestplate;
}