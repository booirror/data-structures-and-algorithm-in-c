#include <stdio.h>
#include <stdlib.h>
#include "binary_search_tree.h"

void fatal_error(const char* errmsg)
{
	fprintf(stderr, "%s\n", errmsg);
	exit(1);
}

void donothing_warnning(const char* warn)
{
	fprintf(stdout, "warnning: %s\n", warn);
}

bstree bst_create_root(element_type e)
{
	node_ptr ptr = (node_ptr)malloc(sizeof(struct bstree_tag));
	if (ptr == NULL) {
		fatal_error("out of space");
	}
	ptr->data = e;
	ptr->left = ptr->right = NULL;
	return ptr;
}


void bst_insert(bstree bst, element_type e)
{
	if (bst->data == e) {
		return;
	} else if (bst->data < e) {
		if (bst->right != NULL) {
			bst_insert(bst->right, e);
		} else {
			bstree node = bst_create_root(e);
			bst->right = node;
		}
	} else {
		if (bst->left != NULL) {
			bst_insert(bst->left, e);
		} else {
			bstree node = bst_create_root(e);
			bst->left = node;
		}
	}
}

bstree bst_create(element_type a[], int size)
{
	int i = 1;
	if (size <= 0) return NULL;
	bstree bst = bst_create_root(a[0]);
	for (; i < size; i++) {
		bst_insert(bst, a[i]);
	}
	return bst;
}

node_ptr bst_find(bstree bst, element_type e)
{
	if (bst == NULL)
		return NULL;
	else if (bst->data < e) {
		return bst_find(bst->right, e);
	} else if (bst->data > e) {
		return bst_find(bst->left, e);
	}
	return bst;
}

node_ptr bst_min_element(bstree bst)
{
	if (bst->left != NULL)
		return bst_min_element(bst->left);
	return bst;
}

node_ptr bst_max_element(bstree bst)
{
	while (bst->right != NULL) {
		bst = bst->right;
	}
	return bst;
}

static bstree bst_delete_min(bstree bst, element_type* pdata)
{
	while (bst->left != NULL) {
		bst = bst->left;
	}
	node_ptr right = bst->right;
	*pdata = bst->data;
	free(bst);
	return right;
}

bstree bst_delete(bstree bst, element_type e)
{
	if (bst == NULL) {
		donothing_warnning("element not found");
		return bst;
	} else if (bst->data > e) {
		bst->left = bst_delete(bst->left, e);
	} else if (bst->data < e) {
		bst->right = bst_delete(bst->right, e);
	} else {
		// bst->data == e
		if (bst->left == NULL && bst->right == NULL) {
			free(bst);
			return NULL;
		} else if (bst->left == NULL || bst->right == NULL) {
			node_ptr node = bst->left == NULL ? bst->right : bst->left;
			free(bst);
			return node;
		}
		bst->right = bst_delete_min(bst->right, &bst->data);
	}
	return bst;
}

void bst_inorder_traversal(bstree bst, bst_func func)
{
	if (bst == NULL) return;
	bst_inorder_traversal(bst->left, func);
	func(bst);
	bst_inorder_traversal(bst->right, func);
}

static void free_node(node_ptr p)
{
	free(p);
}
void bst_postorder_traversal(bstree bst, bst_func func)
{
	if (bst == NULL) return;
	bst_postorder_traversal(bst->left, func);
	bst_postorder_traversal(bst->right, func);
	func(bst);
}

void bst_destroy(bstree *bst)
{
	bst_postorder_traversal(*bst, free_node);
	*bst = NULL;
}