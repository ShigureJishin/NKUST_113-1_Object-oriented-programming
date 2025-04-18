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
  char  shiftTable[36] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
                           'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
                           'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 
                           'U', 'V', 'W', 'X', 'Y', 'Z' };

public:
  Data(string str, int num);  
  ~Data();

  void convert();
  string getResult();
  string getData();
};


void Data::convert() {
  result.clear();  // 確保結果字符串是空的
  vector<int> numVec;  // 處理大數

  // 將數字轉換為大數
  for (int i = 0; i < NumData.length(); i++) {
    numVec.push_back(NumData[i] - '0');
  }

  // 進行除法並取餘數
  while (!numVec.empty()) {
    int remainder = 0;
    vector<int> temp;

    for (int digit : numVec) {
      // 當前數字
      int current = remainder * 10 + digit;
      // 商
      temp.push_back(current / toConvert);
      // 餘數
      remainder = current % toConvert;
    }

    // 將餘數轉換為字串
    result = shiftTable[remainder] + result;

    // 清除前導零
    while (!temp.empty() && temp[0] == 0) {
      temp.erase(temp.begin());
    }
    numVec = temp;
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