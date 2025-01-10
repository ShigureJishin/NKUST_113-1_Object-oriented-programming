
#ifndef MAPDATA_H
#define MAPDATA_H

#include <map>
#include "Place.h"
#include "Store.h"

#define MAX_MONSTER_PER_PLACE 4 

class CMapData {
	friend class CPlace;
public:	
	CMapData ();
	~CMapData ();	
	void show_description (int in_ID);
	void show_map(int in_ID);
	void show_allmonster();
	void loadStores();
	string get_exits (int in_ID);
	int next_city (int cur_city, int next_dir);
	void generate_monsters ();
	void generate_monsters_place(CPlace* inCity);
	CPlace *get_place_by_id (int id);
	CPlace *get_place_by_name(string name);
	int get_id_by_place(CPlace *);
	map<int, CStore *> storedata;
private:
	map<int, CPlace *> mapdata;
	int num_cities;
};

#endif