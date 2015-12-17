#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"
#include "algorithm.h"
#include "vector.h"

namespace mySTL {
	
	// implement queue using list
	template <typename T, typename Container = list<T>>
	class queue {
		private:
			Container _elem;
		public:
			// constructor and destructor
			queue() {}
			queue(queue& q) { _elem = q._elem;}
			// capacity
			bool empty() { return _elem.empty();}
			rank size() { return _elem.size();}
			// front and back element
			T& front() { return _elem.front();}
			T& back() { return _elem.back();}
			// push and pop element
			void push(T val) { _elem.push_back(val);}
			void pop() { _elem.pop_front();}
			void swap(queue& q) { _elem.swap(q._elem);}
	};
	
	// implement priority_queue using vector
	template <typename T, typename Container = vector<T>, typename Compare = less<T>>
	class priority_queue {
		private:
			Container _elem;
			Compare _cmp;
			// support function
			bool inHeap(rank i) { return (i >= 0) && (i < _elem.size());}
			rank parent(rank i) { return (i > 0) ? ((i - 1) / 2) : 0;}
			rank lchild(rank i) { return (i * 2 + 1);}
			rank rchild(rank i) { return (i * 2 + 2);}
			rank porperParent(rank i);
			void buildHeap();
			rank filteUp(rank i);
			rank filteDown(rank i);
			template <typename X>
			void swapSupport(X& a, X& b) {
				X tmp = a; a = b; b = tmp;
			}
		public:
			// constructor and destructor
			priority_queue() {}
			priority_queue(Container instance);
			// capacity
			bool empty() { return _elem.empty();}
			rank size() { return _elem.size();}
			// modifiers
			T& top() { return _elem.front();}
			void push(T element);
			void pop();
			void swap(priority_queue<T>& q) { _elem.swap(q._elem);}
	};
	
	// private impelement support function
	template <typename T, typename Container, typename Compare>
	rank priority_queue<T, Container, Compare>::porperParent(rank i) {
		if (inHeap(rchild(i))) {
			rank ret = i;
			if (_cmp(_elem[i], _elem[lchild(i)])) {
				ret = lchild(i);
			}
			if (_cmp(_elem[ret], _elem[rchild(i)])) {
				ret = rchild(i);
			}
			return ret;
		} else if (inHeap(lchild(i))) {
			return (_cmp(_elem[i], _elem[lchild(i)])) ? lchild(i) : i;
		}
		return i;
	}
	template <typename T, typename Container, typename Compare>
	void priority_queue<T, Container, Compare>::buildHeap() {
		for (rank i = parent(_elem.size() - 1); i >= 0; --i) {
			filteDown(i);
		}
	}
	template <typename T, typename Container, typename Compare>
	rank priority_queue<T, Container, Compare>::filteUp(rank i) {
		while (inHeap(parent(i))) {
			rank j = parent(i);
			if (!_cmp(_elem[j], _elem[i])) {
				break;
			}
			swapSupport(_elem[i], _elem[j]);
			i = j;
		}
		return i;
	}
	template <typename T, typename Container, typename Compare>
	rank priority_queue<T, Container, Compare>::filteDown(rank i) {
		for (int j = i; i != (j = porperParent(i)); ) {
			swapSupport(_elem[i], _elem[j]);
			i = j;
		}
		return i;
	}
	// constructor and destructor
	template <typename T, typename Container, typename Compare>
	priority_queue<T, Container, Compare>::priority_queue(Container instance) {
		_elem = instance;
		buildHeap();
	}
	// modifiers
	template <typename T, typename Container, typename Compare>
	void priority_queue<T, Container, Compare>::push(T element) {
		_elem.push_back(element);
		filteUp(_elem.size() - 1);
	}
	template <typename T, typename Container, typename Compare>
	void priority_queue<T, Container, Compare>::pop() {
		swapSupport(_elem.front(), _elem.back());
		_elem.pop_back();
		filteDown(0);
	}
} 

#endif
