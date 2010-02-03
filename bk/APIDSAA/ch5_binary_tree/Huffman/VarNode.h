// Module Name: VarNode.h
// Objective: provide the generic variable node implementation
// Author: jcyang[at]ymail.com
// Date: 3.Feb.2010
// Revision: alpha

class VarBinNode {
public:
	virtual bool isLeaf() = 0;
};

template<class Elem> 
class LeafNode : public VarBinNode {
public:
	LeafNode<Elem>* 
