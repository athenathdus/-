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
	printf("2019038079 �ڼҿ� ");
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

void inorderTraversal(Node* ptr)  //������ȸ
{
	if (ptr != NULL) {//�θ���->���� �ڽĳ��->������ �ڽĳ��
		inorderTraversal(ptr->left);
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

void preorderTraversal(Node* ptr) //������ȸ
{
	if (ptr != NULL) { //���� �ڽĳ��->�θ���->������ �ڽĳ��
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr)  //������ȸ
{
	if (ptr != NULL) {  //���� �ڽĳ��->������ �ڽĳ��->�θ���
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);
	}
}

int insert(Node* head, int key)
{
	Node *newnode = (Node*)malloc(sizeof(Node));  //newnode�� ����� �����Ҵ�
	Node *n = head->left;  //n��带 ������ head�� ���ʳ��� ���� 
	newnode->right = NULL;  //newnode�� ����, ������ ��带 null�� �ʱ�ȭ
	newnode->left = NULL;
	newnode->key = key;  

	if (head->left == NULL) {  //���� head����� ���ʳ�尡 null ���ϰ��(�ƹ� ��嵵 �������)
		head->left = newnode;  //head�� ���ʳ�忡 newnode�� ����
		return 0;
	}
	
	while (1) {
		if (n->key < key){  //���� �Է��� key���� ������ key������ �������
			if (n->right == NULL) {  //n�� ������ ��尡 null�̸� 
				n->right = newnode;  //n�� ������ ��带 newnode�� ���� 
			}
			n = n->right; //n�� �̵���Ŵ
		}
		else if(n->key>key){  //Ŭ���
			if (n->left == NULL){  //n�� ���� ��尡 null�ϰ��
				n->left = newnode;  //n�� ���� ��带 newnode�� ���� 
			}
			n = n->left;  //n�� �̵���Ŵ
		}
		else {//���� ��� return 1
			if (n->key == key)
				return 1;
		}
	}
	return 0;
}
	
int deleteLeafNode(Node* head, int key)
{   
	Node*parent = NULL;  //�θ����� ���� null�� �ʱ�ȭ
	Node*n = head->left;  //n ��带 head�� �������� ����
	

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
	else  //���ϳ�尡 �ƴҰ�� �޼��� ���
		printf(" ������ �Ұ����մϴ�. ");
		return 1;
	}

Node* searchRecursive(Node* ptr, int key)
{

	if (ptr== NULL)   //ptr�� null�ϰ��, null���� ��ȯ
		return NULL;

	if (key == ptr->key)  //���ϴ� ���� ��� ptr�� ����
		return ptr; 
	else if (key < ptr->key)  //ã�� �� ���� Ŭ��� ���������� �̵� 
		return searchRecursive(ptr->left, key);
	else  //�׷��� ������ �������� �̵� 
		return searchRecursive(ptr->right, key);
	
}

Node* searchIterative(Node* head, int key)
{
	Node *n = head->left;  //n��� ���� (head�� ���ʳ��)

	while ( n != NULL) {  //n��null�� �ƴҶ�
		if (key == n->key)  //���ϴ� �� �߰��ϸ� n�� return 
			return  n;
		else if (key <n->key)  //���� �� ū��� �������� �̵� 
			n = n->left;
		else  //������� ���������� �̵� 
			n= n->right;
	}
	return NULL;

}

int freeBST(Node* head)  //�����Ҵ� �޸� ���� 
{
	if (head == NULL)
		return 0;
	if (head->left == NULL)
		return 0;
	
	freeBST(head->left);
	freeBST(head->right);
	free(head);

}



