// Module Name: GenNode.h
// Objective: provide the generic general node implementation
// Author: jcyang[at]ymail.com
// Date: 14.Feb.2010
// Revision: alpha

#ifndef __GENERIC_GENERAL_NODE__
#define __GENERIC_GENERAL_NODE__

#include "..\ch4_list\LList.h"

typedef enum {
	GEN_NODE_NDELIM,
	GEN_NODE_LDELIM,
	GEN_NODE_RDELIM
} GenNodeDelim;

template<class Elem>
class GenNode {
	friend ostream& operator<<(ostream& out, const GenNode<Elem> node) { }

protected:
	Elem value;
	SingleLinkedList< GenNode<Elem>* > children;
	GenNodeDelim delim;

public:
	GenNode(const Elem initval) : 
					value(initval), delim(GEN_NODE_NDELIM) { }
	GenNode(const GenNodeDelim initdelim) : 
					delim(initdelim) { }
	GenNode() { }

	void addChild(GenNode<Elem>* child) {
		children.append(child);
	}

	GenNode<Elem>* getHeadChild() {
		return children.head;
	}
	GenNode<Elem>* getTailChild() {
		return children.tail;
	}

	bool isLeaf() {
		return (children.getSize() == 0)
	}

	bool isLeftDelim() {
		return (delim == GEN_NODE_LDELIM);
	}
	bool isRightDelim() {
		return (delim == GEN_NODE_RDELIM);
	}
	bool isDelim() {
		return (delim != GEN_NODE_NDELIM);
	}
};

#endif
