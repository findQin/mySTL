#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>
#include "iterator.h" 

namespace mySTL {

typedef int rank;

template <typename T>
class vector {
	private:
		static const int defaultCapacity = 4;
	private:
		T* _elem;
		rank _size;
		rank _capacity;
		
		//true if index is valid
		bool inRange (rank index) {
			return (0 <= index && index < _size);
		}
		//copy elems from elem
		void copyFrom (T* elem, rank lo, rank hi);
		//expand or shrink capacity
		void expand();
		void shrink();
		template <typename X>
		void swapSupply (X& a, X& b) {
			X tmp = a; a = b; b =tmp;
		}
	public:
		//constructor and destructor
		vector ();
		vector (rank size, T value);
		vector (T* elem, rank lo, rank hi);
		~vector () { delete[] _elem;}
		//copy constructor
		vector (vector<T>& v);
		//return basic info
		rank size () { return _size;}
		rank capacity () { return _capacity;}
		bool empty () { return (_size == 0);}
		//override operator
		vector<T>& operator = (vector<T>& v);
		T& operator [] (rank index);
		//element access
		T& at (rank index);
		T& front ();
		T& back ();
		//basic modification operation
		rank push_back (T e);
		void pop_back() { erase(_size - 1);}
		rank insert (rank pos, T e);
		T erase (rank pos);
		rank erase (rank lo, rank hi);
		void resize(rank size);
		void clear();
		void assign(rank size, T e);
		void swap(vector<T>& vec);
		
		//vector<T>::iterator
		class iterator : RandomAccessIterator {
			private:
				T* _element;
			public:
				//constructor and destructor
				iterator() { }
				iterator(T* element)
					: _element(element) { }
				//override operator
				T& operator * () {
					return *(this->_element);
				}
				T* operator -> () {
					return &(operator *());
				}
				iterator& operator = (const iterator it) {
					this->_element = it._element;
					return *this;
				}
				iterator& operator + (int length) {
					this->_element += length;
					return *this;
				}
				iterator& operator - (int length) {
					this->_element -= length;
					return *this;
				}
				int operator - (const iterator it) {
					int length = this->_element - it._element;
					return length;
				}
				iterator& operator ++ () {
					this->_element++;
					return *this;
				}
				const iterator operator ++ (int) {
					return iterator (this->_element++);
				}
				iterator& operator -- () {
					this->_element--;
					return *this;
				}
				const iterator operator -- (int) {
					return iterator (this->_element--);
				}
				bool operator == (const iterator it) {
					return (this->_element == it._element);
				}
				bool operator != (const iterator it) {
					return (this->_element != it._element);
				}
				bool operator < (const iterator it) {
					return (this->_element < it._element);
				}
				bool operator <= (const iterator it) {
					return (this->_element <= it._element);
				}
				bool operator > (const iterator it) {
					return (this->_element > it._element);
				}
				bool operator >= (const iterator it) {
					return (this->_element >= it._element);
				}
		};
	private:
		iterator _begin;
		iterator _end;
	public:
		iterator& begin () {
			_begin = iterator(_elem);
			return _begin;
		}
		iterator& end () {
			_end = iterator(_elem + _size);
			return _end;
		}
};

//private function to supply
template <typename T>
void vector<T>::copyFrom (T* elem, rank lo, rank hi) {
	for (rank i = lo, pos = 0; i < hi; ++i, ++pos) {
		_elem[pos] = elem[i];
	}
}
template <typename T>
void vector<T>::expand () {
	if (_size < _capacity) {
		return;
	}
	while (_capacity < _size) {
		_capacity *= 2;
	}
	T* temp = new T[_capacity];
	for (int i = 0; i < _size; ++i) {
		temp[i] = _elem[i];
	}
	delete[] _elem;
	_elem = temp;
}
template <typename T>
void vector<T>::shrink () {
	if (_capacity < _size << 2 || 
		_capacity / 2 < defaultCapacity) {
		return;
	}
	_capacity = (_size == 0)
			? defaultCapacity : _capacity/= 2;
	T* temp = new T[_capacity];
	for (int i = 0; i < _size; ++i) {
		temp[i] = _elem[i];
	}
	delete[] _elem;
	_elem = temp;
}

//constructor and destructor
template <typename T>
vector<T>::vector () : _size(0), _capacity(defaultCapacity) {
	_elem = new T[_capacity];
}
template <typename T>
vector<T>::vector (rank size, T value) : _size(size) {
	_capacity = ((2 * size) < defaultCapacity)
				? defaultCapacity : 2 * size;
	_elem = new T[_capacity];
	for (rank i = 0; i < _size; ++i) {
		_elem[i] = value;
	}
}
template <typename T>
vector<T>::vector (T* elem, rank lo, rank hi) : _size(hi - lo), _capacity(2 * _size) {
	_elem = new T[_capacity];
	copyFrom(elem, lo, hi);
}
//copy constructor
template <typename T>
vector<T>::vector (vector<T>& v) : _size(v.size()), _capacity(v.capacity()){
	_elem = new T[_capacity];
	copyFrom(v._elem, 0, v.size());
}

//override operator
template <typename T>
vector<T>& vector<T>::operator = (vector<T>& v) {
	if (_elem) {
		delete[] _elem;
	}
	_size = v.size();
	_capacity = 2 * _size;
	_elem = new T[_capacity];
	copyFrom (v._elem, 0, v.size());
}
template <typename T>
T& vector<T>::operator [] (rank index) {
	if (!inRange(index)) {
		throw std::out_of_range("Index is out of range");
	}
	return _elem[index];
}
//element access
template <typename T>
T& vector<T>::at (rank index) {
	if (!inRange(index)) {
		throw std::out_of_range("Index is out of range");
	}
	return _elem[index];
}
template <typename T>
T& vector<T>::front () {
	if (_size == 0) {
		throw std::underflow_error("vector contains nothing");
	}
	return _elem[0];
}
template <typename T>
T& vector<T>::back () {
	if (_size == 0) {
		throw std::underflow_error("vector contains nothing");
	}
	return _elem[_size - 1];
}
//basic modification operation
template <typename T>
rank vector<T>::push_back(T e) {
	expand ();
	_elem[_size++] = e;
	return (_size - 1);
}
template <typename T>
rank vector<T>::insert(rank pos, T e) {
	expand ();
	for (int i = _size; pos < i; --i) {
		_elem[i] = _elem[i - 1];
	}
	_size++;
	_elem[pos] = e;
	return pos;
}
template <typename T>
T vector<T>::erase(rank pos) {
	T temp = _elem[pos];
	erase (pos, pos + 1);
	return temp;
}
template <typename T>
rank vector<T>::erase(rank lo, rank hi) {
	for (int i = hi, pos = lo; i < _size; ++i, ++pos) {
		_elem[pos] = _elem[i];
	}
	_size -= hi - lo;
	shrink();
	return (hi - lo);
}
template <typename T>
void vector<T>::resize(rank size) {
	if (size <= _size) {
		_size = size;
		shrink();
	} else {
		_size = size;
		expand();
	}
}
template <typename T>
void vector<T>::clear() {
	_size = 0;
	_capacity = defaultCapacity;
	delete[] _elem;
	_elem = new T[_capacity];
}
template <typename T>
void vector<T>::assign(rank size, T e) {
	resize(size);
	for (rank i = 0; i < _size; ++i) {
		_elem[i] = e;
	}
}
template <typename T>
void vector<T>::swap(vector<T>& vec) {
	swapSupply(_elem, vec._elem);
	swapSupply(_size, vec._size);
	swapSupply(_capacity, vec._capacity);
}
//end of namespace
}
#endif
