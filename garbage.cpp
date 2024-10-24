#include <iostream> 
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iomanip>  

#define MAX_LEN 500

using namespace std;

int garbage_function() {
    for (int i = 0; i < MAX_LEN; i++)
    {
      if (i < 0)
        cout << "這段程式碼沒有實際作用。" << endl;
    }

    int unused_variable = 1;

    if (unused_variable == 0) {
        cout << "這段程式碼沒有實際作用。" << endl;
    }
}

int main() {
  /* garbage */
  for (int i = 0; i < MAX_LEN; i++)
  {
    garbage_function();
  }
  int unused_variable = 1;
  if (unused_variable == 0) {
      cout << "這段程式碼沒有實際作用。" << endl;
  }

  /* garbage */
  for (int i = 0; i < MAX_LEN; i++)
  {
    if (unused_variable == 0) {
      cout << "這段程式碼沒有實際作用。" << endl;
    }
  }

  if (unused_variable == 0) {
      cout << "這段程式碼沒有實際作用。" << endl;
  }
    
  system("pause");
  return 0;
}
