#include <stdio.h>
#include <stdlib.h>
void main()
{printf("[----- [�ڼҿ�] [2019038079] -----]");
int list[5];  // �̸��� list �迭 5�� ����
int *plist[5];  // int�� �����͸� ������ �ִ� plist �迭 5�� ����
list[0] = 10;  //list [0]�� 10�� �־���
list[1] = 11;  //list [1]�� 11�� �־���
plist[0] = (int*)malloc(sizeof(int)); // plist[0]�� malloc�� ���� �����Ҵ��� ����
printf("list[0] \t= %d\n", list[0]);  //list [0]�� �� ���
printf("address of list \t= %p\n", list);  //list�� �ּ� ���
printf("address of list[0] \t= %p\n", &list[0]);  //list[0]�� �ּҸ� ���
printf("address of list + 0 \t= %p\n", list+0);  //list�� �ּ� ���
printf("address of list + 1 \t= %p\n", list+1); //list +1 �� �ּ� ���
printf("address of list + 2 \t= %p\n", list+2);  //list +2 �� �ּ� ��� (list+1 �ּҿ��� 4����Ʈ ����)
printf("address of list + 3 \t= %p\n", list+3);  //list +3 �� �ּ� ��� (list+2 �ּҿ��� 4����Ʈ ����)
printf("address of list + 4 \t= %p\n", list+4);  //list +4 �� �ּ� ��� (list+3 �ּҿ��� 4����Ʈ ����)
printf("address of list[4] \t= %p\n", &list[4]);  //list [4]�� �ּҸ� ��� (list+3 �ּҿ��� 4����Ʈ ����)
free(plist[0]);  //����
}
