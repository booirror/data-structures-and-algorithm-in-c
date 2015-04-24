#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

void fatal_error(const char* errmsg)
{
	fprintf(stderr, "%s\n", errmsg);
	exit(1);
}

LIST list_create()
{
	node_ptr ptr = malloc(sizeof(struct node));
	if (ptr == NULL) {
		fatal_error("out of space");
		return NULL;
	}
	ptr->next = NULL;
	return ptr;
}

void list_destroy(LIST *Lptr)
{
	position tmp;
	position p = *Lptr;
	while (p != NULL) {
		tmp = p;
		p = p->next;
		free(tmp);
	}
	*Lptr = NULL;
}

int list_is_empty(LIST L)
{
	return (L->next == NULL);
}

int list_is_last(position p, LIST L)
{
	return (p->next == NULL);
}

position list_find(element_type x, LIST L)
{
	L = L->next;
	while (L != NULL && L->element != x) {
		L = L->next;
	}
	return L;
}

void list_reverse(LIST L)
{
	if (L->next == NULL) return;
	node_ptr p = L->next, first = L->next;
	while (p != NULL && p->next != NULL) {
		node_ptr next_node = p->next;
		p->next = next_node->next;
		next_node->next = first;
		first = next_node;
	}
	L->next = first;
}

void list_delete(element_type x, LIST L)
{
	position p, tmp_node;
	p = list_find_previous(x, L);
	if (p->next != NULL) {
		tmp_node = p->next;
		p->next = tmp_node->next;
		free(tmp_node);
	}
}

position list_find_previous(element_type x, LIST L)
{
	while (L->next != NULL && L->next->element != x) {
		L = L->next;
	}
	return L;
}

void list_insert(element_type x, LIST L, position p)
{
	node_ptr node = (node_ptr)malloc(sizeof(struct node));
	if (node == NULL) {
		fatal_error("out of space");
	} else {
		node->element = x;
		node->next = p->next;
		p->next = node;
	}
}

void list_insert_header(element_type x, LIST L)
{
	list_insert(x, L, L);
}