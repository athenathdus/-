/*
 * hw5-sorting.c
 *
 *  Created on: May 22, 2019
 *
 *  Homework 5: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h> //헤더
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE                  13      /* prime number , MAX_ARRAY_SIZE를 13으로 고정*/
#define MAX_HASH_TABLE_SIZE     MAX_ARRAY_SIZE  // MAX_HASH_TABLE_SIZE 와  MAX_ARRAY_SIZE 를 정의한다. 

 /* 필요에 따라 함수 추가 가능 */
int initialize(int **a);  //이중포인터를 사용한 동적할당
int freeArray(int *a);  //동적할당 해제 함수
void printArray(int *a);  //print하는 함수

int selectionSort(int *a);  //선택정렬 함수
int insertionSort(int *a);  //삽입정렬 함수 
int bubbleSort(int *a);  //버블정렬 함수 
int shellSort(int *a);  //셸 정렬 함수 
/* recursive function으로 구현 */
int quickSort(int *a, int n);  //퀵정렬


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);  //해시 코드 

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);  //해싱

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key); //탐색함수 


int main()
{
	char command;   //문자형 command를 선언
	int *array = NULL;  //*array와 *hashtable을 NULL로 초기화시킴 
	int *hashtable = NULL;
	int key = -1;  //key와 index를 -1로 지정 
	int index = -1;

	srand(time(NULL));  //랜덤함수 

	do {
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)  //동적할당 함수 
{
	int *temp = NULL;  //*temp를 NULL로 초기화 시켜줌 

	/* array가 NULL인 경우 메모리 할당 */
	if (*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	}
	else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)  //동적할당 해제 함수 
{
	if (a != NULL)  //만약 array가 NULL이 아닐경우 , free를 통해 해제시켜줌 
		free(a);
	return 0;
}

void printArray(int *a)  //print함수 
{
	if (a == NULL) {  //만약 a가 NULL일경우 
		printf("nothing to print.\n");  //nothing to print.라는 멘트를 출력시켜줌 
		return;
	}
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)  //for문을 사용해 i는 0부터 MAXSIZE까지 계속 반복시켜줌
		printf("a[%02d] ", i);  //값을 프린트 해줌(0으로 공백 채워서) 
	printf("\n");
	for (int i = 0; i < MAX_ARRAY_SIZE; i++) //for문을 사용해 i는 0부터 MAXSIZE까지 계속 반복시켜줌
		printf("%5d ", a[i]); //값을 프린트 해줌(5개의 칸을 만들고 오른쪽으로 정렬 ) 
	printf("\n");
}

