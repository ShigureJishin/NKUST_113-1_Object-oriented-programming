#include <iostream>
#include <Windows.h>
#include "GlobalInfo.h"
#include "LifeEntity.h"
#include "Fighter.h"
#include "ArmorEffect.h"
#include "Pet.h"
#include "def.h"

CLifeEntity::CLifeEntity (int initHP, int initSP, string initname){
	maxSP = SP = initSP;
	maxHP = HP = initHP;
	Name = initname;
	weapon = nullptr;
	chestplate = nullptr;
	helmet = nullptr;
	boots = nullptr;
}

void CLifeEntity::setInitSPHP (int initHP, int initSP, int initMP){
	maxSP = SP = initSP;
	maxHP = HP = initHP;
	maxMP = MP = initMP;
}

void CLifeEntity::setMP(int inMP) {
	MP = inMP > maxMP ? maxMP : inMP;
}

void CLifeEntity::addMP(int inMP) {
	MP = (inMP + MP) > maxMP ? maxMP : (MP + inMP);
}

void CLifeEntity::delMP(int inMP) {
	MP -= inMP;
}

void CLifeEntity::addMAXMP(int inMP) {
	maxMP += inMP;
	MP += inMP;
}

void CLifeEntity::setHP (int inHP){
	HP = inHP > maxHP ? maxHP : inHP;	
}

void CLifeEntity::addHP (int inHP){
	HP = (inHP+HP) > maxHP ? maxHP : (HP+inHP);	
}

void CLifeEntity::addSP (int inSP){
	SP = inSP+SP;	
}

void CLifeEntity::delSP (int inSP){
	SP -= inSP;	
}

void CLifeEntity::addMAXHP(int inMAXHP) {
	maxHP += inMAXHP;
	HP += inMAXHP;
}

void CLifeEntity::addMAXSP(int inMAXSP) {
	maxSP += inMAXSP;
	SP += inMAXSP;
}

int CLifeEntity::getHP (){
	return (HP > 0 ? HP : 0);	
}

int CLifeEntity::getMAXHP (){
	return (maxHP);	
}

int CLifeEntity::getSP (){
	return SP;	
}

int CLifeEntity::getMAXSP (){
	return (maxSP);	
}

bool CLifeEntity::isdead (){
	return (HP<=0);
}

int  CLifeEntity::gethurt (int hurt){
	if (hurt > HP)
		setHP(0);
	else if (hurt > 0)
		setHP(HP - hurt);
	return HP;
}

string CLifeEntity::getname (){
	return Name;
}

void CLifeEntity::setname (string inname){
	Name = inname;	
}

bool CLifeEntity::kill (CLifeEntity *enemy){
	int f_damage = 0, s_damage = 0;
	CLifeEntity *first, *second;
	int whofirst;
	while (!this->isdead () && !enemy->isdead()){
		whofirst = rand () % 2;
		if (whofirst == 0){
			cout << "���m�o�����A���X��ˤH" << endl;
			first = (CLifeEntity *) enemy;
			second = (CLifeEntity *) this;
		} else{
			cout << "�A�m�o�����A���X��ˤH" << endl;
			first = (CLifeEntity *) this;
			second = (CLifeEntity *) enemy;	
		}
		
		
		// ���a����
		s_damage = first->attack (second);		
		fightstatus (enemy, this);
		if (second->isdead()){			
			Sleep (1000);				
			break;
		}

		// �p�G���a���d���A���d������
		if (this->isA() == efighter && ((CFighter*)this)->getCurrentPet()) {
			CPet *pet = ((CFighter*)this)->getCurrentPet();
			if (pet) {
				pet->attack(enemy);  // ���d������
				fightstatus(enemy, this);
			}
			if (enemy->isdead()) {
				Sleep(1000);
				break;
			}

			Sleep(2000);
		}
		

		// �Ǫ�����
		f_damage = second->attack (first);		
		fightstatus (enemy, this);		
		Sleep (2000);
	}
	if (this->isdead ())
		return 0;
	return 1;
}

void CLifeEntity::fightstatus (CLifeEntity *f, CLifeEntity *s){
		cout << endl << f->getname () << endl;
		bloodbarshow (string ("HP"), f->getMAXHP (), f->getHP ());
		cout << s->getname () << endl;
		bloodbarshow (string ("HP"), s->getMAXHP (), s->getHP ());
		cout << endl;
}

void CLifeEntity::bloodbarshow (string title, int maxvalue, int value){		
		cout <<  title << "     |";
		float hpslotlen = (float)maxvalue / MAXBLOODBARLEN;
		int numhp = (int)ceil(value / hpslotlen);
		for (int i = 0; i < numhp; i++){
			cout <<"#";
		}
		numhp = (int)floor((maxvalue- value) / hpslotlen);
		for (int i = 0; i < numhp; i++){
			cout <<" ";
		}
		cout << "|" << endl;
}
