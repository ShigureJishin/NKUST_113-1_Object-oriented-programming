#include "Item.h"

CItem::CItem (string inname, int initSize, int initWeight, int initID, ItemType initType){
	Name = inname;
	Size = initSize;
	Weight = initWeight;
	ID = initID;
	Type = initType;
}

void CItem::setSize (int inSize){
	Size = inSize >= 0 ? inSize : 0;	
}

void CItem::setWeight (int inWeight){
	Weight = inWeight >= 0 ? inWeight : 0;	
}

void CItem::setName (string inName){
	Name = inName;	
}

int CItem::getSize (){
	return Size;	
}

int CItem::getWeight (){
	return Weight;	
}

string CItem::getName (){
	return Name;	
}
