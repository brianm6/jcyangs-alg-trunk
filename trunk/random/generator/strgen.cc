// Module Name: StrGen.cc
// Objective: generate random strings with standard random routines
// Author: jcyang[at]ymail.com
// Date: 27.Jan.2010

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

string randomStrGen(int length) {
	static string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	string result;
	result.resize(length);

	for (int i = 0; i < length; i++)
		result[i] = charset[rand() % charset.length()];
	
	return result;
}

int main()
{
	int nums;

	srand(time(NULL));
	cin >> nums;
	while(nums--)
		cout << randomStrGen(12) << endl;

	return 0;
}
