// Module Name: IntBST.cc
// Objective: make use of int binary search tree
// Author: jcyang[at]ymail.com
// Date: 27.Jan.2010

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "IntBST.h"
using namespace std;

int main() 
{
	int* initArr;
	int size;
	int num;
	int travOrder;
	int inputMethod;

	cout << "size = ";
	cin >> size;
	initArr = new int[size];

	cout << "random(0) or manual(1) = ";
	cin >> inputMethod;
	if (inputMethod == 0) {
		srand(time(NULL));
		for (int i = 0; i < size; i++)
			initArr[i] = rand() % 10 + 1;
	} else if (inputMethod == 1) {
		cout << "initArr = ";
		for (int i = 0; i < size; i++)
		cin >> initArr[i];
	}

	cout << "+ The input number array = " << endl;
	for (int i = 0; i < size; i++) 
		cout << initArr[i] << "   ";
	cout << endl;

	IntBST intbst(initArr, size);

	cout << "number to find = ";
	cin >> num;
	if (intbst.find(num))
		cout <<"+ Find the number " << num << endl;
	else
		cout <<"+ Could not find the number " << num << endl;

	cout << "traversal(prec = 0, mid = 1, back = 2) = ";
	cin >> travOrder;
	cout << "+ The travesal result is : " << endl;
	switch (travOrder) {
		case 0:
			intbst.precOrder();
			break;
		case 1:
			intbst.midOrder();
			break;
		case 2:
			intbst.backOrder();
			break;
	}
	
	return 0;
}
