#ifndef POTION_H
#define POTION_H

#include "Item.h"

class CPotion : public CItem {
public:
	CPotion(string inname = "", int initSize = 0, int initWeight = 0, int initID = 0, int init_mp = 0);
	int getmpbonus();
	virtual void beUsed(CLifeEntity*);
	virtual void UnUsed(CLifeEntity*);
	virtual int isA();
private:
	int bonus_mp;
};

#endif