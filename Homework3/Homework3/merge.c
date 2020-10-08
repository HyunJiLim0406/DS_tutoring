#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode* link;
}ListNode;

typedef struct {
	ListNode* head;
	ListNode* tail;
	int length;
}ListType;

void init(ListType* list) { //리스트 초기화
	list->length = 0;
	list->head = list->tail = NULL;
}

ListNode* get_node_at(ListType* list, int position) { //position에 있는 node 반환
	ListNode* tmp_node = list->head;
	if (position < 0)
		return NULL;
	for (int i = 0; i < position; i++) //position에 닿을 때까지 link 통해 이동
		tmp_node = tmp_node->link;
	return tmp_node;
}

void insert_last(ListType* list, ListNode* new_node) {
	if (list->head == NULL) { //비어있는 리스트였다면 헤드, 테일도 갱신
		new_node->link = NULL;
		list->head = new_node;
		list->tail = new_node;
	}
	else { //테일 갱신
		new_node->link = NULL;
		list->tail->link = new_node;
		list->tail = new_node;
	}
}

void add_last(ListType* list, element data) {
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	if (node == NULL) {
		printf("Memory allocation error\n");
		return;
	}
	node->data = data;
	insert_last(list, node);
	list->length++;
}

void display(ListType* list) { //헤드부터 시작해서 리스트가 끝날 때까지 data 출력
	ListNode* node = list->head;
	printf("( ");
	for (int i = 0; i < list->length; i++) {
		printf("%d ", node->data);
		node = node->link;
	}
	printf(" )\n");
}

//Time Complexity : 반복문이 a->length + b->length 만큼 돌기 때문에 T(n) = O(m + n)
void merge_list(ListType* list1, ListType* list2, ListType* result) {
	ListNode* a = list1->head;
	ListNode* b = list2->head;

	while (a && b) {
		if (a->data < b->data) { //a->data가 더 작다면 c 리스트에 a->data 삽입
			add_last(result, a->data);
			a = a->link;
		}
		else { //b->data가 더 작거나 같다면 c 리스트에 b->data 삽입
			add_last(result, b->data);
			b = b->link;
		}
	}
	for (; a != NULL; a = a->link) //a 리스트의 남은 데이터 삽입
		add_last(result, a->data);
	for (; b != NULL; b = b->link) //b 리스트의 남은 데이터 삽입
		add_last(result, b->data);
}

int main() {
	ListType a, b, c;
	init(&a);
	init(&b);
	init(&c);

	add_last(&a, 1);
	add_last(&a, 2);
	add_last(&a, 5);
	add_last(&a, 10);
	add_last(&a, 15);
	add_last(&a, 20);
	add_last(&a, 25);

	add_last(&b, 3);
	add_last(&b, 7);
	add_last(&b, 8);
	add_last(&b, 15);
	add_last(&b, 18);
	add_last(&b, 30);

	merge_list(&a, &b, &c);
	display(&c);
}