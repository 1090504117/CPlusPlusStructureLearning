#include <iostream>
#include "Utils.h"

#include "MaximumSubarray.h"

int MaximumSubarray(vector<int>& nums)
{
	int sum = nums[0];
	int max = sum;
	for (int i = 1; i < nums.size(); i++)
	{
		if (sum < 0)
			sum = nums[i];
		else
			sum = sum + nums[i];	//只要小于0，再怎么加都是会减少的，所以干脆舍弃，同时比较最大值
		if (sum > max) max = sum;
	}
	return max;
}

void MaximumSubarrayTest()
{
	vector<int> testVector;
	int a[] = {0,-10,5,4,-8,44};
	for(int i = 0; i < ArrayIntNum(a);i++)
	{
		testVector.push_back(a[i]);
	}
	printf("max = %d", MaximumSubarray(testVector));
}