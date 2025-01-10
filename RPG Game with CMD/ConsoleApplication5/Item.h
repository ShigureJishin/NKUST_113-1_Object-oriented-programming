#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "def.h"

class CLifeEntity;
using namespace std;

class CItem {
public:
	CItem (string inname = "", int initSize = 0, int initWeight = 0, int initID = 0, ItemType initType = Other);
	void setSize (int);
	int getSize ();
	void setWeight (int);
	int getWeight ();
	void setName (string);
	string getName ();
	int getID (){return ID;};
	ItemType getType() const { return Type; };
	virtual void beUsed (CLifeEntity *) = 0;
	virtual void UnUsed (CLifeEntity *) = 0;
	virtual int isA () = 0;
private:	
	int ID;	
	int Size, Weight;
	string Name;
	ItemType Type;
};

#endif