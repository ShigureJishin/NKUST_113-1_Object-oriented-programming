#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

char shiftTable[36] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
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
    string convertIntegerPart();
    string convertFractionPart();
    string multiplyFractionByBase(string fraction, int base);
};

Data::Data(string str, int num) {
    NumData = str;
    toConvert = num;
}

Data::~Data() {
  delete this;
}

string Data::getResult() {
  return result;
}

string Data::getData() {
  return NumData;
}

// 秈矪瞶
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

// ㄢ计
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

// ㄓ方 - 俱计场だ
string Data::convertIntegerPart() {
  int integerPart = 0;
  for (char ch : NumData) {
      if (isdigit(ch)) {
          integerPart = integerPart * 10 + (ch - '0');
      } else {
          break; // Stop when we reach the decimal point
      }
  }
  
  vector<int> baseResult;
  while (integerPart > 0) {
      baseResult.push_back(integerPart % toConvert);
      integerPart /= toConvert;
  }
  if (baseResult.empty()) baseResult.push_back(0); // Special case for 0
  
  string result;
  for (int i = baseResult.size() - 1; i >= 0; --i) {
      result += shiftTable[baseResult[i]];
  }
  return result;
}

// ㄓ方 - 计场だ
string Data::multiplyFractionByBase(string fraction, int base) {
    string result = "";
    long long frac = 0;  // ノㄓ纗计场だ计
    long long power = 1;       // ノㄓ璸衡计场だ计
    // 盢计场だ锣传俱计Α矪瞶
    for (char digit : fraction) {
        frac = frac * 10 + (digit - '0');
        power *= 10;
    }

    while (result.size() < 60) {  // 60
        frac *= base;  
        int integerPart = frac / power;  
        result += shiftTable[integerPart]; 
        frac = frac % power;
    }

    return result;
}




// Convert fraction part manually
string Data::convertFractionPart() {
    string fractionPart = NumData.substr(NumData.find('.') + 1);  // Get fraction part after decimal
    string result = multiplyFractionByBase(fractionPart, toConvert);
    return result;
}

// 璶锣传
void Data::convert() {
    result.clear();  // 睲 result
    string intPart = convertIntegerPart();
    result += intPart;
    string fracPart = convertFractionPart();
    if (!fracPart.empty()) {
        result += "." + fracPart;
    }
}