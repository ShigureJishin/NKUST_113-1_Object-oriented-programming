#ifndef SKILL_H
#define SKILL_H

#include "def.h"

using namespace std;

class CSkill {
private:
    int ID;
    string name;    // 技能名稱
    int CostMP;     // 消耗 MP
    int Damage;     // 技能傷害
    int Level;
    Profession Restrictions;

public:
    CSkill(int ,string , int , int, Profession);
    CSkill(int inID, string inName, int inMP, int inDMG, int inLevel, int inProfession);
    int getID() const { return ID; };
    string getName() const { return name; }
    int getMPCost() const { return CostMP; }
    int getDamage() const { return Damage; }
    int getLevel() const { return Level; }
    Profession getProfession() const { return Restrictions; }
    void displaySkillInfo() const;
    void upgrade();
};

#endif