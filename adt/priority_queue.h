#ifndef _priority_queue_h_
#define _priority_queue_h_
#include <limits.h>
typedef int element_type;

#define min_data INT_MIN

typedef struct heap_tag{
	unsigned int max_size;
	unsigned int size;
	element_type *elements;
}*priority_queue;

priority_queue pq_create(unsigned int max_size);

void pq_destroy(priority_queue* pheap);

void pq_insert(priority_queue pq, element_type e);

int pq_is_full(priority_queue pq);

element_type pq_delete_min(priority_queue heap);

void pq_decrease_key(priority_queue heap, unsigned int position, element_type delta);

void pq_increase_key(priority_queue heap, unsigned int position, element_type delta);

void pq_delete(priority_queue heap, unsigned int p);

#endif