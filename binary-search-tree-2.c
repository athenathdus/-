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

	printf(" 2019038079 박소연");

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
void iterativeInorder(Node* node) //반복적 중위순회
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
void levelOrder(Node* ptr) //레벨순서 순회
{
	int front = 0;
	int rear = 0;
	Node* queue[MAX_QUEUE_SIZE];

	if (!ptr)return;  //ptr이 null이 아닐경우 return 

	enQueue(ptr);  //enqueue함수

	for(;;) {  //while(1)
		ptr = deQueue();  //queue삭제
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
	Node*parent = NULL;  //부모노드의 값을 null로 초기화
	Node*n = head->left;  //n 노드를 head의 왼쪽으로 지정
	Node*child;
	Node*a, *ap;

	while (n != NULL && n->key != key) {  //key를 갖는 노드를 탐색
		parent = n;  //부모 노드를 n값과 동일하게 두고 탐색
		n = (key < parent->key) ? parent->left : parent->right;  //t는 key 값에 따라 내려감
	}

	if (!n) {
		printf("key값이 tree내부에 없습니다.");
		return 1;
	}

	if (head->left == NULL) {  //만약 head노드 다음의 노드가 없다면 지울값이 없다고 출력
		printf("지울값이 없습니다.");
		return 1;
	}

	if (n->left == NULL && n->right == NULL) {  //만약 오른쪽 , 왼쪽 모두 null이라면 (단일노드라면)
		if (parent != NULL) {  //만약 부모노드가 null이아니면 (존재하면)
			if (parent->left == n)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
	}
	
	if ((n->left == NULL) || (n->right == NULL)) { //하나의 자식을 가질 경우
		child = (n->left != NULL) ? n->left : n->right;  //만약 n의 왼쪽이 null이 아니면 왼쪽으로 가고, 그 반대일 경우 오른쪽으로 감
		if (parent != NULL) {   //만약 부모노드가 null이 아닐경우
			if (parent->left == n)  //만약 parent의 왼쪽이 n이면, parent의 왼쪽과 child를 연결 (부모와 자식을 연결시키는 과정)
				parent->left = child;
			else //오른쪽의 경우
				parent->right = child;
		}
		else  //아니면 n=child
			n = child;
	}
	else  //두개의 자식을 가질 경우
	{
		ap = n;  //ap를 n이라 칭함
		a = n->right;  //a는 n의 오른쪽이라 칭함 (임의로)
		while (a->left != NULL) {  //a의 left가 null일때까지 반복
			ap = a;
			a = a->left;
		}  //부모와 자식 연결
		if (ap->left == a)  //ap의 왼쪽이 a 이면 연결
			ap->left = a->right;
		else  //아닐경우
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



Node* pop()  //stack 제거함수
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

void push(Node* aNode) //stack 삽입함수
{
	if (top >= MAX_STACK_SIZE - 1) 
	{ 
		return;
	}
	top++;  
	stack[top] = aNode;  

}



Node* deQueue() //큐를 삭제하는 함수
{
	Node* dnode = NULL;
	if (front == rear) {
		return dnode;
	}
	front++;
	dnode = queue[front];
	return dnode;
}

void enQueue(Node* aNode) //큐를 삽입하는 함수
{

	if (rear == MAX_QUEUE_SIZE - 1) {  
		return;
	}
	rear++; 
	queue[rear] = aNode;

}







