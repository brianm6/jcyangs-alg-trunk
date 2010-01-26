//: Permutation : MyCount.cc
// count the total permutation
// by jcyang email: jcyangzh@gmail.com
#include <iostream>
#include <string>
using namespace std;

big_int getFactorial(int n) {
	big_int factorial = 1;
	for (int i = 1; i <= n; i++)
		factorial *= i;
	return factorial;
}

big_int getCombination(int whole, int part) {
	big_int sum = 1;
	for (int i = whole; i > whole - part; i--)
		sum *= i;
	return sum / getFactorial(part);
}

int main()
{
    int whole, part;
    cin >> whole >> part;
    cout << getCombination(whole, part) << endl;
	return 0;
}
