/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */



int main()
{
	char command;
	int key;
	Node* head = NULL;

	printf(" 2019038079 �ڼҿ�");

	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}

void recursiveInorder(Node* ptr)
{
	if (ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node) //�ݺ��� ������ȸ
{
	int top = -1;
	Node* stack[MAX_STACK_SIZE];
	for (;;) {
		for (; node; node = node->left)
			push(node);
		node = pop();

		if (!node)break;

		printf(" [%d] ", node->key);
		node = node->right;
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr) //�������� ��ȸ
{
	int front = 0;
	int rear = 0;
	Node* queue[MAX_QUEUE_SIZE];

	if (!ptr)return;  //ptr�� null�� �ƴҰ�� return 

	enQueue(ptr);  //enqueue�Լ�

	for(;;) {  //while(1)
		ptr = deQueue();  //queue����
		if (ptr) {
			printf(" [%d] ", ptr->key);
			if (ptr->left)
				enQueue(ptr->left);
			if (ptr->right)
				enQueue(ptr->right);
		}
		else break;
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while (ptr != NULL) {

		/* if there is a node for the key, then just return */
		if (ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if (parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	Node*parent = NULL;  //�θ����� ���� null�� �ʱ�ȭ
	Node*n = head->left;  //n ��带 head�� �������� ����
	Node*child;
	Node*a, *ap;

	while (n != NULL && n->key != key) {  //key�� ���� ��带 Ž��
		parent = n;  //�θ� ��带 n���� �����ϰ� �ΰ� Ž��
		n = (key < parent->key) ? parent->left : parent->right;  //t�� key ���� ���� ������
	}

	if (!n) {
		printf("key���� tree���ο� �����ϴ�.");
		return 1;
	}

	if (head->left == NULL) {  //���� head��� ������ ��尡 ���ٸ� ���ﰪ�� ���ٰ� ���
		printf("���ﰪ�� �����ϴ�.");
		return 1;
	}

	if (n->left == NULL && n->right == NULL) {  //���� ������ , ���� ��� null�̶�� (���ϳ����)
		if (parent != NULL) {  //���� �θ��尡 null�̾ƴϸ� (�����ϸ�)
			if (parent->left == n)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
	}
	
	if ((n->left == NULL) || (n->right == NULL)) { //�ϳ��� �ڽ��� ���� ���
		child = (n->left != NULL) ? n->left : n->right;  //���� n�� ������ null�� �ƴϸ� �������� ����, �� �ݴ��� ��� ���������� ��
		if (parent != NULL) {   //���� �θ��尡 null�� �ƴҰ��
			if (parent->left == n)  //���� parent�� ������ n�̸�, parent�� ���ʰ� child�� ���� (�θ�� �ڽ��� �����Ű�� ����)
				parent->left = child;
			else //�������� ���
				parent->right = child;
		}
		else  //�ƴϸ� n=child
			n = child;
	}
	else  //�ΰ��� �ڽ��� ���� ���
	{
		ap = n;  //ap�� n�̶� Ī��
		a = n->right;  //a�� n�� �������̶� Ī�� (���Ƿ�)
		while (a->left != NULL) {  //a�� left�� null�϶����� �ݺ�
			ap = a;
			a = a->left;
		}  //�θ�� �ڽ� ����
		if (ap->left == a)  //ap�� ������ a �̸� ����
			ap->left = a->right;
		else  //�ƴҰ��
			ap->right = a->right;

		n->key = a->key;  
		n = a;
	}
	
}




void freeNode(Node* ptr)
{
	if (ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if (head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()  //stack �����Լ�
{
	Node* node = NULL;
	if (top == -1)
	{ 
		return node;
	} 
	node = stack[top]; 
	top--;
	return node;

}

void push(Node* aNode) //stack �����Լ�
{
	if (top >= MAX_STACK_SIZE - 1) 
	{ 
		return;
	}
	top++;  
	stack[top] = aNode;  

}



Node* deQueue() //ť�� �����ϴ� �Լ�
{
	Node* dnode = NULL;
	if (front == rear) {
		return dnode;
	}
	front++;
	dnode = queue[front];
	return dnode;
}

void enQueue(Node* aNode) //ť�� �����ϴ� �Լ�
{

	if (rear == MAX_QUEUE_SIZE - 1) {  
		return;
	}
	rear++; 
	queue[rear] = aNode;

}







