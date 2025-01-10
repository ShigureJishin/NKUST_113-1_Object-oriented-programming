#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cassert>
#include <Windows.h>
#include "Place.h"
#include "CmdParser.h"
#include "GlobalInfo.h"
#include "User.h"
#include "MapData.h"
#include "Fighter.h"
#include "def.h"
#include "ItemData.h"
#include "Store.h"
#include "SkillData.h"
#include "Pet.h"

int function_exit (vector<string> &tokens) {	
	system("cls");
	cout << "�A��!" << endl;
	exit(0);
	return -1;
}

int function_logout(vector<string>& tokens) {
	system("cls");
	return -1;
}

int function_next_direction (vector<string> &tokens){	
	if (tokens.size () != 1){
		for (vector<string>::iterator it = tokens.begin (); it != tokens.end (); it++){
			cerr << (*it) << " ";
		}
		cerr << " command error" << endl;
		return 0;
	}
	int next_dir = 0;
	string dir = tokens [0];
	if (dir == string ("east")){
		next_dir = eEast;
	} else if  (dir == string ("west")){
		next_dir = eWest;
	} else if  (dir == string ("north")){
		next_dir = eNorth;	
	} else if  (dir == string ("south")){
		next_dir = eSouth;	
	} else if  (dir == string ("eastnorth")){
		next_dir = eEastNorth;	
	} else if  (dir == string ("eastsouth")){
		next_dir = eEastSouth;	
	} else if  (dir == string ("westnorth")){
		next_dir = eWestNorth;	
	} else if  (dir == string ("westsouth")){
		next_dir = eWestSouth;
	} else {
		cout << "no such command " << dir << endl;
		return 0;
	}
	
	int next_city = CGlobalInfo::user->goto_next_city (next_dir);
	if (next_city){
		system ("cls");
		CGlobalInfo::map_data->show_description (next_city);		
	} else {
		cout << "����S����!!!�д��Ӥ�V�a" << endl;		
	}
	return 0;
}

int function_list (vector<string> &tokens){	
	if (tokens.size () != 1){
		for (vector<string>::iterator it = tokens.begin (); it != tokens.end (); it++){
			cerr << (*it) << " ";
		}
		cerr << " command error" << endl;
		return 0;
	}	

	system("cls");
	int city = CGlobalInfo::user->get_current_city ();	
	CPlace *cityptr = CGlobalInfo::map_data->get_place_by_id (city);
	if (cityptr){
		cout << "�i�Ǫ��C��j" << endl;
		cityptr->show_mosters ();
		cout << endl;
	}

	CGlobalInfo::map_data->show_description(city);
	return 0;
}

int function_kill (vector<string> &tokens){	
	if (tokens.size () != 2){
		for (vector<string>::iterator it = tokens.begin (); it != tokens.end (); it++){
			cerr << (*it) << " ";
		}
		cerr << " command error" << endl;
		return 0;
	}	
	string monster_engname = tokens[1];
	int city = CGlobalInfo::user->get_current_city ();	
	CPlace *cityptr = CGlobalInfo::map_data->get_place_by_id (city);
	assert(cityptr);
	CMonster *monster = cityptr->get_monster_by_engname (monster_engname);
	if (!monster){
		cout << "no such monsters" << endl;
		return 0;
	}

	CLifeEntity *usr = CGlobalInfo::user->get_user ();
	assert (usr);
	if (usr->kill (monster)){		
		
		cout << "�Ǫ��w���A�q�Ǫ����W���U�_��" << endl;		
		CItemData *id = CGlobalInfo::itm_data;		
		if (usr->isA() == efighter){
			((CFighter *)usr)->captureItem (id->getRand());
			int RandMoney = 200 + rand() % ((CLifeEntity*)monster)->getMAXHP();
			int muilt = (((CFighter*)usr)->getCurrentPet()) ? ((CFighter*)usr)->getCurrentPet()->getLevel() : 1;
			if (muilt > 1)
				cout << "�]����a�d��������o���v���ɡA";
			((CFighter*)usr)->addMoney(RandMoney * muilt);
			int RandXP = 400 + rand() % ((CLifeEntity*)monster)->getMAXHP();
			((CFighter *)usr)->addXP(RandXP);
			if (((CFighter *)usr)->getCurrentPet())
				((CFighter *)usr)->getCurrentPet()->addXP(400);

			// �d������
			int captureChance = rand() % 100;	 // 0 ~ 99 ���H����
			if (captureChance < ((CFighter*)usr)->getLucky()) {
				cout << "�A�P����@�ѤO�q�A�o���Ǫ������F�A���d���I" << endl;
				CPet *newPet = new CPet( ((CLifeEntity *)monster)->getname(), 1, monster->getMAXHP(), monster->getMAXSP(), 0);
				((CFighter*)usr)->addPet(newPet); // �N�d���[�J���a���d���M��
				cout << "��o�s�d���G" << newPet->getname() << endl;
			}

			cityptr->remove_moster_by_engname(monster_engname);
			if (cityptr->get_monster_count() == 0) {
				CGlobalInfo::map_data->generate_monsters_place(cityptr);
			}
		}
	} else {
		cout << "�A�{�b�ݩ󦺤`���A" << endl;
	}
	
	return 0;
}


