#ifndef BST_H
#define BST_H

#include <iostream>
#include "iterator.h"
#include "algorithm.h"

namespace mySTL {
	// strcut BSTNode
	template <typename T>
	struct BSTNode {
		T _element;
		rank _height;
		BSTNode* parent;
		BSTNode* lchild;
		BSTNode* rchild;
		BSTNode() : _element(T()), _height(0), parent(NULL), lchild(NULL), rchild(NULL){}
		BSTNode(T element, rank height = rank(), BSTNode* par = NULL, BSTNode* lc = NULL, BSTNode* rc = NULL)
				: _element(element), _height(height), parent(par), lchild(lc), rchild(rc) {}
		BSTNode(BSTNode& node) {
			_element = node._element; _height = node._height; 
			parent = NULL; lchild = NULL; rchild = NULL;
		}
		BSTNode& operator = (BSTNode& node) {
			_element = node._element; _height = node._height; 
			return *this;
		}
		void swap(BSTNode& node) {
			T tmp = _element;
			_element = node._element;
			node._element = tmp;
		}
	};
	
	template <typename T, typename Node = BSTNode<T>>
	class BST {
		protected:
			Node* _root;
			rank _size;
			
			void copyBST(BST& Tree);
			void deleteBST();
			Node* search(T element);
			Node* searchIn(T element);
			rank getHeight(Node* p) { return (p == NULL) ? -1 : p->_height;}
			void UpdateHeight(Node* p);
		public:
			// constructor and destructor
			BST() : _root(NULL), _size(0) {}
			BST(BST& Tree) { copyBST(Tree);}
			~BST(){ deleteBST();}
			BST& operator = (BST Tree);
			
			// capacity
			bool empty() { return (_size == 0);}
			rank size() { return _size;}
			
			// modifiers
			Node* find(T element);
			Node* insert(T element);
			Node* erase(T element);
			
	};
	// implement support
	template <typename T, typename Node>
	void BST<T, Node>::copyBST(BST<T, Node>& Tree) {
		_size = Tree._size;
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
		_root = _des[0];
		delete[] _res;
		delete[] _des;
	}
	template <typename T, typename Node>
	void BST<T, Node>::deleteBST() {
		Node** _res = new Node*[_size + 1];
		_res[0] = _root;
		rank now = 1;
		for (rank i = 0; i < _size; ++i) {
			if (_res[i]->lchild) {
				_res[now++] = _res[i]->lchild;
			}
			if (_res[i]->rchild) {
				_res[now++] = _res[i]->rchild;
			}
			if (_res[i] != NULL)
				delete _res[i];
		}
		_size = 0;
		_root = NULL;
	}
	template <typename T, typename Node>
	Node* BST<T, Node>::search(T element) {
		Node* p = _root;
		while(p) {
			if (p->_element == element) {
				return p;
			}
			p = (p->_element < element) ? p->rchild : p->lchild;
		} 
		return p;
	}
	template <typename T, typename Node>
	Node* BST<T, Node>::searchIn(T element) {
		Node* p = _root;
		if (!p) {
			_size++;
			_root = new Node();
			return _root;
		}
		while(p) {
			if (p->_element == element) {
				return p;
			}
			if (p->_element < element) {
				if (p->rchild) {
					p = p->rchild;
				} else {
					p->rchild = new Node();
					p->rchild->parent = p;
					_size++;
					UpdateHeight(p);
					return p->rchild;
				}
			} else {
				if (p->lchild) {
					p = p->lchild;
				} else {
					p->lchild = new Node();
					p->lchild->parent = p;
					_size++;
					UpdateHeight(p);
					return p->lchild;
				}
			}
		}
		return p;
	}
	template <typename T, typename Node>
	void BST<T, Node>::UpdateHeight(Node* p) {
		while (p) {
			p->_height = max(getHeight(p->lchild), getHeight(p->rchild)) + 1;
			p = p->parent;
		}
	}
	// constructor and destructor
	template <typename T, typename Node>
	BST<T, Node>& BST<T,Node>::operator = (BST<T, Node> Tree) {
		deleteBST();
		copyBST(Tree);
		return *this;
	} 
	
	// modifiers
	template <typename T, typename Node>
	Node* BST<T, Node>::find(T element) {
		return search(element);
	}
	template <typename T, typename Node>
	Node* BST<T, Node>::insert(T element) {
		Node* tmp = searchIn(element);
		tmp->_element = element;
		return tmp;
	}
	template <typename T, typename Node>
	Node* BST<T, Node>::erase(T element) {
		Node* tmp = search(element);
		if (!tmp) {
			return NULL;
		}
		_size--;
		Node* ret = NULL;
		if (tmp->lchild == NULL && tmp->rchild == NULL) {
			if (!tmp->parent) {
				delete tmp;
				_root = NULL;
			} else {
				if (tmp->parent->lchild == tmp) tmp->parent->lchild = NULL;
				if (tmp->parent->rchild == tmp) tmp->parent->rchild = NULL;
				UpdateHeight(tmp->parent);
				ret = tmp->parent;
				delete tmp;
			}
		} else if (tmp->lchild == NULL && tmp->rchild != NULL) {
			if (!tmp->parent) {
				_root = tmp->lchild;
				_root->parent = NULL;
				ret = _root;
				delete tmp;
			} else {
				if (tmp->parent->lchild == tmp) tmp->parent->lchild = tmp->rchild;
				if (tmp->parent->rchild == tmp) tmp->parent->rchild = tmp->rchild;
				tmp->rchild->parent = tmp->parent;
				UpdateHeight(tmp->parent);
				ret = tmp->parent;
				delete tmp;
			}
		} else if (tmp->lchild != NULL && tmp->rchild == NULL) {
			if (!tmp->parent) {
				_root = tmp->rchild;
				_root->parent = NULL;
				ret = _root;
				delete tmp;
			} else {
				if (tmp->parent->lchild == tmp) tmp->parent->lchild = tmp->lchild;
				if (tmp->parent->rchild == tmp) tmp->parent->rchild = tmp->lchild;
				tmp->lchild->parent = tmp->parent;
				UpdateHeight(tmp->parent);
				ret = tmp->parent;
				delete tmp;
			}
		} else {
			Node* RL = tmp->rchild;
			while (RL->lchild) {
				RL = RL->lchild;
			}
			tmp->swap(*RL);
			if (!RL->rchild) {
				if (RL->parent->lchild == RL) RL->parent->lchild = NULL;
				if (RL->parent->rchild == RL) RL->parent->rchild = NULL;
				UpdateHeight(RL->parent);
				ret = RL->parent;
				delete RL;
			} else {
				if (RL->parent->lchild == RL) RL->parent->lchild = RL->rchild;
				if (RL->parent->rchild == RL) RL->parent->rchild = RL->rchild;
				RL->rchild->parent = RL->parent;
				UpdateHeight(RL->parent);
				ret = RL->parent;
				delete RL;
			}
		}
		return ret;
	}
	
	// end of namespace
}

#endif
