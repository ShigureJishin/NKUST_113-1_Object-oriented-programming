#include <fstream>
#include <iostream>
#include <iomanip>
#include "Skill.h"
#include "SkillData.h"
#include "def.h"
#include "GlobalInfo.h"

using namespace std;

void CSkillData::Initialize() {
	LoadSkillData();
}

void CSkillData::LoadSkillData() {
	ifstream fin("skill.txt");
	if (!fin) {
		cout << "讀檔失敗: skill.txt" << endl;
		return;
	}

	int num_skill;
	fin >> num_skill;

	string name;
	int demage, MP;
	int inID;
	CSkill* skill;
	int jobType;

	for (int i = 0; i < num_skill; i++) {
		fin >> inID >> name >> MP >> demage >> jobType;
		skill = new CSkill(inID , name , MP , demage, static_cast<Profession>(jobType));
		skill_array[inID] = skill;
		//cout << name << " " << MP << endl;
	}

#if 0
	map<int, CSkill*>::iterator it;
	for (it = skill_array.begin(); it != skill_array.end(); it++) {
		cout << (*it).first << " " << (*it).second->getName() << " " << (*it).second->getMPCost() << " " << (*it).second->getDamage() << endl;
	}
#endif 
	fin.close();
}

// 根據技能ID取得技能指標
CSkill* CSkillData::getSkill(int skillID) const {
	auto it = skill_array.find(skillID);
	if (it != skill_array.end()) {
		return it->second; // 返回技能指標
	}
	return nullptr; // 如果找不到該技能，返回空指標
}

void CSkillData::showAllSkills() const {
	cout << left
		 << setw(5) << "ID"
		 << setw(15) << "技能名稱"
		 << setw(10) << "MP消耗"
		 << setw(10) << "傷害"
		 << setw(10) << "職業限定" << endl;
	cout << setfill('-') << setw(50) << "-" << setfill(' ') << endl; // 分隔線

	for (auto it = skill_array.cbegin(); it != skill_array.cend(); ++it) {
		cout << setw(5) << it->first
			 << setw(15) << it->second->getName()
			 << setw(10) << it->second->getMPCost() 
			 << setw(10) << it->second->getDamage() 
			<< setw(10) << returnProfessionName(it->second->getProfession()) << endl;
	}
	cout << setfill('-') << setw(50) << "-" << setfill(' ') << endl; // 分隔線
}