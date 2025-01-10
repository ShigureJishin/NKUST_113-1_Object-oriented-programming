#ifndef DEF_H
#define DEF_H

using namespace std;


enum {
	efood = 1,
	eweapon,
	ehelmet,
	echestplate,
	eboots
};

enum {
	efighter = 1,
	emonster,
	epet
};

enum ItemType {
	Food = 0,
	Weapon = 1,
	Helmet = 2,
	Chestplate = 3,
	Boots = 4,
	Potion = 5,
	Other = 6
};

enum class Profession {
	Berserker = 1,
	Mage = 2,
	Tank = 3,
	All = 0
};

inline string returnProfessionName(Profession profession) {
	switch (profession) {
	case Profession::Berserker: return "Berserker";
	case Profession::Mage: return "Mage";
	case Profession::Tank: return "Tank";
	case Profession::All: return "All";
	default: return "Unknown";
	}
}

#endif