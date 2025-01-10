#ifndef PLACE_H
#define PLACE_H

#include <string>
#include <vector>
#include "Monster.h"
using namespace std;

#define MAX_DIRECTIONS 8
enum {
	eNorth = 0,
	eEastNorth,
	eEast,
	eEastSouth,
	eSouth,
	eWestSouth,
	eWest,
	eWestNorth
};
// type of exits
// 0: north
// 1: eastnorth
// 2: east
// 3: eastsouth
// 4: south 
// 5: westsouth
// 6: west
// 7: westnorth

class CMonster;

class CPlace {	
	friend class CMapData;
public:	
	CPlace (string filename, string filename2);
	string getname (){return name;};	
	string getdescription (){return description;};
	string get_exits ();
	void gen_monster_by_id (int);
	void show_mosters ();	
	CMonster *get_monster_by_engname (string);
	void showMap() const;
	bool remove_moster_by_engname (string);
	void clear_monster() { monsters.clear(); };
	int get_monster_count() { return monsters.size(); };
private:		
	string name;
	string description;
	vector<string> visualMap;        // 圖像化地圖
	int exits [8]; // store next direction place ID
	vector <CMonster *> monsters;
	
};

#endif