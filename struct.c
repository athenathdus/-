#include<stdio.h>

struct student1 {  //student1 구조체 선언
    char lastName;
    int studentId;
    char grade;
};
typedef struct {  //student2 구조체 선언 (구조체 표현하는 또다른 방법)
char lastName;
int studentId;
char grade;
 } student2;

int main() {
    printf("[----- [박소연] [2019038079] -----]");
struct student1 st1 = {'A', 100, 'A'};  //student1의 구조체에 변수 st1을 선언하여 각각에 넣어줌 

printf("st1.lastName = c\n", st1.lastName);  //st1의 lastname을 출력
printf("st1.studentId = d\n", st1.studentId);  //st1의 studentid를 출력
printf("st1.grade = c\n", st1.grade);  //st1의 grade를 출력

student2 st2 = {'B', 200, 'B'}; //student2의 구조체에 변수 st2을 선언하여 각각에 넣어줌 (typeof를 사용하여 student2 앞에 struct를 사용하지 않음 )

printf("\nst2.lastName = c\n", st2.lastName);  //st2의 lastname을 출력
printf("st2.studentId = d\n", st2.studentId);  //st2의 studentid를 출력
printf("st2.grade Xc\n", st2.grade); //st2의 grade를 출력

student2 st3;  //student2의 변수 st3지정 

st3 = st2;  //st3에 st2를 구조치환해줌

printf("\nst3.lastName = %c\n", st3. lastName);  //st3의 lastname을 출력
printf("st3.studentId = %d\n", st3.studentId);   //st3의 studentid를 출력
printf("st3.grade c\n", st3.grade);  //st3의 grade를 출력
/* equality test "/
if(st3 ==
printf("equal\n");
else
printf("not equal\n");
*/
return 0;
