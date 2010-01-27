// Module Name: IntBST.h
// Objective: provide the declaration and definition of int binary search tree
// Author: jcyang[at]ymail.com
// Date: 26.Jan.2010
#include <iostream>
using namespace std;

class BinNode {
public:
	BinNode* lchild;
	BinNode* rchild;
	int value;
	
	BinNode(BinNode* lchild, int value, BinNode* rchild) {
		this->lchild = lchild;
		this->value = value;
		this->rchild = rchild;
	}
	bool isLeaf() {
		return (lchild == NULL && rchild == NULL);
	}
	bool isOneChild() {
		return (lchild == NULL || rchild == NULL);
	}
	bool isOneLeftChild() {
		return (lchild != NULL && rchild == NULL);
	}
	bool isOneRightChild() {
		return (lchild == NULL && rchild != NULL);
	}
};

class IntBST {
private:
	BinNode* root;
	
	void backOrderHelper(BinNode* subroot) {
		if (subroot->lchild != NULL)
			backOrderHelper(subroot->lchild);
		if (subroot->rchild != NULL)
			backOrderHelper(subroot->rchild);
		cout << subroot->value << "   ";
	}
	
	void precOrderHelper(BinNode* subroot) {
		cout << subroot->value << "   ";
		if (subroot->lchild != NULL)
			precOrderHelper(subroot->lchild);
		if (subroot->rchild != NULL)
			precOrderHelper(subroot->rchild);
	}

	void midOrderHelper(BinNode* subroot) {
		if (subroot->lchild != NULL)
			midOrderHelper(subroot->lchild);
		cout << subroot->value << "   ";
		if (subroot->rchild != NULL)
			midOrderHelper(subroot->rchild);
	}
public:
	IntBST(int* initArr, int size) {
		if (size <= 0)
			return ;
		root = new BinNode(NULL, initArr[0], NULL);
		for (int i = 1; i < size; i++)
			insert(initArr[i]);
	}

	void insert(const int& val) {
        BinNode* subroot = root;
        BinNode* parent;
        bool isLeft;

        while (subroot != NULL) {
            parent = subroot;
            if (val >= subroot->value)  {
                subroot = subroot->rchild;
                isLeft = false;
            } else {
                subroot = subroot->lchild;
                isLeft = true;
            }
        }
        if (isLeft) 
            parent->lchild = new BinNode(NULL, val, NULL);
        else
            parent->rchild = new BinNode(NULL, val, NULL);
	}

	bool find(int val) {
		BinNode* subroot = root;
		while (subroot != NULL) {
			if (val > subroot->value)
				subroot = subroot->rchild;
			else if (val < subroot->value)
				subroot = subroot->lchild;
			else
				return true;
		}
		return false;
	}

	void backOrder() {
		BinNode* subroot = root;
		backOrderHelper(subroot);
	}

	void precOrder() {
		BinNode* subroot = root;
		precOrderHelper(subroot);
	}

	void midOrder() {
		BinNode* subroot = root;
		midOrderHelper(subroot);
	}
};