int function_check_bag (vector<string> &tokens){	
	if (tokens.size () != 1){
		for (vector<string>::iterator it = tokens.begin (); it != tokens.end (); it++){
			cerr << (*it) << " ";
		}
		cerr << " command error" << endl;
		return 0;
	}	
	CLifeEntity *usr = CGlobalInfo::user->get_user ();
	assert (usr);
	if (usr->isA() == efighter){
		CFighter *f = (CFighter *) usr;	
		cout << f->getname () << " ��I�]���}" << endl;
		cout << "Money: " << "$" << ((CFighter*)usr)->getMoney() << endl;

		int num = f->showAllBagItems ();
		if (num == 0){			
			cout << "�I�]�ŪŦp�]" << endl;
			cout << f->getname () << "  ���W�I�]" << endl;
			return 0;
		}
	
		int selection = 0;		
		cout << "�ݭn���򪫫~ (0�N���ݭn)" << endl;
		cin >> selection;
		while (selection > 0){
			if (!f->useBagItems (selection)){
				cout << "�L���ﶵ�s�b" << endl;
			}
			selection = 0;
			cout << "�ݭn���򪫫~ (0�N���ݭn)" << endl;
			cin >> selection;
		}		
		cout << f->getname () << "  ���W�I�]" << endl;

	}	
	cin.clear();
	cin.ignore(1024, '\n');
	Sleep(1000);
	system("cls");
	int city = CGlobalInfo::user->get_current_city();
	CGlobalInfo::map_data->show_description(city);

	return 0;
}

/* �a�϶ǰe */
int function_teleport (vector<string> &tokens){	
	if (tokens.size () != 2){
		for (vector<string>::iterator it = tokens.begin (); it != tokens.end (); it++){
			cerr << (*it) << " ";
		}
		cerr << " command error" << endl;
		return 0;
	}

	CLifeEntity* usr = CGlobalInfo::user->get_user();
	assert(usr);
	if (usr->isA() == efighter) {
		int next_city = ((CFighter*)usr)->moveto_city(tokens[1].c_str());
		
		if (next_city) {
			system("cls");
			CGlobalInfo::map_data->show_description(next_city);
		}
		else {
			cout << "No Such Map" << endl;
			Sleep(1000);
			system("cls");
			int city = CGlobalInfo::user->get_current_city();
			CGlobalInfo::map_data->show_description(city);
		}
	}
	return 0;
}

