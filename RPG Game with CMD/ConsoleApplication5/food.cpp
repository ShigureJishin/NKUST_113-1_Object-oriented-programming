#include <iostream>
#include "Item.h"
#include "food.h"
#include "LifeEntity.h"
#include "def.h"

using namespace std;

CFood::CFood (string inname, int initSize, int initWeight, int initID, int init_hp) : CItem (inname, initSize, initWeight, initID, Food){	
	bonus_hp = init_hp;
}

int CFood::gethpbonus (){	
	return bonus_hp;
}

void CFood::beUsed (CLifeEntity *le){
	cout << "戰士使用食物" << getName () << ", ";
	le->addHP (this->gethpbonus ());
	cout << "體力回升到 " << le->getHP () << endl;
}

void CFood::UnUsed (CLifeEntity *le){	
}


int CFood::isA (){
	return efood;
}