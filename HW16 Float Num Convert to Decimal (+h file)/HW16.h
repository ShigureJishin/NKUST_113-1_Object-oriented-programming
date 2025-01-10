#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

char shiftTable[36] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
                        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
                        'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 
                        'U', 'V', 'W', 'X', 'Y', 'Z'};  


class Data {
private:
    string NumData;
    int toConvert;
    double result;

public:
    Data(string str, int num);
    int charToValue(char c);
    void convertToDecimal(string m, int base);
    double getResult() { return result; }
};

Data::Data(string str, int num) {
    NumData = str;
    toConvert = num;
}

int Data::charToValue(char c) {
    for (int i = 0; i < 36; i++) {
        if (c == shiftTable[i]) {
            return i;
        }
    }
    return -1;
}

// 將 n 進制數字轉換為 10 進制
void Data::convertToDecimal(string m, int base) {
    size_t pointPos = m.find('.'); // 小數點位置
    string intPart = (pointPos == string::npos) ? m : m.substr(0, pointPos);  // 整數部分
    string fracPart = (pointPos == string::npos) ? "" : m.substr(pointPos + 1); // 小數部分

    // 轉換整數部分
    reverse(intPart.begin(), intPart.end()); // 反轉整數部分
    int decimalValue = 0;
    int baseInt = 1;
    
    for (char c : intPart) {
        int digitValue = charToValue(c);
        decimalValue = digitValue * baseInt + decimalValue;
        baseInt *= base;
        
    }

    // 轉換小數部分
    double fractionalValue = 0;
    double baseFactor = 1.0 / base;
    for (char c : fracPart) {
        int digitValue = charToValue(c);
       
        fractionalValue += digitValue * baseFactor;
        baseFactor /= base;
    }

    // 合併整數部分和小數部分
    result = decimalValue + fractionalValue;
}

