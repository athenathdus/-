/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */

#include<stdio.h>
#include<stdlib.h>

 /* �ʿ��� ������� �߰� if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;

/* �Լ� ����Ʈ */
int initialize(headNode** h);

/* note: freeList�� �̱������͸� �Ű������� ����
		- initialize�� �� �ٸ��� ���� �Ұ�
		 - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */


int freeList(headNode* h);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);
void printList(headNode* h);


int main()
{

    printf("2019038079 �ڼҿ�\n");
	char command;
	int key;
	headNode* headnode = NULL;

	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
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
			initialize(&headnode);
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


int initialize(headNode** h) {

if ((*h) != NULL)  //���� 
		freeList(*h);

	//headnode�� ���� �޸𸮸� �Ҵ��Ͽ� ����
	(*h) = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;
	return h;
}


int freeList(headNode* h) {  //listnode �޸� ������ ���Ͽ��Ḯ��Ʈ�� ����. 

	listNode* p = h->first;  //p�� h�� �������� Ī�Ѵ�. 

	listNode* prev = NULL;  //prev��� ��带 �ϳ� ������ش�.
	while (p != NULL) {  //p�� null�� �ƴҶ����� while���� �ݺ��ȴ�. 
		prev = p;  //prev�� p�� �־��ش�. �׷��� prev�� h->first�� �ȴ�.
		p = p->rlink;  // p�� p�� ����Ű�� ������ ��ũ�� �Ű��ش�.
		free(prev);  //prev�� �������ش�.
	}
	free(h);  //h�� �������ش�.
	return 0;
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
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}

/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {  

	listNode* n;
	listNode* lastnode;
	n = h->first;  //n�� h�� ���� ����� ����
	lastnode = (listNode*)malloc(sizeof(listNode));  //lastnode�� �����Ҵ��� ����
	lastnode->rlink = NULL;  //lastnode�� �����ʸ�ũ�� null�� ����Ŵ
	lastnode->key = key;  //lastnode�� key���� key�� �־���

	if (h->first == NULL)  //���� h�� ���� ��尡 null�̸�
	{
		h->first = lastnode;  //h�� ���� ��忡 lastnode��带 �־���
	}

	while (n->rlink != NULL) {  //n�� ������ ��ũ�� null�� �ƴϸ�

		n = n->rlink; //n�� ���� n�� ����Ű�� rlink�� �ٲ���(null�� ���ö����� ��� �ݺ�����)
	}

	n->rlink = lastnode;  //while������ �������԰�, n�� ����Ű�� rlink���ٰ� lastnode�� �־���
	return 0;
}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {

	listNode*dlastnode;
	listNode*dn;

	if (h->first == NULL)   //���� h�� ���� ��尡 null�̸� �״�� ����
		return;

	if (h->first->rlink == NULL) {  //h�� ��������� �����ʸ�ũ�� null�̸�
		h->first = NULL;  //h�� first��带 null�� �������� (�� ���� ����)
		free(h->first); //��� �޸� ����
		return;
	}
	else {  //�׷��� ������
		dn = h->first; // dn�� h�� ���� ���� �־��ְ�
		dlastnode = h->first->rlink;  //dlastnode�� dn�� ����Ű�� ������ũ�� ��������
		while (dlastnode->rlink != NULL) {  //���� dlastnode�� ������ũ�� null�� �ƴҰ��
			dn = dlastnode; //dn�� dlastnode�� �־��� (�ڷ� �̵��ϴ� ����)
			dlastnode = dlastnode->rlink;  //dlastnode�� dlastnode�� ����Ű�� ������ũ�� �־���
		}

	}
	free(dlastnode); //��� �޸� ����
	dn->rlink = NULL;  //dn�� ��ũ�� null�̴� (dlastnode�� ������)

	return 0;
}


/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));  //node�� �ϳ� ��������
	node->key = key;  //����� key���� �Է��� ���� �־���

	node->rlink = h->first;  //����� ������ ��ũ�� h->first�� ����Ű�� ��ũ�� �ٲ���
	h->first = node;  //h�� ���� ��带 node�� ��������

	return 0;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {

	listNode* tnode = h->first;  //tnode�� h�� �������� ����
	h->first = tnode->rlink;  //h�� ������带 tnode�� ��ũ�� ��������


	return 0;
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {

	listNode* blank; //�ӽ�����
	listNode* result; //����� ����
	listNode* t; //head ��ġ ��Ÿ���� ������

	t = h->first;  //������ �ʱ�ȭ
	blank = NULL;
	result = NULL;

	//����� ������ �ݴ�� �ٲٱ�
	while (t != NULL)
	{
		blank = result; //blank�� �����͸� result�� �־���
		result = t; //result�� t�� �־���
		t = t->rlink;  //�������� �� �� ��忡 �ִ� t�� �������� �Ű���
		result->rlink = blank;  //�� �� ����� ��ũ�� ������ blank�� �־���
	}

	h->first = result;


	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {

	listNode* nnode = (listNode*)malloc(sizeof(listNode));  //nnode ��� ���ο� ��带 �����Ҵ� ����(�Է��� ���� �� ���)
	nnode->key = key;  //nnode�� �Է��� Ű ���� ����
	listNode*now;  //now�� trail��带 ����(��ġ�� �˱� ���ؼ�)
	listNode*trail;
	now = h->first;  //now�� trail���� ����� ������ ��带 �־���
	trail = h->first;
	nnode->rlink = NULL;  //nnode�� ����Ű�� ��ũ�� null������ �������

	if (h->first == NULL) {  //���� ������� ������ null���̶�� (�߰��� �ƹ��͵� ���°��̱� ������)
		h->first = nnode;  //����� ������ nnode�� �־���
		return;
	}
	while (now != NULL)  //now �� ���� null�϶����� while���� �ݺ���
	{
		if (now->key >= key) {  //���� �Է��� key���� now�� �ִ� key������ �۰ų� �������
			if (now == h->first)  //�� �߿�����, now �� ������� �ٷ� ���� ����� ��쿡
			{
				
				nnode->rlink=h->first;  //h�� ������带 nnode�� ������ ��ũ�� �־���
				
				h->first = nnode;  //h->first�� nnode�� ��������
				

			}

			else /*if (now->key < key)*/  //���� ���� �ʴٸ�, 
			{
				
				nnode->rlink = trail->rlink;  //trail�� rlink�� nnode�� rlink�� ��������
				trail->rlink = nnode;  //trail�� ������ ��ũ�� nnode�� �־���
			}

			return;

		}
		trail = now;  //trail ������ now �� �˰������� �����ϱ� ������ trail���ٰ� now���� �־���(trail�� ������ ��ĭ �̵�)
		now = now->rlink;  //now�� now�� �����ʸ�ũ�� ����Ű�� ��ũ�� �̵� (now�� ������ ��ĭ �̵�)

	}
	trail->rlink = nnode;  //�Ǹ������� ���ԵǴ� ��� (trail�� ��ũ�� nnode�� ����)

	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
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
			ppre->rlink = pnode->rlink;  //��������
			break;
		}
		else  //�׷��� ������
		{
			ppre = pnode;  //�ڸ��� �Ű���
		}
		pnode = pnode->rlink;
	
	}
	return 1;
}