#include<stdio.h>
#include<stdlib.h>
void main(){
    printf("[----- [�ڼҿ�] [2019038079] -----]");
int **x;  //int�� ���������� x����
printf("sizeof(x) = xlu\n", sizeof(x));  //x�� size�� ���
printf("sizeof(*x) = Xlu\n", sizeof(*x));  //������ x�� size�� ���
printf("sizeof(**x) = Xlu\n", sizeof (**x));  //���������� x�� size�� ���
}
