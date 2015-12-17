#ifndef ALGORITHM_H
#define ALGORITHM_H

namespace mySTL {
	
	//min and max function
	template <typename T>
	const T& min (const T& a, const T& b) {
		return (a < b) ? a : b;
	}
	template <typename T, typename V>
	const T& min (const T& a, const T& b, V& _compare) {
		return (_compare(a, b)) ? a : b;
	}
	template <typename T>
	const T& max (const T& a, const T& b) {
		return (a < b) ? b : a;
	}
	template <typename T, typename V>
	const T& max (const T& a, const T& b, V& _compare) {
		return (_compare(a, b)) ? b : a;
	}
	
	// compare
	template <typename T>
	struct less {
		bool operator () (const T& a, const T& b) {
			return (a < b);
		}
	};
	template <typename T>
	struct greater {
		bool operator () (const T& a, const T& b) {
			return (a > b);
		}
	};
}

#endif
