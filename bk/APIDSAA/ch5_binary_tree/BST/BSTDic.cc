// Module Name: BSTDic.cc
// Objective: demonstrate the usage of the generic BSTDic implementation
// Author: jcyang[at]ymail.com
// Date: 28.Jan.2010
// Revision: alpha

#include <string>
#include "BSTDic.h"
#include "Comp.h"
using namespace std;

int main()
{
	int size;
	string* keyArr, valArr;
	int method;
	
	cout << "dict size = ";
	cin >> size;
	cout << endl;

	cout << "manual(0) or random(1) = ";
	cin >> method;
	if (method == 0) {
		keyArr = new string[
	BSTDict dict<string, StringComparator, string, StringComparator>(
