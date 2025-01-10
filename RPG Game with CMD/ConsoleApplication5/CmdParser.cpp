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
	cout << "再見!" << endl;
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
		cout << "那邊沒路喔!!!請換個方向吧" << endl;		
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
		cout << "【怪物列表】" << endl;
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
		
		cout << "怪物已死，從怪物身上掉下寶物" << endl;		
		CItemData *id = CGlobalInfo::itm_data;		
		if (usr->isA() == efighter){
			((CFighter *)usr)->captureItem (id->getRand());
			int RandMoney = 200 + rand() % ((CLifeEntity*)monster)->getMAXHP();
			int muilt = (((CFighter*)usr)->getCurrentPet()) ? ((CFighter*)usr)->getCurrentPet()->getLevel() : 1;
			if (muilt > 1)
				cout << "因為攜帶寵物金幣獲得倍率提升，";
			((CFighter*)usr)->addMoney(RandMoney * muilt);
			int RandXP = 400 + rand() % ((CLifeEntity*)monster)->getMAXHP();
			((CFighter *)usr)->addXP(RandXP);
			if (((CFighter *)usr)->getCurrentPet())
				((CFighter *)usr)->getCurrentPet()->addXP(400);

			// 寵物捕獲
			int captureChance = rand() % 100;	 // 0 ~ 99 的隨機數
			if (captureChance < ((CFighter*)usr)->getLucky()) {
				cout << "你感受到一股力量，這隻怪物成為了你的寵物！" << endl;
				CPet *newPet = new CPet( ((CLifeEntity *)monster)->getname(), 1, monster->getMAXHP(), monster->getMAXSP(), 0);
				((CFighter*)usr)->addPet(newPet); // 將寵物加入玩家的寵物清單
				cout << "獲得新寵物：" << newPet->getname() << endl;
			}

			cityptr->remove_moster_by_engname(monster_engname);
			if (cityptr->get_monster_count() == 0) {
				CGlobalInfo::map_data->generate_monsters_place(cityptr);
			}
		}
	} else {
		cout << "你現在屬於死亡狀態" << endl;
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
		cout << f->getname () << " 把背包打開" << endl;
		cout << "Money: " << "$" << ((CFighter*)usr)->getMoney() << endl;

		int num = f->showAllBagItems ();
		if (num == 0){			
			cout << "背包空空如也" << endl;
			cout << f->getname () << "  關上背包" << endl;
			return 0;
		}
	
		int selection = 0;		
		cout << "需要什麼物品 (0代表不需要)" << endl;
		cin >> selection;
		while (selection > 0){
			if (!f->useBagItems (selection)){
				cout << "無此選項存在" << endl;
			}
			selection = 0;
			cout << "需要什麼物品 (0代表不需要)" << endl;
			cin >> selection;
		}		
		cout << f->getname () << "  關上背包" << endl;

	}	
	cin.clear();
	cin.ignore(1024, '\n');
	Sleep(1000);
	system("cls");
	int city = CGlobalInfo::user->get_current_city();
	CGlobalInfo::map_data->show_description(city);

	return 0;
}

/* 地圖傳送 */
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

