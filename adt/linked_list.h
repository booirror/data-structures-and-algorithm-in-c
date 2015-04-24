#ifndef _linked_list_h_
#define _linked_list_h_

typedef int element_type;
typedef struct node *node_ptr;

struct node {
element_type element;
node_ptr next;
};

typedef node_ptr LIST;
typedef node_ptr position;

LIST list_create();

void list_destroy(LIST *L);

void fatal_error(const char* errmsg);

int list_is_empty(LIST L);

int list_is_last(position p, LIST L);

position list_find(element_type x, LIST L);

void list_reverse(LIST L);

void list_insert(element_type x, LIST L, position p);

void list_insert_header(element_type x, LIST L);

void list_delete(element_type x, LIST L);

position list_find_previous(element_type x, LIST L);

#endif