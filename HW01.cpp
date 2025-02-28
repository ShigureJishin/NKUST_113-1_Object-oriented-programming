#include <iostream> 
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iomanip>  

using namespace std;

int main() {
    int num1, num2, diff, reserve;
    
    while (1) {
        reserve = 0;
        diff = 0;

        cin >> num1 >> num2;

        diff = num1 - num2;

        if ( num1 < 0 and num2 < 0 ) {
            break;
        }

        if (diff < 0) {
            cout << "Error" << endl;
            continue;
        }

        for (int i = 0; diff > 0; i++){
            reserve = reserve * 10 + diff % 10;
            diff /= 10;
        }

        cout << fixed << setprecision(2) << sqrt(reserve) << endl;
    }

    system("pause");
    return 0;
}