/* 人物狀態欄 */
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

			// 顯示人物狀態欄
			cout << f->getname() << " 開啟人物狀態欄" << endl;
			cout << "----------------------------------------" << endl;
			cout << usr->getname() << "'s 屬性面板" << setw(6) << "Lv" << f->getLevel() << setw(6) << " " << f->getXP() << "/1000" << endl;
			cout << "職業 : " << f->getProfession_String() << endl;
			cout << "HP : " << usr->getHP() << "/" << usr->getMAXHP() << endl
				<< "MP : " << f->getMP() << "/" << f->getMAXMP() << endl
				<< "ATK : " << usr->getSP() << endl
				<< "Defense : " << f->getDefense() << endl
				<< "Lucky : " << f->getLucky() << endl;

			cout << "----------------------------------------" << endl;
			cout << "【當前裝備】" << endl;
			cout << "武器   : " << (usr->getWeapon() ? usr->getWeapon()->getName() : "無") << "(" << (usr->getWeapon() ? usr->getWeapon()->getID() : 0) << ")" << endl;
			cout << "帽子   : " << (usr->getHelmet() ? usr->getHelmet()->getName() : "無") << "(" << (usr->getHelmet() ? usr->getHelmet()->getID() : 0) << ")" << endl;
			cout << "胸甲   : " << (usr->getChestplate() ? usr->getChestplate()->getName() : "無") << "(" << (usr->getChestplate() ? usr->getChestplate()->getID() : 0) << ")" << endl;
			cout << "靴子   : " << (usr->getBoots() ? usr->getBoots()->getName() : "無") << "(" << (usr->getBoots() ? usr->getBoots()->getID() : 0) << ")" << endl;
			f->getCurrentSet();

			cout << "----------------------------------------" << endl
				<< "【技能】" << endl
				<< f->displaySkills()
				<< "----------------------------------------" << endl
				<< "可使用屬性點數 ： " << f->getProperty_Point() << " 點" << endl
				<< "可使用技能點數 ： " << f->getSkill_Point() << " 點" << endl
				<< "----------------------------------------" << endl
				<< "當前金額：" << "$" << f->getMoney() << endl
				<< "----------------------------------------" << endl;

			cout << "【屬性點花費列表】" << endl;
			cout << "1. 花費 1 屬性點，提升 10 HP" << endl;
			cout << "2. 花費 1 屬性點，提升 20 MP" << endl;
			cout << "3. 花費 1 屬性點，提升 5 點攻擊" << endl;
			cout << "4. 花費 1 屬性點，提升 10 點防禦" << endl;
			cout << "5. 花費 2 屬性點，提升 1 點幸運" << endl;

			int selection = 0;
			cout << "需要升級什麼屬性 (0代表退出面板)" << endl;
			cin >> selection;

			if (cin.fail()) {
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "無效輸入，請輸入數字。" << endl;
				Sleep(1000);
				system("cls");
				continue;
			}

			if (selection == 0) {
				cout << f->getname() << " 關上人物狀態欄" << endl;
				break;
			}

			if (!f->addProperty(selection)) {
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "無此選項存在或屬性點數不足" << endl;
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

/* 技能面板 */
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
		cout << f->getname() << " 開啟技能面板" << endl;

		while (true) {
			cout << "----------------------------------------" << endl;
			cout << usr->getname() << "'s 技能面板"
				<< setw(6) << "Lv" << f->getLevel()
				<< setw(6) << " " << f->getXP() << "/1000" << endl;

			cout << "----------------------------------------" << endl
				<< "【技能】" << endl
				<< f->displaySkills()
				<< "----------------------------------------" << endl
				<< "可使用技能點數 ： " << f->getSkill_Point() << " 點" << endl
				<< "----------------------------------------" << endl;

			cout << "1. 學習新技能\n2. 升級技能\n3. 離開技能面板\n請選擇操作: ";
			int selection = 0;
			cin >> selection;

			if (cin.fail()) {
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "無效輸入，請輸入數字。" << endl;
				Sleep(1500);
				system("cls");
				continue;
			}

			if (selection == 1) {
				cout << "【可學習技能清單】" << endl;
				CGlobalInfo::skillManager->showAllSkills();

				cout << "請輸入要學習的技能ID: ";
				int skillID;
				cin >> skillID;

				if (CGlobalInfo::skillManager->getSkill(skillID)) {
					f->learnSkill(skillID);
				}
				else {
					cout << "技能 ID 無效或不存在！" << endl;
				}
			}
			else if (selection == 2) {
				cout << "請輸入要升級的技能序號: ";
				int skillID;
				cin >> skillID;

				f->upgradeSkill(skillID);
			}
			else if (selection == 3) {
				cout << f->getname() << " 關上技能面板" << endl;
				break;
			}
			else {
				cout << "無此選項存在" << endl;
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

/* 寵物面板 */
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
			cout << f->getname() << " 開啟寵物面板" << endl;
			cout << "----------------------------------------" << endl;

			cout << usr->getname() << "'s 寵物面板" << setw(6) << "Lv" << f->getLevel() << setw(6) << f->getXP() << "/1000" << endl;

			cout << "【當前寵物】" << endl;
			cout << f->getCurrentPet_String();

			cout << "----------------------------------------" << endl
				<< "【擁有寵物】" << endl;
			f->showPets();
			cout << "----------------------------------------" << endl;

			int selection = 0;
			cout << "需要更換寵物嗎 (0代表取消寵物 -1代表離開)" << endl;
			cin >> selection;

			if (cin.fail()) {
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "無效輸入，請輸入數字。" << endl;
				Sleep(1500);
				system("cls");
				continue;
			}

			if (selection == -1) {
				cout << f->getname() << " 關上寵物面板" << endl;
				break;
			}

			if (!f->setCurrentPet(selection - 1)) {
				cout << "無此選項存在" << endl;
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

/* 開啟商店 */
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
		cerr << "此地點無商店" << endl;
		return 0;
	}
	CLifeEntity* usr = CGlobalInfo::user->get_user();
	assert(usr);

	CStore* store = storeIt->second;
	assert(store);

	cout << "歡迎來到 " << store->getName() << " !!" << endl;

	cout << usr->getname() << ", 你擁有 $" << ((CFighter*)usr)->getMoney() << endl;
	store->displayStoreInfo();

	int selection = 0;
	cout << "需要購買什麼物品 (0代表不需要)" << endl;
	cin >> selection;

	while (selection > 0) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "無效輸入，請輸入數字。" << endl;
			Sleep(1500);
			system("cls");
			continue;
		}

		if (selection > 0 && selection <= store->getItemCount()) {

			pair<CItem*, int> itemPair = store->getItemById(selection);
			CItem* item = itemPair.first;
			int itemPrice = itemPair.second;

			if (!item) {
				cout << "無此選項存在" << endl;
				continue;
			}

			if (((CFighter*)usr)->getMoney() >= itemPrice) {
				cout << "購買成功: " << item->getName() << "，花費 $" << itemPrice << endl;
				((CFighter*)usr)->reduceMoney(itemPrice);
				((CFighter*)usr)->buyItem(item);  // 加入物品至玩家
			}
			else {
				cout << "金額不足，無法購買 " << item->getName() << endl;
			}
		}

		cout << "需要購買什麼物品 (0代表不需要)" << endl;
		cin >> selection;
	}

	cout << usr->getname() << " 離開商店" << endl;
	
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
		cout << "沒有 command_list.txt 檔案！\n";
		exit(0);
	}

	string line;
	while (getline(fin, line)) { // 正確的檔案讀取方式
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
	cout << "【系統提示】 全地圖怪物將重新生成！" << endl;
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
	if (tokens.size () == 0){ // 未輸入
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

