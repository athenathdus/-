
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** create_matrix(int row, int col); //�����Ҵ��� ���� (�־��� create_matrix() �Լ� ���)
int free_matrix(int** matrix, int row, int col); //�����Ҵ� ����������   (�־��� free_matrix �Լ� ���)
void print_matrix(int** matrix, int row, int col); //����� �������  (�־��� print_matrix �Լ� ���)
int fill_data(int **matrix, int row, int col); //����� random�� ������ ���� (�־��� fill_data �Լ� ���)
int transpose_matrix(int **matrix, int **matrix_t, int row, int col); //����� ��ġ (�־��� transpose_matrix �Լ� ���)
int addition_matrix(int **matrix_a, int **matrix_b, int **matrix_sum, int row, int col); //����� ���� (�־��� addition_matrix �Լ� ���)
int subtraction_matrix(int **matrix_a, int **matrix_b, int **matrix_sub, int row, int col); //����� ���� (�־��� subtraction_matrix �Լ� ���)
int multiply_matrix(int **matrix_a, int **matrix_t, int **matrix_axt, int row, int col); //����� ���� (�־��� multiply_matrix �Լ� ���)


int main() {

   printf(" [----- [�ڼҿ�] [2019038079] -----] \n");
    int row, col;  //��, �� ����
	int **matrix_a;  //�ʿ��� ������ ����
	int **matrix_b;
	int **matrix_sum;
	int **matrix_axt;
	int **matrix_t;
	int **matrix_sub;
	

	srand(time(NULL)); //�����Լ��� �ʱ�ȭ
	printf("��� �� �Է��ϼ��� (���� : 3 4) : ");  
	scanf("%d %d", &row, &col);  //����� ��, ���� ���� �Է¹���(�־��� scanf()���)

	if (row <= 0 || col <= 0) {  //�Է¹��� ���� �ϳ��� 0���� ���� ���, ����� ���� �ٽ� �Է¹ޱ� ����
		printf("��� ���� 1 �̻��� ���� �ٽ� �Է����ּ���\n ��� �� �Է��ϼ��� (���� : 3 4) : "); 
		scanf("%d %d", &row, &col);
	}
	
	matrix_a = create_matrix(row, col);  //create_matrix�Լ��� ���� �����Ҵ� ����
	matrix_b = create_matrix(row, col);
	matrix_sub = create_matrix(row, col);  
	matrix_sum = create_matrix(row, col); 
	matrix_axt = create_matrix(row, col); 


    fill_data(matrix_a, row, col); //fil_data�Լ��� ���� ������
	fill_data(matrix_b, row, col);

	if (row == col) {  //���� ��� ���� �������
		matrix_t = create_matrix(row, col);  //��� ���� �״�� �־���
	}

	else {
		matrix_t = create_matrix(col, row);  //��� ���� �ٲ㼭 �־���
	}

	printf("���A : \n");  //��� A ���
	print_matrix(matrix_a, row, col);

	printf("���B : \n");  //��� B ���
	print_matrix(matrix_b, row, col);

	printf("��ĵ��� (A + B) : \n");  //��� A+B ���
	addition_matrix(matrix_a, matrix_b, matrix_sum, row, col);
	print_matrix(matrix_sum, row, col);

	printf("��Ļ��� (A - B) : \n");  //��� A-B ���
	subtraction_matrix(matrix_a, matrix_b, matrix_sub, row, col);
	print_matrix(matrix_sub, row, col);

    printf("A�� ��ġ��� : \n");  //��ġ��� ���

	transpose_matrix(matrix_a, matrix_t, row, col);
	print_matrix(matrix_t, col, row);

	printf("��İ��� (A X T) : \n");  //��� A X T ���
	if (row != col) {
		printf(" �Ұ����� �����Դϴ�.\n\n"); //����� ��, ���� ������ �ϱ⿡ �������� ������ �Ұ�����
				return 1;
	}
	
	else {  //������ �ϱ⿡ �����ϴٸ� multiply�Լ��� �־��ְ� print�Լ��� �������
		multiply_matrix(matrix_a, matrix_t, matrix_axt, row, col);
		print_matrix(matrix_axt, row, col);
	}

	free_matrix(matrix_a, row, col);  //�����Ҵ� ���� �Լ�
	free_matrix(matrix_b, row, col);
	free_matrix(matrix_sub, row, col);
	free_matrix(matrix_sum, row, col);
	free_matrix(matrix_axt, row, col);


	if (row == col) {  //��� ���� ���� �ٸ��� �����Ҵ��� ����������
		free_matrix(matrix_t, row, col);
	}
	if (row != col) {
		free_matrix(matrix_t, col, row);
	}
	free_matrix(matrix_axt, row, col);


	return 0;

}
int** create_matrix(int row, int col) {  //�����Ҵ��� ���ִ� �Լ�

	/* check pre conditions */  //��ó���˻�
	if(row <= 0 || col <=0) {
	printf("Check the sizes of row and col!\n");
	return NULL;
		}

	int **matrix;  //matrix �̸��� ���������� ����

	matrix = (int**)malloc(row * sizeof(int *));  
	for (int i = 0; i < row; ++i) {  //for���� ���� �����Ҵ�
		matrix[i] = (int *)malloc(col * sizeof(int));
		for (int j = 0; j < col; ++j) {
			matrix[i][j] = 0;
		}
	}

	/* check post conditions */  //��ó���˻�

	if(matrix == NULL) {
	printf(" ������ ����� �ƴմϴ�. "); 
	}
	return matrix;
}
int free_matrix(int** matrix, int row, int col) {  //�����Ҵ��� ����������

	for (int i = 0; i < row; ++i)  //for���� ���� ����������
		free(matrix[i]);
	free(matrix);

	return 0;
} 
void print_matrix(int** matrix, int row, int col) {  //����� ������ִ� �Լ�

	for (int i = 0; i < row; i++) //for���� ���Ͽ� ��, ���� �������
	{
		for (int j = 0; j < col; j++)
			printf("%3d ", matrix[i][j]);
		printf("\n");
	}
	printf("\n");

} 
int fill_data(int **matrix, int row, int col) { //filldata�Լ��� rand�Լ��� �̿��Ͽ� ���Ƿ� random ���� �����Ͽ� �־��ִ� ������ ��

	for (int i = 0; i < row; i++) {  //���� for���� ����Ͽ� ���� �־���
		for (int j = 0; j < col; j++) {
			matrix[i][j] = rand() % 20;    //rand�Լ��� ����Ͽ� 0����19���� ���� �Է¹ް� ����
		}
	}

	return **matrix;
} 
int transpose_matrix(int **matrix, int **matrix_t, int row, int col){  //��ġ��� �Լ�
    
	/* check pre conditions */  //��ó���˻�

   if(row <= 0 || col <=0) {
   printf("Check the sizes of row and col!\n");
   }
   
if( matrix ==0)
{
    return 1;
}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			matrix_t[j][i] = matrix[i][j];  //����� ��� ���� �ٲ���
		}
	}
  /* check post conditions */  //��ó���˻�
     if(matrix_t == NULL)
	  {
	printf(" ������ ����� �ƴմϴ�. ");

    }
	return matrix_t;

} 
int addition_matrix(int **matrix_a, int **matrix_b, int **matrix_sum,int row, int col) { // ���� �Լ�
    	/* check pre conditions */  //��ó���˻�

   if(row <= 0 || col <=0) {
   printf("Check the sizes of row and col!\n");
   return NULL;
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j]; //����� ������ ����
	}
	/* check post conditions */  //��ó���˻�
	if(matrix_sum == NULL) {
	printf(" ������ ����� �ƴմϴ�. ");

	}
	return matrix_sum;
}
int subtraction_matrix(int **matrix_a, int **matrix_b, int **matrix_sub,int row, int col) { // �E�� �Լ�
			
	/* check pre conditions */  //��ó���˻�

   if(row <= 0 || col <=0) {
   printf("Check the sizes of row and col!\n");
   return NULL;
	}



	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];  //����� ������ ����
	}
	/* check post conditions */  //��ó���˻�
	if(matrix_sub == NULL) {
	printf(" ������ ����� �ƴմϴ�. ");

	}
	return matrix_sub;
}
int multiply_matrix(int **matrix_a, int **matrix_t, int **matrix_axt,int row, int col) {  //���� �Լ�

		/* check pre conditions */  //��ó���˻�

   if(row <= 0 || col <=0) {
   printf("Check the sizes of row and col!\n");
   return NULL;
   }


	for (int i = 0; i < row; ++i) {  //matrix_axt �迭�� �ʱ�ȭ ������
		for (int j = 0; j < col; ++j) {
			matrix_axt[i][j] = 0;
		}
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			for (int k = 0; k < row; k++)
			{
				matrix_axt[i][j] += matrix_a[i][k] * matrix_t[k][j];  //������ �ʱ�ȭ ������ matrix_axt �迭�ȿ� ������ ���� �־���
			}

		}

	}
 	/* check post conditions */  //��ó���˻�
	if(matrix_axt == NULL) 
	{
	printf(" ������ ����� �ƴմϴ�. ");

	}
	return matrix_axt;
}
