/*
 * Term Project - Graph
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

 //필요한 자료구조

#define MAX_VERTEX 20 /* you can change value 20 */
#define TRUE 1
#define FALSE 0
#define MAX_QUEUE_SIZE 100

typedef struct Vertex {
	int num; /* vertex number */
	struct Vertex* link; /* link to a next adjacent vertext */
} Vertex;

typedef struct VertexHead {
	Vertex* head; /* linked list of all adjacent vertices */
} VertexHead;

typedef struct Graph {
	VertexHead* vlist; /* list of all vertices: vlist[MAX_VERTEX] */
} Graph;

//int형 arr배열을 MAX_VERTEX만큼 선언한 후, 0으로 초기화
int arr[MAX_VERTEX] = { 0 };

//함수 list
int createGraph(VertexHead**h); /* empty graph creation */
void destroyGraph(VertexHead**h); /* deallocating all allocated memory */
int insertVertex(int key); /* vertex insertion */
int deleteVertex(VertexHead*h, int key); /* vertex deletion */
void insertEdge(VertexHead*h, int v1, int v2); /* new edge creation between two vertices */
int deleteEdge(VertexHead*h, int v1, int v2); /* edge removal */
int depthFS(VertexHead*h,int key); /* depth firt search using stack */
int breadthFS(VertexHead*h,int key); /* breadth first search using queue */
void printGraph(VertexHead*h); /* printing graph with vertices and edges */

