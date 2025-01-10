
#ifndef LIFEENTITY_H
#define LIFEENTITY_H

#include <string>
#include "weapon.h"
#include "chestplate.h"
#include "boots.h"
#include "helmet.h"

#define MAXBLOODBARLEN 40
using namespace std;

class CLifeEntity {
public:
	CLifeEntity (int initHP = 0, int initSP = 0, string initname = "");	
	void setInitSPHP (int initHP = 0, int initSP = 0, int initMP = 0);
	bool isdead ();

	/* ¦å¶q */
	void setHP (int);
	void addHP (int);
	int getHP ();
	void addMAXHP(int);
	int getMAXHP ();

	/* §ðÀ»¤O */
	int getSP ();
	void addMAXSP(int);
	int getMAXSP ();
	void addSP (int);
	void delSP (int);

	/* MP */
	void setMP(int);
	void addMP(int);
	void delMP(int);
	int getMP() { return MP; };
	void addMAXMP(int);
	int getMAXMP() { return maxMP; };

	int gethurt (int hurt);
	string getname ();
	void setname (string);
	CWeapon *getWeapon (){return weapon;};
	void setWeapon (CWeapon *in_weapon){weapon = in_weapon;}
	CChestplate *getChestplate() { return chestplate; };
	void setChestplate(CChestplate *in_chestplate) { chestplate = in_chestplate; }
	CHelmet *getHelmet() { return helmet; };
	void setHelmet(CHelmet *in_helmet) { helmet = in_helmet; }
	CBoots *getBoots() { return boots; };
	void setBoots(CBoots *in_boots) { boots = in_boots; };

	bool kill (CLifeEntity *);
	virtual int attack (CLifeEntity *) = 0;
	virtual int defense (CLifeEntity *) = 0;
	virtual int isA () = 0;
private:	
	void fightstatus (CLifeEntity *f, CLifeEntity *s);
	void bloodbarshow (string title, int maxvalue, int value);
	int maxSP, maxHP, maxMP;
	int SP, HP, MP;
	string Name;
	CWeapon *weapon; 
	CChestplate *chestplate;
	CHelmet *helmet;
	CBoots *boots;
};

#endif