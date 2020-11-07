#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right, * parent;
} TreeNode;

//	  G
//  C	 F
// A B	D E

TreeNode n1 = { 'A',NULL,NULL,NULL };
TreeNode n2 = { 'B',NULL,NULL,NULL };
TreeNode n3 = { 'C',&n1,&n2,NULL };
TreeNode n4 = { 'D',NULL,NULL,NULL };
TreeNode n5 = { 'E',NULL,NULL,NULL };
TreeNode n6 = { 'F',&n4,&n5,NULL };
TreeNode n7 = { 'G',&n3,&n6,NULL };
TreeNode* exp = &n7;

TreeNode* tree_predecessor(TreeNode* p) {
	TreeNode* pred;
	//p's left subtree is not null
	if (p->left != NULL) { //rightmost node of left subtree
		pred = p->left;
		p = pred->right;
		while (pred->right != NULL) {
			pred = p;
			p = p->right;
		}
	}
	//p's left subtree is null
	else {
		pred = p->parent;
		while ((pred != NULL) && (p == pred->left)) {
			p = pred;
			pred = pred->parent;
		}
	}
	return pred;
}

void main() {
	TreeNode* q = exp;
	n1.parent = &n3;
	n2.parent = &n3;
	n3.parent = &n7;
	n4.parent = &n6;
	n5.parent = &n6;
	n6.parent = &n7;
	n7.parent = NULL;

	while (q->right)
		q = q->right;
	do {
		printf("%c\n", q->data);
		q = tree_predecessor(q);
	} while (q);
}