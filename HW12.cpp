/*請實作一程式，此程式可以不斷地要求使用者輸入一組資料，
此組資料包含一個編碼表以及一行文字，編碼表一開始使用 n 來表示有幾組編碼符號，
接著輸入每一個符號所代表的單字為何，請使用此編碼表來為接下來的文字資料做單字置換動作
(即將每個在編碼表中出現的單字使用相對應的符號來取代)。當資料內的 n<= 0時，即代表結束程式。
*/

#include <iostream>
#include <sstream>
#include <vector> 
#include <cstdlib>
#include <cstring>

using namespace std;

struct CodeTable {
  string symbol;
  string code;
};

class StringData {
  public:
    StringData(string source) {
      data = source;
    }

    ~StringData() {}

    void setData(string source) {
      data = source;
    }

    string getData() const {
      return result;
    }

    string getResult() const {
      return result;
    }

    void createCodeTable(string symbol, string code) {
      codeTable.push_back({symbol, code});
    
    }

    void replace() {
      result = "";  // 重置結果
      istringstream iss(data);
      string word;

      while (iss >> word) {
        char punctuation = '\0';
        bool replaced = false;

        // 檢查單字是否包含標點符號( 判斷最後一個字元是否為標點符號 )
        if (ispunct( word[word.length() - 1] )) {
          punctuation = word.back();
          word.pop_back();  // 移除最後的標點符號
        }

        for (int i = 0; i < codeTable.size(); i++) {
          if (codeTable[i].code == word) {
            result += codeTable[i].symbol;
            replaced = true;
            break;
          }     
        }

        if (!replaced) {
          result += word;
        }

        if (punctuation) {
          result += punctuation;
        }

        result += " ";
      }
    }

    void testCodeTable() {
      for (int i = 0; i < codeTable.size(); i++) {
        cout << "Size of " << codeTable.size() << endl;
        cout << "No" << i+1 << codeTable[i].symbol << " " << codeTable[i].code << endl;
      }
    }

  private:
    vector<CodeTable> codeTable;
    string data;
    string result;
};

int main() {
  int n;
  char symbol;
  string code;
  string strSource;

  while (true) {
    cin >> n;

    // 離開程式
    if (n <= 0) break;

    StringData strData("");

    // 輸入編碼表
    for (int i = 0; i < n; i++) {
      string symbol;
      string code;
      cin >> symbol >> code;
      strData.createCodeTable(symbol, code);
    }

    // 輸出編碼表
    // strData.testCodeTable();

    // 輸入字串
    cin.ignore();
    getline(cin, strSource);
    strData.setData(strSource);

    // 進行替換
    strData.replace();

    // 輸出結果
    cout << strData.getResult() << endl;
  }

  system("pause");
  return 0;
}