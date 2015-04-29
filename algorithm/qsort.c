/*
 *author: booirror@163.com
 *date: 2015/4/28
 */
#include <stdio.h>
void swap(int a[], int n, int m)
{
	if (n == m) return;
	int tmp = a[n];
	a[n] = a[m];
	a[m] = tmp;
}

void qsort(int a[], int n)
{
	int i, j;
	int last = 0;
	if (n < 2) return;
	swap(a, 0, n/2);
	for (i = 1; i < n; i++) {
		if (a[i] < a[0]) {
			swap(a, ++last, i);
		}
	}
	swap(a, 0, last);
	qsort(a, last);
	qsort(a+last+1, n-last-1);
}

int main()
{
	int i = 0;
    int ra[10] = {12, 23, 55, 33, 1, 25, 32, 99, 77, 11};
    qsort(ra, 10);

    while (i < 10)
        printf(" %d", ra[i++]);
    puts("\n");
    int ar[6] = {4, 22, 11, 77, 33, 41};
	qsort(ar, 6);
	for (i=0; i < 6; i++) {
		printf("%d ", ar[i]);
	}
	puts("\n");
    return 0;
}