#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <time.h>
#include <set>
#include<stack>
using namespace std;

#include "list.h"

void test_list1()
{
	list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);

	list<int>::iterator it = lt.begin();
	while (it != lt.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	lt.push_front(10);
	lt.push_front(20);
	lt.push_front(30);
	lt.push_front(40);

	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;

	lt.pop_back();
	lt.pop_back();
	lt.pop_front();
	lt.pop_front();

	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;

	lt.pop_back();
	lt.pop_back();
	lt.pop_back();
	lt.pop_back();
	//lt.pop_back();
	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;
}

void test_list2()
{
	list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);

	auto pos = find(lt.begin(), lt.end(), 3);
	if (pos != lt.end())
	{
	
		lt.insert(pos, 30);
	}

	cout << *pos << endl;
	(*pos)++;

	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;

	// pos失效
	lt.erase(pos);

	//cout << *pos << endl;
	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;
}

void test_list3()
{
	list<int> lt;
	lt.push_back(10);
	lt.push_back(2);
	lt.push_back(5);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(4);
	lt.push_back(6);
	lt.push_back(4);
	lt.push_back(0);

	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;

	lt.remove(3);

	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;

	lt.remove(30);
	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;

	lt.sort();
	
	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;

	lt.unique();
	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;
}

// N个数据需要排序，vector+ 算法sort  list+ sort
void test_op()
{
	srand(time(0));
	const int N = 100000;
	vector<int> v;
	v.reserve(N);

	list<int> lt1;
	list<int> lt2;
	for (int i = 0; i < N; ++i)
	{
		auto e = rand();
		//v.push_back(e);
		lt1.push_back(e);
		lt2.push_back(e);
	}

	// 拷贝到vector排序，排完以后再拷贝回来
	int begin1 = clock();
	for (auto e : lt1)
	{
		v.push_back(e);
	}
	sort(v.begin(), v.end());
	size_t i = 0;
	for (auto& e : lt1)
	{
		e = v[i++];
	}
	int end1 = clock();

	int begin2 = clock();
	// sort(lt.begin(), lt.end());
	lt2.sort();
	int end2 = clock();

	printf("vector sort:%d\n", end1 - begin1);
	printf("list sort:%d\n", end2 - begin2);
}

void test_set1()
{
	set<int> s;
	s.insert(4);
	s.insert(1);
	s.insert(2);
	s.insert(5);

	set<int>::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}
//题目
class Solution1 {
public:
	int maxArea(vector<int>& height) {
		int left = 0;
		int right = height.size() - 1;
		int maxArea = 0;
		int currentArea;

		while (left < right) {
			// 计算当前面积
			currentArea = min(height[left], height[right]) * (right - left);

			// 更新最大面积
			maxArea = max(maxArea, currentArea);

			// 移动指针，尝试找到更高的柱子以有可能增加面积
			if (height[left] < height[right]) {
				left++;
			}
			else {
				right--;
			}
		}

		return maxArea;
	}
};

class MinStack {
public:
	// 构造函数，不需要做任何初始化
	MinStack() {}

	// 将元素val推入栈中
	void push(int val)
	{
		// 将元素val推入主栈
		_st.push(val);

		// 如果最小栈为空，或者最小栈的顶部元素大于等于val，
		// 则将val也推入最小栈。这确保了最小栈顶部始终保持当前栈中的最小元素
		if (_minst.empty() || _minst.top() >= val) {
			_minst.push(val);
		}
	}

	// 移除栈顶元素
	void pop()
	{
		// 如果主栈的顶部元素等于最小栈的顶部元素，
		// 那么在移除主栈的顶部元素后，也需要移除最小栈的顶部元素。
		// 这样可以确保最小栈的顶部元素始终是当前栈中的最小元素
		if (_st.top() == _minst.top()) {
			_minst.pop();
		}
		// 移除主栈的顶部元素
		_st.pop();
	}

	// 获取栈顶元素
	int top()
	{
		// 返回主栈的顶部元素
		return _st.top();
	}

	// 获取当前栈中的最小元素
	int getMin()
	{
		// 返回最小栈的顶部元素，这个元素是当前栈中的最小元素
		return _minst.top();
	}

private:
	// 主栈，用于存储所有元素
	stack<int> _st;

	// 最小栈，用于存储栈中的最小元素
	stack<int> _minst;
};


int main()
{
	test_list3();
	test_list2();
	test_set1();
	return 0;
}