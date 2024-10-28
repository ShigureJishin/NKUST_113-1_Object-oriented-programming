/*請實作一程式，此程式會不斷地要求使用者輸入一個數字N ([-51, 51])以及一字串S，當N值小於-51或大於51時則結束程式。
當輸入一數字N以及一字串S後，請將字串中每個字元(包含a-zA-Z，其他符號除外)根據下面表格右移|N|個位數(當N為正數時)或左移|N|個位數(當N為負數時)並得到新的字元，以取代原字串，完成加密動作。
注意1: |N|代表N的絕對值
注意2: 大寫Z右移一個位數將成為小寫a
注意3: 小寫a左移一個位數將成為大寫Z*/

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

class StringData {
  public:
    // Constructor
    StringData(string source, int shiftMode) {
      L_R = shiftMode >= 0 ? 1: -1;
      shiftNum = abs(shiftMode);
      length = source.length();
      this->data = source;
    }

    // Destructor
    ~StringData() {}

    string getData() const {
      return data;
    }

    string getResult() const {
      return result;
    }

    void shiftData() {
      result = data;

      for (int i = 0; i < data.length(); i++) {
        if ( (result [i] < 'A') || (result[i] > 'Z' && result[i] < 'a') || (result[i] > 'z') ) continue;
        
        for (int j = 0; j < shiftNum; j++) {
          
          if (L_R == 1) {
            if (result[i] == 'Z') {
              result[i] = 'a';
            } 
            else if (result[i] == 'z') {
              result[i] = 'A';
            }
            else {
              result[i]++;
            }
          }
          else {
            if (result[i] == 'a') {
              result[i] = 'Z';
            } 
            else if (result[i] == 'A') {
              result[i] = 'z';
            } 
            else {
              result[i]--;
            }
          }
        }
      } 
    }
    

  private:
    string data;
    string result;
    int length;
    int L_R;
    int shiftNum;
};

int main() {
  int N;
  string strSource;

  while (true) {
    cin >> N;

    // 離開程式
    if (N > 51 || N < -51) break;

    cin >> strSource;

    // Creating StringData object
    StringData StrData(strSource, N);

    // Shift data
    StrData.shiftData();

    // 輸出結果
    cout << StrData.getResult() << endl;
  }

  system("pause");
  return 0;
}
