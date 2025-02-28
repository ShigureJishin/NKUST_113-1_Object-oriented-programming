/*
�й갵�@�{���A���{���i�H���_�a��J�@�ո�ơA���ո�ƥ]�t�@n�i����m�A
�H�Τ@���n(2 <= n <= 36)�A �����J��m�p�󵥩�0��n���ݩ�2��36�����@�Ȯɫh�����{���C
�C��J�@�ո�ƫ�A�бN�Ӳ�n�i�����ഫ��10�i�줧�Ʀr�ÿ�X�C(��J��m�ȳ̦h��1000��Ʀr)

36�i��ȥ]�t�F 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, �K, X, Y, Z
*/

#include <iostream>
#include <vector> 
#include "HW16.h"

using namespace std;

int main() {
  string Num;
  int fromConvert;

  while (true) {
    // ��J���
    cin >> fromConvert >> Num; 

    // ���}�{��
    if (fromConvert < 2 || fromConvert > 36) break;
    if ( Num == "0" || Num[0] == '-') break;

    // �إߪ���
    Data *data = new Data(Num, fromConvert);
    data->convertToDecimal(Num, fromConvert);
    double result = data->getResult();

    // �ഫ
    cout << fixed << setprecision(5) << floor(result * 100000) / 100000 << endl;
  }

  system("pause");
  return 0;
}