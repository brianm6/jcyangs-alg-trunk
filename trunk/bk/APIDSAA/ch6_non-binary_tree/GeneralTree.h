// Module Name: GeneralTree.h
// Objective: provide the generic general tree implementation
// Author: jcyang[at]ymail.com
// Date: 14.Feb.2010
// Revision: alpha

#ifndef __GENERAL_TREE__
#define __GENERAL_TREE__


template<class Elem>
class GeneralTree {
private:
	GenNode<Elem>* root;

	void midTravesal(GenNode<Elem>* subroot) {
		if (subroot->isLeaf())	
			cout << subroot->value << "  ";
		else {
			cout << '|' << "   ";
			GenNode<Elem>* currChild = subroot->getHeadChild();
			if (currChild != NULL) {
				while (currChild->next != NULL) {
					midTravesal(currChild);
					currChild = currChild->next;
				}
				midTravesal(currChild);
			}
		}
	}
		
public:
	GeneralTree(Elem* initArr) {
		int nLeftBrk = 0;
		root = createTree(initArr, nLeftBrk);
	};
	
	// deserialize with bracket pairs.e.g. A(A1 ( A11 A12) A2 A3 (A31 A32))
	GenNode<Elem>* createTree(Elem* initElem, int& nLeftBrk) {
		if (initElem->isLeftDelim()) {
			nLeftBrk++;
			GenNode<Elem>* parentNode = new GenNode<Elem>(initElem[-1]);
			int leftBrk = 1;
			while (leftBrk != 0) // the whole process done
				parentNode.addChild(createTree(++initElem, leftBrk));
		} else if (initElem->isRightDelim()) 
			nLeftBrk--;
		else {
			return new GenNode<Elem>(*initElem);
		}
	}
	
	// do serialization
	GenNode<Elem>* serialize() {
	}

	// show the tree
	void show() {
		midTravesal(root);
	}
};
		

#endif
