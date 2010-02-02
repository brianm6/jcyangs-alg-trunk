// Module Name: SLList.cc
// Objective: application of generic (single/double) sorted-linked-list implementation
// Author: jcyang[at]ymail.com
// Date: 2.Feb.2010
// Revision: alpha

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "SLList.h"
#include "..\BST\Comp.h"
#include "..\BST\Random.h"
using namespace std;

int main()
{
	int size;
	string* strArr;
	int inputMethod;
	int strLength;
	string insertStr;
	string maxStr;

	srand(time(NULL));

	cout << "size = "; 
	cin >> size;
	strArr = new string[size];
	cout << "string length = ";
	cin >> strLength;

	cout << "input method (random = 0, manual = 1) = ";
	cin >> inputMethod;
	for (int i = 0; i < size; i++) {
		if (inputMethod == 0) 
			strArr[i] = randomStrGen(strLength);
		else if (inputMethod == 1) {
			cout << i << "st string = ";
			cin >> strArr[i];
		}
	}

	cout << "+ The input string array is: " << endl;
	for (int i = 0; i < size; i++) 
		cout << strArr[i] << endl;
	cout << endl;

	// SSLList<string, StringComparator> list(strArr, size);
	SDLList<string, StringComparator> list(strArr, size);

	cout << "+ After create the sorted single-linked list is : " << endl;
	list.show();
	cout << endl;
	
	cout << "insert string = ";
	cin >> insertStr;
	list.insert(insertStr);
	cout << "+ After insert string " << insertStr << " : " << endl;
	list.show();
	cout << endl;

	list.peekMax(maxStr);
	cout << "+ peekMax return : " << maxStr << endl;
	cout << "+ After peek max string : " << endl;
	list.show();
	cout << endl;

	list.removeMax(maxStr);
	cout << "+ removeMax return : " << maxStr << endl;
	cout << "+ After remove max string : " << endl;
	list.show();
	cout << endl;

	return 0;
}