/* �H�����A�� */
int function_player_stauts(vector<string>& tokens) {
	if (tokens.size() != 1) {
		for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
			cerr << (*it) << " ";
		}
		cerr << " command error" << endl;
		return 0;
	}
	system("cls");

	CLifeEntity* usr = CGlobalInfo::user->get_user();
	assert(usr);

	

	if (usr->isA() == efighter) {
		CFighter* f = (CFighter*)usr;
		while (true) {

			// ��ܤH�����A��
			cout << f->getname() << " �}�ҤH�����A��" << endl;
			cout << "----------------------------------------" << endl;
			cout << usr->getname() << "'s �ݩʭ��O" << setw(6) << "Lv" << f->getLevel() << setw(6) << " " << f->getXP() << "/1000" << endl;
			cout << "¾�~ : " << f->getProfession_String() << endl;
			cout << "HP : " << usr->getHP() << "/" << usr->getMAXHP() << endl
				<< "MP : " << f->getMP() << "/" << f->getMAXMP() << endl
				<< "ATK : " << usr->getSP() << endl
				<< "Defense : " << f->getDefense() << endl
				<< "Lucky : " << f->getLucky() << endl;

			cout << "----------------------------------------" << endl;
			cout << "�i��e�˳ơj" << endl;
			cout << "�Z��   : " << (usr->getWeapon() ? usr->getWeapon()->getName() : "�L") << "(" << (usr->getWeapon() ? usr->getWeapon()->getID() : 0) << ")" << endl;
			cout << "�U�l   : " << (usr->getHelmet() ? usr->getHelmet()->getName() : "�L") << "(" << (usr->getHelmet() ? usr->getHelmet()->getID() : 0) << ")" << endl;
			cout << "�ݥ�   : " << (usr->getChestplate() ? usr->getChestplate()->getName() : "�L") << "(" << (usr->getChestplate() ? usr->getChestplate()->getID() : 0) << ")" << endl;
			cout << "�u�l   : " << (usr->getBoots() ? usr->getBoots()->getName() : "�L") << "(" << (usr->getBoots() ? usr->getBoots()->getID() : 0) << ")" << endl;
			f->getCurrentSet();

			cout << "----------------------------------------" << endl
				<< "�i�ޯ�j" << endl
				<< f->displaySkills()
				<< "----------------------------------------" << endl
				<< "�i�ϥ��ݩ��I�� �G " << f->getProperty_Point() << " �I" << endl
				<< "�i�ϥΧޯ��I�� �G " << f->getSkill_Point() << " �I" << endl
				<< "----------------------------------------" << endl
				<< "��e���B�G" << "$" << f->getMoney() << endl
				<< "----------------------------------------" << endl;

			cout << "�i�ݩ��I��O�C��j" << endl;
			cout << "1. ��O 1 �ݩ��I�A���� 10 HP" << endl;
			cout << "2. ��O 1 �ݩ��I�A���� 20 MP" << endl;
			cout << "3. ��O 1 �ݩ��I�A���� 5 �I����" << endl;
			cout << "4. ��O 1 �ݩ��I�A���� 10 �I���m" << endl;
			cout << "5. ��O 2 �ݩ��I�A���� 1 �I���B" << endl;

			int selection = 0;
			cout << "�ݭn�ɯŤ����ݩ� (0�N��h�X���O)" << endl;
			cin >> selection;

			if (cin.fail()) {
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "�L�Ŀ�J�A�п�J�Ʀr�C" << endl;
				Sleep(1000);
				system("cls");
				continue;
			}

			if (selection == 0) {
				cout << f->getname() << " ���W�H�����A��" << endl;
				break;
			}

			if (!f->addProperty(selection)) {
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "�L���ﶵ�s�b���ݩ��I�Ƥ���" << endl;
				Sleep(1000);
				system("cls");
				continue;
			}

			Sleep(1000);
			system("cls");

		}
	}

	cin.clear();
	cin.ignore(1024, '\n');
	Sleep(1000);
	system("cls");
	int city = CGlobalInfo::user->get_current_city();
	CGlobalInfo::map_data->show_description(city);

	return 0;
}

/* �ޯୱ�O */
int function_skill_menu(vector<string>& tokens) {
	if (tokens.size() != 1) {
		for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
			cerr << (*it) << " ";
		}
		cerr << " command error" << endl;
		return 0;
	}
	system("cls");

	CLifeEntity* usr = CGlobalInfo::user->get_user();
	assert(usr);

	if (usr->isA() == efighter) {
		CFighter* f = (CFighter*)usr;
		cout << f->getname() << " �}�ҧޯୱ�O" << endl;

		while (true) {
			cout << "----------------------------------------" << endl;
			cout << usr->getname() << "'s �ޯୱ�O"
				<< setw(6) << "Lv" << f->getLevel()
				<< setw(6) << " " << f->getXP() << "/1000" << endl;

			cout << "----------------------------------------" << endl
				<< "�i�ޯ�j" << endl
				<< f->displaySkills()
				<< "----------------------------------------" << endl
				<< "�i�ϥΧޯ��I�� �G " << f->getSkill_Point() << " �I" << endl
				<< "----------------------------------------" << endl;

			cout << "1. �ǲ߷s�ޯ�\n2. �ɯŧޯ�\n3. ���}�ޯୱ�O\n�п�ܾާ@: ";
			int selection = 0;
			cin >> selection;

			if (cin.fail()) {
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "�L�Ŀ�J�A�п�J�Ʀr�C" << endl;
				Sleep(1500);
				system("cls");
				continue;
			}

			if (selection == 1) {
				cout << "�i�i�ǲߧޯ�M��j" << endl;
				CGlobalInfo::skillManager->showAllSkills();

				cout << "�п�J�n�ǲߪ��ޯ�ID: ";
				int skillID;
				cin >> skillID;

				if (CGlobalInfo::skillManager->getSkill(skillID)) {
					f->learnSkill(skillID);
				}
				else {
					cout << "�ޯ� ID �L�ĩΤ��s�b�I" << endl;
				}
			}
			else if (selection == 2) {
				cout << "�п�J�n�ɯŪ��ޯ�Ǹ�: ";
				int skillID;
				cin >> skillID;

				f->upgradeSkill(skillID);
			}
			else if (selection == 3) {
				cout << f->getname() << " ���W�ޯୱ�O" << endl;
				break;
			}
			else {
				cout << "�L���ﶵ�s�b" << endl;
			}

			Sleep(1500);
			system("cls");
			cin.clear();
			cin.ignore(1024, '\n');
		}
		
	}

	Sleep(1000);
	system("cls");
	int city = CGlobalInfo::user->get_current_city();
	CGlobalInfo::map_data->show_description(city);

	return 0;
}

