#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include <iostream>
#include <stdexcept>
#include "iterator.h"

namespace mySTL {
	
	template <typename T>
	class forward_list {
		private:
			// data struct of forward list
			struct ListNode {
				T value;
				ListNode* next;
				ListNode(ListNode* pNext = NULL) : next(pNext){
				} 
				ListNode(T val, ListNode* pNext = NULL) : value(val), next(pNext) {
				}
			};
			// dummy node
			ListNode* beginNode;
			ListNode* endNode;
			rank _size;
			
			// basic support function
			void initDummy();
			void copyFrom(forward_list<T>& list);
			void copyValue(rank n, T val);
			void delContain();
			template <typename V>
			void support_swap(V& a, V& b) {
				V tmp = a; a = b; b = tmp;
			}
		public:
			// constructor and destructor
			forward_list();
			forward_list(rank size, T val);
			forward_list(forward_list<T>& list);
			~forward_list();
			// override operator =
			forward_list<T>& operator = (forward_list<T>& list);
			// capacity
			bool empty();
			rank size() { return _size;}
			// element access
			T& front();
			// modifiers
			void assign(rank size, T val);
			void push_front(T val);
			void pop_front();
			void swap(forward_list<T>& list);
			void resize(rank n, T val);
			void clear();
			// operations
			void remove(T val);
			void unique();
			void reverse();
			
