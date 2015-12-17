#ifndef ITERATOR_H
#define ITERATOR_H

#include <iostream>

namespace mySTL {
	
	typedef int rank;
	//Basic iterator

	class BasicIterator {
		protected:
			BasicIterator () { }
		public:
			virtual ~BasicIterator () { }
	};
	//Basic const iterator
	class CBasicIterator {
		protected:
			CBasicIterator () { }
		public:
			virtual ~CBasicIterator () { }
	};
	//Fordward iterator
	class ForwardIterator : public BasicIterator {
		protected:
			ForwardIterator () { }
		public:
			virtual ~ForwardIterator () { }
	};
	//Bidirectional iterator
	class BidirectionIterator : public BasicIterator {
		protected:
			BidirectionIterator () { }
		public:
			virtual ~BidirectionIterator () { }
	};
	//Random access iterator
	class RandomAccessIterator : public BasicIterator {
		protected:
			RandomAccessIterator () { }
		public:
			virtual ~RandomAccessIterator () { }
	};
//end of namespace
}

#endif
