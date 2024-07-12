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

	// posʧЧ
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

// N��������Ҫ����vector+ �㷨sort  list+ sort
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

	// ������vector���������Ժ��ٿ�������
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
//��Ŀ
class Solution1 {
public:
	int maxArea(vector<int>& height) {
		int left = 0;
		int right = height.size() - 1;
		int maxArea = 0;
		int currentArea;

		while (left < right) {
			// ���㵱ǰ���
			currentArea = min(height[left], height[right]) * (right - left);

			// ����������
			maxArea = max(maxArea, currentArea);

			// �ƶ�ָ�룬�����ҵ����ߵ��������п����������
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
	// ���캯��������Ҫ���κγ�ʼ��
	MinStack() {}

	// ��Ԫ��val����ջ��
	void push(int val)
	{
		// ��Ԫ��val������ջ
		_st.push(val);

		// �����СջΪ�գ�������Сջ�Ķ���Ԫ�ش��ڵ���val��
		// ��valҲ������Сջ����ȷ������Сջ����ʼ�ձ��ֵ�ǰջ�е���СԪ��
		if (_minst.empty() || _minst.top() >= val) {
			_minst.push(val);
		}
	}

	// �Ƴ�ջ��Ԫ��
	void pop()
	{
		// �����ջ�Ķ���Ԫ�ص�����Сջ�Ķ���Ԫ�أ�
		// ��ô���Ƴ���ջ�Ķ���Ԫ�غ�Ҳ��Ҫ�Ƴ���Сջ�Ķ���Ԫ�ء�
		// ��������ȷ����Сջ�Ķ���Ԫ��ʼ���ǵ�ǰջ�е���СԪ��
		if (_st.top() == _minst.top()) {
			_minst.pop();
		}
		// �Ƴ���ջ�Ķ���Ԫ��
		_st.pop();
	}

	// ��ȡջ��Ԫ��
	int top()
	{
		// ������ջ�Ķ���Ԫ��
		return _st.top();
	}

	// ��ȡ��ǰջ�е���СԪ��
	int getMin()
	{
		// ������Сջ�Ķ���Ԫ�أ����Ԫ���ǵ�ǰջ�е���СԪ��
		return _minst.top();
	}

private:
	// ��ջ�����ڴ洢����Ԫ��
	stack<int> _st;

	// ��Сջ�����ڴ洢ջ�е���СԪ��
	stack<int> _minst;
};


int main()
{
	test_list3();
	test_list2();
	test_set1();
	return 0;
}