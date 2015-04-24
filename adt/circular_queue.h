#ifndef _CIRCULAR_QUEUE_H
#define _CIRCULAR_QUEUE_H


struct queue_tag;
typedef struct queue_tag *queue;
typedef int element_type;
queue queue_create();

void queue_destroy(queue * qtr);

void queue_enqueue(queue q, element_type e);

element_type queue_dequeue(queue q);

int queue_is_empty(queue q);

int queue_is_full(queue q);

#endif