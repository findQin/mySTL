#ifndef MAP_H
#define MAP_H

#include "AVLBST.h"

namespace mySTL {
	
	template <typename T, typename Value, typename Node = AVLNode<T, Value>>
	class map : AVLBST<T, Value, Node> {
		protected:
			void copyMap(map<T, Value, Node>& m);
		public:
			// constructor and destructor
			map() : AVLBST<T, Value, Node>() {}
			map(map<T, Value, Node>& m) { copyMap(m);}
			map<T, Value, Node>& operator = (map<T, Value, Node> m) { BST<T, Node>::deleteBST(); copyMap(m);}
			~map() {}
			
			// capacity
			bool empty() { return BST<T, Node>::empty();}
			rank size() { return BST<T, Node>::size();}
			
			// modifiers
			Node* find(T element) { return AVLBST<T, Value, Node>::find(element);}
			rank count(T element) { return (AVLBST<T, Value, Node>::find(element) == NULL) ? 0 : 1;}
			Node* insert(T element, Value value) { Node* ret = AVLBST<T, Value, Node>::insert(element); ret->_value = value; return ret;}
			Node* erase(T element) { return AVLBST<T, Value, Node>::erase(element);}
			void clear() { BST<T, Node>::deleteBST();}
			
			// element accsee
			Value& operator [] (T element) { Node* ret = AVLBST<T, Value, Node>::insert(element); return ret->_value;}
			Value& at (T element) { return operator [] (element);}
	};
	// protected function
	template <typename T, typename Value, typename Node>
	void map<T, Value, Node>::copyMap(map<T, Value, Node>& m) {
		BST<T, Node>::_size = m._size;
		Node** _res = new Node*[m._size + 1];
		Node** _des = new Node*[m._size + 1];
		_res[0] = m._root;
		_des[0] = NULL;
		if (m._root)
			_des[0] = new Node(*(_res[0]));
		rank now = 1;
		for (rank i = 0; i < m._size; ++i) {
			if (_res[i]->lchild) {
				_res[now] = _res[i]->lchild;
				_des[now] = new Node(*(_res[i]->lchild));
				_des[i]->lchild = _des[now];
				_des[now++]->parent = _des[i];
			}
			if (_res[i]->rchild) {
				_res[now] = _res[i]->rchild;
				_des[now] = new Node(*(_res[i]->rchild));
				_des[i]->rchild = _des[now];
				_des[now++]->parent = _des[i];
			}
		}
		BST<T, Node>::_root = _des[0];
		delete[] _res;
		delete[] _des;
	}
	// end of namespace
}

#endif
