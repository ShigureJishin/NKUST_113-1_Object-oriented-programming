/*請實作一程式，此程式可以不斷地要求使用者輸入一組日期(日期格式YYYY/MM/DD，如2021/07/25)，
請判斷此日為此年第幾天(需考慮閏年)，若月份或當月日期超出範圍(如2020/01/32 or 2020/13 /01)則輸出”Error!”，
當輸入字串-1時則程式結束。

閏年規則如下：
西元年除以400可整除 或 西元年除以4可整除但除以100不可整除，為閏年。
西元年除以4不可整除 或 西元年分除以100可整除但除以400不可整除，為平年。
閏年是指該年有366日，多一天2月29日
*/
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

int main() {
  string inputData;

  while (true) {
    cin >> inputData;

    if (inputData == "-1") break;  // 當輸入字串 "-1" 時，結束程式

    int year = stoi(inputData.substr(0, 4));
    int month = stoi(inputData.substr(5, 2));
    int day = stoi(inputData.substr(8, 2));

    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
      if (day > 31 || day < 1) {
        cout << "Error!" << endl;
        continue;
      }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
      if (day > 30 || day < 1) {
        cout << "Error!" << endl;
        continue;
      }
    } else if (month == 2) {
      if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) {
        if (day > 29 || day < 1) {
          cout << "Error!" << endl;
          continue;
        }
      } else if (day > 28 || day < 1) {
        cout << "Error!" << endl;
        continue;
      }
    } else {
      cout << "Error!" << endl;
      continue;
    }

    int totalDays = 0;

    for (int i = 1; i < month; i++) {
      if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12) {
        totalDays += 31;
      } else if (i == 4 || i == 6 || i == 9 || i == 11) {
        totalDays += 30;
      } else if (i == 2) {
        if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) {
          totalDays += 29;
        } else {
          totalDays += 28;
        }
      }
    }

    totalDays += day;

    cout << totalDays;
    
    //cout << inputData << " ";

    cout << endl;  // 每組資料輸出後分隔一行
  }

  system("pause");
  return 0;
}