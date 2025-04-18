#ifndef MONSTER_H
#define MONSTER_H

#include "LifeEntity.h"
class CMonsterType;

class CMonster : public CLifeEntity {
public:
	CMonster (int initHP = 0, int initSP = 0, int initrough = 0, string init_name = string ("�Ǫ�"), string init_eng_name = string ("monster"));
	CMonster (const CMonsterType *type);
	int getRough ();
	int physicaldamage ();	
	virtual int attack (CLifeEntity *);
	virtual int defense (CLifeEntity *);
	virtual int isA ();
	string get_basic_data ();
	string get_engname (){return eng_name;};
	static void resetCounter() { counter_for_monster_id = 0; }
private:	
	static int counter_for_monster_id;
	string eng_name;
	int RoughDegree;
};

#endif