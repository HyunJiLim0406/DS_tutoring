#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 200

typedef struct element {
	int key;
}element;

typedef struct {
	element* heap;
	int heap_size;
}HeapType;

void init(HeapType* h) {
	h->heap_size = 0;
}

void insert_min_heap(HeapType* h, element item) {
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

//insert_min_heap과 비슷함
void decrease_key_min_heap(HeapType* h, int point, int key) {
	element temp;
	if (key >= h->heap[point].key) {
		printf("error : new key is not smaller than current key\n");
	}
	h->heap[point].key = key;
	int i = point;
	while ((i != 1) && (h->heap[i].key < h->heap[i / 2].key)) {
		temp = h->heap[i];
		h->heap[i] = h->heap[i / 2];
		h->heap[i / 2] = temp;
		i /= 2;
	}
}

//delete_min_heap과 비슷함
void increase_key_min_heap(HeapType* h, int point, int key) {
	int parent, child;
	element temp;
	if (key <= h->heap[point].key) {
		printf("error : new key is not larger than current key\n");
	}
	h->heap[point].key = key;
	temp = h->heap[point];
	parent = point;
	if ((point * 2) <= h->heap_size)
		child = point * 2;
	while (child <= h->heap_size) {
		if ((child < h->heap_size) && (h->heap[child].key > h->heap[child + 1].key))
			child++;
		if (temp.key <= h->heap[child].key)
			break;
		h->heap[parent] = h->heap[child];
		h->heap[child] = temp;
		child *= 2;
	}
}

void main() {
	int input_size = 10;
	int input_data[10] = { 1,4,2,7,5,3,3,7,8,9 };
	element* d = (element*)malloc(sizeof(element));
	HeapType* h = (HeapType*)malloc(sizeof(HeapType));
	h->heap = (element*)malloc(sizeof(element) * ((input_size)+1));
	for (int i = 0; i < input_size; i++) {
		d[i].key = input_data[i];
	}
	init(h);
	for (int i = 0; i < input_size; i++) {
		insert_min_heap(h, d[i]);
	}

	printf("Input data\n");
	int flag = 1;
	for (int i = 0; i < input_size; i++) {
		printf("%d ", h->heap[i + 1].key);
		if ((i + 1) == flag) {
			printf("\n");
			flag = flag * 2 + 1;
		}
	}
	printf("\n");

	decrease_key_min_heap(h, 4, 3);
	increase_key_min_heap(h, 3, 10);

	printf("\n");
	printf("Output data\n");
	flag = 1;
	for (int i = 0; i < input_size; i++) {
		printf("%d ", h->heap[i + 1].key);
		if ((i + 1) == flag) {
			printf("\n");
			flag = flag * 2 + 1;
		}
	}
	printf("\n");
}