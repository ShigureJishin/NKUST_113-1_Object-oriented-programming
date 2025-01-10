#include <iostream>
#include "Pet.h"

#include "def.h"

CPet::CPet(string name="", int level = 0, int hp = 0, int atk = 0, int XP = 0) : 
    CLifeEntity(hp, atk, name), name(name), Level(level), hp(hp), atk(atk), XP(0) {
}

void CPet::setName(string newName) {
    name = newName;
}

void CPet::addXP(int inXP) {
	XP += inXP;

	if (XP >= 1000) {
		XP -= 1000;
		Level += 1;
		hp += 10;  // 每升級增加的血量
		atk += 5;  // 每升級增加的攻擊力
		cout << "恭喜寵物 " << this->getname() << " 升級 1 等，目前等級 Lv" << Level << endl;
	}
}

int CPet::physicaldamage() {
	return getDamage();
}

int CPet::attack(CLifeEntity* l) {
	int damage = physicaldamage() - l->defense(l);
	if (damage > l->getHP())
		damage = l->getHP();

	l->gethurt(damage);

	if (damage > 0) {
		cout << "寵物" << this->getname() << " 猛力一揮，造成 " << l->getname() << " " << damage << " 血損失" << endl;
	}
	else {
		cout << "寵物" << this->getname() << " 猛力一揮，造成 " << l->getname() << " 異常幸運，因此躲避了攻擊" << endl;
	}
	return (damage);
	return 0;
}

int CPet::defense(CLifeEntity* l) {
	return 0;
}

int CPet::isA() {
	return epet;
}
