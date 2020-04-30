/*
 * single linked list
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>

 //�ʿ��� ������� �߰� 
typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


//�Լ� ����Ʈ
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode = NULL;

	printf(" 2019038079 �ڼҿ� \n");
	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	//headnode�� null�� �ƴϸ� freenode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ����
	if (h != NULL)
		freeList(h);

	//headnode�� ���� �޸𸮸� �Ҵ��Ͽ� ����
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h) {
	//h�� ����� listnode �޸� ����
	//headnode�� �����Ǿ����
	listNode* p = h->first;

	listNode* prev = NULL;
	while (p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}

int insertFirst(headNode* h, int key) {
	//listó���� key�� ���� ��� �ϳ��� �߰�
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


//����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ����
int insertNode(headNode* h, int key) {

	listNode* nnode = (listNode*)malloc(sizeof(listNode));  //nnode ��� ���ο� ��带 �����Ҵ� ����(�Է��� ���� �� ���)
	nnode->key = key;  //nnode�� �Է��� Ű ���� ����
	listNode*now;  //now�� trail��带 ����(��ġ�� �˱� ���ؼ�)
	listNode*trail;
	now = h->first;  //now�� trail���� ����� ������ ��带 �־���
	trail = h->first;
	nnode->link = NULL;  //nnode�� ����Ű�� ��ũ�� null������ �������
	
	if (h->first == NULL) {  //���� ������� ������ null���̶�� (�߰��� �ƹ��͵� ���°��̱� ������)
		h->first = nnode;  //����� ������ nnode�� �־���
		return;
	}
	while (now != NULL)  //now �� ���� null�϶����� while���� �ݺ���
	{
		if (now->key >= key) {  //���� �Է��� key���� now�� �ִ� key������ �۰ų� �������
			if (now == h->first)  //�� �߿�����, now �� ������� �ٷ� ���� ����� ��쿡
			{
				nnode->link = now;  //nnode�� ��ũ�� now�� �������ְ�
				h->first = nnode;  //����� ������ ��带 nnode�� �־���

			}

			else /*if (now->key < key)*/  //���� ���� �ʴٸ�, 
			{
				nnode->link = trail->link;  //nnode�� ��ũ�� trail�� ����Ű�� �ִ� ��ũ�� �ٲ��ְ� 
				trail->link = nnode;  //trail�� ��ũ�� nnode�� ��������
			}

			return;

		}
			trail = now;  //trail ������ now �� �˰������� �����ϱ� ������ trail���ٰ� now���� �־���(trail�� ������ ��ĭ �̵�)
			now = now->link;  //now�� now�� ����Ű�� ��ũ�� �̵� (now�� ������ ��ĭ �̵�)
		
	} 
	trail->link = nnode;  //�Ǹ������� ���ԵǴ� ��� (trail�� ��ũ�� nnode�� ����)
	
	return 0;
	
}

//list�� key�� ���� ��� �ϳ��� �߰� 
int insertLast(headNode* h, int key) {
	
	listNode* n;
	listNode* lastnode;
	n = h->first;  //n�� h�� ���� ����� ����
	lastnode = (listNode*)malloc(sizeof(listNode));  //lastnode�� �����Ҵ��� ����
	lastnode->link = NULL;  //lastnode�� ��ũ�� null�� ����Ŵ
	lastnode->key = key;  //lastnode�� key���� key�� �־���
	
	if (h->first==NULL)  //���� h�� ���� ��尡 null�̸�
	{        
		h->first = lastnode;  //h�� ���� ��忡 lastnode��带 �־���
	}
	
	while (n->link != NULL) {  //n�� ��ũ�� null�� �ƴϸ�

		n = n->link; //n�� ���� n�� ����Ű�� link�� �ٲ���(null�� ���ö����� ��� �ݺ�����)
	}

		n->link = lastnode;  //while������ �������԰�, n�� ����Ű�� link���ٰ� lastnode�� �־���
	
}

//list�� ù��° ��� ����  
int deleteFirst(headNode* h) {

	listNode* tnode = h->first;  //tnode�� h�� �������� ����
	h->first = tnode->link;  //h�� ������带 tnode�� ��ũ�� ��������
		
	return 0;
		}

//list���� key �� ���� ��� ����
int deleteNode(headNode* h, int key) {


	if (h->first == NULL) {  //���鸮��Ʈ�� ���
		printf("�� ����Ʈ�Դϴ�.");
		return 0;
	}

	listNode * ppre;
	listNode * pnode;
	ppre = NULL; 
	pnode = h->first;  //pnode�� ������� �������� �־���

	while (h->first != NULL)  //������� ���� ���� null�϶����� while���� ����
	{
		if (pnode->key == key)  //���� pnode�� key�� �Է��� key���� ������ 
		{
			ppre->link = pnode->link;  //��������
			break;
		}
		else  //�׷��� ������
		{
			ppre = pnode;  //�ڸ��� �Ű���
		}
		pnode = pnode->link; 
	}
}

//list�� ������ ��� ����  
int deleteLast(headNode* h) {

	listNode*dlastnode;
	listNode*dn;

	if (h->first == NULL)   //���� h�� ���� ��尡 null�̸� �״�� ����
		return;

	if(h->first->link == NULL) {  //h�� ��������� ��ũ�� null�̸�
		h->first = NULL;  //h�� first��带 null�� �������� (�� ���� ����)
		free(h->first); //��� �޸� ����
		return;
	}
	else {  //�׷��� ������
		dn = h->first; // dn�� h�� ���� ���� �־��ְ�
		dlastnode = h->first->link;  //dlastnode�� dn�� ����Ű�� ��ũ�� ��������
		while (dlastnode->link != NULL) {  //���� dlastnode�� ��ũ�� null�� �ƴҰ��
			dn = dlastnode; //dn�� dlastnode�� �־��� (�ڷ� �̵��ϴ� ����)
			dlastnode = dlastnode->link;  //dlastnode�� dlastnode�� ����Ű�� ��ũ�� �־���
		}
		 
	}
	free(dlastnode); //��� �޸� ����
	dn->link = NULL;  //dn�� ��ũ�� null�̴� (dlastnode�� ������)
}

//����Ʈ�� ��ũ�� �������� ���ġ 
int invertList(headNode* h) {

	
	listNode* blank; //�ӽ�����
	listNode* result; //����� ����
	listNode* t; //head ��ġ ��Ÿ���� ������

	t = h->first;  //������ �ʱ�ȭ
	blank = NULL;  
	result = NULL;

	//����� ������ �ݴ�� �ٲٱ�
	while (t!= NULL)
	{
		blank = result; //blank�� �����͸� result�� �־���
		result = t; //result�� p�� �־���
		t = t->link;  //�������� �� �� ��忡 �ִ� p�� �������� �Ű���
		result->link = blank;  //�� �� ����� ��ũ�� ������ blank�� �־���
	}

	h->first = result;
	}

			
void printList(headNode* h) {
				int i = 0;
				listNode* p;

				printf("\n---PRINT\n");

				if (h == NULL) {
					printf("Nothing to print....\n");
					return;
				}

				p = h->first;

				while (p != NULL) {
					printf("[ [%d]=%d ] ", i, p->key);
					p = p->link;
					i++;
				}

				printf("  items = %d\n", i);
			}
