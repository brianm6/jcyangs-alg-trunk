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
	bool isLeaf() {
		return (this->lchild == NULL && this->rchild == NULL);
	}
};

template<class Elem>
void deleteMin(BinNode<Elem>* subroot, Elem& elem) {
    BinNode<Elem>* parent = NULL;

    while (subroot->lchild != NULL) {
        parent = subroot;
        subroot = subroot->lchild;
    }
    elem = subroot->value;
    if (parent != NULL) 
        parent->lchild = NULL;
    delete subroot;
}

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

	bool find(const Elem& elem) {
		BinNode<Elem>* subroot = root;
		while (subroot != NULL) {
			if (EComp::eq(elem, subroot->value))
				return true;
			else if (EComp::gt(elem, subroot->value))
				subroot = subroot->rchild;
			else 
				subroot = subroot->lchild;
		}
		
		return false;
	}

	void deleteMin(Elem& elem) {
		BinNode<Elem>* subroot = root;
		BinNode<Elem>* parent = NULL;

		while (subroot->lchild != NULL) {
			parent = subroot;
			subroot = subroot->lchild;
		}
		elem = subroot->value;
		if (parent != NULL) {
			if (subroot->rchild == NULL) 
				parent->lchild = NULL;
			else 
				parent->lchild = subroot->rchild;
		}
		delete subroot;
	}

	bool deleteElem(const Elem& elem) {
		BinNode<Elem>* subroot = root;
		BinNode<Elem>* parent = NULL;
		BinNode<Elem>* target = NULL;
		bool isLeft;

		while (subroot != NULL) {
			if (EComp::eq(elem, subroot->value)) {
				target = subroot;
				break;
			} else if (EComp::gt(elem, subroot->value)) {
				parent = subroot;
				subroot = subroot->rchild;
				isLeft = false;
			} else {
				parent = subroot;
				subroot = subroot->lchild;
				isLeft = true;
			}
		}

		if (target == NULL)
			return false;
		else {
			if (target->isLeaf()) {
				delete target;
				if (parent == NULL)
					return true;
				else {
					if (isLeft) 
						parent->lchild = NULL;
					else
						parent->rchild = NULL;
				}
			} else if (target->rchild != NULL) {
				Elem rmin;
				::deleteMin<string>(target, rmin);
				target->value = rmin;
			} else {
				if (parent == NULL) {
					root = target->lchild;
					delete target;
				} else {
					parent->lchild = target->lchild;
					delete target;
				}
			}
		}
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

template<class Elem, class EComp>
void output(BST<Elem, EComp> bst, int order) {
	switch (order) {
		case 0:
			bst.precOrder();
			break;
		case 1:
			bst.midOrder();
			break;
		case 2:
			bst.backOrder();
			break;
	}
	cout << endl;
}

template<class Elem, class EComp>
void output(BST<Elem, EComp> bst) {
	int order;

	cout << "precOrder(0) or midOrder(1) or backOrder(2) = ";
	cin >> order;
	output(bst, order);
}
