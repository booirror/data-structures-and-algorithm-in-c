#ifndef ADT_STACK_H_
#define ADT_STACK_H_

#define SIZE 100
struct stack_tag;
typedef int element_type;
typedef struct stack_tag *stack;

stack stack_create();

void stack_destroy(stack* s);

element_type stack_top(stack s);

void stack_pop(stack s);

void stack_push(stack s, element_type e);

int stack_size(stack s);

int stack_is_empty(stack s);

#endif