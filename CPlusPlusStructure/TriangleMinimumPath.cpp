#include <iostream>
#include "Utils.h"
#include <algorithm>

#include "TriangleMinimumPath.h"

int TriangleMinimumPath(vector<vector<int>>& triangle)
{
	int size = (int)triangle.size();
	if (size < 1) return 0;
	if (1 == size) return triangle[0][0];
	int calNum = 0;
	int temp,num;
	vector<int> a;
	a.push_back(triangle[0][0]);
	for (int i = 1; i < size; i++)
	{
		vector<int> &tempVector = triangle[i];
		a.push_back(tempVector[i]);
		temp = a[0];
		for (int j = 1; j < i; j++)
		{
			num = a[j];
			calNum = temp < num ? temp + tempVector[j]: num + tempVector[j];
			temp = num;
			a[j] = calNum;
		}
		a[0] = tempVector[0] + a[0];
		a[i] = tempVector[i] + temp;
	}
	int min = a[0];
	for (int i = 0; i < size; i++)
	{
		if (a[i] < min) min = a[i];
	}
	return min;
}

int TriangleMinimumPath2(vector<vector<int>>& triangle)
{
	int size = (int)triangle.size();
	if (size < 1) return 0;
	vector<int> a(triangle.back());
	for (int i = size - 2; i > -1; i--)
	{
		for (int j = 0; j <= i; j++)	//此处层出现问题 j <=i ,原先可能是j < i,故严格注意边界问题
		{
			a[j] = triangle[i][j] + MinInt(a[j + 1], a[j]);
		}
	}
	return a[0];
}

void TriangleMinimumPathTest()
{
	vector<vector<int>> testVector;
	int a[] =
	{
		2,
		3,4,
		6,5,7,
		4,1,8,3
	};
	int len = 4;
	int index = 0;
	for (int i = 0; i < len; i++)
	{
		vector<int> tmpVector;
		for (int j = 0; j <= i; j++)
			tmpVector.push_back(a[index++]);
		testVector.push_back(tmpVector);
	}
	printf("min = %d", TriangleMinimumPath2(testVector));
}