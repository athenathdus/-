#include <stdio.h>
#define MAX_SIZE 100 //MAX_SIZE �� 100���� ��������

float sum(float [], int); //������Ÿ�� ����
float input[MAX_SIZE], answer;  //input �̸��� ���� �迭�� MAX_SIZE(100)�� �־���, float���� answer ����
int i;  //int i ����
void main(void)
{
    printf("[----- [�ڼҿ�] [2019038079] -----]");
for(i=0; i < MAX_SIZE; i++)  //for�� (i�� 0���� 99�� �ɶ����� ���ư�)
input[i] = i;  //�迭�� �ִ� �ּҰ��� ������ 
/* for checking call by reference*/
printf("address of input = %p\n", input);  //input�� �ּ� ���

answer = sum(input, MAX_SIZE);  // sum �Լ��� �Ű�����
printf("The sum is: %f\n", answer);  //answer���� ���
}
float sum(float list[], int n)  //list�� input�� �ּҰ� ����, list�� ���ؼ� input�� �迭�� ������. int n���� MAX_SIZE�� ��
{

printf("value of list = %p\n", list);   //list���� ���
printf("address of list = %p\n\n", &list);  //list�� �ּҸ� ���

int i;
float tempsum = 0;  //tempsum�� 0���� �ʱ�ȭ
for(i = 0; i < n; i++)  //100���� for���� ���ư�
tempsum += list[i];  //tempsum = tempsum + list[i] ���� list[i]�ȿ� �ִ� ���� �� ������
return tempsum; //tempsum�� ��ȯ��
}