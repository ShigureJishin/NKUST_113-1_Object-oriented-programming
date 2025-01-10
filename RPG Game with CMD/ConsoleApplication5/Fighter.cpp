#include <iostream>
#include <sstream>
#include <iomanip>
#include "Fighter.h"
#include "Monster.h"
#include "food.h"
#include "Bag.h"
#include "Skill.h"
#include "Pet.h"
#include "def.h"
#include "GlobalInfo.h"
#include "ArmorEffect.h"
#include "MapData.h"
#include "SkillData.h"
#include "ItemData.h"

using namespace std;

CFighter::CFighter (string inName , int initHP, int initSP, int initMP, int initLucky, int initDefense, int in_city, Profession inProfession) {
	/*if (initHP == 0 && initSP == 0 && initLucky == 0) {
		initHP = 1 + rand() % (FIGHTER_MAXHP);
		initSP = 1 + rand() % (FIGHTER_MAXSP);
		initMP = 100 + rand() % (FIGHTER_RANGEMP);
		initLucky = 1 + rand() % (FIGHTER_MAXLUCKY);
		initDefense = 1 + rand() % (FIGHTER_MAXDEFENSE);
		
	}*/

	setname(inName);
	switch (inProfession) {
	case Profession::Berserker:
		initSP = 25;
		initHP = 150;
		initMP = 30;
		initDefense = 10;
		initLucky = 15 + rand()%10;
		break;
	case Profession::Mage:
		initSP = 15;
		initHP = 80;
		initMP = 150;
		initDefense = 5;
		initLucky = 10 + rand() % 10;
		break;
	case Profession::Tank:
		initSP = 10;
		initHP = 200;
		initMP = 50;
		initDefense = 25;
		initLucky = 5 + rand() % 10;
		break;
	}
	profession = inProfession; //當前職業
	XP = 0;		  // 經驗
	Level = 1;	  // 等級
	Money = 1000; // 啟動資金
	Property_Point = 0; // 屬性點數
	Skill_Point = 0;    // 技能點數

	setInitSPHP (initHP,initSP, initMP);
	Lucky = initLucky;
	Defense = initDefense;
	cur_city = in_city;
	bag = new CBag ();
	currentPet = nullptr;
	currentSetBonus = nullptr;
	cout << "One " << returnProfessionName(inProfession)  << " is created with (HP, ATK, Defense) = (" << initHP << ", " << initSP << ", " << initDefense << ")" << endl;
}

CFighter::CFighter(string inName, int initMAXHP, int initHP, int initSP, int initMAXSP, int initMP, int initMAXMP, int initLucky, int initDefense, int inMoney, int inXP, int inLevel, int in_city, Profession inProfession, int point1, int point2) {
	setname(inName);
	setInitSPHP(initMAXHP, initMAXSP, initMAXMP);
	setHP(initHP);
	setMP(initMP);
	profession = inProfession;
	XP = inXP;			// 經驗
	Level = inLevel;	// 等級
	Money = inMoney;	// 啟動資金
	
	Lucky = initLucky;
	Defense = initDefense;
	cur_city = in_city;

	Property_Point = point1; // 屬性點數
	Skill_Point = point2;    // 技能點數
	bag = new CBag();
	currentPet = NULL;
	currentSetBonus = nullptr;
}

CFighter::~CFighter (){
	if (bag)
		delete bag;
}

int CFighter::getLucky (){
	return Lucky;
}

void CFighter::addLucky(int inLucky) {
	Lucky += inLucky;
}

void CFighter::addMoney(int inMoney) {
	Money += inMoney;

	cout << this->getname() << "獲得 $"<< inMoney <<"，目前擁有 $" << Money << endl;
}

void CFighter::reduceMoney(int inMoney) {
	Money -= inMoney;
}

int CFighter::getMoney() {
	return Money;
}

void CFighter::addXP(int inXP) {
	XP += inXP;

	if (XP >= 1000) {
		XP -= 1000;
		Level += 1;
		Property_Point += FIGHTER_PropertyPOINT_PERLEVELUP; // 屬性點數
		Skill_Point += FIGHTER_SkillPOINT_PERLEVELUP;    // 技能點數
		cout << "恭喜 " << this->getname() << " 升級 1 等，目前等級 Lv" << Level << endl;
	}
}