int selectionSort(int *a) //선택정렬 함수 
{
	int min;  //int형 변수를 네개 선언해줌
	int minindex;
	int i, j;

	printf("Selection Sort: \n");  //선택정렬 결과를 print해줌 
	printf("----------------------------------------------------------------\n");

	printArray(a);   //print함수 사용

	for (i = 0; i < MAX_ARRAY_SIZE; i++)  //for문을 사용해 i는 0부터 MAX까지 계속 반복시켜줌
	{
		minindex = i;  //i를 minindex라 지정함 (인덱스)
		min = a[i];  //a[i]값을 min이라 지정함 (최솟값을 저장하는 변수)
		for (j = i + 1; j < MAX_ARRAY_SIZE; j++) //j를 i의 바로 다음순서으로 지정하고 MAX까지 for문을 사용해 반복시켜줌 
		{
			if (min > a[j])  //만약 min값이 a배열에 있는 값보다 크게 된다면
			{
				min = a[j];  //a[j]에 있는 값을 min으로 지정(현재값과 그 다음값을 바꾸는 과정)
				minindex = j; //j는 minindex에 저장 
			}
		}
		a[minindex] = a[i];  //a[i]에 있는 값 (현재 제일 최대값), a[minindex] (제일 작은 값의 인덱스) 이므로 제일 최댓값을 제일 작은값의 index의 위치의 값으로 지정해줌
		a[i] = min;  //제일 작은값은 min을 a[i] (즉 위치하는 제일 앞부분)에 옮겨줌  (그렇게 되면 첫번쨰 값과 그 뒤로 탐색한 값중에 제일 작은값의 위치가 서로 바뀌게 됨)
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int insertionSort(int *a)  //삽입정렬함수
{
	int i, j, t;  //int형 변수 세개지정

	printf("Insertion Sort: \n");  //삽입정렬 print
	printf("----------------------------------------------------------------\n");

	printArray(a);  

	for (i = 1; i < MAX_ARRAY_SIZE; i++)  //for문을 사용해 i는 1부터 MAX까지 계속 반복시켜줌
	{
		t = a[i]; //t를 a의 두번째 값으로 넣어줌 
		j = i;  //j는 i값으로 지정 
		while (a[j - 1] > t && j > 0)  //a[j-1]의 값이 t보다 크고(자신보다 값이 큼) , j가 0보다 클때까지 반복 
		{
			a[j] = a[j - 1];  //더 큰 값을 뒤로 넣어줌 
			j--;  //j의 값 감소 (-1을 해줌) - 계속 반복하다가 while문에 다시 들어가지 못하게 하는 역할을 함 
		}
		a[j] = t;  //t값을 a[j]에 넣어줌
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a)  //버블정렬함수 
{
	int i, j, t; //int형 변수를 세개 지정 

	printf("Bubble Sort: \n");  //버블 정렬 print 
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++)  //for문을 사용해 i는 0부터 MAX까지 계속 반복시켜줌 
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)  //for문을 사용해 j는 0부터 MAX까지 계속 반복시켜줌
		{
			if (a[j - 1] > a[j])  //j의 바로 앞의 값과 j의 값을 비교해서 만약 앞의 값이 더 크면 
			{
				t = a[j - 1];  //(swap) t에 j의 바로 앞의 값을 넣어주고 
				a[j - 1] = a[j];  //j값을 j의 바로 앞의 값에 넣어주고 
				a[j] = t;  //t의 값을 j에 넣어줌 (결과적으로 앞뒤 값이 바뀌게 됨 ) 
			}
		}
	}
	//제일 큰 값을 마지막으로 보내고 제일 마지막 값을 빼고 계속 반복해서 정렬하는 것
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a)  //셸 정렬
{
	int i, j, k, h, v;  //int형 변수 5개 선언 

	printf("Shell Sort: \n");  //셸 정렬 print 
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE / 2; h > 0; h /= 2)  //h의 값을 MAX의 반의 값이라 두고, h가 0보다 클때까지,h의 값을 반으로 나눔 (간격을 2분의1로 줄이는 과정)
	{
		for (i = 0; i < h; i++)  //i가 0부터 i가 h까지 i가 증가함(for문을 사용하여 반복, 절반으로 줄인만큼 반복)
		{
			for (j = i + h; j < MAX_ARRAY_SIZE; j += h)  //j가 i+h부터(size/2+1부분을 이야기함) j가 MAX까지 j=j+h해줌( 짝을 묶어줌)
			{
				v = a[j];  //a[j]의값을 v에 넣어줌
				k = j;  //j값을 k로 넣어줌
				while (k > h - 1 && a[k - h] > v)  //k가 h-1보다 크고, a[k-h]가 v보다 클때까지 반복 ( 값을 비교하는과정)
				{
					a[k] = a[k - h]; //a[k - h]의 값을 a[k]에 저장 (큰값은 뒤로 옮김)
					k -= h; //k=k-h (h는 비교하는 값두개의 떨어져있는값,k-h를 해줌으로써 비교하는 두개의 값 중 index가 더 작은 값을 가리키게함
				}
				a[k] = v; //위에서 값을 변경해준 k번째에 v에 저장되있는 작은값을 넣어줌
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n) //퀵정렬
{
	int v, t;  //int형 변수 4개 선언 
	int i, j;

	if (n > 1)  //만약 n이 1보다 클 경우,
	{
		v = a[n - 1];  //v는 a의 왼쪽 (제일 마지막 값을 나타냄)
		i = -1; //i는 index를 나타내는데 -1부터 시작하게 둠 
		j = n - 1;  //j는 a의 왼쪽 인덱스 (제일 마지막 index)

		while (1)
		{
			while (a[++i] < v);  //i의 값이 오른쪽으로 계속 증가 (a[++i]값이 v보다 작을때까지 반복)
			while (a[--j] > v);  //j값이 왼쪽으로 계속 감소 (index를 이동- a[--j]값이 v보다 클까지 반복)

			if (i >= j) break;  //만약 i가 j보다 크거나 같으면 break (둘이 같은 위치일 경우)
			t = a[i];  //swap (a[i]값과 a[j]값이 t를 사용하여 자리를 바꿈)
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];  //swap (a[i]값과 v값이 t를 사용하여 자리를 바꿈)
		a[i] = a[n - 1];
		a[n - 1] = t;

		//분할하여 정렬을 하기 위함 
		quickSort(a, i); 
		quickSort(a + i + 1, n - i - 1);
	}


	return 0;
}

int hashCode(int key) {//해시코드
	return key % MAX_HASH_TABLE_SIZE;  //key값을 13으로 나눈 나머지를 반환 (=hashcode)
}

int hashing(int *a, int **ht)//해싱
{
	int *hashtable = NULL;  //hashtable을 NULL로 초기화

	/* hash table이 NULL인 경우 메모리 할당 */
	if (*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	}
	else {
		hashtable = *ht;        /* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for (int i = 0; i < MAX_HASH_TABLE_SIZE; i++)  //해시테이블안의 값을 모두 -1로 초기화
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
			printf("hashtable[%d] = %d\n", i, hashtable[i]);  
	*/

	int key = -1;  //key값 -1로 초기화
	int hashcode = -1;  //hashcode를 -1로 초기화
	int index = -1;//index를 -1로 초기화
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)  //i는 MAX까지 for문을 사용하여 반복
	{
		key = a[i]; //key값에 a의 i번째 배열의 값을 넣어줌
		hashcode = hashCode(key);  //hashcode의 함수를 호출하여 hashcode를 저장함
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)  //만약 if문이 성립한다면, (원래 초기화한 값이 -1임/값이 들어가있지 않음을 의미)
		{
			hashtable[hashcode] = key;  //hashtable의 hashcode에 key값을 넣어줌
		}
		else {  //그렇지 않으면 (이미 값이 들어가있다면/충돌 발생)

			index = hashcode; //hashcode를 index에 넣어줌

			while (hashtable[index] != -1) //hashtable의 index가 -1이면 break
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;  //그 다음인덱스로 넘어가기 위해 1을 더해주고 나머지를 구한 후에 index에 저장해줌 
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;  //hashtable의 index에 key값을 넣어줌
		}
	}

	return 0;
}

int search(int *ht, int key)  //탐색 함수 
{
	int index = hashCode(key);  //hashcode함수를 호출하여 값을 계산한 후에 그 값을 index에 넣어줌

	if (ht[index] == key) //만약 index가  key와 같다면
		return index;  //index의 값을 return 해줌 (탐색 성공)

	while (ht[++index] != key)  //ht[++index] 가 key값일때까지 반복 
	{
		index = index % MAX_HASH_TABLE_SIZE;  //index에서 MAX로 나눈 나머지를 저장 index
	}
	return index;  //index의 값을 return 해줌
}



