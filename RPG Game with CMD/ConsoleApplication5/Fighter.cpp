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
	profession = inProfession; //��e¾�~
	XP = 0;		  // �g��
	Level = 1;	  // ����
	Money = 1000; // �Ұʸ��
	Property_Point = 0; // �ݩ��I��
	Skill_Point = 0;    // �ޯ��I��

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
	XP = inXP;			// �g��
	Level = inLevel;	// ����
	Money = inMoney;	// �Ұʸ��
	
	Lucky = initLucky;
	Defense = initDefense;
	cur_city = in_city;

	Property_Point = point1; // �ݩ��I��
	Skill_Point = point2;    // �ޯ��I��
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

	cout << this->getname() << "��o $"<< inMoney <<"�A�ثe�֦� $" << Money << endl;
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
		Property_Point += FIGHTER_PropertyPOINT_PERLEVELUP; // �ݩ��I��
		Skill_Point += FIGHTER_SkillPOINT_PERLEVELUP;    // �ޯ��I��
		cout << "���� " << this->getname() << " �ɯ� 1 ���A�ثe���� Lv" << Level << endl;
	}
}

void CFighter::addDefense(int inDefense) {
	Defense += inDefense;
}

void CFighter::delDefense(int inDefense) {
	Defense -= inDefense;
}

int CFighter::physicaldamage (){ // ��¦���� /*+ �H���B�~�ˮ`*/
	//return (rand () % getSP ());
	return getSP();
}

int CFighter::attack (CLifeEntity *l){
	int damage = 0;

	vector<CSkill*> usableSkills;

	// �ˬd�Ҧ��ޯ�A�N�i�Ϊ��ޯ��i usableSkills �C��
	for (auto& skill : Skills) {
		if (this->getMP() >= skill.getMPCost()) {
			usableSkills.push_back(&skill);
		}
	}
	

	char selection;
	cout << "0:���� 1:�ޯ����" << endl;
	cin >> selection;

	// �p�G���i�Ϊ��ޯ�A�H����ܤ@�Өϥ�
	if (Skills.empty() && selection == '1')
		cout << "��������: �S���ޯ�A�ٿ�ƻ�ޯ�A���A�۰ʴ���ԡI" << endl;
	else if (usableSkills.empty() && selection == '1') {
		cout << "��������: �S�� MP�A�٤����֥h�ɡA���A�۰ʴ���ԡI" << endl;
	}
	else if (!usableSkills.empty() && selection == '1') {
		int randomIndex = rand() % usableSkills.size();  // �H����ܧޯ�
		CSkill* chosenSkill = usableSkills[randomIndex];

		// �ϥΧޯ�A���� MP
		this->delMP(chosenSkill->getMPCost());

		// �p��ޯ�ˮ`
		damage = chosenSkill->getDamage();
		if (damage > l->getHP())
			damage = l->getHP();

		// �����Ĥ��q
		l->gethurt(damage);

		cout << this->getname() << " �ϥΧޯ�u" << chosenSkill->getName()
			<< "�v�A�y�� " << l->getname() << " " << damage << " �I�ˮ`" << endl;

		return (damage > 0 ? damage : 0);
	}

	damage = physicaldamage () - l->defense (l); 
	if (damage > l->getHP ())
		damage = l->getHP ();
	
	l->gethurt (damage);
	
	if (damage > 0){
		cout << this->getname () << " �r�O�@���A�y�� " << l->getname () << " " << damage << " ��l��" <<endl;			
	} else {
		cout << this->getname () << " �r�O�@���A���O " << l->getname () << " �j�O�@�סA�]���S���y������l��" <<endl;
	}
	return (damage > 0 ? damage : 0);
}

