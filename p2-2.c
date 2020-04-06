#include <stdio.h>
void print1 (int *ptr, int rows);  //프로토타입 선언
int main()
{
    printf("[----- [박소연] [2019038079] -----]");
int one[] = {0, 1, 2, 3, 4};  // one이라는 배열을 초기화해줌
printf("one= %p\n", one);  //one의 주소를 출력
printf("&one= %p\n", &one);  //one의 주소를 출력
printf("&one[0]%p\n", &one[0]);  //one의 0번째 배열의 주소를 출력
printf("\n");
print1(&one[0], 5); //매개변수
return 0;
}

void print1 (int *ptr, int rows)  // *ptr에는 one의 0번째 주소를, rows엔 5를 넣어줌 
{/* print out a one-dimensional array using a potnter */
int i;  //int 형 변수 i 선언
printf ("Address \t Contents\n");
for (i = 0; i < rows; i++)  //for문을 통해 0부터 4까지 i를 증가시켜줌
printf("%p \t %5d\n", ptr + i, *(ptr + i));  // ptr+i의 주소와, ptr+i 의 값을 출력해줌
printf("\n");
}