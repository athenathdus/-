/*
 * circularQ.c
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4  //MAX_QUEUE_SIZE를 4로 정의

typedef char element;  //char를 별칭 element로 정의
typedef struct {
	element queue[MAX_QUEUE_SIZE];  //queue를 선언
	int front, rear;
}QueueType;  //별칭이 QueueType인 구조체 선언


QueueType *createQueue();
int isEmpty(QueueType *cQ); //비어있음을 나타내는 함수
int isFull(QueueType *cQ);  //다 차있음을 나타내는 함수
void enQueue(QueueType *cQ, element item);  //큐에 넣는 함수
void deQueue(QueueType *cQ, element* item);  //큐에서 뺴는 함수
void printQ(QueueType *cQ);  //큐를 프린트하는 함수	
void debugQ(QueueType *cQ);  //큐를 디버깅하는 함수
element getElement();  //char형 이기 때문에 element로 받음


int main(void)
{
	printf("2019038079 박소연");
	QueueType *cQ = createQueue();  //*cQ를 동적할당 해줌
	element data;  //char형 data 변수 선언

	char command;

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Dubug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ,&data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
	        free(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}


QueueType *createQueue()  //큐를 생성하는 함수
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));  //cQ를 동적할당해줌
	cQ->front = 0;  //front,rear 가 0을 가르키도록 해줌
	cQ->rear = 0;
	return cQ;
}

element getElement()  //문자를 넣어주는 함수
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


int isEmpty(QueueType *cQ)  //함수가 비어있는지를 확인해주는 함수
{
  	if(cQ->front==cQ->rear)  //front와 rear가 같을때 비어있음을 알려줌
   	return 1;
	else
    return 0;
}


int isFull(QueueType *cQ)   //함수가 포화되어있는지를 확인해주는 함수
{
	if((cQ->rear + 1)% MAX_QUEUE_SIZE == cQ->front)// 계산한 나머지 값이 front와 같으면 포화됨을 알려줌
	return 1;
	else
	return 0;
	
   
}

/* complete the function */
void enQueue(QueueType *cQ, element item)  //큐에 문자를 넣어주는 함수
{
	
    if(isFull(cQ))  // cQ가 포화상태인지를 확인
	printf(" FULL "); //포화상태인것을 확인하면 full을 출력
	else {cQ-> rear=(cQ->rear+1)%MAX_QUEUE_SIZE;  //그렇지 않다면, 계산한 나머지 값을 확인하고
	cQ->queue[cQ->rear] = item; //queue의 rear에 입력된 문자를 넣어줌
	}
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)  //큐에서 문자를 지워주는 함수
{
	if(isEmpty(cQ))  // cQ가 비어있는상태인지를 확인
	printf(" EMPTY ");  //포화상태인것을 확인하면 empty를 출력
	else {cQ->front=(cQ->front+1)%MAX_QUEUE_SIZE ;  //그렇지 않다면, 계산한 나머지 값을 확인하고 ( front=front+1 )
	*item=cQ->queue[cQ->front];  //queue의 front 다음에 입력된 문자를 지움
	}
}


void printQ(QueueType *cQ)  //queue를 프린트해주는 함수
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;  
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;   

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ) //queue를 디버그 해주는 함수
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)  //디버그를 for문을 사용해서 구현함
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}

