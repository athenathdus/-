/* postfix.c
 *  2020 Data Structures, Homework #5
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10  //최대 스택 사이즈를 10으로 설정
#define MAX_EXPRESSION_SIZE 20  //최대 표현 사이즈를 20으로 설정

 //stack내에서 우선순위를 정의
typedef enum {  //enum 이라는 이름을 가진 구조체를 선언
	lparen = 0,  //왼쪽 괄호
	rparen = 9,  //오른쪽괄호
	times = 7,   //곱셈
	divide = 6,  //나눗셈
	plus = 5,    //덧셈
	minus = 4,   //뺄셈
	operand = 1 //피연산자
} precedence;  //typeof 를 사용하여 구조체 별칭을 precedence 으로 정의


char infixExp[MAX_EXPRESSION_SIZE];   	//infix expression을 저장하는 배열
char postfixExp[MAX_EXPRESSION_SIZE];	//postfix로 변경된 문자열을 저장하는 배열
char postfixStack[MAX_STACK_SIZE];	//postfix로 변환을 위해 필요한 스택
int evalStack[MAX_STACK_SIZE];		//계산을 위해 필요한 스택

int postfixStackTop = -1;   //postfic스택의 top을 -1이라 지정
int evalStackTop = -1;	  //eval스택의 top을 -1이라 지정
int evalResult = 0;	   //계산 결과를 저장

void postfixPush(char x)  //postfix에 넣는것
{
	postfixStack[++postfixStackTop] = x;
}

char postfixPop()  //postfix에서 값을 빼줌
{
	char x;  //char형 변수 x선언
	if (postfixStackTop == -1)  //만약, postfixstacktop이 -1이면, (스택이 없음을 의미)
		return '\0';  //NULL을 리턴
	else {  //그것이 아니라면, 
		x = postfixStack[postfixStackTop--];  //postficstack에서 top에 있는 것을 惠
	}
	return x;  //x 리턴
}

void evalPush(int x)  //eval에 넣는것
{
	evalStack[++evalStackTop] = x;
}

int evalPop()  //eval에서 빼내는것
{
	if (evalStackTop == -1) //만약, evalstacktop이 -1이면, (스택이 없음을 의미)
		return -1;  //-1을 리턴
	else  //그것이 아니라면, 
		return evalStack[evalStackTop--];  //evalstck에서 top에 있는 것을 빼냄
}

void getInfix()  //infix expression을 입력받음
{
	printf("Type the expression >>> ");
	scanf("%s", infixExp);  //infixexp에 입력된 값을 저장
}

precedence getToken(char symbol)//각각의 기호가 무엇을 의미하는지 알려줌
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

precedence getPriority(char x)  //우선순위에 따름
{
	return getToken(x);
}

void charCat(char* c)  //문자하나를 전달받아, postfixexp에 추가
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

void debug()//디버그 하는 함수
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

void reset()  //초기화 하는 함수
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for (int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';

	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}


void toPostfix(infixExp)  //infixexp의 문자를 하나씩 읽어가면서, stack을 이용하여 postfix로 변경
//변경된 postfix는 postfixexp에 저장된다. 
{

	char *exp = infixExp;  //infixexp의 문자 하나씩을 읽기 위한 포인터
	char x; //문자 하나를 임시로 저장하기 위한 변수


	while (*exp != '\0')//입력값이 null값이 나올때까지 반복
	{
		precedence token=0;
		int top = 0; 
		postfixStack[0] = '\0';  //첫번째 스택을 null값으로 초기화
		/*우선순위연산자 변수가 null값이 나올때까지 반복되는 반복문*/
		for (token == getToken(*exp);  //우선순위 연산자변수에 입력받는 문자를 넣어준다.
			token != '\0';
			token == getToken(*exp))
		{
			if (token == operand)//토큰이 피연산자일 경우
				printf("%c", *exp);//문자 출력
			else if (token == rparen)//토큰이 '('일 경우
			{
				/* 왼쪽 괄호가 나올 때까지 토큰들을 제거 */
				while (postfixStack[top] != lparen)//후위표기스택의 탑이 ')'될 때까지 반복
					x = postfixPop();
				/* 왼쪽 괄호를 버린다 */
			}
			else
				/* symbol의 isp가 token의 icp보다 크거나 같으면 symbol을 제거 */
				while (postfixStack[postfixStackTop] >= getPriority(*exp))//기존의 연산자보다 새로운 연산자의 우선순위가 크거나 같아질 때까지 반복
					x = postfixPop();

		}

		while ((token = postfixPop(&top)) != '\0')//토큰에 null값이 나올 때까지 반복
			x = postfixPop();
		printf("\n");
	}
}




	void evaluation()  //값을 계산하는 함수
	{
		//postfixexp, evalstack을 이용한 계산
		precedence token;//토큰 변수
		char *exp = infixExp;//문자를 하나씩 받을 수있도록 만든 변수
		int op1;
		int op2;
		int top = -1;
		token = getToken(*exp);
		while (*exp != '\0')  //입력받은 값이 null이 아니라면 계속 반복함
		{
			if (getToken(*exp) == operand)  //입력받은 값이 숫자면 
				evalPush(*exp - '0');  //아스키 문자값 48을 빼면 숫자를 얻을 수 있음
			else { //두 피연산자를 삭제하여 연산을 수행 한 후, 그 결과를 스택에 삽입함
				op2 = evalPop();  //연산자이면, 스택을 삭제하는 함수를 사용
				op1 = evalPop();  //연산자이면, 스택을 삭제하는 함수를 사용

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
		printf("2019038079 박소연");
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
