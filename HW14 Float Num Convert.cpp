/*
請實做一程式，此程式可以不斷地輸入一組資料，此組資料包含一整數m，以及一整數n(2 <= n <= 36)， 
直到輸入的m小於等於0或n不屬於2到36間任一值時則結束程式。每輸入一組資料後，請將該組資料視為10進位數字，
並把此數字轉換為n進位之數字並輸出。(整數部分最多有1000位數字)
36進制的值包含了 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, …, X, Y, Z
*/

#include <iostream>
#include <vector> 

using namespace std;

class Data {
private:
  string NumData;
  string result;
  int toConvert;

public:
  Data(string str, int num);  
  ~Data();

  void convert();
  string getResult();
  string getData();
};

void Data::convert() {
  if (toConvert == 10) {
    result = NumData;
    return;
  }
  else {
    //
    // 轉換
    //
  }
}

string Data::getResult() {
  return result;
}

string Data::getData() {
  return NumData;
}

Data::Data(string str, int num) {
  NumData = str;
  toConvert = num;
}

Data::~Data() {
  delete this;
}

int main() {
  string Num;
  int toConvert;

  while (true) {
    // 輸入資料
    cin >> Num >> toConvert; 

    // 離開程式
    if (toConvert < 2 || toConvert > 36) break;
    if ( Num == "0" || Num[0] == '-') break;

    // 建立物件
    Data *data = new Data(Num, toConvert);

    // 轉換
    data->convert();

    // 輸出
    cout << data->getResult() << endl;
  }

  system("pause");
  return 0;
}