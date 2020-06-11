/*
 * hw5-sorting.c
 *
 *  Created on: May 22, 2019
 *
 *  Homework 5: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h> //���
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE                  13      /* prime number , MAX_ARRAY_SIZE�� 13���� ����*/
#define MAX_HASH_TABLE_SIZE     MAX_ARRAY_SIZE  // MAX_HASH_TABLE_SIZE ��  MAX_ARRAY_SIZE �� �����Ѵ�. 

 /* �ʿ信 ���� �Լ� �߰� ���� */
int initialize(int **a);  //���������͸� ����� �����Ҵ�
int freeArray(int *a);  //�����Ҵ� ���� �Լ�
void printArray(int *a);  //print�ϴ� �Լ�

int selectionSort(int *a);  //�������� �Լ�
int insertionSort(int *a);  //�������� �Լ� 
int bubbleSort(int *a);  //�������� �Լ� 
int shellSort(int *a);  //�� ���� �Լ� 
/* recursive function���� ���� */
int quickSort(int *a, int n);  //������


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);  //�ؽ� �ڵ� 

/* array a���� �� hash table�� �����. */
int hashing(int *a, int **ht);  //�ؽ�

/* hash table���� key�� ã�� hash table�� index return */
int search(int *ht, int key); //Ž���Լ� 


int main()
{
	char command;   //������ command�� ����
	int *array = NULL;  //*array�� *hashtable�� NULL�� �ʱ�ȭ��Ŵ 
	int *hashtable = NULL;
	int key = -1;  //key�� index�� -1�� ���� 
	int index = -1;

	srand(time(NULL));  //�����Լ� 

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

int initialize(int** a)  //�����Ҵ� �Լ� 
{
	int *temp = NULL;  //*temp�� NULL�� �ʱ�ȭ ������ 

	/* array�� NULL�� ��� �޸� �Ҵ� */
	if (*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	}
	else
		temp = *a;

	/* �������� �迭�� ������ ���� */
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)  //�����Ҵ� ���� �Լ� 
{
	if (a != NULL)  //���� array�� NULL�� �ƴҰ�� , free�� ���� ���������� 
		free(a);
	return 0;
}

void printArray(int *a)  //print�Լ� 
{
	if (a == NULL) {  //���� a�� NULL�ϰ�� 
		printf("nothing to print.\n");  //nothing to print.��� ��Ʈ�� ��½����� 
		return;
	}
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)  //for���� ����� i�� 0���� MAXSIZE���� ��� �ݺ�������
		printf("a[%02d] ", i);  //���� ����Ʈ ����(0���� ���� ä����) 
	printf("\n");
	for (int i = 0; i < MAX_ARRAY_SIZE; i++) //for���� ����� i�� 0���� MAXSIZE���� ��� �ݺ�������
		printf("%5d ", a[i]); //���� ����Ʈ ����(5���� ĭ�� ����� ���������� ���� ) 
	printf("\n");
}

