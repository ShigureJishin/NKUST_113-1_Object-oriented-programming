#include <fstream>
#include <iostream>
#include "Skill.h"
#include "def.h"

CSkill::CSkill(int inID, string inName, int inMP, int inDMG, Profession inProfession) {
    ID = inID;
    name = inName;
    CostMP = inMP;
    Damage = inDMG;
    Level = 1;
    Restrictions = inProfession;
}

CSkill::CSkill(int inID, string inName, int inMP, int inDMG, int inLevel, int inProfession) {
    ID = inID;
    name = inName;
    CostMP = inMP;
    Damage = inDMG;
    Level = inLevel;
    Restrictions = static_cast<Profession>(inProfession);
}

void CSkill::upgrade() {
    Level++;
    Damage += 10; // 每次升級，傷害 +10
    CostMP += 5;  // 增加MP消耗
}

void CSkill::displaySkillInfo() const
{
    /*cout << "技能: " << name << ", 消耗 MP: " << CostMP
        << ", 傷害: " << damage << endl;*/
}