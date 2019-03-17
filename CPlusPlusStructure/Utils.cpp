#include "Utils.h"

template<typename T> void Swap(T &x, T &y)
{
	int temp;
	temp = x;
	x = y;
	y = temp;
}

void PrintArrayInt(int a[], int n)
{
	for (int i = 0;i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}