void CFighter::addDefense(int inDefense) {
	Defense += inDefense;
}

void CFighter::delDefense(int inDefense) {
	Defense -= inDefense;
}

int CFighter::physicaldamage (){ // 基礎攻擊 /*+ 隨機額外傷害*/
	//return (rand () % getSP ());
	return getSP();
}

int CFighter::attack (CLifeEntity *l){
	int damage = 0;

	vector<CSkill*> usableSkills;

	// 檢查所有技能，將可用的技能放進 usableSkills 列表
	for (auto& skill : Skills) {
		if (this->getMP() >= skill.getMPCost()) {
			usableSkills.push_back(&skill);
		}
	}
	

	char selection;
	cout << "0:普攻 1:技能攻擊" << endl;
	cin >> selection;

	// 如果有可用的技能，隨機選擇一個使用
	if (Skills.empty() && selection == '1')
		cout << "攻擊提示: 沒有技能，還選甚麼技能，幫你自動普攻拉！" << endl;
	else if (usableSkills.empty() && selection == '1') {
		cout << "攻擊提示: 沒有 MP，還不趕快去補，幫你自動普攻拉！" << endl;
	}
	else if (!usableSkills.empty() && selection == '1') {
		int randomIndex = rand() % usableSkills.size();  // 隨機選擇技能
		CSkill* chosenSkill = usableSkills[randomIndex];

		// 使用技能，消耗 MP
		this->delMP(chosenSkill->getMPCost());

		// 計算技能傷害
		damage = chosenSkill->getDamage();
		if (damage > l->getHP())
			damage = l->getHP();

		// 扣除敵方血量
		l->gethurt(damage);

		cout << this->getname() << " 使用技能「" << chosenSkill->getName()
			<< "」，造成 " << l->getname() << " " << damage << " 點傷害" << endl;

		return (damage > 0 ? damage : 0);
	}

	damage = physicaldamage () - l->defense (l); 
	if (damage > l->getHP ())
		damage = l->getHP ();
	
	l->gethurt (damage);
	
	if (damage > 0){
		cout << this->getname () << " 猛力一揮，造成 " << l->getname () << " " << damage << " 血損失" <<endl;			
	} else {
		cout << this->getname () << " 猛力一揮，但是 " << l->getname () << " 強力一擋，因此沒有造成任何損失" <<endl;
	}
	return (damage > 0 ? damage : 0);
}

int CFighter::petAttack(CLifeEntity* l) {
	int damage = 0;

	if (currentPet) {
		damage = currentPet->attack(l);
		cout << "你的寵物 " << currentPet->getname() << " 攻擊了 " << l->getname() << "，造成 " << damage << " 血損失" << endl;
	}

	return (damage > 0 ? damage : 0);
}

int CFighter::defense (CLifeEntity *l){
	return getDefense();
}

void CFighter::captureItem (CItem *in_item){
	
	CBagEntry *entry = bag->item_lookup (in_item->isA(), in_item->getID ());
	if (!entry)
		bag->item_insert (in_item);
	else
		entry->addNum (1);	
	cout << this->getname () << " 從地上撿起 " << in_item->getName () << endl;
}

void CFighter::buyItem(CItem* in_item) {

	CBagEntry* entry = bag->item_lookup(in_item->isA(), in_item->getID());
	if (!entry)
		bag->item_insert(in_item);
	else
		entry->addNum(1);
	cout << this->getname() << " 從商店買入 " << in_item->getName() << endl;
}

int CFighter::showAllBagItems (){	
	return bag->showAllItems ();	
}

