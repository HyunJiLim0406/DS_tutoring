// huffman.cpp : Defines the entry point for the console application.
//

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#define MAX_ELEMENT 1000
#define MAX_BIT		10
#define MAX_CHAR	20
#define TRUE 1
#define FALSE 0

// Input data for huffman code
typedef struct input_huff {
	char* data;		// Character array (a ~ f)
	int* freq;		// Frequency array
	int size;		// Number of characters
} input_huff;

// Structure for huffman binary tree
typedef struct TreeNode {
	char data;			// Character (a ~ f)
	int key;			// Frequency
	int bits[MAX_BIT];	// Huffman codeword
	int bit_size;		// Huffman codeword's size
	struct TreeNode* l;	// Left child of huffman binary tree
	struct TreeNode* r;	// Right child of huffman binary tree
} TreeNode;

// Structure for bits stream
typedef struct bits_stream {
	int* stream;
	int length;
} bits_stream;

// Elements used in the heap
typedef struct element {
	TreeNode* ptree;
	int key;	// frequency of each character
} element;

// Heap
typedef struct HeapType {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

int** m_LUT, * m_bit_size;
int	m_char_size = 6;

// Initialization
void init(HeapType* h)
{
	h->heap_size = 0;
}
//
int is_empty(HeapType* h)
{
	if (h->heap_size == 0)
		return TRUE;
	else
		return FALSE;
}

void insert_min_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);

	// compare it with the parent node in an order from the leaf to the root
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item; // Insert new node
}

element delete_min_heap(HeapType* h)
{
	int parent, child;
	element item, temp;
	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)
			child++;
		if (temp.key <= h->heap[child].key) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

// Node generation in binary tree
TreeNode* make_tree(TreeNode* left, TreeNode* right)
{
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	if (node == NULL) {
		fprintf(stderr, "Memory allocation error\n");
		exit(1);
	}
	node->l = left;
	node->r = right;
	return node;
}

// Binary tree removal
void destroy_tree(TreeNode* root)
{
	if (root == NULL) return;
	destroy_tree(root->l);
	destroy_tree(root->r);
	free(root);
}

// Huffman code generation
element huffman_tree(input_huff* huff)
{
	int i;
	TreeNode* node, * x;
	HeapType heap;
	element e, e1, e2;
	init(&heap);

	int n = huff->size;

	for (i = 0; i < n; i++) {
		node = make_tree(NULL, NULL);
		e.ptree = node;
		node->data = huff->data[i];
		e.key = node->key = huff->freq[i];
		memset(node->bits, 0, sizeof(int) * MAX_BIT);
		node->bit_size = 0;

		insert_min_heap(&heap, e);
	}

	for (i = 1; i < n; i++) {
		// Delete two nodes with minimum values
		e1 = delete_min_heap(&heap);
		e2 = delete_min_heap(&heap);

		// Merge two nodes
		x = make_tree(e1.ptree, e2.ptree);
		e.ptree = x;
		x->data = NULL;
		e.key = x->key = e1.key + e2.key;
		memset(x->bits, 0, sizeof(int) * MAX_BIT);
		x->bit_size = 0;

		insert_min_heap(&heap, e);
	}
	e = delete_min_heap(&heap); // Final Huffman binary tree

	return e;
	//destroy_tree(e.ptree);
}

// Generate the huffman codeword from the huffman binary tree
// Hint: use the recursion for tree traversal
// input: root node
// output: m_LUT, m_bit_size
// 백트래킹 재귀함수 사용
void huffman_traversal(TreeNode* node, int* c_array, int cnt)
{
	int c_index;
	// 왼쪽 노드가 있으면 왼쪽으로 가면서 0 입력
	if (node->l != NULL) {
		c_array[cnt] = 0;
		huffman_traversal(node->l, c_array, cnt + 1);
	}
	// 오른쪽 노드가 있으면 오른쪽으로 가면서 1 입력
	if (node->r != NULL) {
		c_array[cnt] = 1;
		huffman_traversal(node->r, c_array, cnt + 1);
	}
	// leaf node 일 때 노드의 데이터를 확인 후 지금까지 입력된 값을 해당 m_LUT에 대입
	if ((node->l == NULL) && (node->r == NULL)) {
		switch (node->data) {
		case 'a':
			c_index = 0;
			break;
		case 'b':
			c_index = 1;
			break;
		case 'c':
			c_index = 2;
			break;
		case 'd':
			c_index = 3;
			break;
		case 'e':
			c_index = 4;
			break;
		case 'f':
			c_index = 5;
			break;
		}
		for (int j = 0; j < cnt; j++) {
			m_LUT[c_index][j] = c_array[j];
		}
		m_bit_size[c_index] = cnt;
	}
}

int** mem_2D_int(int row, int col)
{
	int** m2 = (int**)malloc(sizeof(int*) * row);
	for (int i = 0; i < row; i++)
		m2[i] = (int*)malloc(sizeof(int) * col);
	return m2;
}

