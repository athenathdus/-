
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** create_matrix(int row, int col); //동적할당을 해줌 (주어진 create_matrix() 함수 사용)
int free_matrix(int** matrix, int row, int col); //동적할당 해제시켜줌   (주어진 free_matrix 함수 사용)
void print_matrix(int** matrix, int row, int col); //행렬을 출력해줌  (주어진 print_matrix 함수 사용)
int fill_data(int **matrix, int row, int col); //행렬을 random한 값으로 받음 (주어진 fill_data 함수 사용)
int transpose_matrix(int **matrix, int **matrix_t, int row, int col); //행렬의 전치 (주어진 transpose_matrix 함수 사용)
int addition_matrix(int **matrix_a, int **matrix_b, int **matrix_sum, int row, int col); //행렬의 덧셈 (주어진 addition_matrix 함수 사용)
int subtraction_matrix(int **matrix_a, int **matrix_b, int **matrix_sub, int row, int col); //행렬의 뺄셈 (주어진 subtraction_matrix 함수 사용)
int multiply_matrix(int **matrix_a, int **matrix_t, int **matrix_axt, int row, int col); //행렬의 곱셈 (주어진 multiply_matrix 함수 사용)


int main() {

   printf(" [----- [박소연] [2019038079] -----] \n");
    int row, col;  //행, 열 선언
	int **matrix_a;  //필요한 변수들 선언
	int **matrix_b;
	int **matrix_sum;
	int **matrix_axt;
	int **matrix_t;
	int **matrix_sub;
	

	srand(time(NULL)); //랜덤함수의 초기화
	printf("행과 열 입력하세요 (예시 : 3 4) : ");  
	scanf("%d %d", &row, &col);  //행렬의 행, 열의 값을 입력받음(주어진 scanf()사용)

	if (row <= 0 || col <= 0) {  //입력받은 값이 하나라도 0보다 작을 경우, 행렬의 수를 다시 입력받기 위함
		printf("행과 열을 1 이상의 수로 다시 입력해주세요\n 행과 열 입력하세요 (예시 : 3 4) : "); 
		scanf("%d %d", &row, &col);
	}
	
	matrix_a = create_matrix(row, col);  //create_matrix함수를 통해 동적할당 해줌
	matrix_b = create_matrix(row, col);
	matrix_sub = create_matrix(row, col);  
	matrix_sum = create_matrix(row, col); 
	matrix_axt = create_matrix(row, col); 


    fill_data(matrix_a, row, col); //fil_data함수로 값을 보내줌
	fill_data(matrix_b, row, col);

	if (row == col) {  //만약 행과 열이 같을경우
		matrix_t = create_matrix(row, col);  //행과 열을 그대로 넣어줌
	}

	else {
		matrix_t = create_matrix(col, row);  //행과 열을 바꿔서 넣어줌
	}

	printf("행렬A : \n");  //행렬 A 출력
	print_matrix(matrix_a, row, col);

	printf("행렬B : \n");  //행렬 B 출력
	print_matrix(matrix_b, row, col);

	printf("행렬덧셈 (A + B) : \n");  //행렬 A+B 출력
	addition_matrix(matrix_a, matrix_b, matrix_sum, row, col);
	print_matrix(matrix_sum, row, col);

	printf("행렬뺄셈 (A - B) : \n");  //행렬 A-B 출력
	subtraction_matrix(matrix_a, matrix_b, matrix_sub, row, col);
	print_matrix(matrix_sub, row, col);

    printf("A의 전치행렬 : \n");  //전치행렬 출력

	transpose_matrix(matrix_a, matrix_t, row, col);
	print_matrix(matrix_t, col, row);

	printf("행렬곱셈 (A X T) : \n");  //행렬 A X T 출력
	if (row != col) {
		printf(" 불가능한 곱셈입니다.\n\n"); //행렬의 행, 열이 곱셈을 하기에 적합하지 않으면 불가능함
				return 1;
	}
	
	else {  //곱셈을 하기에 적합하다면 multiply함수에 넣어주고 print함수로 출력해줌
		multiply_matrix(matrix_a, matrix_t, matrix_axt, row, col);
		print_matrix(matrix_axt, row, col);
	}

	free_matrix(matrix_a, row, col);  //동적할당 해제 함수
	free_matrix(matrix_b, row, col);
	free_matrix(matrix_sub, row, col);
	free_matrix(matrix_sum, row, col);
	free_matrix(matrix_axt, row, col);


	if (row == col) {  //행과 열이 같던 다르던 동적할당을 해제시켜줌
		free_matrix(matrix_t, row, col);
	}
	if (row != col) {
		free_matrix(matrix_t, col, row);
	}
	free_matrix(matrix_axt, row, col);


	return 0;

}
int** create_matrix(int row, int col) {  //동적할당을 해주는 함수

	/* check pre conditions */  //전처리검사
	if(row <= 0 || col <=0) {
	printf("Check the sizes of row and col!\n");
	return NULL;
		}

	int **matrix;  //matrix 이름의 이중포인터 선언

	matrix = (int**)malloc(row * sizeof(int *));  
	for (int i = 0; i < row; ++i) {  //for문을 통한 동적할당
		matrix[i] = (int *)malloc(col * sizeof(int));
		for (int j = 0; j < col; ++j) {
			matrix[i][j] = 0;
		}
	}

	/* check post conditions */  //후처리검사

	if(matrix == NULL) {
	printf(" 적절한 결과가 아닙니다. "); 
	}
	return matrix;
}
int free_matrix(int** matrix, int row, int col) {  //동적할당을 해제시켜줌

	for (int i = 0; i < row; ++i)  //for문을 통해 해제시켜줌
		free(matrix[i]);
	free(matrix);

	return 0;
} 
void print_matrix(int** matrix, int row, int col) {  //행렬을 출력해주는 함수

	for (int i = 0; i < row; i++) //for문을 통하여 행, 열을 출력해줌
	{
		for (int j = 0; j < col; j++)
			printf("%3d ", matrix[i][j]);
		printf("\n");
	}
	printf("\n");

} 
int fill_data(int **matrix, int row, int col) { //filldata함수가 rand함수를 이용하여 임의로 random 값을 지정하여 넣어주는 역할을 함

	for (int i = 0; i < row; i++) {  //이중 for문을 사용하여 값을 넣어줌
		for (int j = 0; j < col; j++) {
			matrix[i][j] = rand() % 20;    //rand함수를 사용하여 0부터19까지 값을 입력받게 해줌
		}
	}

	return **matrix;
} 
int transpose_matrix(int **matrix, int **matrix_t, int row, int col){  //전치행렬 함수
    
	/* check pre conditions */  //전처리검사

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
			matrix_t[j][i] = matrix[i][j];  //행렬의 행과 열을 바꿔줌
		}
	}
  /* check post conditions */  //후처리검사
     if(matrix_t == NULL)
	  {
	printf(" 적절한 결과가 아닙니다. ");

    }
	return matrix_t;

} 
int addition_matrix(int **matrix_a, int **matrix_b, int **matrix_sum,int row, int col) { // 덧셈 함수
    	/* check pre conditions */  //전처리검사

   if(row <= 0 || col <=0) {
   printf("Check the sizes of row and col!\n");
   return NULL;
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j]; //행렬의 덧셈을 해줌
	}
	/* check post conditions */  //후처리검사
	if(matrix_sum == NULL) {
	printf(" 적절한 결과가 아닙니다. ");

	}
	return matrix_sum;
}
int subtraction_matrix(int **matrix_a, int **matrix_b, int **matrix_sub,int row, int col) { // 뺼셈 함수
			
	/* check pre conditions */  //전처리검사

   if(row <= 0 || col <=0) {
   printf("Check the sizes of row and col!\n");
   return NULL;
	}



	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];  //행렬의 뺄셈을 해줌
	}
	/* check post conditions */  //후처리검사
	if(matrix_sub == NULL) {
	printf(" 적절한 결과가 아닙니다. ");

	}
	return matrix_sub;
}
int multiply_matrix(int **matrix_a, int **matrix_t, int **matrix_axt,int row, int col) {  //곱셈 함수

		/* check pre conditions */  //전처리검사

   if(row <= 0 || col <=0) {
   printf("Check the sizes of row and col!\n");
   return NULL;
   }


	for (int i = 0; i < row; ++i) {  //matrix_axt 배열을 초기화 시켜줌
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
				matrix_axt[i][j] += matrix_a[i][k] * matrix_t[k][j];  //위에서 초기화 시켜준 matrix_axt 배열안에 곱셈한 값을 넣어줌
			}

		}

	}
 	/* check post conditions */  //후처리검사
	if(matrix_axt == NULL) 
	{
	printf(" 적절한 결과가 아닙니다. ");

	}
	return matrix_axt;
}
