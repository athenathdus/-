#include <stdio.h>
#include <stdlib.h>
void main()
{printf("[----- [박소연] [2019038079] -----]");
int list[5];  // 이름이 list 배열 5개 선언
int *plist[5];  // int형 포인터를 가지고 있는 plist 배열 5개 선언
list[0] = 10;  //list [0]에 10을 넣어줌
list[1] = 11;  //list [1]에 11을 넣어줌
plist[0] = (int*)malloc(sizeof(int)); // plist[0]에 malloc을 통해 동적할당을 해줌
printf("list[0] \t= %d\n", list[0]);  //list [0]의 값 출력
printf("address of list \t= %p\n", list);  //list의 주소 출력
printf("address of list[0] \t= %p\n", &list[0]);  //list[0]의 주소를 출력
printf("address of list + 0 \t= %p\n", list+0);  //list의 주소 출력
printf("address of list + 1 \t= %p\n", list+1); //list +1 의 주소 출력
printf("address of list + 2 \t= %p\n", list+2);  //list +2 의 주소 출력 (list+1 주소에서 4바이트 증가)
printf("address of list + 3 \t= %p\n", list+3);  //list +3 의 주소 출력 (list+2 주소에서 4바이트 증가)
printf("address of list + 4 \t= %p\n", list+4);  //list +4 의 주소 출력 (list+3 주소에서 4바이트 증가)
printf("address of list[4] \t= %p\n", &list[4]);  //list [4]의 주소를 출력 (list+3 주소에서 4바이트 증가)
free(plist[0]);  //해제
}
