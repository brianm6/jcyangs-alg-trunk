// Module Name: AList.cc
// Objective: demonstarte the usage of generic array-based list implementation
// Author: jcyang[at]ymail.com
// Date: 29.Jan.2010
// Revision: alpha

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "AList.h"
#include "../BST/Comp.h"
using namespace std;

int main()
{
	const int maxsize = 256;
	int size;
	int* intArr;
	int inputMethod;
	int addInt;
	int removeInt;
	int findInt;

	srand(time(NULL));
	
	// input the list
	cout << "size = ";
	cin >> size;
	intArr = new int[size];

	cout << "input method(random = 0, manual = 1) = ";
	cin >> inputMethod;
	if (inputMethod == 0) {
		for (int i = 0; i < size; i++)
			intArr[i] = rand() % 10;
	} else if (inputMethod = 1) {
		for (int i = 0; i < size; i++)
			cin >> intArr[i];
	}
	cout << endl;

	cout << "+ The input integer list is : " << endl;
	for (int i = 0; i < size; i++)
		cout << intArr[i] << "   ";
	cout << endl;

	
	// create the list
	SAList<int, IntComparator> saList(intArr, size, maxsize);
	
	cout << "+ the list is : " << endl;
	saList.show();
	cout << endl;

	// test the [] operator
	cout << saList[1] << endl;


	// add one element
	cout << "add integer = ";
	cin >> addInt;

	saList.insert(addInt);

	cout << "+ the new list is : " << endl;
	saList.show();
	cout << endl;


	// find one element
	cout << "find integer = ";
	cin >> findInt;

	int findPos = -1;
	if ((findPos = saList.find(findInt)) != -1) 
		cout << "+ found integer " << findInt << " position = " << findPos << endl;
	else
		cout << "+ could not find integer " << findInt << endl;
	cout << endl;


	// remove one element
	cout << "remove integer = ";
	cin >> removeInt;

	int removePos;
	if (saList.remove(removeInt, removePos))
		cout << "+ removed integer " << removeInt << " position = " << removePos << endl;
	else
		cout << "+ could not remove integer " << removeInt << endl;

	cout << "+ after remove,the list is : " << endl;
	saList.show();
}
