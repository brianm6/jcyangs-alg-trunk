// Module Name: SLPriorQueue.h
// Objective: provide the generic implementation of sorted list priority queue
// Author: jcyang[at]ymail.com
// Date: 29.Jan.2010
// Revisoin: Alpha

#include "IPriorityQueue.h"
#include "AList.h"

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
	bool gt(ElemPrior<Elem, Prior> e1, ElemPrior<Elem, Prior> e2) {
		return PComp::gt(e1.prior, e2.prior);
	}

	bool ge(ElemPrior<Elem, Prior> e1, ElemPrior<Elem, Prior> e2) {
		return PComp::ge(e1.prior, e2.prior);
	}

	bool lt(ElemPrior<Elem, Prior> e1, ElemPrior<Elem, Prior> e2) {
		return PComp::lt(e1.prior, e2.prior);
	}
};

template<class Elem, class Prior>
class Test {
public:
    Test(Elem elem, Prior prior) {
        ElemPrior<Elem, Prior> elemPriorArr[10];
        int size = 1;
        int maxsize = 2;
        SAList< ElemPrior<Elem, Prior>, ElemPriorComp<Elem, Prior> > salist(elemPriorArr, size, maxsize);
        elemPriorArr[2] = salist[1];
    }
};

int main()
{
    Test* = new Test();
    
    return 0;
}