bool CFighter::useBagItems (int no){
	CBagEntry* ne = bag->item_lookup (no);
	if (!ne){		
		return false;
	} 
	if (ne->itm->isA () == eweapon){
#if 0
		cout << static_cast<int>(((CWeapon*)ne->itm)->getProfession()) << static_cast<int>(profession);
#endif
		if (((CWeapon*)ne->itm)->getProfession() != Profession::All && ((CWeapon*)ne->itm)->getProfession() != profession) {
			cout << "裝備失敗: 此武器僅限於 " << returnProfessionName(((CWeapon*)ne->itm)->getProfession()) << " 使用。" << endl;
			return true;
		}

		CWeapon *cur_weapon = this->getWeapon ();
		if (cur_weapon != NULL){
			CItem *weapon_item = (CItem *) cur_weapon;
			CBagEntry *entry = bag->item_lookup (weapon_item->isA(), weapon_item->getID ());
			if (!entry)
				bag->item_insert (weapon_item);
			else
				entry->addNum (1);	
			cout << this->getname () << " 將手上武器 " << weapon_item->getName () << " 放回背包中" << endl;
			weapon_item->UnUsed (this);			
		}
		this->setWeapon ((CWeapon *) ne->itm);				
	}

	if (ne->itm->isA() == echestplate) {
		CChestplate* cur_chestplate = this->getChestplate();
		if (cur_chestplate != NULL) {
			CItem* chestplate_item = (CItem*)cur_chestplate;
			CBagEntry* entry = bag->item_lookup(chestplate_item->isA(), chestplate_item->getID());
			if (!entry)
				bag->item_insert(chestplate_item);
			else
				entry->addNum(1);
			cout << this->getname() << " 將身上 " << chestplate_item->getName() << " 卸下，並收回背包中" << endl;
			chestplate_item->UnUsed(this);
		}
		this->setChestplate((CChestplate*)ne->itm);
	}
	if (ne->itm->isA() == ehelmet) {
		CHelmet* cur_helmet = this->getHelmet();
		if (cur_helmet != NULL) {
			CItem* helmet_item = (CItem*)cur_helmet;
			CBagEntry* entry = bag->item_lookup(helmet_item->isA(), helmet_item->getID());
			if (!entry)
				bag->item_insert(helmet_item);
			else
				entry->addNum(1);
			cout << this->getname() << " 將身上 " << helmet_item->getName() << " 卸下，並收回背包中" << endl;
			helmet_item->UnUsed(this);
		}
		this->setHelmet((CHelmet*)ne->itm);
	}

	if (ne->itm->isA() == eboots) {
		CBoots* cur_boots = this->getBoots();
		if (cur_boots != NULL) {
			CItem* boots_item = (CItem*)cur_boots;
			CBagEntry* entry = bag->item_lookup(boots_item->isA(), boots_item->getID());
			if (!entry)
				bag->item_insert(boots_item);
			else
				entry->addNum(1);
			cout << this->getname() << " 將身上 " << boots_item->getName() << " 卸下，並收回背包中" << endl;
			boots_item->UnUsed(this);
		}
		this->setBoots((CBoots*)ne->itm);
	}

	ne->itm->beUsed (this);
	ne->deleteNum ();
	if (ne->getNum () == 0){
		bag->item_delete (ne);
	}
	this->applySetBonus();
	this->showAllBagItems ();
	return true;
}

int CFighter::isA (){
	return efighter;
}

int CFighter::goto_next_city (int next_dir){
	int next_city = CGlobalInfo::map_data->next_city (cur_city, next_dir);	
	if (next_city){
		cur_city = next_city;
		return cur_city;
	}
	return 0;
}

int CFighter::moveto_city(string next_city_name) {
	CPlace *next_city = CGlobalInfo::map_data->get_place_by_name(next_city_name);

	if (next_city) {
		cur_city = CGlobalInfo::map_data->get_id_by_place(next_city);
		return cur_city;
	}
	return 0;
}

int CFighter::get_current_city (){
	return cur_city;	
}

bool CFighter::addProperty(const int no) {

	switch (no) {
	case 1: // HP
		if (Property_Point > 0) {
			addMAXHP(10);
			Property_Point--;
			cout << "【提示】 已耗費 1 點屬性點，提升 10 HP" << endl;
			return true;
		}
		break;
	case 2: // MP
		if (Property_Point > 0) {
			addMAXMP(20);
			Property_Point--;
			cout << "【提示】 已耗費 1 點屬性點，提升 20 MP" << endl;
			return true;
		}
		break;
	case 3: // ATK
		if (Property_Point > 0) {
			addSP(5);
			Property_Point--;
			cout << "【提示】 已耗費 1 點屬性點，提升 5 點攻擊" << endl;
			return true;
		}
		break;
	case 4: // Defense
		if (Property_Point > 0) {
			addDefense(10);
			Property_Point--;
			cout << "【提示】 已耗費 1 點屬性點，提升 10 點防禦" << endl;
			return true;
		}
		break;
	case 5: // Lucky
		if (Lucky == 100) {
			cout << "幸運值已滿！" << endl;
			return true;
		}
		if (Property_Point > 1) {
			addLucky(1);
			Property_Point -= 2;
			cout << "【提示】 已耗費 2 點屬性點，提升 1 幸運" << endl;
			return true;
		}
		break;

	default:
		break;
	}

	return false;
}


