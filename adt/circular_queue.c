#include <stdio.h>
#include <stdlib.h>
#include "circular_queue.h"

#define SIZE 100

struct queue_tag
{
	element_type qdata[SIZE];
	int qfront;
	int qrear;
};

void fatal_error(const char* errmsg)
{
	fprintf(stderr, "%s\n", errmsg);
	exit(1);
}

void donothing_warnning(const char* warn)
{
	fprintf(stdout, "warnning: %s\n", warn);
}

queue queue_create()
{
	queue q = (queue)malloc(sizeof(struct queue_tag));
	if (q == NULL) {
		fatal_error("out of space");
	}
	q->qfront = q->qrear = 0;
	return q;
}

void queue_destroy(queue * qptr)
{
	if (*qptr != NULL) {
		free(*qptr);
		*qptr = NULL;
	}
}

void queue_enqueue(queue q, element_type e)
{
	if ((q->qrear + 1)%SIZE == q->qfront) {
		donothing_warnning("queue overflow");
		return;
	}
	q->qdata[q->qrear] = e;
	q->qrear = (q->qrear + 1) % SIZE;
}

element_type queue_dequeue(queue q)
{
	element_type tmp;
	if (q->qfront == q->qrear) {
		donothing_warnning("queue underflow");
		return -1;
	}
	tmp = q->qdata[q->qfront];
	q->qfront = (q->qfront + 1) % SIZE;
	return tmp;
}

int queue_is_empty(queue q)
{
	return q->qfront == q->qrear;
}

int queue_is_full(queue q)
{
	return (q->qrear + 1)%SIZE == q->qfront;
}