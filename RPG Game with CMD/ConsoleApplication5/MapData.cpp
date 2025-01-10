#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cassert>
#include "MapData.h"
#include "MonsterData.h"
#include "GlobalInfo.h"

using namespace std;

CMapData::CMapData (){
	ifstream fin("mapdata.txt");	
	if (!fin){
		cout << "讀檔失敗: mapdata.txt" << endl;
		return;
	}
	fin >> num_cities;
	int id, num_exits, dirs, place_id;
	map<int, CPlace *>::iterator it;
	string map_name, showhap_name;	
	CPlace *tmp_place;
	for (int i = 0; i < num_cities; i++){
		fin >> id >> map_name >> showhap_name;
		tmp_place = new CPlace (map_name, showhap_name);
		it = mapdata.find (id);
		if (it == mapdata.end ()){
			mapdata.insert (pair<int, CPlace *> (id, tmp_place));
			fin >> num_exits;
			for (int j = 0; j < num_exits; j++){
				fin >> dirs >> place_id;
				tmp_place->exits [dirs] = place_id;
			}
		} else {
			cout << map_name << " with " << id << " has been added before" << endl;
			exit (0);
		}
	}	
	fin.close ();

	// 加載所有商店
	loadStores();
#if 0
	for(it = mapdata.begin(); it != mapdata.end(); it++){
		cout << (*it).first << " " << (*it).second->getname () << endl;
	}
#endif    
}

CMapData::~CMapData (){
	for(map<int, CPlace *>::iterator it = mapdata.begin(); it != mapdata.end(); it++){
		delete it->second;
	}
}

string CMapData::get_exits (int in_ID){
	map<int, CPlace *>::iterator it = mapdata.find (in_ID);
	if (it == mapdata.end ()){
		cerr << "CMapData::get_exits Error";
		exit (0);
	}
	return (*it).second->get_exits ();
}

void CMapData::show_description (int in_ID){
	map<int, CPlace *>::iterator it = mapdata.find (in_ID);
	if (it == mapdata.end ()){
		cerr << "CMapData::show_description Error";
		exit (0);
	}
	CPlace *place = (*it).second;
	assert (place);
	cout << place->getname () << endl << place->getdescription () << endl;
	cout << place->get_exits () << endl;
}

void CMapData::show_map(int in_ID) {
	map<int, CPlace*>::iterator it = mapdata.find(in_ID);
	if (it == mapdata.end()) {
		cerr << "CMapData::show_map Error";
		exit(0);
	}
	CPlace* place = (*it).second;
	assert(place);
	place->showMap();
}

int CMapData::next_city (int cur_city, int next_dir){
	map<int, CPlace *>::iterator it = mapdata.find (cur_city);
	if (it == mapdata.end ()){
		cerr << "user is in a wrong city";
		exit (0);
	}
	assert (next_dir >= 0 && next_dir <= 7);	
	return (it->second->exits [next_dir]);
}

void CMapData::generate_monsters (){	
	map<int, CPlace *>::iterator it;
	int num, monster_id;

	for(it = mapdata.begin(); it != mapdata.end(); it++){
		it->second->clear_monster();
		num = 1 + rand () % MAX_MONSTER_PER_PLACE;
		cout << it->second->name << "產生 " << num << " 隻怪獸"<< endl;
		for (int i = 0; i < num; i++){
			monster_id = CGlobalInfo::monster_data->rand_get_monster_id ();
			it->second->gen_monster_by_id (monster_id);
		}
	}
}

void CMapData::generate_monsters_place(CPlace* inCity) {
	int num, monster_id;
	inCity->clear_monster();
	num = 1 + rand() % MAX_MONSTER_PER_PLACE;
	cout << "【警告】" << inCity->name << " 怪物已被清空，重新投放 " << num << " 隻怪獸" << endl;
	for (int i = 0; i < num; i++) {
		monster_id = CGlobalInfo::monster_data->rand_get_monster_id();
		inCity->gen_monster_by_id(monster_id);
	}
}

CPlace *CMapData::get_place_by_id (int id){
	map<int, CPlace *>::iterator it = mapdata.find (id);
	if (it == mapdata.end ()){
		cerr << id << " id is wrong";
		exit (0);
	}	
	return (it->second);
}

CPlace* CMapData::get_place_by_name(string name) {
	for (map<int, CPlace*>::iterator it = mapdata.begin(); it != mapdata.end(); it++) {
		if (it->second->getname() == name) {
			return it->second;
		}
	}
	
	return NULL;
}

int CMapData::get_id_by_place(CPlace *place) {
	for (map<int, CPlace *>::iterator it = mapdata.begin(); it != mapdata.end(); it++) {
		if (it->second == place) {
			return it->first; // 找到對應的鍵，返回
		}
	}

	return 0;
}

void CMapData::loadStores() {
	ifstream storeDataFile("storedata.txt");
	if (!storeDataFile) {
		cout << "讀檔失敗: storedata.txt" << endl;
		return;
	}

	int numStores;
	storeDataFile >> numStores;
	map<int, CStore*>::iterator it;
	string storeFile;
	CStore* tmp_store;
	int location;
	for (int i = 0; i < numStores; i++) {
		storeDataFile >> storeFile >> location;

		tmp_store = new CStore(storeFile);
		it = storedata.find(location);
		if (it == storedata.end()) {
			storedata.insert(pair<int, CStore*>(location, tmp_store));
		}
		else {
			cout << storeFile << " with " << location << " has been added before" << endl;
			exit(0);
		}

		
	}
	storeDataFile.close();
}

void CMapData::show_allmonster() {
	cout << "---------------------------------------------------------------------------------------" << endl;

	for (const auto& pair : mapdata) {
		int key = pair.first;
		CPlace* place = pair.second;
		cout << "【" << place->getname() << "】" << endl;
		place->show_mosters();
		cout << "---------------------------------------------------------------------------------------" << endl;
	}

}