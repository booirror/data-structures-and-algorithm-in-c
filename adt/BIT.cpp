#include <vector>
#include <iostream>

using namespace std;

class BIT {
public:
	BIT(std::vector<int>& v);
	void update(int i, int val);
	int sum(int n);
private:
	int lowbit(int a);
	void preProcessing(const std::vector<int>& v);
	vector<int> vec;
	vector<int>&nums;
};

BIT::BIT(std::vector<int>& v):nums(v)
{
	vec.resize(v.size() + 1);
	preProcessing(v);
}

void BIT::preProcessing(const std::vector<int>& v)
{
	int n = vec.size();
	for (int i = 0; i < v.size(); i++) {
		int m = i + 1;
		while (m < n) {
			vec[m] += v[i];
			m += lowbit(m);
		}
	}
}

void BIT::update(int i, int val)
{
	int diff = val - nums[i];
	nums[i] = val;
	i = i + 1;
	int n = vec.size();
	while (i < n) {
		vec[i] += diff;
		i += lowbit(i);
	}
}

//n 指的是原数组的索引
int BIT::sum(int n)
{
	n = n + 1;
	int sum = 0;
	while (n > 0) {
		sum += vec[n];
		n -= lowbit(n);
	}
	return sum;
}

int BIT::lowbit(int a)
{
	return a & (-a);
}

class NumArray {
public:
public:
	NumArray(vector<int> &nums) :bit(nums) {
	}

	void update(int i, int val) {
		bit.update(i, val);
	}

	int sumRange(int i, int j) {
		return bit.sum(j) - bit.sum(i-1);
	}
private:
	BIT bit;
};

void bit_test()
{
	std::vector<int> v{ 1, 2, 4, 6 };

	BIT bit(v);

	int s = bit.sum(3);

	bit.update(0, 4);

	s = bit.sum(3);

	cout << s << endl;
	cout << "++++++++++++++++" << endl;

	vector<int> nums{ 1, 3, 5 };

	NumArray na(nums);
	cout << na.sumRange(0, 2) << endl;
	na.update(1, 2);
	cout << na.sumRange(0, 2) << endl;
}