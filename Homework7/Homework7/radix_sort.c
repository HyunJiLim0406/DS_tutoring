#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define INPUT 1001
#define BUCKETS 64 // 24-bit 수를 4 segments로 나누니까 1개의 segment는 6-bit
#define DIGITS 4

int generate_rand() { // 110101101 등의 이진수 형태를 바로 십진수로 바꿈
	int num = 0, mul = 1;

	for (int i = 0; i < 24; i++) {
		int rd = rand() % 2; // 0 or 1
		num += (rd * mul);
		mul *= 2;
	}
	return num;
}

void radix_sort(int A[], int n) {
	int C[BUCKETS], B[INPUT] = { 0, };
	int factor = 1;
	int i;

	for (int d = 0; d < DIGITS; d++) {
		//counting sort
		memset(C, 0, sizeof(int) * BUCKETS); //배열 C를 0으로 초기화
		for (i = 0; i < n; i++)
			C[(A[i] / factor) % BUCKETS] += 1;
		for (i = 1; i < BUCKETS; i++)
			C[i] = C[i] + C[i - 1];
		for (i = n - 1; i > 0; i--) {
			B[C[(A[i] / factor) % BUCKETS]] = A[i];
			C[(A[i] / factor) % BUCKETS] -= 1;
		}

		for (i = 1; i < n; i++)
			A[i] = B[i];
		factor *= BUCKETS;
	}
}

bool check_sort(int A[], int n) { //제대로 정렬된건지 확인
	for (int i = 2; i < n; i++) {
		if (A[i] < A[i - 1])
			return false;
	}
	return true;
}

int main() {
	srand((unsigned)time(NULL));
	int A[INPUT];
	
	//방법 1 : 간단하지만 32767 보다 큰 소수는 포함되지 않고, 약수가 많은 합성수 위주로 값이 편향될 가능성이 있음
	for (int i = 1; i < INPUT; i++) {
		int front = rand() + 1; // 1 ~ 2^15
		int back = rand() % 512 + 1; // 1 ~ 2^9
		int num = front * back - 1; // 1 ~ 2^24-1

		A[i] = num;
	}

	//방법 2 : 해당 범위 모든 수를 포함할 수 있고, 편향도 없으나 굳이 이렇게까지?
	for (int i = 1; i < INPUT; i++) {
		A[i] = generate_rand();
	}
	
	radix_sort(A, INPUT);

	if (check_sort(A, INPUT)) { //제대로 정렬됐다면 처음 10개와 마지막 10개 데이터를 출력
		for (int i = 1; i <= 10; i++)
			printf("%d\n", A[i]);
		printf("...\n");
		for (int i = 991; i <= 1000; i++)
			printf("%d\n", A[i]);
	}
	else
		printf("Wrong\n");
}