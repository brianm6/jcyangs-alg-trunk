// Module Name: AList.h
// Objective: provide the generic array-based implementation of list
// Author: jcyang[at]ymail.com
// Date: 30.Jan.2010
// Revision: Alpha

#include <iostream>
#include "IList.h"
#include "Sort.h"

template<class Elem>
class UAList : public IList<Elem> {
private:
	Elem* elemArr;
	int size;
	int maxsize;
public:
	UAList(Elem* initArr, int size, int maxsize) {
		this->size = size;
		this->maxsize = maxsize;
		elemArr = new Elem[maxsize];

		for (int i = 0; i < size; i++) 
			elemArr[i] = initArr[i];
	}

	bool insert(const Elem elem) {
		if (size == maxsize)
			return false;
		else {
			elemArr[++size] = elem;
			return true;
		}
	}

	bool remove(Elem& elem) {
		if (size == 0)
			return false;
		else {
			elem = elemArr[size--];
			return true;
		}
	}
};

template<class Elem, class EComp>
class SAList : public IList<Elem> {
private:
	Elem* elemArr;
	int size;
	int maxsize;
	
	int subFindInsertPos(Elem elem, int startPos, int endPos) {
		static bool isLeft;
		char ch;
		int midPos = (startPos + endPos) / 2;

		if (startPos > endPos) {
			if (isLeft) 
				return (startPos + 1);
			else
				return startPos;
		}
		
		if (EComp::eq(elem, elemArr[midPos]))
			return midPos;
		else if (EComp::gt(elem, elemArr[midPos])) {
			isLeft = false;
			return subFindInsertPos(elem, midPos + 1, endPos);
		} else {
			isLeft = true;
			return subFindInsertPos(elem, startPos, midPos - 1);
		}
	}

	int subFind(Elem elem, int startPos, int endPos) {
		int midPos = (startPos + endPos) / 2;
		
		if (startPos > endPos)
			return -1;
		
		if (EComp::eq(elem, elemArr[midPos]))
			return midPos;
		else if (EComp::gt(elem, elemArr[midPos]))
			return subFind(elem, midPos + 1, endPos);
		else
			return subFind(elem, startPos, midPos - 1);
	}

	int findInsertPos(Elem elem) {
		return subFindInsertPos(elem, 0, size - 1);
	}

public:
	SAList(Elem* initArr, int size, int maxsize) {
		this->size = size;
		this->maxsize = maxsize;
		elemArr = new Elem[maxsize];

		for (int i = 0; i < size; i++)
			elemArr[i] = initArr[i];
		sort<Elem, EComp>(elemArr, size);
	}

	Elem operator[](int index) {
		return elemArr[index];
	}

	Elem at(int index) {
		return elemArr[index];
	}

	bool insert(const Elem elem) {
		if (size == maxsize)
			return false;

		int pos = findInsertPos(elem);
		for (int i = ++size; i > pos; i--) 
			elemArr[i] = elemArr[i - 1];
		elemArr[pos] = elem;

		return true;
	}

	bool remove(Elem& elem) {
		int pos;

		if (size == 0)
			return false;

		if ((pos = find(elem)) == -1) 
			return false;

		for (int i = pos; i < size - 1; i++)
			elemArr[i] = elemArr[i + 1];
		size--;
		return true;
	}

	bool remove(Elem& elem, int& pos) {
		if (size == 0)
			return false;
		if ((pos = find(elem)) == -1)
			return false;

		for (int i = pos; i < size - 1; i++)
			elemArr[i] = elemArr[i + 1];
		--size;
		return true;
	}

	bool removeMax(Elem& elem) { 
		if (size == 0)
			return false;
		elem = elemArr[--size];
		return true;
	}

	bool removeMin(Elem& elem) {
		if (size == 0)
			return false;
		elem = elemArr[0];
		--size;
		return true;
	}

	int find(Elem elem) {
		return subFind(elem, 0, size);
	}

	bool findMax(Elem& elem) {
		if (size == 0)
			return false;
		elem = elemArr[size - 1];
		return true;
	}

	bool findMin(Elem& elem) {
		if (size == 0)
			return false;
		elem = elemArr[0];
		return true;
	}

	int getSize() {
		return size;
	}

	void show() {
		for (int i = 0; i < size; i++)
			std::cout << elemArr[i] << "   ";
		std::cout << std::endl;
	}
};
