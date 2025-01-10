#ifndef SKILLDATA_H
#define SKILLDATA_H

#include <vector>
#include <map>
#include "Skill.h"

class CSkillData {
public:
	void Initialize();
	CSkill* getSkill(int) const;
	void showAllSkills() const;

private:
	void LoadSkillData();
	map<int, CSkill*> skill_array;
};

#endif