#include <iostream>
#include <fstream>
#include <cassert>
#include "Store.h"
#include "Place.h"
#include "MapData.h"
#include "MonsterData.h"
#include "GlobalInfo.h"
#include "weapon.h"
#include "food.h"
#include "helmet.h"
#include "chestplate.h"
#include "boots.h"
#include "potion.h"
#include "ItemData.h"
#include "def.h"

using namespace std;

CStore::CStore(string filename) {
	ifstream fin(filename);
	if (!fin) {
		cout << "讀檔失敗: " << filename << endl;
		return;
	}
    CGlobalInfo::itm_data->Initialize();

    fin >> name >> itemCount; // 讀取商店名稱和販賣物品種類數

    for (int i = 0; i < itemCount; ++i) {
        int id, price, bouns;
        string itemName, itemType;
        fin >> id >> itemName >> price >> bouns >> itemType;

        CItem* newItem = NULL;
        if (itemType == "weapon") {
            CWeapon* tmp = CGlobalInfo::itm_data->findWeaponByID(id);

            if (tmp)
                newItem = new CWeapon(itemName, 0, 0, id, bouns, tmp->getProfession());
            else
                newItem = new CWeapon(itemName, 0, 0, id, bouns, Profession::All);
        }
        else if (itemType == "food") {
            newItem = new CFood(itemName, 0, 0, id, bouns);
        }
        else if (itemType == "chestplate") {
            newItem = new CChestplate(itemName, 0, 0, id, bouns);
        }
        else if (itemType == "boots") {
            newItem = new CBoots(itemName, 0, 0, id, bouns);
        }
        else if (itemType == "helmet") {
            newItem = new CHelmet(itemName, 0, 0, id, bouns);
        }
        else if (itemType == "potion") {
            newItem = new CPotion(itemName, 0, 0, id, bouns);
        }

        if (newItem != NULL) {
            Products[i+1] = make_pair(newItem, price);  // 儲存商品及價格
        }
    }

	fin.close();
}

void CStore::displayStoreInfo() const {
    cout << "商品列表:" << endl;
    for (const auto& item : Products) {
        cout << "  ID: " << item.first
            << ", 名稱: " << item.second.first->getName()
            << ", 價格: " << item.second.second << endl;
    }
}

pair<CItem*, int> CStore::getItemById(const int inID) const {
    auto it = Products.find(inID);
    if (it != Products.end()) {
        return it->second; // 直接回傳 pair
    }
    return { NULL, 0 };    // 找不到時回傳 {nullptr, 0}，表示商品不存在且價格為0
}