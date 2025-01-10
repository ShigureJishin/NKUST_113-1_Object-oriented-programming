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
		hp += 10;  // �C�ɯżW�[����q
		atk += 5;  // �C�ɯżW�[�������O
		cout << "�����d�� " << this->getname() << " �ɯ� 1 ���A�ثe���� Lv" << Level << endl;
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
		cout << "�d��" << this->getname() << " �r�O�@���A�y�� " << l->getname() << " " << damage << " ��l��" << endl;
	}
	else {
		cout << "�d��" << this->getname() << " �r�O�@���A�y�� " << l->getname() << " ���`���B�A�]�����פF����" << endl;
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
