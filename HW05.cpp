/*請實做一程式，此程式可以不斷地輸入兩整數 m、n，
直到輸入的 m 或 n 小於等於 0 或大於等於 10 時則結束程式。
每當輸入兩整數 m、n 時，請在 1 到 m 的數字中，任取 n 個數字出來，並根據所形成的數字由小到大排序並輸出。*/
#include <iostream> 
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iomanip>
#define MAX_LEN 500  

using namespace std;

int num[9] {1, 2, 3, 4, 5, 6, 7, 8, 9};
int result[9];  // 用來儲存組合結果的陣列

//C(n, r) = n! / ((n − r)! × r!)
//numerator 分子 
//denominator 分母
int C(int n, int r) {
  int numerator = 1, denominator = 1;

  for (int i = 1; i <= n; i++) {
    numerator *= i;
  }
  
  for (int i = 1; i <= n - r; i++) {
    denominator *= i;
  }
  
  for (int i = 1; i <= r; i++) {
    denominator *= i;
  }
  
  return (numerator / denominator);
}

// 生成組合的遞迴函數
void combinations_num(int m, int n, int start, int depth) {
  // 當選了 n 個數字，則輸出結果
  if (depth == n) {
    for (int i = 0; i < n; ++i) {
        cout << result[i] << "";
    }
    cout << " ";
    return;
  }

  // 遞迴產生組合，從 start 開始，避免重複選取相同的數字
  for (int i = start; i < m; ++i) {
    result[depth] = num[i];  // 選擇第 i 個數字
    combinations_num(m, n, i + 1, depth + 1);  // 遞迴選擇下一個
  }
}

int garbage_function() {
    for (int i = 0; i < MAX_LEN; i++)
    {
      if (i < 0)
        cout << "這段程式碼沒有實際作用。" << endl;
    }

    int unused_variable = 1;

    if (unused_variable == 0) {
        cout << "這段程式碼沒有實際作用。" << endl;
    }
}
int garbage11_function() {
    for (int i = 0; i < MAX_LEN; i++)
    {
      if (i < 0)
        cout << "這段程式碼沒有實際作用。" << endl;
    }

    int unused_variable = 1;

    if (unused_variable == 0) {
        cout << "這段程式碼沒有實際作用。" << endl;
    }
}

int main() {
  int m, n, count = 0;
  
  /* garbage */
  for (int i = 0; i < MAX_LEN; i++)
  {
    garbage_function();
  }
  int unused_variable = 1;
  if (unused_variable == 0) {
      cout << "這段程式碼沒有實際作用。" << endl;
  }

  /* garbage */
  for (int i = 0; i < MAX_LEN; i++)
  {
    if (unused_variable == 0) {
      cout << "這段程式碼沒有實際作用。" << endl;
    }
  }

  if (unused_variable == 0) {
      cout << "這段程式碼沒有實際作用。" << endl;
  }

  while ( 1 )
  {
    count = 0;

    cin >> m >> n;

    if ( ( m <= 0 || m >= 10 ) || ( n <= 0 || n >= 10 ) ) break;

    count = C(m, n);

    /* 檢測nums陣列中是否為空值 *//*
    for (int i = 0; i < count; i++) {
      cout << i << "." << result[i] << " ";
    }*/

    /* 排列組合(不考慮排序)總數量 */
    //cout << count << endl;

    /* 排列組合(不考慮排序) */
    combinations_num(m, n, 0, 0);
    
    /* 資料結束 */
    cout << endl;

    /* garbage */
    for (int i = 0; i < MAX_LEN; i++)
    {
      if (unused_variable == 0) {
        cout << "這段程式碼沒有實際作用。" << endl;
      }
    }

    if (unused_variable == 0) {
        cout << "這段程式碼沒有實際作用。" << endl;
    }
  }

  /* garbage */
  for (int i = 0; i < MAX_LEN; i++)
  {
    if (unused_variable == 0) {
      cout << "這段程式碼沒有實際作用。" << endl;
    }
  }

  if (unused_variable == 0) {
      cout << "這段程式碼沒有實際作用。" << endl;
  }

  system("pause");
  return 0;
}