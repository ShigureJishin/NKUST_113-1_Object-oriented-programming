/*請實做一程式，此程式可以不斷地輸入一組資料，此組資料包含一整數m，
以及m個物品名稱，直到輸入資料的m小於等於0時結束程式。當資料輸入後，
請輸出選擇這些物品的可能組合(包含都不選，都不選時請輸出”empty”)，
輸出結果時請將所選擇物品依照字典出現順序排序輸出。
此外，輸出資料時，請優先輸出選擇數較少的組合，當選擇數一樣時，則所選物品在字典排序中最前面者先行輸出。
*/
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

// 用來生成組合的遞迴函數
void generate_combinations(string items[], string result[], int start, int n, int depth, int m) {
  if (depth == n) {
    // 當前選擇的組合輸出
    for (int i = 0; i < n; ++i) {
      cout << result[i];
      
      if ( i == n - 1)
        cout << "";
      else
        cout << " ";
    }
    cout << endl;
    
    return;
  }

  for (int i = start; i < m; ++i) {
    result[depth] = items[i];  // 選定物品
    generate_combinations(items, result, i + 1, n, depth + 1, m);  // 遞迴
  }
}

int main() {
  int WordCount;

  while (true) {
    cin >> WordCount;
    if (WordCount <= 0) break;  // 當 WordCount <= 0 時，結束程式

    string items[WordCount];  // 儲存物品名稱
    string result[WordCount]; // 儲存當前選擇的組合

    // 輸入物品名稱
    for (int i = 0; i < WordCount; ++i) {
        cin >> items[i];
    }

    // 輸出 "empty" 作為空組合
    cout << "empty" << endl;

    // 對物品名稱按照字典順序進行排序
    sort(items, items + WordCount);

    // 生成所有可能的組合，從選擇 1 到 WordCount 個
    for (int i = 1; i <= WordCount; ++i) {
        generate_combinations(items, result, 0, i, 0, WordCount);
    }

    cout << endl;  // 每組資料輸出後分隔一行
  }

  system("pause");
  return 0;
}