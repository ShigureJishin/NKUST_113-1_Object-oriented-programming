#ifndef Store_H
#define Store_H

#include <string>
#include <vector>
#include <map>
#include "Item.h"
#include "ItemData.h"

using namespace std;

class CStore {
public:
    CStore(const string filename);
    string getName() { return name; };
    int getItemCount() { return itemCount; };
    pair<CItem*, int> getItemById(const int) const;
    void displayStoreInfo() const;

private:
    string name;
    int itemCount;
    map<int, pair<CItem*, int>> Products;  // 儲存商品ID和價格
};

#endif