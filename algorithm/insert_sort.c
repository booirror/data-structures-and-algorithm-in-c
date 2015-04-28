#include <stdio.h>


void insertion_sort(int a[], int n)
{
	int i,j,tmp;
	for (i = 1; i < n; i++) {
		tmp = a[i];
		for (j = i - 1; j >= 0 && a[j] > tmp; j--) {
			a[j+1] = a[j];
		}
		a[j+1] = tmp;
	}
}

int main()
{
	int i = 0;
	int ar[6] = {4, 22, 11, 77, 33, 41};
	insertion_sort(ar, 6);
	for (; i < 6; i++) {
		printf("%d ", ar[i]);
	}
	puts("\n");
	return 0;
}