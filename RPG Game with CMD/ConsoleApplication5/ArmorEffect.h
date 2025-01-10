#ifndef ARMOREFFECT_H
#define ARMOREFFECT_H

#include <vector>

using namespace std;

// 套裝效果結構
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

    // 從文件加載套裝加成數據
    void loadFromFile(string filePath);

    // 根據裝備 ID 獲取對應的套裝效果
    const ArmorEffect* getEffect(int helmetID, int bootsID, int chestplateID) const;

private:
    vector<ArmorEffect> effects;
};

#endif
