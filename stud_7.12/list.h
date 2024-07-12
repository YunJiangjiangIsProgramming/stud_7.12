#pragma once
#include<assert.h>

namespace luow
{
	template<class T>
	struct list_node
	{
		list_node<T>* _next;
		list_node<T>* _prev;
		T _data;

		list_node(const T& x)
			:_next(nullptr)
			, _prev(nullptr)
			, _data(x)
		{}
	};


	template<class T, class Ref, class Ptr>
	struct __list_iterator
	{
		typedef list_node<T> node;
		typedef __list_iterator<T, Ref, Ptr> Self;
		node* _pnode;

		__list_iterator(node* p)
			:_pnode(p)
		{}

		Ptr operator->()
		{
			return &_pnode->_data;
		}

		Ref operator*()
		{
			return _pnode->_data;
		}

		Self& operator++()
		{
			_pnode = _pnode->_next;
			return *this;
		}

		// it++
		Self operator++(int)
		{
			Self tmp(*this);
			_pnode = _pnode->_next;
			return tmp;
		}

		Self& operator--()
		{
			_pnode = _pnode->_prev;
			return *this;
		}

		Self operator--(int)
		{
			Self tmp(*this);
			_pnode = _pnode->_prev;
			return tmp;
		}

		bool operator!=(const Self& it) const
		{
			return _pnode != it._pnode;
		}

		bool operator==(const Self& it) const
		{
			return _pnode == it._pnode;
		}
	};


	
	template<class T>
	class list
	{
		typedef list_node<T> node;
	public:
		typedef __list_iterator<T, T&, T*> iterator;
		//typedef __list_const_iterator<T> const_iterator;
		typedef __list_iterator<T, const T&, const T*> const_iterator;

		const_iterator begin() const
		{
			return const_iterator(_head->_next);
		}

		const_iterator end() const
		{
			return const_iterator(_head);
		}

		iterator begin()
		{
			return iterator(_head->_next);
		}

		iterator end()
		{
			return iterator(_head);
		}

		void empty_initialize()
		{
			_head = new node(T());
			_head->_next = _head;
			_head->_prev = _head;

			_size = 0;
		}

		list()
		{
			empty_initialize();
		}



		template <class InputIterator>
		list(InputIterator first, InputIterator last)
		{
			empty_initialize();
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		void swap(list<T>& lt)
		{
			std::swap(_head, lt._head);
			std::swap(_size, lt._size);
		}

		list(const list<T>& lt)
		
		{
			empty_initialize();

			list<T> tmp(lt.begin(), lt.end());
			swap(tmp);
		}

		list<T>& operator=(list<T> lt)
		
		{
			swap(lt);
			return *this;
		}

		size_t size() const
		{
			return _size;
		}

		bool empty() const
		{
			return _size == 0;
		}

		~list()
		{
			clear();

			delete _head;
			_head = nullptr;
		}

		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				it = erase(it);
			}
		}

		void push_back(const T& x)
		{
	
			insert(end(), x);
		}

		void push_front(const T& x)
		{
			insert(begin(), x);
		}

		void pop_front()
		{
			erase(begin());
		}

		void pop_back()
		{
			erase(--end());
		}

		iterator insert(iterator pos, const T& x)
		{
			node* newnode = new node(x);
			node* cur = pos._pnode;
			node* prev = cur->_prev;

			// prev newnode cur
			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = cur;
			cur->_prev = newnode;

			++_size;

			return iterator(newnode);
		}

		iterator erase(iterator pos)
		{
			assert(pos != end());

			node* prev = pos._pnode->_prev;
			node* next = pos._pnode->_next;

			prev->_next = next;
			next->_prev = prev;

			delete pos._pnode;
			--_size;

			return iterator(next);
		}

	private:
		node* _head;
		size_t _size;
	};

	void test_list1()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);

		// iterator 1、内嵌类型 2、行为像指针一样 
		list<int>::iterator it = lt.begin();
		while (it != lt.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;

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
		lt.push_front(5);
		lt.push_front(6);

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
	}

	void test_list3()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		lt.push_front(5);
		lt.push_front(6);

		for (auto e : lt)
		{
			cout << e << " ";
		}
		cout << endl;
		cout << lt.size() << endl;

		list<int> lt1(lt);
		for (auto e : lt1)
		{
			cout << e << " ";
		}
		cout << endl;


		list<int> lt2;
		lt2.push_back(10);
		lt2.push_back(20);
		lt2.push_back(30);
		lt2.push_back(40);
		cout << lt2.size() << endl;

		lt = lt2;
		for (auto e : lt)
		{
			cout << e << " ";
		}
		cout << endl;
	}

	void print_list(const list<int>& lt)
	{
		list<int>::const_iterator it = lt.begin();
		while (it != lt.end())
		{
			// (*it) += 2; // 不能写
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}

	void test_list4()
	{
		list<int> lt1;
		lt1.push_back(1);
		lt1.push_back(2);
		lt1.push_back(3);
		lt1.push_back(4);

		list<int>::iterator it = lt1.begin();
		while (it != lt1.end())
		{
			(*it) += 2; // 可以写
			cout << *it << " ";
			++it;
		}
		cout << endl;

		print_list(lt1);
	}

	struct Pos
	{
		int _row;
		int _col;

		Pos(int row = 0, int col = 0)
			:_row(row)
			, _col(col)
		{}
	};

	void print_list(const list<Pos>& lt)
	{
		list<Pos>::const_iterator it = lt.begin();
		while (it != lt.end())
		{
			//it->_row++;

			cout << it->_row << ":" << it->_col << endl;

			++it;
		}
		cout << endl;
	}

	void test_list5()
	{
		list<Pos> lt;
		Pos p1(1, 1);
		lt.push_back(p1);
		lt.push_back(p1);
		lt.push_back(p1);
		lt.push_back(Pos(2, 2));
		lt.push_back(Pos(3, 3));

		list<Pos>::iterator it = lt.begin();
	
		while (it != lt.end())
		{
			it->_row++;

			//cout << (&(*it))->_row << ":" << (*it)._col << endl;
			cout << it->_row << ":" << it->_col << endl;
			//cout << it.operator->()->_row << ":" << it->_col << endl;

			++it;
		}
		cout << endl;

		print_list(lt);
	}
}
