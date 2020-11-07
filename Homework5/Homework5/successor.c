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

TreeNode* tree_successor(TreeNode* p) {
	TreeNode* succ;
	//p's right subtree is not null
	if (p->right != NULL) { //leftmost node of right subtree
		succ = p->right;
		p = succ->left;
		while (succ->left != NULL) {
			succ = p;
			p = p->left;
		}
	}
	//p's right subtree is null
	else {
		succ = p->parent;
		while ((succ != NULL) && (p == succ->right)) {
			p = succ;
			succ = succ->parent;
		}
	}
	return succ;
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

	while (q->left)
		q = q->left;
	do {
		printf("%c\n", q->data);
		q = tree_successor(q);
	} while (q);
}