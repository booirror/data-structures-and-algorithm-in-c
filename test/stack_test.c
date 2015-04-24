#include <assert.h>
#include <stdio.h>
#include "../adt/stack.h"

int main()
{
	stack s = stack_create();
	stack as = stack_create();
	assert(stack_is_empty(s));
	stack_push(s, 3);
	assert(1 == stack_size(s));
	stack_push(s, 5);
	assert(5 == stack_top(s));
	stack_push(as, 10);
	stack_pop(s);
	assert(stack_size(s) == stack_size(as));
	printf("3 = [%d], 10 = [%d]\n", stack_top(s), stack_top(as));
	stack_destroy(&s);
	stack_destroy(&as);
	assert(s == NULL);
	return 0;
}