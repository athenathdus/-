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

 //�ʿ��� �ڷᱸ��

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

//int�� arr�迭�� MAX_VERTEX��ŭ ������ ��, 0���� �ʱ�ȭ
int arr[MAX_VERTEX] = { 0 };

//�Լ� list
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
    printf("2019038079 �ڼҿ�\n");
	char command;
	int key;
	int key2;

	Graph vlist;
	vlist.vlist = NULL;  // vlist�ȿ� �ִ� VertexHead * vlist�� �����Ⱚ�� �� �־ �ʱ�ȭ �ʿ�  

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
	if ((*h) != NULL)  //���� vertexhead �� NULL�� �ƴҰ��                                           
		destroyGraph(&(*h));  //destroyGraph�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� 

	(*h) = (VertexHead*)malloc(sizeof(VertexHead)*MAX_VERTEX);  //�����Ҵ��� ���� (SIZE�� VertexHead* MAX_VERTEX��ŭ) 
	
	for (int i = 0; i < MAX_VERTEX ; i++) {  //for���� ����Ͽ� MAX���� head�� NULL���� �־��� 
		((*h)+i)->head= NULL;
	}
	return *h;  //VertexHead�� ���� �޸𸮸� �Ҵ��Ͽ� ����
	
}

void destroyGraph(VertexHead**h) { /* deallocating all allocated memory */
	
	Vertex* tmp = NULL;
	Vertex*p = NULL;
	for (int i = 0; i < MAX_VERTEX; i++) {  //for���� ����Ͽ� MAX���� tmp�� ���� head�� ���� �־���
		
		tmp= ((*h) + i)->head;
		

		while (tmp != NULL) { //����� link�� ��ü���ִ� ���� 
			p = tmp;
			tmp = tmp->link;
			p->link = NULL;
			free(p);
		}
		((*h) + i)->head = NULL;
		arr[i] = 0;  //��ü�� �κ��� �ٽ� 0���� ������� 

	}free(*h);  
	return 0;
}

int insertVertex(int num) /* vertex insertion */
{
	if (num > MAX_VERTEX|| num<0)  //����, �Է��� ���ڰ� MAX���� ũ�ų� 0���� �۰� �Ǹ� �޼��� ���
	{
		printf("���� �����Դϴ�.\n");
		return 1;
	}

	if (arr[num - 1] == 0) {  //���� �Է��� ������ arr�迭�� 0 ���̸� (�� ���ڰ� ���ٴ� ��)
		arr[num - 1] = 1;  //arr �迭�� ���� 1�� �ٲ��� 
	}

	else  //���� ó�� (���� vertex�� �Է��� ��� �޼��� ���)
		printf("������ vertex�� �Է��Ͽ����ϴ�.\n");
}

int deleteVertex(VertexHead*h, int num)/* vertex deletion */
{
	Vertex*t = h[num-1].head;  //t�� h[num-1]�� ���� ����
	if (t== NULL) {  //����, t�� null�� �ƴҰ�� �޼��� ��� 
		printf("������ �� ���� vertex�Դϴ�.\n");
		return 0;
	}
	//+)�Է��� num ��尡 �̾����ִ� ��������Ʈ���� ������ ��, �� free�� �����Ҵ� ���� ������
}
	
