// Module Name: StrBST.cc
// Objective: use generic BST implementation to support string BST
// Author: jcyang[at]ymail.com
// Date: 27.Jan.2010

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "alg.h"
#include "BST.h"
using namespace std;

class StrComp {
public:
	static bool ge(string s1, string s2) {
		if (s1 >= s2)
			return true;
		else
			return false;
	}
};

int main()
{
	int size;
	int method;
	int length;
	string *strArr;
	string fstr;
	int order;

	srand(time(NULL));

	cout << "size = ";
	cin >> size;
	strArr = new string[size];

	cout << "random(0) or manual(1) = ";
	cin >> method;
	if (method == 0) {
		cout << "length of string = ";
		cin >> length;
		for (int i = 0; i <size; i++)
			strArr[i] = randomStrGen(length);
	} else if (method == 1) {
		for (int i = 0; i < size; i++)
			cin >> strArr[i];
	}
	
	cout << "+ The initialize string array is : " << endl;
	for (int i = 0; i < size; i++) 
		cout << strArr[i] << "   ";
	cout << endl;
	
	BST<string, StrComp> strbst(strArr, size);
	
	cout << "find string = ";
	cin >> fstr;
	cout << strbst.find(fstr) << endl;
	
	cout << "precOrder(0) or midOrder(1) or backOrder(2) = ";
	cin >> order;
	switch (order) {
		case 0:
			strbst.precOrder();
			break;
		case 1:
			strbst.midOrder();
			break;
		case 2:
			strbst.backOrder();
			break;
	}

	return 0;
}
