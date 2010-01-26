//: ch2 : Permutation.cc
// simulation the process of permutation
#include <iostream>
#include <string>
using namespace std;

int getPermuNums(string elems)
{
	if (elems.size() == 1) 
		return 1;
	else {
		int result = 0;
		for (int i = 0; i < elems.size(); i++) {
			string t = elems;
			t.erase(i, 1);
			result += getPermuNums(t);
		}
		return result;
	}
}

void swap(string &str, int pos1, int pos2)
{
	char tch;

	tch = str[pos1];
	str[pos1] = str[pos2];
	str[pos2] = tch;
}

void permute(string elems, int mid, int end)
{
	static int count;
	if (mid == end) {
		cout << ++count << " : " << elems << endl;
		return ;
	} else {
		for (int i = mid; i <= end; i++) {
			swap(elems, mid, i);
			permute(elems, mid + 1, end);
			swap(elems, mid, i);
		}
	}
}

int main()
{
	string elems;
	int mid;
	int end;

	cout << "The elems of the permutation : ";
	cin >> elems;

	cout << "Total number of the permutation is : " << getPermuNums(elems) << endl;
	
	cout << "Permutation arguments: " << endl;
	cout << "\tmid = "; cin >> mid;
	cout << "\tend = "; cin >> end;
	permute(elems, mid, end);

	return 0;
}
