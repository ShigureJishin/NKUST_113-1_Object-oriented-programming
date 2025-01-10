#include <iostream>
#include "Item.h"
#include "potion.h"
#include "LifeEntity.h"
#include "def.h"

using namespace std;

CPotion::CPotion(string inname, int initSize, int initWeight, int initID, int init_mp) : CItem(inname, initSize, initWeight, initID, Potion) {
	bonus_mp  = init_mp;
}

int CPotion::getmpbonus() {
	return bonus_mp;
}

void CPotion::beUsed(CLifeEntity* le) {
	cout << "戰士使用藥水" << getName() << ", ";
	le->addMP(this->getmpbonus());
	cout << "MP回升到 " << le->getMP() << endl;
}

void CPotion::UnUsed(CLifeEntity* le) {
}


int CPotion::isA() {
	return efood;
}