void print_codeword()
{
	printf("* Huffman codeword\n");
	for (int i = 0; i < m_char_size; i++)
	{
		switch (i) {
		case 0:
			printf("%c: ", 'a');
			break;
		case 1:
			printf("%c: ", 'b');
			break;
		case 2:
			printf("%c: ", 'c');
			break;
		case 3:
			printf("%c: ", 'd');
			break;
		case 4:
			printf("%c: ", 'e');
			break;
		case 5:
			printf("%c: ", 'f');
			break;
		}

		for (int j = 0; j < m_bit_size[i]; j++)
			printf("%d", m_LUT[i][j]);

		printf("\n");
	}

}

// Input: 'str'
// Output: 'bits_stream' (consisting of 0 or 1)
// 'bits_stream' is generated using 'm_LUT' generated by the huffman binary tree
// Return the total length of bits_stream
void huffman_encoding(char* str, bits_stream* bits_str)
{
	// str을 char단위로 나눠 해당 데이터에 대입되는 m_LUT 값을 저장
	int interval = 0;
	int i, j;
	for (i = 0; i < strlen(str); i++) {
		switch (str[i]) {
		case 'a':
			for (j = 0; j < m_bit_size[0]; j++) {
				bits_str->stream[interval] = m_LUT[0][j];
				interval++;
			}
			break;
		case 'b':
			for (j = 0; j < m_bit_size[1]; j++) {
				bits_str->stream[interval] = m_LUT[1][j];
				interval++;
			}
			break;
		case 'c':
			for (j = 0; j < m_bit_size[2]; j++) {
				bits_str->stream[interval] = m_LUT[2][j];
				interval++;
			}
			break;
		case 'd':
			for (j = 0; j < m_bit_size[3]; j++) {
				bits_str->stream[interval] = m_LUT[3][j];
				interval++;
			}
			break;
		case 'e':
			for (j = 0; j < m_bit_size[4]; j++) {
				bits_str->stream[interval] = m_LUT[4][j];
				interval++;
			}
			break;
		case 'f':
			for (j = 0; j < m_bit_size[5]; j++) {
				bits_str->stream[interval] = m_LUT[5][j];
				interval++;
			}
			break;
		}
	}
	bits_str->length = interval;

	printf("\n* Huffman encoding\n");
	printf("total length of bits stream: %d\n", interval);
	printf("bits stream: ");
	for (int i = 0; i < interval; i++)
		printf("%d", bits_str->stream[i]);
	printf("\n");
}

// input: 'bits_stream' and 'total_length'
// output: 'decoded_str'
int huffman_decoding(bits_stream* bits_str, TreeNode* node, char* decoded_str)
{
	// TreeNode를 탐색하면서 leaf node를 만났을 때 해당 node의 data를 가져온다
	TreeNode* d_index; //root 저장용
	d_index = node;
	int index_char = 0;
	for (int i = 0; i < bits_str->length; i++) {
		node = d_index;
		while (node) {
			if (bits_str->stream[i] == 0) {
				node = node->l;
			}
			else if (bits_str->stream[i] == 1) {
				node = node->r;
			}
			//leaf node인지 확인
			if (node->l == NULL && node->r == NULL)
				break;
			i++;
		}
		decoded_str[index_char] = node->data;
		index_char++;
	}

	printf("\n* Huffman decoding\n");
	printf("total number of decoded chars: %d\n", index_char);
	printf("decoded chars: ");
	for (int i = 0; i < index_char; i++)
		printf("%c", decoded_str[i]);
	printf("\n");

	return index_char;
}

void main()
{
	int arr[10];
	char data[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
	int freq[] = { 45, 13, 12, 16, 9, 5 };

	input_huff* huff1 = (input_huff*)malloc(sizeof(input_huff));
	huff1->data = data;
	huff1->freq = freq;
	huff1->size = m_char_size;

	// m_LUT: each row corresponds to the codeword for each character
	// m_bit_size: 1D array of codeword size for each character
	// For instance, a = 0, b = 101, ...
	// 1st row of 'm_LUT': 0 0 ... 0
	// 2nd row of 'm_LUT': 1 0 1 ...0
	// m_bit_size = {1, 3, ...}
	m_LUT = mem_2D_int(m_char_size, MAX_BIT);
	m_bit_size = (int*)malloc(sizeof(int) * m_char_size);

	// Generate the huffman binary tree on heap
	// 'element_root': element containing the root node
	element element_root = huffman_tree(huff1);

	// Generate the huffman codeword from the huffman binary tree
	huffman_traversal(element_root.ptree, arr, 0);

	//printf out the huffman codeword
	print_codeword();

	//example of input data
	char str[MAX_CHAR] = { "abacdebaf" };
	//char str[MAX_CHAR] = { "ab" };
	char decoded_str[MAX_CHAR];

	printf("\n* input chars: ");
	for (int i = 0; i < strlen(str); i++)
		printf("%c", str[i]);
	printf("\n");

	//start encoding
	bits_stream* bits_str1 = (bits_stream*)malloc(sizeof(bits_stream));
	bits_str1->stream = (int*)malloc(sizeof(int) * MAX_BIT * MAX_CHAR);
	memset(bits_str1->stream, -1, sizeof(int) * MAX_BIT * MAX_CHAR);
	bits_str1->length = 0;

	huffman_encoding(str, bits_str1);

	//start decoding	
	int decoded_char_length = huffman_decoding(bits_str1, element_root.ptree, decoded_str);
}