#ifndef ARMOREFFECT_H
#define ARMOREFFECT_H

#include <vector>

using namespace std;

// �M�ˮĪG���c
struct ArmorEffect {
    int helmetID;
    int bootsID;
    int chestplateID;
    int atkBonus;
    int defenseBonus;

    ArmorEffect(int hID = 0, int bID = 0, int cID = 0, int atk = 0, int def = 0)
        : helmetID(hID), bootsID(bID), chestplateID(cID), atkBonus(atk), defenseBonus(def) {
    }
};

class CArmorEffectData {
public:
    CArmorEffectData(string filePath);
    ~CArmorEffectData();

    // �q���[���M�˥[���ƾ�
    void loadFromFile(string filePath);

    // �ھڸ˳� ID ����������M�ˮĪG
    const ArmorEffect* getEffect(int helmetID, int bootsID, int chestplateID) const;

private:
    vector<ArmorEffect> effects;
};

#endif
