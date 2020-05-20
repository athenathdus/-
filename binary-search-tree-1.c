/*
 * Binary Search Tree #1
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

int initializeBST(Node** h);

void inorderTraversal(Node* ptr);     /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);     /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;   /* temp */
	printf("2019038079 박소연 ");
	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
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
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
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
	(*h)->left = NULL;   /* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}

void inorderTraversal(Node* ptr)  //전위순회
{
	if (ptr != NULL) {//부모노드->왼쪽 자식노드->오른쪽 자식노드
		inorderTraversal(ptr->left);
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

void preorderTraversal(Node* ptr) //중위순회
{
	if (ptr != NULL) { //왼쪽 자식노드->부모노드->오른쪽 자식노드
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr)  //후위순회
{
	if (ptr != NULL) {  //왼쪽 자식노드->오른쪽 자식노드->부모노드
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);
	}
}

int insert(Node* head, int key)
{
	Node *newnode = (Node*)malloc(sizeof(Node));  //newnode를 만들어 동적할당
	Node *n = head->left;  //n노드를 생성해 head의 왼쪽노드로 지정 
	newnode->right = NULL;  //newnode의 왼쪽, 오른쪽 노드를 null로 초기화
	newnode->left = NULL;
	newnode->key = key;  

	if (head->left == NULL) {  //만약 head노드의 왼쪽노드가 null 값일경우(아무 노드도 없을경우)
		head->left = newnode;  //head의 왼쪽노드에 newnode를 연결
		return 0;
	}
	
	while (1) {
		if (n->key < key){  //만약 입력한 key값이 지정된 key값보다 작을경우
			if (n->right == NULL) {  //n의 오른쪽 노드가 null이면 
				n->right = newnode;  //n의 오른쪽 노드를 newnode로 지정 
			}
			n = n->right; //n을 이동시킴
		}
		else if(n->key>key){  //클경우
			if (n->left == NULL){  //n의 왼쪽 노드가 null일경우
				n->left = newnode;  //n의 왼쪽 노드를 newnode로 지정 
			}
			n = n->left;  //n을 이동시킴
		}
		else {//같을 경우 return 1
			if (n->key == key)
				return 1;
		}
	}
	return 0;
}
	
int deleteLeafNode(Node* head, int key)
{   
	Node*parent = NULL;  //부모노드의 값을 null로 초기화
	Node*n = head->left;  //n 노드를 head의 왼쪽으로 지정
	

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
	else  //단일노드가 아닐경우 메세지 출력
		printf(" 삭제가 불가능합니다. ");
		return 1;
	}

Node* searchRecursive(Node* ptr, int key)
{

	if (ptr== NULL)   //ptr이 null일경우, null값을 반환
		return NULL;

	if (key == ptr->key)  //원하는 값일 경우 ptr을 리턴
		return ptr; 
	else if (key < ptr->key)  //찾는 값 보다 클경우 오른쪽으로 이동 
		return searchRecursive(ptr->left, key);
	else  //그렇지 않으면 왼쪽으로 이동 
		return searchRecursive(ptr->right, key);
	
}

Node* searchIterative(Node* head, int key)
{
	Node *n = head->left;  //n노드 생성 (head의 왼쪽노드)

	while ( n != NULL) {  //n이null이 아닐때
		if (key == n->key)  //원하는 값 발견하면 n을 return 
			return  n;
		else if (key <n->key)  //값이 더 큰경우 왼쪽으로 이동 
			n = n->left;
		else  //작을경우 오른쪽으로 이동 
			n= n->right;
	}
	return NULL;

}

int freeBST(Node* head)  //동적할당 메모리 해제 
{
	if (head == NULL)
		return 0;
	if (head->left == NULL)
		return 0;
	
	freeBST(head->left);
	freeBST(head->right);
	free(head);

}



