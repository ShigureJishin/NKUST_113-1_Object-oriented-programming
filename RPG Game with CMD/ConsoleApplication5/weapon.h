#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"

class CWeapon : public CItem {
public:
	CWeapon (string inname = "", int initSize = 0, int initWeight = 0, int initID = 0, int init_attack = 0, Profession inProfession = Profession::All);
	int getattackbonus ();
	virtual void beUsed (CLifeEntity *);
	virtual void UnUsed (CLifeEntity *);
	virtual int isA ();
	Profession getProfession() const { return Restrictions; };
private:
	int bonus_attack;
	Profession Restrictions;
};

#endif