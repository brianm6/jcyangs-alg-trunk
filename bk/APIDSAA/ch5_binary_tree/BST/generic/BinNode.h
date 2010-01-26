// Module Name: BinNode.h
// Objective: provide generic class for binary node
// Author: jcyangzh[at]gmail.com
// Date: 26.Jan.2010

<class Elem>
template class BinNode {
public:
	BinNode<Elem>* rchild;
	BinNode<Elem>* lchild;
	Elem value;
}
