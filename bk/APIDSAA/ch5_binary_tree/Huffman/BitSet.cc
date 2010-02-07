// Module Name: BitSet.cc
// Objective: tester for the BitSet class
// Author: jcyang[at]ymail.com
// Date: 6.Feb.2010
// Revision: alpha

#include <iostream>
#include "BitSet.h"
using namespace std;

int main()
{
	BitSet bits(10);
	
	cout << bits << endl;
	cout << "+ length = " << bits.getLength() << endl;

	for (int i = 0; i < 10; i = i + 2) 
		bits.set(i, 1);
	cout << bits << endl;

	BitSet bits2("101010");
	cout << bits2 << endl;

	BitSet* bits3 = new BitSet("111000");
	cout << bits3 << endl;

	BitSet* bits4 = new BitSet("1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001", true);

	cout << bits4 << "   " << hex << bits4->getLength();
}
