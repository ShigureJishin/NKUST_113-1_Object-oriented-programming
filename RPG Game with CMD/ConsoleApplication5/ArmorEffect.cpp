#include <fstream>
#include <sstream>
#include <iostream>

#include "ArmorEffect.h"

using namespace std;

CArmorEffectData::CArmorEffectData(string filePath) {
    loadFromFile(filePath);
}

void CArmorEffectData::loadFromFile(string filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "Failed to open file: " << filePath << endl;
        return;
    }
    else if (!file) {
        cout << "Failed to Read: " << filePath << endl;
        return;
    }

    string line;
    int effectCount;
    file >> effectCount;


    // 讀取每一行套裝加成數據
    int helmetID, bootsID, chestplateID, atkBonus, defenseBonus;
    for (int i = 0; i < effectCount; i++) {
        file >> helmetID >> bootsID >> chestplateID >> atkBonus >> defenseBonus;
        effects.emplace_back(helmetID, bootsID, chestplateID, atkBonus, defenseBonus);
    }
}

const ArmorEffect* CArmorEffectData::getEffect(int helmetID, int bootsID, int chestplateID) const {
    for (const auto& effect : effects) {
        if (effect.helmetID == helmetID &&
            effect.bootsID == bootsID &&
            effect.chestplateID == chestplateID) {
            return &effect; // 返回找到的套裝效果的指標
        }
    }
    return nullptr; // 無匹配效果
}