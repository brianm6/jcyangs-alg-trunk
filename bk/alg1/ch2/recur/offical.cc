//: ch2 : offical.cc
// offical edition of Permutation.cc
#include <iostream>
using namespace std;

template<class T>
void swap(T list[], int p1, int p2) 
{
	T t;
	t = list[p1];
	list[p1] = list[p2];
	list[p2] = t;
}

template<class T> 
void permutation(T list[], int mid, int end)
{
	static int count;
	if (mid == end) {
		cout << ++count << " : ";
		for (int i = 0; i <= end; i++)
			cout << list[i] << ' ';
		cout << endl;
		return ;
	} else {
		for (int i = mid; i <= end; i++) {
			swap(list, mid, i);
			permutation(list, mid + 1, end);
			swap(list, mid, i);
		}
	}
}

int main()
{
	int cn;
	int *intElems;
	int mid, end;
	string *strElems;

	cout << "Number of integers = "; 
	cin >> cn;
	intElems = new int[cn];
	cout << "Integers = ";
	for (int i = 0; i < cn; i++)
		cin >> intElems[i];
	
	cout << "mid = ?, end = ?"; 
	cin >> mid; cin >> end;
	permutation(intElems, mid, end);

	cout << "Number of strings = ";
	cin >> cn;
	strElems = new string[cn];
	cout << "Strings = ";
	for (int i = 0; i < cn; i++)
		cin >> strElems[i];

	cout << "mid = ?, end = ?";
	cin >> mid; cin >> end;
	permutation(strElems, mid, end);

	return 0;
}
	
