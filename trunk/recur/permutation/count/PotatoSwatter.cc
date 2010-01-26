#include <iostream>
#include <string>
using namespace std;

double getFactorial(int n) {
	int factorial = 1;
	if (n == 0)
		return 1;
	for (int i = 1; i <= n; i++)
		factorial *= i;
	return factorial;
}

double countPermutations(string s) {
	double divisor = 1;
	sort(s.begin(), s.end());
	for (string::iterator pen = s.begin(); pen != s.end(); ) {
		size_t cnt = 0;
		char value = *pen;
		while (pen != s.end() && *pen == value) ++cnt, ++pen;
		divisor *= getFactorial(cnt);
	}
	cout << divisor << endl;
	cout << getFactorial(s.size()) << endl;
	return getFactorial(s.size()) / divisor;
}

int main()
{
	string str;
	cin >> str;
	cout << countPermutations(str) << endl;
	return 0;
}
