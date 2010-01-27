// Module Name: BST.h
// Objective: provide the generic interface for binary search tree
// Author: jcyang[at]ymail.com
// Date: 27.Jan.2010
#include <iostream>
using namespace std;

template<class Elem>
class BinNode {
public:
	Elem value;
	BinNode* rchild;
	BinNode* lchild;
	BinNode(const Elem& value, BinNode* lchild, BinNode* rchild) {
		this->value = value;
		this->lchild = lchild;
		this->rchild = rchild;
	}
};

template<class Elem, class EComp>
class BST {
private:
	BinNode<Elem>* root;

	void backOrderHelper(BinNode<Elem>* subroot) {
		if (subroot->lchild != NULL)
			backOrderHelper(subroot->lchild);
		if (subroot->rchild != NULL)
			backOrderHelper(subroot->rchild);
		cout << subroot->value << "   ";
	}

	void precOrderHelper(BinNode<Elem>* subroot) {
		cout << subroot->value << "   ";
		if (subroot->lchild != NULL)
			precOrderHelper(subroot->lchild);
		if (subroot->rchild != NULL)
			precOrderHelper(subroot->rchild);
	}

	void midOrderHelper(BinNode<Elem>* subroot) {
		if (subroot->lchild != NULL)
			midOrderHelper(subroot->lchild);
		cout << subroot->value << "   ";
		if (subroot->rchild != NULL)
			midOrderHelper(subroot->rchild);
	}

public:
	BST(const Elem* initArr, int size) {
		if (size <= 0)
			return ;
		root = new BinNode<Elem>(initArr[0], NULL, NULL);
		for (int i = 1; i < size; i++) 
			insert(initArr[i]);
	}

	void insert(const Elem& elem) {
		BinNode<Elem>* subroot = root;
		BinNode<Elem>* parent;
		bool isLeft;
		
		while (subroot != NULL) {
			parent = subroot;
			if (EComp::ge(elem, subroot->value))  {
				isLeft = false;
				subroot = subroot->rchild;
			} else {
				isLeft = true;
				subroot = subroot->lchild;
			}
		}

		if (isLeft) 
			parent->lchild = new BinNode<Elem>(elem, NULL, NULL);
		else
			parent->rchild = new BinNode<Elem>(elem, NULL, NULL);
	}

	bool find(const Elem& val) {
		BinNode<Elem>* subroot = root;
		while (subroot != NULL) {
			if (val == subroot->value)
				return true;
			else if (val > subroot->value)
				subroot = subroot->rchild;
			else 
				subroot = subroot->lchild;
		}
		
		return false;
	}

	void backOrder() {
		BinNode<Elem>* subroot = root;
		backOrderHelper(subroot);
	}
	
	void precOrder() {
		BinNode<Elem>* subroot = root;
		precOrderHelper(subroot);
	}

	void midOrder() {
		BinNode<Elem>* subroot = root;
		midOrderHelper(subroot);
	}
};
