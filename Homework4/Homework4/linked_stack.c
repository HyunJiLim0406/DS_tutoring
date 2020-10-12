// linked_stack.cpp : Defines the entry point for the console application.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef int element;

typedef struct StackNode {
	element item;
	struct StackNode* llink;
	struct StackNode* rlink;
} StackNode;

typedef struct {
	StackNode* top;
} LinkedStackType;

void init(LinkedStackType* s, StackNode *head)
{
	head->llink = head;
	head->rlink = head;
	s->top = head;
}

int is_empty(LinkedStackType* s, StackNode *head)
{
	return (s->top == head);
}

void push(LinkedStackType* s, element item)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	if (temp == NULL) {
		fprintf(stderr, "Memory allocation error\n");
		return;
	}

	else {
		temp->item = item;
		temp->llink = s->top->llink;
		temp->rlink = s->top;
		//아래 두 줄 순서 바뀌면 안됨
		s->top->llink->rlink = temp;
		s->top->llink = temp;
		s->top = temp;
	}
}

element pop(LinkedStackType* s, StackNode *head)
{
	if (is_empty(s, head)) {
		fprintf(stderr, "Stack is empty\n");
		exit(1);
	}
	else {
		StackNode* temp = s->top;
		int item = temp->item;
		temp->llink->rlink = temp->rlink;
		temp->rlink->llink = temp->llink;
		s->top = s->top->rlink;
		free(temp);
		return item;
	}
}

element peek(LinkedStackType* s, StackNode *head)
{
	if (is_empty(s, head)) {
		fprintf(stderr, "Stack is empty\n");
		exit(1);
	}
	else {
		return s->top->item;
	}
}

void main()
{
	LinkedStackType s;
	StackNode head_node;
	init(&s, &head_node);
	push(&s, 1);
	push(&s, 2);
	push(&s, 3);

	printf("%d\n", pop(&s, &head_node));
	printf("%d\n", pop(&s, &head_node));
	printf("%d\n", pop(&s, &head_node));
}