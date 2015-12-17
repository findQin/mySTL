#ifndef STACK_H
#define STACK_H

#include "vector.h"

namespace mySTL {
	template < typename T, typename Container = vector<T> >
	class stack {
		private:
			Container _elem;
		public:
			//constructor and destructor
			stack () {};
			stack (Container& vec) {
				this->_elem = vec;
			}
			stack (stack<T, Container>& _stack) {
				this->_elem = _stack._elem;
			}
			~stack () {}
			//override operator =
			void operator = (stack<T, Container>& _stack) {
				this->_elem = _stack._elem;
			}
			//basic stack information
			bool empty () {
				return _elem.empty ();
			}
			rank size () {
				return _elem.size ();
			}
			//get or modify element in stack
			T& top () {
				return _elem.back();
			}
			void push (const T& element) {
				_elem.push_back (element);
			}
			void pop () {
				if (_elem.size() != 0) {
					_elem.erase(_elem.size () - 1);
				} else {
					throw std::underflow_error("stack contains nothing");
				}
			}
	};
	//end of namespace mySTL
}

#endif 
