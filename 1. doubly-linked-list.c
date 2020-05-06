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

 /* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
		- initialize와 왜 다른지 이해 할것
		 - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */


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

    printf("2019038079 박소연\n");
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

if ((*h) != NULL)  //만약 
		freeList(*h);

	//headnode에 대한 메모리를 할당하여 리턴
	(*h) = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;
	return h;
}


int freeList(headNode* h) {  //listnode 메모리 해제는 단일연결리스트와 같다. 

	listNode* p = h->first;  //p를 h의 다음노드라 칭한다. 

	listNode* prev = NULL;  //prev라는 노드를 하나 만들어준다.
	while (p != NULL) {  //p가 null이 아닐때까지 while문이 반복된다. 
		prev = p;  //prev를 p에 넣어준다. 그러면 prev가 h->first가 된다.
		p = p->rlink;  // p를 p가 가리키는 오른쪽 링크로 옮겨준다.
		free(prev);  //prev를 해제해준다.
	}
	free(h);  //h를 해제해준다.
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
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {  

	listNode* n;
	listNode* lastnode;
	n = h->first;  //n을 h의 다음 노드라고 지정
	lastnode = (listNode*)malloc(sizeof(listNode));  //lastnode에 동적할당을 해줌
	lastnode->rlink = NULL;  //lastnode의 오른쪽링크가 null을 가리킴
	lastnode->key = key;  //lastnode의 key값에 key를 넣어줌

	if (h->first == NULL)  //만약 h의 다음 노드가 null이면
	{
		h->first = lastnode;  //h의 다음 노드에 lastnode노드를 넣어줌
	}

	while (n->rlink != NULL) {  //n의 오른쪽 링크가 null이 아니면

		n = n->rlink; //n의 값을 n이 가리키는 rlink로 바꿔줌(null이 나올때까지 계속 반복해줌)
	}

	n->rlink = lastnode;  //while문에서 빠져나왔고, n이 가리키는 rlink에다가 lastnode를 넣어줌
	return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	listNode*dlastnode;
	listNode*dn;

	if (h->first == NULL)   //만약 h의 다음 노드가 null이면 그대로 끝냄
		return;

	if (h->first->rlink == NULL) {  //h의 다음노드의 오른쪽링크가 null이면
		h->first = NULL;  //h의 first노드를 null로 연결해줌 (그 사이 삭제)
		free(h->first); //노드 메모리 해제
		return;
	}
	else {  //그렇지 않으면
		dn = h->first; // dn을 h의 다음 노드로 넣어주고
		dlastnode = h->first->rlink;  //dlastnode를 dn이 가리키는 다음링크로 설정해줌
		while (dlastnode->rlink != NULL) {  //만약 dlastnode의 다음링크가 null이 아닐경우
			dn = dlastnode; //dn에 dlastnode를 넣어줌 (뒤로 이동하는 과정)
			dlastnode = dlastnode->rlink;  //dlastnode를 dlastnode가 가리키는 다음링크로 넣어줌
		}

	}
	free(dlastnode); //노드 메모리 해제
	dn->rlink = NULL;  //dn의 링크는 null이다 (dlastnode는 삭제됨)

	return 0;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));  //node를 하나 생성해줌
	node->key = key;  //노드의 key값에 입력한 값을 넣어줌

	node->rlink = h->first;  //노드의 오른쪽 링크를 h->first가 가리키던 링크로 바꿔줌
	h->first = node;  //h의 다음 노드를 node로 지정해줌

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	listNode* tnode = h->first;  //tnode를 h의 다음노드로 설정
	h->first = tnode->rlink;  //h의 다음노드를 tnode의 링크로 설정해줌


	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	listNode* blank; //임시저장
	listNode* result; //결과를 저장
	listNode* t; //head 위치 나타내는 포인터

	t = h->first;  //변수들 초기화
	blank = NULL;
	result = NULL;

	//노드의 연결을 반대로 바꾸기
	while (t != NULL)
	{
		blank = result; //blank의 포인터를 result로 넣어줌
		result = t; //result를 t로 넣어줌
		t = t->rlink;  //포인터의 맨 앞 노드에 있던 t를 다음노드로 옮겨줌
		result->rlink = blank;  //맨 앞 노드의 링크를 뒤집은 blank에 넣어줌
	}

	h->first = result;


	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* nnode = (listNode*)malloc(sizeof(listNode));  //nnode 라는 새로운 노드를 동적할당 해줌(입력한 값이 들어갈 노드)
	nnode->key = key;  //nnode에 입력한 키 값을 넣음
	listNode*now;  //now와 trail노드를 생성(위치를 알기 위해서)
	listNode*trail;
	now = h->first;  //now와 trail에는 헤드노드 다음의 노드를 넣어줌
	trail = h->first;
	nnode->rlink = NULL;  //nnode가 가리키는 링크는 null값으로 만들어줌

	if (h->first == NULL) {  //만약 헤드노드의 다음이 null값이라면 (중간에 아무것도 없는것이기 때문에)
		h->first = nnode;  //헤드노드 다음에 nnode를 넣어줌
		return;
	}
	while (now != NULL)  //now 의 값이 null일때까지 while문이 반복됨
	{
		if (now->key >= key) {  //만약 입력한 key값이 now가 있는 key값보다 작거나 같을경우
			if (now == h->first)  //그 중에서도, now 가 헤드노드의 바로 다음 노드일 경우에
			{
				
				nnode->rlink=h->first;  //h의 다음노드를 nnode의 오른쪽 링크로 넣어줌
				
				h->first = nnode;  //h->first를 nnode로 설정해줌
				

			}

			else /*if (now->key < key)*/  //만약 작지 않다면, 
			{
				
				nnode->rlink = trail->rlink;  //trail의 rlink를 nnode의 rlink로 변경해줌
				trail->rlink = nnode;  //trail의 오른쪽 링크를 nnode로 넣어줌
			}

			return;

		}
		trail = now;  //trail 다음이 now 인 알고리즘으로 진행하기 때문에 trail에다가 now값을 넣어줌(trail이 앞으로 한칸 이동)
		now = now->rlink;  //now는 now의 오른쪽링크가 가리키는 링크로 이동 (now가 앞으로 한칸 이동)

	}
	trail->rlink = nnode;  //맨마지막에 삽입되는 경우 (trail의 링크를 nnode라 해줌)

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) {  //공백리스트일 경우
		printf("빈 리스트입니다.");
		return 0;
	}

	listNode * ppre;
	listNode * pnode;
	ppre = NULL;
	pnode = h->first;  //pnode를 헤드노드의 다음으로 넣어줌

	while (h->first != NULL)  //헤드노드의 다음 값이 null일때까지 while문이 실행
	{
		if (pnode->key == key)  //만약 pnode의 key가 입력한 key값과 같으면 
		{
			ppre->rlink = pnode->rlink;  //삭제해줌
			break;
		}
		else  //그렇지 않으면
		{
			ppre = pnode;  //자리를 옮겨줌
		}
		pnode = pnode->rlink;
	
	}
	return 1;
}