// Module Name : GeneralTree.cc
// Objective: demonstrate the usage of general tree
// Author: jcyang[at]ymail.com
// Date: 17.Feb.2010
// Revision: alpha

#include <iostream>
#include <string>
#include "GenNode.h"
#include "GeneralTree.h"
using namespace std;

/*GenNode<char>** loadTree(string inStr) {
	size_t size = inStr.length();
	GenNode<char>** initArr = new GenNode<char>*[size];
	for (int i = 0; i < size; i++) {
		if (inStr[i] == '(')
			initArr[i] = new GenNode<char>(GEN_NODE_LDELIM);
		else if (inStr[i] == ')')
			initArr[i] = new GenNode<char>(GEN_NODE_RDELIM);
		else
			initArr[i] = new GenNode<char>(inStr[i]);
	}
	return initArr;
}*/

		
int main()
{
	string inStr;
	cin >> inStr;

	GenNode<char>** initArr = loadTree(inStr);
	GeneralTree<char> tree(initArr);
	tree.show();
	
	return 0;
}
