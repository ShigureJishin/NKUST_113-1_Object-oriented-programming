#ifndef PET_H
#define PET_H

#include "LifeEntity.h"

class CPet : public CLifeEntity {
public:
    CPet(string, int, int, int, int);
    void setName(string newName);

    /* µ¥¯Å¬ÛÃö */
    void addXP(int);
    int getXP() { return XP; };
    int getLevel() { return Level; };

    int getDamage() { return atk; };
    int physicaldamage();
    virtual int attack(CLifeEntity*);
    virtual int defense(CLifeEntity*);
    virtual int isA();
private:
    string name;
    int XP;
    int Level;
    int hp;
    int atk;
};

#endif