string CFighter::displaySkills() const {
	stringstream ss;
	int index = 1;
	if (Skills.empty()) {
		ss << "尚未學會任何技能！" << endl;
	}
	else {
		for (CSkill skill : Skills) {
			ss << index << "." << " " << "Lv" << skill.getLevel() << " " << skill.getName()
				<< ", 消耗MP: " << skill.getMPCost()
				<< ", 傷害: " << skill.getDamage() << endl;
			index++;
		}
	}
	return ss.str();
}

void CFighter::learnSkill(int skillID) {
	// 透過技能管理器獲取技能
	CSkill* skill = CGlobalInfo::skillManager->getSkill(skillID);
	if (!skill) {
		cout << "無效的技能 ID: " << skillID << endl;
		return;
	}

	if (skill->getProfession() != Profession::All && skill->getProfession() != profession) {
		cout << "該技能不屬於此職業，該技能屬於 " << returnProfessionName(skill->getProfession()) << " 。" << endl;
		return;
	}

	// 檢查技能點數
	if (Skill_Point <= 0) {
		cout << "技能點數不足，無法學習技能！" << endl;
		return;
	}

	// 檢查是否已經學會該技能
	for (const auto& learnedSkill : Skills) {
		if (learnedSkill.getName() == skill->getName()) {
			cout << "你已經學會該技能: " << skill->getName() << endl;
			return;
		}
	}

	Skill_Point -= 1;
	Skills.push_back(*skill); // 複製技能物件
	cout << "成功學會技能: " << skill->getName() << endl;
}

void CFighter::upgradeSkill(int skillID) {
	if (skillID < 1 || skillID > Skills.size()) {
		cout << "無效的技能序號！" << endl;
		return;
	}

	if (Skill_Point <= 0) {
		cout << "技能點數不足，無法升級技能！" << endl;
		return;
	}

	int skillIndex = skillID - 1;
	// 升級指定技能
	if (Skills[skillIndex].getLevel() < 10){
		Skills[skillIndex].upgrade();
		Skill_Point--;
		cout << "成功升級技能: " << Skills[skillIndex].getName()
			<< "，當前等級: " << Skills[skillIndex].getLevel() << endl;
	}
	else {
		cout << "技能: " << Skills[skillIndex].getName() << " 已達最高等級"
			<< "，當前等級: " << Skills[skillIndex].getLevel() << endl;
	}
}

void CFighter::addPet(CPet *pet) {
	Pets.push_back(pet);
}

bool CFighter::setCurrentPet(const int indexPet) {
	if (indexPet >= 0 && indexPet < Pets.size()) {  // 檢查索引範圍
		if (currentPet)
			Pets.push_back(currentPet);

		currentPet = Pets[indexPet];
		Pets.erase(Pets.begin()+indexPet);
		cout << "你選擇了寵物: " << currentPet->getname() << endl;
		return true;
	}
	else if (indexPet == -1) {  // 特殊處理，取消當前寵物
		if (currentPet) {
			Pets.push_back(currentPet);
			currentPet = nullptr;
			cout << "你取消了當前寵物。" << endl;
			return true;
		}
		else {
			cout << "當前寵物沒有任何寵物。" << endl;
			return true;
		}
	}
	else {
		return false;
	}
}


string CFighter::getCurrentPet_String() const {
	stringstream msg;

	if (currentPet) {
		msg << "Lv " << currentPet->getLevel() << " " << currentPet->getname() << " ATK: " << currentPet->getSP() << "," << setw(3) << " " << currentPet->getXP() << "/1000" << endl;
	}
	else {
		msg << "尚未裝備寵物！";
	}

	return msg.str();
}

void CFighter::showPets() const {
	if (Pets.empty()) {
		cout << "你目前沒有任何寵物！" << endl;
	}
	else {
		int index = 1;
		for (const auto& pet : Pets) {
			cout << index << ".Lv " << pet->getLevel() << " " << pet->getname() << ", ATK: " << pet->getSP() << "," << setw(3) << " " << pet->getXP() <<"/1000" << endl;
			index++;
		}
	}
}

