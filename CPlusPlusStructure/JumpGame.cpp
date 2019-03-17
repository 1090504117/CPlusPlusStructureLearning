using namespace std;

#include "JumpGame.h"
#include "Utils.h"


bool JumpGameCanJump(vector<int>& nums)
{
	if (nums.size() < 1) return false;
	int maxIndex = 0;
	int curMaxIndex = maxIndex;
	for (int i = 0; i < nums.size() && i <= maxIndex; i++)
	{
		curMaxIndex = i + nums[i];
		if (curMaxIndex > maxIndex) maxIndex = curMaxIndex;
		if (maxIndex > nums.size() - 2) return true;
	}
	return false;
}

void JumpGameCanJumpTest()
{
	vector<int> testVector;
	int a[] = {0};
	for (int i = 0; i < ArrayIntNum(a); i++)
	{
		testVector.push_back(a[i]);
	}
	printf("isCanJump = %d", JumpGameCanJump(testVector));
}