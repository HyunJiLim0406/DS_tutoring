#include <stdio.h>
#include <stdbool.h>
#define MAX_TERMS 10

typedef struct {
	int row;
	int col;
	int value;
}element;

typedef struct SparseMatrix {
	element data[MAX_TERMS];
	int rows;
	int cols;
	int terms;
}SparseMatrix;

void transpose_matrix(SparseMatrix *m1, SparseMatrix *m2) {
	m2->rows = m1->rows;
	m2->cols = m1->cols;
	m2->terms = m1->terms;
	for (int i = 0; i < m1->terms; i++) { //col과 row를 바꿔주기
		m2->data[i].col = m1->data[i].row;
		m2->data[i].row = m1->data[i].col;
		m2->data[i].value = m1->data[i].value;
	}
}

void print_matrix(SparseMatrix m) { //방법 1
	bool isZero; //0을 프린트 해야하는지 판단하는 bool 변수

	for (int i = 0; i < m.rows; i++) {
		for (int j = 0; j < m.cols; j++) {
			isZero = true;
			for (int k = 0; k < m.terms; k++) { //row, col 오름차순으로 미리 정렬한다면 굳이 매번 데이터를 모두 확인할 필요 없음
				if (i == m.data[k].row && j == m.data[k].col) {
					isZero = false; //해당 위치에 value값이 있다는 뜻이므로 isZero를 false로
					printf("%d ", m.data[k].value);
					break;
				}
			}
			if (isZero) //루프를 돈 뒤 isZero가 true라면 0을 프린트 
				printf("0 ");
		}
		printf("\n");
	}
	printf("\n");
}

void print_matrix_2(SparseMatrix m) { //방법 2
	//SparseMatrix 크기의 2차원 배열을 동적 할당
	int** temp = (int**)malloc(sizeof(int*) * m.rows);
	for (int i = 0; i < m.rows; i++)
		temp[i] = (int*)malloc(sizeof(int) * m.cols);

	for (int i = 0; i < m.rows; i++) { //2차원 배열의 모든 값을 0으로 초기화
		for (int j = 0; j < m.cols; j++)
			temp[i][j] = 0;
	}
	for (int i = 0; i < m.terms; i++) //SparseMatrix의 value들을 2차원 배열에 대입
		temp[m.data[i].row][m.data[i].col] = m.data[i].value;

	for (int i = 0; i < m.rows; i++) { //출력
		for (int j = 0; j < m.cols; j++)
			printf("%d ", temp[i][j]);
		printf("\n");
	}
	printf("\n");
}

int main() {
	SparseMatrix B = { {{0,3,7},{1,0,9},{1,5,8},{3,0,6},{3,1,5},{4,5,1},{5,2,2}},6,6,7 };
	SparseMatrix B_t;
	
	transpose_matrix(&B, &B_t); //B_t 초기화 하지 않아서 포인터로 안받으면 빌드 오류
	print_matrix(B);
	print_matrix_2(B_t);
}