int main() {
    printf("2019038079 박소연\n");
	char command;
	int key;
	int key2;

	Graph vlist;
	vlist.vlist = NULL;  // vlist안에 있는 VertexHead * vlist에 쓰레기값이 들어가 있어서 초기화 필요  

	do {
		
		printf("----------------------------------------------------------------\n");
		printf("                    Term Project (Graph)                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" createGraph   = z           printGraph    = p \n");
		printf(" insertVertex  = i           deleteVertex  = d \n");
		printf(" insertEdge    = n          deleteEdge     = e\n");
		printf(" depthFS       = f           destroyGraph  = q\n");
		printf(" breadthFS     = r                                     \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			createGraph(&vlist.vlist);
			break;
		case 'p': case 'P':
			printGraph(vlist.vlist);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertVertex(key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteVertex(vlist.vlist, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			printf("Your Key = ");
			scanf("%d", &key2);
			insertEdge(vlist.vlist, key, key2);
			insertEdge(vlist.vlist, key2, key);
			break;
		case 'e': case 'E':
			printf("Your Key = ");
            printf("Your Key = ");
			scanf("%d", &key);
			scanf("%d", &key2);
			deleteEdge(vlist.vlist, key, key2);
			deleteEdge(vlist.vlist, key2, key);
			break;
		case 'f': case 'F':
			depthFS(vlist.vlist,key);
			break;
		case 'r': case 'R':
			printf("Your Key = ");
			scanf("%d", &key);
			breadthFS(vlist.vlist,key);
			break;
		case 'q': case 'Q':
			destroyGraph(vlist.vlist);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	} while (command != 'q' && command != 'Q');

	return 1;
}

int createGraph(VertexHead**h) /* empty graph creation */
{
	if ((*h) != NULL)  //만약 vertexhead 가 NULL이 아닐경우                                           
		destroyGraph(&(*h));  //destroyGraph를 호출하여 할당된 메모리 모두 해제 

	(*h) = (VertexHead*)malloc(sizeof(VertexHead)*MAX_VERTEX);  //동적할당을 해줌 (SIZE는 VertexHead* MAX_VERTEX만큼) 
	
	for (int i = 0; i < MAX_VERTEX ; i++) {  //for문을 사용하여 MAX까지 head에 NULL값을 넣어줌 
		((*h)+i)->head= NULL;
	}
	return *h;  //VertexHead에 대한 메모리를 할당하여 리턴
	
}

void destroyGraph(VertexHead**h) { /* deallocating all allocated memory */
	
	Vertex* tmp = NULL;
	Vertex*p = NULL;
	for (int i = 0; i < MAX_VERTEX; i++) {  //for문을 사용하여 MAX까지 tmp에 각각 head의 값을 넣어줌
		
		tmp= ((*h) + i)->head;
		

		while (tmp != NULL) { //연결된 link를 해체해주는 과정 
			p = tmp;
			tmp = tmp->link;
			p->link = NULL;
			free(p);
		}
		((*h) + i)->head = NULL;
		arr[i] = 0;  //해체한 부분을 다시 0으로 만들어줌 

	}free(*h);  
	return 0;
}

int insertVertex(int num) /* vertex insertion */
{
	if (num > MAX_VERTEX|| num<0)  //만약, 입력한 숫자가 MAX보다 크거나 0보다 작게 되면 메세지 출력
	{
		printf("예외 숫자입니다.\n");
		return 1;
	}

	if (arr[num - 1] == 0) {  //만약 입력한 숫자의 arr배열이 0 값이면 (그 숫자가 없다는 뜻)
		arr[num - 1] = 1;  //arr 배열의 값을 1로 바꿔줌 
	}

	else  //예외 처리 (같은 vertex를 입력할 경우 메세지 출력)
		printf("동일한 vertex를 입력하였습니다.\n");
}

int deleteVertex(VertexHead*h, int num)/* vertex deletion */
{
	Vertex*t = h[num-1].head;  //t는 h[num-1]의 헤드로 선언
	if (t== NULL) {  //만약, t가 null이 아닐경우 메세지 출력 
		printf("삭제할 수 없는 vertex입니다.\n");
		return 0;
	}
	//+)입력한 num 노드가 이어져있는 인접리스트들을 제거한 후, 다 free로 동적할당 해제 시켜줌
}
	
void insertEdge(VertexHead*h, int from, int to) /* new edge creation between two vertices */
{
	Vertex* v = NULL;  //v값을 NULL로 초기화
	Vertex*t = h[from-1].head;  //t안에 h[from-1]의 head를 넣어줌
	int a = arr[from - 1];  //int 형 변수인 a와 b에 arr배열 값을 넣어줌 (있으면 1, 없으면 0을 나타냄)
	int b = arr[to - 1];

	v= (Vertex*)malloc(sizeof(Vertex));  //v를 동적할당 해주고, v의 num에 입력한 to값을 넣어주고, link를 NULL값으로 둠
	v->num = to;
	v->link = NULL;

	if (b == 0 || a == 0) {  //만약 a또는 b가 0이라면, 메세지 출력 ( 0이라는 것은 둘중에 하나라도 vertex값이 없다는 의미)
		printf("잘못된 연결입니다.\n");
		return;
	}

	if (t == NULL ) {  //만약 (head값이 NULL일경우)
			h[from-1].head = v;  //h[from-1]의 head값을 v로 해줌 (head에 v값 넣어줌)
		}
	else {  // 그렇지 않을 경우
			while (t->link != NULL) {  //자리를 옮겨서 넣어주는 코드 구현
				t = t->link;
			}
			t->link = v;
		}
	}

int deleteEdge(VertexHead*h, int from, int to)/* edge removal */
{
	Vertex*t = h[from-1].head;  //t를 배열의 head라 선언
	Vertex * ppre = NULL;  //ppre는 null로 초기화

	if (t== NULL) {  //공백리스트일 경우 메세지 출력
		printf("빈 리스트입니다.\n");
		return 0;
	}

	while (t != NULL)  //t의 값이 null일때까지 while문이 실행
	{
		if (t->num == to)  //t의 num이 to와 같다면
		{
			if (t == h[from - 1].head) { //t는 h[from-1]의 head가 되고
				h[from - 1].head = t->link;  //t의 다음 링크는  h[from-1]의 헤드가 됨
			}

			else  //그렇지 않으면( = 같지 않다면)
			{
				ppre->link = t->link;  //자리를 옮겨줌
			}
			free(t);  //t의 동적할당 해제
			return 0;
		}
		ppre = t;  //이동과정
		t = t->link;
		
	}
	
	return 1;
}

int depthFS(VertexHead*h, int key) /* depth firt search using stack */
{
}

int breadthFS(VertexHead*h, int key)/* breadth first search using queue */
{
	/*Vertex *w = h[key].head; //w에는 key값의 head를 설정
	QueueType q;  //queuetype이라는 구조체를 만들어 변수 선언
	init(&q);   //큐 초기화
	printf("%d ", key);  			//입력한 key 및 방문한 정점을 print
	visited[key] = TRUE;      // 방문한 정점을 표시
	enqueue(&q, key);			// 시작정점을 큐에 저장 
	while (!is_empty(&q)) {
		key = dequeue(&q);		// 큐에 저장된 정점 선택 
		for (w = h[key].head; w; w = w->link) //인접 정점 탐색
			if (!visited[w->num]) {	// 방문하지 않은 정점을 탐색
				visited[w->num] = TRUE;   // 방문하였음을 표시
				printf("%d ", w->num);  //print
				enqueue(&q, w->num);	//정점을 큐에 삽입하도록 함
			}
	}*/
}
		
void printGraph(VertexHead*h) {/* printing graph with vertices and edges */
	
	Vertex* tmp = NULL;  //tmp를 null로 설정
	printf("\nPRINT\n");
	if (h == NULL) {  //만약 h가 null 이라면, 메세지 출력 (출력할 값이 없음을 의미)
		printf("nothing");
		return;
	}

	for (int i = 0; i < MAX_VERTEX; i++) {  //for문을 사용해 MAX_VERTEX까지 tmp안에 순서대로 h[i]의 head값을 넣어줌 
		tmp = h[i].head;
		if (arr[i] == 1) { //만약 arr안의 값이 1이면 ( vertex가 존재한다는 의미)
			printf("\n[%d]인접리스트:", i + 1);  //메세지 출력
		}
		while (tmp) { 
			printf("[%d]->", tmp->num); //인접리스트를 출력
			tmp = tmp->link;
		}
	}
	puts(" ");
}

