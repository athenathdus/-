/*
 * single linked list
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>

 //필요한 헤더파일 추가 
typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


//함수 리스트
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

	printf(" 2019038079 박소연 \n");
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

	//headnode가 null이 아니면 freenode를 호출하여 할당된 메모리 모두 해제
	if (h != NULL)
		freeList(h);

	//headnode에 대한 메모리를 할당하여 리턴
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h) {
	//h와 연결된 listnode 메모리 해제
	//headnode도 해제되어야함
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
	//list처음에 key에 대한 노드 하나를 추가
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


//리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
int insertNode(headNode* h, int key) {

	listNode* nnode = (listNode*)malloc(sizeof(listNode));  //nnode 라는 새로운 노드를 동적할당 해줌(입력한 값이 들어갈 노드)
	nnode->key = key;  //nnode에 입력한 키 값을 넣음
	listNode*now;  //now와 trail노드를 생성(위치를 알기 위해서)
	listNode*trail;
	now = h->first;  //now와 trail에는 헤드노드 다음의 노드를 넣어줌
	trail = h->first;
	nnode->link = NULL;  //nnode가 가리키는 링크는 null값으로 만들어줌
	
	if (h->first == NULL) {  //만약 헤드노드의 다음이 null값이라면 (중간에 아무것도 없는것이기 때문에)
		h->first = nnode;  //헤드노드 다음에 nnode를 넣어줌
		return;
	}
	while (now != NULL)  //now 의 값이 null일때까지 while문이 반복됨
	{
		if (now->key >= key) {  //만약 입력한 key값이 now가 있는 key값보다 작거나 같을경우
			if (now == h->first)  //그 중에서도, now 가 헤드노드의 바로 다음 노드일 경우에
			{
				nnode->link = now;  //nnode의 링크를 now에 연결해주고
				h->first = nnode;  //헤드노드 다음의 노드를 nnode로 넣어줌

			}

			else /*if (now->key < key)*/  //만약 작지 않다면, 
			{
				nnode->link = trail->link;  //nnode의 링크를 trail이 가리키고 있는 링크로 바꿔주고 
				trail->link = nnode;  //trail의 링크는 nnode로 연결해줌
			}

			return;

		}
			trail = now;  //trail 다음이 now 인 알고리즘으로 진행하기 때문에 trail에다가 now값을 넣어줌(trail이 앞으로 한칸 이동)
			now = now->link;  //now는 now가 가리키는 링크로 이동 (now가 앞으로 한칸 이동)
		
	} 
	trail->link = nnode;  //맨마지막에 삽입되는 경우 (trail의 링크를 nnode라 해줌)
	
	return 0;
	
}

//list에 key에 대한 노드 하나를 추가 
int insertLast(headNode* h, int key) {
	
	listNode* n;
	listNode* lastnode;
	n = h->first;  //n을 h의 다음 노드라고 지정
	lastnode = (listNode*)malloc(sizeof(listNode));  //lastnode에 동적할당을 해줌
	lastnode->link = NULL;  //lastnode의 링크가 null을 가리킴
	lastnode->key = key;  //lastnode의 key값에 key를 넣어줌
	
	if (h->first==NULL)  //만약 h의 다음 노드가 null이면
	{        
		h->first = lastnode;  //h의 다음 노드에 lastnode노드를 넣어줌
	}
	
	while (n->link != NULL) {  //n의 링크가 null이 아니면

		n = n->link; //n의 값을 n이 가리키는 link로 바꿔줌(null이 나올때까지 계속 반복해줌)
	}

		n->link = lastnode;  //while문에서 빠져나왔고, n이 가리키는 link에다가 lastnode를 넣어줌
	
}

//list의 첫번째 노드 삭제  
int deleteFirst(headNode* h) {

	listNode* tnode = h->first;  //tnode를 h의 다음노드로 설정
	h->first = tnode->link;  //h의 다음노드를 tnode의 링크로 설정해줌
		
	return 0;
		}

//list에서 key 에 대한 노드 삭제
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
			ppre->link = pnode->link;  //삭제해줌
			break;
		}
		else  //그렇지 않으면
		{
			ppre = pnode;  //자리를 옮겨줌
		}
		pnode = pnode->link; 
	}
}

//list의 마지막 노드 삭제  
int deleteLast(headNode* h) {

	listNode*dlastnode;
	listNode*dn;

	if (h->first == NULL)   //만약 h의 다음 노드가 null이면 그대로 끝냄
		return;

	if(h->first->link == NULL) {  //h의 다음노드의 링크가 null이면
		h->first = NULL;  //h의 first노드를 null로 연결해줌 (그 사이 삭제)
		free(h->first); //노드 메모리 해제
		return;
	}
	else {  //그렇지 않으면
		dn = h->first; // dn을 h의 다음 노드로 넣어주고
		dlastnode = h->first->link;  //dlastnode를 dn이 가리키는 링크로 설정해줌
		while (dlastnode->link != NULL) {  //만약 dlastnode의 링크가 null이 아닐경우
			dn = dlastnode; //dn에 dlastnode를 넣어줌 (뒤로 이동하는 과정)
			dlastnode = dlastnode->link;  //dlastnode를 dlastnode가 가리키는 링크로 넣어줌
		}
		 
	}
	free(dlastnode); //노드 메모리 해제
	dn->link = NULL;  //dn의 링크는 null이다 (dlastnode는 삭제됨)
}

//리스트의 링크를 역순으로 재배치 
int invertList(headNode* h) {

	
	listNode* blank; //임시저장
	listNode* result; //결과를 저장
	listNode* t; //head 위치 나타내는 포인터

	t = h->first;  //변수들 초기화
	blank = NULL;  
	result = NULL;

	//노드의 연결을 반대로 바꾸기
	while (t!= NULL)
	{
		blank = result; //blank의 포인터를 result로 넣어줌
		result = t; //result를 t로 넣어줌
		t = t->link;  //포인터의 맨 앞 노드에 있던 t를 다음노드로 옮겨줌
		result->link = blank;  //맨 앞 노드의 링크를 뒤집은 blank에 넣어줌
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
