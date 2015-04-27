#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

static void fatal_error(const char* errmsg)
{
	fprintf(stderr, "%s\n", errmsg);
	exit(1);
}


hash_table_ptr hash_init_table(unsigned int size, hash f, cmp_func c)
{
	int i = 0;
	if (f == NULL) {
		fatal_error("hash function must be provided");
	}
	if (c == NULL) {
		fatal_error("compare function must be provided");
	}
	hash_table_ptr tbl = (hash_table_ptr)malloc(sizeof(struct hash_table));
	if (tbl == NULL) {
		fatal_error("out of space");
	}
	tbl->cells = (cell*)malloc(sizeof(cell)*size);
	if (tbl->cells == NULL){
		free(tbl);
		fatal_error("out of space");
	}
	tbl->table_size = size;
	tbl->hfunc = f;
	tbl->equals = c;
	for (; i < size; ++i) {
		tbl->cells[i].info = empty;
	}
	return tbl;
}

void hash_insert(hash_table_ptr tbl, element_type e)
{
	position pos = tbl->hfunc(e);
	while (tbl->cells[pos].info != empty) {
		pos = (pos+1) % tbl->table_size;
	}
	tbl->cells[pos].element = e;
	tbl->cells[pos].info = legitimate;
}

position hash_find(hash_table_ptr tbl, element_type e)
{
	int i = 0;
	position idx = tbl->hfunc(e);
	while (i < tbl->table_size) {
		if (tbl->cells[idx].info == legitimate && tbl->equals(tbl->cells[idx].element, e))
			return idx;
		idx = (idx+1) % tbl->table_size;
		i++;
	}
	return -1;
}

void hash_delete(hash_table_ptr ptr, element_type e)
{
	position pos = hash_find(ptr, e);
	if (pos != -1) {
		ptr->cells[pos].info = deleted;
	}
}

void hash_destroy_table(hash_table_ptr* phash_ptr)
{
	hash_table_ptr tbl = *phash_ptr;
	if (*phash_ptr == NULL) return;
	if (tbl->cells != NULL) {
		free(tbl->cells);
	}
	free(tbl);
	*phash_ptr = NULL;
}