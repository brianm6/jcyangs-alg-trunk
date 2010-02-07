// Module Name: BinNode.h
// Objective: provide the generic implementation of binary node
// Author: jcyang[at]ymail.com
// Date: 3.Feb.2010
// Revision: alpha

template<class Elem>
class BinNode {
public:
	Elem value;
	BinNode* rchild;
	BinNode* lchild;
	BinNode(const Elem value, BinNode* lchild, BinNode* rchild) {
		this->value = value;
		this->lchild = lchild;
		this->rchild = rchild;
	}
	bool isLeaf() {
		return (this->lchild == NULL && this->rchild == NULL);
	}
};