int CFighter::petAttack(CLifeEntity* l) {
	int damage = 0;

	if (currentPet) {
		damage = currentPet->attack(l);
		cout << "�A���d�� " << currentPet->getname() << " �����F " << l->getname() << "�A�y�� " << damage << " ��l��" << endl;
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
	cout << this->getname () << " �q�a�W�߰_ " << in_item->getName () << endl;
}

void CFighter::buyItem(CItem* in_item) {

	CBagEntry* entry = bag->item_lookup(in_item->isA(), in_item->getID());
	if (!entry)
		bag->item_insert(in_item);
	else
		entry->addNum(1);
	cout << this->getname() << " �q�ө��R�J " << in_item->getName() << endl;
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
			cout << "�˳ƥ���: ���Z���ȭ��� " << returnProfessionName(((CWeapon*)ne->itm)->getProfession()) << " �ϥΡC" << endl;
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
			cout << this->getname () << " �N��W�Z�� " << weapon_item->getName () << " ��^�I�]��" << endl;
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
			cout << this->getname() << " �N���W " << chestplate_item->getName() << " ���U�A�æ��^�I�]��" << endl;
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
			cout << this->getname() << " �N���W " << helmet_item->getName() << " ���U�A�æ��^�I�]��" << endl;
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
			cout << this->getname() << " �N���W " << boots_item->getName() << " ���U�A�æ��^�I�]��" << endl;
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
			cout << "�i���ܡj �w�ӶO 1 �I�ݩ��I�A���� 10 HP" << endl;
			return true;
		}
		break;
	case 2: // MP
		if (Property_Point > 0) {
			addMAXMP(20);
			Property_Point--;
			cout << "�i���ܡj �w�ӶO 1 �I�ݩ��I�A���� 20 MP" << endl;
			return true;
		}
		break;
	case 3: // ATK
		if (Property_Point > 0) {
			addSP(5);
			Property_Point--;
			cout << "�i���ܡj �w�ӶO 1 �I�ݩ��I�A���� 5 �I����" << endl;
			return true;
		}
		break;
	case 4: // Defense
		if (Property_Point > 0) {
			addDefense(10);
			Property_Point--;
			cout << "�i���ܡj �w�ӶO 1 �I�ݩ��I�A���� 10 �I���m" << endl;
			return true;
		}
		break;
	case 5: // Lucky
		if (Lucky == 100) {
			cout << "���B�Ȥw���I" << endl;
			return true;
		}
		if (Property_Point > 1) {
			addLucky(1);
			Property_Point -= 2;
			cout << "�i���ܡj �w�ӶO 2 �I�ݩ��I�A���� 1 ���B" << endl;
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
		ss << "�|���Ƿ|����ޯ�I" << endl;
	}
	else {
		for (CSkill skill : Skills) {
			ss << index << "." << " " << "Lv" << skill.getLevel() << " " << skill.getName()
				<< ", ����MP: " << skill.getMPCost()
				<< ", �ˮ`: " << skill.getDamage() << endl;
			index++;
		}
	}
	return ss.str();
}

void CFighter::learnSkill(int skillID) {
	// �z�L�ޯ�޲z������ޯ�
	CSkill* skill = CGlobalInfo::skillManager->getSkill(skillID);
	if (!skill) {
		cout << "�L�Ī��ޯ� ID: " << skillID << endl;
		return;
	}

	if (skill->getProfession() != Profession::All && skill->getProfession() != profession) {
		cout << "�ӧޯण�ݩ�¾�~�A�ӧޯ��ݩ� " << returnProfessionName(skill->getProfession()) << " �C" << endl;
		return;
	}

	// �ˬd�ޯ��I��
	if (Skill_Point <= 0) {
		cout << "�ޯ��I�Ƥ����A�L�k�ǲߧޯ�I" << endl;
		return;
	}

	// �ˬd�O�_�w�g�Ƿ|�ӧޯ�
	for (const auto& learnedSkill : Skills) {
		if (learnedSkill.getName() == skill->getName()) {
			cout << "�A�w�g�Ƿ|�ӧޯ�: " << skill->getName() << endl;
			return;
		}
	}

	Skill_Point -= 1;
	Skills.push_back(*skill); // �ƻs�ޯફ��
	cout << "���\�Ƿ|�ޯ�: " << skill->getName() << endl;
}

void CFighter::upgradeSkill(int skillID) {
	if (skillID < 1 || skillID > Skills.size()) {
		cout << "�L�Ī��ޯ�Ǹ��I" << endl;
		return;
	}

	if (Skill_Point <= 0) {
		cout << "�ޯ��I�Ƥ����A�L�k�ɯŧޯ�I" << endl;
		return;
	}

	int skillIndex = skillID - 1;
	// �ɯū��w�ޯ�
	if (Skills[skillIndex].getLevel() < 10){
		Skills[skillIndex].upgrade();
		Skill_Point--;
		cout << "���\�ɯŧޯ�: " << Skills[skillIndex].getName()
			<< "�A��e����: " << Skills[skillIndex].getLevel() << endl;
	}
	else {
		cout << "�ޯ�: " << Skills[skillIndex].getName() << " �w�F�̰�����"
			<< "�A��e����: " << Skills[skillIndex].getLevel() << endl;
	}
}

