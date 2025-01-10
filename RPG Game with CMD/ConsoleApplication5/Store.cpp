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
		cout << "Ū�ɥ���: " << filename << endl;
		return;
	}
    CGlobalInfo::itm_data->Initialize();

    fin >> name >> itemCount; // Ū���ө��W�٩M�c�檫�~������

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
            Products[i+1] = make_pair(newItem, price);  // �x�s�ӫ~�λ���
        }
    }

	fin.close();
}

void CStore::displayStoreInfo() const {
    cout << "�ӫ~�C��:" << endl;
    for (const auto& item : Products) {
        cout << "  ID: " << item.first
            << ", �W��: " << item.second.first->getName()
            << ", ����: " << item.second.second << endl;
    }
}

pair<CItem*, int> CStore::getItemById(const int inID) const {
    auto it = Products.find(inID);
    if (it != Products.end()) {
        return it->second; // �����^�� pair
    }
    return { NULL, 0 };    // �䤣��ɦ^�� {nullptr, 0}�A��ܰӫ~���s�b�B���欰0
}