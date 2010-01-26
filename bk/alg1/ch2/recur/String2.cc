//: ch2 : String2.cc
// operations on standard string type
#include <iostream>
#include <string>
using namespace std;

int main()
{
	string str = "abc";
	cout << "str = " << str << endl;
	
	cout << "str.size() = " << str.size() << endl;
	cout << "str.length() = " << str.length() << endl;
	
	cout << "use iterator iterate str: " << endl;
	string::iterator it;
	for (it = str.begin(); it < str.end(); it++) 
		cout << *it;
	cout << endl;

	cout << "use index to iterate str: " << endl;
	for (int i = 0; i < str.size(); i++)
		cout << str[i];
	cout << endl;

	string t = str; t.erase(); 
	cout << "str.erase() = " << t << endl;
	t = str; t.erase(0, 1);
	cout << "str.erase(0, 1) = " << t << endl;
	t = str; it = str.begin(); t.erase(it);
	cout << "str.erase(it) it = str.begin() : " << t << endl;
	//t = str; it = str.end() - 1; t.erase(it);
	//cout << "str.erase(it) it = str.end() - 1 : " << t << endl;

	//t = str; it = t.end(); t.erase(it);
	t = str; it = t.end() - 1; t.erase(it);
	cout << "t.erase(it) it = t.end() : " << t << endl;

	return 0;
}
