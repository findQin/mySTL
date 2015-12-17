#ifndef AVLBST_H
#define AVLBST_H

#include "BST.h"

namespace mySTL {
	// struct AVLNode
	template <typename T, typename Value>
	struct AVLNode {
		T _element;
		Value _value;
		rank _height;
		AVLNode* parent;
		AVLNode* lchild;
		AVLNode* rchild;
		AVLNode() : _element(T()), _value(Value()), _height(0), parent(NULL), lchild(NULL), rchild(NULL){}
		AVLNode(T element, Value value, rank height = rank(), AVLNode* par = NULL, AVLNode* lc = NULL, AVLNode* rc = NULL)
				: _element(element), _value(value), _height(height), parent(par), lchild(lc), rchild(rc) {}
		AVLNode(AVLNode& node) {
			_element = node._element; _value = node._value, _height = node._height; 
			parent = NULL; lchild = NULL; rchild = NULL;
		}
		AVLNode& operator = (AVLNode& node) {
			_element = node._element; _value = node._value; _height = node._height; 
			return *this;
		}
		void swap(AVLNode& node) {
			T tmp = _element; Value tmpV = _value;
			_element = node._element; _value = node._value;
			node._element = tmp; node._value = tmpV;
		}
	};
	
	template <typename T, typename Value, typename Node = AVLNode<T, Value>>
	class AVLBST : BST<T, Node> {
		protected:
			
			void copyAVL(AVLBST& Tree);
			Node* rotateAt(Node* g);
			Node* connect34(Node* a, Node* b, Node* c, Node* T0, Node* T1, Node* T2, Node* T3);
			bool isBalanced(Node* g);
		public:
			// constructor and destructor
			AVLBST() : BST<T, Node>(){}
			AVLBST(AVLBST& Tree) { copyAVL(Tree);}
			~AVLBST() { }
			
			// capacity
			bool empty() { return BST<T, Node>::empty();}
			rank size() { return BST<T, Node>::size();}
			
			// modifiers
			Node* find(T element);
			Node* insert(T element);
			Node* erase(T element);
			
			// test
			Node* getRoot() { return BST<T, Node>::_root;}
	};
	
	// protected implement
	template <typename T, typename Value, typename Node>
	void AVLBST<T, Value, Node>::copyAVL(AVLBST& Tree) {
		BST<T, Node>::_size = Tree._size;
		Node** _res = new Node*[Tree._size + 1];
		Node** _des = new Node*[Tree._size + 1];
		_res[0] = Tree._root;
		_des[0] = NULL;
		if (Tree._root)
			_des[0] = new Node(*(_res[0]));
		rank now = 1;
		for (rank i = 0; i < Tree._size; ++i) {
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
	
	template <typename T, typename Value, typename Node>
	Node* AVLBST<T, Value, Node>::rotateAt(Node* g) {
		if (BST<T, Node>::getHeight(g->lchild) > BST<T, Node>::getHeight(g->rchild)) {
			Node* p = g->lchild;
			if (BST<T, Node>::getHeight(p->lchild) > BST<T, Node>::getHeight(p->rchild)) {
				// zig-zig
				p->parent = g->parent;
				if (g->parent) {
					if (g->parent->lchild == g) g->parent->lchild = p;
					if (g->parent->rchild == g) g->parent->rchild = p;
				}
				return connect34(p->lchild, p, g, p->lchild->lchild, p->lchild->rchild, p->rchild, g->rchild);
			} else {
				// zig-zag
				p->rchild->parent = g->parent;
				if (g->parent) {
					if (g->parent->lchild == g) g->parent->lchild = p->rchild;
					if (g->parent->rchild == g) g->parent->rchild = p->rchild;
				}
				return connect34(p, p->rchild, g, p->lchild, p->rchild->lchild, p->rchild->rchild, g->rchild);
			}
		} else {
			Node* p = g->rchild;
			if (BST<T, Node>::getHeight(p->lchild) < BST<T, Node>::getHeight(p->rchild)) {
				// zag-zag
				p->parent = g->parent;
				if (g->parent) {
					if (g->parent->lchild == g) g->parent->lchild = p;
					if (g->parent->rchild == g) g->parent->rchild = p;
				}
				return connect34(g, p, p->rchild, g->lchild, p->lchild, p->rchild->lchild, p->rchild->rchild);
			} else {
				// zag-zig
				p->lchild->parent = g->parent;
				if (g->parent) {
					if (g->parent->lchild == g) g->parent->lchild = p->lchild;
					if (g->parent->rchild == g) g->parent->rchild = p->lchild;
				}
				return connect34(g, p->lchild, p, g->lchild, p->lchild->lchild, p->lchild->rchild, p->rchild);		
			}
		}
	}
	template <typename T, typename Value, typename Node>
	Node* AVLBST<T, Value, Node>::connect34(Node* a, Node* b, Node* c, Node* T0, Node* T1, Node* T2, Node* T3) {
		b->lchild = a; b->rchild = c;
		a->parent = b; c->parent = b;
		a->lchild = T0; if (T0) T0->parent = a;
		a->rchild = T1; if (T1) T1->parent = a;
		c->lchild = T2; if (T2) T2->parent = c;
		c->rchild = T3; if (T3) T3->parent = c;
		BST<T, Node>::UpdateHeight(a);
		BST<T, Node>::UpdateHeight(c);
		return b;
	}
	template <typename T, typename Value, typename Node>
	bool AVLBST<T, Value, Node>::isBalanced(Node* g) {
		if (g == NULL) {
			return true;
		}
		rank lh = BST<T, Node>::getHeight(g->lchild);
		rank rh = BST<T, Node>::getHeight(g->rchild);
		return ((lh - rh > -2) && (lh - rh < 2));
	}
	// public function
	template <typename T, typename Value, typename Node>
	Node* AVLBST<T, Value, Node>::find(T element) {
		return BST<T, Node>::find(element);
	}
	
	template <typename T, typename Value, typename Node>
	Node* AVLBST<T, Value, Node>::insert(T element) {
		Node* _hot = BST<T, Node>::insert(element);
		for (Node* g = _hot; g; g = g->parent) {
			if (!isBalanced(g)) {
				g = rotateAt(g);
				if (g->parent == NULL) {
					BST<T, Node>::_root = g;
				}	
			} else {
				BST<T, Node>::UpdateHeight(g);
			}
		}
		return _hot;
	}
	
	template <typename T, typename Value, typename Node>
	Node* AVLBST<T, Value, Node>::erase(T element) {
		Node* _hot = BST<T, Node>::erase(element);
		for (Node* g = _hot; g; g = g->parent) {
			if (!isBalanced(g)) {
				g = rotateAt(g);
				if (g->parent == NULL) {
					BST<T, Node>::_root = g;
				}	
			}
			BST<T, Node>::UpdateHeight(g);
		}
		return _hot;
	}
	
	// end of namespace
}


#endif
