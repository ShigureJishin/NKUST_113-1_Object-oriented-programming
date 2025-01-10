#include <iostream>
//#include <fstream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <iterator>
#include <sstream>
#include <ctime>
#include <windows.h>
#include "Fighter.h"
#include "Monster.h"
#include "food.h"
#include "ItemData.h"
#include "MapData.h"
#include "GlobalInfo.h"
#include "CmdParser.h"
#include "User.h"
#include "MonsterData.h"
#include "SkillData.h"
#include "AccountData.h"
#include "ArmorEffect.h"
#include <limits>
using namespace std;

#define MAXBARLEN 40

void askforbaglist (CFighter *f){
	int num = f->showAllBagItems ();
	if (num == 0)
		return;
	cout << f->getname () << " �ݭn�ϥέI�]���~��?\n0 --> No, Others --> Yes, �ϥΤ����~�s��: ";
	int selection;
	cin >> selection;
	if (selection){		
		if (!f->useBagItems (selection))
			cout << "�L���ﶵ�s�b" << endl;
	}
}

CMonster *MonsterSelection (CFighter *f){
	int selection;
	askforbaglist (f);
	cout << "�п�ܩǪ�����: 1. �T�@ 2. �j�@ 3. �r�@ 4. �䦺�@ " << endl;
	cin >> selection;
	int m_MaxHP, m_MaxSP, m_MaxRough;
	switch (selection){		
		case 1:
			m_MaxHP = f->getMAXHP () / 2;
			m_MaxSP = f->getMAXSP () / 2;
			m_MaxRough = (int)(f->getMAXHP () * 0.1);
			break;
		case 2:
			m_MaxHP = f->getMAXHP ();
			m_MaxSP = f->getMAXSP ();
			m_MaxRough = (int)(f->getMAXHP () * 0.2);
			break;
		case 3:
			m_MaxHP = (int)(f->getMAXHP () * 1.5);
			m_MaxSP = (int)(f->getMAXSP () * 1.2);
			m_MaxRough = (int)(f->getMAXHP () * 0.2);
			break;
		default:
			m_MaxHP = f->getMAXHP () * 2;
			m_MaxSP = f->getMAXSP () * 2;
			m_MaxRough = (int)(f->getMAXHP () * 0.5);			
	}
	CMonster *m  = new CMonster(m_MaxHP, m_MaxSP, m_MaxRough);
	system ("CLS");
	return m;
}

void bloodbarshow (int maxhp, int hp){		
		cout <<  "HP     |";
		float hpslotlen = (float)maxhp / MAXBARLEN;
		int numhp = (int)ceil(hp / hpslotlen);
		for (int i = 0; i < numhp; i++){
			cout <<"#";
		}
		numhp = (int)floor((maxhp- hp) / hpslotlen);
		for (int i = 0; i < numhp; i++){
			cout <<" ";
		}
		cout << "|" << endl;
}

void fightstatus (CMonster *m, CFighter *f){
		cout << endl << f->getname () << endl;
		bloodbarshow (f->getMAXHP (), f->getHP ());
		cout << m->getname () << endl;
		bloodbarshow (m->getMAXHP (), m->getHP ());
		cout << endl;
}

void fightshow (CMonster *m, CFighter *f){
		fightstatus (m, f);
		cout << "�z�ѤU " << f->getHP () << "�w��" << endl;
		Sleep (1000);		
}

void startfight (CMonster *m, CFighter *f){
	int f_damage = 0, s_damage = 0;
	CLifeEntity *first, *second;
	int whofirst;
	while (!m->isdead () && !f->isdead()){

		whofirst = rand () % 2;
		if (whofirst == 0){
			cout << "�Ǫ��m�o�����A���X��ˤH" << endl;
			first = (CLifeEntity *) m;
			second = (CLifeEntity *) f;
		} else {
			cout << "�A�m�o�����A���X��ˤH" << endl;
			first = (CLifeEntity *) f;
			second = (CLifeEntity *) m;	
		}

		s_damage = first->attack (second);		
		if (second->isdead()){
			whofirst == 0 ? fightshow ((CMonster *)first, (CFighter *)second) : fightshow ((CMonster *)second, (CFighter *)first);
			break;
		}

		f_damage = second->attack (first);		
		whofirst == 0 ? fightshow ((CMonster *)first, (CFighter *)second) : fightshow ((CMonster *)second, (CFighter *)first);
	}
	if (m->isdead () && !f->isdead ()){
		cout << "�Ǫ��w���A�q�Ǫ����W���U�_��" << endl;		
		CItemData *id = CGlobalInfo::itm_data;			
		f->captureItem (id->getRand ());
	
		//f->showAllBagItems ();
	}
}


CItemData *CGlobalInfo::itm_data = new CItemData;
CCmdParser *CGlobalInfo::parser = new CCmdParser;
CMapData* CGlobalInfo::map_data = new CMapData;
CUser *CGlobalInfo::user = new CUser;
CMonsterData *CGlobalInfo::monster_data = new CMonsterData;
CSkillData *CGlobalInfo::skillManager = new CSkillData;
CArmorEffectData *CGlobalInfo::armor_effect_data = new CArmorEffectData("ArmorEffect.txt");
CAccountData* CGlobalInfo::accountManager = new CAccountData("UserDatas.txt");

int CMonster::counter_for_monster_id = 0;

void Initialize (){
	srand((unsigned int)time(NULL));
	CMonster::resetCounter();
	CGlobalInfo::itm_data->Initialize ();
	CGlobalInfo::map_data->generate_monsters ();
	CGlobalInfo::skillManager->Initialize();
}

int main() {
	/* �n�J */
	while (CGlobalInfo::accountManager->query() < 0) {
		Sleep(1000);
		system("cls");
	}
	system("cls");

	/* ���� */
	while (CGlobalInfo::accountManager->queryCharacters() < 0) {
		Sleep(1000);
		system("cls");
	}
	system("cls");

	Initialize();
	CFighter* fighter = CGlobalInfo::accountManager->getFighter();
	CGlobalInfo::user->set_user((CLifeEntity*)fighter);
	int cur_city = CGlobalInfo::user->get_current_city();
	CGlobalInfo::map_data->show_description(cur_city);

	while (TRUE) {
		/* �C�� */
		while (CGlobalInfo::parser->query() >= 0) {
			CGlobalInfo::accountManager->saveToFile();
			//cur_city = CGlobalInfo::user->get_current_city();
			//CGlobalInfo::map_data->show_description (cur_city);
		}

		/* �n�J */
		CGlobalInfo::accountManager->logout();
		while (CGlobalInfo::accountManager->query() < 0) {
			Sleep(1000);
			system("cls");
		}
		system("cls");

		/* ���� */
		while (CGlobalInfo::accountManager->queryCharacters() < 0) {
			Sleep(1000);
			system("cls");
		}

		system("cls");
		Initialize();
		fighter = CGlobalInfo::accountManager->getFighter();
		CGlobalInfo::user->set_user((CLifeEntity*)fighter);
		cur_city = CGlobalInfo::user->get_current_city();
		CGlobalInfo::map_data->show_description(cur_city);
	}

	system("pause");
	return 0;
}

