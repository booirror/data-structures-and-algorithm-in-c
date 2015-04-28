#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

static void fatal_error(const char* errmsg)
{
	fprintf(stderr, "%s\n", errmsg);
	exit(1);
}

static void donothing_warnning(const char* warn)
{
	fprintf(stdout, "warnning: %s\n", warn);
}

priority_queue pq_create(unsigned int max_size)
{
	priority_queue heap = (priority_queue)malloc(sizeof(struct heap_tag));
	if (heap == NULL) {
		fatal_error("out of space");
	}
	heap->elements = (element_type*)malloc(sizeof(element_type)*max_size);
	if (heap->elements == NULL) {
		fatal_error("out of space");
	}
	heap->max_size = max_size;
	heap->size = 0;
	heap->elements[0] = min_data;
	return heap;
}

void pq_destroy(priority_queue *pheap)
{
	priority_queue pq = *pheap;
	if (pq == NULL) {
		return;
	}
	if (pq->elements != NULL) {
		free(pq->elements);
	}
	free(pq);
	*pheap = NULL;
}

int pq_is_full(priority_queue pq)
{
	return pq->max_size == pq->size+1;
}

void pq_insert(priority_queue heap, element_type x)
{
	unsigned int i;
	if (pq_is_full(heap)) {
		donothing_warnning("binary heap is full");
		return;
	}
	i = ++heap->size;
	while (heap->elements[i/2] > x) {
		heap->elements[i] = heap->elements[i/2];
		i /= 2;
	}
	heap->elements[i] = x;
}

element_type pq_delete_min(priority_queue pq)
{
	element_type min = pq->elements[1];
	element_type x = pq->elements[pq->size--];
	int i = 1;
	element_type tmp;
	int flag = 0;
	while (2 * i <= pq->size)
	{
		flag = 0;
		if (pq->elements[2*i] < x) {
			tmp = x;
			pq->elements[i] = x = pq->elements[2*i];
			pq->elements[2*i] = tmp;
			flag = 0;
		}
		if (2*i+1 <= pq->size && pq->elements[2*i+1] < x) {
			tmp = x;
			pq->elements[i] = x = pq->elements[2*i+1];
			pq->elements[2*i+1] = tmp;
			flag = 1;
		}
		i = 2 * i + flag;
		x = pq->elements[i];
	}
	return min;
}

void pq_decrease_key(priority_queue heap, unsigned int pos, element_type delta)
{
	if (pos > heap->size) {
		return;
	}
	element_type x = heap->elements[pos] - delta;
	unsigned int i = pos;
	while (heap->elements[i/2] > x) {
		heap->elements[i] = heap->elements[i/2];
		i /= 2;
	}
	heap->elements[i] = x;
}

void pq_increase_key(priority_queue heap, unsigned int pos, element_type delta)
{
	if (pos > heap->size) {
		return;
	}
	element_type x = heap->elements[pos] + delta;
	unsigned int i = pos;
	unsigned int child;
	for (; i*2 < heap->size; i = child) {
		child = i * 2;
		if ((child != heap->size) && heap->elements[child+1] < heap->elements[child]) {
			child++;
		}
		if (x > heap->elements[child]) {
				heap->elements[i] = heap->elements[child];
			} else {
				break;
			}
	}
	heap->elements[i] = x;
}

void pq_delete(priority_queue q, unsigned int p)
{
	pq_decrease_key(q, p, q->elements[p] - q->elements[1] -1);
	pq_delete_min(q);
}