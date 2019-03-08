#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>
#include <stdio.h>

#define ArrayIntNum(a) sizeof(a)/sizeof(int)

#define MinInt(a,b) (a<b?a:b);

void Swap(int *x, int *y);

void PrintArrayInt(int a[], int n);



#endif // !__UTILS_H__

