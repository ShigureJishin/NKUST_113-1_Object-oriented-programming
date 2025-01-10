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
    Damage += 10; // �C���ɯšA�ˮ` +10
    CostMP += 5;  // �W�[MP����
}

void CSkill::displaySkillInfo() const
{
    /*cout << "�ޯ�: " << name << ", ���� MP: " << CostMP
        << ", �ˮ`: " << damage << endl;*/
}