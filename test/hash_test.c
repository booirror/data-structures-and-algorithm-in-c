#include <stdio.h>
#include <assert.h>
#include "../adt/hash.h"

#define SIZE 10

position hashfunc(int e)
{
	return e % 10;
}

int cmp_int(int a, int b)
{
	return a == b;
}

int main()
{
	int k = 0;
	int array[] = {4371, 1323, 6173, 4199, 4344, 9679, 1989};
	hash_table_ptr tbl = hash_init_table(SIZE, hashfunc, cmp_int);
	for (; k < 7; k++) {
		hash_insert(tbl, array[k]);
	}
	position p = hash_find(tbl, 6173);
	position q = hash_find(tbl, 1323);
	assert(p != -1);
	assert(p != q);
	assert(tbl->cells[p].element == 6173);
	hash_delete(tbl, 6173);
	p = hash_find(tbl, 6173);
	assert(p == -1);
	for (k = 0; k < SIZE; k++) {
		if (tbl->cells[k].info == legitimate) {
			printf("%d ", tbl->cells[k].element);
		}
	}
	puts("\n");
	hash_destroy_table(&tbl);
	assert(tbl == NULL);
	return 0;
}