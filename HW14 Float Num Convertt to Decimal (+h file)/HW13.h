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
    void normalize(vector<int> &num);
    vector<int> addBigNumbers(const vector<int> &a, const vector<int> &b);
};

void Data::convert() {
    result.clear();  // 確保結果字符串是空的
    vector<int> numVec;         // 用於存儲 n 進制的每位數字
    vector<int> decimalResult;  // 用於存儲十進制結果（大數）
    vector<int> basePower = {1}; // 進制次方值初始化為 1（十進制）

    // 初始化十進制結果為 0
    decimalResult.push_back(0);

    // 將 n 進制數字存入 numVec (反向存儲以便後續處理)
    for (int i = NumData.size() - 1; i >= 0; --i) {
        if (isdigit(NumData[i])) {
            numVec.push_back(NumData[i] - '0');
        } else if (isalpha(NumData[i])) {
            numVec.push_back(toupper(NumData[i]) - 'A' + 10);
        }
    }

    // 將 n 進制數轉換為十進制數
    for (int digit : numVec) {
        // decimalResult += digit * basePower
        vector<int> temp = basePower;  // temp = basePower
        for (int &x : temp) x *= digit;  // temp = temp * digit
        normalize(temp);               // 處理進位
        decimalResult = addBigNumbers(decimalResult, temp);  // 大數加法

        // basePower *= toConvert
        for (int &x : basePower) x *= toConvert;
        normalize(basePower);  // 處理進位
    }

    // 將十進制結果轉換為字符串
    for (int i = decimalResult.size() - 1; i >= 0; --i) {
        result += to_string(decimalResult[i]);
    }
}

// 處理大數進位
void Data::normalize(vector<int> &num) {
    int carry = 0;
    for (int &digit : num) {
        digit += carry;
        carry = digit / 10;
        digit %= 10;
    }
    while (carry > 0) {
        num.push_back(carry % 10);
        carry /= 10;
    }
}

// 大數加法
vector<int> Data::addBigNumbers(const vector<int> &a, const vector<int> &b) {
    vector<int> result;
    int carry = 0, sum = 0;
    int maxSize = max(a.size(), b.size());
    for (int i = 0; i < maxSize; ++i) {
        sum = carry;
        if (i < a.size()) sum += a[i];
        if (i < b.size()) sum += b[i];
        result.push_back(sum % 10);
        carry = sum / 10;
    }
    if (carry > 0) result.push_back(carry);
    return result;
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
