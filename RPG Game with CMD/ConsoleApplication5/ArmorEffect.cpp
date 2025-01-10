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


    // Ū���C�@��M�˥[���ƾ�
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
            return &effect; // ��^��쪺�M�ˮĪG������
        }
    }
    return nullptr; // �L�ǰt�ĪG
}