int selectionSort(int *a) //�������� �Լ� 
{
	int min;  //int�� ������ �װ� ��������
	int minindex;
	int i, j;

	printf("Selection Sort: \n");  //�������� ����� print���� 
	printf("----------------------------------------------------------------\n");

	printArray(a);   //print�Լ� ���

	for (i = 0; i < MAX_ARRAY_SIZE; i++)  //for���� ����� i�� 0���� MAX���� ��� �ݺ�������
	{
		minindex = i;  //i�� minindex�� ������ (�ε���)
		min = a[i];  //a[i]���� min�̶� ������ (�ּڰ��� �����ϴ� ����)
		for (j = i + 1; j < MAX_ARRAY_SIZE; j++) //j�� i�� �ٷ� ������������ �����ϰ� MAX���� for���� ����� �ݺ������� 
		{
			if (min > a[j])  //���� min���� a�迭�� �ִ� ������ ũ�� �ȴٸ�
			{
				min = a[j];  //a[j]�� �ִ� ���� min���� ����(���簪�� �� �������� �ٲٴ� ����)
				minindex = j; //j�� minindex�� ���� 
			}
		}
		a[minindex] = a[i];  //a[i]�� �ִ� �� (���� ���� �ִ밪), a[minindex] (���� ���� ���� �ε���) �̹Ƿ� ���� �ִ��� ���� �������� index�� ��ġ�� ������ ��������
		a[i] = min;  //���� �������� min�� a[i] (�� ��ġ�ϴ� ���� �պκ�)�� �Ű���  (�׷��� �Ǹ� ù���� ���� �� �ڷ� Ž���� ���߿� ���� �������� ��ġ�� ���� �ٲ�� ��)
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int insertionSort(int *a)  //���������Լ�
{
	int i, j, t;  //int�� ���� ��������

	printf("Insertion Sort: \n");  //�������� print
	printf("----------------------------------------------------------------\n");

	printArray(a);  

	for (i = 1; i < MAX_ARRAY_SIZE; i++)  //for���� ����� i�� 1���� MAX���� ��� �ݺ�������
	{
		t = a[i]; //t�� a�� �ι�° ������ �־��� 
		j = i;  //j�� i������ ���� 
		while (a[j - 1] > t && j > 0)  //a[j-1]�� ���� t���� ũ��(�ڽź��� ���� ŭ) , j�� 0���� Ŭ������ �ݺ� 
		{
			a[j] = a[j - 1];  //�� ū ���� �ڷ� �־��� 
			j--;  //j�� �� ���� (-1�� ����) - ��� �ݺ��ϴٰ� while���� �ٽ� ���� ���ϰ� �ϴ� ������ �� 
		}
		a[j] = t;  //t���� a[j]�� �־���
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a)  //���������Լ� 
{
	int i, j, t; //int�� ������ ���� ���� 

	printf("Bubble Sort: \n");  //���� ���� print 
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++)  //for���� ����� i�� 0���� MAX���� ��� �ݺ������� 
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)  //for���� ����� j�� 0���� MAX���� ��� �ݺ�������
		{
			if (a[j - 1] > a[j])  //j�� �ٷ� ���� ���� j�� ���� ���ؼ� ���� ���� ���� �� ũ�� 
			{
				t = a[j - 1];  //(swap) t�� j�� �ٷ� ���� ���� �־��ְ� 
				a[j - 1] = a[j];  //j���� j�� �ٷ� ���� ���� �־��ְ� 
				a[j] = t;  //t�� ���� j�� �־��� (��������� �յ� ���� �ٲ�� �� ) 
			}
		}
	}
	//���� ū ���� ���������� ������ ���� ������ ���� ���� ��� �ݺ��ؼ� �����ϴ� ��
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a)  //�� ����
{
	int i, j, k, h, v;  //int�� ���� 5�� ���� 

	printf("Shell Sort: \n");  //�� ���� print 
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE / 2; h > 0; h /= 2)  //h�� ���� MAX�� ���� ���̶� �ΰ�, h�� 0���� Ŭ������,h�� ���� ������ ���� (������ 2����1�� ���̴� ����)
	{
		for (i = 0; i < h; i++)  //i�� 0���� i�� h���� i�� ������(for���� ����Ͽ� �ݺ�, �������� ���θ�ŭ �ݺ�)
		{
			for (j = i + h; j < MAX_ARRAY_SIZE; j += h)  //j�� i+h����(size/2+1�κ��� �̾߱���) j�� MAX���� j=j+h����( ¦�� ������)
			{
				v = a[j];  //a[j]�ǰ��� v�� �־���
				k = j;  //j���� k�� �־���
				while (k > h - 1 && a[k - h] > v)  //k�� h-1���� ũ��, a[k-h]�� v���� Ŭ������ �ݺ� ( ���� ���ϴ°���)
				{
					a[k] = a[k - h]; //a[k - h]�� ���� a[k]�� ���� (ū���� �ڷ� �ű�)
					k -= h; //k=k-h (h�� ���ϴ� ���ΰ��� �������ִ°�,k-h�� �������ν� ���ϴ� �ΰ��� �� �� index�� �� ���� ���� ����Ű����
				}
				a[k] = v; //������ ���� �������� k��°�� v�� ������ִ� �������� �־���
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n) //������
{
	int v, t;  //int�� ���� 4�� ���� 
	int i, j;

	if (n > 1)  //���� n�� 1���� Ŭ ���,
	{
		v = a[n - 1];  //v�� a�� ���� (���� ������ ���� ��Ÿ��)
		i = -1; //i�� index�� ��Ÿ���µ� -1���� �����ϰ� �� 
		j = n - 1;  //j�� a�� ���� �ε��� (���� ������ index)

		while (1)
		{
			while (a[++i] < v);  //i�� ���� ���������� ��� ���� (a[++i]���� v���� ���������� �ݺ�)
			while (a[--j] > v);  //j���� �������� ��� ���� (index�� �̵�- a[--j]���� v���� Ŭ���� �ݺ�)

			if (i >= j) break;  //���� i�� j���� ũ�ų� ������ break (���� ���� ��ġ�� ���)
			t = a[i];  //swap (a[i]���� a[j]���� t�� ����Ͽ� �ڸ��� �ٲ�)
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];  //swap (a[i]���� v���� t�� ����Ͽ� �ڸ��� �ٲ�)
		a[i] = a[n - 1];
		a[n - 1] = t;

		//�����Ͽ� ������ �ϱ� ���� 
		quickSort(a, i); 
		quickSort(a + i + 1, n - i - 1);
	}


	return 0;
}

int hashCode(int key) {//�ؽ��ڵ�
	return key % MAX_HASH_TABLE_SIZE;  //key���� 13���� ���� �������� ��ȯ (=hashcode)
}

int hashing(int *a, int **ht)//�ؽ�
{
	int *hashtable = NULL;  //hashtable�� NULL�� �ʱ�ȭ

	/* hash table�� NULL�� ��� �޸� �Ҵ� */
	if (*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	}
	else {
		hashtable = *ht;        /* hash table�� NULL�� �ƴѰ��, table ��Ȱ��, reset to -1 */
	}

	for (int i = 0; i < MAX_HASH_TABLE_SIZE; i++)  //�ؽ����̺���� ���� ��� -1�� �ʱ�ȭ
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
			printf("hashtable[%d] = %d\n", i, hashtable[i]);  
	*/

	int key = -1;  //key�� -1�� �ʱ�ȭ
	int hashcode = -1;  //hashcode�� -1�� �ʱ�ȭ
	int index = -1;//index�� -1�� �ʱ�ȭ
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)  //i�� MAX���� for���� ����Ͽ� �ݺ�
	{
		key = a[i]; //key���� a�� i��° �迭�� ���� �־���
		hashcode = hashCode(key);  //hashcode�� �Լ��� ȣ���Ͽ� hashcode�� ������
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)  //���� if���� �����Ѵٸ�, (���� �ʱ�ȭ�� ���� -1��/���� ������ ������ �ǹ�)
		{
			hashtable[hashcode] = key;  //hashtable�� hashcode�� key���� �־���
		}
		else {  //�׷��� ������ (�̹� ���� ���ִٸ�/�浹 �߻�)

			index = hashcode; //hashcode�� index�� �־���

			while (hashtable[index] != -1) //hashtable�� index�� -1�̸� break
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;  //�� �����ε����� �Ѿ�� ���� 1�� �����ְ� �������� ���� �Ŀ� index�� �������� 
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;  //hashtable�� index�� key���� �־���
		}
	}

	return 0;
}

int search(int *ht, int key)  //Ž�� �Լ� 
{
	int index = hashCode(key);  //hashcode�Լ��� ȣ���Ͽ� ���� ����� �Ŀ� �� ���� index�� �־���

	if (ht[index] == key) //���� index��  key�� ���ٸ�
		return index;  //index�� ���� return ���� (Ž�� ����)

	while (ht[++index] != key)  //ht[++index] �� key���϶����� �ݺ� 
	{
		index = index % MAX_HASH_TABLE_SIZE;  //index���� MAX�� ���� �������� ���� index
	}
	return index;  //index�� ���� return ����
}



