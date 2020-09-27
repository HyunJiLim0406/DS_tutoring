#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double*** mem_alloc_3D_double(int x, int y, int z) {
	double*** matrix = (double***)malloc(sizeof(double**) * x); //1차원 할당
	for (int i = 0; i < x; i++) {
		matrix[i] = (double**)malloc(sizeof(double*) * y); //2차원 할당
		for (int j = 0; j < y; j++) {
			matrix[i][j] = (double*)malloc(sizeof(double) * z); //3차원 할당
		}
	}
	return matrix;
}

void numbering(double*** matrix, int x, int y, int z) {
	srand(time(NULL));
	double start_num = (rand() % 10) + 10; //10~19 사이의 난수 생성

	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			for (int k = 0; k < z; k++) { //처음 생성한 난수 하나씩 증가하며 대입
				matrix[i][j][k] = start_num;
				start_num++;
			}
		}
	}
}

void addition_3D(double*** m1, double*** m2, int x, int y, int z) { //더해서 바로 프린트 하는 함수
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			for (int k = 0; k < z; k++)
				printf("%.2f ", m1[i][j][k] + m2[i][j][k]);
			printf("\n");
		}
		printf("\n");
	}
	printf("\n");
}

void mem_dealloc_3D_double(double*** m) {
	if (m != NULL) {
		free(m[0][0]); //3차원 해제
		free(m[0]); //2차원 해제
		free(m); //1차원 해제
		m = NULL;
	}
}

int main() {
	double*** A = mem_alloc_3D_double(2, 3, 4);
	double*** B = mem_alloc_3D_double(2, 3, 4);

	numbering(A, 2, 3, 4);
	numbering(B, 2, 3, 4);

	addition_3D(A, B, 2, 3, 4);

	mem_dealloc_3D_double(A);
	mem_dealloc_3D_double(B);
}