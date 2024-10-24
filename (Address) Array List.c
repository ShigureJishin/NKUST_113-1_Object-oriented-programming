#include <stdio.h>
#include <stdlib.h>
//第一種寫法    (位址，全指標)

void swap1 (int* p){        
    int temp;
    temp = *p;
    *p = *(p+1);
    *(p+1) = temp;
}

//第二種寫法    (位址，參數指標，內容是陣列)
void swap2(int* p){
    int temp;
    temp = p[0];
    p[0] = p[1];
    p[1] = temp;
}

//第三種寫法    (位址，全部都是陣列)
void swap3(int p[]){
    printf("%p\n",p);
    int temp;
    temp = p[0];
    p[0] = p[1];
    p[1] = temp;
}



int main(void){
  int x[2] = {3,8};
  printf("指標 %p\n", x);//3  8
  printf("數字 %d %d\n", x[0], x[1]);//3  8
  swap3(x);        //單寫矩陣名稱時，他代表矩陣中第一個元素位址。
  printf("%d %d", x[0], x[1]);//8  3

  system("PAUSE");
  return 0;
}