void CFighter::addPet(CPet *pet) {
	Pets.push_back(pet);
}

bool CFighter::setCurrentPet(const int indexPet) {
	if (indexPet >= 0 && indexPet < Pets.size()) {  // �ˬd���޽d��
		if (currentPet)
			Pets.push_back(currentPet);

		currentPet = Pets[indexPet];
		Pets.erase(Pets.begin()+indexPet);
		cout << "�A��ܤF�d��: " << currentPet->getname() << endl;
		return true;
	}
	else if (indexPet == -1) {  // �S��B�z�A������e�d��
		if (currentPet) {
			Pets.push_back(currentPet);
			currentPet = nullptr;
			cout << "�A�����F��e�d���C" << endl;
			return true;
		}
		else {
			cout << "��e�d���S�������d���C" << endl;
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
		msg << "�|���˳��d���I";
	}

	return msg.str();
}

void CFighter::showPets() const {
	if (Pets.empty()) {
		cout << "�A�ثe�S�������d���I" << endl;
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
	case Profession::Berserker: return "�g�Ԥh (Berserker)";
	case Profession::Mage: return "�P���� (Mage)";
	case Profession::Tank: return "���ê� (Tank)";
	default: return "����¾�~";
	}
}

void CFighter::changeProfession(Profession newProfession) {
	if (profession == newProfession) {
		cout << "�A�w�g�O��¾�~�G" << static_cast<int>(newProfession) << endl;
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

	cout << "¾�~�w�󴫬��G" << static_cast<int>(profession) << endl;
}

void CFighter::applySetBonus() {
	// �T�O ArmorEffectManager �s�b
	CArmorEffectData* manager = CGlobalInfo::armor_effect_data;

	// �p�G�w�g���E�����M�ˮĪG�A��������
	if (currentSetBonus) {
		delSP(currentSetBonus->atkBonus);
		delDefense(currentSetBonus->defenseBonus);
		cout << "�˳ƴ���: �����M�ˮĪG"
			<< " ATK: +" << currentSetBonus->atkBonus
			<< ", Defense: +" << currentSetBonus->defenseBonus << endl;
		currentSetBonus = nullptr;
	}

	// �ˬd�˳ƬO�_����
	if (!getHelmet() || !getBoots() || !getChestplate()) {
		return;
	}

	// ���ը��o�s���M�ˮĪG
	const ArmorEffect* effect = manager->getEffect(getHelmet()->getID(), getBoots()->getID(), getChestplate()->getID());
	if (!effect) {
		return;
	}

	// ���ηs���M�ˮĪG
	addSP(effect->atkBonus);
	addDefense(effect->defenseBonus);
	currentSetBonus = effect; // �O����e�E�����M�ˮĪG
	cout << "�˳ƴ���: �ҥήM�ˮĪG"
		<< " ATK: " << effect->atkBonus
		<< ", Defense: " << effect->defenseBonus << endl;
}

/* �s�ɥ� */
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

	// �ǦC�Ʒ�e�d��
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
	// �ǦC�ƪZ��
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

	// �ǦC�Ưݥ�
	CChestplate* chestplate = Self->getChestplate();
	if (chestplate) {
		ss << "chestplate:" << chestplate->getID() << "," 
			<< chestplate->getName() << ","
			<< chestplate->getdefensebonus() << ";";
	}
	else {
		ss << "chestplate:null;";
	}

	// �ǦC���Y��
	CHelmet* helmet = Self->getHelmet();
	if (helmet) {
		ss << "helmet:" << helmet->getID() << "," 
			<< helmet->getName() << ","
			<< helmet->getdefensebonus() << ";";
	}
	else {
		ss << "helmet:null;";
	}

	// �ǦC�ƹu�l
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

/* Ū�ɥ� */
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

			skillStream >> ID >> comma; // �ѪR ID
			getline(skillStream, name, ','); // �ѪR�ޯ�W��
			skillStream >> CostMP >> comma >> Damage >> comma >> Level>> comma >> JobType; // �ѪR�ƭ�
			
			// �K�[�ܧޯ�C��
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
			// �˳Ƭ���
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
		cout << "��e�M�ˮĪG: "
			<< " ATK Bonus: " << currentSetBonus->atkBonus
			<< ", Defense Bonus: " << currentSetBonus->defenseBonus
			<< endl;
	}
}