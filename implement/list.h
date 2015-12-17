#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <stdexcept>
#include "iterator.h"

namespace mySTL {
	
	template <typename T>
	class list {
		private:
			// struct ListNode body
			struct ListNode {
				T value;
				ListNode* prev;
				ListNode* next;
				ListNode() : prev(NULL), next(NULL) {
				}
				ListNode(T val, ListNode* _prev, ListNode* _next)
					: value(val), prev(_prev), next(_next) {
				}
			};
			// dummy node
			ListNode* beginNode;
			ListNode* endNode;
			rank _size;
			// support function
			void initDummy();
			void copyValue(rank n, T val, ListNode* beg, ListNode* end);
			void copyFrom(list<T>& li);
			void delContain(ListNode* beg, ListNode* end);
			template <typename X>
			void swapSupply (X& a, X& b) {
				X tmp = a; a = b; b =tmp;
			}
			void sortSupply(ListNode* beg, ListNode* end);
			ListNode* getHalf(ListNode* beg, ListNode* end) {
				if (beg == end || beg->next == end || beg->next->next == end) {
					return beg;
				}
				ListNode* slow = beg;
				ListNode* fast = beg;
				for ( ; ; slow = slow->next, fast = fast->next->next) {
					if (fast->next == end || fast->next->next == end) {
						break;
					} 
				}
				return slow;
			}
			void getPorperMid(ListNode* beg, ListNode* mid, ListNode* end);
		public:
			// constructor and destructor
			list();
			list(rank n, T val);
			list(list& li);
			~list();
			// override operator =
			list<T>& operator = (list<T>& res);
			// capacity
			bool empty() { return (_size == 0);}
			rank size() { return _size;}
			// element access
			T& front();
			T& back();
			// modifiers
			void assign(rank n, T val);
			void push_front(T val);
			void pop_front();
			void push_back(T val);
			void pop_back();
			void swap(list<T>& li);
			void resize(rank n, T val);
			void clear();
			// operations
			void remove(T val);
			void unique();
			void merge(list<T>& li);
			void reverse();
			void sort();
			
