/*
請實做一程式，此程式可以不斷地輸入一組資料，此組資料包含一n進制整數m，
以及一整數n(2 <= n <= 36)， 直到輸入的m小於等於0或n不屬於2到36間任一值時則結束程式。
每輸入一組資料後，請將該組n進制資料轉換為10進位之數字並輸出。(輸入的m值最多有1000位數字)

36進制的值包含了 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, …, X, Y, Z
*/

#include <iostream>
#include <vector> 
#include "HW16.h"

using namespace std;

int main() {
  string Num;
  int fromConvert;

  while (true) {
    // 輸入資料
    cin >> fromConvert >> Num; 

    // 離開程式
    if (fromConvert < 2 || fromConvert > 36) break;
    if ( Num == "0" || Num[0] == '-') break;

    // 建立物件
    Data *data = new Data(Num, fromConvert);
    data->convertToDecimal(Num, fromConvert);
    double result = data->getResult();

    // 轉換
    cout << fixed << setprecision(5) << floor(result * 100000) / 100000 << endl;
  }

  system("pause");
  return 0;
}