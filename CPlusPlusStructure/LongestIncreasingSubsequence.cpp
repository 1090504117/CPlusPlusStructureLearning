#include <iostream>

#include "LongestIncreasingSubsequence.h"
#include "Utils.h"

int LongestIncreasingSubsequenceN(vector<int>& nums)
{
	if (nums.size() < 1) return 0;
	int ret = 1;
	int max = 1;
	vector<int> record;
	record.push_back(1);

	for (int i = 1; i < nums.size(); i++)
	{
		max = 1;
		for (int j = 0; j < i ;j++)
		{
			if (nums[i] > nums[j] && (record[j] + 1) > max) max = record[j] + 1;
		}
		record.push_back(max);
		if (max > ret) ret = max;
	}
	return ret;
}

void LongestIncreasingSubsequenceTest()
{
	vector<int> testVector;
	int a[] = { 10,9,2,5,3,7,101,18 };
	for (int i = 0; i < ArrayIntNum(a); i++)
	{
		testVector.push_back(a[i]);
	}
	printf("max = %d", LongestIncreasingSubsequence(testVector));
}