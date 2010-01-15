//: Permutation : MyCount.cc
// count the total permutation
// by jcyang email: jcyangzh@gmail.com
#include <iostream>
#include <string>
using namespace std;

double getFactorial(int n) {
	double factorial = 1;
	for (int i = 1; i <= n; i++)
		factorial *= i;
	return factorial;
}

double getCombination(int whole, int part) {
	double sum = 1;
	for (int i = whole; i > whole - part; i--)
		sum *= i;
	return sum / getFactorial(part);
}

double countPermutations(string str) {
	const int MAX_ASCII= 127;
	const int MAX_ELEMS = 20;

	int *numCounts;
	int length;
	int elemsCount;
	bool bElemDup;
	double dupElemsPermuCount;

	numCounts = new int[MAX_ASCII + 1]; // only support ASCII code
	memset(numCounts, 0, sizeof(int) * (MAX_ASCII + 1)); 

	length = str.size();
	if (length > MAX_ELEMS)
		return -1;

	bElemDup = false;
	dupElemsPermuCount = 1;

	for (string::iterator it = str.begin(); it != str.end(); ++it) 
		numCounts[*it]++;
	
	for (int i = 0; i <= MAX_ASCII; i++) {
		if (numCounts[i] > 1) {
			bElemDup = true;
			dupElemsPermuCount *= getCombination(length, numCounts[i]);
			length -= numCounts[i];
		}
	}
	
	if (bElemDup)
		return dupElemsPermuCount * getFactorial(length);
	else
		return getFactorial(length);
}

int main()
{
	string str;
	cin >> str;
	cout <<countPermutations(str);
	return 0;
}