void insertEdge(VertexHead*h, int from, int to) /* new edge creation between two vertices */
{
	Vertex* v = NULL;  //v���� NULL�� �ʱ�ȭ
	Vertex*t = h[from-1].head;  //t�ȿ� h[from-1]�� head�� �־���
	int a = arr[from - 1];  //int �� ������ a�� b�� arr�迭 ���� �־��� (������ 1, ������ 0�� ��Ÿ��)
	int b = arr[to - 1];

	v= (Vertex*)malloc(sizeof(Vertex));  //v�� �����Ҵ� ���ְ�, v�� num�� �Է��� to���� �־��ְ�, link�� NULL������ ��
	v->num = to;
	v->link = NULL;

	if (b == 0 || a == 0) {  //���� a�Ǵ� b�� 0�̶��, �޼��� ��� ( 0�̶�� ���� ���߿� �ϳ��� vertex���� ���ٴ� �ǹ�)
		printf("�߸��� �����Դϴ�.\n");
		return;
	}

	if (t == NULL ) {  //���� (head���� NULL�ϰ��)
			h[from-1].head = v;  //h[from-1]�� head���� v�� ���� (head�� v�� �־���)
		}
	else {  // �׷��� ���� ���
			while (t->link != NULL) {  //�ڸ��� �Űܼ� �־��ִ� �ڵ� ����
				t = t->link;
			}
			t->link = v;
		}
	}

int deleteEdge(VertexHead*h, int from, int to)/* edge removal */
{
	Vertex*t = h[from-1].head;  //t�� �迭�� head�� ����
	Vertex * ppre = NULL;  //ppre�� null�� �ʱ�ȭ

	if (t== NULL) {  //���鸮��Ʈ�� ��� �޼��� ���
		printf("�� ����Ʈ�Դϴ�.\n");
		return 0;
	}

	while (t != NULL)  //t�� ���� null�϶����� while���� ����
	{
		if (t->num == to)  //t�� num�� to�� ���ٸ�
		{
			if (t == h[from - 1].head) { //t�� h[from-1]�� head�� �ǰ�
				h[from - 1].head = t->link;  //t�� ���� ��ũ��  h[from-1]�� ��尡 ��
			}

			else  //�׷��� ������( = ���� �ʴٸ�)
			{
				ppre->link = t->link;  //�ڸ��� �Ű���
			}
			free(t);  //t�� �����Ҵ� ����
			return 0;
		}
		ppre = t;  //�̵�����
		t = t->link;
		
	}
	
	return 1;
}

int depthFS(VertexHead*h, int key) /* depth firt search using stack */
{
}

int breadthFS(VertexHead*h, int key)/* breadth first search using queue */
{
	/*Vertex *w = h[key].head; //w���� key���� head�� ����
	QueueType q;  //queuetype�̶�� ����ü�� ����� ���� ����
	init(&q);   //ť �ʱ�ȭ
	printf("%d ", key);  			//�Է��� key �� �湮�� ������ print
	visited[key] = TRUE;      // �湮�� ������ ǥ��
	enqueue(&q, key);			// ���������� ť�� ���� 
	while (!is_empty(&q)) {
		key = dequeue(&q);		// ť�� ����� ���� ���� 
		for (w = h[key].head; w; w = w->link) //���� ���� Ž��
			if (!visited[w->num]) {	// �湮���� ���� ������ Ž��
				visited[w->num] = TRUE;   // �湮�Ͽ����� ǥ��
				printf("%d ", w->num);  //print
				enqueue(&q, w->num);	//������ ť�� �����ϵ��� ��
			}
	}*/
}
		
void printGraph(VertexHead*h) {/* printing graph with vertices and edges */
	
	Vertex* tmp = NULL;  //tmp�� null�� ����
	printf("\nPRINT\n");
	if (h == NULL) {  //���� h�� null �̶��, �޼��� ��� (����� ���� ������ �ǹ�)
		printf("nothing");
		return;
	}

	for (int i = 0; i < MAX_VERTEX; i++) {  //for���� ����� MAX_VERTEX���� tmp�ȿ� ������� h[i]�� head���� �־��� 
		tmp = h[i].head;
		if (arr[i] == 1) { //���� arr���� ���� 1�̸� ( vertex�� �����Ѵٴ� �ǹ�)
			printf("\n[%d]��������Ʈ:", i + 1);  //�޼��� ���
		}
		while (tmp) { 
			printf("[%d]->", tmp->num); //��������Ʈ�� ���
			tmp = tmp->link;
		}
	}
	puts(" ");
}

