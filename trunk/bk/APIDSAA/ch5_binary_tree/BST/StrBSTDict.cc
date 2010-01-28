// Module Name: StrBSTDict.cc
// Objective: implementate the string dictionary based on  BSTDict 
// Author: jcyang[at]ymail.com
// Date: 28.Jan.2010
// Revision: alpha

#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cstdlib>
#include "BSTDic.h"
#include "Comp.h"
#include "Random.h"
using namespace std;

int main()
{
	int size;
	string* keyArr;
	string* valArr;
	int method;
	int strLen;
	const int MAX_DICT_SIZE = 256;
	string searchKey;
	string addKey, addValue;
	
	srand(time(NULL));

	cout << "dict size = ";
	cin >> size;
	keyArr = new string[size];
	valArr = new string[size];
	cout << endl;

	cout << "manual(0) or random(1) = ";
	cin >> method;
	if (method == 0) {
		for (int i = 0; i < size; i++) {
			cout << i + 1 << "st key-value pair = ";
			cin >> keyArr[i] >> valArr[i];
		}
	} else if (method == 1) {
		cout << "the length of the string = ";
		cin >> strLen;
		for (int i = 0; i < size; i++) {
			keyArr[i] = randomStrGen(strLen);
			valArr[i] = randomStrGen(strLen);
		}
	}
	
	cout << "+ The key-value pairs are : " << endl;
	for (int i = 0; i < size; i++) 
		cout << keyArr[i] << setw(30) << valArr[i] << endl;
	cout << endl;
		
	BSTDict<string, StringComparator, string, StringComparator> dict(keyArr, valArr, size, MAX_DICT_SIZE);
	
	cout << "adding key-value pair = ";
	cin >> addKey >> addValue;
	dict.add(addKey, addValue);

	cout << "searching key = ";
	cin >> searchKey;
	cout << "+ The companion value = " << dict.get(searchKey) << endl; 

	return 0;
}



	
