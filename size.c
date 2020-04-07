#include<stdio.h>
#include<stdlib.h>
void main(){
    printf("[----- [박소연] [2019038079] -----]");
int **x;  //int형 이중포인터 x선언
printf("sizeof(x) = xlu\n", sizeof(x));  //x의 size를 출력
printf("sizeof(*x) = Xlu\n", sizeof(*x));  //포인터 x의 size를 출력
printf("sizeof(**x) = Xlu\n", sizeof (**x));  //이중포인터 x의 size를 출력
}
