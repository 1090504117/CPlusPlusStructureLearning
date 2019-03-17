#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>
#include <stdio.h>

#define ArrayIntNum(a) sizeof(a)/sizeof(int)

template<typename T> void Swap(T &x, T &y);

void PrintArrayInt(int a[], int n);

#endif // !__UTILS_H__

