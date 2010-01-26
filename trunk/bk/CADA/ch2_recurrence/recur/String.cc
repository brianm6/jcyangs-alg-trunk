//: ch2 : String.cc
// test the string functionality
#include <iostream>
#include <string>
using namespace std;

int main() 
{
	string str = "abc";
	string t;
	/* for (int i = 1; i < str.size(); i++) {
		string t = str;
		string::iterator it = str.begin() + i;
		t.erase(i);
		cout << t << endl;
	} */
	t = str; t.erase();
	cout << t << endl;
	t = str;
	cout << t[0] << endl;
	cout << t[1] << endl;
	cout << t[2] << endl;
	cout << t[3] << endl;
	t.erase(0, 1);
	cout << t << endl;
	string::iterator it = str.begin();
	t = str; t.erase(it);
	cout << t << endl;
	t = "abc"; it = str.end() - 1;
	cout << t << endl;
	t.erase(it);
	cout << t << endl;
	str = "This is an example pharse.";
	// string::iterator it;

	str.erase(10, 8);
	cout << str << endl;

	it = str.begin() + 9;
	str.erase(it);
	cout << str << endl;

	str.erase(str.begin() + 5, str.end() - 7);
	cout << str << endl;
	return 0;
}
