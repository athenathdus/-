
/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
 /* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* �Լ� ����Ʈ */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode = NULL;
	printf("2019038079 �ڼҿ�\n");
	do {
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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


int initialize(listNode** h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if (*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* �޸� ���� */
int freeList(listNode* h) {
	if (h->rlink == h) {  //h�� rlink�� ������� ���, �ƹ��͵� ������ �ǹ��ϹǷ� h�� ���������ش�. 
		free(h);
	}
	
	listNode* p = h->rlink;  //p�� h�� �������� Ī�Ѵ�. 

	listNode* prev = NULL;  //prev��� ��带 �ϳ� ������ش�.
	while (p != NULL  || p!=h) {  //p�� null �Ǵ� p�� h�� �ƴҶ����� while���� �ݺ��ȴ�. 
		prev = p;  //prev�� p�� �־��ش�. �׷��� prev�� h->rlink�� �ȴ�.
		p = p->rlink;  // p�� p�� ����Ű�� ������ ��ũ�� �Ű��ش�.
		free(prev);  //prev�� �������ش�.
	}
	free(h);  //h�� �������ش�.


	return 0;
}


void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}


/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key) {
	listNode* n;
	n = h->rlink;
	listNode* lastnode;
	lastnode = (listNode*)malloc(sizeof(listNode));  //lastnode�� �����Ҵ��� ����
	lastnode->rlink = NULL;  //lastnode�� rlink�� llink ��� null ������ �ʱ�ȭ
	lastnode->llink = NULL;
	lastnode->key = key;  //lastnode�� key���� key�� �־���

	if (h == NULL) {  //����, h�� null�ϰ�쿡 �����Դϴ� �޼����� ���
		printf("�����Դϴ�.");
		return 0;
	}
	 
	
		while (n->rlink != h){   //���� ������ �ƴ϶��(�߰��� ��尡 �ִٸ�)
			n = n->rlink;
		}
		
			n->rlink = lastnode;
			lastnode->llink = n;
			lastnode->rlink = h;
			h->llink = lastnode;

		return 0;
}
	

	



/**
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) {

	listNode*dlastnode;
	listNode*dn=h->rlink;

	if (h== NULL || h->rlink==h) {  //���� h�� null�̰ų� h�ۿ� ������ 
		printf(" ���� ��尡 �����ϴ�. \n");  //�����尡 ������ ���
		return 1;
	}

	if (dn->rlink == h) {  //h�� ��������� �����ʸ�ũ�� h�̸�
		h->rlink = h;  //h�� �����ʸ�ũ�� ������ �������� 
		free(dn); //��� �޸� ����
		return 1;
	}
	else {  //�׷��� ������

		dlastnode = dn->rlink;  //dlastnode�� dn�� ����Ű�� ������ũ�� ��������

		while (dlastnode->rlink != h) {  //���� dlastnode�� ������ũ�� h�� �ƴҰ��
			dn = dlastnode; //dn�� dlastnode�� �־��� (�ڷ� �̵��ϴ� ����)
			dlastnode = dlastnode->rlink;  //dlastnode�� dlastnode�� ����Ű�� ������ ��ũ�� �־���
		}
		free(dlastnode); //��� �޸� ����
		dn->rlink =h;  //dn�� �����ʸ�ũ�� ������̴� (dlastnode�� ������)

	}
	return 1;
}


/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key) {

	listNode* firstnode = (listNode*)malloc(sizeof(listNode));  //firstnode�� �ϳ� ��������
	firstnode->key = key;  //����� key���� �Է��� ���� �־���
	firstnode->llink = NULL;  //firstnode�� rlink�� llink �� ���� null�� �ʱ�ȭ����
	firstnode->rlink = NULL;

	firstnode->rlink = h->rlink;  //firstnode�� rlink���� h�� ����Ű�� ������ ������ �ٲ��� (firstnode�� �������� ����)
	h->rlink->llink = firstnode;  //h�� rlink�� llink �� ���� h�� ����Ű�� �����ʳ���� ���� ��ũ�� firstnode�� ��������  (firstnode�� ������尡 �ֹ� ����)
	firstnode->llink = h;  // firstnode�� ���� ��ũ�� ������ ����  (firstnode�� ���ʸ�ũ�� h�� ����)
	h->rlink = firstnode;  //h�� �����ʸ�ũ�� firstnode�� ���� (firstnode�� h�� �ֹ����� ����)

	return 1;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h) {


	listNode* tnode = h->rlink;  //tnode�� h�� �����ʸ�ũ�μ���
	h->rlink = tnode->rlink;  //tnode�� ����Ű�� ������ ��ũ�� h�� rlink�� �ٲ��� (����� ������ ����)
	h->rlink->rlink->llink = h; //h->rlink->rlink->llink�� h�� ���� ( ����� ������ �����ִ� ���� �Ϸ�)
	free(tnode);  //�����Ҵ� ���� tnode


	return 1;

}

/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) {

	if (h == NULL || h->rlink == h) {
		printf(" ���ġ �� ��� ����");
		return 0;
	}

	listNode* blank=h; 
	listNode* result=h; 
	listNode* t=h->rlink; //head ��ġ ��Ÿ���� ������
	
	//����� ������ �ݴ�� �ٲٱ�
	while (t != h)  //t�� h�϶����� �ݺ�
	{
		blank = result; //blank�� �����͸� result�� �־���
		result = t; //result�� t�� �־���
		t = t->rlink;  //�������� �� �� ��忡 �ִ� t�� �������� �Ű���
		result->rlink = blank; //result�� �����ʸ�ũ�� blank�� ����
		result->llink = t;//result�� ���ʸ�ũ�� t�� ����
	}
	;
	h->rlink= result; //h�� �����ʸ�ũ�� result
	return 0;

}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(listNode* h, int key) {

	listNode* nnode = (listNode*)malloc(sizeof(listNode));  //nnode ��� ���ο� ��带 �����Ҵ� ����(�Է��� ���� �� ���)
	nnode->key = key;  //nnode�� �Է��� Ű ���� ����
	listNode*now;  //now�� trail��带 ����(��ġ�� �˱� ���ؼ�)
	listNode*trail;
	now = h->rlink;  //now�� trail���� ������� �����ʸ�ũ
	trail = h->rlink;
	nnode->rlink = NULL;  //nnode�� ����Ű�� ��ũ�� null������ �������
	nnode->llink = NULL;

	
	if (h->rlink == h) {  //���� h�� �����ʸ�ũ�� h��� 
		
		h->rlink = nnode;  //h�� ������ ��ũ�� nnode�� ����
		nnode->llink = h;  //nnode�� ���ʸ�ũ�� h�� ����
		nnode->rlink = h;   //nnode�� �����ʸ�ũ�� h�� ����
		h->llink = nnode;  //h�� ���ʸ�ũ�� nnode�� ����
		
		
		return 1;
	}

	while (now!=h)  //now �� ���� h�϶����� while���� �ݺ���
	{
		if (now->key >= key) {  //���� �Է��� key���� now�� �ִ� key������ �۰ų� �������
			if (now == h->rlink)  //�� �߿�����, now �� ������� �ٷ� ���� ����� ��쿡
			{
				nnode->rlink =now;  
				now->llink = nnode;
				h->rlink = nnode;  
				nnode->llink = h;
			}

			else /*if (now->key < key)*/  //���� ���� �ʴٸ�, 
			{
				nnode->rlink =now; 
				now->llink = nnode;
				trail->rlink = nnode;
				nnode->llink = trail;
			}

			return 1;

		}
		trail = now;  //trail ������ now �� �˰������� �����ϱ� ������ trail���ٰ� now���� �־���(trail�� ������ ��ĭ �̵�)
		now = now->rlink;  //now�� now�� �����ʸ�ũ�� ����Ű�� ��ũ�� �̵� (now�� ������ ��ĭ �̵�)

	}
	trail->rlink = nnode;  //�Ǹ������� ���ԵǴ� ��� (trail�� ��ũ�� nnode�� ����)
	nnode->rlink = h; //nnode�� �����ʸ�ũ�� h�� Ī��


	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {

	if (h->rlink == h) {  //���鸮��Ʈ�� ���
		printf("�� ����Ʈ�Դϴ�.");
		return 0;
	}

	listNode * ppre;
	listNode * pnode;
	
	pnode = h->rlink;  //pnode�� ������� �������� �־���
	ppre = pnode->rlink;  //ppre�� pnode�� �����ʸ�ũ�� ����
	while (pnode->rlink != h || pnode->rlink != NULL)  //pnode�� �����ʸ�ũ�� h�� �ƴϰų� pnode�� �����ʸ�ũ�� null�϶����� �ݺ�
	{
		if (pnode->key == key)  //���� pnode�� key�� �Է��� key���� ������ 
		{
			if (pnode == h->rlink) {  //pnode�� h->rlink���, 
				h->rlink = pnode->rlink;
				pnode->rlink->llink = h;
				free(pnode);
			}

			else  //�׷��� ���� ����϶�, 
			{
				pnode->llink->rlink = ppre->rlink;
				ppre->rlink->llink = pnode->llink;
				free(ppre);
			}
			return 0;
		}

		deleteLast(h);   //������ ��� ���� 
	}
		pnode = pnode->rlink;  //pnode�� �ڸ� �̵�
		
	
	return 0;
}
	