string CFighter::getProfession_String() const {
	switch (profession) {
	case Profession::Berserker: return "狂戰士 (Berserker)";
	case Profession::Mage: return "星詠者 (Mage)";
	case Profession::Tank: return "鋼衛者 (Tank)";
	default: return "未知職業";
	}
}

void CFighter::changeProfession(Profession newProfession) {
	if (profession == newProfession) {
		cout << "你已經是該職業：" << static_cast<int>(newProfession) << endl;
		return;
	}

	profession = newProfession;

	switch (profession) {
	case Profession::Berserker:
		
		Lucky = 5;
		break;
	case Profession::Mage:
		
		Lucky = 10;
		break;
	case Profession::Tank:
		
		Defense = 25;
		Lucky = 3;
		break;
	}

	cout << "職業已更換為：" << static_cast<int>(profession) << endl;
}

void CFighter::applySetBonus() {
	// 確保 ArmorEffectManager 存在
	CArmorEffectData* manager = CGlobalInfo::armor_effect_data;

	// 如果已經有激活的套裝效果，先移除它
	if (currentSetBonus) {
		delSP(currentSetBonus->atkBonus);
		delDefense(currentSetBonus->defenseBonus);
		cout << "裝備提示: 移除套裝效果"
			<< " ATK: +" << currentSetBonus->atkBonus
			<< ", Defense: +" << currentSetBonus->defenseBonus << endl;
		currentSetBonus = nullptr;
	}

	// 檢查裝備是否完整
	if (!getHelmet() || !getBoots() || !getChestplate()) {
		return;
	}

	// 嘗試取得新的套裝效果
	const ArmorEffect* effect = manager->getEffect(getHelmet()->getID(), getBoots()->getID(), getChestplate()->getID());
	if (!effect) {
		return;
	}

	// 應用新的套裝效果
	addSP(effect->atkBonus);
	addDefense(effect->defenseBonus);
	currentSetBonus = effect; // 記錄當前激活的套裝效果
	cout << "裝備提示: 啟用套裝效果"
		<< " ATK: " << effect->atkBonus
		<< ", Defense: " << effect->defenseBonus << endl;
}

/* 存檔用 */
string CFighter::serializeSkills() const {
	stringstream ss;
	if (Skills.empty()) {
		return "null";
	}
	for (const auto& skill : Skills) {
		ss << skill.getID() << "," << skill.getName() << "," << skill.getMPCost() << "," << skill.getDamage() << "," << skill.getLevel() << "," << static_cast<int>(skill.getProfession()) << ";";
	}
	return ss.str();
}


string CFighter::serializeCurrentPet() const {
	stringstream ss;

	// 序列化當前寵物
	CPet* pet = this->getCurrentPet();
	if (pet) {
		ss << pet->getname() << "," << pet->getLevel() << "," << pet->getHP() << "," << pet->getSP() << "," << pet->getXP();
	}
	else {
		ss << "null;";
	}

	return ss.str();
}


string CFighter::serializePets() const {
	stringstream ss;

	if (Pets.empty()) {
		return "null";
	}
	for (const auto& pet : Pets) {
		ss << pet->getname() << "," << pet->getLevel() << "," << pet->getHP() << "," << pet->getSP() << "," << pet->getXP();
	}
	return ss.str();
}

string CFighter::serializeArror() const {
	stringstream ss;
	CLifeEntity* Self = ((CLifeEntity*)this);
	// 序列化武器
	CWeapon* weapon = Self->getWeapon();
	if (weapon) {
		ss << "weapon:"
			<< weapon->getID() << "," 
			<< weapon->getName() << ","
			<< weapon->getattackbonus() << ";";
	}
	else {
		ss << "weapon:null;";
	}

	// 序列化胸甲
	CChestplate* chestplate = Self->getChestplate();
	if (chestplate) {
		ss << "chestplate:" << chestplate->getID() << "," 
			<< chestplate->getName() << ","
			<< chestplate->getdefensebonus() << ";";
	}
	else {
		ss << "chestplate:null;";
	}

	// 序列化頭盔
	CHelmet* helmet = Self->getHelmet();
	if (helmet) {
		ss << "helmet:" << helmet->getID() << "," 
			<< helmet->getName() << ","
			<< helmet->getdefensebonus() << ";";
	}
	else {
		ss << "helmet:null;";
	}

	// 序列化靴子
	CBoots* boots = Self->getBoots();
	if (boots) {
		ss << "boots:" << boots->getID() << ","
			<< boots->getName() << ","
			<< boots->getdefensebonus() << ";";
	}
	else {
		ss << "boots:null;";
	}

	return ss.str();
}