			class iterator : BidirectionIterator {
				friend class list<T>;
				private:
					ListNode* _element;
				public:
					iterator() { }
					iterator(ListNode* element)
						: _element(element) { }
					T& operator * () {
						return _element->value;
					}
					T* operator -> () {
						return &(operator *());
					}
					iterator& operator = (iterator it) {
						_element = it._element;
						return *this;
					}
					iterator& operator ++ () {
						_element = _element->next;
						return *this;
					}
					iterator& operator -- () {
						_element = _element->prev;
						return *this;
					}
					const iterator operator ++ (int) {
						iterator it(_element);
						_element = _element->next;
						return it;
					}
					const iterator operator -- (int) {
						iterator it(_element);
						_element = _element->prev;
						return it;
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
			iterator& before_begin() {
				_before_begin = iterator(beginNode);
				return _before_begin;
			}
			iterator& begin() {
				_begin = iterator(beginNode->next);
				return _begin;
			}
			iterator& end() {
				_end = iterator(endNode);
				return _end;
			}
			iterator insert(iterator it, T value) {
				copyValue(1, value, it._element->prev, it._element);
				return iterator(it._element->next);
			}
			iterator insert(iterator it, rank n, T value) {
				copyValue(n, value, it._element->prev, it._element);
				return iterator(it._element->next);
			}
			iterator erase(iterator it) {
				ListNode* tmp = it._element->next;
				delContain(it._element->prev, tmp);
				return iterator(tmp);
			}
			iterator erase(iterator beg, iterator end) {
				delContain(beg._element->prev, end._element);
				return iterator(end._element);
			}
	};
	// priavte
	// implement of support function
	template <typename T>
	void list<T>::initDummy() {
		_size = 0;
		beginNode = new ListNode();
		endNode = new ListNode();
		beginNode->next = endNode;
		endNode->prev = beginNode;
	}
	template <typename T>
	void list<T>::copyValue(rank n, T val, ListNode* beg, ListNode* end) {
		_size += n;
		ListNode* tmp = beg;
		while (n--) {
			tmp->next = new ListNode (val, tmp, NULL);
			tmp = tmp->next;
		}
		tmp->next = end;
		end->prev = tmp;
	}
	template <typename T>
	void list<T>::copyFrom(list<T>& li) {
		_size = li._size;
		ListNode* res = li.beginNode;
		ListNode* des = beginNode;
		while ( res->next != li.endNode) {
			des->next = new ListNode(res->next->value, des, NULL);
			res = res->next;
			des = des->next;
		}
		des->next = endNode;
		endNode->prev = des;
	}
	template <typename T>
	void list<T>::delContain(ListNode* beg, ListNode* end) {
		ListNode* tmp = beg->next;
		while (tmp != end) {
			_size--;
			ListNode* t = tmp->next;
			delete tmp;
			tmp = t;
		}
		beg->next = end;
		end->prev = beg;
	}
	template <typename T>
	void list<T>::getPorperMid(ListNode* beg, ListNode* mid, ListNode* end) {
		if (mid->value < beg->value && mid->value < end->value) {
			if (beg->value < end->value) {
				swapSupply(mid->value, beg->value);
			} else {
				swapSupply(mid->value, end->value);
			}
		} else if (mid->value > beg->value && mid->value > end->value) {
			if (beg->value < end->value) {
				swapSupply(mid->value, end->value);
			} else {
				swapSupply(mid->value, beg->value);
			}
		}
	}
	template <typename T>
	void list<T>::sortSupply(ListNode* beg, ListNode* end) {
		ListNode* mid = getHalf(beg, end);
		if (mid == beg) {
			return;
		}
		getPorperMid(beg->next, mid, end->prev);
		T val = mid->value;
		ListNode* tmpBeg = beg;
		ListNode* tmpMid = mid;
		ListNode* tmp = beg->next;
		ListNode* tmpM = mid->next;
		for ( ; tmp != mid; tmp = tmp->next) {
			if (tmp->value < val) {
				tmpBeg->next = tmp;
				tmp->prev = tmpBeg;
				tmpBeg = tmpBeg->next;
			} else {
				tmpMid->next = tmp;
				tmp->prev = tmpMid;
				tmpMid = tmpMid->next;
			}
		}
		for ( ; tmpM != end; tmpM = tmpM->next) {
			if (tmpM->value < val) {
				tmpBeg->next = tmpM;
				tmpM->prev = tmpBeg;
				tmpBeg = tmpBeg->next;
			} else {
				tmpMid->next = tmpM;
				tmpM->prev = tmpMid;
				tmpMid = tmpMid->next;
			}
		}
		tmpBeg->next = mid;
		mid->prev = tmpBeg;
		tmpMid->next = end;
		end->prev = tmpMid;
		sortSupply(beg, mid);
		sortSupply(mid, end);
	}
	// implement of constructor and descontructor
	template <typename T>
	list<T>::list() {
		initDummy();
	}
	template <typename T>
	list<T>::list(rank n, T val) {
		initDummy();
		copyValue( n, val, beginNode, endNode);
	}
	template <typename T>
	list<T>::list(list<T>& li) {
		initDummy();
		copyFrom(li);
	}
	template <typename T>
	list<T>::~list() {
		delContain(beginNode, endNode);
		delete beginNode;
		delete endNode;
	}
	// implement of override operator =
	template <typename T>
	list<T>& list<T>::operator = (list<T>& res) {
		delContain(beginNode, endNode);
		copyFrom(res);
	}
	// implement of element access
	template <typename T>
	T& list<T>::front() {
		if (_size == 0) {
			throw std::underflow_error("list contains nothing");
		}
		return beginNode->next->value;
	}
	template <typename T>
	T& list<T>::back() {
		if (_size == 0) {
			throw std::underflow_error("list contains nothing");
		}
		return endNode->prev->value;
	}
	// implement of modifiers
	template <typename T>
	void list<T>::assign(rank n, T val) {
		delContain(beginNode, endNode);
		copyValue( n, val, beginNode, endNode);
	}
	template <typename T>
	void list<T>::push_front(T val) {
		copyValue(1, val, beginNode, beginNode->next);
	}
	template <typename T>
	void list<T>::pop_front() {
		if (_size == 0) {
			throw std::underflow_error("list contains nothing");
		}
		delContain(beginNode, beginNode->next->next);
	}
	template <typename T>
	void list<T>::push_back(T val) {
		copyValue(1, val, endNode->prev, endNode);
	}
	template <typename T>
	void list<T>::pop_back() {
		if (_size == 0) {
			throw std::underflow_error("list contains nothing");
		}
		delContain(endNode->prev->prev, endNode);
	}
	template <typename T>
	void list<T>::swap(list<T>& li) {
		swapSupply(_size, li._size);
		swapSupply(beginNode, li.beginNode);
		swapSupply(endNode, li.endNode);
	}
	template <typename T>
	void list<T>::resize(rank n, T val) {
		if ( n == _size) {
			return;
		} else if ( n < _size) {
			ListNode* tmp = beginNode;
			for ( ; n--; tmp = tmp->next)
				;
			delContain(tmp, endNode);
		} else {
			ListNode* tmp = endNode->prev;
			copyValue(n - _size, val, tmp, endNode);
		}
	}
	template <typename T>
	void list<T>::clear() {
		delContain(beginNode, endNode);
	}
	// operations
	template <typename T>
	void list<T>::remove(T val) {
		ListNode* beg = beginNode;
		ListNode* tmp = beg->next;
		while (tmp != endNode) {
			if (tmp->value == val) {
				ListNode* t = tmp->next;
				delContain(tmp->prev, tmp->next);
				tmp = t;
			} else {
				beg = beg->next;
				tmp = tmp->next;
			}
		}
	}
	template <typename T>
	void list<T>::unique() {
		if (_size <= 1) {
			return;
		}
		ListNode* beg = beginNode->next;
		ListNode* tmp = beg->next;
		while (tmp != endNode) {
			if (tmp->value == beg->value) {
				ListNode* t = tmp->next;
				delContain(tmp->prev, tmp->next);
				tmp = t;
			} else {
				beg = beg->next;
				tmp = tmp->next;	
			}
		}
	}
	template <typename T>
	void list<T>::merge(list<T>& li) {
		_size += li._size;
		ListNode* res = beginNode;
		ListNode* des = li.beginNode;
		while (res->next != endNode || des->next != li.endNode) {
			if (res->next->value <= des->next->value) {
				res = res->next;
			} else {
				ListNode* t = res->next;
				res->next = new ListNode(des->next->value, res, t);
				t->prev = res->next;
				res = res->next;
				des = des->next;
			}
		}
		while (des->next != li.endNode) {
			ListNode* t = res->next;
			res->next = new ListNode(des->next->value, res, t);
			t->prev = res->next;
			res = res->next;
			des = des->next;
		}
	}
	template <typename T>
	void list<T>::reverse() {
		ListNode* tmp = endNode;
		ListNode* t = endNode->prev;
		while (t != beginNode) {
			ListNode* p = t->prev;
			tmp->next = t;
			t->prev = tmp;
			tmp = tmp->next;
			t = p;
		}
		ListNode* p = endNode->next;
		tmp->next = endNode;
		endNode->prev = tmp;
		endNode->next = NULL;
		beginNode->next = p;
		p->prev = beginNode;
		beginNode->prev = NULL;
	}
	template <typename T>
	void list<T>::sort() {
		sortSupply(beginNode, endNode);
	}
// end of namepace
}
#endif
