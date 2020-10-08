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
ListType list1;

void init(ListType* list) { //리스트 초기화
	list->length = 0;
	list->head = list->tail = NULL;
}

bool is_empty(ListType* list) { //리스트 헤드가 NULL이면 true 반환
	if (list->head == NULL)
		return true;
	else
		return false;
}

int get_length(ListType* list) { //리스트 길이 반환
	return list->length;
}

ListNode* get_node_at(ListType* list, int position) { //position에 있는 node 반환
	ListNode* tmp_node = list->head;
	if (position < 0)
		return NULL;
	for (int i = 0; i < position; i++) //position에 닿을 때까지 link 통해 이동
		tmp_node = tmp_node->link;
	return tmp_node;
}

void insert_node(ListType* list, ListNode* p, ListNode* new_node) {
	if (list->head == NULL) { //비어있는 리스트였다면 헤드, 테일도 갱신
		new_node->link = NULL;
		list->head = new_node;
		list->tail = new_node;
	}
	else {
		if (p == NULL) {
			printf("The preceding node cannot be NULL.\n");
			return;
		}
		else {
			new_node->link = p->link;
			p->link = new_node;
		}
	}
}

void add(ListType* list, int position, element data) {
	ListNode* p;
	if ((position >= 0) && (position <= list->length)) {
		ListNode* node = (ListNode*)malloc(sizeof(ListNode));
		if (node == NULL) {
			printf("Memory allocation error\n");
			return;
		}
		node->data = data;
		p = get_node_at(list, position - 1); //before node를 p에 저장
		insert_node(list, p, node);
		list->length++;
	}
}

void insert_first(ListType* list, ListNode* new_node) {
	if (list->head == NULL) { //비어있는 리스트였다면 헤드, 테일도 갱신
		new_node->link = NULL;
		list->head = new_node;
		list->tail = new_node;
	}
	else { //헤드 갱신
		new_node->link = list->head;
		list->head = new_node;
	}
}

void add_first(ListType* list, element data) {
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	if (node == NULL) {
		printf("Memory allocation error\n");
		return;
	}
	node->data = data;
	insert_first(list, node);
	list->length++;
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

void remove_node(ListType* list, ListNode* p, ListNode* removed) {
	if (list->head == NULL) {
		printf("The list is blank.\n");
		return;
	}
	else {
		if (p == NULL) {
			printf("The preceding node cannot be NULL.\n");
			return;
		}
		else {
			p->link = removed->link;
			free(removed);
		}
	}
}

void delete(ListType* list, int position) {
	if (!is_empty(list) && (position >= 0) && (position < list->length)) {
		ListNode* p = get_node_at(list, position - 1); //before node를 p에 저장
		ListNode* removed = get_node_at(list, position); //삭제할 노드를 removed에 저장
		remove_node(list, p, removed);
		list->length--;
	}
}

void remove_first(ListType* list) {
	if (list->head == NULL) {
		printf("The list is blank.\n");
		return;
	}
	else {
		ListNode* removed = list->head;
		list->head = removed->link;
		free(removed);
		if (list->head == NULL) //남은 노드가 없는 경우
			list->tail = NULL;
	}
}

void delete_first(ListType* list) {
	if (!is_empty(list)) {
		remove_first(list);
		list->length--;
	}
}

void remove_last(ListType* list) {
	if (list->tail == NULL) {
		printf("The list is blank.\n");
		return;
	}
	else {
		ListNode* removed = list->tail;
		int position = list->length - 1; //tail의 postition
		list->tail = get_node_at(list, position - 1); //before node
		free(removed);
		if (list->tail == NULL) //남은 노드가 없는 경우
			list->head = NULL;
		else //남은 노드가 있는 경우
			list->tail->link = NULL;
	}
}

void delete_last(ListType* list) {
	if (!is_empty(list)) {
		remove_last(list);
		list->length--;
	}
}

element get_entry(ListType* list, int position) { //특정 위치(position)의 data를 반환
	ListNode* p;
	if (position >= list->length) {
		printf("Position error\n");
		return;
	}
	p = get_node_at(list, position);
	return p->data;
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

bool is_in_list(ListType* list, element item) { //특정 data가 리스트에 있는지 확인
	ListNode* p;
	p = list->head;
	while ((p != NULL)) {
		if (p->data == item) //찾는 data를 발견했다면 break
			break;
		p = p->link; //아니면 다음 노드로 이동
	}
	if (p == NULL)
		return false;
	else
		return true;
}

int main() {
	init(&list1);
	add_first(&list1, 20);
	add_last(&list1, 30);
	add_first(&list1, 10);
	add_last(&list1, 40);
	add(&list1, 2, 70);
	display(&list1);

	delete(&list1, 2);
	delete_first(&list1);
	delete_last(&list1);
	display(&list1);

	printf("%s\n", is_in_list(&list1, 20) == true ? "TRUE" : "FALSE");
	printf("%d\n", get_entry(&list1, 0));
}