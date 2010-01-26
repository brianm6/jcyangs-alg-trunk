// Module Name: BST.h
// Objective: provide generic interface for binary search tree
// Author: jcyangzh[at]gmail.com
// Date: 26.Jan.2010
#include "BinNode.h"

template<class Elem>
class BST {
private:
	BinNode<Elem>* root;
public:
	void insert(const Elem& e) = 0;
	void remove(const Elem& e, BinNode<Elem>& node) = 0;
	void removeAny(BinNode<Elem>& node) = 0;
	void clear() = 0;
	BST(const Elem* elemArr, int size) = 0;
};

class IntBST : public BST<int> { };
