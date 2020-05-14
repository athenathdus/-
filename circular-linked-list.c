
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
 /* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
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
	printf("2019038079 박소연\n");
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

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h) {
	if (h->rlink == h) {  //h의 rlink가 헤드노드일 경우, 아무것도 없음을 의미하므로 h를 해제시켜준다. 
		free(h);
	}
	
	listNode* p = h->rlink;  //p를 h의 다음노드라 칭한다. 

	listNode* prev = NULL;  //prev라는 노드를 하나 만들어준다.
	while (p != NULL  || p!=h) {  //p가 null 또는 p가 h가 아닐때까지 while문이 반복된다. 
		prev = p;  //prev를 p에 넣어준다. 그러면 prev가 h->rlink가 된다.
		p = p->rlink;  // p를 p가 가리키는 오른쪽 링크로 옮겨준다.
		free(prev);  //prev를 해제해준다.
	}
	free(h);  //h를 해제해준다.


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
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
	listNode* n;
	n = h->rlink;
	listNode* lastnode;
	lastnode = (listNode*)malloc(sizeof(listNode));  //lastnode에 동적할당을 해줌
	lastnode->rlink = NULL;  //lastnode의 rlink와 llink 모두 null 값으로 초기화
	lastnode->llink = NULL;
	lastnode->key = key;  //lastnode의 key값에 key를 넣어줌

	if (h == NULL) {  //만약, h가 null일경우에 오류입니다 메세지를 출력
		printf("오류입니다.");
		return 0;
	}
	 
	
		while (n->rlink != h){   //위의 조건이 아니라면(중간에 노드가 있다면)
			n = n->rlink;
		}
		
			n->rlink = lastnode;
			lastnode->llink = n;
			lastnode->rlink = h;
			h->llink = lastnode;

		return 0;
}
	

	



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	listNode*dlastnode;
	listNode*dn=h->rlink;

	if (h== NULL || h->rlink==h) {  //만약 h가 null이거나 h밖에 없으면 
		printf(" 지울 노드가 없습니다. \n");  //지울노드가 없음을 출력
		return 1;
	}

	if (dn->rlink == h) {  //h의 다음노드의 오른쪽링크가 h이면
		h->rlink = h;  //h의 오른쪽링크를 헤드노드로 연결해줌 
		free(dn); //노드 메모리 해제
		return 1;
	}
	else {  //그렇지 않으면

		dlastnode = dn->rlink;  //dlastnode를 dn이 가리키는 다음링크로 설정해줌

		while (dlastnode->rlink != h) {  //만약 dlastnode의 다음링크가 h가 아닐경우
			dn = dlastnode; //dn에 dlastnode를 넣어줌 (뒤로 이동하는 과정)
			dlastnode = dlastnode->rlink;  //dlastnode를 dlastnode가 가리키는 오른쪽 링크로 넣어줌
		}
		free(dlastnode); //노드 메모리 해제
		dn->rlink =h;  //dn의 오른쪽링크는 헤드노드이다 (dlastnode는 삭제됨)

	}
	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	listNode* firstnode = (listNode*)malloc(sizeof(listNode));  //firstnode를 하나 생성해줌
	firstnode->key = key;  //노드의 key값에 입력한 값을 넣어줌
	firstnode->llink = NULL;  //firstnode의 rlink와 llink 의 값을 null로 초기화해줌
	firstnode->rlink = NULL;

	firstnode->rlink = h->rlink;  //firstnode의 rlink값을 h이 가리키던 오른쪽 값으로 바꿔줌 (firstnode의 오른쪽이 연결)
	h->rlink->llink = firstnode;  //h의 rlink의 llink 즉 원래 h가 가리키던 오른쪽노드의 왼쪽 링크를 firstnode와 연결해줌  (firstnode와 다음노드가 쌍방 연결)
	firstnode->llink = h;  // firstnode의 왼쪽 링크를 헤드노드와 연결  (firstnode의 왼쪽링크를 h와 연결)
	h->rlink = firstnode;  //h의 오른쪽링크를 firstnode와 연결 (firstnode와 h가 쌍방으로 연결)

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {


	listNode* tnode = h->rlink;  //tnode를 h의 오른쪽링크로설정
	h->rlink = tnode->rlink;  //tnode가 가리키던 오른쪽 링크를 h의 rlink로 바꿔줌 (노드의 연결을 끊음)
	h->rlink->rlink->llink = h; //h->rlink->rlink->llink를 h로 연결 ( 노드의 연결을 끊어주는 과정 완료)
	free(tnode);  //동적할당 해제 tnode


	return 1;

}

/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {

	if (h == NULL || h->rlink == h) {
		printf(" 재배치 할 노드 없음");
		return 0;
	}

	listNode* blank=h; 
	listNode* result=h; 
	listNode* t=h->rlink; //head 위치 나타내는 포인터
	
	//노드의 연결을 반대로 바꾸기
	while (t != h)  //t가 h일때까지 반복
	{
		blank = result; //blank의 포인터를 result로 넣어줌
		result = t; //result를 t로 넣어줌
		t = t->rlink;  //포인터의 맨 앞 노드에 있던 t를 다음노드로 옮겨줌
		result->rlink = blank; //result의 오른쪽링크를 blank로 설정
		result->llink = t;//result의 왼쪽링크를 t로 설정
	}
	;
	h->rlink= result; //h의 오른쪽링크는 result
	return 0;

}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {

	listNode* nnode = (listNode*)malloc(sizeof(listNode));  //nnode 라는 새로운 노드를 동적할당 해줌(입력한 값이 들어갈 노드)
	nnode->key = key;  //nnode에 입력한 키 값을 넣음
	listNode*now;  //now와 trail노드를 생성(위치를 알기 위해서)
	listNode*trail;
	now = h->rlink;  //now와 trail에는 헤드노드의 오른쪽링크
	trail = h->rlink;
	nnode->rlink = NULL;  //nnode가 가리키는 링크는 null값으로 만들어줌
	nnode->llink = NULL;

	
	if (h->rlink == h) {  //만약 h의 오른쪽링크가 h라면 
		
		h->rlink = nnode;  //h의 오른쪽 링크를 nnode로 연결
		nnode->llink = h;  //nnode의 왼쪽링크를 h랑 연결
		nnode->rlink = h;   //nnode의 오른쪽링크를 h랑 연결
		h->llink = nnode;  //h의 왼쪽링크를 nnode랑 연결
		
		
		return 1;
	}

	while (now!=h)  //now 의 값이 h일때까지 while문이 반복됨
	{
		if (now->key >= key) {  //만약 입력한 key값이 now가 있는 key값보다 작거나 같을경우
			if (now == h->rlink)  //그 중에서도, now 가 헤드노드의 바로 다음 노드일 경우에
			{
				nnode->rlink =now;  
				now->llink = nnode;
				h->rlink = nnode;  
				nnode->llink = h;
			}

			else /*if (now->key < key)*/  //만약 작지 않다면, 
			{
				nnode->rlink =now; 
				now->llink = nnode;
				trail->rlink = nnode;
				nnode->llink = trail;
			}

			return 1;

		}
		trail = now;  //trail 다음이 now 인 알고리즘으로 진행하기 때문에 trail에다가 now값을 넣어줌(trail이 앞으로 한칸 이동)
		now = now->rlink;  //now는 now의 오른쪽링크가 가리키는 링크로 이동 (now가 앞으로 한칸 이동)

	}
	trail->rlink = nnode;  //맨마지막에 삽입되는 경우 (trail의 링크를 nnode라 해줌)
	nnode->rlink = h; //nnode의 오른쪽링크를 h라 칭함


	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	if (h->rlink == h) {  //공백리스트일 경우
		printf("빈 리스트입니다.");
		return 0;
	}

	listNode * ppre;
	listNode * pnode;
	
	pnode = h->rlink;  //pnode를 헤드노드의 다음으로 넣어줌
	ppre = pnode->rlink;  //ppre를 pnode의 오른쪽링크로 설정
	while (pnode->rlink != h || pnode->rlink != NULL)  //pnode의 오른쪽링크가 h가 아니거나 pnode의 오른쪽링크가 null일때까지 반복
	{
		if (pnode->key == key)  //만약 pnode의 key가 입력한 key값과 같으면 
		{
			if (pnode == h->rlink) {  //pnode가 h->rlink라면, 
				h->rlink = pnode->rlink;
				pnode->rlink->llink = h;
				free(pnode);
			}

			else  //그렇지 않은 경우일때, 
			{
				pnode->llink->rlink = ppre->rlink;
				ppre->rlink->llink = pnode->llink;
				free(ppre);
			}
			return 0;
		}

		deleteLast(h);   //마지막 노드 삭제 
	}
		pnode = pnode->rlink;  //pnode의 자리 이동
		
	
	return 0;
}
	

