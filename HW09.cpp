/*
請設計一個程式，此程式可以不斷地輸入一個 N 的值(1<N<1000000，當N<=1時則離開程式) ，
請輸出此整數 N 是非質數(not prime)，質數(prime)，或 emirp。
*/
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

class Number {
public:
  int Num;
  int reseverNum;
  bool isPrime;
  bool isEmirp;

  /* 原數質數判斷 */
  void checkPrime() {
    isPrime = true;

    for (int i = 2; i < Num; i++) {
      if (Num % i == 0) {
        isPrime = false;
        break;
      }
    }
  }

  /* 翻轉後數字質數判斷 */
  void checkEmirp() {
    isEmirp = true;

    /* 翻轉後的數字等於原數，不會是emirp */
    if (  reseverNum == Num ){
      isEmirp = false;
      return;
    }
    
    for (int i = 2; i < reseverNum; i++) {
      if (reseverNum % i == 0) {
        isEmirp = false;
        break;
      }
    }
  }

  /* 翻轉數字 */
  void reverseNum() {
    int tempNum = Num;
    reseverNum = 0;

    while (tempNum > 0) {
      reseverNum = reseverNum * 10 + tempNum % 10;
      tempNum /= 10;
    }

    //cout << reseverNum << endl;
  }
};

int main() {

  int N;

  while (true) {

    cin >> N;

    if (N <= 1) break;
    
    Number number;
    number.Num = N;

    /* 判斷 */
    number.checkPrime();
    number.reverseNum();
    number.checkEmirp();
    

    /* 輸出結果 */
    if (number.isPrime && number.isEmirp) {
      cout << "emirp" << endl;
    } 
    else if (number.isPrime) {
      cout << "prime" << endl;
    } 
    else {
      cout << "not prime" << endl;
    }
  }

  system("pause");
  return 0;
}