#include <iostream>
#include <vector>
#include <vector>
#include <cstdlib>
#include <cstring>

using namespace std;

class Case {
public:
  string data;  // 儲存輸入的趨勢字串
  vector<string> chart; // 儲存最後的走勢圖

  // 生成走勢圖
  void generateChart() {
    int height = 0;  // 當前高度
    int maxHeight = 0, minHeight = 0;  // 最高點和最低點

    // 計算走勢圖的最高點和最低點
    for (char c : data) {
      if (c == 'R') height++;
      else if (c == 'F') height--;
      maxHeight = max(maxHeight, height);
      minHeight = min(minHeight, height);
    }

    int totalHeight = maxHeight - minHeight + 1;  // 總高度範圍

    // 初始化空的走勢圖
    for (int i = 0; i < totalHeight; i++) {
      chart.push_back(string(data.size(), ' '));  // 每一行插入長度為 data.size() 的空格字串
    } 

    // 由後往前繪製，繪製走勢圖，從最高點開始
    height = maxHeight;
    for (int j = 0; j < data.size(); j++) {
      if (data[j] == 'R' ) {
        chart[height][j] = '/';
        height--;  // 上升後移動到下一行
      }
      else if (data[j] == 'F') {
        height++;  // 下降前先移動到上一行
        chart[height][j] = '\\';
      } 
      else {
        chart[height][j] = '_';  // 持平
      }
    }
  }

  // 輸出走勢圖
  void printChart() {
    int i = 1;

    // 檢查走勢圖是否第一列為空
    for (char c : chart[0]){
      if (c != ' ') {
        i = 0;
        break;
      }
    }

    // 輸出垂直邊界和走勢圖
    for ( i ; i < chart.size(); i++) {
        cout << "| " << chart[i] << endl;
    }

    // 輸出底線
    cout << "+-";
    for (i = 0; i < data.size()+1; i++) {
        cout << "-";
    }
    cout << endl; 
  }
};

int main() {
  int N;

  while (true) {

    // N <= 0，結束程式
    cin >> N;
    if (N <= 0) break;  
    
    vector<Case> cases(N);   

    // 讀取每組測試資料
    for (int i = 0; i < N; i++) {
      cin >> cases[i].data;
    }

    // 生成所有測試資料的走勢圖
    for (int i = 0; i < N; i++) {
      cases[i].generateChart();
    }

    // 輸出所有走勢圖
    for (int i = 0; i < N; i++) {
      cout << "Case #" << i + 1 << ": " << endl;  // 輸出編號
      cases[i].printChart(); // 輸出走勢圖
      cout << endl;
    }
  }

  system("pause");
  return 0;
}
