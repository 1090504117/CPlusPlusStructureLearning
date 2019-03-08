#include "Utils.h"

void Swap(int *x, int *y)
{
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void PrintArrayInt(int a[], int n)
{
	for (int i = 0;i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}