/* �d�����O */
int function_pet_menu(vector<string>& tokens) {
	if (tokens.size() != 1) {
		for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
			cerr << (*it) << " ";
		}
		cerr << " command error" << endl;
		return 0;
	}
	system("cls");

	CLifeEntity* usr = CGlobalInfo::user->get_user();
	assert(usr);

	if (usr->isA() == efighter) {
		CFighter* f = (CFighter*)usr;
		while (true) {
			cout << f->getname() << " �}���d�����O" << endl;
			cout << "----------------------------------------" << endl;

			cout << usr->getname() << "'s �d�����O" << setw(6) << "Lv" << f->getLevel() << setw(6) << f->getXP() << "/1000" << endl;

			cout << "�i��e�d���j" << endl;
			cout << f->getCurrentPet_String();

			cout << "----------------------------------------" << endl
				<< "�i�֦��d���j" << endl;
			f->showPets();
			cout << "----------------------------------------" << endl;

			int selection = 0;
			cout << "�ݭn���d���� (0�N������d�� -1�N�����})" << endl;
			cin >> selection;

			if (cin.fail()) {
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "�L�Ŀ�J�A�п�J�Ʀr�C" << endl;
				Sleep(1500);
				system("cls");
				continue;
			}

			if (selection == -1) {
				cout << f->getname() << " ���W�d�����O" << endl;
				break;
			}

			if (!f->setCurrentPet(selection - 1)) {
				cout << "�L���ﶵ�s�b" << endl;
			}

			Sleep(1500);
			system("cls");

		}
	}

	cin.clear();
	cin.ignore(1024, '\n');
	Sleep(1000);
	system("cls");
	int city = CGlobalInfo::user->get_current_city();
	CGlobalInfo::map_data->show_description(city);

	return 0;
}

/* �}�Ұө� */
int function_store(vector<string>& tokens) {
	if (tokens.size() != 1) {
		for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
			cerr << (*it) << " ";
		}
		cerr << " command error" << endl;
		return 0;
	}

	int cur_city = CGlobalInfo::user->get_current_city();
	auto storeIt = CGlobalInfo::map_data->storedata.find(cur_city);
	if (storeIt == CGlobalInfo::map_data->storedata.end()) {
		cerr << "���a�I�L�ө�" << endl;
		return 0;
	}
	CLifeEntity* usr = CGlobalInfo::user->get_user();
	assert(usr);

	CStore* store = storeIt->second;
	assert(store);

	cout << "�w��Ө� " << store->getName() << " !!" << endl;

	cout << usr->getname() << ", �A�֦� $" << ((CFighter*)usr)->getMoney() << endl;
	store->displayStoreInfo();

	int selection = 0;
	cout << "�ݭn�ʶR���򪫫~ (0�N���ݭn)" << endl;
	cin >> selection;

	while (selection > 0) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "�L�Ŀ�J�A�п�J�Ʀr�C" << endl;
			Sleep(1500);
			system("cls");
			continue;
		}

		if (selection > 0 && selection <= store->getItemCount()) {

			pair<CItem*, int> itemPair = store->getItemById(selection);
			CItem* item = itemPair.first;
			int itemPrice = itemPair.second;

			if (!item) {
				cout << "�L���ﶵ�s�b" << endl;
				continue;
			}

			if (((CFighter*)usr)->getMoney() >= itemPrice) {
				cout << "�ʶR���\: " << item->getName() << "�A��O $" << itemPrice << endl;
				((CFighter*)usr)->reduceMoney(itemPrice);
				((CFighter*)usr)->buyItem(item);  // �[�J���~�ܪ��a
			}
			else {
				cout << "���B�����A�L�k�ʶR " << item->getName() << endl;
			}
		}

		cout << "�ݭn�ʶR���򪫫~ (0�N���ݭn)" << endl;
		cin >> selection;
	}

	cout << usr->getname() << " ���}�ө�" << endl;
	
	Sleep(1000);
	system("cls");
	int city = CGlobalInfo::user->get_current_city();
	CGlobalInfo::map_data->show_description(city);

	return 0;
}

