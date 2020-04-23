/* postfix.c
 *  2020 Data Structures, Homework #5
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10  //�ִ� ���� ����� 10���� ����
#define MAX_EXPRESSION_SIZE 20  //�ִ� ǥ�� ����� 20���� ����

 //stack������ �켱������ ����
typedef enum {  //enum �̶�� �̸��� ���� ����ü�� ����
	lparen = 0,  //���� ��ȣ
	rparen = 9,  //�����ʰ�ȣ
	times = 7,   //����
	divide = 6,  //������
	plus = 5,    //����
	minus = 4,   //����
	operand = 1 //�ǿ�����
} precedence;  //typeof �� ����Ͽ� ����ü ��Ī�� precedence ���� ����


char infixExp[MAX_EXPRESSION_SIZE];   	//infix expression�� �����ϴ� �迭
char postfixExp[MAX_EXPRESSION_SIZE];	//postfix�� ����� ���ڿ��� �����ϴ� �迭
char postfixStack[MAX_STACK_SIZE];	//postfix�� ��ȯ�� ���� �ʿ��� ����
int evalStack[MAX_STACK_SIZE];		//����� ���� �ʿ��� ����

int postfixStackTop = -1;   //postfic������ top�� -1�̶� ����
int evalStackTop = -1;	  //eval������ top�� -1�̶� ����
int evalResult = 0;	   //��� ����� ����

void postfixPush(char x)  //postfix�� �ִ°�
{
	postfixStack[++postfixStackTop] = x;
}

char postfixPop()  //postfix���� �����°�
{
	char x;  //char�� ���� x����
	if (postfixStackTop == -1)  //����, postfixstacktop�� -1�̸�, (������ ������ �ǹ�)
		return '\0';  //NULL�� ����
	else {  //�װ��� �ƴ϶��, 
		x = postfixStack[postfixStackTop--];  //postficstack���� top�� �ִ� ���� ����
	}
	return x;  //x ����
}

void evalPush(int x)  //eval�� �ִ°�
{
	evalStack[++evalStackTop] = x;
}

int evalPop()  //eval���� �����°�
{
	if (evalStackTop == -1) //����, evalstacktop�� -1�̸�, (������ ������ �ǹ�)
		return -1;  //-1�� ����
	else  //�װ��� �ƴ϶��, 
		return evalStack[evalStackTop--];  //evalstck���� top�� �ִ� ���� ����
}

void getInfix()  //infix expression�� �Է¹���
{
	printf("Type the expression >>> ");
	scanf("%s", infixExp);  //infixexp�� �Էµ� ���� ����
}

precedence getToken(char symbol)//������ ��ȣ�� ������ �ǹ��ϴ��� �˷���
{
	switch (symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	default: return operand;
	}

}

precedence getPriority(char x)  //�켱������ ����
{
	return getToken(x);
}

void charCat(char* c)  //�����ϳ��� ���޹޾�, postfixexp�� �߰�
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

void debug()//����� �ϴ� �Լ�
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for (int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()  //�ʱ�ȭ �ϴ� �Լ�
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for (int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';

	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}


void toPostfix(infixExp)  //infixexp�� ���ڸ� �ϳ��� �о�鼭, stack�� �̿��Ͽ� postfix�� ����
//����� postfix�� postfixexp�� ����ȴ�. 
{

	char *exp = infixExp;  //infixexp�� ���� �ϳ����� �б� ���� ������
	char x; //���� �ϳ��� �ӽ÷� �����ϱ� ���� ����


	while (*exp != '\0')//�Է°��� null���� ���ö����� �ݺ�
	{
		precedence token=0;
		int top = 0; 
		postfixStack[0] = '\0';  //ù��° ������ null������ �ʱ�ȭ
		/*�켱���������� ������ null���� ���ö����� �ݺ��Ǵ� �ݺ���*/
		for (token == getToken(*exp);  //�켱���� �����ں����� �Է¹޴� ���ڸ� �־��ش�.
			token != '\0';
			token == getToken(*exp))
		{
			if (token == operand)//��ū�� �ǿ������� ���
				printf("%c", *exp);//���� ���
			else if (token == rparen)//��ū�� '('�� ���
			{
				/* ���� ��ȣ�� ���� ������ ��ū���� ���� */
				while (postfixStack[top] != lparen)//����ǥ�⽺���� ž�� ')'�� ������ �ݺ�
					x = postfixPop();
				/* ���� ��ȣ�� ������ */
			}
			else
				/* symbol�� isp�� token�� icp���� ũ�ų� ������ symbol�� ���� */
				while (postfixStack[postfixStackTop] >= getPriority(*exp))//������ �����ں��� ���ο� �������� �켱������ ũ�ų� ������ ������ �ݺ�
					x = postfixPop();

		}

		while ((token = postfixPop(&top)) != '\0')//��ū�� null���� ���� ������ �ݺ�
			x = postfixPop();
		printf("\n");
	}
}




	void evaluation()  //���� ����ϴ� �Լ�
	{
		//postfixexp, evalstack�� �̿��� ���
		precedence token;//��ū ����
		char *exp = infixExp;//���ڸ� �ϳ��� ���� ���ֵ��� ���� ����
		int op1;
		int op2;
		int top = -1;
		token = getToken(*exp);
		while (*exp != '\0')  //�Է¹��� ���� null�� �ƴ϶�� ��� �ݺ���
		{
			if (getToken(*exp) == operand)  //�Է¹��� ���� ���ڸ� 
				evalPush(*exp - '0');  //�ƽ�Ű ���ڰ� 48�� ���� ���ڸ� ���� �� ����
			else { //�� �ǿ����ڸ� �����Ͽ� ������ ���� �� ��, �� ����� ���ÿ� ������
				op2 = evalPop();  //�������̸�, ������ �����ϴ� �Լ��� ���
				op1 = evalPop();  //�������̸�, ������ �����ϴ� �Լ��� ���

				switch(token) {
				case plus: evalPush(op1 + op2); break;
				case minus: evalPush(op1 - op2); break;
				case times: evalPush(op1*op2); break;
				case divide: evalPush(op1 / op2); break;

				}

			}
			token = getToken(*exp); 
		}
	}




	int main()
	{
		printf("2019038079 �ڼҿ�");
		char command;

		do {
			printf("----------------------------------------------------------------\n");
			printf("               Infix to Postfix, then Evaluation               \n");
			printf("----------------------------------------------------------------\n");
			printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
			printf("----------------------------------------------------------------\n");

			printf("Command = ");
			scanf(" %c", &command);

			switch (command) {
			case 'i': case 'I':
				getInfix();
				break;
			case 'p': case 'P':
				toPostfix();
				break;
			case 'e': case 'E':
				evaluation();
				break;
			case 'd': case 'D':
				debug();
				break;
			case 'r': case 'R':
				reset();
				break;
			case 'q': case 'Q':
				break;
				default:
				printf("\n       >>>>>   Concentration!!   <<<<<     \n");
				break;
			}

		} while (command != 'q' && command != 'Q');

		return 0;


	}