#include <stdio.h>
#include <stdlib.h>
void main()  //main 함수 선언

{printf("[----- [박소연] [2019038079] -----]");
int list[5];  // 이름이 list 배열 5개 선언
int *plist[5] = {NULL,}; //int형 포인터를 가지고있는 plist를 null로 초기화 
plist[0] = (int *)malloc(sizeof(int));   //plist 0번째에 malloc을 통해 동적할당을 해줌
list[0] = 1; //0번쨰 배열에 1을 넣음
list[1] = 100;  // 1번째 배열에 100을 넣음 

*plist[0] = 200;  //plist 0번이 가리기키고 있는 곳에 200을 넣음 
printf("value of list[0] = %d\n", list[0]);  //list [0]의 값
printf("address of list[0] =%p\n",&list[0]);  //list [0]의 주소
printf("value of list =%p\n",&list);  //list [0]의 주소
printf("address of list (&list) =%p\n",&list);  //list [0]의 주소

//list array의 0번쨰 주소, 이름의 값, list의 주소가 다 동일함을 의미함 

printf("---------------------------------------------------------------\n\n");
printf("value of list[1]= %d\n", list[1]);  //list [1]의 값
printf("address of list[1] = %p\n", &list[1]);  //list [1]의 주소
printf("value of *(list+1) = %d\n", *(list + 1));  //list+ 1의 값
printf("address of list+1 = %p\n", list+1);  //list+1의 주소

//list +1은 list타입이 int형이므로 첫번째 주소에서 4바이트만큼 이동한 것임

printf("---------------------------------------------------------------\n\n");

printf("value of *plist[0] = %d\n", *plist[0]);  //plist 0번이 가리키는 값
printf("&plist[0]= %p\n", &plist[0]);  // plist[0]의 주소
printf("&plist= %p\n", &plist);  //plist의 주소
printf("plist= %p\n", plist);  //plist의 주소 
printf("plist[0]= %p\n", plist[0]);  //plist[0]이 가지고 있는 주소 
printf("plist[1]= %p\n", plist[1]); //plist[1]의 값
printf("plist[2]= %p\n", plist[2]); //plist[2]의 값
printf("plist[3]= %p\n", plist[3]); //plist[3]의 값
printf("plist[4]= %p\n", plist[4]); //plist[4]의 값

//plist [1] 부터 plist [4]까지는 null 값이 나옴 

free(plist[0]);  //동적할당 해제
}