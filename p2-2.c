#include <stdio.h>
void print1 (int *ptr, int rows);  //������Ÿ�� ����
int main()
{
    printf("[----- [�ڼҿ�] [2019038079] -----]");
int one[] = {0, 1, 2, 3, 4};  // one�̶�� �迭�� �ʱ�ȭ����
printf("one= %p\n", one);  //one�� �ּҸ� ���
printf("&one= %p\n", &one);  //one�� �ּҸ� ���
printf("&one[0]%p\n", &one[0]);  //one�� 0��° �迭�� �ּҸ� ���
printf("\n");
print1(&one[0], 5); //�Ű�����
return 0;
}

void print1 (int *ptr, int rows)  // *ptr���� one�� 0��° �ּҸ�, rows�� 5�� �־��� 
{/* print out a one-dimensional array using a potnter */
int i;  //int �� ���� i ����
printf ("Address \t Contents\n");
for (i = 0; i < rows; i++)  //for���� ���� 0���� 4���� i�� ����������
printf("%p \t %5d\n", ptr + i, *(ptr + i));  // ptr+i�� �ּҿ�, ptr+i �� ���� �������
printf("\n");
}