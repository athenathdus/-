#include <stdio.h>
struct student  //student ����ü ����
{char lastName[13]; /* 13 bytes */  //lastname �迭�� 13ĭ ����
int studentId;/* 4 bytes */ //student id ����
short grade;/* 2 bytes */  //grade ����
};


int main()

{  printf("[----- [�ڼҿ�] [2019038079] -----]\n");
struct student pst;  //student ����ü�� pst�� ��Ī
printf("size of student = %ld\n", sizeof(struct student));//����ü student�� ũ�⸦ ��� (3byte padding)
printf("size of int = %ld\n", sizeof(int));//int�� ����� ���
printf("size of short = %ld\n", sizeof(short));//short�� ����� ��� (2byte padding)
return 0;
}
