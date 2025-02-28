#include <iostream> 
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iomanip>  

using namespace std;

int main() {
    string sentence, result;
    char C1, C2;
    
    while (1) {
        result = "";

        cin >> sentence;

        if (sentence == "bye")
          break;

        cin >> C1 >> C2;

        for (int i = 0; i < sentence.length(); i++){
            if (sentence[i] == C1)
              sentence[i] = C2;
        }

        result = sentence;

        cout << result << endl;
    }

    system("pause");
    return 0;
}