#include <iostream>
using namespace std;
void f();

int main()
{
	static int a;
	cout << a << endl;
	f();
	f();
}

void f() {
	static int a;
	cout << a << endl;
	a++;
}
