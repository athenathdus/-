#include<stdio.h>

struct student1 {  //student1 ����ü ����
    char lastName;
    int studentId;
    char grade;
};
typedef struct {  //student2 ����ü ���� (����ü ǥ���ϴ� �Ǵٸ� ���)
char lastName;
int studentId;
char grade;
 } student2;

int main() {
    printf("[----- [�ڼҿ�] [2019038079] -----]");
struct student1 st1 = {'A', 100, 'A'};  //student1�� ����ü�� ���� st1�� �����Ͽ� ������ �־��� 

printf("st1.lastName = c\n", st1.lastName);  //st1�� lastname�� ���
printf("st1.studentId = d\n", st1.studentId);  //st1�� studentid�� ���
printf("st1.grade = c\n", st1.grade);  //st1�� grade�� ���

student2 st2 = {'B', 200, 'B'}; //student2�� ����ü�� ���� st2�� �����Ͽ� ������ �־��� (typeof�� ����Ͽ� student2 �տ� struct�� ������� ���� )

printf("\nst2.lastName = c\n", st2.lastName);  //st2�� lastname�� ���
printf("st2.studentId = d\n", st2.studentId);  //st2�� studentid�� ���
printf("st2.grade Xc\n", st2.grade); //st2�� grade�� ���

student2 st3;  //student2�� ���� st3���� 

st3 = st2;  //st3�� st2�� ����ġȯ����

printf("\nst3.lastName = %c\n", st3. lastName);  //st3�� lastname�� ���
printf("st3.studentId = %d\n", st3.studentId);   //st3�� studentid�� ���
printf("st3.grade c\n", st3.grade);  //st3�� grade�� ���
/* equality test "/
if(st3 ==
printf("equal\n");
else
printf("not equal\n");
*/
return 0;