			// forward_list<T> iterator
			class iterator : ForwardIterator {
				friend class forward_list<T>;
				private:
					ListNode* _element;
				public:
				//constructor and destructor
				iterator() { }
				iterator(ListNode* element)
					: _element (element) { }
				//override operator
				T& operator * () {
					return this->_element->value;
				}
				T* operator -> () {
					return &(operator *());
				}
				iterator& operator = (const iterator it) {
					this->_element = it._element;
					return *this;
				}
				iterator& operator ++ () {
					this->_element = this->_element->next;
					return *this;
				}
				const iterator operator ++ (int) {
					iterator tmp(this->_element);
					this->_element = this->_element->next;
					return tmp;
				}
				bool operator == (const iterator it) {
					return (this->_element == it._element);
				}
				bool operator != (const iterator it) {
					return (this->_element != it._element);
				}
			};
		private:
			iterator _before_begin;
			iterator _begin;
			iterator _end;
		public:
			iterator& before_begin () {
				_before_begin = iterator(beginNode);
				return _before_begin;
			}
			iterator& begin () {
				_begin = iterator(beginNode->next);
				return _begin;
			}
			iterator& end () {
				_end = iterator(endNode);
				return _end;
			}
			// modifiers with iterator
			iterator insert_after (iterator it, T val) {
				if (it._element == endNode) {
					return _end;
				}
				ListNode* tmp = it._element->next;
				it._element->next = new ListNode(val, tmp);
				_size++;
				return iterator(it._element->next);
			}
			iterator erase_after (iterator it) {
				if (it._element == endNode || it._element->next == endNode) {
					return _end;
				}
				ListNode* tmp = it._element->next->next;
				delete it._element->next;
				it._element->next = tmp;
				_size--;
				return iterator(it._element->next);
			}
	};
	// priavte
	// basic support function
	template <typename T>
	void forward_list<T>::initDummy() {
		beginNode = new ListNode();
		endNode = new ListNode();
		beginNode->next = endNode;
		_size = 0;
	}
	template <typename T>
	void forward_list<T>::copyFrom(forward_list<T>& list) {
		ListNode* res = list.beginNode;
		ListNode* des = beginNode;
		while (res->next != list.endNode) {
			des->next = new ListNode(res->next->value);
			des = des->next;
			res = res->next;
		}
		des->next = endNode;
		_size = list._size;
	}
	template <typename T>
	void forward_list<T>::copyValue(rank n, T val) {
		_size = n;
		ListNode* tmp = beginNode;
		while (n-- > 0) {
			tmp->next = new ListNode(val);
			tmp = tmp->next;
		}
		tmp->next = endNode;
	}
	template <typename T>
	void forward_list<T>::delContain() {
		ListNode* tmp = beginNode->next;
		while (tmp != endNode) {
			ListNode* t = tmp;
			tmp = tmp->next;
			delete t;
		}
		beginNode->next = endNode;
		_size = 0;
	}
	// implement of constructor and destructor
	template <typename T>
	forward_list<T>::forward_list() {
		initDummy();
	}
	template <typename T>
	forward_list<T>::forward_list(rank size, T val) {
		initDummy();
		copyValue(size, val);
	}
	template <typename T>
	forward_list<T>::forward_list(forward_list<T>& list) {
		initDummy();
		copyFrom(list);
	}
	template <typename T>
	forward_list<T>::~forward_list() {
		delContain();
		delete beginNode;
		delete endNode;
	}
	// implement override operator =
	template <typename T>
	forward_list<T>& forward_list<T>::operator = (forward_list<T>& list) {
		delContain();
		copyFrom(list);
		return *this;
	}
	// capacity 
	template <typename T>
	bool forward_list<T>::empty() {
		return (_size == 0);
	}
	// element access
	template <typename T>
	T& forward_list<T>::front() {
		if (_size == 0) {
			throw std::underflow_error("forward_list contains nothing");
		}
		return beginNode->next->value;
	}
	// modifiers
	template <typename T>
	void forward_list<T>::assign(rank size, T val) {
		delContain();
		copyValue(size, val);
	}
	template <typename T>
	void forward_list<T>::push_front(T val) {
		ListNode* tmp = new ListNode(val, beginNode->next);
		beginNode->next = tmp;
		_size++;
	}
	template <typename T>
	void forward_list<T>::pop_front() {
		if (_size == 0) {
			throw std::underflow_error("forward_list contains nothing");
		}
		ListNode* tmp = beginNode->next;
		beginNode->next = tmp->next;
		delete tmp;
		_size--;
	}
	template <typename T>
	void forward_list<T>::swap(forward_list<T>& list) {
		support_swap(beginNode, list.beginNode);
		support_swap(endNode, list.endNode);
		support_swap(_size, list._size);
	}
	template <typename T>
	void forward_list<T>::resize(rank n, T val) {
		if (n == _size) {
			return;
		} else if (n < _size) {
			ListNode* tmp = beginNode;
			for ( rank i = 0; i < n; ++i, tmp = tmp->next)
				;
			while (tmp->next != endNode) {
				ListNode* t = tmp->next->next;
				delete tmp->next;
				tmp->next = t;
			}
			tmp->next = endNode;
			_size = n;
		} else {
			ListNode* tmp = beginNode;
			while (tmp->next != endNode) {
				tmp = tmp->next;
			}
			for ( ; _size < n; ++_size) {
				tmp->next = new ListNode(val);
				tmp = tmp->next;
			}
			tmp->next = endNode;
		}
	}
	template <typename T>
	void forward_list<T>::clear() {
		delContain();
	}
	// operations
	template <typename T>
	void forward_list<T>::remove(T val) {
		ListNode* beg = beginNode;
		ListNode* tmp = beginNode->next;
		while (tmp != endNode) {
			if (tmp->value == val) {
				tmp = tmp->next;
				delete beg->next;
				beg->next = tmp;
				_size--;
				continue;
			}
			tmp = tmp->next;
			beg = beg->next;
		}
	}
	template <typename T>
	void forward_list<T>::unique() {
		if (_size <= 1) {
			return;
		}
		ListNode* tmp = beginNode->next;
		ListNode* tmpNext = tmp->next;
		while (tmpNext != endNode) {
			if (tmp->value == tmpNext->value) {
				tmpNext = tmpNext->next;
				delete tmp->next;
				tmp->next = tmpNext;
				_size--;
				continue;
			}
			tmp = tmp->next;
			tmpNext = tmpNext->next;
		}
	}
	template <typename T>
	void forward_list<T>::reverse() {
		ListNode* save = beginNode->next;
		ListNode* tmp = save;
		while (tmp != endNode) {
			ListNode* tmpNext = tmp->next;
			tmp->next = beginNode->next;
			beginNode->next = tmp;
			tmp = tmpNext;
		}
		save->next = endNode;
	}
//end of namespace
}
#endif 
