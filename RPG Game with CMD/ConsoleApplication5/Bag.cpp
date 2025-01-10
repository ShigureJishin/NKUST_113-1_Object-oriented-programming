#include <iostream>
#include <sstream>
#include "Bag.h"
#include "Item.h"
#include "def.h"
#include "food.h"
#include "weapon.h"
#include "boots.h"
#include "chestplate.h"
#include "Helmet.h"
#include "GlobalInfo.h"
#include "ItemData.h"

using namespace std;

CBagEntry::CBagEntry(CItem *in_item, int in_num){
	itm = in_item; 
	number = in_num;
}

CBag::CBag (){
	LIST_INIT(&listhead);	
}

CBag::~CBag (){
	CBagEntry* ne = listhead.lh_first;
	CBagEntry* tmp = NULL;
	while (ne){
		tmp = ne->next_link.le_next;
		LIST_REMOVE (ne, next_link);
		ne = tmp;
	}
}

void CBag::item_insert (CItem *in_item){
	CBagEntry* new_entry = new CBagEntry (in_item);
	LIST_INSERT_HEAD(&listhead, new_entry, next_link);
}

CBagEntry* CBag::item_lookup (int type, int id){
	CBagEntry* ne = listhead.lh_first;
	for (; ne; ne = ne->next_link.le_next){
		if (ne->itm->isA() == type && ne->itm->getID () == id)
			break;
	}
	return ne;
}

CBagEntry* CBag::item_lookup (int no){
	CBagEntry* ne = listhead.lh_first;
	int countnum = 1;
	for (; ne; ne = ne->next_link.le_next){
		if (no == countnum){						
			break;
		}
		countnum++;
	}
	return ne;
}

void CBag::item_delete (CBagEntry* be){
	LIST_REMOVE (be, next_link);
}

int CBag::showAllItems (){
	CBagEntry* ne = listhead.lh_first;
	CItem *tmp;
	int countnum = 0;
	if (ne)
		cout << "背包內容如下所示：" << endl;
	for (; ne; ne = ne->next_link.le_next){
		tmp = ne->itm;
		cout << ++countnum << ". " << tmp->getName () << ", 數量-> " << ne->number << endl;
	}	
	return countnum;
}

string CBag::serializeItems() {
	stringstream ss;
	ss.clear();

	CBagEntry* ne = listhead.lh_first;
	CItem* tmp;

	int countnum = 0;
	if (ne){
		for (; ne; ne = ne->next_link.le_next) {
			tmp = ne->itm;
			ss << tmp->getID() << "," << tmp->getName() << "," << ne->number << "," << static_cast<int>(tmp->getType()) << ";";
		}

		return ss.str();
	}
	else
		return "null";
}

void CBag::deserializeItems(string item) {
	stringstream BagItem(item);
	int ID, ItemCount, Category;
	string Name;
	char comm;

	BagItem >> ID >> comm;
	getline(BagItem, Name, ',');
	BagItem >> ItemCount >> comm >> Category;

	CItem* newItem = nullptr;
	int bouns = CGlobalInfo::itm_data->getBouns(static_cast<ItemType>(Category), ID);

	// 根據類型創建具體物品
	if (Category == Weapon) {
		CWeapon *tmp = CGlobalInfo::itm_data->findWeaponByID(ID);
		if (tmp)
			newItem = new CWeapon(Name, 0, 0, ID, bouns, tmp->getProfession() );
		else 
			newItem = new CWeapon(Name, 0, 0, ID, bouns, Profession::All);
	}
	else if (Category == Boots) {
		newItem = new CBoots(Name, 0, 0, ID, bouns);
	}
	else if (Category == Helmet) {
		newItem = new CHelmet(Name, 0, 0, ID, bouns);
	}
	else if (Category == Chestplate) {
		newItem = new CChestplate(Name, 0, 0, ID, bouns);
	}
	else if (Category == Food) {
		newItem = new CFood(Name, 0, 0, ID, bouns);
	}
	else{
		cout << "未知物品類型，ID：" << ID << endl;
		return;
	}

	// 添加物品到背包
	if (newItem) {
		CBagEntry* existingEntry = item_lookup(newItem->isA(), ID);
		if (existingEntry) {
			existingEntry->addNum(ItemCount); // 增加數量
		}
		else {
			CBagEntry* newEntry = new CBagEntry(newItem, ItemCount);
			item_insert(newItem);           // 插入新物品到背包
		}
	}
}