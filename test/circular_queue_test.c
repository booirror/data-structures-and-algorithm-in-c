#include <stdio.h>
#include <assert.h>
#include "../adt/circular_queue.h"

int main()
{
	int i;
	queue q = queue_create();
	assert(queue_is_empty(q));
	queue_enqueue(q, 3);
	assert(queue_dequeue(q) == 3);
	assert(queue_is_empty(q));
	for (i= 0; i < 99; i++) {
		queue_enqueue(q, i);
	}
	assert(queue_is_full(q));
	assert(queue_dequeue(q) == 0);
	queue_enqueue(q, 1);
	queue_enqueue(q, 1);
	assert(queue_is_full(q));
	queue_destroy(&q);
	assert(q == NULL);
	return 0;
}