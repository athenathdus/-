/*
 * circularQ.c
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4  //MAX_QUEUE_SIZE�� 4�� ����

typedef char element;  //char�� ��Ī element�� ����
typedef struct {
	element queue[MAX_QUEUE_SIZE];  //queue�� ����
	int front, rear;
}QueueType;  //��Ī�� QueueType�� ����ü ����


QueueType *createQueue();
int isEmpty(QueueType *cQ); //��������� ��Ÿ���� �Լ�
int isFull(QueueType *cQ);  //�� �������� ��Ÿ���� �Լ�
void enQueue(QueueType *cQ, element item);  //ť�� �ִ� �Լ�
void deQueue(QueueType *cQ, element* item);  //ť���� ���� �Լ�
void printQ(QueueType *cQ);  //ť�� ����Ʈ�ϴ� �Լ�	
void debugQ(QueueType *cQ);  //ť�� ������ϴ� �Լ�
element getElement();  //char�� �̱� ������ element�� ����


int main(void)
{
	printf("2019038079 �ڼҿ�");
	QueueType *cQ = createQueue();  //*cQ�� �����Ҵ� ����
	element data;  //char�� data ���� ����

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


QueueType *createQueue()  //ť�� �����ϴ� �Լ�
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));  //cQ�� �����Ҵ�����
	cQ->front = 0;  //front,rear �� 0�� ����Ű���� ����
	cQ->rear = 0;
	return cQ;
}

element getElement()  //���ڸ� �־��ִ� �Լ�
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


int isEmpty(QueueType *cQ)  //�Լ��� ����ִ����� Ȯ�����ִ� �Լ�
{
  	if(cQ->front==cQ->rear)  //front�� rear�� ������ ��������� �˷���
   	return 1;
	else
    return 0;
}


int isFull(QueueType *cQ)   //�Լ��� ��ȭ�Ǿ��ִ����� Ȯ�����ִ� �Լ�
{
	if((cQ->rear + 1)% MAX_QUEUE_SIZE == cQ->front)// ����� ������ ���� front�� ������ ��ȭ���� �˷���
	return 1;
	else
	return 0;
	
   
}

/* complete the function */
void enQueue(QueueType *cQ, element item)  //ť�� ���ڸ� �־��ִ� �Լ�
{
	
    if(isFull(cQ))  // cQ�� ��ȭ���������� Ȯ��
	printf(" FULL "); //��ȭ�����ΰ��� Ȯ���ϸ� full�� ���
	else {cQ-> rear=(cQ->rear+1)%MAX_QUEUE_SIZE;  //�׷��� �ʴٸ�, ����� ������ ���� Ȯ���ϰ�
	cQ->queue[cQ->rear] = item; //queue�� rear�� �Էµ� ���ڸ� �־���
	}
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)  //ť���� ���ڸ� �����ִ� �Լ�
{
	if(isEmpty(cQ))  // cQ�� ����ִ»��������� Ȯ��
	printf(" EMPTY ");  //��ȭ�����ΰ��� Ȯ���ϸ� empty�� ���
	else {cQ->front=(cQ->front+1)%MAX_QUEUE_SIZE ;  //�׷��� �ʴٸ�, ����� ������ ���� Ȯ���ϰ� ( front=front+1 )
	*item=cQ->queue[cQ->front];  //queue�� front ������ �Էµ� ���ڸ� ����
	}
}


void printQ(QueueType *cQ)  //queue�� ����Ʈ���ִ� �Լ�
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


void debugQ(QueueType *cQ) //queue�� ����� ���ִ� �Լ�
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)  //����׸� for���� ����ؼ� ������
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}

