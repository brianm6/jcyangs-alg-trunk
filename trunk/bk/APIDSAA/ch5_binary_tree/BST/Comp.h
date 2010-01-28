// Module Name: Comp.h
// Objective: provide the usual class comparator
// Author: jcyang[at]ymail.com
// Date: 28.Jan.2010
#include <string>

template<class Elem>
class GenericComparator {
public:
	static bool eq(Elem e1, Elem e2) {
		return e1 == e2;
	}
	static bool df(Elem e1, Elem e2) {
		return !eq(e1, e1);
	}
	static bool gt(Elem e1, Elem e2) {
		return e1 > e2;
	}
	static bool ge(Elem e1, Elem e2) {
		return e1 >= e2;
	}
	static bool lt(Elem e1, Elem e2) {
		return e1 < e2;
	}
	static bool le(Elem e1, Elem e2) {
		return e1 <= e2;
	}
};

class StringComparator : public GenericComparator<std::string> {
};

class IntComparator : public GenericComparator<int> {
};

class DoubleComparator : public GenericComparator<double> {
};
