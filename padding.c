#include <stdio.h>
struct student  //student 구조체 선언
{char lastName[13]; /* 13 bytes */  //lastname 배열에 13칸 선언
int studentId;/* 4 bytes */ //student id 선언
short grade;/* 2 bytes */  //grade 선언
};


int main()

{  printf("[----- [박소연] [2019038079] -----]\n");
struct student pst;  //student 구조체를 pst라 지칭
printf("size of student = %ld\n", sizeof(struct student));//구조체 student의 크기를 출력 (3byte padding)
printf("size of int = %ld\n", sizeof(int));//int의 사이즈를 출력
printf("size of short = %ld\n", sizeof(short));//short의 사이즈를 출력 (2byte padding)
return 0;
}
