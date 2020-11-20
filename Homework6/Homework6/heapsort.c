// heapsort.cpp : Defines the entry point for the console application.
//

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "time.h"
#include "stdbool.h"

#define MAX_ELEMENT 2000
typedef struct element {
	int key;
} element;

typedef struct {
	element* heap;
	int heap_size;
} HeapType;

// Integer random number generation function between 0 and n-1
int random(int n)
{
	return rand() % n;
}

// Initialization
void init(HeapType* h) {
	h->heap_size = 0;
}

// Insert the item at heap h, (# of elements: heap_size)
void insert_max_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);

	// The process of comparing with the parent node as it traverses the tree
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item; // Insert new node
}

// Delete the root at heap h, (# of elements: heap_size)
element delete_max_heap(HeapType* h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// Find a smaller child node
		if ((child < h->heap_size) &&
			(h->heap[child].key) < h->heap[child + 1].key)
			child++;
		if (temp.key >= h->heap[child].key) break;
		// Move down one level
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

void build_max_heap(HeapType* h)
{
	int i;
	int parent, child;
	int flag = h->heap_size / 2; //처음으로 leaf node가 아닌 node
	element temp;

	// delete와 매우 유사
	for (i = flag; i >= 1; i--) {
		parent = i;
		child = i * 2;
		while (child <= h->heap_size) {
			//right child가 있는지 확인
			if ((parent * 2 + 1) <= h->heap_size) {
				if ((child < h->heap_size) && ((h->heap[child].key) < (h->heap[child + 1].key))) {
					child++;
				}
			}
			if (h->heap[parent].key >= h->heap[child].key)
				break;
			temp = h->heap[parent];
			h->heap[parent] = h->heap[child];
			h->heap[child] = temp;
			parent = child;
			child *= 2;
		}
	}
}

//input: heap 'h'
//output: sorted element array 'a'
void heap_sort(HeapType* h, element* a, int n)
{
	int i;

	build_max_heap(h);
	for (i = (n - 1); i >= 0; i--) {
		a[i] = delete_max_heap(h);
	}
}

bool check_sort_results(element* output, int n)
{
	bool index = 1;
	for (int i = 0; i < n - 1; i++)
		if (output[i].key > output[i + 1].key)
		{
			index = 0;
			break;
		}
	return index;
}

void main()
{
	//Intializes random number generator 

	int input_size = 5000;	//10, 100, 1000
	int data_maxval = 10000;

	HeapType* h1 = (HeapType*)malloc(sizeof(HeapType));
	// 'heap' is allocated according to 'input_size'.  heap starts with 1, so 'input_size+1' is used.
	h1->heap = (element*)malloc(sizeof(element) * (input_size + 1));

	// output: sorted result
	element* output = (element*)malloc(sizeof(element) * input_size);

	// Generate an input data randomly
	for (int i = 0; i < input_size; i++)
		h1->heap[i + 1].key = random(data_maxval);	// note) heap starts with 1.
	h1->heap_size = input_size;

	if (input_size < 20) {
		printf("Input data\n");
		for (int i = 0; i < input_size; i++)	printf("%d\n", h1->heap[i + 1].key);
		printf("\n");
	}

	//ms 단위로 측정
	double start = clock();

	// Perform the heap sort
	heap_sort(h1, output, input_size);

	double end = clock();

	if (input_size < 20) {
		printf("Sorted data\n");
		for (int i = 0; i < input_size; i++)	printf("%d\n", output[i].key);
		printf("\n");
	}

	// Your code should pass the following function (returning 1)
	if (check_sort_results(output, input_size))
		printf("Sorting result is correct.\n");
	else
		printf("Sorting result is wrong.\n");

	printf("Runtime is %f", (double)(end - start) / CLOCKS_PER_SEC);
}