// Module Name: SLPriorQueue.h
// Objective: provide the generic implementation of sorted list priority queue
// Author: jcyang[at]ymail.com
// Date: 29.Jan.2010
// Revisoin: Alpha

#include "IPriorityQueue.h"
#include "AList.h"
#include <string>
#include "..\BST\Comp.h"
using namespace std;

template<class Elem, class Prior>
class ElemPrior {
public:
	Elem elem;
	Prior prior;
	ElemPrior(const Elem elem, const Prior prior) {
		this->elem = elem;
		this->prior = prior;
	}
	ElemPrior() { }
};

template<class Elem, class Prior, class PComp>
class ElemPriorComp {
public:
	static bool gt(ElemPrior<Elem, Prior> e1, ElemPrior<Elem, Prior> e2) {
		return PComp::gt(e1.prior, e2.prior);
	}

	static bool ge(ElemPrior<Elem, Prior> e1, ElemPrior<Elem, Prior> e2) {
		return PComp::ge(e1.prior, e2.prior);
	}

	static bool lt(ElemPrior<Elem, Prior> e1, ElemPrior<Elem, Prior> e2) {
		return PComp::lt(e1.prior, e2.prior);
	}

	static bool eq(ElemPrior<Elem, Prior> e1, ElemPrior<Elem, Prior> e2) {
		return PComp::eq(e1.prior, e2.prior);
	}
};

template<class Elem, class Prior>
class Test {
public:
    Test() {
        ElemPrior<string, int> elemPriorArr[10];
        int size = 1;
        int maxsize = 2;
        SAList< ElemPrior<string, int>, ElemPriorComp<string, int, IntComparator> > salist(elemPriorArr, size, maxsize);
        elemPriorArr[2] = salist[1];
    }
};

int main()
{
    Test<string, int> testObj;
    
    return 0;
}