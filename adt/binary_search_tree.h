#ifndef _BST_H_
#define _BST_H_

typedef int element_type;
typedef struct bstree_tag *bstree;
typedef struct bstree_tag *node_ptr;

struct bstree_tag
{
	element_type data;
	node_ptr left;
	node_ptr right;
};

typedef void (*bst_func)(node_ptr nptr);

bstree bst_create_root(element_type e);

/* create bst with array */
bstree bst_create(element_type a[], int size);

void bst_destroy(bstree* bst);

/* bst should not null */
void bst_insert(bstree bst, element_type e);

node_ptr bst_find(bstree bst, element_type e);

node_ptr bst_min_element(bstree bst);

node_ptr bst_max_element(bstree bst);

bstree bst_delete(bstree bst, element_type e);

void bst_inorder_traversal(bstree bst, bst_func func);

void bst_postorder_traversal(bstree bst, bst_func func);
#endif