string CFighter::serializeBag() const {
	return bag ? bag->serializeItems() : "null";
}

/* 讀檔用 */
void CFighter::deserializeSkills(const string& data) {
	if (data == "null") {
		return;
	}

	Skills.clear();
	stringstream ss(data);
	string token;
	while (getline(ss, token, ';')) {
		if (!token.empty()) {
			stringstream skillStream(token);
			int ID;
			string name;
			int CostMP,  Damage, Level, JobType;
			char comma;

			skillStream >> ID >> comma; // 解析 ID
			getline(skillStream, name, ','); // 解析技能名稱
			skillStream >> CostMP >> comma >> Damage >> comma >> Level>> comma >> JobType; // 解析數值
			
			// 添加至技能列表
			Skills.push_back(CSkill(ID, name, CostMP, Damage, Level, JobType));
		}
	}
}

void CFighter::deserializePets(const string& data) {
	if (data == "null") {
		return;
	}

	Pets.clear();
	stringstream ss(data);
	string token;
	while (getline(ss, token, ';')) {
		if (!token.empty()) {
			stringstream petStream(token);
			string name;
			int level, hp, atk, XP;
			char comma;
			getline(petStream, name, ',');
			petStream >> level >> comma >> hp >> comma >> atk >> comma >> XP;
			Pets.push_back(new CPet(name, level, hp, atk, XP));
		}
	}
}

void CFighter::deserializeCurrentPet(const string& data) {
	if (data == "null") {
		return;
	}

	stringstream ss(data);
	string name;
	int level, hp, atk, XP;
	char comma;
	getline(ss, name, ',');
	ss >> level >> comma >> hp >> comma >> atk >> comma >> XP;
	currentPet = new CPet(name, level, hp, atk, XP);
}

void CFighter::deserializeBag(const string& data) {
	bag = new CBag();

	if (data == "null") {
		return;
	}

	stringstream ss(data);
	string token;

	while (getline(ss, token, ';')) {
		if (!token.empty()) {
			bag->deserializeItems(token);
		}
	}
}

void CFighter::deserializeArror(const string& data) {
	stringstream ss(data);
	string token;

	while (getline(ss, token, ';')) {
		if (token.empty()) continue;

		stringstream itemStream(token);
		string type, attributes;
		getline(itemStream, type, ':');
		getline(itemStream, attributes);

		if (attributes == "null") {
			// 裝備為空
			if (type == "weapon") setWeapon(nullptr);
			if (type == "chestplate") setChestplate(nullptr);
			if (type == "helmet") setHelmet(nullptr);
			if (type == "boots") setBoots(nullptr);
			continue;
		}

		stringstream attrStream(attributes);
		string name;
		char comm;
		int stat1, id;

		attrStream >> id >> comm;
		getline(attrStream, name, ',');
		attrStream >> stat1;

		CItemData * data= CGlobalInfo::itm_data;

		if (type == "weapon") {
			setWeapon(new CWeapon(name, 0, 0, id, stat1, data->findWeaponByID(id)->getProfession()));
		}
		else if (type == "chestplate") {
			setChestplate(new CChestplate(name, 0, 0, id, stat1));
		}
		else if (type == "helmet") {
			setHelmet(new CHelmet(name, 0, 0, id, stat1));
		}
		else if (type == "boots") {
			setBoots(new CBoots(name, 0, 0, id, stat1));
		}
	}

	this->applySetBonus();
}

void CFighter::getCurrentSet() const {
	if (!currentSetBonus) {
		return;
	}
	else {
		cout << "當前套裝效果: "
			<< " ATK Bonus: " << currentSetBonus->atkBonus
			<< ", Defense Bonus: " << currentSetBonus->defenseBonus
			<< endl;
	}
}