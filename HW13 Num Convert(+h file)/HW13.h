using namespace std;

char  shiftTable[36] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
                        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
                        'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 
                        'U', 'V', 'W', 'X', 'Y', 'Z'};  
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
