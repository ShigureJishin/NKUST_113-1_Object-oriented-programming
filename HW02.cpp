#include <iostream> 
#include <stdlib.h>
#include <string.h>

using namespace std;
int main() {
    string str1, str2;

    while (1) {
        cin >> str1 >> str2;

        if ( str1 == "bye" or str2 == "bye" ) {
            break;
        }

        int maxLength = str1.length() > str2.length() ? str1.length() : str2.length();

        for (int i = 0; i < maxLength; i++){ // �����C�Ӧr��

            char charStr1 = (i < str1.length()) ? str1[i] : 0;
            char charStr2 = (i < str2.length()) ? str2[i] : 0;

            // �p�� ASCII �Ȯt�Z
            int difference = charStr1 - charStr2;

            cout << difference << " ";
        }
		
        cout << endl;
    }

    system("pause");
    return 0;
}