int function_showmap(vector<string>& tokens) {
	CLifeEntity* usr = CGlobalInfo::user->get_user();
	assert(usr);
	int cur_city = ((CFighter*)usr)->get_current_city();

	system("cls");
	CGlobalInfo::map_data->show_map(cur_city);
	CGlobalInfo::map_data->show_description(cur_city);
	return 0;
}

int function_showcommand(vector<string>& tokens) {
	system("cls");

	ifstream fin("command_list.txt");

	if (!fin) {
		cout << "�S�� command_list.txt �ɮסI\n";
		exit(0);
	}

	string line;
	while (getline(fin, line)) { // ���T���ɮ�Ū���覡
		cout << line << endl;
	}
	fin.close();
	system("pause");

	system("cls");
	int city = CGlobalInfo::user->get_current_city();
	CGlobalInfo::map_data->show_description(city);
	return 0;
}

int function_showallmonster(vector<string>& tokens) {
	system("cls");
	CGlobalInfo::map_data->show_allmonster();
	system("pause");
	system("cls");
	int city = CGlobalInfo::user->get_current_city();
	CGlobalInfo::map_data->show_description(city);

	return 0;
}

int function_regenmonster(vector<string>& tokens) {
	system("cls");
	cout << "�i�t�δ��ܡj ���a�ϩǪ��N���s�ͦ��I" << endl;
	Sleep(500);
	CMonster::resetCounter();
	CGlobalInfo::map_data->generate_monsters();
	int city = CGlobalInfo::user->get_current_city();
	CGlobalInfo::map_data->show_description(city);

	return 0;
}

CCmdParser::CCmdParser (){
	mappingfunc [string("exit")] = function_exit;
	mappingfunc [string("logout")] = function_logout;
	mappingfunc [string("east")] = function_next_direction;
	mappingfunc [string("eastnorth")] = function_next_direction;
	mappingfunc [string("eastsouth")] = function_next_direction;
	mappingfunc [string("west")] = function_next_direction;
	mappingfunc [string("westsouth")] = function_next_direction;
	mappingfunc [string("westnorth")] = function_next_direction;
	mappingfunc [string("north")] = function_next_direction;
	mappingfunc [string("south")] = function_next_direction;
	mappingfunc [string("ls")] = function_list;
	mappingfunc [string("kill")] = function_kill;
	mappingfunc [string("checkbag")] = function_check_bag;
	mappingfunc[string("move")] = function_teleport;
	mappingfunc[string("playerstatus")] = function_player_stauts;
	mappingfunc[string("skillmenu")] = function_skill_menu;
	mappingfunc[string("petmenu")] = function_pet_menu;
	mappingfunc[string("store")] = function_store;
	mappingfunc[string("map")] = function_showmap;
	mappingfunc[string("cmdlist")] = function_showcommand;
	mappingfunc[string("allmonster")] = function_showallmonster;
	mappingfunc[string("regenmonster")] = function_regenmonster;
#if 0
	for (vector<string>::iterator it = tokens.begin (); it != tokens.end (); it++){
		cout << (*it) << endl;			
	}		
#endif

}

int CCmdParser::query (){
	string sentense;	
	getline (cin, sentense);	
	vector<string> tokens;		
	splitstring (sentense, tokens, string(" "));	
	if (tokens.size () == 0){ // ����J
		return 0;
	}

	map<string,  void (*)>::iterator it;
	it = mappingfunc.find (tokens [0]);
	if (it == mappingfunc.end ()){
		cout << "no such commands" << endl;
		return 0;
	}	
	return (reinterpret_cast<int(*)(const vector<string> &)>(it->second)(tokens));		
}

void CCmdParser::splitstring(const string& s, vector<string>& v, const string& c)
{
	string::size_type pos1, pos2;
	pos2 = s.find_first_of(c);
	pos1 = 0;
	while (string::npos != pos2){
		if(pos2-pos1)
			v.push_back(s.substr(pos1, pos2 - pos1));
		pos1 = pos2 + 1;
		pos2 = s.find_first_of(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}

