#include <stdio.h>
#include <assert.h>
#include "../adt/linked_list.h"

void print_list(LIST L)
{
	while (L->next != NULL) {
		printf("%d ", L->next->element);
		L = L->next;
	}
	printf("\n");
}

int main()
{
	LIST list = list_create();
	assert(list_is_empty(list));
	list_insert_header(3, list);
	assert(!list_is_empty(list));
	position p = list_find(3, list);
	assert(list_is_last(p, list));
	list_insert_header(4, list);
	list_insert_header(5, list);
	print_list(list);
	list_reverse(list);
	print_list(list);
	list_delete(5, list);
	assert(list_find(5, list) == NULL);
	return 0;
}