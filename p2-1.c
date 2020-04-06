#include <stdio.h>
#define MAX_SIZE 100 //MAX_SIZE 를 100으로 정의해줌

float sum(float [], int); //프로토타입 선언
float input[MAX_SIZE], answer;  //input 이름을 가진 배열에 MAX_SIZE(100)을 넣어줌, float변수 answer 선언
int i;  //int i 선언
void main(void)
{
    printf("[----- [박소연] [2019038079] -----]");
for(i=0; i < MAX_SIZE; i++)  //for문 (i가 0부터 99가 될때까지 돌아감)
input[i] = i;  //배열에 있는 주소값을 가져옴 
/* for checking call by reference*/
printf("address of input = %p\n", input);  //input의 주소 출력

answer = sum(input, MAX_SIZE);  // sum 함수의 매개변수
printf("The sum is: %f\n", answer);  //answer값을 출력
}
float sum(float list[], int n)  //list에 input의 주소가 들어가고, list를 통해서 input의 배열에 접근함. int n에는 MAX_SIZE가 들어감
{

printf("value of list = %p\n", list);   //list값을 출력
printf("address of list = %p\n\n", &list);  //list의 주소를 출력

int i;
float tempsum = 0;  //tempsum을 0으로 초기화
for(i = 0; i < n; i++)  //100번의 for문이 돌아감
tempsum += list[i];  //tempsum = tempsum + list[i] 으로 list[i]안에 있는 값을 다 더해줌
return tempsum; //tempsum을 반환함
}