#include <stdio.h>
#include <assert.h>
#include "../adt/binary_search_tree.h"

static void print_node(node_ptr p)
{
	printf("%d ", p->data);
}

static void print_bst(bstree bst)
{
	bst_inorder_traversal(bst, print_node);
	printf("\n");
}

int main(int argc, char const *argv[])
{
	int a[6] = {9, 4, 11, 16, 14, 7}; 
	bstree bst = bst_create(a, 6);
	print_bst(bst);
	bst_insert(bst, 8);
	print_bst(bst);
	node_ptr f = bst_find(bst, 4);
	node_ptr m = bst_min_element(bst);
	assert(f == m);
	bst = bst_delete(bst, 11);
	print_bst(bst);
	f = bst_find(bst, 11);
	assert(f == NULL);
	bst_destroy(&bst);
	assert(bst == NULL);
	return 0;
}