#include <stdio.h>
#include <assert.h>
#include "../adt/priority_queue.h"

int main(int argc, char const *argv[])
{
	int i = 1;
	priority_queue heap = pq_create(10);
	for (; i < 10; i++) {
		pq_insert(heap, i);
	}
	for (i = 1; i <=heap->size; i++) {
		printf(" %d", heap->elements[i]);
	}
	puts("\n1--------------\n");
	assert(pq_is_full(heap));
	assert(pq_delete_min(heap) == 1);
	assert(!pq_is_full(heap));
	for (i = 1; i <=heap->size; i++) {
		printf(" %d", heap->elements[i]);
	}
	puts("\n2--------------\n");
	pq_decrease_key(heap, 8, 8);
	for (i = 1; i <=heap->size; i++) {
		printf(" %d", heap->elements[i]);
	}
	puts("\n3--------------\n");
	assert(pq_delete_min(heap) == 1);
	pq_increase_key(heap, 1, 7);
	for (i = 1; i <=heap->size; i++) {
		printf(" %d", heap->elements[i]);
	}
	puts("\n4--------------\n");
	pq_delete(heap, 7);
	for (i = 1; i <=heap->size; i++) {
		printf(" %d", heap->elements[i]);
	}
	puts("\n5--------------\n");
	pq_destroy(&heap);
	return 0;
}