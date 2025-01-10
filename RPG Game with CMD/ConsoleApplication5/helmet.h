#ifndef HELMET_H
#define HELMET_H

#include "Item.h"

class CHelmet : public CItem {
public:
	CHelmet(string inname = "", int initSize = 0, int initWeight = 0, int initID = 0, int init_defense = 0);
	int getdefensebonus();
	virtual void beUsed(CLifeEntity*);
	virtual void UnUsed(CLifeEntity*);
	virtual int isA();
private:
	int bonus_defense;
};

#endif