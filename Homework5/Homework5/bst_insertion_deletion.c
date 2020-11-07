// bst_insertion_deletion.cpp : Defines the entry point for the console application.
//
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef struct TreeNode {
	int key;
	struct TreeNode* left, * right;
} TreeNode;

//    	               35
//          18                 68
//   7             26                   99
//3     12     22         30
//    10          24      

TreeNode n12 = { 24, NULL, NULL };
TreeNode n11 = { 10, NULL, NULL };
TreeNode n10 = { 30, NULL, NULL };
TreeNode n9 = { 22, NULL, &n12 };
TreeNode n8 = { 12, &n11, NULL };
TreeNode n7 = { 3,  NULL, NULL };
TreeNode n6 = { 99, NULL, NULL };
TreeNode n5 = { 26, &n9, &n10 };
TreeNode n4 = { 7,  &n7, &n8 };
TreeNode n3 = { 68, NULL, &n6 };
TreeNode n2 = { 18, &n4, &n5 };
TreeNode n1 = { 35, &n2, &n3 };

// Insert the key into the binary search tree root.
// If key is already in root, it is not inserted.
void insert_node(TreeNode** root, int key)
{
	TreeNode* p, * t;// p: parent node, t: current node
	TreeNode* n;// n: new node to be inserted
	t = *root;
	p = NULL;
	// Search first
	while (t != NULL) {
		if (key == t->key) {
			printf("The same key exists in the tree.\n");
			return;
		}
		p = t;
		if (key < t->key) t = t->left;
		else t = t->right;
	}
	// Since the key is not in the tree, insertion is possible.
	n = (TreeNode*)malloc(sizeof(TreeNode));
	if (n == NULL) return;
	n->key = key;
	n->left = n->right = NULL;

	if (p != NULL)
		if (key < p->key)
			p->left = n;
		else p->right = n;
	else *root = n;
}

// Deletion in binary search tree
void delete_node(TreeNode** root, int key)
{
	TreeNode* p, * child, * pred, * pred_p, * t;
	// search node t with key, p: t¡¯s parent
	p = NULL;
	t = *root;
	while (t != NULL && t->key != key) {
		p = t;
		t = (key < t->key) ? t->left : t->right;
	}
	// If t is NULL at the end, there is no key in the tree
	if (t == NULL) {
		printf("key is not in the tree");
		return;
	}

	// Case 1
	if ((t->left == NULL) && (t->right == NULL)) {
		if (p != NULL) {
			if (p->left == t)
				p->left = NULL;
			else p->right = NULL;
		}
		// If the parent node is NULL, the node to be deleted is the root
		else
			*root = NULL;
	}

	// Case 2
	else if ((t->left == NULL) || (t->right == NULL)) {
		child = (t->left != NULL) ? t->left : t->right;
		if (p != NULL) {
			if (p->left == t)
				p->left = child;
			else p->right = child;
		}
		// If the parent node is NULL, the node to be deleted is the root
		else
			*root = child;
	}
	// Case 3
	else {
		// Find the predecessor at left subtree
		pred_p = t;
		pred = t->left;
		// Keep moving to the right and find the predecessor
		while (pred->right != NULL) {
			pred_p = pred;
			pred = pred->right;
		}
		//succ_p->left = succ->left;		
		if (pred_p->left == pred)
			pred_p->left = pred->left;
		else
			pred_p->right = pred->left;
		t->key = pred->key;
		t = pred;
	}
	//	free(t);
}



void inorder(TreeNode* root) {
	if (root) {
		inorder(root->left); // Left subtree
		printf("%d\t", root->key); // Visit root node
		inorder(root->right);// Right subtree
	}
}

void main()
{
	TreeNode* root = &n1;

	printf("Binary tree\n");
	inorder(root);
	printf("\n\n");

	delete_node(&root, 7);

	printf("Binary tree\n");
	inorder(root);
	printf("\n\n");
}