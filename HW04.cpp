#include <iostream> 
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iomanip>  

#define MAX_LEN 500

using namespace std;

int muilt(int Num, int result[]) {
  /* 歸零 result 陣列*/
  for (int i = 0; i < MAX_LEN; i++){
    result[i] = 0;
  }

  /* 結果 1 設置 1*1 =1，使用位數為 1 */
  result[0] = 1; 
  int result_size = 1;

  for (int i = 2; i <= Num; i++) {
    int carry = 0;  // 進位初始化

    // 對每個位數進行乘法
    for (int j = 0; j < result_size; j++) {
      int prod = result[j] * i + carry;
      result[j] = prod % 10;  // 最後一位
      carry = prod / 10;  // 進位
    }

    // 處理剩餘的進位
    while (carry) {
      result[result_size] = carry % 10;
      carry = carry / 10;
      result_size++;
    }
  }

  return result_size;  // 返回結果的位數
}

// 搜索指定數字在 result 的出現次數
int Search(int keyNum, int data[], int data_size) {
    int countNum = 0;
    for (int i = 0; i < data_size; i++) {
        if (data[i] == keyNum) {
            countNum++;
        }
    }
    return countNum;
}

int main() {
    int result[MAX_LEN];
    int InputNum, SearchNum, result_size;

    while (1) {
      int NumCount = 0;

      cin >> InputNum >> SearchNum;

      for (int i = 1; i <= InputNum; i++)
      {
        memset(result, 0, sizeof(result)); // 初始化

        int result_size = muilt(i, result);

        /* 顯示計算結果 */
        /*
        for (int index = result_size - 1; index >= 0; index--)
          cout << result[index];

        cout << endl;
        */

        /* 搜尋 */
        NumCount = NumCount + Search(SearchNum, result, result_size);
      }
      
      cout << NumCount << endl;
  }
    
  system("pause");
  return 0;
}
